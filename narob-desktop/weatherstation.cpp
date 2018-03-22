#include "weatherstation.h"

#include <QDate>
#include <QDebug>

WeatherStation::WeatherStation(ObservationsModel *model, WeatherTab *parent) :
    QObject(parent),
    mObservationsModel(model)
{
    setComPort();
    if(mRunning){
        connect(mComPort, &QSerialPort::readyRead, this, &WeatherStation::getStationData);
        connect(&mTimer, &QTimer::timeout, this, &WeatherStation::handleTimeout);
        connect(mComPort, &QSerialPort::errorOccurred, this, &WeatherStation::handleError);

        mTimer.start(1000);
    }
}

WeatherStation::~WeatherStation()
{
    delete mComPort;
}

void WeatherStation::setComPort()
{
    const QList<QSerialPortInfo> allPorts = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &portInfo : allPorts) {
        if(portInfo.vendorIdentifier() == 0x403 &&
                portInfo.productIdentifier() == 0x6001 &&
                portInfo.manufacturer() == "FTDI"){
            mComPort = new QSerialPort(portInfo);
            mComPort->setBaudRate(9600);
        }
    }

    if(mComPort != nullptr){
        if(mComPort->open(QIODevice::ReadOnly)){
            mRunning = true;
        }else{
            qDebug() << mComPort->error();
            qDebug("WRITE CODE");
        }
    }
}


void WeatherStation::getStationData()
{
    mReadData.append(mComPort->readAll());

    if(!mTimer.isActive()){
        mTimer.start(1000);
    }
}

void WeatherStation::handleTimeout()
{
    if(mReadData.contains("Z")){
        int i = mReadData.lastIndexOf("Z");
        mLine.append(mReadData.mid(0, i + 1));
        mReadData = mReadData.mid(i + 1);

        if(mLine.contains("CSS")){
            handleCompleteLine(mLine.mid(mLine.indexOf("CSS")));
        }
        mLine = "";

    }else{
        mLine.append(mReadData);
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

void WeatherStation::handleCompleteLine(QByteArray line)
{
    // Check for size = 54 first. *******

    // 0's in speed and gust and 115 in direction
    // (also with trailing 3 before the Z)
    // wind sensor not plugged in OR
    // zero wind.  Does not seem to be error message.
    // Zero wind sends the direction over 360.
    // Disregard wind under 2 and this should fix
    // itself.  May check for low wind and high
    // direction value to invalidate wind.

    // add validity check

    mTemps += line.mid(3, 5).trimmed().toDouble();
    mHums += line.mid(8, 5).trimmed().toDouble();
    mPres += line.mid(13, 5).trimmed().toDouble();
    mVPs += line.mid(18, 5).trimmed().toDouble();
    mDpts += line.mid(23, 5).trimmed().toDouble();
    mDAs += line.mid(28, 5).trimmed().toInt();
    mWSpeeds += line.mid(43, 3).trimmed().toInt();
    mWGusts += line.mid(46, 3).trimmed().toInt();
    mWDirs += relativeWind(line.mid(49, 3).trimmed().toInt(), line.mid(43, 3).trimmed().toInt());

    mSampleCount += 1;

    int span = 0;
    QTime now = QTime::currentTime();

    if(now.minute() > mLastTime.minute()){
        span = now.minute() - mLastTime.minute();
    }else if(now.minute() == 0 && mLastTime.minute() != 0){
        span = 60 - mLastTime.minute();
    }

    if(span){
        if(mSampleCount){
            writeToDB();
        }else if(span > 5){
            qDebug("More than 5 minutes without weather - WRITE CODE");
        }
    }
}

double formatNum(double num, int decimals)
{
    return QString::number(num, 'f', decimals).toDouble();
}

void WeatherStation::writeToDB()
{
    Observation o;

    QDateTime cDT;
    cDT.setDate(QDate::currentDate());
    cDT.setTime(QTime(QTime::currentTime().hour(), QTime::currentTime().minute()));
    o.setValue("dateTime", cDT);

    o.setValue("temperature", formatNum(mTemps / mSampleCount, 1));
    o.setValue("humidity", formatNum(mHums / mSampleCount, 1));
    o.setValue("pressure", formatNum(mPres / mSampleCount, 2));
    o.setValue("vaporPressure", formatNum(mVPs / mSampleCount, 2));
    o.setValue("dewPoint", formatNum(mDpts / mSampleCount, 1));
    o.setValue("densityAltitude", mDAs / mSampleCount);
    o.setValue("windSpeed", mWSpeeds / mSampleCount);
    o.setValue("windGust", mWGusts / mSampleCount);
    o.setValue("windDirection", mWDirs / mSampleCount);

    mObservationsModel->addObservation(o);

    emit newWeatherWritten();
    emit sendStatus(QString("Current Weather ->   "
                            "Temperature: %1      "
                            "Humidity: %2      "
                            "Pressure: %3      "
                            "Vapor Press: %4      "
                            "Dew Point: %5      "
                            "Density Altitude: %6      "
                            "Wind Speed: %7      "
                            "Wind Gust: %8      "
                            "Wind Direction: %9")
                    .arg(o.value("temperature"))
                    .arg(o.value("humidity"))
                    .arg(o.value("pressure"))
                    .arg(o.value("vaporPressure"))
                    .arg(o.value("dewPoint"))
                    .arg(o.value("densityAltitude"))
                    .arg(o.value("windSpeed"))
                    .arg(o.value("windGust"))
                    .arg(o.value("windDirection")));

    mTemps = 0;
    mHums = 0;
    mPres = 0;
    mVPs = 0;
    mDpts = 0;
    mDAs = 0;
    mWSpeeds = 0;
    mWGusts = 0;
    mWDirs = 0;

    mSampleCount = 0;

    mLastTime = QTime::currentTime();
}
