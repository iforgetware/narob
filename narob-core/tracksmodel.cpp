#include "tracksmodel.h"

using namespace std;

TracksModel::TracksModel(QObject *parent) :
    ModelBase(parent),
    mDb(DatabaseManager::instance()),
    mTracks(mDb.trackDao.tracks())
{
    setTable("tracks");

    mFields.append(Field("name", "Name", 150, 0));
    mFields.append(Field("evelavtion", "Elev", 50, 0));
    mFields.append(Field("bearing", "Bear", 50, 0));
    mFields.append(Field("radio", "Radio", 50, 1));

    setHeaders();

    select();
}

Track* TracksModel::getTrack(const int id)
{
    return mTracks.at(id);
}

Track* TracksModel::firstTrack()
{
    return mTracks.at(1);
}

QModelIndex TracksModel::addTrack(const Track &track)
{
    int rowIndex = rowCount();

    beginInsertRows(QModelIndex(), rowIndex, rowIndex);
    Track* newTrack = new Track(track);
    mDb.trackDao.addTrack(*newTrack);
    mTracks.append(newTrack);
    endInsertRows();

    return index(rowIndex, 0);
}

//void TracksModel::updateTrack(const Track *track)
//{
//    mDb.trackDao.updateTrack(track);
//}

int TracksModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return mTracks.size();
}

bool TracksModel::removeRows(int row, int count, const QModelIndex &parent)
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
        const Track& track = *mTracks.at(row + countLeft);
        mDb.trackDao.removeTrack(track.id());
    }
    mTracks.erase(mTracks.begin() + row,
                  mTracks.begin() + row + count);
    endRemoveRows();
    return true;
}
