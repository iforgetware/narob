#include "predictiondao.h"

#include <QSqlQuery>
#include <QVariant>

#include <QDebug>

#include "databasemanager.h"

PredictionDao::PredictionDao(QSqlDatabase &database) :
    mDatabase(database)
{
}

void PredictionDao::init() const
{
    if(!mDatabase.tables().contains("predictions")){
        QSqlQuery query(mDatabase);
        query.exec("CREATE TABLE predictions ("
                   "id INTEGER PRIMARY KEY,"

                   "raceId INTEGER,"
                   "vehicleId INTEGER,"

                   "date TEXT,"
                   "time TEXT,"

                   "vehicleWeight INTEGER,"
                   "riderWeight REAL,"

                   "temperature REAL,"
                   "humidity REAL,"
                   "pressure REAL,"
                   "vaporPressure REAL,"
                   "dewPoint REAL,"
                   "densityAltitude INTEGER,"
                   "windSpeed INTEGER,"
                   "windGust INTEGER,"
                   "windDirection INTEGER,"

                   "windFactor INTEGER,"
                   "weightFactor INTEGER,"

                   "eTp REAL,"
                   "eHp REAL,"
                   "ePp REAL,"
                   "eAp REAL,"
                   "eDp REAL,"
                   "windCorrectionEighth REAL,"

                   "qTp REAL,"
                   "qHp REAL,"
                   "qPp REAL,"
                   "qAp REAL,"
                   "qDp REAL,"
                   "windCorrectionQuarter REAL)");
        DatabaseManager::debugQuery(query);
    }
}

void PredictionDao::addPrediction(Prediction *prediction) const
{
    QSqlQuery query(mDatabase);

    query.prepare("INSERT INTO predictions ("
                  "raceId,"
                  "vehicleId,"

                  "date,"
                  "time,"

                  "vehicleWeight,"
                  "riderWeight,"

                  "temperature,"
                  "humidity,"
                  "pressure,"
                  "vaporPressure,"
                  "dewPoint,"
                  "densityAltitude,"
                  "windSpeed,"
                  "windGust,"
                  "windDirection,"

                  "windFactor,"
                  "weightFactor,"

                  "eTp,"
                  "eHp,"
                  "ePp,"
                  "eAp,"
                  "eDp,"
                  "windCorrectionEighth,"

                  "qTp,"
                  "qHp,"
                  "qPp,"
                  "qAp,"
                  "qDp,"
                  "windCorrectionQuarter"

                  ") VALUES ("

                  ":raceId,"
                  ":vehicleId,"

                  ":date,"
                  ":time,"

                  ":vehicleWeight,"
                  ":riderWeight,"

                  ":temperature,"
                  ":humidity,"
                  ":pressure,"
                  ":vaporPressure,"
                  ":dewPoint,"
                  ":densityAltitude,"
                  ":windSpeed,"
                  ":windGust,"
                  ":windDirection,"

                  ":windFactor,"
                  ":weightFactor,"

                  ":eTp,"
                  ":eHp,"
                  ":ePp,"
                  ":eAp,"
                  ":eDp,"
                  ":windCorrectionEighth,"

                  ":qTp,"
                  ":qHp,"
                  ":qPp,"
                  ":qAp,"
                  ":qDp,"
                  ":windCorrectionQuarter"
                  ")");

    query.bindValue(":raceId", prediction->raceId());
    query.bindValue(":vehicleId", prediction->vehicleId());

    query.bindValue(":date", prediction->date());
    query.bindValue(":time", prediction->time());

    query.bindValue(":vehicleWeight", prediction->vehicleWeight());
    query.bindValue(":riderWeight", prediction->riderWeight());

    query.bindValue(":temperature", prediction->temperature());
    query.bindValue(":humidity", prediction->humidity());
    query.bindValue(":pressure", prediction->pressure());
    query.bindValue(":vaporPressure", prediction->vaporPressure());
    query.bindValue(":dewPoint", prediction->dewPoint());
    query.bindValue(":densityAltitude", prediction->densityAltitude());
    query.bindValue(":windSpeed", prediction->windSpeed());
    query.bindValue(":windGust", prediction->windGust());
    query.bindValue(":windDirection", prediction->windDirection());

    query.bindValue(":windFactor", prediction->windFactor());
    query.bindValue(":weightFactor", prediction->weightFactor());

    query.bindValue(":eTp", prediction->eTp());
    query.bindValue(":eHp", prediction->eHp());
    query.bindValue(":ePp", prediction->ePp());
    query.bindValue(":eAp", prediction->eAp());
    query.bindValue(":eDp", prediction->eDp());
    query.bindValue(":windCorrectionEighth", prediction->windCorrectionEighth());

    query.bindValue(":qTp", prediction->qTp());
    query.bindValue(":qHp", prediction->qHp());
    query.bindValue(":qPp", prediction->qPp());
    query.bindValue(":qAp", prediction->qAp());
    query.bindValue(":qDp", prediction->qDp());
    query.bindValue(":windCorrectionQuarter", prediction->windCorrectionQuarter());

    query.exec();

    DatabaseManager::debugQuery(query);

    prediction->setId(query.lastInsertId().toInt());
}

