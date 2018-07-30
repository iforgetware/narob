#include "databasemanager.h"

#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>


DatabaseManager::DatabaseManager(QObject *parent) :
    QObject(parent)
{
    mDatabase = QSqlDatabase::addDatabase("QSQLITE");
    mDatabase.setDatabaseName("narob.sqlite");
    mDatabase.open();

//    clearDatabase(); //DEV ONLY

    initTables();
}

DatabaseManager::~DatabaseManager()
{
    mDatabase.close();
}

void DatabaseManager::debugQuery(const QSqlQuery& query)
{
    if (query.lastError().type() == QSqlError::ErrorType::NoError) {
//        qDebug() << "Query OK:"  << query.lastQuery();
    } else {
       qWarning() << "Query KO:" << query.lastError().text();
       qWarning() << "Query text:" << query.lastQuery();
    }
}

void DatabaseManager::initTables()
{
    tracks.init();
    races.init();
    vehicles.init();
    tickets.init();
    observations.init();
    predictions.init();
    refPTs.init();
    settings.init();
}

void DatabaseManager::clearDatabase() // DEV ONLY
{
    QSqlQuery query;

    QStringList tables = mDatabase.tables();

    foreach (QString table, tables){
        if(table != "settings"){
            query.exec(QString("DROP TABLE %1").arg(table));
            debugQuery(query);
        }
    }

    query.clear();

    qDebug("Dropped all database tables - DEV ONLY");
}

void DatabaseManager::testWeather() // DEV ONLY
{
    setupTest();

    ObservationsModel observationsModel;
    VehiclesModel vehiclesModel;
    RacesModel racesModel;

    Vehicle *vehicle = vehiclesModel.getVehicle(0);
    Race *race = racesModel.getRace(0);

    TicketsModel ticketsModel(vehicle, this);
    PredictionsModel predictionsModel(vehicle, race, this);

    Ticket t;

    t.setValue("vehicleId", 1);
    t.setValue("trackId", 1);
    t.setValue("raceId", 1);
    t.setValue("dateTime", QDateTime(QDate(2017, 03, 11),QTime(9, 25)));
    t.setValue("lane", "Right");
    t.setValue("dial", 8.80);
    t.setValue("reaction", 0.023);
    t.setValue("sixty", 1.337);
    t.setValue("threeThirty", 3.532);
    t.setValue("eighth", 4.000);
    t.setValue("eighthMPH", 125.00);
    t.setValue("eighthGood", false);
    t.setValue("thousand", 7.448);
    t.setValue("quarter" ,8.00);
    t.setValue("quarterMPH", 150.00);
    t.setValue("quarterGood", false);
    t.setValue("delay", 1.090);
    t.setValue("vehicleWeight", 350);
    t.setValue("riderWeight", 150.0);
    t.setValue("temperature", 40.0);
    t.setValue("humidity", 30.0);
    t.setValue("pressure", 33.00);
    t.setValue("vaporPressure", 0.54);
    t.setValue("dewPoint", 60.1);
    t.setValue("densityAltitude", -2000);
    t.setValue("windSpeed", 0);
    t.setValue("windGust", 0);
    t.setValue("windDirection", 0);

    ticketsModel.addRow(t);

    t.setValue("eighthGood", true);
    t.setValue("quarterGood", true);

    int i;
    int step = 1;

    for(i = 0; i < 4 * step; i += step){

        t.setValue("dateTime", QDateTime(QDate(2017, 03, 11),QTime(10 + i, 25)));
        t.setValue("eighth", 5.0 + (0.1 * i));
        t.setValue("quarter" ,10.0 + (0.2 * i));
        t.setValue("temperature", 60.0 + (10 * i));
        t.setValue("humidity", 30.0 + (10 * i));
        t.setValue("pressure", 31.00 - i);
        t.setValue("densityAltitude", 1000 * i);

        ticketsModel.addRow(t);
    }

    qDebug("Weather test - tickets written - DEV ONLY");

    Observation o;

    o.setValue("dateTime", QDateTime(QDate(2017, 03, 11), QTime(10 + i, 25)));
    o.setValue("temperature", 60.0 + (10 * i));
    o.setValue("humidity", 30.0 + (10 * i));
    o.setValue("pressure", 31.00 - i);
    o.setValue("vaporPressure", 0.54);
    o.setValue("dewPoint", 60.1);
    o.setValue("densityAltitude", 1000 * i);
    o.setValue("windSpeed", 0);
    o.setValue("windGust", 0);
    o.setValue("windDirection", 0);
    observationsModel.addRow(o);

    o.setValue("dateTime", QDateTime(QDate(2017,03,11), QTime(10, 25)));
    o.setValue("temperature", 60.0);
    o.setValue("humidity", 30.0);
    o.setValue("pressure", 31.00);
    o.setValue("densityAltitude", 0);
    observationsModel.addRow(o);

    qDebug("Weather test - observations written - DEV ONLY");

    Prediction p;

    p.setValue("vehicleId", 1);
    p.setValue("raceId", 1);
    p.setValue("riderWeight", 150);
    p.setValue("vehicleWeight", 350);

    p.setValue("windAdjustment", 0);
    p.setValue("weightAdjustment", 0);

    p.setValue("DateTime", QDateTime(QDate(1111,11,11), QTime(1, 11)));

    p.setValue("temperature", 60.0 + (10 * i));
    p.setValue("humidity", 30.0 + (10 * i));
    p.setValue("pressure", 31.00 - i);
    p.setValue("vaporPressure", 0.54);
    p.setValue("dewPoint", 60.1);
    p.setValue("densityAltitude", 1000 * i);
    p.setValue("windSpeed", 0);
    p.setValue("windGust", 0);
    p.setValue("windDirection", 0);

    p.setValue("eTp", 5.0 + (0.1 * i));
    p.setValue("eHp", 5.0 + (0.1 * i));
    p.setValue("ePp", 5.0 + (0.1 * i));
    p.setValue("eAp", 5.0 + (0.1 * i));
    p.setValue("eDp", 5.0 + (0.1 * i));

    p.setValue("qTp", 10.0 + (0.2 * i));
    p.setValue("qHp", 10.0 + (0.2 * i));
    p.setValue("qPp", 10.0 + (0.2 * i));
    p.setValue("qAp", 10.0 + (0.2 * i));
    p.setValue("qDp", 10.0 + (0.2 * i));

    predictionsModel.addRow(p);

    qDebug("Weather test - reference prediction written - DEV ONLY");
}

