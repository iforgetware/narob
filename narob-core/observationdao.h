#ifndef OBSERVATIONDAO_H
#define OBSERVATIONDAO_H

#include <QVector>
#include <QSqlDatabase>

#include "observation.h"

class ObservationDao
{
public:
    ObservationDao(QSqlDatabase &database);
    void init() const;


    void addObservation(Observation &observation) const;
    void removeObservation(int id) const;
    Observation* observationForTime(QDate date, QTime time) const;
    Observation* latestObservation() const;
    QVector<Observation*> observations() const;

private:
    void populateObservation(Observation* observation,
                             QSqlQuery query) const;
    QSqlDatabase &mDatabase;
};

#endif // OBSERVATIONDAO_H
