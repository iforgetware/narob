#ifndef PREDICTIONSMODEL_H
#define PREDICTIONSMODEL_H

#include <QVector>

#include "narob-core_global.h"
#include "modelbase.h"
#include "prediction.h"
#include "vehicle.h"
#include "race.h"
#include "databasemanager.h"

class NAROBCORESHARED_EXPORT PredictionsModel : public ModelBase
{
    Q_OBJECT

public:
    PredictionsModel(Vehicle *vehicle,
                     Race *race = 0,
                     QObject *parent = 0);

    QModelIndex addPrediction(const Prediction &prediction);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    bool removeRows(int row, int count, const QModelIndex& parent) override;

private:
    DatabaseManager &mDb;
    Vehicle *mVehicle;
    Race *mRace;
    QVector<Prediction*> mPredictions;
};

#endif // PREDICTIONSMODEL_H
