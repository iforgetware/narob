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
}

TracksModel::TracksModel(QObject *parent) :
    ModelBase("tracks",
              TRACK_FIELDS,
              parent)
{
}

QString TracksModel::trackName(const int id)
{
    QString name = "";
    QSqlQuery query;
    query.prepare("SELECT * FROM tracks "
                  "WHERE id = :id");
    query.bindValue(":id", id);

    query.exec();

    Track track;

    if(query.next()){
        name = query.record().value("name").toString();
    }

    query.clear();

    return name;
}
