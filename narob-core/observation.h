#ifndef OBSERVATION_H
#define OBSERVATION_H

#include <QDateTime>

#include "narob-core_global.h"

class NAROBCORESHARED_EXPORT Observation
{
public:
    explicit Observation();
    explicit Observation(const Observation &observation);

    int id() const { return mId; }
    void setId(const int &id) { mId = id; }


    QDateTime dateTime() const { return mDateTime; }
    void setDateTime(const QDateTime &dateTime) { mDateTime = dateTime; }


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

private:
    int mId;

    QDateTime mDateTime;

    double mTemperature;
    double mHumidity;
    double mPressure;
    double mVaporPressure;
    double mDewPoint;
    int mDensityAltitude;
    int mWindSpeed;
    int mWindGust;
    int mWindDirection;
};

#endif // OBSERVATION_H
