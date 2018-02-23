#include "ticketdao.h"

#include <QSqlQuery>
#include <QVariant>

#include <QDebug>

#include "databasemanager.h"

TicketDao::TicketDao(QSqlDatabase &database) :
    mDatabase(database)
{
}

void TicketDao::init() const
{
    if(!mDatabase.tables().contains("tickets")){
        QSqlQuery query(mDatabase);
        query.exec("CREATE TABLE tickets ("
                   "id INTEGER PRIMARY KEY,"

                   "vehicleId INTEGER,"
                   "trackId INTEGER,"
                   "raceId INTEGER,"
                   "predictionId INTEGER,"

                   "date TEXT,"
                   "time TEXT,"

                   "lane TEXT,"
                   "delay REAL,"
                   "reaction REAL,"
                   "sixty REAL,"
                   "threeThirty REAL,"
                   "eighth REAL,"
                   "eighthMPH REAL,"
                   "eighthGood INT,"
                   "thousand REAL,"
                   "dial REAL,"
                   "quarter REAL,"
                   "quarterMPH REAL,"
                   "quarterGood INT,"

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
                   "windDirection INTEGER)");
        DatabaseManager::debugQuery(query);
    }
}

void TicketDao::addTicket(Ticket &ticket) const
{
    QSqlQuery query(mDatabase);

    query.prepare("INSERT INTO tickets ("
                  "vehicleId,"
                  "trackId,"
                  "raceId,"
                  "predictionId,"

                  "date,"
                  "time,"

                  "lane,"
                  "delay,"
                  "reaction,"
                  "sixty,"
                  "threeThirty,"
                  "eighth,"
                  "eighthMPH,"
                  "eighthGood,"
                  "thousand,"
                  "dial,"
                  "quarter,"
                  "quarterMPH,"
                  "quarterGood,"

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
                  "windDirection"

                  ") VALUES ("

                  ":vehicleId,"
                  ":trackId,"
                  ":raceId,"
                  ":predictionId,"

                  ":date,"
                  ":time,"

                  ":lane,"
                  ":delay,"
                  ":reaction,"
                  ":sixty,"
                  ":threeThirty,"
                  ":eighth,"
                  ":eighthMPH,"
                  ":eighthGood,"
                  ":thousand,"
                  ":dial,"
                  ":quarter,"
                  ":quarterMPH,"
                  ":quarterGood,"

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
                  ":windDirection"
                  ")");

    query.bindValue(":vehicleId", ticket.vehicleId());
    query.bindValue(":trackId", ticket.trackId());
    query.bindValue(":raceId", ticket.raceId());
    query.bindValue(":predictionId", ticket.predictionId());

    query.bindValue(":date", ticket.date());
    query.bindValue(":time", ticket.time());

    query.bindValue(":lane", ticket.lane());
    query.bindValue(":delay", ticket.delay());
    query.bindValue(":reaction", ticket.reaction());
    query.bindValue(":sixty", ticket.sixty());
    query.bindValue(":threeThirty", ticket.threeThirty());
    query.bindValue(":eighth", ticket.eighth());
    query.bindValue(":eighthMPH", ticket.eighthMPH());
    query.bindValue(":eighthGood", ticket.eighthGood());
    query.bindValue(":thousand", ticket.thousand());
    query.bindValue(":dial", ticket.dial());
    query.bindValue(":quarter", ticket.quarter());
    query.bindValue(":quarterMPH", ticket.quarterMPH());
    query.bindValue(":quarterGood", ticket.quarterGood());

    query.bindValue(":vehicleWeight", ticket.vehicleWeight());
    query.bindValue(":riderWeight", ticket.riderWeight());

    query.bindValue(":temperature", ticket.temperature());
    query.bindValue(":humidity", ticket.humidity());
    query.bindValue(":pressure", ticket.pressure());
    query.bindValue(":vaporPressure", ticket.vaporPressure());
    query.bindValue(":dewPoint", ticket.dewPoint());
    query.bindValue(":densityAltitude", ticket.densityAltitude());
    query.bindValue(":windSpeed", ticket.windSpeed());
    query.bindValue(":windGust", ticket.windGust());
    query.bindValue(":windDirection", ticket.windDirection());

    query.exec();

    DatabaseManager::debugQuery(query);

    ticket.setId(query.lastInsertId().toInt());
}

void TicketDao::removeTicket(int id) const
{
    QSqlQuery query(mDatabase);

    query.prepare("DELETE from tickets WHERE id=:id");

    query.bindValue(":id", id);

    query.exec();

    DatabaseManager::debugQuery(query);
}




// maybe make this all tickets and only filter in model
// have seperate models for each tab, update with signals if needed
// can add filter to prediction tab's foreach
// will not cost much





QVector<Ticket*> TicketDao::ticketsForVehicle(int vehicleId) const
{
    QSqlQuery query(mDatabase);

    query.prepare("SELECT * FROM tickets WHERE vehicleId = :vehicleId");
    query.bindValue(":vehicleId", vehicleId);

    query.exec();

    QVector<Ticket*> list;

    while(query.next()) {
        Ticket* ticket = new Ticket();

        ticket->setId(query.value("id").toInt());

        ticket->setVehicleId(query.value("vehicleId").toInt());
        ticket->setTrackId(query.value("trackId").toInt());
        ticket->setRaceId(query.value("raceId").toInt());
        ticket->setPredictionId(query.value("predictionId").toInt());

        ticket->setDate(query.value("date").toDate());
        ticket->setTime(query.value("time").toTime());

        ticket->setLane(query.value("lane").toString());
        ticket->setDelay(query.value("delay").toDouble());
        ticket->setReaction(query.value("reaction").toDouble());
        ticket->setSixty(query.value("sixty").toDouble());
        ticket->setThreeThirty(query.value("threeThirty").toDouble());
        ticket->setEighth(query.value("eighth").toDouble());
        ticket->setEighthMPH(query.value("eighthMPH").toDouble());
        ticket->setEighthGood(query.value("eighthGood").toBool());
        ticket->setThousand(query.value("thousand").toDouble());
        ticket->setDial(query.value("dial").toDouble());
        ticket->setQuarter(query.value("quarter").toDouble());
        ticket->setQuarterMPH(query.value("quarterMPH").toDouble());
        ticket->setQuarterGood(query.value("quarterGood").toBool());

        ticket->setVehicleWeight(query.value("vehicleWeight").toInt());
        ticket->setRiderWeight(query.value("riderWeight").toDouble());

        ticket->setTemperature(query.value("temperature").toDouble());
        ticket->setHumidity(query.value("humidity").toDouble());
        ticket->setPressure(query.value("pressure").toDouble());
        ticket->setVaporPressure(query.value("vaporPressure").toDouble());
        ticket->setDewPoint(query.value("dewPoint").toDouble());
        ticket->setDensityAltitude(query.value("densityAltitude").toInt());
        ticket->setWindSpeed(query.value("windSpeed").toInt());
        ticket->setWindGust(query.value("windGust").toInt());
        ticket->setWindDirection(query.value("windDirection").toInt());

        list.append(ticket);
    }

    return list;
}
