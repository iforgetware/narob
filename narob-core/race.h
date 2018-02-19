#ifndef RACE_H
#define RACE_H

#include <QDate>
#include <QString>

#include "narob-core_global.h"

class NAROBCORESHARED_EXPORT Race
{
public:
    explicit Race();
    explicit Race(const Race &race);

    int id() const { return mId; }
    void setId(const int &id) { mId = id; }

    QDate date() const { return mDate; }
    void setDate(const QDate &date) { mDate = date; }

    QString name() const { return mName; }
    void setName(const QString &name) { mName = name; }

    int trackId() const { return mTrackId; }
    void setTrackId(const int &trackId) { mTrackId = trackId; }

private:
    int mId;

    QDate mDate;
    QString mName;
    int mTrackId;
};

#endif // RACE_H
