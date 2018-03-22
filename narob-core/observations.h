#ifndef OBSERVATIONS_H
#define OBSERVATIONS_H

#include <QSqlRecord>
#include <QSortFilterProxyModel>

#include "dbtablebase.h"
#include "dbrecordbase.h"
#include "modelbase.h"

#include "narob-core_global.h"

class Observations : public DbTableBase
{
public:
    explicit Observations();
};


class Observation : public DbRecordBase
{
public:
    explicit Observation();
};


class ObservationsModel : public ModelBase
{
    Q_OBJECT

public:
    explicit ObservationsModel(QObject *parent = 0);

    Observation *getObservation(const int row);
    Observation* lastObservation();
    Observation* observationForTime(QDateTime dateTime);
};


#endif // OBSERVATIONS_H
