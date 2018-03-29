#ifndef PREDICTIONS_H
#define PREDICTIONS_H

#include "dbtablebase.h"
#include "dbrecordbase.h"
#include "modelbase.h"

#include "vehicles.h"
#include "races.h"

#include "narob-core_global.h"

class Predictions : public DbTableBase
{
public:
    explicit Predictions();
};


class NAROBCORESHARED_EXPORT Prediction : public DbRecordBase
{
public:
    explicit Prediction();
};


class NAROBCORESHARED_EXPORT PredictionsModel : public ModelBase
{
    Q_OBJECT

public:
    explicit PredictionsModel(Vehicle *vehicle,
                              Race *race,
                              QObject *parent = 0);
    void addPrediction(Prediction &prediction);

private:
    Vehicle *mVehicle;
    Race *mRace;
};

#endif // PREDICTIONS_H
