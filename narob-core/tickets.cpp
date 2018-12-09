#include "tickets.h"

#include <QColor>
#include <QDebug>

Tickets::Tickets() :
    DbTableBase("tickets",
                TICKET_FIELDS)
{
}


Ticket::Ticket() :
    DbRecordBase("tickets",
                 TICKET_FIELDS)
{
    init();
}

TicketsModel::TicketsModel(Vehicle *vehicle,
                           QObject *parent) :
    ModelBase("tickets",
              TICKET_FIELDS,
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

            if(item.data().toDouble() <= 0){
                return QVariant(QColor(Qt::gray));
            }
        }
    }

    return QSqlRelationalTableModel::data(item, role);
}

QVector<Ticket*> TicketsModel::allTickets()
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
        ticket->populate(record(0));
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
