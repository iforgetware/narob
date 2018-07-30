#include "tickets.h"

Fields ticketFields()
{
    Fields f;

    f.append(Field("id", "id", 0, 0));

    f.append(Field("vehicleId", "Vehicle", 150, 0));
    f.append(Field("trackId", "Track", 150, 0));
    f.append(Field("raceId", "Race", 150, 0));
    f.append(Field("predictionId", "Prediction", 0, 0));

    f.append(Field("dateTime", "Date       Time", 160, -3));

    f.append(Field("lane", "Lane", 50, 0));
    f.append(Field("delay", "Delay", 50, 3));
    f.append(Field("reaction", "R/T", 60, 3));
    f.append(Field("sixty", "60'", 50, 3));
    f.append(Field("threeThirty", "330'", 50, 3));
    f.append(Field("eighth", "1/8", 50, 3));
    f.append(Field("eighthMPH", "1/8 MPH", 75, 2));
    f.append(Field("eighthGood", "Use 1/8", 70, -1));
    f.append(Field("thousand", "1000'", 50, 3));
    f.append(Field("quarter", "1/4", 60, 3));
    f.append(Field("quarterMPH", "1/4 MPH", 75, 2));
    f.append(Field("quarterGood", "Use 1/4", 70, -1));

    f.append(Field("dial", "Dial", 50, 2));
    f.append(Field("vehicleWeight", "V Weight", 70, 0));
    f.append(Field("riderWeight", "R Weight", 70, 1));

    f.append(Field("temperature", "Temp", 50, 1));
    f.append(Field("humidity", "Humid",50, 1));
    f.append(Field("pressure", "Pres", 50, 2));
    f.append(Field("vaporPressure", "V Pres", 50, 2));
    f.append(Field("dewPoint", "D Point", 60, 1));
    f.append(Field("densityAltitude", "D Alt", 50, 0));
    f.append(Field("windSpeed", "W Speed", 70, 0));
    f.append(Field("windGust", "W Gust", 70, 0));
    f.append(Field("windDirection", "W Dir", 60, 0));

    f.append(Field("notes", "Notes", 0, 0));

    f.append(Field("pm5Id", "pm5Id", 0, 0));
    f.append(Field("pm4Id", "pm4Id", 0, 0));
    f.append(Field("pm3Id", "pm3Id", 0, 0));
    f.append(Field("pm2Id", "pm2Id", 0, 0));
    f.append(Field("pm1Id", "pm1Id", 0, 0));
    f.append(Field("p0Id" , "p0Id" , 0, 0));
    f.append(Field("pp1Id", "pp1Id", 0, 0));
    f.append(Field("pp2Id", "pp2Id", 0, 0));
    f.append(Field("pp3Id", "pp3Id", 0, 0));
    f.append(Field("pp4Id", "pp4Id", 0, 0));
    f.append(Field("pp5Id", "pp5Id", 0, 0));

    return f;
}

Tickets::Tickets() :
    DbTableBase()
{
    mFields = ticketFields();
    mTable = "tickets";
}


Ticket::Ticket() :
    DbRecordBase()
{
    mFields = ticketFields();
    init("tickets");
}


TicketsModel::TicketsModel(Vehicle *vehicle,
                           QObject *parent) :
    ModelBase("tickets",
              ticketFields(),
              parent),
    mVehicle(vehicle)
{
    QString filter = QString("vehicleId = %1").arg(mVehicle->value("id").toInt());

    setFilter(filter);

    setSort(fieldIndex("dateTime"), Qt::DescendingOrder);

    select();
}

QVector<Ticket*> TicketsModel::tickets()
{
    QVector<Ticket*> ticketsVector;

    for(int row = 0; row < rowCount(); row++){
        Ticket *ticket = new Ticket();
        ticket->populate(record(row));
        ticketsVector.append(ticket);
    }

    return ticketsVector;
}

double TicketsModel::lastWeight()
{
    double riderWeight = 0;
    Ticket *ticket = new Ticket();

    if(rowCount()){
        ticket->populate(record(rowCount() - 1));
        riderWeight = ticket->value("riderWeight").toDouble();
    }

    return riderWeight;
}


TicketsRaceModel::TicketsRaceModel(int raceId, QObject *parent) :
    QSortFilterProxyModel(parent),
    mRaceId(raceId)
{
}

bool TicketsRaceModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QModelIndex raceIndex = sourceModel()->index(sourceRow, 3, sourceParent);

    return sourceModel()->data(raceIndex).toInt() == mRaceId;
}


TicketsTrackModel::TicketsTrackModel(int trackId, QObject *parent) :
    QSortFilterProxyModel(parent),
    mTrackId(trackId)
{
}

bool TicketsTrackModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QModelIndex trackIndex = sourceModel()->index(sourceRow, 2, sourceParent);

    return sourceModel()->data(trackIndex).toInt() == mTrackId;
}
