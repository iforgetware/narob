#ifndef OBSERVATIONS_H
#define OBSERVATIONS_H

#include <memory>

#include <QVector>
#include <QDateTime>

#include "dbtablebase.h"
#include "dbrecordbase.h"
#include "modelbase.h"

#include "narob-core_global.h"

const Fields OBSERVATION_FIELDS{
            Field("id", "id", 0, 0),
            Field("dateTime", "Date       Time", 160, -3),
            Field("temperature", "Temp", 50, 1),
            Field("humidity", "Humid",50, 1),
            Field("pressure", "Pres", 50, 2),
            Field("vaporPressure", "V Pres", 50, 2),
            Field("dewPoint", "D Point", 60, 1),
            Field("densityAltitude", "D Alt", 60, 0),
            Field("windSpeed", "W Speed", 70, 0),
            Field("windDirection", "W Dir", 60, 0),
            Field("windGust", "G Speed", 70, 0),
            Field("windGustDirection", "G Dir", 60, 0),
            Field("samples", "Sam", 60, 0)
};


class Observations : public DbTableBase
{
public:
    explicit Observations();
};






// add purge weather button?
// or just autodelete if older than {setting}

// create observations history table
// save the 11 around a ticket to this
// never purge this table
// only delete when ticket is deleted







class NAROBCORESHARED_EXPORT Observation : public DbRecordBase
{
public:
    explicit Observation();
};


class NAROBCORESHARED_EXPORT ObservationsModel : public ModelBase
{
    Q_OBJECT

public:
    explicit ObservationsModel(QObject *parent = nullptr);

    Observation lastObservation();
    Observation observationForTime(QDateTime dateTime);
    std::unique_ptr<std::vector<std::unique_ptr<Observation>>> observationsForToday();
    std::unique_ptr<std::vector<std::unique_ptr<Observation>>> observationsForDays(const int days);
};


#endif // OBSERVATIONS_H
