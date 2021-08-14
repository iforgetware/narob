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

double Ticket::temperature()
{
    double t = value("temperatureM").toDouble();

    if(t != 0.0){
        qDebug("temperature overide");
        return t;
    }else{
        return value("temperature").toDouble();
    }
}

double Ticket::humidity()
{
    double h = value("humidityM").toDouble();

    if(h != 0.0){
        return h;
    }else{
        return value("humidity").toDouble();
    }
}

double Ticket::pressure()
{
    double p = value("pressureM").toDouble();

    if(p != 0.0){
        return p;
    }else{
        return value("pressure").toDouble();
    }
}

int Ticket::windSpeed()
{
    int wS = value("windSpeedM").toInt();

    if(wS != 0){
        return wS;
    }else{
        return value("windSpeed").toInt();
    }
}

int Ticket::windDirection()
{
    int wD = value("windDirectionM").toInt();

    if(wD != 0){
        return wD;
    }else{
        return value("windDirection").toInt();
    }
}

TicketsModel::TicketsModel(QObject *parent) :
    ModelBase("tickets",
              TICKET_FIELDS,
              parent)
{
    setSort(fieldIndex("dateTime"), Qt::DescendingOrder);
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

TicketsLogbookModel::TicketsLogbookModel(int vehicleId,
                           QObject *parent) :
    TicketsModel(parent),
    mVehicleId(vehicleId)
{
    QString filter = QString("vehicleId = %1").arg(mVehicleId);

    setFilter(filter);

    select();
}

TicketsTrackModel::TicketsTrackModel(int vehicleId,
                                     int trackId,
                                     QObject *parent) :
    TicketsModel(parent),
    mVehicleId(vehicleId),
    mTrackId(trackId)
{
    QString filter = QString("vehicleId = %1 AND trackId = %2")
                     .arg(mVehicleId)
                     .arg(mTrackId);

    setFilter(filter);

    select();
}

TicketsRaceModel::TicketsRaceModel(int vehicleId,
                                   int raceId,
                                   QObject *parent) :
    TicketsModel(parent),
    mVehicleId(vehicleId),
    mRaceId(raceId)
{
    QString filter = QString("vehicleId = %1 AND raceId = %2")
                     .arg(mVehicleId)
                     .arg(mRaceId);

    setFilter(filter);

    select();
}

unique_ptr<vector<shared_ptr<Ticket>>> TicketsLogbookModel::predictionTickets(
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

double TicketsLogbookModel::lastWeight()
{
    double riderWeight = 0;

    if(rowCount()){
        riderWeight = record(0).value("riderWeight").toDouble();
    }

    return riderWeight;
}

int TicketsLogbookModel::ticketsSinceDateTime(const QDateTime dateTime) const
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


//TicketsRaceModel::TicketsRaceModel(int raceId, QObject *parent) :
//    QSortFilterProxyModel(parent),
//    mRaceId(raceId)
//{
//}

//bool TicketsRaceModel::filterAcceptsRow(int sourceRow,
//                                        const QModelIndex &sourceParent) const
//{
//    QModelIndex raceIndex = sourceModel()->index(sourceRow, 3, sourceParent);

//    return sourceModel()->data(raceIndex).toInt() == mRaceId;
//}


//TicketsTrackModel::TicketsTrackModel(int trackId, QObject *parent) :
//    QSortFilterProxyModel(parent),
//    mTrackId(trackId)
//{
//}

//bool TicketsTrackModel::filterAcceptsRow(int sourceRow,
//                                         const QModelIndex &sourceParent) const
//{
//    QModelIndex trackIndex = sourceModel()->index(sourceRow, 2, sourceParent);

//    return sourceModel()->data(trackIndex).toInt() == mTrackId;
//}