void DatabaseManager::testWind() // DEV ONLY
{
    setupTest();

    ObservationsModel observationsModel;
    VehiclesModel vehiclesModel;
    RacesModel racesModel;

    Vehicle *vehicle = vehiclesModel.getVehicle(0);
    Race *race = racesModel.getRace(0);

    TicketsModel ticketsModel(vehicle, this);
    PredictionsModel predictionsModel(vehicle, race, this);

    Ticket t;

    t.setValue("vehicleId", 1);
    t.setValue("trackId", 2);
    t.setValue("raceId", 2);
    t.setValue("lane", "Right");
    t.setValue("dial", 8.80);
    t.setValue("reaction", 0.023);
    t.setValue("sixty", 1.337);
    t.setValue("threeThirty", 3.532);
    t.setValue("eighth", 4.000);
    t.setValue("eighthMPH", 125.00);
    t.setValue("eighthGood", true);
    t.setValue("thousand", 7.448);
    t.setValue("quarter" ,8.00);
    t.setValue("quarterMPH", 150.00);
    t.setValue("quarterGood", true);
    t.setValue("delay", 1.090);
    t.setValue("vehicleWeight", 350);
    t.setValue("riderWeight", 150.0);
    t.setValue("temperature", 80.0);
    t.setValue("humidity", 50.0);
    t.setValue("pressure", 30.00);
    t.setValue("vaporPressure", 0.54);
    t.setValue("dewPoint", 60.1);
    t.setValue("densityAltitude", 1000);
    t.setValue("windDirection", 0);

    double windAdjustment = 0.010;
    int i;
    int step = 2;

    for(i = 0; i < 5 * step; i += step){

        t.setValue("dateTime", QDateTime(QDate(2017, 03, 11),QTime(10 + i, 25)));
        t.setValue("eighth", 5.0 + (windAdjustment / 2 * i));
        t.setValue("quarter" ,10.0 + (windAdjustment * i));
        t.setValue("windSpeed", i);
        t.setValue("windGust", i);

        ticketsModel.addRow(t);
    }

    qDebug("Wind test - tickets written - DEV ONLY");

    Observation o;

    o.setValue("dateTime", QDateTime(QDate(2017, 03, 11), QTime(10 + i, 25)));
    o.setValue("temperature", 80.0);
    o.setValue("humidity", 50.0);
    o.setValue("pressure", 30.00);
    o.setValue("vaporPressure", 0.54);
    o.setValue("dewPoint", 60.1);
    o.setValue("densityAltitude", 1000);
    o.setValue("windSpeed", i);
    o.setValue("windGust", i);
    o.setValue("windDirection", 0);
    observationsModel.addRow(o);

    qDebug("Wind test - observations written - DEV ONLY");

    Prediction p;

    p.setValue("vehicleId", vehicle->value("id").toInt());
    p.setValue("raceId", 2);
    p.setValue("riderWeight", 150);
    p.setValue("vehicleWeight", 350);

    p.setValue("windAdjustment", windAdjustment);
    p.setValue("weightAdjustment", 0);

    p.setValue("DateTime", QDateTime(QDate(1111,11,11), QTime(1, 11)));

    p.setValue("temperature", 80.0);
    p.setValue("humidity", 50.0);
    p.setValue("pressure", 30.00);
    p.setValue("vaporPressure", 0.54);
    p.setValue("dewPoint", 60.1);
    p.setValue("densityAltitude", 1000);
    p.setValue("windSpeed", i);
    p.setValue("windGust", i);
    p.setValue("windDirection", 0);

    p.setValue("eTp", 5.0 + (windAdjustment / 2 * i));
    p.setValue("eHp", 5.0 + (windAdjustment / 2 * i));
    p.setValue("ePp", 5.0 + (windAdjustment / 2 * i));
    p.setValue("eAp", 5.0 + (windAdjustment / 2 * i));
    p.setValue("eDp", 5.0 + (windAdjustment / 2 * i));

    p.setValue("qTp", 10.0 + (windAdjustment * i));
    p.setValue("qHp", 10.0 + (windAdjustment * i));
    p.setValue("qPp", 10.0 + (windAdjustment * i));
    p.setValue("qAp", 10.0 + (windAdjustment * i));
    p.setValue("qDp", 10.0 + (windAdjustment * i));

    predictionsModel.addRow(p);

    qDebug("Wind test - reference prediction written - DEV ONLY");
}

