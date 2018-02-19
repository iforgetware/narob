#include "ticket.h"

Ticket::Ticket() :
    mId(-1),

    mVehicleId(1),
    mTrackId(1),
    mRaceId(1),
    mPredictionId(0),

    mDate(QDate()),
    mTime(QTime()),

    mLane(""),
    mDelay(0),
    mReaction(0),
    mSixty(0),
    mThreeThirty(0),
    mEighth(0),
    mEighthMPH(0),
    mEighthGood(true),
    mThousand(0),
    mDial(0),
    mQuarter(0),
    mQuarterMPH(0),
    mQuarterGood(true),

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
    mWindDirection(0)
{
}

Ticket::Ticket(const Ticket &ticket) :
    mId(ticket.id()),

    mVehicleId(ticket.vehicleId()),
    mTrackId(ticket.trackId()),
    mRaceId(ticket.raceId()),
    mPredictionId(ticket.predictionId()),

    mDate(ticket.date()),
    mTime(ticket.time()),

    mLane(ticket.lane()),
    mDelay(ticket.delay()),
    mReaction(ticket.reaction()),
    mSixty(ticket.sixty()),
    mThreeThirty(ticket.threeThirty()),
    mEighth(ticket.eighth()),
    mEighthMPH(ticket.eighthMPH()),
    mEighthGood(ticket.eighthGood()),
    mThousand(ticket.thousand()),
    mDial(ticket.dial()),
    mQuarter(ticket.quarter()),
    mQuarterMPH(ticket.quarterMPH()),
    mQuarterGood(ticket.quarterGood()),

    mVehicleWeight(ticket.vehicleWeight()),
    mRiderWeight(ticket.riderWeight()),

    mTemperature(ticket.temperature()),
    mHumidity(ticket.humidity()),
    mPressure(ticket.pressure()),
    mVaporPressure(ticket.vaporPressure()),
    mDewPoint(ticket.dewPoint()),
    mDensityAltitude(ticket.densityAltitude()),
    mWindSpeed(ticket.windSpeed()),
    mWindGust(ticket.windGust()),
    mWindDirection(ticket.windDirection())
{
}
