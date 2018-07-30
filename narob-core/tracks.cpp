#include <QSqlQuery>

#include "tracks.h"

Fields trackFields()
{
    Fields f;

    f.append(Field("id", "id", 0, 0));
    f.append(Field("name", "Name", 150, -4));
    f.append(Field("elevation", "Elev", 50, 0));
    f.append(Field("bearing", "Bear", 50, 0));
    f.append(Field("radio", "Radio", 50, 1));

    return f;
}

Tracks::Tracks() :
    DbTableBase()
{
    mFields = trackFields();
    mTable = "tracks";
}


Track::Track() :
    DbRecordBase()
{
    mFields = trackFields();
    init("tracks");
}

TracksModel::TracksModel(QObject *parent) :
    ModelBase("tracks",
              trackFields(),
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
