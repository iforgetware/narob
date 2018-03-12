#ifndef OBSERVATIONSMODEL_H
#define OBSERVATIONSMODEL_H

#include <QVector>
#include "narob-core_global.h"
#include "modelbase.h"
#include "observation.h"
#include "databasemanager.h"

class NAROBCORESHARED_EXPORT ObservationsModel : public ModelBase
{
    Q_OBJECT

public:
    ObservationsModel(QObject *parent = 0);

    QModelIndex addObservation(const Observation &observation);
    Observation* lastObservation();
    Observation* observationForTime(QDateTime dateTime);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    bool removeRows(int row, int count, const QModelIndex& parent) override;

private:
    DatabaseManager &mDb;
    QVector<Observation*> mObservations;
};

#endif // OBSERVATIONSMODEL_H
