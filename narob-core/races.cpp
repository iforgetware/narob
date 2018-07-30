#include <QSqlQuery>

#include "races.h"

Fields raceFields()
{
    Fields f;

    f.append(Field("id", "id", 0, 0));
    f.append(Field("date", "Date", 100, -2));
    f.append(Field("name", "Name", 150, -4));
    f.append(Field("trackId", "Track", 150, 0));

    return f;
}

Races::Races() :
    DbTableBase()
{
    mFields = raceFields();
    mTable = "races";
}


Race::Race() :
    DbRecordBase()
{
    mFields = raceFields();
    init("races");
}

RacesModel::RacesModel(QObject *parent) :
    ModelBase("races",
              raceFields(),
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
