#ifndef PREDICTION_H
#define PREDICTION_H

#include <QVector>
#include <QDate>
#include <QTime>

#include "narob-core_global.h"

class NAROBCORESHARED_EXPORT Prediction
{
public:
    explicit Prediction();
    explicit Prediction(const Prediction &prediction);


    int id() const { return mId; }
    void setId(const int &id) { mId = id; }


    int raceId() const { return mRaceId; }
    void setRaceId(int raceId) { mRaceId = raceId; }

    int vehicleId() const { return mVehicleId; }
    void setVehicleId(int vehicleId) { mVehicleId = vehicleId; }


    QDate date() const { return mDate; }
    void setDate(const QDate &Date) { mDate = Date; }

    QTime time() const { return mTime; }
    void setTime(const QTime &Time) { mTime = Time; }


    int vehicleWeight() const { return mVehicleWeight; }
    void setVehicleWeight(const int &vehicleWeight) { mVehicleWeight = vehicleWeight; }

    double riderWeight()const { return mRiderWeight; }
    void setRiderWeight(const double &riderWeight) { mRiderWeight = riderWeight; }


    double temperature() const { return mTemperature; }
    void setTemperature(const double &temperature) { mTemperature = temperature; }

    double humidity() const { return mHumidity; }
    void setHumidity(const double &humidity) { mHumidity = humidity; }

    double pressure() const { return mPressure; }
    void setPressure(const double &pressure) { mPressure = pressure; }

    double vaporPressure() const { return mVaporPressure; }
    void setVaporPressure(const double &vaporPressure) { mVaporPressure = vaporPressure; }

    double dewPoint() const { return mDewPoint; }
    void setDewPoint(const double &dewPoint) { mDewPoint = dewPoint; }

    int densityAltitude() const { return mDensityAltitude; }
    void setDensityAltitude(const int &densityAltitude) { mDensityAltitude = densityAltitude; }

    int windSpeed() const { return mWindSpeed; }
    void setWindSpeed(const int &windSpeed) { mWindSpeed = windSpeed; }

    int windGust() const { return mWindGust; }
    void setWindGust(const int &windGust) { mWindGust = windGust; }

    int windDirection() const { return mWindDirection; }
    void setWindDirection(const int &windDirection) { mWindDirection = windDirection; }


    double eTp() const { return mETp; }
    void setETp(const double &eTp) { mETp = eTp; }

    double eHp() const { return mEHp; }
    void setEHp(const double &eHp) { mEHp = eHp; }

    double ePp() const { return mEPp; }
    void setEPp(const double &ePp) { mEPp = ePp; }

    double eAp() const { return mEAp; }
    void setEAp(const double &eAp) { mEAp = eAp; }

    double eDp() const { return mEDp; }
    void setEDp(const double &eDp) { mEDp = eDp; }


    double qTp() const { return mQTp; }
    void setQTp(const double &qTp) { mQTp = qTp; }

    double qHp() const { return mQHp; }
    void setQHp(const double &qHp) { mQHp = qHp; }

    double qPp() const { return mQPp; }
    void setQPp(const double &qPp) { mQPp = qPp; }

    double qAp() const { return mQAp; }
    void setQAp(const double &qAp) { mQAp = qAp; }

    double qDp() const { return mQDp; }
    void setQDp(const double &qDp) { mQDp = qDp; }

private:
    int mId;

    int mRaceId;
    int mVehicleId;

    QDate mDate;
    QTime mTime;

    int mVehicleWeight;
    double mRiderWeight;

    double mTemperature;
    double mHumidity;
    double mPressure;
    double mVaporPressure;
    double mDewPoint;
    int mDensityAltitude;
    int mWindSpeed;
    int mWindGust;
    int mWindDirection;

    double mETp;
    double mEHp;
    double mEPp;
    double mEAp;
    double mEDp;

    double mQTp;
    double mQHp;
    double mQPp;
    double mQAp;
    double mQDp;
};

#endif // PREDICTION_H
