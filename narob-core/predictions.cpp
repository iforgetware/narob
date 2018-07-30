#include <QDebug>

#include "predictions.h"

Fields predictionFields()
{
    Fields f;

    f.append(Field("id", "id", 0, 0));

    f.append(Field("raceId", "Race", 150, 0));
    f.append(Field("vehicleId", "Vehicle", 150, 0));

    f.append(Field("dateTime", "Date       Time", 160, -3));

    f.append(Field("vehicleWeight", "V Weight", 70, 0));
    f.append(Field("riderWeight", "R Weight", 70, 1));

    f.append(Field("temperature", "Temp", 50, 1));
    f.append(Field("humidity", "Humid",50, 1));
    f.append(Field("pressure", "Pres", 50, 2));
    f.append(Field("vaporPressure", "V Pres", 50, 2));
    f.append(Field("dewPoint", "D Point", 60, 1));
    f.append(Field("densityAltitude", "D Alt", 50, 0));
    f.append(Field("windSpeed", "W Speed", 70, 0));
    f.append(Field("windGust", "W Gust", 70, 0));
    f.append(Field("windDirection", "W Dir", 60, 0));

    f.append(Field("windAdjustment", "Wd A", 50, 3));
    f.append(Field("weightAdjustment", "Wt A", 50, 3));

    f.append(Field("eTp", "1/8T", 60, 3));
    f.append(Field("eHp", "1/8H", 60, 3));
    f.append(Field("ePp", "1/8P", 60, 3));
    f.append(Field("eAp", "1/8A", 60, 3));
    f.append(Field("eDp", "1/8D", 60, 3));
//    f.append(Field("windCorrectionEighth", "Wn CE", 50, 3));

    f.append(Field("qTp", "1/4T", 60, 3));
    f.append(Field("qHp", "1/4H", 60, 3));
    f.append(Field("qPp", "1/4P", 60, 3));
    f.append(Field("qAp", "1/4A", 60, 3));
    f.append(Field("qDp", "1/4D", 60, 3));
//    f.append(Field("windCorrectionQuarter", "Wn CQ", 50, 3));

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

PredictionsModel::PredictionsModel(Vehicle *vehicle,
                                   Race *race,
                                   QObject *parent) :
    ModelBase("predictions",
              predictionFields(),
              parent),
    mVehicle(vehicle),
    mRace(race)
{
    QString filter = QString("vehicleId = %1 AND raceId = %2")
                     .arg(mVehicle->value("id").toInt())
                     .arg(mRace->value("id").toInt());

    setFilter(filter);

    setSort(fieldIndex("dateTime"), Qt::DescendingOrder);

    select();
}

void PredictionsModel::addPrediction(Prediction &prediction)
{
    insertRecord(-1, prediction);
    submitAll();
    select();
}
