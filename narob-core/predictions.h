#ifndef PREDICTIONS_H
#define PREDICTIONS_H

#include "dbtablebase.h"
#include "dbrecordbase.h"
#include "modelbase.h"

#include "tickets.h"
#include "vehicles.h"
#include "races.h"

#include "narob-core_global.h"

static Fields PREDICTION_FIELDS{Field("id", "id", 0, 0),

            Field("vehicleId", "Vehicle", 150, 0),
            Field("raceId", "Race", 150, 0),
            Field("ticketId", "Ticket", 150, 0),

            Field("dateTime", "Date       Time", 160, -3),

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

            Field("windAdjustment", "Wd A", 50, 3),
            Field("weightAdjustment", "Wt A", 50, 3),
            Field("allForVehicle", "AFV", 50, -1),
            Field("allForTrack", "AFT", 50, -1),

            Field("sixtyD", "60'", 50, 3),
            Field("threeThirtyD", "330'", 50, 3),
            Field("eighthD", "1/8", 50, 3),
            Field("thousandD", "1000'", 50, 3),
            Field("quarterD", "1/4", 60, 3),

            Field("sixtyA", "60'", 50, 3),
            Field("threeThirtyA", "330'", 50, 3),
            Field("eighthA", "1/8", 50, 3),
            Field("thousandA", "1000'", 50, 3),
            Field("quarterA", "1/4", 60, 3),

            Field("sixtyT", "60'", 50, 3),
            Field("threeThirtyT", "330'", 50, 3),
            Field("eighthT", "1/8", 50, 3),
            Field("thousandT", "1000'", 50, 3),
            Field("quarterT", "1/4", 60, 3),

            Field("sixtyH", "60'", 50, 3),
            Field("threeThirtyH", "330'", 50, 3),
            Field("eighthH", "1/8", 50, 3),
            Field("thousandH", "1000'", 50, 3),
            Field("quarterH", "1/4", 60, 3),

            Field("sixtyP", "60'", 50, 3),
            Field("threeThirtyP", "330'", 50, 3),
            Field("eighthP", "1/8", 50, 3),
            Field("thousandP", "1000'", 50, 3),
            Field("quarterP", "1/4", 60, 3)};


class Predictions : public DbTableBase
{
public:
    explicit Predictions();
};


class NAROBCORESHARED_EXPORT Prediction : public DbRecordBase
{
public:
    explicit Prediction(TicketsModel *model,
                        Vehicle *vehicle,
                        Race *race,
                        const int ticketId);
    void predictClocks(QDateTime dateTime,
                       double riderWeight,
                       int vehicleWeight,
                       double windAdjustment,
                       double weightAdjustment,
                       bool allForVehicle,
                       bool allForTrack);
    QVector<Prediction*> adjacentPredictions();

private:
    QVector<Ticket*> validTickets(const QString &clock);
    void getWeather();
    void predictClock(const QString &clock);
    double windCorrection(Ticket *ticket);
    double weightCorrection(Ticket *ticket);

    int mTrackId;
    int mRaceId;
    int mTicketId;
    Vehicle *mVehicle;
    Race *mRace;
    bool mAllForVehicle;
    bool mAllForTrack;
    TicketsModel *mTicketsModel;
    QVector<Ticket*> mTickets;
};


class NAROBCORESHARED_EXPORT PredictionsModel : public ModelBase
{
    Q_OBJECT

public:
    explicit PredictionsModel(int vehicleId,
                              int raceId,
                              int ticketId,
                              QObject *parent);
    QVariant data(const QModelIndex &item, int role) const;
};

#endif // PREDICTIONS_H
