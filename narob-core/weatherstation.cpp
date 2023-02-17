#include "weatherstation.h"

#include "settings.h"

#include <QSerialPortInfo>
#include <QDate>
#include <QDebug>
#include <QtMath>
#include <QThread>


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

    if(mWeatherStationPort->isOpen()){
        mWeatherStationPort->moveToThread(mComPortThread);

        connect(mComPortThread, &QThread::finished,
                mWeatherStationPort, &QObject::deleteLater);

        connect(mWeatherStationPort, &WeatherStationPort::sendStationData,
                this, &WeatherStation::handleStationData);

        mRunning = true;
        mComPortThread->start();

        if(!mComPortThread->isRunning()){
            qDebug("Com port thread not started");
        }
    }else{
        qDebug("Weather station not found");
    }
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

void WeatherStation::writeToDB()
{
    QDateTime cDT;
    QTime cT = QTime::currentTime();
    cDT.setDate(QDate::currentDate());
    cDT.setTime(QTime(cT.hour(), cT.minute()));

    double temp = mTemps / mSampleCount;

    double windAverageY = mWYs / mSampleCount;
    double windAverageX = mWXs / mSampleCount;

    double windSpeed = qSqrt(qPow(windAverageY, 2) +
                             qPow(windAverageX, 2));

    double windDirection = 180 +
                           qRadiansToDegrees(qAtan2(windAverageY,
                                                    windAverageX));

    Observation o(temp, mHums / mSampleCount, mPres / mSampleCount);

    o.setValue("dateTime", cDT);
    o.setValue("dewPoint", formatNum(mDPts / mSampleCount, 1));
    o.setValue("windSpeed", static_cast<int>(windSpeed));
    o.setValue("windDirection", static_cast<int>(windDirection));
    o.setValue("windGust", mWGustSpeed);
    o.setValue("windGustDirection", mWGustDir);
    o.setValue("samples", mSampleCount);

    int dA = o.value("densityAltitude").toInt();

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
    mDPts = 0;
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

    mDPts += val16(30);

    mWYs += -wS * qSin(qDegreesToRadians(wD));
    mWXs += -wS * qCos(qDegreesToRadians(wD));

    mSampleCount += 1;

    if(wS > mWGustSpeed){
        mWGustSpeed = static_cast<int>(wS);
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
    mReadTimer(new QTimer(this)),
    mReadData(""),
    mLine("")
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
        qDebug() << mComPort->error() << " <- WRITE CODE";
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
    if(mComPort->isOpen()){
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
    }else{
        qDebug() << "Cannot read weather station."
                    "Com Port not open. <- Write CODE";
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
