#include <QDebug>

#include <QColor>
#include <QPointF>

#include "predictions.h"
#include "tickets.h"
#include "observations.h"

using namespace std;

typedef QList<QPointF> Points;

struct Line
{
    double mSlope;
    double mIntercept;

    Line(Points &pts)
    {
        int nPoints = pts.size();

        qreal sumX = 0, sumY = 0, sumXY = 0, sumX2 = 0;

        for(int i = 0; i < nPoints; i++) {
            sumX += pts[i].rx();
            sumY += pts[i].ry();
            sumXY += pts[i].rx() * pts[i].ry();
            sumX2 += pts[i].rx() * pts[i].rx();
        }

        double xMean = sumX / nPoints;
        double yMean = sumY / nPoints;
        double denominator = sumX2 - sumX * xMean;

        if(denominator == 0.0){
            denominator = 0.000001;
        }

        mSlope = (sumXY - (sumX * yMean)) / denominator;
        mIntercept = yMean - (mSlope * xMean);
    }

    double getYforX(double x)
    {
        return (mSlope * x) + mIntercept;
    }
};

Predictions::Predictions() :
    DbTableBase("predictions",
                PREDICTION_FIELDS)
{
}


Prediction::Prediction(TicketsModel *model,
                       const int vehicleId,
                       const int trackId,
                       const int raceId,
                       const int ticketId) :
    DbRecordBase("predictions",
                 PREDICTION_FIELDS),
    mVehicleId(vehicleId),
    mTrackId(trackId),
    mRaceId(raceId),
    mTicketId(ticketId),
    mTicketsModel(model)
{
    setValue("vehicleId", mVehicleId);
    setValue("raceId", mRaceId);
    setValue("ticketId", mTicketId);
}

void Prediction::predictClocks(QDateTime dateTime,
                               double riderWeight,
                               int vehicleWeight,
                               double windAdjustment,
                               double weightAdjustment,
                               bool allForVehicle,
                               bool allForTrack)
{
    setValue("dateTime",dateTime);
    setValue("riderWeight", riderWeight);
    setValue("vehicleWeight", vehicleWeight);
    setValue("windAdjustment", windAdjustment);
    setValue("weightAdjustment", weightAdjustment);
    setValue("allForVehicle", allForVehicle);
    setValue("allForTrack", allForTrack);

    mRiderWeight = riderWeight;
    mVehicleWeight = vehicleWeight;
    mWindAdjustment = windAdjustment;
    mWeightAdjustment = weightAdjustment;
    mAllForTrack = allForTrack;
    mAllForVehicle = allForVehicle;

    mTickets = mTicketsModel->predictionTickets(mAllForTrack,
                                                mAllForVehicle,
                                                mTrackId,
                                                mRaceId,
                                                mTicketId);

    getWeather();

    predictClock("sixty");
    predictClock("threeThirty");
    predictClock("eighth");
    predictClock("thousand");
    predictClock("quarter");
}

QVector<Prediction*> Prediction::adjacentPredictions(){
    QVector<Prediction*> aPredictions;

    QDateTime ticketDateTime = value("dateTime").toDateTime();
    QTime ticketTime = ticketDateTime.time();
    QTime startTime = ticketTime.addSecs(-300);

    for(int i = 0; i < 11; i++){
        Prediction *prediction = new Prediction(mTicketsModel,
                                                mVehicleId,
                                                mTrackId,
                                                mRaceId,
                                                mTicketId);

        prediction->predictClocks(QDateTime(ticketDateTime.date(),
                                            startTime.addSecs(i * 60)),
                                  mRiderWeight,
                                  mVehicleWeight,
                                  mWindAdjustment,
                                  mWeightAdjustment,
                                  mAllForVehicle,
                                  mAllForTrack);

        aPredictions.append(prediction);
    }

    return aPredictions;
}

void Prediction::predictClock(const QString &clock)
{
    Points tPoints;
    Points hPoints;
    Points pPoints;
    Points dPoints;

    double factor = 1.0;

    if(clock == "sixty"){
        factor = 22.0;
    }else if(clock == "threeThirty"){
        factor = 4.0;
    }else if(clock == "eighth"){
        factor = 2.0;
    }else if(clock == "thousand"){
        factor = 1.32;
    }

    vector<shared_ptr<Ticket>> validTickets;

    for(auto&& ticket : *mTickets){
        if(ticket->value(clock).toDouble() > 0){
            validTickets.push_back(ticket);
        }
    }

    if(!validTickets.empty()  && mTemperature > 0.0){
        for(auto&& ticket : validTickets){
            double adjustedClock = ticket->value(clock).toDouble()
                                   + (windCorrection(ticket) / factor)
                                   + (weightCorrection(ticket) / factor);

            tPoints.append(QPointF(ticket->value("temperature").toDouble(),
                                   adjustedClock));
            hPoints.append(QPointF(ticket->value("humidity").toDouble(),
                                   adjustedClock));
            pPoints.append(QPointF(ticket->value("pressure").toDouble(),
                                   adjustedClock));
            dPoints.append(QPointF(ticket->value("densityAltitude").toInt(),
                                   adjustedClock));
        }

        Line tLine(tPoints);
        Line hLine(hPoints);
        Line pLine(pPoints);
        Line dLine(dPoints);

        setValue(clock + "T",
                       tLine.getYforX(mTemperature));
        setValue(clock + "H",
                       hLine.getYforX(mHumidity));
        setValue(clock + "P",
                       pLine.getYforX(mPressure));
        setValue(clock + "D",
                       dLine.getYforX(mDensityAltitude));
        setValue(clock + "A",
                       (value(clock + "T").toDouble()
                        + value(clock + "H").toDouble()
                        + value(clock + "P").toDouble())
                       / 3);
    }else{
        setValue(clock + "T", 0.0);
        setValue(clock + "H", 0.0);
        setValue(clock + "P", 0.0);
        setValue(clock + "D", 0.0);
        setValue(clock + "A", 0.0);
    }
}

