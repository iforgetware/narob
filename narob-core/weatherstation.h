#ifndef WEATHERSTATION_H
#define WEATHERSTATION_H

#include "observations.h"
#include "narob-core_global.h"

#include <QSerialPort>
#include <QTime>
#include <QTimer>
#include <QThread>
#include <QtWidgets/QWidget>

#include <QObject>

class WeatherStationPort : public QObject
{
    Q_OBJECT

public:
    WeatherStationPort();
    ~WeatherStationPort();

    bool isOpen(){return mComPort->isOpen();}

private:
    void openComPort();
//    void wakeStation();

    QSerialPort *mComPort;

    QTimer *mReadTimer;

    QByteArray mReadData;
    QByteArray mLine;

public slots:
    void readStation();

private slots:
    void handleError(QSerialPort::SerialPortError serialPortError);

signals:
    void sendStationData(QByteArray data);
};


class NAROBCORESHARED_EXPORT WeatherStation : public QObject
{
    Q_OBJECT

public:
    explicit WeatherStation(ObservationsModel *model,
                            QObject *parent = nullptr);
    ~WeatherStation();

    bool isRunning(){ return mWeatherStationPort->isOpen(); }

private:
    int val8(int p);
    int val16(int p);
    void writeToDB();

    QThread *mComPortThread;
    WeatherStationPort *mWeatherStationPort;

    QByteArray mLoopPacket;
    QTime mLastTime;
    bool mLoopPacketGood;
    bool mRunning;
    ObservationsModel *mObservationsModel;

    double mTemps;
    double mHums;
    double mPres;
    double mDPts;
    int mWSpeeds;
    int mWDirs;
    double mWXs;
    double mWYs;
    int mWGustSpeed;
    int mWGustDir;
    int mSampleCount;

private slots:
    void handleStationData(QByteArray data);

signals:
    void newWeatherWritten();
    void sendObservation(Observation o);
    void sendStatus(QString status);
};

#endif // WEATHERSTATION_H


// Old Performaire code

//#ifndef WEATHERSTATION_H
//#define WEATHERSTATION_H

//#include "observations.h"
//#include "narob-core_global.h"

//#include <QSerialPort>
//#include <QSerialPortInfo>
//#include <QTime>
//#include <QTimer>
//#include <QtWidgets/QWidget>

//#include <QObject>

//class NAROBCORESHARED_EXPORT WeatherStation : public QObject
//{
//    Q_OBJECT

//public:
//    explicit WeatherStation(ObservationsModel *model,
//                            QObject *parent = nullptr);
//    ~WeatherStation();

//    bool isRunning(){ return mRunning; }

//private slots:
//    void getStationData();
//    void handleTimeout();
//    void handleError(QSerialPort::SerialPortError serialPortError);

//private:
//    void setComPort();

//    QSerialPort *mComPort = nullptr;
//    QSerialPortInfo mComPortInfo;

//    void handleCompleteLine(QByteArray line);
//    void writeToDB();

//    QByteArray mReadData = "";
//    QByteArray mLine = "";

//    double mTemps = 0;
//    double mHums = 0;
//    double mPres = 0;
//    double mVPs = 0;
//    double mDpts = 0;
//    int mDAs = 0;
//    int mWSpeeds = 0;
//    int mWGusts = 0;
//    int mWDirs = 0;

//    QTime mLastTime = QTime::currentTime();

//    int mSampleCount;

//    QTimer mTimer;

//    bool mRunning = false;

//    ObservationsModel *mObservationsModel;

//signals:
//    void newWeatherWritten();
//    void sendStatus(QString status);
//};

//#endif // WEATHERSTATION_H
