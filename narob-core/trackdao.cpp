#include "trackdao.h"

#include <QSqlQuery>
#include <QVariant>

#include <QDebug>

#include "databasemanager.h"

TrackDao::TrackDao(QSqlDatabase &database) :
    mDatabase(database)
{
}

void TrackDao::init() const
{
    // look into using varchar(length) for text fields

    if(!mDatabase.tables().contains("tracks")){
        QSqlQuery query(mDatabase);
        query.exec("CREATE TABLE tracks ("
                   "id INTEGER PRIMARY KEY,"
                   "name TEXT,"
                   "elevation INTEGER,"
                   "bearing INTEGER,"
                   "radio REAL)");
        DatabaseManager::debugQuery(query);
    }
}

void TrackDao::addTrack(Track &track) const
{
    QSqlQuery query(mDatabase);

    query.prepare("INSERT INTO tracks ("
                  "name,"
                  "elevation,"
                  "bearing,"
                  "radio"
                  ") VALUES ("
                  ":name, "
                  ":elevation, "
                  ":bearing, "
                  ":radio"
                  ")");

    query.bindValue(":name", track.name());
    query.bindValue(":elevation", track.elevation());
    query.bindValue(":bearing", track.bearing());
    query.bindValue(":radio", track.radio());

    query.exec();

    DatabaseManager::debugQuery(query);

    track.setId(query.lastInsertId().toInt());
}

//void TrackDao::updateTrack(const Track *track) const
//{
//    QSqlQuery query(mDatabase);

//    qDebug("in update track");
//    qDebug() << track->name();

//    query.prepare("UPDATE tracks SET "
//                  "name=:name,"
//                  "elevation=:elevation,"
//                  "bearing=:bearing,"
//                  "radio=:radio "
//                  "WHERE id=:id");

//    query.bindValue(":name", track->name());
//    query.bindValue(":elevation", track->elevation());
//    query.bindValue(":bearing", track->bearing());
//    query.bindValue(":radio", track->radio());
//    query.bindValue(":id", track->id());

//    query.exec();

//    DatabaseManager::debugQuery(query);
//}

void TrackDao::removeTrack(int id) const
{
    QSqlQuery query(mDatabase);

    query.prepare("DELETE from tracks WHERE id=:id");

    query.bindValue(":id", id);

    query.exec();

    DatabaseManager::debugQuery(query);
}

QVector<Track*> TrackDao::tracks() const
{
    QSqlQuery query("SELECT * FROM tracks", mDatabase);

    query.exec();

    QVector<Track*> list;

    while(query.next()) {
        Track* track = new Track();
        track->setId(query.value("id").toInt());
        track->setName(query.value("name").toString());
        track->setElevation(query.value("elevation").toInt());
        track->setBearing(query.value("bearing").toInt());
        track->setRadio(query.value("radio").toDouble());

        list.append(track);
    }

    return list;
}
