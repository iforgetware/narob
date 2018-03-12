#include "prediction.h"

Prediction::Prediction() :
    mId(-1),

    mRaceId(-1),
    mVehicleId(-1),

    mDateTime(QDateTime()),

    mVehicleWeight(0),
    mRiderWeight(0),

    mTemperature(0),
    mHumidity(0),
    mPressure(0),
    mVaporPressure(0),
    mDewPoint(0),
    mDensityAltitude(0),
    mWindSpeed(0),
    mWindGust(0),
    mWindDirection(0),

    mWindFactor(0),
    mWeightFactor(0),

    mETp(0),
    mEHp(0),
    mEPp(0),
    mEAp(0),
    mEDp(0),
    mWindCorrectionEighth(0),

    mQTp(0),
    mQHp(0),
    mQPp(0),
    mQAp(0),
    mQDp(0),
    mWindCorrectionQuarter(0)
{
}

Prediction::Prediction(const Prediction &prediction) :
    mId(prediction.id()),

    mRaceId(prediction.raceId()),
    mVehicleId(prediction.vehicleId()),

    mDateTime(prediction.dateTime()),

    mVehicleWeight(prediction.vehicleWeight()),
    mRiderWeight(prediction.riderWeight()),

    mTemperature(prediction.temperature()),
    mHumidity(prediction.humidity()),
    mPressure(prediction.pressure()),
    mVaporPressure(prediction.vaporPressure()),
    mDewPoint(prediction.dewPoint()),
    mDensityAltitude(prediction.densityAltitude()),
    mWindSpeed(prediction.windSpeed()),
    mWindGust(prediction.windGust()),
    mWindDirection(prediction.windDirection()),

    mWindFactor(prediction.windFactor()),
    mWeightFactor(prediction.weightFactor()),

    mETp(prediction.eTp()),
    mEHp(prediction.eHp()),
    mEPp(prediction.ePp()),
    mEAp(prediction.eAp()),
    mEDp(prediction.eDp()),
    mWindCorrectionEighth(prediction.windCorrectionEighth()),

    mQTp(prediction.qTp()),
    mQHp(prediction.qHp()),
    mQPp(prediction.qPp()),
    mQAp(prediction.qAp()),
    mQDp(prediction.qDp()),
    mWindCorrectionQuarter(prediction.windCorrectionQuarter())
{
}
