#ifndef RACES_H
#define RACES_H

#include <QSqlRecord>

#include "dbtablebase.h"
#include "dbrecordbase.h"
#include "modelbase.h"

#include "narob-core_global.h"

class Races : public DbTableBase
{
public:
    explicit Races();
};


class Race : public DbRecordBase
{
public:
    explicit Race();
};


class RacesModel : public ModelBase
{
    Q_OBJECT

public:
    explicit RacesModel(QObject *parent = 0);

    Race *getRace(const int row);
    Race* firstRace();
};

#endif // RACES_H
