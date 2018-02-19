#include "observationsmodel.h"

ObservationsModel::ObservationsModel(QObject *parent) :
    ModelBase(parent),
    mDb(DatabaseManager::instance()),
    mObservations(mDb.observationDao.observations())
{
    setTable("observations");

    mFields.append(Field("date", "Date", 100, 0));
    mFields.append(Field("time", "Time", 80, -2));
    mFields.append(Field("temperature", "Temp", 50, 1));
    mFields.append(Field("humidity", "Humid",50, 1));
    mFields.append(Field("pressure", "Pres", 50, 2));
    mFields.append(Field("vaporPressure", "V Pres", 50, 2));
    mFields.append(Field("dewPoint", "D Point", 60, 1));
    mFields.append(Field("densityAltitude", "D Alt", 60, 0));
    mFields.append(Field("windSpeed", "W Speed", 70, 0));
    mFields.append(Field("windGust", "W Gust", 70, 0));
    mFields.append(Field("windDirection", "W Dir", 60, 0));

    setHeaders();

    setSort(fieldIndex("date"), Qt::DescendingOrder);
    setSort(fieldIndex("time"), Qt::DescendingOrder);

    select();
}

QModelIndex ObservationsModel::addObservation(const Observation &observation)
{
    int rowIndex = rowCount();

    beginInsertRows(QModelIndex(), rowIndex, rowIndex);
    Observation* newObservation = new Observation(observation);
    mDb.observationDao.addObservation(*newObservation);
    mObservations.append(newObservation);
    endInsertRows();

    return index(rowIndex, 0);
}

Observation* ObservationsModel::lastObservation()
{
    Observation* observation = new Observation();
    observation = mDb.observationDao.latestObservation();

    return observation;
}

Observation* ObservationsModel::observationForTime(QDate date, QTime time)
{
    return mDb.observationDao.observationForTime(date, time);
}

int ObservationsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return mObservations.size();
}

bool ObservationsModel::removeRows(int row, int count, const QModelIndex &parent)
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
        const Observation& observation = *mObservations.at(row + countLeft);
        mDb.observationDao.removeObservation(observation.id());
    }
    mObservations.erase(mObservations.begin() + row,
                  mObservations.begin() + row + count);
    endRemoveRows();
    return true;
}