void PredictionDao::updatePrediction(const Prediction* prediction) const
{
    QSqlQuery query(mDatabase);

    query.prepare("UPDATE predictions SET "
                  "raceId=:raceId,"
                  "vehicleId=:vehicleId,"

                  "date=:date,"
                  "time=:time,"

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

    query.bindValue(":raceId", prediction->raceId());
    query.bindValue(":vehicleId", prediction->vehicleId());

    query.bindValue(":date", prediction->date());
    query.bindValue(":time", prediction->time());

    query.bindValue(":vehicleWeight", prediction->vehicleWeight());
    query.bindValue(":riderWeight", prediction->riderWeight());

    query.bindValue(":temperature", prediction->temperature());
    query.bindValue(":humidity", prediction->humidity());
    query.bindValue(":pressure", prediction->pressure());
    query.bindValue(":vaporPressure", prediction->vaporPressure());
    query.bindValue(":dewPoint", prediction->dewPoint());
    query.bindValue(":densityAltitude", prediction->densityAltitude());
    query.bindValue(":windSpeed", prediction->windSpeed());
    query.bindValue(":windGust", prediction->windGust());
    query.bindValue(":windDirection", prediction->windDirection());

    query.bindValue(":windFactor", prediction->windFactor());
    query.bindValue(":weightFactor", prediction->weightFactor());

    query.bindValue(":eTp", prediction->eTp());
    query.bindValue(":eHp", prediction->eHp());
    query.bindValue(":ePp", prediction->ePp());
    query.bindValue(":eAp", prediction->eAp());
    query.bindValue(":eDp", prediction->eDp());
    query.bindValue(":windCorrectionEighth", prediction->windCorrectionEighth());

    query.bindValue(":qTp", prediction->qTp());
    query.bindValue(":qHp", prediction->qHp());
    query.bindValue(":qPp", prediction->qPp());
    query.bindValue(":qAp", prediction->qAp());
    query.bindValue(":qDp", prediction->qDp());
    query.bindValue(":id", prediction->id());
    query.bindValue(":windCorrectionQuarter", prediction->windCorrectionQuarter());

    query.exec();

    DatabaseManager::debugQuery(query);
}

void PredictionDao::removePrediction(int id) const
{
    QSqlQuery query(mDatabase);

    query.prepare("DELETE from predictions WHERE id=:id");

    query.bindValue(":id", id);

    query.exec();

    DatabaseManager::debugQuery(query);
}

QVector<Prediction*> PredictionDao::predictionsForVehicleAndRace(int vehicleId,
                                                                 int raceId) const
{
    QSqlQuery query(mDatabase);
    query.prepare("SELECT * FROM predictions WHERE "
                  "raceId = :raceId AND "
                  "vehicleId = :vehicleId"
                  "ORDER BY "
                  "date DESC,"
                  "time DESC");
    query.bindValue(":raceId", raceId);
    query.bindValue(":vehicleId", vehicleId);

    query.exec();

    QVector<Prediction*> list;

    while(query.next()) {
        Prediction* prediction = new Prediction();

        prediction->setId(query.value("id").toInt());

        prediction->setRaceId(query.value("raceId").toInt());
        prediction->setVehicleId(query.value("vehicleId").toInt());

        prediction->setDate(query.value("date").toDate());
        prediction->setTime(query.value("time").toTime());

        prediction->setVehicleWeight(query.value("vehicleWeight").toInt());
        prediction->setRiderWeight(query.value("riderWeight").toDouble());

        prediction->setTemperature(query.value("temperature").toDouble());
        prediction->setHumidity(query.value("humidity").toDouble());
        prediction->setPressure(query.value("pressure").toDouble());
        prediction->setVaporPressure(query.value("vaporPressure").toDouble());
        prediction->setDewPoint(query.value("dewPoint").toDouble());
        prediction->setDensityAltitude(query.value("densityAltitude").toInt());
        prediction->setWindSpeed(query.value("windSpeed").toInt());
        prediction->setWindGust(query.value("windGust").toInt());
        prediction->setWindDirection(query.value("windDirection").toInt());

        prediction->setWindFactor(query.value("windFactor").toInt());
        prediction->setWeightFactor(query.value("weightFactor").toInt());

        prediction->setETp(query.value("eTp").toDouble());
        prediction->setEHp(query.value("eHp").toDouble());
        prediction->setEPp(query.value("ePp").toDouble());
        prediction->setEAp(query.value("eAp").toDouble());
        prediction->setEDp(query.value("eDp").toDouble());
        prediction->setWindCorrectionEighth(query.value("windCorrectionEighth").toDouble());

        prediction->setQTp(query.value("qTp").toDouble());
        prediction->setQHp(query.value("qHp").toDouble());
        prediction->setQPp(query.value("qPp").toDouble());
        prediction->setQAp(query.value("qAp").toDouble());
        prediction->setQDp(query.value("qDp").toDouble());
        prediction->setWindCorrectionQuarter(query.value("windCorrectionQuarter").toDouble());

        list.append(prediction);
    }

    return list;
}
