#include "racedao.h"
//#include "tracksmodel.h"

#include <QSqlQuery>
#include <QVariant>

//#include <QDebug>

#include "databasemanager.h"

RaceDao::RaceDao(QSqlDatabase &database) :
    mDatabase(database)
{
}

void RaceDao::init() const
{
    if(!mDatabase.tables().contains("races")){
        QSqlQuery query(mDatabase);
        query.exec("CREATE TABLE races ("
                   "id INTEGER PRIMARY KEY,"
                   "date TEXT,"
                   "name TEXT,"
                   "trackId INTEGER)");
        DatabaseManager::debugQuery(query);
    }
}

//Race* RaceDao::getRace(int id) const
//{
//    QSqlQuery query(mDatabase);

//    query.prepare("SELECT * FROM races "
//                  "WHERE id = :id");

//    query.bindValue(":id", id);

//    query.exec();

//    DatabaseManager::debugQuery(query);

//    Race *race = new Race;

//    if(query.next()){
//        race->setId(query.value("id").toInt());
//        race->setDate(query.value("date").toDate());
//        race->setName(query.value("name").toString());
//        race->setTrackId(query.value("trackId").toInt());
//    }

//    return race;

//}

void RaceDao::addRace(Race &race) const
{
//    TracksModel tracksModel;
//    race.setTrackId(tracksModel.firstTrack()->id());

    QSqlQuery query(mDatabase);

    query.prepare("INSERT INTO races ("
                  "date,"
                  "name,"
                  "trackId"
                  ") VALUES ("
                  ":date,"
                  ":name,"
                  ":trackId"
                  ")");

    query.bindValue(":date", race.date());
    query.bindValue(":name", race.name());
    query.bindValue(":trackId", race.trackId());

    query.exec();

    DatabaseManager::debugQuery(query);

    race.setId(query.lastInsertId().toInt());
}

//void RaceDao::updateRace(const Race *race) const
//{
//    QSqlQuery query(mDatabase);

//    qDebug("in update race");
//    qDebug() << race->name();

//    query.prepare("UPDATE races SET "
//                  "date=:date,"
//                  "name=:name,"
//                  "trackId=:trackId "
//                  "WHERE id=:id");

//    query.bindValue(":date", race->date());
//    query.bindValue(":name", race->name());
//    query.bindValue(":trackId", race->trackId());
//    query.bindValue(":id", race->id());

//    query.exec();

//    DatabaseManager::debugQuery(query);
//}

void RaceDao::removeRace(int id) const
{
    QSqlQuery query(mDatabase);

    query.prepare("DELETE from races WHERE id=:id");

    query.bindValue(":id", id);

    query.exec();

    DatabaseManager::debugQuery(query);
}

QVector<Race*> RaceDao::races() const
{
    QSqlQuery query("SELECT * FROM races", mDatabase);

    query.exec();

    QVector<Race*> list;

    while(query.next()) {
        Race* race = new Race();
        race->setId(query.value("id").toInt());
        race->setDate(query.value("date").toDate());
        race->setName(query.value("name").toString());
        race->setTrackId(query.value("trackId").toInt());

        list.append(race);
    }

    return list;
}
