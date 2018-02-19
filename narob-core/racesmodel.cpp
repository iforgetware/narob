#include "racesmodel.h"

#include <QDebug>

using namespace std;

RacesModel::RacesModel(QObject *parent) :
    ModelBase(parent),
    mDb(DatabaseManager::instance()),
    mRaces(mDb.raceDao.races())
{
    setTable("races");

    setRelation(3, QSqlRelation("tracks", "id", "name"));

    mFields.append(Field("date", "Date", 100, 0));
    mFields.append(Field("name", "Name", 150, 0));
    mFields.append(Field("trackId", "Track", 150, 0));

    setHeaders();

    select();
}

Race *RacesModel::getRace(const int id)
{
    return mRaces.at(id);
}

QModelIndex RacesModel::addRace(const Race &race)
{
    int rowIndex = rowCount();

    beginInsertRows(QModelIndex(), rowIndex, rowIndex);
    Race* newRace = new Race(race);
    mDb.raceDao.addRace(*newRace);
    mRaces.append(newRace);
    endInsertRows();

    return index(rowIndex, 0);
}

//void RacesModel::updateRace(const Race *race)
//{
//    mDb.raceDao.updateRace(race);
//}

int RacesModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return mRaces.size();
}

bool RacesModel::removeRows(int row, int count, const QModelIndex &parent)
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
        const Race& race = *mRaces.at(row + countLeft);
        mDb.raceDao.removeRace(race.id());
    }
    mRaces.erase(mRaces.begin() + row,
                  mRaces.begin() + row + count);
    endRemoveRows();
    return true;
}