void DatabaseManager::testWeight() // DEV ONLY
{
    setupTest();

    ObservationsModel observationsModel;
    VehiclesModel vehiclesModel;
    RacesModel racesModel;

    Vehicle *vehicle = vehiclesModel.getVehicle(0);
    Race *race = racesModel.getRace(0);

    TicketsModel ticketsModel(vehicle, this);
    PredictionsModel predictionsModel(vehicle, race, this);


    Ticket t;

    t.setValue("vehicleId", 1);
    t.setValue("trackId", 1);
    t.setValue("raceId", 3);
    t.setValue("lane", "Right");
    t.setValue("dial", 8.80);
    t.setValue("reaction", 0.023);
    t.setValue("sixty", 1.337);
    t.setValue("threeThirty", 3.532);
    t.setValue("eighth", 5.000);
    t.setValue("eighthMPH", 125.00);
    t.setValue("eighthGood", true);
    t.setValue("thousand", 7.448);
    t.setValue("quarter", 10.00);
    t.setValue("quarterMPH", 150.00);
    t.setValue("quarterGood", true);
    t.setValue("delay", 1.090);
    t.setValue("vehicleWeight", 350);
    t.setValue("temperature", 80.0);
    t.setValue("humidity", 50.0);
    t.setValue("pressure", 30.00);
    t.setValue("vaporPressure", 0.54);
    t.setValue("dewPoint", 60.1);
    t.setValue("densityAltitude", 1000);
    t.setValue("windSpeed", 0);
    t.setValue("windGust", 0);
    t.setValue("windDirection", 0);

    double weightAdjustment = .010;
    int i;
    int step = 2;

    for(i = 0; i < 4 * step; i += step){

        t.setValue("dateTime", QDateTime(QDate(2017, 03, 11),QTime(10 + i, 25)));
        t.setValue("eighth", 5.0 + (weightAdjustment / 2 * i));
        t.setValue("quarter" ,10.0 + (weightAdjustment * i));
        t.setValue("riderWeight", 150.0 + i);

        ticketsModel.addRow(t);
    }

    qDebug("Weight test - tickets written - DEV ONLY");

    Observation o;

    o.setValue("dateTime", QDateTime(QDate(2017, 03, 11), QTime(10 + i, 25)));
    o.setValue("temperature", 80.0);
    o.setValue("humidity", 50.0);
    o.setValue("pressure", 30.00);
    o.setValue("vaporPressure", 0.54);
    o.setValue("dewPoint", 60.1);
    o.setValue("densityAltitude", 1000);
    o.setValue("windSpeed", 0);
    o.setValue("windGust", 0);
    o.setValue("windDirection", 0);
    observationsModel.addRow(o);

    qDebug("Weight test - observation written - DEV ONLY");

    Prediction p;

    p.setValue("vehicleId", vehicle->value("id").toInt());
    p.setValue("raceId", 3);
    p.setValue("riderWeight", 150.0 + i);
    p.setValue("vehicleWeight", 350);

    p.setValue("windAdjustment", 0);
    p.setValue("weightAdjustment", weightAdjustment);

    p.setValue("DateTime", QDateTime(QDate(1111,11,11), QTime(1, 11)));

    p.setValue("temperature", 80.0);
    p.setValue("humidity", 50.0);
    p.setValue("pressure", 30.00);
    p.setValue("vaporPressure", 0.54);
    p.setValue("dewPoint", 60.1);
    p.setValue("densityAltitude", 1000);
    p.setValue("windSpeed", 0);
    p.setValue("windGust", 0);
    p.setValue("windDirection", 0);

    p.setValue("eTp", 5.0 + (weightAdjustment / 2 * i));
    p.setValue("eHp", 5.0 + (weightAdjustment / 2 * i));
    p.setValue("ePp", 5.0 + (weightAdjustment / 2 * i));
    p.setValue("eAp", 5.0 + (weightAdjustment / 2 * i));
    p.setValue("eDp", 5.0 + (weightAdjustment / 2 * i));

    p.setValue("qTp", 10.0 + (weightAdjustment * i));
    p.setValue("qHp", 10.0 + (weightAdjustment * i));
    p.setValue("qPp", 10.0 + (weightAdjustment * i));
    p.setValue("qAp", 10.0 + (weightAdjustment * i));
    p.setValue("qDp", 10.0 + (weightAdjustment * i));

    predictionsModel.addRow(p);

    qDebug("Weight test - reference prediction written - DEV ONLY");
}

