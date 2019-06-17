#include "tickets.h"

#include <QColor>
#include <QSqlQuery>
#include <QDebug>

using namespace std;

Tickets::Tickets() :
    DbTableBase("tickets",
                TICKET_FIELDS)
{
}


Ticket::Ticket() :
    DbRecordBase("tickets",
                 TICKET_FIELDS)
{
}

TicketsModel::TicketsModel(int vehicleId,
                           QObject *parent) :
    ModelBase("tickets",
              TICKET_FIELDS,
              parent),
    mVehicleId(vehicleId)
{
    QString filter = QString("vehicleId = %1").arg(mVehicleId);

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

unique_ptr<vector<shared_ptr<Ticket>>> TicketsModel::predictionTickets(
        bool allForTrack,
        bool allForVehicle,
        int trackId,
        int raceId,
        int ticketId)
{
    auto ticketsVector = make_unique<vector<shared_ptr<Ticket>>>();

    bool valid;

    for(int row = 0; row < rowCount(); row++){
        valid = true;

        if(!allForVehicle){
            valid = record(row).value("trackId").toInt() == trackId;

            if(!allForTrack){
                valid = record(row).value("raceId").toInt() == raceId;
            }
        }

        if(valid && ticketId){
            valid = (record(row).value("id").toInt() != ticketId);
        }

        if(valid){
            auto ticket = make_unique<Ticket>();
            ticket->populate(record(row));
            ticketsVector->push_back(move(ticket));
        }
    }

    return ticketsVector;
}

double TicketsModel::lastWeight()
{
    double riderWeight = 0;

    if(rowCount()){
        riderWeight = record(0).value("riderWeight").toDouble();
    }

    return riderWeight;
}

int TicketsModel::ticketsSinceDateTime(const QDateTime dateTime) const
{
    if(dateTime.isValid()){
        QSqlQuery query;

        query.prepare("SELECT * FROM tickets "
                      "WHERE vehicleId = :vehicleId "
                      "AND dateTime >= :dateTime");
        query.bindValue(":vehicleId", mVehicleId);
        query.bindValue(":dateTime", dateTime.toString(Qt::ISODate));

        query.exec();
        query.last();

        return query.at() + 1;
    }else{
        return 0;
    }
}


TicketsRaceModel::TicketsRaceModel(int raceId, QObject *parent) :
    QSortFilterProxyModel(parent),
    mRaceId(raceId)
{
}

bool TicketsRaceModel::filterAcceptsRow(int sourceRow,
                                        const QModelIndex &sourceParent) const
{
    QModelIndex raceIndex = sourceModel()->index(sourceRow, 3, sourceParent);

    return sourceModel()->data(raceIndex).toInt() == mRaceId;
}


TicketsTrackModel::TicketsTrackModel(int trackId, QObject *parent) :
    QSortFilterProxyModel(parent),
    mTrackId(trackId)
{
}

bool TicketsTrackModel::filterAcceptsRow(int sourceRow,
                                         const QModelIndex &sourceParent) const
{
    QModelIndex trackIndex = sourceModel()->index(sourceRow, 2, sourceParent);

    return sourceModel()->data(trackIndex).toInt() == mTrackId;
}
