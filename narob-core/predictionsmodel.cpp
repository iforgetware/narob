#include "predictionsmodel.h"

#include <QDebug>

PredictionsModel::PredictionsModel(Vehicle *vehicle, Race *race, QObject *parent) :
    ModelBase(parent),
    mDb(DatabaseManager::instance()),
    mVehicle(vehicle),
    mRace(race),
    mPredictions(mDb.predictionDao.predictionsForVehicleAndRace(mVehicle->id(),
                                                                mRace->id()))
{
    setTable("predictions");

    QString filter = QString("vehicleId = %1 AND raceId = %2")
                     .arg(mVehicle->id())
                     .arg(mRace->id());

    setFilter(filter);

    mFields.append(Field("date", "Date", 100, 0));
    mFields.append(Field("time", "Time", 80, -2));
    mFields.append(Field("vehicleWeight", "V Weight", 70, 0));
    mFields.append(Field("riderWeight", "R Weight", 70, 1));
    mFields.append(Field("temperature", "Temp", 50, 1));
    mFields.append(Field("humidity", "Humid",50, 1));
    mFields.append(Field("pressure", "Pres", 50, 2));
    mFields.append(Field("vaporPressure", "V Pres", 50, 2));
    mFields.append(Field("dewPoint", "D Point", 60, 1));
    mFields.append(Field("densityAltitude", "D Alt", 50, 0));
    mFields.append(Field("windSpeed", "W Speed", 70, 0));
    mFields.append(Field("windGust", "W Gust", 70, 0));
    mFields.append(Field("windDirection", "W Dir", 60, 0));
    mFields.append(Field("eTp", "1/8T", 50, 3));
    mFields.append(Field("eHp", "1/8H", 50, 3));
    mFields.append(Field("ePp", "1/8P", 50, 3));
    mFields.append(Field("eAp", "1/8A", 50, 3));
    mFields.append(Field("eDp", "1/8D", 50, 3));
    mFields.append(Field("qTp", "1/4T", 50, 3));
    mFields.append(Field("qHp", "1/4H", 50, 3));
    mFields.append(Field("qPp", "1/4P", 50, 3));
    mFields.append(Field("qAp", "1/4A", 50, 3));
    mFields.append(Field("qDp", "1/4D", 50, 3));

    setHeaders();

    setSort(fieldIndex("date"), Qt::DescendingOrder);
    setSort(fieldIndex("time"), Qt::DescendingOrder);

    select();
}

QModelIndex PredictionsModel::addPrediction(Prediction* prediction)
{
    int rowIndex = rowCount();

    beginInsertRows(QModelIndex(), rowIndex, rowIndex);
    mDb.predictionDao.addPrediction(prediction);
    mPredictions.append(prediction);
    endInsertRows();

    return index(rowIndex, 0);
}

void PredictionsModel::updatePrediction(Prediction *prediction)
{
    mDb.predictionDao.updatePrediction(prediction);
}

int PredictionsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return mPredictions.size();
}

bool PredictionsModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (row < 0
            || row >= rowCount()
            || count < 0
            || (row + count) > rowCount()) {
        return false;
    }
    beginRemoveRows(parent, row, row + count - 1);
    int countLeft = count;
    while (countLeft--) {
        const Prediction& prediction = *mPredictions.at(row + countLeft);
        mDb.predictionDao.removePrediction(prediction.id());
    }
    mPredictions.erase(mPredictions.begin() + row,
                  mPredictions.begin() + row + count);
    endRemoveRows();
    return true;
}
