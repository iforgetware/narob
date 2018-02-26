#include "databasemanager.h"

#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

DatabaseManager &DatabaseManager::instance()
{
    static DatabaseManager singleton;
    return singleton;
}

DatabaseManager::DatabaseManager(const QString &path) :
    mDatabase(new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"))),
    trackDao(*mDatabase),
    raceDao(*mDatabase),
    vehicleDao(*mDatabase),
    ticketDao(*mDatabase),
    observationDao(*mDatabase),
    settingsDao(*mDatabase),
    predictionDao(*mDatabase),
    refPTDao(*mDatabase)
{
    mDatabase->setDatabaseName(path);
    mDatabase->open();

    clearDatabase(); // DEV ONLY

    trackDao.init();
    raceDao.init();
    vehicleDao.init();
    ticketDao.init();
    observationDao.init();
    settingsDao.init();
    predictionDao.init();
    refPTDao.init();

    populateTables(); // DEV ONLY
}

DatabaseManager::~DatabaseManager()
{
    mDatabase->close();
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

void DatabaseManager::clearDatabase() // DEV ONLY
{
    QSqlQuery query(mDatabase->database());

    QStringList tables = mDatabase->tables();

    foreach (QString table, tables){
        if(table != "settings"){
            query.exec(QString("DROP TABLE %1").arg(table));
        }
    }

    qDebug("Cleared all database tables - DEV ONLY");
}

void DatabaseManager::populateTables() // DEV ONLY
{
    //Track *t1 = new Track;

    Track t1;

    t1.setName("Belle Rose");
    t1.setElevation(8);
    t1.setBearing(97);
    t1.setRadio(89.5);
    trackDao.addTrack(t1);

    Track t2;

    t2.setName("Baytown");
    t2.setElevation(30);
    t2.setBearing(360);
    t2.setRadio(87.9);
    trackDao.addTrack(t2);

    Track t3;

    t3.setName("Ennis");
    t3.setElevation(510);
    t3.setBearing(55);
    t3.setRadio(88.7);
    trackDao.addTrack(t3);

    Race r1;

    r1.setDate(QDate(2017,03,11));
    r1.setName("LODRS-4-1");
    r1.setTrackId(1);
    raceDao.addRace(r1);

    Race r2;

    r2.setDate(QDate(2017,04,27));
    r2.setName("LODRS-4-2");
    r2.setTrackId(2);
    raceDao.addRace(r2);

    Race r3;

    r3.setDate(QDate(2017,03,11));
    r3.setName("BBN");
    r3.setTrackId(1);
    raceDao.addRace(r3);

    Vehicle v1;

    v1.setNumber("4270");
    v1.setCompClass("ETMX");
    v1.setWeight(350);
    vehicleDao.addVehicle(v1);

    Vehicle v2;

    v2.setNumber("42");
    v2.setCompClass("ETMX");
    v2.setWeight(375);
    vehicleDao.addVehicle(v2);

    Ticket tk1;

    tk1.setVehicleId(1);
    tk1.setTrackId(1);
    tk1.setRaceId(1);
    tk1.setDate(QDate(2017,03,11));
    tk1.setTime(QTime(10, 25));
    tk1.setLane("right");
    tk1.setDial(8.80);
    tk1.setReaction(0.023);
    tk1.setSixty(1.337);
    tk1.setThreeThirty(3.532);
    tk1.setEighth(5.600);
    tk1.setEighthMPH(125.00);
    tk1.setEighthGood(true);
    tk1.setThousand(7.448);
    tk1.setQuarter(8.700);
    tk1.setQuarterMPH(150.00);
    tk1.setQuarterGood(true);
    tk1.setDelay(1.090);
    tk1.setVehicleWeight(350);
    tk1.setRiderWeight(150.0);
    tk1.setTemperature(80.0);
    tk1.setHumidity(50.0);
    tk1.setPressure(30.00);
    tk1.setVaporPressure(0.54);
    tk1.setDewPoint(60.1);
    tk1.setDensityAltitude(1000);
    tk1.setWindSpeed(0);
    tk1.setWindGust(0);
    tk1.setWindDirection(0);
    ticketDao.addTicket(tk1);

    Ticket tk2;

    tk2.setVehicleId(1);
    tk2.setTrackId(1);
    tk2.setRaceId(1);
    tk2.setDate(QDate(2017,03,11));
    tk2.setTime(QTime(11, 25));
    tk2.setLane("right");
    tk2.setDial(8.80);
    tk2.setReaction(0.023);
    tk2.setSixty(1.337);
    tk2.setThreeThirty(3.532);
    tk2.setEighth(5.700);
    tk2.setEighthMPH(125.00);
    tk2.setEighthGood(true);
    tk2.setThousand(7.448);
    tk2.setQuarter(8.900);
    tk2.setQuarterMPH(150.00);
    tk2.setQuarterGood(true);
    tk2.setDelay(1.090);
    tk2.setVehicleWeight(350);
    tk2.setRiderWeight(150.0);
    tk2.setTemperature(85.0);
    tk2.setHumidity(60.0);
    tk2.setPressure(29.00);
    tk2.setVaporPressure(0.54);
    tk2.setDewPoint(60.1);
    tk2.setDensityAltitude(2000);
    tk2.setWindSpeed(5);
    tk2.setWindGust(5);
    tk2.setWindDirection(0);
    ticketDao.addTicket(tk2);

    Ticket tk3;

    tk3.setVehicleId(1);
    tk3.setTrackId(2);
    tk3.setRaceId(2);
    tk3.setDate(QDate(2017,03,11));
    tk3.setTime(QTime(10, 25));
    tk3.setLane("right");
    tk3.setDial(8.80);
    tk3.setReaction(0.023);
    tk3.setSixty(1.337);
    tk3.setThreeThirty(3.532);
    tk3.setEighth(5.701);
    tk3.setEighthMPH(125.00);
    tk3.setEighthGood(true);
    tk3.setThousand(7.448);
    tk3.setQuarter(8.901);
    tk3.setQuarterMPH(150.00);
    tk3.setQuarterGood(true);
    tk3.setDelay(1.090);
    tk3.setVehicleWeight(350);
    tk3.setRiderWeight(150.0);
    tk3.setTemperature(90.1);
    tk3.setHumidity(70.1);
    tk3.setPressure(28.01);
    tk3.setVaporPressure(0.54);
    tk3.setDewPoint(60.1);
    tk3.setDensityAltitude(3001);
    tk3.setWindSpeed(5);
    tk3.setWindGust(5);
    tk3.setWindDirection(0);
    ticketDao.addTicket(tk3);

    Ticket tk4;

    tk4.setVehicleId(1);
    tk4.setTrackId(2);
    tk4.setRaceId(2);
    tk4.setDate(QDate(2017,03,11));
    tk4.setTime(QTime(10, 25));
    tk4.setLane("right");
    tk4.setDial(8.80);
    tk4.setReaction(0.023);
    tk4.setSixty(1.337);
    tk4.setThreeThirty(3.532);
    tk4.setEighth(5.600);
    tk4.setEighthMPH(125.00);
    tk4.setEighthGood(true);
    tk4.setThousand(7.448);
    tk4.setQuarter(8.700);
    tk4.setQuarterMPH(150.00);
    tk4.setQuarterGood(true);
    tk4.setDelay(1.090);
    tk4.setVehicleWeight(350);
    tk4.setRiderWeight(150.0);
    tk4.setTemperature(90.0);
    tk4.setHumidity(70.0);
    tk4.setPressure(28.00);
    tk4.setVaporPressure(0.54);
    tk4.setDewPoint(60.1);
    tk4.setDensityAltitude(3000);
    tk4.setWindSpeed(0);
    tk4.setWindGust(0);
    tk4.setWindDirection(0);
    ticketDao.addTicket(tk4);

    Ticket tk5;

    tk5.setVehicleId(1);
    tk5.setTrackId(1);
    tk5.setRaceId(3);
    tk5.setDate(QDate(2017,03,11));
    tk5.setTime(QTime(10, 25));
    tk5.setLane("right");
    tk5.setDial(8.80);
    tk5.setReaction(0.023);
    tk5.setSixty(1.337);
    tk5.setThreeThirty(3.532);
    tk5.setEighth(5.600);
    tk5.setEighthMPH(125.00);
    tk5.setEighthGood(true);
    tk5.setThousand(7.448);
    tk5.setQuarter(8.700);
    tk5.setQuarterMPH(150.00);
    tk5.setQuarterGood(true);
    tk5.setDelay(1.090);
    tk5.setVehicleWeight(350);
    tk5.setRiderWeight(150.0);
    tk5.setTemperature(80.0);
    tk5.setHumidity(50.0);
    tk5.setPressure(30.00);
    tk5.setVaporPressure(0.54);
    tk5.setDewPoint(60.1);
    tk5.setDensityAltitude(1000);
    tk5.setWindSpeed(10);
    tk5.setWindGust(10);
    tk5.setWindDirection(0);
    ticketDao.addTicket(tk5);

    Ticket tk6;

    tk6.setVehicleId(1);
    tk6.setTrackId(1);
    tk6.setRaceId(3);
    tk6.setDate(QDate(2017,03,11));
    tk6.setTime(QTime(11, 25));
    tk6.setLane("right");
    tk6.setDial(8.80);
    tk6.setReaction(0.023);
    tk6.setSixty(1.337);
    tk6.setThreeThirty(3.532);
    tk6.setEighth(5.700);
    tk6.setEighthMPH(125.00);
    tk6.setEighthGood(true);
    tk6.setThousand(7.448);
    tk6.setQuarter(8.900);
    tk6.setQuarterMPH(150.00);
    tk6.setQuarterGood(true);
    tk6.setDelay(1.090);
    tk6.setVehicleWeight(350);
    tk6.setRiderWeight(150.0);
    tk6.setTemperature(85.0);
    tk6.setHumidity(60.0);
    tk6.setPressure(29.00);
    tk6.setVaporPressure(0.54);
    tk6.setDewPoint(60.1);
    tk6.setDensityAltitude(2000);
    tk6.setWindSpeed(10);
    tk6.setWindGust(10);
    tk6.setWindDirection(0);
    ticketDao.addTicket(tk6);

    Ticket tk7;

    tk7.setVehicleId(1);
    tk7.setTrackId(1);
    tk7.setRaceId(3);
    tk7.setDate(QDate(2017,03,11));
    tk7.setTime(QTime(10, 25));
    tk7.setLane("right");
    tk7.setDial(8.80);
    tk7.setReaction(0.023);
    tk7.setSixty(1.337);
    tk7.setThreeThirty(3.532);
    tk7.setEighth(5.600);
    tk7.setEighthMPH(125.00);
    tk7.setEighthGood(true);
    tk7.setThousand(7.448);
    tk7.setQuarter(8.700);
    tk7.setQuarterMPH(150.00);
    tk7.setQuarterGood(true);
    tk7.setDelay(1.090);
    tk7.setVehicleWeight(350);
    tk7.setRiderWeight(150.0);
    tk7.setTemperature(80.0);
    tk7.setHumidity(50.0);
    tk7.setPressure(30.00);
    tk7.setVaporPressure(0.54);
    tk7.setDewPoint(60.1);
    tk7.setDensityAltitude(1000);
    tk7.setWindSpeed(10);
    tk7.setWindGust(10);
    tk7.setWindDirection(0);
    ticketDao.addTicket(tk7);

    Ticket tk8;

    tk8.setVehicleId(1);
    tk8.setTrackId(1);
    tk8.setRaceId(3);
    tk8.setDate(QDate(2017,03,11));
    tk8.setTime(QTime(10, 25));
    tk8.setLane("right");
    tk8.setDial(8.80);
    tk8.setReaction(0.023);
    tk8.setSixty(1.337);
    tk8.setThreeThirty(3.532);
    tk8.setEighth(5.600);
    tk8.setEighthMPH(125.00);
    tk8.setEighthGood(true);
    tk8.setThousand(7.448);
    tk8.setQuarter(8.700);
    tk8.setQuarterMPH(150.00);
    tk8.setQuarterGood(true);
    tk8.setDelay(1.090);
    tk8.setVehicleWeight(350);
    tk8.setRiderWeight(150.0);
    tk8.setTemperature(80.0);
    tk8.setHumidity(50.0);
    tk8.setPressure(30.00);
    tk8.setVaporPressure(0.54);
    tk8.setDewPoint(60.1);
    tk8.setDensityAltitude(1000);
    tk8.setWindSpeed(10);
    tk8.setWindGust(10);
    tk8.setWindDirection(0);
    ticketDao.addTicket(tk8);

    Observation o1;

    o1.setDate(QDate(2017,03,11));
    o1.setTime(QTime(12, 25));
    o1.setTemperature(90.0);
    o1.setHumidity(70.0);
    o1.setPressure(28.00);
    o1.setVaporPressure(0.54);
    o1.setDewPoint(60.1);
    o1.setDensityAltitude(3000);
    o1.setWindSpeed(10);
    o1.setWindGust(10);
    o1.setWindDirection(0);
    observationDao.addObservation(o1);

    Observation o2;

    o2.setDate(QDate(2017,03,11));
    o2.setTime(QTime(10, 25));
    o2.setTemperature(80.0);
    o2.setHumidity(50.0);
    o2.setPressure(30.00);
    o2.setVaporPressure(0.54);
    o2.setDewPoint(60.1);
    o2.setDensityAltitude(10000);
    o2.setWindSpeed(10);
    o2.setWindGust(10);
    o2.setWindDirection(0);
    observationDao.addObservation(o2);

    qDebug("tables populated - DEV ONLY");
}
