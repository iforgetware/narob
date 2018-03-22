#include <QSqlQuery>
#include <QSqlField>

#include "predictions.h"
#include "databasemanager.h"

Fields setPredictionFields()
{
    Fields retFields;

    retFields.append(Field("id", "id", 0, 0));
    retFields.append(Field("dateTime", "Date       Time", 160, -3));

    retFields.append(Field("vehicleWeight", "V Weight", 70, 0));
    retFields.append(Field("riderWeight", "R Weight", 70, 1));

    retFields.append(Field("temperature", "Temp", 50, 1));
    retFields.append(Field("humidity", "Humid",50, 1));
    retFields.append(Field("pressure", "Pres", 50, 2));
    retFields.append(Field("vaporPressure", "V Pres", 50, 2));
    retFields.append(Field("dewPoint", "D Point", 60, 1));
    retFields.append(Field("densityAltitude", "D Alt", 50, 0));
    retFields.append(Field("windSpeed", "W Speed", 70, 0));
    retFields.append(Field("windGust", "W Gust", 70, 0));
    retFields.append(Field("windDirection", "W Dir", 60, 0));

    retFields.append(Field("windFactor", "Wd F", 50, 0));
    retFields.append(Field("weightFactor", "Wt F", 50, 0));

    retFields.append(Field("eTp", "1/8T", 50, 3));
    retFields.append(Field("eHp", "1/8H", 50, 3));
    retFields.append(Field("ePp", "1/8P", 50, 3));
    retFields.append(Field("eAp", "1/8A", 50, 3));
    retFields.append(Field("eDp", "1/8D", 50, 3));
    retFields.append(Field("windCorrectionEighth", "Wn CE", 50, 3));

    retFields.append(Field("qTp", "1/4T", 50, 3));
    retFields.append(Field("qHp", "1/4H", 50, 3));
    retFields.append(Field("qPp", "1/4P", 50, 3));
    retFields.append(Field("qAp", "1/4A", 50, 3));
    retFields.append(Field("qDp", "1/4D", 50, 3));
    retFields.append(Field("windCorrectionQuarter", "Wn CQ", 50, 3));

    return retFields;
}

Fields predictionFields = setPredictionFields();

Predictions::Predictions() :
    DbTableBase()
{
    mFields = predictionFields;
    mTable = "predictions";
}


Prediction::Prediction() :
    DbRecordBase()
{
    mFields = predictionFields;
    init("predictions");
}

PredictionsModel::PredictionsModel(Vehicle *vehicle,
                                   Race *race,
                                   QObject *parent) :
    ModelBase(parent),
    mVehicle(vehicle),
    mRace(race)
{
    setTable("predictions");

    QString filter = QString("vehicleId = %1 AND raceId = %2")
                     .arg(mVehicle->id())
                     .arg(mRace->id());

    setFilter(filter);

    mFields = predictionFields;

    setHeaders();

    setSort(fieldIndex("dateTime"), Qt::DescendingOrder);

    select();
}

//Prediction* PredictionsModel::getPrediction(const int row)
//{
//    QSqlRecord rec = record(row);
//    Prediction *prediction = new Prediction();
//    foreach (Field field, mFields) {
//        prediction->setValue(field.mColumn, rec.value(field.mColumn));
//    }
//    return prediction;
//}

void PredictionsModel::updatePrediction(Prediction *prediction)
{
    QSqlQuery query;
    query.prepare("UPDATE predictions SET "
                  "raceId=:raceId,"
                  "vehicleId=:vehicleId,"

                  "dateTime=:dateTime,"

                  "vehicleWeight=:vehicleWeight,"
                  "riderWeight=:riderWeight,"

                  "temperature=:temperature,"
                  "humidity=:humidity,"
                  "pressure=:pressure,"
                  "vaporPressure=:vaporPressure,"
                  "dewPoint=:dewPoint,"
                  "densityAltitude=:densityAltitude,"
                  "windSpeed=:windSpeed,"
                  "windGust=:windGust,"
                  "windDirection=:windDirection,"

                  "windFactor=:windFactor,"
                  "weightFactor=:weightFactor,"

                  "eTp=:eTp,"
                  "eHp=:eHp,"
                  "ePp=:ePp,"
                  "eAp=:eAp,"
                  "eDp=:eDp,"
                  "windCorrectionEighth=:windCorrectionEighth,"

                  "qTp=:qTp,"
                  "qHp=:qHp,"
                  "qPp=:qPp,"
                  "qAp=:qAp,"
                  "qDp=:qDp,"
                  "windCorrectionQuarter=:windCorrectionQuarter "

                  "WHERE id=:id");

    query.bindValue(":raceId", prediction->value("raceId"));
    query.bindValue(":vehicleId", prediction->value("vehicleId"));

    query.bindValue(":dateTime", prediction->value("dateTime"));

    query.bindValue(":vehicleWeight", prediction->value("vehicleWeight"));
    query.bindValue(":riderWeight", prediction->value("riderWeight"));

    query.bindValue(":temperature", prediction->value("temperature"));
    query.bindValue(":humidity", prediction->value("humidity"));
    query.bindValue(":pressure", prediction->value("pressure"));
    query.bindValue(":vaporPressure", prediction->value("vaporPressure"));
    query.bindValue(":dewPoint", prediction->value("dewPoint"));
    query.bindValue(":densityAltitude", prediction->value("densityAltitude"));
    query.bindValue(":windSpeed", prediction->value("windSpeed"));
    query.bindValue(":windGust", prediction->value("windGust"));
    query.bindValue(":windDirection", prediction->value("windDirection"));

    query.bindValue(":windFactor", prediction->value("windFactor"));
    query.bindValue(":weightFactor", prediction->value("weightFactor"));

    query.bindValue(":eTp", prediction->value("eTp"));
    query.bindValue(":eHp", prediction->value("eHp"));
    query.bindValue(":ePp", prediction->value("ePp"));
    query.bindValue(":eAp", prediction->value("eAp"));
    query.bindValue(":eDp", prediction->value("eDp"));
    query.bindValue(":windCorrectionEighth", prediction->value("windCorrectionEighth"));

    query.bindValue(":qTp", prediction->value("qTp"));
    query.bindValue(":qHp", prediction->value("qHp"));
    query.bindValue(":qPp", prediction->value("qPp"));
    query.bindValue(":qAp", prediction->value("qAp"));
    query.bindValue(":qDp", prediction->value("qDp"));
    query.bindValue(":windCorrectionQuarter", prediction->windCorrectionQuarter());

    query.bindValue(":id", prediction->value("id"));

    query.exec();

    DatabaseManager::debugQuery(query);
}
