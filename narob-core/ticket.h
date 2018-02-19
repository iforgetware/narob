#ifndef TICKET_H
#define TICKET_H

#include <QDate>
#include <QTime>

#include "narob-core_global.h"

class NAROBCORESHARED_EXPORT Ticket
{
public:
    explicit Ticket();
    explicit Ticket(const Ticket &ticket);

    int id() const { return mId; }
    void setId(const int &id) { mId = id; }


    int vehicleId() const { return mVehicleId; }
    void setVehicleId(const int &vehicleId) { mVehicleId = vehicleId; }

    int trackId() const { return mTrackId; }
    void setTrackId(const int &trackId) {mTrackId = trackId; }

    int raceId() const { return mRaceId; }
    void setRaceId(const int &raceId) { mRaceId = raceId;}

    int predictionId() const { return mPredictionId; }
    void setPredictionId(const int &predictionId) { mPredictionId = predictionId; }


    QDate date() const { return mDate; }
    void setDate(const QDate &Date) { mDate = Date; }

    QTime time() const { return mTime; }
    void setTime(const QTime &Time) { mTime = Time; }


    int vehicleWeight() const { return mVehicleWeight; }
    void setVehicleWeight(const int &vehicleWeight) { mVehicleWeight = vehicleWeight; }

    double riderWeight()const { return mRiderWeight; }
    void setRiderWeight(const double &riderWeight) { mRiderWeight = riderWeight; }


    QString lane() const { return mLane; }
    void setLane(const QString &lane) { mLane = lane; }

    double delay() const { return mDelay; }
    void setDelay(const double &delay) { mDelay = delay; }

    double reaction() const { return mReaction; }
    void setReaction(const double &reaction) { mReaction = reaction; }

    double sixty() const { return mSixty; }
    void setSixty(const double &sixty) { mSixty = sixty; }

    double threeThirty() const { return mThreeThirty; }
    void setThreeThirty(const double &threeThirty) { mThreeThirty = threeThirty; }

    double eighth() const { return mEighth; }
    void setEighth(const double &eighth) { mEighth = eighth; }

    double eighthMPH() const { return mEighthMPH; }
    void setEighthMPH(const double &eighthMPH) { mEighthMPH = eighthMPH; }

    bool eighthGood() const { return mEighthGood; }
    void setEighthGood(const bool &eighthGood) { mEighthGood = eighthGood; }

    double thousand() const { return mThousand; }
    void setThousand(const double &thousand) { mThousand = thousand; }

    double dial() const { return mDial; }
    void setDial(const double &dial) { mDial = dial; }

    double quarter() const { return mQuarter; }
    void setQuarter(const double &quarter) { mQuarter = quarter; }

    double quarterMPH() const { return mQuarterMPH; }
    void setQuarterMPH(const double &quarterMPH) { mQuarterMPH = quarterMPH; }

    bool quarterGood() const { return mQuarterGood; }
    void setQuarterGood(const bool &quarterGood) { mQuarterGood = quarterGood; }


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

    int mVehicleId;
    int mTrackId;
    int mRaceId;
    int mPredictionId;

    QDate mDate;
    QTime mTime;

    QString mLane;
    double mDelay;
    double mReaction;
    double mSixty;
    double mThreeThirty;
    double mEighth;
    double mEighthMPH;
    bool mEighthGood;
    double mThousand;
    double mDial;
    double mQuarter;
    double mQuarterMPH;
    bool mQuarterGood;

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
};

#endif // TICKET_H
