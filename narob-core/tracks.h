#ifndef TRACKS_H
#define TRACKS_H

#include "dbtablebase.h"
#include "dbrecordbase.h"
#include "modelbase.h"

#include "narob-core_global.h"

const Fields TRACK_FIELDS{
            Field("id", "id", 0),
            Field("name", "Name", -4),
            Field("elevation", "Elev", 0),
            Field("bearing", "Bear", 0),
            Field("radio", "Radio", 1)};


class Tracks : public DbTableBase
{
public:
    explicit Tracks();
};


class NAROBCORESHARED_EXPORT Track : public DbRecordBase
{
public:
    explicit Track();
};


class NAROBCORESHARED_EXPORT TracksModel : public ModelBase
{
    Q_OBJECT

public:
    explicit TracksModel(QObject *parent = nullptr);

    QString trackName(const int id);
};

#endif // TRACKS_H
