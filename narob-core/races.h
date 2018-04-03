#ifndef RACES_H
#define RACES_H

#include "dbtablebase.h"
#include "dbrecordbase.h"
#include "modelbase.h"

#include "narob-core_global.h"

class Races : public DbTableBase
{
public:
    explicit Races();
};


class NAROBCORESHARED_EXPORT Race : public DbRecordBase
{
public:
    explicit Race();
};


class NAROBCORESHARED_EXPORT RacesModel : public ModelBase
{
    Q_OBJECT

public:
    explicit RacesModel(QObject *parent = 0);

    Race *getRace(const int row);
    Race * raceForId(const int id);
};

#endif // RACES_H
