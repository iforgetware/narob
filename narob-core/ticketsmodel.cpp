#include "ticketsmodel.h"
#include <QDebug>

TicketsModel::TicketsModel(Vehicle* vehicle, QObject* parent) :
    ModelBase(parent),
    mDb(DatabaseManager::instance()),
    mVehicle(vehicle),
    mTickets(mDb.ticketDao.ticketsForVehicle(mVehicle->id()))
{
    setTable("tickets");

    QString filter = QString("vehicleId = %1").arg(mVehicle->id());

    setFilter(filter);

    mFields.append(Field("trackId", "Track", 150, 0));
    mFields.append(Field("raceId", "Race", 150, 0));
    mFields.append(Field("dateTime", "Date       Time", 160, -3));
    mFields.append(Field("lane", "Lane", 50, 0));
    mFields.append(Field("delay", "Delay", 50, 3));
    mFields.append(Field("reaction", "R/T", 50, 3));
    mFields.append(Field("sixty", "60'", 50, 3));
    mFields.append(Field("threeThirty", "330'", 50, 3));
    mFields.append(Field("eighth", "1/8", 50, 3));
    mFields.append(Field("eighthMPH", "1/8 MPH", 75, 2));
    mFields.append(Field("eighthGood", "Use 1/8", 70, -1));
    mFields.append(Field("thousand", "1000'", 50, 3));
    mFields.append(Field("dial", "Dial", 50, 2));
    mFields.append(Field("quarter", "1/4", 50, 3));
    mFields.append(Field("quarterMPH", "1/4 MPH", 75, 2));
    mFields.append(Field("quarterGood", "Use 1/4", 70, -1));
    mFields.append(Field("vehicleWeight", "V Weight", 70, 0));
    mFields.append(Field("riderWeight", "R Weight", 70, 1));
    mFields.append(Field("temperature", "Temp", 50, 1));
    mFields.append(Field("humidity", "Humid",50, 1));
    mFields.append(Field("pressure", "Pres", 50, 2));
    mFields.append(Field("vaporPressure", "V Pres", 50, 2));
    mFields.append(Field("dewPoint", "D Point", 60, 1));
    mFields.append(Field("densityAltitude", "D Alt", 50, 0));
    mFields.append(Field("windSpeed", "W Speed", 70, 0));
    mFields.append(Field("windGust", "W Gust", 70, 0));
    mFields.append(Field("windDirection", "W Dir", 60, 0));

    setHeaders();

    select();
}

QModelIndex TicketsModel::addTicket(const Ticket &ticket)
{
    int rowIndex = rowCount();

    beginInsertRows(QModelIndex(), rowIndex, rowIndex);
    Ticket* newTicket = new Ticket(ticket);

    mDb.ticketDao.addTicket(*newTicket);
    mTickets.append(newTicket);
    endInsertRows();

    return index(rowIndex, 0);
}

//void TicketsModel::getWeather(Ticket *ticket)
//{
//    Observation* observation = new Observation();

//    observation = mDb.observationDao.observationForTime(ticket->date(), ticket->time());

//    if(observation){
//        ticket->setTemperature(observation->temperature());
//        ticket->setHumidity(observation->humidity());
//        ticket->setPressure(observation->pressure());
//        ticket->setVaporPressure(observation->vaporPressure());
//        ticket->setDewPoint(observation->dewPoint());
//        ticket->setDensityAltitude(observation->densityAltitude());
//        ticket->setWindSpeed(observation->windSpeed());
//        ticket->setWindGust(observation->windGust());
//        ticket->setWindDirection(observation->windDirection());
//    }else{
//        qDebug("Weather not found - WRITE CODE");
//    }

//    delete observation;

//    return;
//}

int TicketsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return mTickets.size();
}

bool TicketsModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (row < 0
            || row >= rowCount()
            || count < 0
            || (row + count) > rowCount()) {
        return false;
    }
    beginRemoveRows(parent, row, row + count - 1);
    int countLeft = count;
    while (countLeft--) {
        const Ticket& ticket = *mTickets.at(row + countLeft);
        mDb.ticketDao.removeTicket(ticket.id());
    }
    mTickets.erase(mTickets.begin() + row,
                  mTickets.begin() + row + count);
    endRemoveRows();
    return true;
}
