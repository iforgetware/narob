#include "weatherstation.h"

#include "settings.h"

#include <QSerialPortInfo>
#include <QDate>
#include <QDebug>
#include <QtMath>
#include <QThread>

// constants and conversions

static double mb_to_in = 1 / 33.86389;
static double in_to_mb = 33.86389;
static double m_per_ft = 0.3048;

double formatNum(double num, int decimals)
{
    return QString::number(num, 'f', decimals).toDouble();
}

double calcVPwobus(double tc)
// Calculate the saturation vapor pressure given the temperature(celsius)
// Polynomial from Herman Wobus
{
    double eso = 6.1078;
    double c0 = 0.99999683;
    double c1 = -0.90826951E-02;
    double c2 = 0.78736169E-04;
    double c3 = -0.61117958E-06;
    double c4 = 0.43884187E-08;
    double c5 = -0.29883885E-10;
    double c6 = 0.21874425E-12;
    double c7 = -0.17892321E-14;
    double c8 = 0.11112018E-16;
    double c9 = -0.30994571E-19;

    double pol=c0+tc*
               (c1+tc*
                (c2+tc*
                 (c3+tc*
                  (c4+tc*
                   (c5+tc*
                    (c6+tc*
                     (c7+tc*
                      (c8+tc*
                       (c9)
                       )
                      )
                     )
                    )
                   )
                  )
                 )
                );

    return eso/qPow(pol, 8);
}

double calcDensity(double abspressmb, double e, double tc)
//  Calculate the air density in kg/m3
{
    double Rv=461.4964;
    double Rd=287.0531;

    double tk=tc+273.15;
    double pv=e*100.0;
    double pd= (abspressmb-e)*100.0;

    return (pv/(Rv*tk)) + (pd/(Rd*tk));
}

double calcAltitude(double d)
// Calculate the ISA altitude (meters) for a given density (kg/m3)
{
    double g=9.80665;
    double Po=101325.0;
    double To=288.15;
    double L=6.5;
    double R=8.314320;
    double M=28.9644;

    double D=d*1000.0;

    double p2=( (L*R)/(g*M-L*R) )*qLn( (R*To*D)/(M*Po) );

    double H=-(To/L)*( qExp(p2)-1.0 );

    double h=H*1000.0;

    return h;
}

double calcZ(double h)
// Calculate the Z geometric altitude (meters), given the H geopotential altitide (meters)
{
    double r=6369E3;

    return (r*h)/(r-h);
}

double calcH(double z)
// Calculate the H geopotential altitude (meters), given the Z geometric altitide (meters)
{
    double r=6369E3;

    return (r*z)/(r+z);
}

double calcAs2Press(double As, double h)
// Calculate the actual pressure (mb)from the altimeter setting (mb) and geopotential altitude (m)
{
    double k1=.190263;
    double k2=8.417286E-5;

    double p=qPow( (qPow(As,k1)-(k2*h)),(1.0/k1) );

    return p;
}

double calcDynoCorrection(double temp, double abspress, double vapress)
// Calculate dyno correction given temp(celsius), absolute pressure(inchesHg)  and vapor pressure(inchesHg)
{
    double p1=29.235/(abspress-vapress);
    double p2=qPow( ((temp+273.0)/298.0), 0.5);
    double p3=(1.18*(p1*p2) - 0.18);
    return p3;
}

// Calculate virtual temperature given temp(celsius), absolute pressure(mb)  and vapor pressure(mb)

double calcVirtualTemp(double tc, double abspressmb, double emb){

    double p1=(tc+273.15) / (1- (0.377995*emb/abspressmb) ) ;
    return p1;
}

WeatherStation::WeatherStation(ObservationsModel *model, QObject *parent) :
    QObject(parent),

    mComPortThread(new QThread()),
    mWeatherStationPort(new WeatherStationPort()),
    mLoopPacket(""),
    mLastTime(QTime::currentTime()),
    mLoopPacketGood(false),
    mRunning(false),
    mObservationsModel(model),
    mTemps(0),
    mHums(0),
    mPres(0),
    mVPs(0),
    mDPts(0),
    mWSpeeds(0),
    mWDirs(0),

    mWXs(0),
    mWYs(0),

    mWGustSpeed(0),
    mWGustDir(0),
    mSampleCount(0)
{
    // wake gives port not open error
    // console should stay awake for two minutes after last command
    // sending requests every 4 seconds or so SHOULD remove the need to re-wake

    mWeatherStationPort->moveToThread(mComPortThread);

    connect(mComPortThread, &QThread::finished,
            mWeatherStationPort, &QObject::deleteLater);

    connect(mWeatherStationPort, &WeatherStationPort::sendStationData,
            this, &WeatherStation::handleStationData);















    // check mRunning before any serial IO
















    mRunning = true;
    mComPortThread->start();
}

