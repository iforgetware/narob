#ifndef TRACKS_H
#define TRACKS_H

#include "dbtablebase.h"
#include "dbrecordbase.h"
#include "modelbase.h"

#include "narob-core_global.h"

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
    explicit TracksModel(QObject *parent = 0);

    Track *getTrack(const int row);
    Track *trackForId(const int id);
};

#endif // TRACKS_H
