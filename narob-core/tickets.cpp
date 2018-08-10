#include "tickets.h"

#include <QtGui/QColor>

Fields ticketFields()
{
    Fields f;

    f << Field("id", "id", 0, 0)

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

QVariant TicketsModel::data(const QModelIndex &item, int role) const
{
    if(role == Qt::ForegroundRole){

        if(item.column() == fieldIndex("sixty") ||
           item.column() == fieldIndex("threeThirty") ||
           item.column() == fieldIndex("eighth") ||
           item.column() == fieldIndex("thousand") ||
           item.column() == fieldIndex("quarter")){

            if(item.data().toDouble() < 0){
                return QVariant(QColor(Qt::gray));
            }
        }
    }

    return QSqlRelationalTableModel::data(item, role);
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
