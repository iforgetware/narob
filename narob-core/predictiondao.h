#ifndef PREDICTIONDAO_H
#define PREDICTIONDAO_H

#include <QSqlDatabase>
#include <QVector>

#include "prediction.h"

class PredictionDao
{
public:
    PredictionDao(QSqlDatabase &database);

    void init() const;

    void addPrediction(Prediction &prediction) const;
    void removePrediction(int id) const;
    QVector<Prediction*> predictionsForVehicleAndRace(int raceId,
                                                      int vehicleId) const;

private:
    QSqlDatabase &mDatabase;
};

#endif // PREDICTIONDAO_H
