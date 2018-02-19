#ifndef WEATHERSTATION_H
#define WEATHERSTATION_H

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QSerialPortInfo>
#include <QTime>
#include <QTimer>

#include <QObject>

#include "observationsmodel.h"
#include "weathertab.h"

class WeatherTab;

class WeatherStation : public QObject
{
    Q_OBJECT

public:
    explicit WeatherStation(ObservationsModel *model, WeatherTab *parent = nullptr);
    ~WeatherStation();

    bool isRunning(){ return mRunning; }

private slots:
    void getStationData();
    void handleTimeout();
    void handleError(QSerialPort::SerialPortError serialPortError);

private:
    void setComPort();

    QSerialPort *mComPort = nullptr;
    QSerialPortInfo mComPortInfo;

    void handleCompleteLine(QByteArray line);
    void writeToDB();

    QByteArray mReadData = "";
    QByteArray mLine = "";

    double mTemps = 0;
    double mHums = 0;
    double mPres = 0;
    double mVPs = 0;
    double mDpts = 0;
    int mDAs = 0;
    int mWSpeeds = 0;
    int mWGusts = 0;
    int mWDirs = 0;

    QTime mLastTime = QTime::currentTime();

    int mSampleCount;

    QTimer mTimer;

    bool mRunning = false;

    ObservationsModel *mObservationsModel;

signals:
    void newWeatherWritten();
    void sendStatus(QString status);
};

#endif // WEATHERSTATION_H
