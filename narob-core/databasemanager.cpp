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
//    refPTs.init();
    settings.init();
}

void DatabaseManager::updateLogbook()
{
    QSqlQuery query;
    query.exec("DROP TABLE IF EXISTS refPTs");
    debugQuery(query);
    query.exec("DROP TABLE predictions");
    debugQuery(query);
    query.exec("ALTER TABLE tickets RENAME TO ticketsOld");
    debugQuery(query);

    predictions.init();

    Fields otFields;

    otFields << Field("id", "id", 0, 0)

             << Field("vehicleId", "Vehicle", 150, 0)
             << Field("trackId", "Track", 150, 0)
             << Field("raceId", "Race", 150, 0)
             << Field("predictionId", "Prediction", 0, 0)

             << Field("dateTime", "Date       Time", 160, -3)

             << Field("lane", "Lane", 50, 0)
             << Field("delay", "Delay", 50, 3)
             << Field("reaction", "R/T", 60, 3)
             << Field("sixty", "60'", 50, 13)
             << Field("threeThirty", "330'", 50, 13)
             << Field("eighth", "1/8", 50, 13)
             << Field("eighthMPH", "1/8 MPH", 75, 2)
             << Field("eighthGood", "", 70, -1)
             << Field("thousand", "1000'", 50, 13)
             << Field("quarter", "1/4", 60, 13)
             << Field("quarterMPH", "1/4 MPH", 75, 2)
             << Field("quarterGood", "", 70, -1)

             << Field("dial", "Dial", 50, 2)
             << Field("vehicleWeight", "V Weight", 70, 0)
             << Field("riderWeight", "R Weight", 70, 1)

             << Field("temperature", "Temp", 50, 1)
             << Field("humidity", "Humid",50, 1)
             << Field("pressure", "Pres", 50, 2)
             << Field("vaporPressure", "V Pres", 50, 2)
             << Field("dewPoint", "D Point", 60, 1)
             << Field("densityAltitude", "D Alt", 50, 0)
             << Field("windSpeed", "W Speed", 70, 0)
             << Field("windGust", "W Gust", 70, 0)
             << Field("windDirection", "W Dir", 60, 0)

             << Field("notes", "Notes", 0, 0)

             << Field("pm5Id", "pm5Id", 0, 0)
             << Field("pm4Id", "pm4Id", 0, 0)
             << Field("pm3Id", "pm3Id", 0, 0)
             << Field("pm2Id", "pm2Id", 0, 0)
             << Field("pm1Id", "pm1Id", 0, 0)
             << Field("p0Id" , "p0Id" , 0, 0)
             << Field("pp1Id", "pp1Id", 0, 0)
             << Field("pp2Id", "pp2Id", 0, 0)
             << Field("pp3Id", "pp3Id", 0, 0)
             << Field("pp4Id", "pp4Id", 0, 0)
             << Field("pp5Id", "pp5Id", 0, 0);

    Fields ntFields;

    ntFields << Field("id", "id", 0, 0)

             << Field("vehicleId", "Vehicle", 150, 0)
             << Field("trackId", "Track", 150, 0)
             << Field("raceId", "Race", 150, 0)

             << Field("dateTime", "Date       Time", 160, -3)

             << Field("lane", "Lane", 50, 0)
             << Field("delay", "Delay", 50, 3)
             << Field("reaction", "R/T", 60, 3)
             << Field("sixty", "60'", 50, 13)
             << Field("threeThirty", "330'", 50, 13)
             << Field("eighth", "1/8", 50, 13)
             << Field("eighthMPH", "1/8 MPH", 75, 2)
             << Field("thousand", "1000'", 50, 13)
             << Field("quarter", "1/4", 60, 13)
             << Field("quarterMPH", "1/4 MPH", 75, 2)

             << Field("dial", "Dial", 50, 2)
             << Field("vehicleWeight", "V Weight", 70, 0)
             << Field("riderWeight", "R Weight", 70, 1)

             << Field("temperature", "Temp", 50, 1)
             << Field("humidity", "Humid",50, 1)
             << Field("pressure", "Pres", 50, 2)
             << Field("vaporPressure", "V Pres", 50, 2)
             << Field("dewPoint", "D Point", 60, 1)
             << Field("densityAltitude", "D Alt", 50, 0)
             << Field("windSpeed", "W Speed", 70, 0)
             << Field("windGust", "W Gust", 70, 0)
             << Field("windDirection", "W Dir", 60, 0)

             << Field("notes", "Notes", 0, 0);

    DbRecordBase oldTicket;
    oldTicket.setFields(otFields);
    oldTicket.init("ticketsOld");

    tickets.init();
    DbRecordBase newTicket;
    newTicket.setFields(ntFields);
    newTicket.init("tickets");

    ModelBase oldTicketsModel("ticketsOld", otFields);
    ModelBase newTicketsModel("tickets", ntFields);

    for(int r = 0; r < oldTicketsModel.rowCount(); r++){
        oldTicket.populate(oldTicketsModel.record(r));
        foreach(Field field, ntFields){
            newTicket.setValue(field.mColumn,
                               oldTicket.value(field.mColumn));
        }

        if(!oldTicket.value("eighthGood").toBool()){
            newTicket.setValue("sixty",
                               -oldTicket.value("sixty").toDouble());
            newTicket.setValue("threeThirty",
                               -oldTicket.value("threeThirty").toDouble());
            newTicket.setValue("eighth",
                               -oldTicket.value("eighth").toDouble());
        }

        if(!oldTicket.value("quarterGood").toBool()){
            newTicket.setValue("thousand",
                               -oldTicket.value("thousand").toDouble());
            newTicket.setValue("quarter",
                               -oldTicket.value("quarter").toDouble());
        }

        newTicketsModel.addRow(newTicket);
    }

    query.exec("DROP TABLE ticketsOld");
    debugQuery(query);
    query.clear();
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
    PredictionsModel predictionsModel(vehicle, race, 0, this);

    Ticket t;

    t.setValue("vehicleId", 1);
    t.setValue("trackId", 1);
    t.setValue("raceId", 1);
    t.setValue("dateTime", QDateTime(QDate(2017, 03, 11),QTime(9, 25)));
    t.setValue("lane", "Right");
    t.setValue("dial", 8.80);
    t.setValue("reaction", 0.023);
    t.setValue("sixty", -1.330);
    t.setValue("threeThirty", -3.500);
    t.setValue("eighth", -4.000);
    t.setValue("eighthMPH", 125.00);
    t.setValue("thousand", -7.448);
    t.setValue("quarter" , -8.000);
    t.setValue("quarterMPH", 150.00);
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

    int i;
    int step = 1;

    for(i = 0; i < 4 * step; i += step){
        t.setValue("dateTime", QDateTime(QDate(2017, 03, 11),QTime(10 + i, 25)));
        t.setValue("sixty", 1.32 + (0.2 / 22.0 * i));
        t.setValue("threeThirty", 3.71 + (0.2 / 4.0 * i));
        t.setValue("eighth", 5.65 + (0.2 / 2.0 * i));
        t.setValue("thousand", 7.41 + (0.2 / 1.32 * i));
        t.setValue("quarter" ,8.93 + (0.2 / 1.0 * i));
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
    p.setValue("trackId", 1);
    p.setValue("ticketId", 0);
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

    p.setValue("sixtyD", 1.32 + (0.2 / 22.0 * i));
    p.setValue("sixtyA", 1.32 + (0.2 / 22.0 * i));
    p.setValue("sixtyT", 1.32 + (0.2 / 22.0 * i));
    p.setValue("sixtyH", 1.32 + (0.2 / 22.0 * i));
    p.setValue("sixtyP", 1.32 + (0.2 / 22.0 * i));

    p.setValue("threeThirtyD", 3.71 + (0.2 / 4.0 * i));
    p.setValue("threeThirtyA", 3.71 + (0.2 / 4.0 * i));
    p.setValue("threeThirtyT", 3.71 + (0.2 / 4.0 * i));
    p.setValue("threeThirtyH", 3.71 + (0.2 / 4.0 * i));
    p.setValue("threeThirtyP", 3.71 + (0.2 / 4.0 * i));

    p.setValue("eighthD", 5.65 + (0.2 / 2.0 * i));
    p.setValue("eighthA", 5.65 + (0.2 / 2.0 * i));
    p.setValue("eighthT", 5.65 + (0.2 / 2.0 * i));
    p.setValue("eighthH", 5.65 + (0.2 / 2.0 * i));
    p.setValue("eighthP", 5.65 + (0.2 / 2.0 * i));

    p.setValue("thousandD", 7.41 + (0.2 / 1.32 * i));
    p.setValue("thousandA", 7.41 + (0.2 / 1.32 * i));
    p.setValue("thousandT", 7.41 + (0.2 / 1.32 * i));
    p.setValue("thousandH", 7.41 + (0.2 / 1.32 * i));
    p.setValue("thousandP", 7.41 + (0.2 / 1.32 * i));

    p.setValue("quarterD", 8.93 + (0.2 / 1.0 * i));
    p.setValue("quarterA", 8.93 + (0.2 / 1.0 * i));
    p.setValue("quarterT", 8.93 + (0.2 / 1.0 * i));
    p.setValue("quarterH", 8.93 + (0.2 / 1.0 * i));
    p.setValue("quarterP", 8.93 + (0.2 / 1.0 * i));

    predictionsModel.addRow(p);

    qDebug("Weather test - reference prediction written - DEV ONLY");
}

void DatabaseManager::testTP() // DEV ONLY
{
    setupTest();

    ObservationsModel observationsModel;
    VehiclesModel vehiclesModel;

    Vehicle *vehicle = vehiclesModel.getVehicle(0);

    TicketsModel ticketsModel(vehicle, this);

    Ticket t;
    Observation o;

    t.setValue("vehicleId", 1);
    t.setValue("trackId", 1);
    t.setValue("raceId", 4);
    t.setValue("lane", "Right");
    t.setValue("dial", 8.80);
    t.setValue("reaction", 0.023);
    t.setValue("eighthMPH", 125.00);
    t.setValue("quarterMPH", 150.00);
    t.setValue("delay", 1.090);
    t.setValue("vehicleWeight", 350);
    t.setValue("riderWeight", 150.0);
    t.setValue("vaporPressure", 0.54);
    t.setValue("dewPoint", 60.1);
    t.setValue("windSpeed", 0);
    t.setValue("windGust", 0);
    t.setValue("windDirection", 0);

    int i;
    int step = 1;

    for(i = 0; i < 11 * step; i += step){
        QDateTime dateTime = QDateTime(QDate(2017, 03, 11),QTime(10, 25 + i));
        double temperature = 60.0 + (1 * i);
        double humidity = 30.0 + (1 * i);
        double pressure = 31.00 - (i / 10.0);
        double densityAltitude = 1000 + i;

        t.setValue("dateTime", dateTime);
        t.setValue("sixty", 1.32 + (0.02 / 22.0 * i));
        t.setValue("threeThirty", 3.71 + (0.02 / 4.0 * i));
        t.setValue("eighth", 5.65 + (0.02 / 2.0 * i));
        t.setValue("thousand", 7.41 + (0.02 / 1.32 * i));
        t.setValue("quarter" ,8.93 + (0.02 / 1.0 * i));
        t.setValue("temperature", temperature);
        t.setValue("humidity", humidity);
        t.setValue("pressure", pressure);
        t.setValue("densityAltitude", densityAltitude);

        ticketsModel.addRow(t);

        o.setValue("dateTime", dateTime);
        o.setValue("temperature", temperature);
        o.setValue("humidity", humidity);
        o.setValue("pressure", pressure);
        o.setValue("vaporPressure", 0.54);
        o.setValue("dewPoint", 60.1);
        o.setValue("densityAltitude", densityAltitude);
        o.setValue("windSpeed", 0);
        o.setValue("windGust", 0);
        o.setValue("windDirection", 0);
        observationsModel.addRow(o);
    }

    qDebug("Ticket with Predictions test - tickets written - DEV ONLY");
    qDebug("Ticket with Predictions test - observations written - DEV ONLY");
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
    PredictionsModel predictionsModel(vehicle, race, 0, this);

    Ticket t;

    t.setValue("vehicleId", 1);
    t.setValue("trackId", 2);
    t.setValue("raceId", 2);
    t.setValue("lane", "Right");
    t.setValue("dial", 8.80);
    t.setValue("reaction", 0.023);
    t.setValue("sixty", -1.337);
    t.setValue("threeThirty", -3.532);
    t.setValue("eighth", -4.000);
    t.setValue("eighthMPH", 125.00);
    t.setValue("thousand", -7.448);
    t.setValue("quarter" ,-8.00);
    t.setValue("quarterMPH", 150.00);
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
        t.setValue("sixty", 1.32 + (windAdjustment / 22.0 * i));
        t.setValue("threeThirty", 3.71 + (windAdjustment / 4.0 * i));
        t.setValue("eighth", 5.65 + (windAdjustment / 2.0 * i));
        t.setValue("thousand", 7.41 + (windAdjustment / 1.32 * i));
        t.setValue("quarter" ,8.93 + (windAdjustment / 1.0 * i));
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
    p.setValue("trackId", 2);
    p.setValue("ticketId", 0);
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

    p.setValue("sixtyD", 1.32 + (windAdjustment / 22.0 * i));
    p.setValue("sixtyA", 1.32 + (windAdjustment / 22.0 * i));
    p.setValue("sixtyT", 1.32 + (windAdjustment / 22.0 * i));
    p.setValue("sixtyH", 1.32 + (windAdjustment / 22.0 * i));
    p.setValue("sixtyP", 1.32 + (windAdjustment / 22.0 * i));

    p.setValue("threeThirtyD", 3.71 + (windAdjustment / 4.0 * i));
    p.setValue("threeThirtyA", 3.71 + (windAdjustment / 4.0 * i));
    p.setValue("threeThirtyT", 3.71 + (windAdjustment / 4.0 * i));
    p.setValue("threeThirtyH", 3.71 + (windAdjustment / 4.0 * i));
    p.setValue("threeThirtyP", 3.71 + (windAdjustment / 4.0 * i));

    p.setValue("eighthD", 5.65 + (windAdjustment / 2.0 * i));
    p.setValue("eighthA", 5.65 + (windAdjustment / 2.0 * i));
    p.setValue("eighthT", 5.65 + (windAdjustment / 2.0 * i));
    p.setValue("eighthH", 5.65 + (windAdjustment / 2.0 * i));
    p.setValue("eighthP", 5.65 + (windAdjustment / 2.0 * i));

    p.setValue("thousandD", 7.41 + (windAdjustment / 1.32 * i));
    p.setValue("thousandA", 7.41 + (windAdjustment / 1.32 * i));
    p.setValue("thousandT", 7.41 + (windAdjustment / 1.32 * i));
    p.setValue("thousandH", 7.41 + (windAdjustment / 1.32 * i));
    p.setValue("thousandP", 7.41 + (windAdjustment / 1.32 * i));

    p.setValue("quarterD", 8.93 + (windAdjustment / 1.0 * i));
    p.setValue("quarterA", 8.93 + (windAdjustment / 1.0 * i));
    p.setValue("quarterT", 8.93 + (windAdjustment / 1.0 * i));
    p.setValue("quarterH", 8.93 + (windAdjustment / 1.0 * i));
    p.setValue("quarterP", 8.93 + (windAdjustment / 1.0 * i));

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
    PredictionsModel predictionsModel(vehicle, race, 0, this);


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
    t.setValue("thousand", 7.448);
    t.setValue("quarter", 10.00);
    t.setValue("quarterMPH", 150.00);
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
        t.setValue("sixty", 1.32 + (weightAdjustment / 22.0 * i));
        t.setValue("threeThirty", 3.71 + (weightAdjustment / 4.0 * i));
        t.setValue("eighth", 5.65 + (weightAdjustment / 2.0 * i));
        t.setValue("thousand", 7.41 + (weightAdjustment / 1.32 * i));
        t.setValue("quarter" ,8.93 + (weightAdjustment / 1.0 * i));
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
    p.setValue("trackId", 1);
    p.setValue("ticketId", 0);
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

    p.setValue("sixtyD", 1.32 + (weightAdjustment / 22.0 * i));
    p.setValue("sixtyA", 1.32 + (weightAdjustment / 22.0 * i));
    p.setValue("sixtyT", 1.32 + (weightAdjustment / 22.0 * i));
    p.setValue("sixtyH", 1.32 + (weightAdjustment / 22.0 * i));
    p.setValue("sixtyP", 1.32 + (weightAdjustment / 22.0 * i));

    p.setValue("threeThirtyD", 3.71 + (weightAdjustment / 4.0 * i));
    p.setValue("threeThirtyA", 3.71 + (weightAdjustment / 4.0 * i));
    p.setValue("threeThirtyT", 3.71 + (weightAdjustment / 4.0 * i));
    p.setValue("threeThirtyH", 3.71 + (weightAdjustment / 4.0 * i));
    p.setValue("threeThirtyP", 3.71 + (weightAdjustment / 4.0 * i));

    p.setValue("eighthD", 5.65 + (weightAdjustment / 2.0 * i));
    p.setValue("eighthA", 5.65 + (weightAdjustment / 2.0 * i));
    p.setValue("eighthT", 5.65 + (weightAdjustment / 2.0 * i));
    p.setValue("eighthH", 5.65 + (weightAdjustment / 2.0 * i));
    p.setValue("eighthP", 5.65 + (weightAdjustment / 2.0 * i));

    p.setValue("thousandD", 7.41 + (weightAdjustment / 1.32 * i));
    p.setValue("thousandA", 7.41 + (weightAdjustment / 1.32 * i));
    p.setValue("thousandT", 7.41 + (weightAdjustment / 1.32 * i));
    p.setValue("thousandH", 7.41 + (weightAdjustment / 1.32 * i));
    p.setValue("thousandP", 7.41 + (weightAdjustment / 1.32 * i));

    p.setValue("quarterD", 8.93 + (weightAdjustment / 1.0 * i));
    p.setValue("quarterA", 8.93 + (weightAdjustment / 1.0 * i));
    p.setValue("quarterT", 8.93 + (weightAdjustment / 1.0 * i));
    p.setValue("quarterH", 8.93 + (weightAdjustment / 1.0 * i));
    p.setValue("quarterP", 8.93 + (weightAdjustment / 1.0 * i));

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

    Race r4;

    r4.setValue("date", QDate(2017, 03, 15));
    r4.setValue("name", "ticket prediction test");
    r4.setValue("trackId", 1);
    racesModel.addRow(r4);

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
