#include "observation.h"

Observation::Observation() :
    mId(-1),

    mDateTime(QDateTime()),

    mTemperature(0),
    mHumidity(0),
    mPressure(0),
    mVaporPressure(0),
    mDewPoint(0),
    mDensityAltitude(0),
    mWindSpeed(0),
    mWindGust(0),
    mWindDirection(0)
{
}

Observation::Observation(const Observation &observation) :
    mId(observation.id()),

    mDateTime(observation.dateTime()),

    mTemperature(observation.temperature()),
    mHumidity(observation.humidity()),
    mPressure(observation.pressure()),
    mVaporPressure(observation.vaporPressure()),
    mDewPoint(observation.dewPoint()),
    mDensityAltitude(observation.densityAltitude()),
    mWindSpeed(observation.windSpeed()),
    mWindGust(observation.windGust()),
    mWindDirection(observation.windDirection())
{
}
