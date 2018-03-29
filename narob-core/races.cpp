#include "races.h"

Fields setRaceFields()
{
    Fields retFields;

    retFields.append(Field("id", "id", 0, 0));
    retFields.append(Field("date", "Date", 100, -2));
    retFields.append(Field("name", "Name", 150, -4));
    retFields.append(Field("trackId", "Track", 150, 0));

    return retFields;
}

Fields raceFields = setRaceFields();

Races::Races() :
    DbTableBase()
{
    mFields = raceFields;
    mTable = "races";
}


Race::Race() :
    DbRecordBase()
{
    mFields = raceFields;
    init("races");
}

RacesModel::RacesModel(QObject *parent) :
    ModelBase(parent)
{
    setTable("races");

    setJoinMode(QSqlRelationalTableModel::LeftJoin);

    setRelation(3, QSqlRelation("tracks", "id", "name, trackId as trackId"));

    mFields = raceFields;

    setHeaders();

    select();
}

Race* RacesModel::getRace(const int row)
{
    QSqlRecord rec = record(row);
    Race *race = new Race();
    int i = 0;
    foreach (Field field, mFields) {
        race->setValue(field.mColumn, rec.value(field.mColumn));
        i++;
    }
    return race;
}
