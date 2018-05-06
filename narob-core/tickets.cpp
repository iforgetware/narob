#include "tickets.h"

Fields setTicketFields()
{
    Fields retFields;

    retFields.append(Field("id", "id", 0, 0));

    retFields.append(Field("vehicleId", "Vehicle", 150, 0));
    retFields.append(Field("trackId", "Track", 150, 0));
    retFields.append(Field("raceId", "Race", 150, 0));
    retFields.append(Field("predictionId", "Prediction", 0, 0));

    retFields.append(Field("dateTime", "Date       Time", 160, -3));

    retFields.append(Field("lane", "Lane", 50, 0));
    retFields.append(Field("delay", "Delay", 50, 3));
    retFields.append(Field("reaction", "R/T", 60, 3));
    retFields.append(Field("sixty", "60'", 50, 3));
    retFields.append(Field("threeThirty", "330'", 50, 3));
    retFields.append(Field("eighth", "1/8", 50, 3));
    retFields.append(Field("eighthMPH", "1/8 MPH", 75, 2));
    retFields.append(Field("eighthGood", "Use 1/8", 70, -1));
    retFields.append(Field("thousand", "1000'", 50, 3));
    retFields.append(Field("quarter", "1/4", 50, 3));
    retFields.append(Field("quarterMPH", "1/4 MPH", 75, 2));
    retFields.append(Field("quarterGood", "Use 1/4", 70, -1));

    retFields.append(Field("dial", "Dial", 50, 2));
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

    retFields.append(Field("notes", "Notes", 0, 0));

    return retFields;
}

Fields ticketFields = setTicketFields();

Tickets::Tickets() :
    DbTableBase()
{
    mFields = ticketFields;
    mTable = "tickets";
}


Ticket::Ticket() :
    DbRecordBase()
{
    mFields = ticketFields;
    init("tickets");
}

TicketsModel::TicketsModel(Vehicle *vehicle,
                           QObject *parent) :
    ModelBase(parent),
    mVehicle(vehicle)
{
    setTable("tickets");

    QString filter = QString("vehicleId = %1").arg(mVehicle->value("id").toInt());

    setFilter(filter);

    mFields = ticketFields;

    setHeaders();

    setSort(fieldIndex("dateTime"), Qt::AscendingOrder);

    select();
}

QVector<Ticket*> TicketsModel::tickets()
{
    QVector<Ticket*> ticketsVector;
    QSqlRecord rec;

    for(int row = 0; row < rowCount(); row++){
        rec = record(row);
        Ticket *ticket = new Ticket();

        foreach(Field field, mFields){
            ticket->setValue(field.mColumn, rec.value(field.mColumn));
        }

        ticketsVector.append(ticket);
    }

    return ticketsVector;
}
