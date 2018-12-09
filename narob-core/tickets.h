#ifndef TICKETS_H
#define TICKETS_H

#include <QVector>
#include <QSortFilterProxyModel>

#include "dbtablebase.h"
#include "dbrecordbase.h"
#include "modelbase.h"
#include "vehicles.h"

#include "narob-core_global.h"

static Fields TICKET_FIELDS{Field("id", "id", 0, 0),

            Field("vehicleId", "Vehicle", 150, 0),
            Field("trackId", "Track", 150, 0),
            Field("raceId", "Race", 150, 0),

            Field("dateTime", "Date       Time", 160, -3),

            Field("lane", "Lane", 50, 0),
            Field("delay", "Delay", 50, 3),
            Field("reaction", "R/T", 60, 3),
            Field("sixty", "60'", 50, 13),
            Field("threeThirty", "330'", 50, 13),
            Field("eighth", "1/8", 50, 13),
            Field("eighthMPH", "1/8 MPH", 75, 2),
            Field("thousand", "1000'", 50, 13),
            Field("quarter", "1/4", 60, 13),
            Field("quarterMPH", "1/4 MPH", 75, 2),

            Field("dial", "Dial", 50, 2),
            Field("vehicleWeight", "V Weight", 70, 0),
            Field("riderWeight", "R Weight", 70, 1),

            Field("temperature", "Temp", 50, 1),
            Field("humidity", "Humid",50, 1),
            Field("pressure", "Pres", 50, 2),
            Field("vaporPressure", "V Pres", 50, 2),
            Field("dewPoint", "D Point", 60, 1),
            Field("densityAltitude", "D Alt", 50, 0),
            Field("windSpeed", "W Speed", 70, 0),
            Field("windGust", "W Gust", 70, 0),
            Field("windDirection", "W Dir", 60, 0),

            Field("notes", "Notes", 0, 0)};


class Tickets : public DbTableBase
{
public:
    explicit Tickets();
};


class NAROBCORESHARED_EXPORT Ticket : public DbRecordBase
{
public:
    explicit Ticket();
};


class NAROBCORESHARED_EXPORT TicketsModel : public ModelBase
{
    Q_OBJECT

public:
    explicit TicketsModel(Vehicle *vehicle,
                          QObject *parent = nullptr);
    QVariant data(const QModelIndex &item, int role) const;

    QVector<Ticket*> allTickets();
    double lastWeight();

private:
    Vehicle *mVehicle;
};


class NAROBCORESHARED_EXPORT TicketsRaceModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    TicketsRaceModel(int raceId, QObject* parent);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const;

private:
    int mRaceId;
};


class NAROBCORESHARED_EXPORT TicketsTrackModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    TicketsTrackModel(int trackId, QObject* parent);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const;

private:
    int mTrackId;
};

#endif // TICKETS_H
