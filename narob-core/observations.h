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






// add purge weather button?
// or just autodelete if older than {setting}

// create observations history table
// save the 11 around a ticket to this
// never purge this table
// only delete when ticket is deleted

// move prediction math into predictions.cpp, make public methods
// display 11 predictions in dialog of ticket detail
// may need seperate tab







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
