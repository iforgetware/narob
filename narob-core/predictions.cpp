#include <QDebug>

#include <QtGui/QColor>
#include <QPointF>

#include "predictions.h"
#include "tickets.h"
#include "observations.h"

Fields predictionFields()
{
    Fields f;

    f << Field("id", "id", 0, 0)

      << Field("vehicleId", "Vehicle", 150, 0)
      << Field("trackId", "Track", 150, 0)
      << Field("raceId", "Race", 150, 0)
      << Field("ticketId", "Ticket", 150, 0)

      << Field("dateTime", "Date       Time", 160, -3)

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

      << Field("windAdjustment", "Wd A", 50, 3)
      << Field("weightAdjustment", "Wt A", 50, 3)

      << Field("sixtyD", "60'", 50, 3)
      << Field("threeThirtyD", "330'", 50, 3)
      << Field("eighthD", "1/8", 50, 3)
      << Field("thousandD", "1000'", 50, 3)
      << Field("quarterD", "1/4", 60, 3)

      << Field("sixtyA", "60'", 50, 3)
      << Field("threeThirtyA", "330'", 50, 3)
      << Field("eighthA", "1/8", 50, 3)
      << Field("thousandA", "1000'", 50, 3)
      << Field("quarterA", "1/4", 60, 3)

      << Field("sixtyT", "60'", 50, 3)
      << Field("threeThirtyT", "330'", 50, 3)
      << Field("eighthT", "1/8", 50, 3)
      << Field("thousandT", "1000'", 50, 3)
      << Field("quarterT", "1/4", 60, 3)

      << Field("sixtyH", "60'", 50, 3)
      << Field("threeThirtyH", "330'", 50, 3)
      << Field("eighthH", "1/8", 50, 3)
      << Field("thousandH", "1000'", 50, 3)
      << Field("quarterH", "1/4", 60, 3)

      << Field("sixtyP", "60'", 50, 3)
      << Field("threeThirtyP", "330'", 50, 3)
      << Field("eighthP", "1/8", 50, 3)
      << Field("thousandP", "1000'", 50, 3)
      << Field("quarterP", "1/4", 60, 3);

    return f;
}

Predictions::Predictions() :
    DbTableBase()
{
    mFields = predictionFields();
    mTable = "predictions";
}


Prediction::Prediction() :
    DbRecordBase()
{
    mFields = predictionFields();
    init("predictions");
}

void Prediction::predictClocks(bool allForVehicle,
                               bool allForTrack,
                               TicketsModel *ticketsModel)
{
    mAllForVehicle = allForVehicle;
    mAllForTrack = allForTrack;
    mTicketsModel = ticketsModel;

    getWeather();

//    mRefPTList.clear();

    predictClock("sixty");
    predictClock("threeThirty");
    predictClock("eighth");
    predictClock("thousand");
    predictClock("quarter");

//    return mRefPTList;
}

void Prediction::getWeather()
{
    ObservationsModel *observationsModel = new ObservationsModel();

    Observation* observation = new Observation();
    observationsModel->select();
    if(this->value("dateTime").toDateTime().isValid()){
        observation = observationsModel->observationForTime(this->value("dateTime").toDateTime());
    }else{
        observation = observationsModel->lastObservation();
        this->setValue("DateTime", observation->value("dateTime").toDateTime());
    }

    if(observation){
        this->setValue("temperature", observation->value("temperature"));
        this->setValue("humidity", observation->value("humidity"));
        this->setValue("pressure", observation->value("pressure"));
        this->setValue("vaporPressure", observation->value("vaporPressure"));
        this->setValue("dewPoint", observation->value("dewPoint"));
        this->setValue("densityAltitude" ,observation->value("densityAltitude"));
        this->setValue("windSpeed", observation->value("windSpeed"));
        this->setValue("windGust", observation->value("windGust"));
        this->setValue("windDirection", observation->value("windDirection"));
    }else{
        qDebug("Weather not found - WRITE CODE");
    }

    delete observationsModel;
    delete observation;
}

