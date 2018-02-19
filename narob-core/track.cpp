#include "track.h"

Track::Track() :
    mId(-1),

    mName(""),
    mElevation(0),
    mBearing(0),
    mRadio(0)
{
}

Track::Track(const Track &track) :
    mId(track.id()),

    mName(track.name()),
    mElevation(track.elevation()),
    mBearing(track.bearing()),
    mRadio(track.radio())
{
}