void DatabaseManager::setupTest()
{
    QSqlQuery query;

    QStringList tables = mDatabase.tables();

    foreach (QString table, tables){
        if(table != "settings"){
            query.exec(QString("DROP TABLE %1").arg(table));
            debugQuery(query);

            qDebug() << QString("Dropped table %1 - DEV ONLY").arg(table);
        }
    }

    initTables();

    query.clear();

    TracksModel tracksModel(this);
    RacesModel racesModel(this);
    VehiclesModel vehiclesModel(this);

    Track t1;

    t1.setValue("name", "track1");
    t1.setValue("elevation", 8);
    t1.setValue("bearing", 97);
    t1.setValue("radio", 89.5);
    tracksModel.addRow(t1);

    Track t2;

    t2.setValue("name", "track2");
    t2.setValue("elevation", 30);
    t2.setValue("bearing", 360);
    t2.setValue("radio", 87.9);
    tracksModel.addRow(t2);

    Race r1;

    r1.setValue("date", QDate(2017, 03, 11));
    r1.setValue("name", "weather test");
    r1.setValue("trackId", 1);
    racesModel.addRow(r1);

    Race r2;

    r2.setValue("date", QDate(2017, 04, 27));
    r2.setValue("name", "wind test");
    r2.setValue("trackId", 2);
    racesModel.addRow(r2);

    Race r3;

    r3.setValue("date", QDate(2017, 03, 15));
    r3.setValue("name", "weight test");
    r3.setValue("trackId", 1);
    racesModel.addRow(r3);

    Vehicle v1;

    v1.setValue("number", "4270");
    v1.setValue("compClass", "ETMX");
    v1.setValue("weight", 350);
    vehiclesModel.addRow(v1);

    Vehicle v2;

    v2.setValue("number", "42");
    v2.setValue("compClass", "ETMX");
    v2.setValue("Weight", 375);
    vehiclesModel.addRow(v2);

    qDebug("Test tracks, races, and vehicles written - DEV ONLY");
}