void Prediction::getWeather()
{
    auto observationsModel = make_unique<ObservationsModel>();

    Observation observation;
    observationsModel->select();

    if(value("dateTime").toDateTime().isValid()){
        observation = observationsModel->
                      observationForTime(value("dateTime").toDateTime());
    }else{
        observation = observationsModel->lastObservation();
        setValue("dateTime", observation.value("dateTime").toDateTime());
    }

    setValue("temperature", observation.value("temperature"));
    setValue("humidity", observation.value("humidity"));
    setValue("pressure", observation.value("pressure"));
    setValue("vaporPressure", observation.value("vaporPressure"));
    setValue("dewPoint", observation.value("dewPoint"));
    setValue("densityAltitude", observation.value("densityAltitude"));
    setValue("windSpeed", observation.value("windSpeed"));
    setValue("windGust", observation.value("windGust"));
    setValue("windDirection", observation.value("windDirection"));

    mTemperature = value("temperature").toDouble();
    mHumidity = value("humidity").toDouble();
    mPressure = value("pressure").toDouble();
    mVaporPressure = value("vaporPressure").toDouble();
    mDewPoint = value("dewPoint").toDouble();
    mDensityAltitude = value("densityAltitude").toInt();
    mWindSpeed = value("windSpeed").toInt();
    mWindGust = value("windGust").toInt();
    mWindDirection = value("windDirection").toInt();
}

double windFactor(int windSpeed, int windDirection)
{
    double wFactor = 0;
    double dFactor = 0;

    // wind direction   0 = headwind ( higher ET )
    //                180 = tailwind ( lower ET )

    if(windDirection < 50){
        dFactor = (50 - windDirection) * 0.02;
    }else if(windDirection > 130){
        dFactor = (windDirection - 130) * -0.02;
    }

    wFactor = windSpeed
              * dFactor;

    return wFactor;

}

double Prediction::windCorrection(shared_ptr<Ticket> ticket)
{
    double correction = 0;
    double windDifference = 0;

    windDifference = windFactor(mWindSpeed, mWindDirection) -
                     windFactor(ticket->value("windSpeed").toInt(),
                                 ticket->value("windDirection").toInt());
    correction = windDifference * mWindAdjustment;

    return correction;
}

double Prediction::weightCorrection(shared_ptr<Ticket> ticket)
{
    double correction = 0;
    double weightDifference = 0;

    weightDifference = (mRiderWeight + mVehicleWeight) -
                       (ticket->value("riderWeight").toDouble() +
                        ticket->value("vehicleWeight").toDouble());
    correction = weightDifference * mWeightAdjustment;

    return correction;
}


PredictionsModel::PredictionsModel(int vehicleId,
                                   int raceId,
                                   int ticketId,
                                   QObject *parent) :
    ModelBase("predictions",
              PREDICTION_FIELDS,
              parent)
{
    QString filter = QString("vehicleId = %1 AND "
                             "raceId = %2 AND "
                             "ticketID = %3")
                     .arg(vehicleId)
                     .arg(raceId)
                     .arg(ticketId);


    setFilter(filter);

    setSort(fieldIndex("dateTime"), Qt::DescendingOrder);

    select();
}

QVariant PredictionsModel::data(const QModelIndex &item, int role) const
{
    if(role == Qt::BackgroundRole){

        int col = item.column();

        if(col == fieldIndex("sixtyA") ||
           col == fieldIndex("threeThirtyA") ||
           col == fieldIndex("eighthA") ||
           col == fieldIndex("thousandA") ||
           col == fieldIndex("quarterA")){

            return QVariant(QColor(Qt::lightGray));
        }

        if(col == fieldIndex("sixtyT") ||
           col == fieldIndex("threeThirtyT") ||
           col == fieldIndex("eighthT") ||
           col == fieldIndex("thousandT") ||
           col == fieldIndex("quarterT")){

            return QVariant(QColor(Qt::magenta));
        }

        if(col == fieldIndex("sixtyH") ||
           col == fieldIndex("threeThirtyH") ||
           col == fieldIndex("eighthH") ||
           col == fieldIndex("thousandH") ||
           col == fieldIndex("quarterH")){

            return QVariant(QColor(Qt::cyan));
        }

        if(col == fieldIndex("sixtyP") ||
           col == fieldIndex("threeThirtyP") ||
           col == fieldIndex("eighthP") ||
           col == fieldIndex("thousandP") ||
           col == fieldIndex("quarterP")){

            return QVariant(QColor(Qt::yellow));
        }

    }

    return QSqlRelationalTableModel::data(item, role);
}
