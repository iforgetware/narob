#include <QDebug>

#include <QColor>
#include <QPointF>

#include "predictions.h"
#include "tickets.h"
#include "observations.h"

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
                       Vehicle *vehicle,
                       Race *race,
                       const int ticketId) :
    DbRecordBase("predictions",
                 PREDICTION_FIELDS),
    mTrackId(race->value("trackId").toInt()),
    mRaceId(race->value("id").toInt()),
    mTicketId(ticketId),
    mVehicle(vehicle),
    mRace(race),
    mTicketsModel(model)
{
    init();

    this->setValue("vehicleId", vehicle->value("id").toInt());
    this->setValue("raceId", mRaceId);
    this->setValue("ticketId", mTicketId);
}

void Prediction::predictClocks(QDateTime dateTime,
                               double riderWeight,
                               int vehicleWeight,
                               double windAdjustment,
                               double weightAdjustment,
                               bool allForVehicle,
                               bool allForTrack)
{
    this->setValue("dateTime",dateTime);
    this->setValue("riderWeight", riderWeight);
    this->setValue("vehicleWeight", vehicleWeight);
    this->setValue("windAdjustment", windAdjustment);
    this->setValue("weightAdjustment", weightAdjustment);
    this->setValue("allForVehicle", allForVehicle);
    this->setValue("allForTrack", allForTrack);

    mAllForTrack = allForTrack;
    mAllForVehicle = allForVehicle;

    mTickets = mTicketsModel->allTickets();

    getWeather();

    predictClock("sixty");
    predictClock("threeThirty");
    predictClock("eighth");
    predictClock("thousand");
    predictClock("quarter");

    foreach(Ticket *ticket, mTickets){
        delete ticket;
    }
}

QVector<Prediction*> Prediction::adjacentPredictions(){
    QVector<Prediction*> aPredictions;

    QDateTime ticketDateTime = this->value("dateTime").toDateTime();
    QTime ticketTime = ticketDateTime.time();
    QTime startTime = ticketTime.addSecs(-300);

    for(int i = 0; i < 11; i++){
        Prediction *prediction = new Prediction(mTicketsModel,
                                                mVehicle,
                                                mRace,
                                                mTicketId);

        prediction->predictClocks(QDateTime(ticketDateTime.date(),
                                            startTime.addSecs(i * 60)),
                                  this->value("riderWeight").toDouble(),
                                  this->value("vehicleWeight").toInt(),
                                  this->value("windAdjustment").toDouble(),
                                  this->value("weightAdjustment").toDouble(),
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

    QVector<Ticket*> tickets = validTickets(clock);

    if(tickets.count() > 1 && this->value("temperature").toDouble() > 0.0){
        foreach(Ticket* ticket, tickets){
            double adjustedClock = ticket->value(clock).toDouble()
                                   + (this->windCorrection(ticket) / factor)
                                   + (this->weightCorrection(ticket) / factor);

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

        this->setValue(clock + "T",
                       tLine.getYforX(this->value("temperature")
                                      .toDouble()));
        this->setValue(clock + "H",
                       hLine.getYforX(this->value("humidity")
                                      .toDouble()));
        this->setValue(clock + "P",
                       pLine.getYforX(this->value("pressure")
                                      .toDouble()));
        this->setValue(clock + "D",
                       dLine.getYforX(this->value("densityAltitude")
                                      .toInt()));
        this->setValue(clock + "A",
                       (this->value(clock + "T").toDouble()
                        + this->value(clock + "H").toDouble()
                        + this->value(clock + "P").toDouble())
                       / 3);
    }else{
        this->setValue(clock + "T", 0.0);
        this->setValue(clock + "H", 0.0);
        this->setValue(clock + "P", 0.0);
        this->setValue(clock + "D", 0.0);
        this->setValue(clock + "A", 0.0);
    }
}

void Prediction::getWeather()
{
    ObservationsModel *observationsModel = new ObservationsModel();

    Observation observation;
    observationsModel->select();

    if(this->value("dateTime").toDateTime().isValid()){
        observation = observationsModel->
                      observationForTime(this->value("dateTime").toDateTime());
    }else{
        observation = observationsModel->lastObservation();
        this->setValue("dateTime", observation.value("dateTime").toDateTime());
    }

    this->setValue("temperature", observation.value("temperature"));
    this->setValue("humidity", observation.value("humidity"));
    this->setValue("pressure", observation.value("pressure"));
    this->setValue("vaporPressure", observation.value("vaporPressure"));
    this->setValue("dewPoint", observation.value("dewPoint"));
    this->setValue("densityAltitude" ,observation.value("densityAltitude"));
    this->setValue("windSpeed", observation.value("windSpeed"));
    this->setValue("windGust", observation.value("windGust"));
    this->setValue("windDirection", observation.value("windDirection"));

    delete observationsModel;
}

QVector<Ticket*> Prediction::validTickets(const QString &clock)
{
    QVector<Ticket*> vTickets;

    bool valid;

    foreach(Ticket* ticket, mTickets){
        valid = true;

        if(!mAllForVehicle){
            valid = ticket->value("trackId").toInt() == mTrackId;

            if(!mAllForTrack){
                valid = ticket->value("raceId").toInt() == mRaceId;
            }
        }

        if(valid && mTicketId){
            valid = (ticket->value("id").toInt() != mTicketId);
        }

        if(valid){
            valid = ticket->value(clock).toDouble() > 0;
        }

        if(valid){
            vTickets.append(ticket);
        }
    }

    return vTickets;
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

double Prediction::windCorrection(Ticket *ticket)
{
    double correction = 0;
    double windDifference = 0;

    windDifference = windFactor(this->value("windSpeed").toInt(),
                                this->value("windDirection").toInt()) -
                     windFactor(ticket->value("windSpeed").toInt(),
                                 ticket->value("windDirection").toInt());
    correction = windDifference * this->value("windAdjustment").toDouble();

    return correction;
}

double Prediction::weightCorrection(Ticket *ticket)
{
    double correction = 0;
    double weightDifference = 0;

    weightDifference = (this->value("riderWeight").toDouble() +
                        this->value("vehicleWeight").toDouble()) -
                       (ticket->value("riderWeight").toDouble() +
                        ticket->value("vehicleWeight").toDouble());
    correction = weightDifference * this->value("weightAdjustment").toDouble();

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
