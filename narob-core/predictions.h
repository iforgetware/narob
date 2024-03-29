#ifndef PREDICTIONS_H
#define PREDICTIONS_H

#include <memory>

#include "dbtablebase.h"
#include "dbrecordbase.h"
#include "modelbase.h"

#include "tickets.h"
#include "vehicles.h"
#include "races.h"
#include "observations.h"

#include "narob-core_global.h"

const Fields PREDICTION_FIELDS{
            Field("id", "id", 0),

            Field("vehicleId", "Vehicle", 0),
            Field("raceId", "Race", 0),
            Field("ticketId", "Ticket", 0),

            Field("dateTime", "Date       Time", -3),

            Field("vehicleWeight", "V Weight", 0),
            Field("riderWeight", "R Weight", 1),

            Field("temperature", "Temp", 1),
            Field("humidity", "Humid", 1),
            Field("pressure", "Pres", 2),
            Field("vaporPressure", "V Pres", 2),
            Field("dewPoint", "D Point", 1),
            Field("densityAltitude", "D Alt", 0),
            Field("windSpeed", "W Speed", 0),
            Field("windGust", "W Gust", 0),
            Field("windDirection", "W Dir", 0),

            Field("windAdjustment", "Wd A", 3),
            Field("weightAdjustment", "Wt A", 3),
            Field("allForVehicle", "AFV", -1),
            Field("allForTrack", "AFT", -1),

            Field("sixtyD", "60'", 3),
            Field("threeThirtyD", "330'", 3),
            Field("eighthD", "1/8", 3),
            Field("thousandD", "1000'", 3),
            Field("quarterD", "1/4", 3),

            Field("sixtyA", "60'", 3),
            Field("threeThirtyA", "330'", 3),
            Field("eighthA", "1/8", 3),
            Field("thousandA", "1000'", 3),
            Field("quarterA", "1/4", 3),

            Field("sixtyT", "60'", 3),
            Field("threeThirtyT", "330'", 3),
            Field("eighthT", "1/8", 3),
            Field("thousandT", "1000'", 3),
            Field("quarterT", "1/4", 3),

            Field("sixtyH", "60'", 3),
            Field("threeThirtyH", "330'", 3),
            Field("eighthH", "1/8", 3),
            Field("thousandH", "1000'", 3),
            Field("quarterH", "1/4", 3),

            Field("sixtyP", "60'", 3),
            Field("threeThirtyP", "330'", 3),
            Field("eighthP", "1/8", 3),
            Field("thousandP", "1000'", 3),
            Field("quarterP", "1/4", 3)};


class Predictions : public DbTableBase
{
public:
    explicit Predictions();
};


class NAROBCORESHARED_EXPORT Prediction : public DbRecordBase
{
public:
    explicit Prediction(TicketsLogbookModel *tLModel,
                        const int vehicleId,
                        const int trackId,
                        const int raceId,
                        const int ticketId);
    void predictByTime(QDateTime dateTime,
                       double riderWeight,
                       int vehicleWeight,
                       double windAdjustment,
                       double weightAdjustment,
                       bool allForVehicle,
                       bool allForTrack);
    void predictByObservation(Observation observation,
                              double riderWeight,
                              int vehicleWeight,
                              double windAdjustment,
                              double weightAdjustment,
                              bool allForVehicle,
                              bool allForTrack);
    QVector<Prediction*> adjacentPredictions();
    Points eighthPoints(){return mEighthPoints;}
    Points quarterPoints(){return mQuarterPoints;}
    Line eighthLine(){return  mEighthLine;}
    Line quarterLine(){return mQuarterLine;}

private:
    void getWeather();
    void predictClocks();
    void predictClock(const QString &clock);
    double windCorrection(std::shared_ptr<Ticket> ticket);
    double weightCorrection(std::shared_ptr<Ticket> ticket);

    int mVehicleId;
    int mTrackId;
    int mRaceId;
    int mTicketId;
    double mRiderWeight;
    int mVehicleWeight;
    double mWindAdjustment;
    double mWeightAdjustment;
    bool mAllForVehicle;
    bool mAllForTrack;
    TicketsLogbookModel* mTicketsLogbookModel;
    std::unique_ptr<std::vector<std::shared_ptr<Ticket>>> mTickets;

    double mTemperature;
    double mHumidity;
    double mPressure;
    double mVaporPressure;
    double mDewPoint;
    int mDensityAltitude;
    int mWindSpeed;
    int mWindGust;
    int mWindDirection;

    Points mEighthPoints;
    Points mQuarterPoints;
    Line mEighthLine;
    Line mQuarterLine;
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
