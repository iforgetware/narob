#include <QSqlQuery>

#include "observations.h"

Fields setObservationFields()
{
    Fields retFields;

    retFields.append(Field("id", "id", 0, 0));
    retFields.append(Field("dateTime", "Date       Time", 160, -3));
    retFields.append(Field("temperature", "Temp", 50, 1));
    retFields.append(Field("humidity", "Humid",50, 1));
    retFields.append(Field("pressure", "Pres", 50, 2));
    retFields.append(Field("vaporPressure", "V Pres", 50, 2));
    retFields.append(Field("dewPoint", "D Point", 60, 1));
    retFields.append(Field("densityAltitude", "D Alt", 60, 0));
    retFields.append(Field("windSpeed", "W Speed", 70, 0));
    retFields.append(Field("windGust", "W Gust", 70, 0));
    retFields.append(Field("windDirection", "W Dir", 60, 0));

    return retFields;
}

Fields observationFields = setObservationFields();

Observations::Observations() :
    DbTableBase()
{
    mFields = observationFields;
    mTable = "observations";
}


Observation::Observation() :
    DbRecordBase()
{
    mFields = observationFields;
    init("observations");
}

ObservationsModel::ObservationsModel(QObject *parent) :
    ModelBase(parent)
{
    setTable("observations");

    mFields = observationFields;

    setHeaders();

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
    QSqlRecord rec = record(row);
    Observation *observation = new Observation();

    foreach (Field field, mFields) {
        observation->setValue(field.mColumn, rec.value(field.mColumn));
    }

    return observation;
}

Observation* ObservationsModel::lastObservation()
{
    return getObservation(1);
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

        foreach (Field field, mFields) {
            observation->setValue(field.mColumn, query.value(field.mColumn));
        }
    }

    return observation;
}
