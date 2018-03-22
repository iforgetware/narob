#ifndef TRACKS_H
#define TRACKS_H

#include <QSqlRecord>

#include "dbtablebase.h"
#include "dbrecordbase.h"
#include "modelbase.h"

#include "narob-core_global.h"

class Tracks : public DbTableBase
{
public:
    explicit Tracks();
};


class Track : public DbRecordBase
{
public:
    explicit Track();
};


class TracksModel : public ModelBase
{
    Q_OBJECT

public:
    explicit TracksModel(QObject *parent = 0);

    Track *getTrack(const int row);
    Track* firstTrack();
};

#endif // TRACKS_H
