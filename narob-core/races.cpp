#include <QSqlQuery>
#include <QDebug>

#include <memory>

#include "races.h"

using namespace std;

Races::Races() :
    DbTableBase("races",
                RACE_FIELDS)
{
}


Race::Race() :
    DbRecordBase("races",
                 RACE_FIELDS)
{
}

RacesModel::RacesModel(QObject *parent) :
    ModelBase("races",
              RACE_FIELDS,
              parent)
{
    setJoinMode(QSqlRelationalTableModel::LeftJoin);

    setRelation(fieldIndex("trackId"),
                QSqlRelation("tracks", "id", "name, trackId as trackId"));

    setSort(fieldIndex("date"), Qt::DescendingOrder);

    select();
}

std::shared_ptr<Race> RacesModel::raceForRow(const int row) const
{
    auto race = make_shared<Race>();

    race->populate(record(row));

    return race;
}

std::unique_ptr<Race> RacesModel::raceForId(const int id) const
{
    QSqlQuery query;
    query.prepare("SELECT * FROM races "
                  "WHERE id = :id");
    query.bindValue(":id", id);

    query.exec();

    auto race = make_unique<Race>();

    if(query.next()){
        race->populate(query.record());
    }

    query.clear();

    return race;
}
