#include "predictions.h"

Fields setPredictionFields()
{
    Fields retFields;

    retFields.append(Field("id", "id", 0, 0));

    retFields.append(Field("raceId", "Race", 150, 0));
    retFields.append(Field("vehicleId", "Vehicle", 150, 0));

    retFields.append(Field("dateTime", "Date       Time", 160, -3));

    retFields.append(Field("vehicleWeight", "V Weight", 70, 0));
    retFields.append(Field("riderWeight", "R Weight", 70, 1));

    retFields.append(Field("temperature", "Temp", 50, 1));
    retFields.append(Field("humidity", "Humid",50, 1));
    retFields.append(Field("pressure", "Pres", 50, 2));
    retFields.append(Field("vaporPressure", "V Pres", 50, 2));
    retFields.append(Field("dewPoint", "D Point", 60, 1));
    retFields.append(Field("densityAltitude", "D Alt", 50, 0));
    retFields.append(Field("windSpeed", "W Speed", 70, 0));
    retFields.append(Field("windGust", "W Gust", 70, 0));
    retFields.append(Field("windDirection", "W Dir", 60, 0));

    retFields.append(Field("windFactor", "Wd F", 50, 0));
    retFields.append(Field("weightFactor", "Wt F", 50, 0));

    retFields.append(Field("eTp", "1/8T", 50, 3));
    retFields.append(Field("eHp", "1/8H", 50, 3));
    retFields.append(Field("ePp", "1/8P", 50, 3));
    retFields.append(Field("eAp", "1/8A", 50, 3));
    retFields.append(Field("eDp", "1/8D", 50, 3));
    retFields.append(Field("windCorrectionEighth", "Wn CE", 50, 3));

    retFields.append(Field("qTp", "1/4T", 50, 3));
    retFields.append(Field("qHp", "1/4H", 50, 3));
    retFields.append(Field("qPp", "1/4P", 50, 3));
    retFields.append(Field("qAp", "1/4A", 50, 3));
    retFields.append(Field("qDp", "1/4D", 50, 3));
    retFields.append(Field("windCorrectionQuarter", "Wn CQ", 50, 3));

    return retFields;
}

Fields predictionFields = setPredictionFields();

Predictions::Predictions() :
    DbTableBase()
{
    mFields = predictionFields;
    mTable = "predictions";
}


Prediction::Prediction() :
    DbRecordBase()
{
    mFields = predictionFields;
    init("predictions");
}

PredictionsModel::PredictionsModel(Vehicle *vehicle,
                                   Race *race,
                                   QObject *parent) :
    ModelBase(parent),
    mVehicle(vehicle),
    mRace(race)
{
    setTable("predictions");

    QString filter = QString("vehicleId = %1 AND raceId = %2")
                     .arg(mVehicle->value("id").toInt())
                     .arg(mRace->value("id").toInt());

    setFilter(filter);

    mFields = predictionFields;

    setHeaders();

    setSort(fieldIndex("dateTime"), Qt::DescendingOrder);

    select();
}

void PredictionsModel::addPrediction(Prediction &prediction)
{
    insertRecord(-1, prediction);
    submitAll();
    select();
}