WeatherStation::~WeatherStation()
{
    mComPortThread->quit();
    mComPortThread->wait();
}

int WeatherStation::val8(int p)
{
    return mLoopPacket.at(p);
}

int WeatherStation::val16(int p)
{
    return (mLoopPacket.at(p + 1) << 8) + static_cast<uchar>(mLoopPacket.at(p));
}

int WeatherStation::calcDA(double t, double h, double p)
{
    double tc = (5.0/9.0) * (t - 32);
    double es = calcVPwobus(tc);
    double emb = es * h / 100.0;

    mVaporPressure = emb * mb_to_in;

    double actpressmb = p * in_to_mb;

    mAirDensity = calcDensity(actpressmb, emb, tc);
    mRelAirDensity = 100.0 * (mAirDensity / 1.225);

    double densaltm = calcAltitude(mAirDensity);
    double densaltzm = calcZ(densaltm);

    double da = densaltzm / m_per_ft;

    return qRound(da);
}

void WeatherStation::writeToDB()
{
    Observation o;

    QDateTime cDT;
    QTime cT = QTime::currentTime();
    cDT.setDate(QDate::currentDate());
    cDT.setTime(QTime(cT.hour(), cT.minute()));

    double temp = mTemps / mSampleCount;
    int dA = mDAs / mSampleCount;

    double windAverageY = mWYs / mSampleCount;
    double windAverageX = mWXs / mSampleCount;

    double windSpeed = qSqrt(qPow(windAverageY, 2) +
                             qPow(windAverageX, 2));

    double windDirection = 180 +
                           qRadiansToDegrees(qAtan2(windAverageY,
                                                    windAverageX));

    o.setValue("dateTime", cDT);
    o.setValue("temperature", formatNum(temp, 1));
    o.setValue("humidity", formatNum(mHums / mSampleCount, 1));
    o.setValue("pressure", formatNum(mPres / mSampleCount, 2));
    o.setValue("vaporPressure", formatNum(mVPs / mSampleCount, 2));
    o.setValue("dewPoint", formatNum(mDPts / mSampleCount, 1));
    o.setValue("densityAltitude", dA);
    o.setValue("windSpeed", static_cast<int>(windSpeed));
    o.setValue("windDirection", static_cast<int>(windDirection));
    o.setValue("windGust", mWGustSpeed);
    o.setValue("windGustDirection", mWGustDir);
    o.setValue("samples", mSampleCount);

    if((temp > 0.0) && (dA > -1000) && (dA < 20000)){
        mLastTime = cT;

        mObservationsModel->addRow(o);

        QString s = "   ";
        emit newWeatherWritten();
        emit sendObservation(o);
        emit sendStatus(QString("Weather @ %0 ->   "
                                "Temperature: %1"
                                + s +
                                "Humidity: %2"
                                + s +
                                "Pressure: %3"
                                + s +
                                "Density Altitude: %4"
                                + s +
                                "Wind : %5 MPH"
                                + s +
                                "Wind Direction: %6"
                                + s +
                                "Gust: %7 MPH"
                                + s +
                                "Gust Direction: %8"
                                + s +
                                "Samples: %9")
                        .arg(cDT.time().toString("h:mm AP"))
                        .arg(o.value("temperature").toDouble())
                        .arg(o.value("humidity").toDouble())
                        .arg(o.value("pressure").toDouble())
                        .arg(o.value("densityAltitude").toInt())
                        .arg(o.value("windSpeed").toInt())
                        .arg(o.value("windDirection").toInt())
                        .arg(o.value("windGust").toInt())
                        .arg(o.value("windGustDirection").toInt())
                        .arg(o.value("samples").toInt())
                        );
    }else{
        emit sendStatus("BAD WEATHER DATA - Not written to DB!");
    }

    mTemps = 0;
    mHums = 0;
    mPres = 0;
    mVPs = 0;
    mDPts = 0;
    mDAs = 0;
    mWSpeeds = 0;
    mWDirs = 0;

    mWXs = 0;
    mWYs = 0;

    mWGustSpeed = 0;
    mWGustDir = 0;

    mSampleCount = 0;
}

