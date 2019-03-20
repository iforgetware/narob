#include "weatherstation.h"

#include <QSerialPortInfo>
#include <QDate>
#include <QDebug>
#include <QtMath>

int relativeWind(const int &wDir, const int &wSpeed)
{
    if(wDir > 360 || wSpeed < 1){
        return 0;
    }else if(wDir < 181){
        return wDir;
    }else{
        return 360 - wDir;
    }
}

double formatNum(double num, int decimals)
{
    return QString::number(num, 'f', decimals).toDouble();
}

// constants and conversions

static double mb_to_in = 1 / 33.86389;
static double in_to_mb = 33.86389;
//static double ft_to_m = 0.3048;

//static double in_per_mb = (1/33.86389);
static double m_per_ft = 0.3048;

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

//double calcVP(double tc, double h)
//{
//    double es = calcVPwobus(tc);
//    double emb = es * h / 100;
//    return emb * mb_to_in;
//}

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

WeatherStation::WeatherStation(ObservationsModel *model, QObject *parent) :
    QObject(parent),
    mComPort(nullptr),
    mLoopPacket(""),
    mLastTime(QTime::currentTime()),
    mReadTimer(new QTimer(this)),
    mLoopPacketGood(false),
    mRunning(false),
    mObservationsModel(model),
    mTemps(0),
    mHums(0),
    mPres(0),
    mWSpeeds(0),
    mWDirs(0),
    mWGustSpeed(0),
    mWGustDir(0)
{
    //openComPort();
}

WeatherStation::~WeatherStation()
{
}

void WeatherStation::openComPort()
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

            mComPort = new QSerialPort(this);

            mComPort->setPortName(portInfo.portName());
            mComPort->setBaudRate(19200);
            mComPort->setDataBits(QSerialPort::Data8);
            mComPort->setParity(QSerialPort::NoParity);
            mComPort->setStopBits(QSerialPort::OneStop);

            emit sendStatus("Found Davis Vantage Vue Weather Station");
        }
    }

    if(mComPort != nullptr){
        if(mComPort->open(QIODevice::ReadWrite)){
            connect(mComPort, &QSerialPort::readyRead,
                    this, &WeatherStation::readStationData);
            connect(mReadTimer, &QTimer::timeout,
                    this, &WeatherStation::sendLoopRequest);
            connect(mComPort, &QSerialPort::errorOccurred,
                    this, &WeatherStation::handleError);

            mReadTimer->start(4000);

            mRunning = true;
            emit sendStatus("Weather station running.  Waiting for data");
        }else{
            qDebug() << mComPort->error();
            qDebug("WRITE CODE");
        }
    }else{
        emit sendStatus("NO WEATHER STATION FOUND");
    }

}

int WeatherStation::val8(int p)
{
    return mLoopPacket.at(p);
}

int WeatherStation::val16(int p)
{
    return (mLoopPacket.at(p + 1) << 8) + static_cast<uchar>(mLoopPacket.at(p));
}

void WeatherStation::writeToDB()
{
    Observation o;

    QDateTime cDT;
    QTime cT = QTime::currentTime();
    cDT.setDate(QDate::currentDate());
    cDT.setTime(QTime(cT.hour(), cT.minute()));
    o.setValue("dateTime", cDT);

    o.setValue("temperature", formatNum(mTemps / mSampleCount, 1));
    o.setValue("humidity", formatNum(mHums / mSampleCount, 1));
    o.setValue("pressure", formatNum(mPres / mSampleCount, 2));
    o.setValue("densityAltitude", mDAs / mSampleCount);
    o.setValue("windSpeed", mWSpeeds / mSampleCount);
    o.setValue("windDirection", mWDirs / mSampleCount);
    o.setValue("windGust", mWGustSpeed);
    o.setValue("windGustDirection", mWGustDir);

    if(o.value("temperature").toDouble() > 0.0){
        mObservationsModel->addRow(o);

        emit newWeatherWritten();
        emit sendStatus(QString("Current Weather ->   "
                                "Temperature: %1      "
                                "Humidity: %2      "
                                "Pressure: %3      "
                                "Density Altitude: %6      "
                                "Wind Speed: %7      "
                                "Wind Gust: %8      "
                                "Wind Direction: %9")
                        .arg(o.value("temperature").toDouble())
                        .arg(o.value("humidity").toDouble())
                        .arg(o.value("pressure").toDouble())
                        .arg(o.value("densityAltitude").toInt())
                        .arg(o.value("windSpeed").toInt())
                        .arg(o.value("windGust").toInt())
                        .arg(o.value("windDirection").toInt()));

        mTemps = 0;
        mHums = 0;
        mPres = 0;
        mDAs = 0;
        mWSpeeds = 0;
        mWDirs = 0;
        mWGustSpeed = 0;
        mWGustDir = 0;

        mSampleCount = 0;
        mLastTime = cT;
    }
}

void WeatherStation::sendLoopRequest()
{
    mComPort->write("LOOP\n");
}

void WeatherStation::readStationData()
{
    QByteArray rawData = mComPort->readAll();

    if(rawData.length() > 50 && rawData.contains("LOO")){
        mLoopPacket = rawData.mid(rawData.indexOf("LOO"));

        // check loop for validity
        mLoopPacketGood = true;
    }

    if(mLoopPacketGood){
        mTemps += val16(12) / 10.0;
        mHums += val8(33);
        mPres += val16(7) / 1000.0;
        mDAs += calcDA(val16(12) / 10.0,
                       val8(33),
                       val16(7) / 1000.0);
        mWSpeeds += val8(14);
        mWDirs += relativeWind(val16(16), val8(14));

        mSampleCount += 1;

        if(val8(14) > mWGustSpeed){
            mWGustSpeed = val8(14);
            mWGustDir = val16(16);
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

    }else{
        qDebug("Bad Loop Packet - WRITE CODE");
    }
}



void WeatherStation::handleError(QSerialPort::SerialPortError serialPortError)
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
