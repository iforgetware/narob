#include "race.h"

Race::Race() :
    mId(-1),

    mDate(QDate()),
    mName(""),
    mTrackId(-1)
{
}

Race::Race(const Race &race) :
    mId(race.id()),

    mDate(race.date()),
    mName(race.name()),
    mTrackId(race.trackId())
{
}
