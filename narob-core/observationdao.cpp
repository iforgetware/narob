#include "observationdao.h"

#include <QSqlQuery>
#include <QVariant>

#include <QDebug>

#include "databasemanager.h"

ObservationDao::ObservationDao(QSqlDatabase &database) :
    mDatabase(database)
{
}

void ObservationDao::init() const
{
    if(!mDatabase.tables().contains("observations")){
        QSqlQuery query(mDatabase);
        query.exec("CREATE TABLE observations ("
                   "id INTEGER PRIMARY KEY,"

                   "dateTime TEXT,"

                   "temperature REAL,"
                   "humidity REAL,"
                   "pressure REAL,"
                   "vaporPressure REAL,"
                   "dewPoint REAL,"
                   "densityAltitude INTEGER,"
                   "windSpeed INTEGER,"
                   "windGust INTEGER,"
                   "windDirection INTEGER)");
        DatabaseManager::debugQuery(query);
    }
}

void ObservationDao::addObservation(Observation &observation) const
{
    QSqlQuery query(mDatabase);

    query.prepare("INSERT INTO observations ("
                  "dateTime,"

                  "temperature,"
                  "humidity,"
                  "pressure,"
                  "vaporPressure,"
                  "dewPoint,"
                  "densityAltitude,"
                  "windSpeed,"
                  "windGust,"
                  "windDirection"

                  ") VALUES ("

                  ":dateTime,"

                  ":temperature,"
                  ":humidity,"
                  ":pressure,"
                  ":vaporPressure,"
                  ":dewPoint,"
                  ":densityAltitude,"
                  ":windSpeed,"
                  ":windGust,"
                  ":windDirection"
                  ")");

    query.bindValue(":dateTime", observation.dateTime());

    query.bindValue(":temperature", observation.temperature());
    query.bindValue(":humidity", observation.humidity());
    query.bindValue(":pressure", observation.pressure());
    query.bindValue(":vaporPressure", observation.vaporPressure());
    query.bindValue(":dewPoint", observation.dewPoint());
    query.bindValue(":densityAltitude", observation.densityAltitude());
    query.bindValue(":windSpeed", observation.windSpeed());
    query.bindValue(":windGust", observation.windGust());
    query.bindValue(":windDirection", observation.windDirection());

    query.exec();

    DatabaseManager::debugQuery(query);

    observation.setId(query.lastInsertId().toInt());

}

void ObservationDao::removeObservation(int id) const
{
    QSqlQuery query(mDatabase);

    query.prepare("DELETE from observations WHERE id=:id");

    query.bindValue(":id", id);

    query.exec();

    DatabaseManager::debugQuery(query);
}

Observation* ObservationDao::observationForTime(QDateTime dateTime) const
{
    QSqlQuery query(mDatabase);

    query.prepare("SELECT * FROM observations WHERE "
                  "dateTime = :dateTime");
    query.bindValue(":dateTime", dateTime);

    query.exec();
    DatabaseManager::debugQuery(query);

    Observation* observation = new Observation();

    populateObservation(observation, query);

    return observation;
}

Observation* ObservationDao::latestObservation() const
{
    QSqlQuery query(mDatabase);

    query.prepare("SELECT * FROM observations "
                  "ORDER BY "
                  "dateTime DESC "
                  "LIMIT 1");

    query.exec();
    DatabaseManager::debugQuery(query);

    Observation* observation = new Observation();

    populateObservation(observation, query);

    return observation;
}

void ObservationDao::populateObservation(Observation* observation,
                                         QSqlQuery query) const
{
    if(query.next()){
        observation->setId(query.value("id").toInt());

        observation->setDateTime(query.value("dateTime").toDateTime());

        observation->setTemperature(query.value("temperature").toDouble());
        observation->setHumidity(query.value("humidity").toDouble());
        observation->setPressure(query.value("pressure").toDouble());
        observation->setVaporPressure(query.value("vaporPressure").toDouble());
        observation->setDewPoint(query.value("dewPoint").toDouble());
        observation->setDensityAltitude(query.value("densityAltitude").toInt());
        observation->setWindSpeed(query.value("windSpeed").toInt());
        observation->setWindGust(query.value("windGust").toInt());
        observation->setWindDirection(query.value("windDirection").toInt());
    }
}

QVector<Observation*> ObservationDao::observations() const
{
    QSqlQuery query("SELECT * FROM observations "
                    "ORDER BY "
                    "dateTime DESC"
                    , mDatabase);

    query.exec();

    QVector<Observation*> list;

    while(query.next()) {
        Observation* observation = new Observation();

        observation->setId(query.value("id").toInt());

        observation->setDateTime(query.value("dateTime").toDateTime());

        observation->setTemperature(query.value("temperature").toDouble());
        observation->setHumidity(query.value("humidity").toDouble());
        observation->setPressure(query.value("pressure").toDouble());
        observation->setVaporPressure(query.value("vaporPressure").toDouble());
        observation->setDewPoint(query.value("dewPoint").toDouble());
        observation->setDensityAltitude(query.value("densityAltitude").toInt());
        observation->setWindSpeed(query.value("windSpeed").toInt());
        observation->setWindGust(query.value("windGust").toInt());
        observation->setWindDirection(query.value("windDirection").toInt());

        list.append(observation);
    }

    return list;
}
