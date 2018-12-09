#include <QSqlQuery>

#include "tracks.h"

Tracks::Tracks() :
    DbTableBase("tracks",
                TRACK_FIELDS)
{
}


Track::Track() :
    DbRecordBase("tracks",
                 TRACK_FIELDS)
{
    init();
}

TracksModel::TracksModel(QObject *parent) :
    ModelBase("tracks",
              TRACK_FIELDS,
              parent)
{
}

Track* TracksModel::getTrack(const int row)
{
    Track *track = new Track();
    track->populate(record(row));

    return track;
}

Track *TracksModel::trackForId(const int id)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM tracks "
                  "WHERE id = :id");
    query.bindValue(":id", id);

    query.exec();

    Track *track = new Track();

    if(query.next()){
        track->populate(query.record());
    }

    query.clear();

    return track;
}
