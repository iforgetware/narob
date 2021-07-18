#ifndef TICKETS_H
#define TICKETS_H

#include <memory>

#include <QVector>
#include <QDateTime>
#include <QSortFilterProxyModel>

#include "dbtablebase.h"
#include "dbrecordbase.h"
#include "modelbase.h"
#include "vehicles.h"

#include "narob-core_global.h"

const Fields TICKET_FIELDS{
            Field("id", "id", 0, 0),
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

            Field("splitMPH", "MPH Split", 75, 2),
            Field("splitST", "60-330", 50, 3),
            Field("splitTE", "330-660", 55, 3),
            Field("splitET", "660-1000", 60, 3),
            Field("splitTQ", "1000-1320", 65, 3),

            Field("dial", "Dial", 50, 2),
            Field("vehicleWeight", "V Weight", 70, 0),
            Field("riderWeight", "R Weight", 70, 1),

            Field("densityAltitude", "D Alt", 50, 0),
            Field("temperature", "Temp", 50, 1),
            Field("humidity", "Humid",50, 1),
            Field("pressure", "Pres", 50, 2),
            Field("vaporPressure", "V Pres", 50, 2),
            Field("dewPoint", "D Point", 60, 1),
            Field("windSpeed", "W Speed", 70, 0),
            Field("windDirection", "W Dir", 60, 0),
            Field("windGust", "W Gust", 70, 0),
            Field("windGustDirection", "G Dir", 60, 0),

            Field("densityAltitudeM", "D Alt M", 50, 0),
            Field("temperatureM", "Temp M", 50, 1),
            Field("humidityM", "Humid M",50, 1),
            Field("pressureM", "Pres M", 50, 2),
            Field("windSpeedM", "W Sp M", 70, 0),
            Field("windDirectionM", "W D M", 60, 0),

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
    explicit TicketsModel(QObject *parent = nullptr);
    QVariant data(const QModelIndex &item, int role) const;

};

class NAROBCORESHARED_EXPORT TicketsLogbookModel : public TicketsModel
{
    Q_OBJECT

public:
    explicit TicketsLogbookModel(int vehicleId,
                          QObject *parent = nullptr);
    std::unique_ptr<std::vector<std::shared_ptr<Ticket>>>predictionTickets(
            bool allForTrack,
            bool allForVehicle,
            int trackId,
            int raceId,
            int ticketId);

    double lastWeight();
    int ticketsSinceDateTime(const QDateTime dateTime) const;

    int mVehicleId;
};

class NAROBCORESHARED_EXPORT TicketsTrackModel : public TicketsModel
{
    Q_OBJECT

public:
    explicit TicketsTrackModel(int vehicleId,
                              int trackId,
                              QObject* parent = nullptr);

private:
    int mVehicleId;
    int mTrackId;
};

class NAROBCORESHARED_EXPORT TicketsRaceModel : public TicketsModel
{
    Q_OBJECT

public:
    explicit TicketsRaceModel(int vehicleId,
                              int raceId,
                              QObject* parent = nullptr);

private:
    int mVehicleId;
    int mRaceId;
};

#endif // TICKETS_H
