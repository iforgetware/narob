#include <QSqlQuery>

#include "observations.h"

Fields observationFields()
{
    Fields f;

    f.append(Field("id", "id", 0, 0));
    f.append(Field("dateTime", "Date       Time", 160, -3));
    f.append(Field("temperature", "Temp", 50, 1));
    f.append(Field("humidity", "Humid",50, 1));
    f.append(Field("pressure", "Pres", 50, 2));
    f.append(Field("vaporPressure", "V Pres", 50, 2));
    f.append(Field("dewPoint", "D Point", 60, 1));
    f.append(Field("densityAltitude", "D Alt", 60, 0));
    f.append(Field("windSpeed", "W Speed", 70, 0));
    f.append(Field("windGust", "W Gust", 70, 0));
    f.append(Field("windDirection", "W Dir", 60, 0));

    return f;
}

Observations::Observations() :
    DbTableBase()
{
    mFields = observationFields();
    mTable = "observations";
}


Observation::Observation() :
    DbRecordBase()
{
    mFields = observationFields();
    init("observations");
}

ObservationsModel::ObservationsModel(QObject *parent) :
    ModelBase("observations",
              observationFields(),
              parent)
{
    setSort(fieldIndex("dateTime"), Qt::DescendingOrder);

    select();
}

void ObservationsModel::addObservation(Observation &observation)
{
    insertRecord(-1, observation);
    submitAll();
    select();
}

Observation* ObservationsModel::getObservation(const int row)
{
    Observation *observation = new Observation();
    observation->populate(record(row));

    return observation;
}

Observation* ObservationsModel::lastObservation()
{
    return getObservation(0);
}

Observation* ObservationsModel::observationForTime(QDateTime dateTime)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM observations "
                  "WHERE dateTime = :dateTime");
    query.bindValue(":dateTime", dateTime);

    query.exec();

    Observation *observation = new Observation();

    if(query.next()){
        observation->populate(query.record());
    }

    query.clear();

    return observation;
}