void WeatherStation::handleStationData(QByteArray data)
{
    mLoopPacket = data;

    double t;
    double h;
    double wS;
    double wD;

    double p = val16(7) / 1000.0;

    if(Settings::get("useConsole").toBool()){
        t = val16(9) / 10.0;
        h = val8(11);
        wD = 0;
        wS = 0;
    }else{
        t = val16(12) / 10.0;
        h = val8(33);
        wS = val8(14);
        wD = val16(16);
    }

    if(Settings::get("useOffsets").toBool()){
        t = t + Settings::get("tempOffset").toDouble();
        h = h + Settings::get("humOffset").toDouble();
    }
















// hacks for reversing wind directions
// add code and button in UI

//    if(wD > 0 && wD < 181){
//        wD = wD + 180;
//    }else if(wD > 180 && wD < 360){
//        wD = wD - 180;
//    }else{
//        wD = 0;
//    }










    mTemps += t;
    mHums += h;
    mPres += p;
    mDAs += calcDA(t, h, p);
    mVPs += mVaporPressure; // this is set in calcDA
                            // not elegant
    mDPts += val16(30);

    mWYs += -wS * qSin(qDegreesToRadians(wD));
    mWXs += -wS * qCos(qDegreesToRadians(wD));

    mSampleCount += 1;

    if(wS > mWGustSpeed){
        mWGustSpeed = wS;
        mWGustDir = static_cast<int>(wD);
    }

    QTime now = QTime::currentTime();

    int span = 0;

    if(now.minute() > mLastTime.minute()){
        span = now.minute() - mLastTime.minute();
    }else if(now.minute() == 0 && mLastTime.minute() != 0){
        span = 60 - mLastTime.minute();
    }

    if(span){
        if(mSampleCount == 0){
            qDebug("No good weather samples in one minute -- WRITE CODE");
        }else if(span > 5){
            qDebug("More than 5 minutes without weather - WRITE CODE");
        }else{
            writeToDB();
        }
    }
}


WeatherStationPort::WeatherStationPort() :
    QObject(),

    mComPort(new QSerialPort(this)),
    mReadTimer(new QTimer(this))
{
    connect(mComPort, &QSerialPort::errorOccurred,
            this, &WeatherStationPort::handleError);

    connect(mReadTimer, &QTimer::timeout,
            this, &WeatherStationPort::readStation);

    openComPort();

    mReadTimer->start(4000);
}

WeatherStationPort::~WeatherStationPort()
{
    if(mComPort->isOpen())
    {
        mComPort->close();
    }
}

void WeatherStationPort::openComPort()
{
    // davis
    //   vendor 10c4
    //   product ea60
    //   manufacturer Silicon Labs
    const QList<QSerialPortInfo> allPorts = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &portInfo : allPorts) {
        if(portInfo.vendorIdentifier() == 0x10c4 &&
           portInfo.productIdentifier() == 0xea60 &&
           portInfo.manufacturer() == "Silicon Labs"){

            mComPort->setPortName(portInfo.portName());
            mComPort->setBaudRate(19200);
            mComPort->setDataBits(QSerialPort::Data8);
            mComPort->setParity(QSerialPort::NoParity);
            mComPort->setStopBits(QSerialPort::OneStop);

            qDebug("Found Davis Vantage Vue Weather Station");
        }
    }

    if(mComPort->open(QIODevice::ReadWrite)){
        qDebug("com port open");
    }else{
        qDebug() << mComPort->error();
        qDebug("WRITE CODE");
    }
}

//void WeatherStationPort::wakeStation(){
//    QByteArray resp;

//    for(int t = 0; t < 3; t++){
//        mComPort->write("\n");
//        QThread::sleep(2);
//        resp = mComPort->readAll();
//        qDebug() << "gentle wake to hex ";
//        qDebug() << resp.toHex();
//        if(resp == "\n\r"){
//            qDebug("Davis console gentle wake successful");
//            mRunning = true;
//            return;
//        }

