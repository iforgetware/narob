#include <QSqlQuery>
#include <QDebug>

#include "races.h"

Races::Races() :
    DbTableBase("races",
                RACE_FIELDS)
{
}


Race::Race() :
    DbRecordBase("races",
                 RACE_FIELDS)
{
    init();
}

RacesModel::RacesModel(QObject *parent) :
    ModelBase("races",
              RACE_FIELDS,
              parent)
{
    setJoinMode(QSqlRelationalTableModel::LeftJoin);

    setRelation(3, QSqlRelation("tracks", "id", "name, trackId as trackId"));

    setSort(fieldIndex("date"), Qt::DescendingOrder);

    select();
}

Race* RacesModel::getRace(const int row)
{
    Race *race = new Race();
    race->populate(record(row));

    return race;
}

Race *RacesModel::raceForId(const int id)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM races "
                  "WHERE id = :id");
    query.bindValue(":id", id);

    query.exec();

    Race *race = new Race();

    if(query.next()){
        race->populate(query.record());
    }

    query.clear();

    return race;
}