QVector<Ticket*> Prediction::validTickets(const QString &clock)
{
    QVector<Ticket*> tickets;

    bool valid;

    foreach(Ticket* ticket, mTicketsModel->tickets()){
        valid = true;

        if(!mAllForVehicle){
            valid = ticket->value("trackId") == this->value("trackId");

            if(!mAllForTrack){
                valid = ticket->value("raceId") == this->value("raceId");
            }
        }

        if(valid){
            valid = ticket->value(clock).toDouble() > 0;
        }

        if(valid){
            valid = (ticket->value("id") != this->value("ticketId"));
        }

        if(valid){
            tickets.append(ticket);
        }
    }

    return tickets;
}

typedef QList<QPointF> Points;

struct Line
{
    double mSlope;
    double mIntercept;

    Line(Points &pts)
    {
        int nPoints = pts.size();

        qreal sumX = 0, sumY = 0, sumXY = 0, sumX2 = 0;

        for(int i = 0;i < nPoints; i++) {
            sumX += pts[i].rx();
            sumY += pts[i].ry();
            sumXY += pts[i].rx() * pts[i].ry();
            sumX2 += pts[i].rx() * pts[i].rx();
        }

        double xMean = sumX / nPoints;
        double yMean = sumY / nPoints;
        double denominator = sumX2 - sumX * xMean;

        if(!denominator){
            denominator = 0.000001;
            //qDebug("denominator ZERO - WRITE CODE");
        }

        mSlope = (sumXY - (sumX * yMean)) / denominator;
        mIntercept = yMean - (mSlope * xMean);
    }

    double getYforX(double x)
    {
        return (mSlope * x) + mIntercept;
    }
};

double windFactor(int windSpeed, int windDirection)
{
    double wFactor = 0;
    double dFactor = 0;

    if(windDirection < 50){
        dFactor = (50 - windDirection) * 0.02;
    }

    if(windDirection > 130){
        dFactor = (windDirection - 130) * -0.02;
    }

    wFactor = windSpeed
              * dFactor;

    return wFactor;

}

double Prediction::windCorrection(Ticket *ticket)
{
    // wind direction   0 = headwind ( higher ET )
    //                180 = tailwind ( lower ET )
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

double formatClock(double clock)
{
    return QString::number(clock, 'f', 3).toDouble();
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

//        RefPT refPT;

//        refPT.setValue("ticketId", ticket->value("id").toInt());
//        refPT.setValue("clock", clock);

//        if(this->value("ticketId").toInt()){
//            mRefPTList.append(refPT);
//        }
    }

    Line tLine(tPoints);
    Line hLine(hPoints);
    Line pLine(pPoints);
    Line dLine(dPoints);

    this->setValue(clock + "T",
                   formatClock(tLine.getYforX(this->value("temperature")
                                              .toDouble())));
    this->setValue(clock + "H",
                   formatClock(hLine.getYforX(this->value("humidity")
                                              .toDouble())));
    this->setValue(clock + "P",
                   formatClock(pLine.getYforX(this->value("pressure")
                                  .toDouble())));
    this->setValue(clock + "A",
                   formatClock((this->value(clock + "T").toDouble()
                                + this->value(clock + "H").toDouble()
                                + this->value(clock + "P").toDouble())
                               / 3));
    this->setValue(clock + "D",
                   formatClock(dLine.getYforX(this->value("densityAltitude")
                                              .toInt())));
}


PredictionsModel::PredictionsModel(Vehicle *vehicle,
                                   Race *race,
                                   int ticketId,
                                   QObject *parent) :
    ModelBase("predictions",
              predictionFields(),
              parent),
    mVehicle(vehicle),
    mRace(race),
    mTicketId(ticketId)
{
    QString filter = QString("vehicleId = %1 AND raceId = %2 AND ticketID = %3")
                     .arg(mVehicle->value("id").toInt())
                     .arg(mRace->value("id").toInt())
                     .arg(mTicketId);


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
