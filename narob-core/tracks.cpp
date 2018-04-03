#include <QSqlQuery>

#include "tracks.h"

Fields setTrackFields()
{
    Fields retFields;

    retFields.append(Field("id", "id", 0, 0));
    retFields.append(Field("name", "Name", 150, -4));
    retFields.append(Field("elevation", "Elev", 50, 0));
    retFields.append(Field("bearing", "Bear", 50, 0));
    retFields.append(Field("radio", "Radio", 50, 1));

    return retFields;
}

Fields trackFields = setTrackFields();

Tracks::Tracks() :
    DbTableBase()
{
    mFields = trackFields;
    mTable = "tracks";
}


Track::Track() :
    DbRecordBase()
{
    mFields = trackFields;
    init("tracks");
}

TracksModel::TracksModel(QObject *parent) :
    ModelBase(parent)
{
    setTable("tracks");

    mFields = trackFields;

    setHeaders();

    select();
}

Track* TracksModel::getTrack(const int row)
{
    QSqlRecord rec = record(row);
    Track *track = new Track();
    foreach (Field field, mFields) {
        track->setValue(field.mColumn, rec.value(field.mColumn));
    }
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

        foreach (Field field, mFields) {
            track->setValue(field.mColumn, query.value(field.mColumn));
        }
    }

    return track;

}
