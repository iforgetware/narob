#ifndef TRACK_H
#define TRACK_H

#include <QString>

#include "narob-core_global.h"

class NAROBCORESHARED_EXPORT Track
{
public:
    explicit Track();
    explicit Track(const Track &track);

    int id() const { return mId; }
    void setId(const int &id) { mId = id; }

    QString name() const { return mName; }
    void setName(const QString &name) { mName = name; }

    int elevation() const { return mElevation; }
    void setElevation(const int &elevation) { mElevation = elevation; }

    int bearing() const { return mBearing; }
    void setBearing(const int &bearing) { mBearing = bearing; }

    double radio() const { return mRadio; }
    void setRadio(const double &radio) { mRadio = radio; }

private:
    int mId;

    QString mName;
    int mElevation;
    int mBearing;
    double mRadio;
};

#endif // TRACK_H