//        mComPort->flush();
//        QThread::sleep(1);
//        resp = mComPort->readAll();
//        qDebug() << "rude wake to hex ";
//        qDebug() << resp.toHex();

//        if(resp == "\n\r"){
//            qDebug("Davis console rude wake successful");
//            mRunning = true;
//            return;
//        }

//        qDebug("Davis still sleeping trying again in 2 seconds");

//        QThread::sleep(2);
//    }

//    qDebug("Unable to wake Davis console");
//    return;
//}

void WeatherStationPort::readStation()
{
    mComPort->write("LPS 2 1\n");

    QThread::sleep(2);

    QByteArray rawData = mComPort->readAll();

    if(rawData == "\n\r"){
        qDebug("Got ack response");
        return;
    }

    if(rawData.length() > 50 && rawData.contains("LOO")){
        emit sendStationData(rawData.mid(rawData.indexOf("LOO")));
    }else{
        qDebug() << "Bad Loop Packet -> " << rawData << " <- WRITE CODE";
        mComPort->write("\n");
        QThread::sleep(2);
        QByteArray junk = mComPort->readAll();
    }

    return;
}

void WeatherStationPort::handleError(QSerialPort::SerialPortError serialPortError)
{
    if (serialPortError == QSerialPort::ReadError) {
        qDebug() << QObject::tr("An I/O error occurred while reading "
                                "the data from port %1, error: %2")
                    .arg(mComPort->portName())
                    .arg(mComPort->errorString());
    }
}

// Old Performaire code

//#include "weatherstation.h"

//#include <QDate>
//#include <QDebug>

//WeatherStation::WeatherStation(ObservationsModel *model, QObject *parent) :
//    QObject(parent),
//    mObservationsModel(model)
//{
//    setComPort();
//    if(mRunning){
//        connect(mComPort, &QSerialPort::readyRead,
//                this, &WeatherStation::getStationData);
//        connect(&mTimer, &QTimer::timeout,
//                this, &WeatherStation::handleTimeout);
//        connect(mComPort, &QSerialPort::errorOccurred,
//                this, &WeatherStation::handleError);

//        mTimer.start(1000);
//    }
//}

//WeatherStation::~WeatherStation()
//{
//    delete mComPort;
//}

//void WeatherStation::setComPort()
//{
//    const QList<QSerialPortInfo> allPorts = QSerialPortInfo::availablePorts();
//    for (const QSerialPortInfo &portInfo : allPorts) {
//        if(portInfo.vendorIdentifier() == 0x403 &&
//           portInfo.productIdentifier() == 0x6001 &&
//           portInfo.manufacturer() == "FTDI"){
//            mComPort = new QSerialPort(portInfo);
//            mComPort->setBaudRate(9600);
//        }
//    }

//    if(mComPort != nullptr){
//        if(mComPort->open(QIODevice::ReadOnly)){
//            mRunning = true;
//        }else{
//            qDebug() << mComPort->error();
//            qDebug("WRITE CODE");
//        }
//    }
//}

//void WeatherStation::getStationData()
//{
//    mReadData.append(mComPort->readAll());

//    if(!mTimer.isActive()){
//        mTimer.start(1000);
//    }
//}

//void WeatherStation::handleTimeout()
//{
//    if(mReadData.contains("Z")){
//        int i = mReadData.lastIndexOf("Z");
//        mLine.append(mReadData.mid(0, i + 1));
//        mReadData = mReadData.mid(i + 1);

//        if(mLine.contains("CSS")){
//            handleCompleteLine(mLine.mid(mLine.indexOf("CSS")));
//        }
//        mLine = "";

//    }else{
//        mLine.append(mReadData);
//    }
//}

//void WeatherStation::handleError(QSerialPort::SerialPortError serialPortError)
//{
//    if (serialPortError == QSerialPort::ReadError) {
//        qDebug() << QObject::tr("An I/O error occurred while reading "
//                                "the data from port %1, error: %2")
//                    .arg(mComPort->portName())
//                    .arg(mComPort->errorString());
//    }
//}

//int relativeWind(const int &wDir, const int &wSpeed)
//{
//    if(wDir > 360 || wSpeed < 1){
//        return 0;
//    }else if(wDir < 181){
//        return wDir;
//    }else{
//        return 360 - wDir;
//    }
//}

