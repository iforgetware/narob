#ifndef OBSERVATIONS_H
#define OBSERVATIONS_H

#include <QDateTime>

#include "dbtablebase.h"
#include "dbrecordbase.h"
#include "modelbase.h"

#include "narob-core_global.h"

class Observations : public DbTableBase
{
public:
    explicit Observations();
};


class NAROBCORESHARED_EXPORT Observation : public DbRecordBase
{
public:
    explicit Observation();
};


class NAROBCORESHARED_EXPORT ObservationsModel : public ModelBase
{
    Q_OBJECT

public:
    explicit ObservationsModel(QObject *parent = 0);

    void addObservation(Observation &observation);
    Observation *getObservation(const int row);
    Observation *lastObservation();
    Observation *observationForTime(QDateTime dateTime);
};


#endif // OBSERVATIONS_H
