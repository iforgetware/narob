#ifndef PREDICTIONS_H
#define PREDICTIONS_H

#include <QSqlRecord>

#include "dbtablebase.h"
#include "dbrecordbase.h"
#include "modelbase.h"
#include "vehicle.h"
#include "race.h"

#include "narob-core_global.h"

class Predictions : public DbTableBase
{
public:
    explicit Predictions();
};


class Prediction : public DbRecordBase
{
public:
    explicit Prediction();
};


class PredictionsModel : public ModelBase
{
    Q_OBJECT

public:
    explicit PredictionsModel(Vehicle *vehicle,
                              Race *race,
                              QObject *parent = 0);
    void updatePrediction(Prediction *prediction);

//    Prediction *getPrediction(const int row);

private:
    Vehicle *mVehicle;
    Race *mRace;
};

#endif // PREDICTIONS_H