//void WeatherStation::handleCompleteLine(QByteArray line)
//{
//    // Check for size = 54 first. *******

//    // 0's in speed and gust and 115 in direction
//    // (also with trailing 3 before the Z)
//    // wind sensor not plugged in OR
//    // zero wind.  Does not seem to be error message.
//    // Zero wind sends the direction over 360.
//    // Disregard wind under 2 and this should fix
//    // itself.  May check for low wind and high
//    // direction value to invalidate wind.

//    // add validity check

//    mTemps += line.mid(3, 5).trimmed().toDouble();
//    mHums += line.mid(8, 5).trimmed().toDouble();
//    mPres += line.mid(13, 5).trimmed().toDouble();
//    mVPs += line.mid(18, 5).trimmed().toDouble();
//    mDpts += line.mid(23, 5).trimmed().toDouble();
//    mDAs += line.mid(28, 5).trimmed().toInt();
//    mWSpeeds += line.mid(43, 3).trimmed().toInt();
//    mWGusts += line.mid(46, 3).trimmed().toInt();
//    mWDirs += relativeWind(line.mid(49, 3).trimmed().toInt(), line.mid(43, 3).trimmed().toInt());

//    mSampleCount += 1;

//    int span = 0;
//    QTime now = QTime::currentTime();

//    if(now.minute() > mLastTime.minute()){
//        span = now.minute() - mLastTime.minute();
//    }else if(now.minute() == 0 && mLastTime.minute() != 0){
//        span = 60 - mLastTime.minute();
//    }

//    if(span){
//        if(mSampleCount){
//            writeToDB();
//        }else if(span > 5){
//            qDebug("More than 5 minutes without weather - WRITE CODE");
//        }
//    }
//}

//double formatNum(double num, int decimals)
//{
//    return QString::number(num, 'f', decimals).toDouble();
//}

//void WeatherStation::writeToDB()
//{
//    Observation o;

//    QDateTime cDT;
//    cDT.setDate(QDate::currentDate());
//    cDT.setTime(QTime(QTime::currentTime().hour(), QTime::currentTime().minute()));
//    o.setValue("dateTime", cDT);

//    o.setValue("temperature", formatNum(mTemps / mSampleCount, 1));
//    o.setValue("humidity", formatNum(mHums / mSampleCount, 1));
//    o.setValue("pressure", formatNum(mPres / mSampleCount, 2));
//    o.setValue("vaporPressure", formatNum(mVPs / mSampleCount, 2));
//    o.setValue("dewPoint", formatNum(mDpts / mSampleCount, 1));
//    o.setValue("densityAltitude", mDAs / mSampleCount);
//    o.setValue("windSpeed", mWSpeeds / mSampleCount);
//    o.setValue("windGust", mWGusts / mSampleCount);
//    o.setValue("windDirection", mWDirs / mSampleCount);

//    if(o.value("temperature").toDouble() > 0.0){
//        mObservationsModel->addRow(o);

//        emit newWeatherWritten();
//        emit sendStatus(QString("Current Weather ->   "
//                                "Temperature: %1      "
//                                "Humidity: %2      "
//                                "Pressure: %3      "
//                                "Vapor Press: %4      "
//                                "Dew Point: %5      "
//                                "Density Altitude: %6      "
//                                "Wind Speed: %7      "
//                                "Wind Gust: %8      "
//                                "Wind Direction: %9")
//                        .arg(o.value("temperature").toDouble())
//                        .arg(o.value("humidity").toDouble())
//                        .arg(o.value("pressure").toDouble())
//                        .arg(o.value("vaporPressure").toDouble())
//                        .arg(o.value("dewPoint").toDouble())
//                        .arg(o.value("densityAltitude").toInt())
//                        .arg(o.value("windSpeed").toInt())
//                        .arg(o.value("windGust").toInt())
//                        .arg(o.value("windDirection").toInt()));
//    }

//    mTemps = 0;
//    mHums = 0;
//    mPres = 0;
//    mVPs = 0;
//    mDpts = 0;
//    mDAs = 0;
//    mWSpeeds = 0;
//    mWGusts = 0;
//    mWDirs = 0;

//    mSampleCount = 0;

//    mLastTime = QTime::currentTime();
//}
