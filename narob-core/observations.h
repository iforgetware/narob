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
            Field("id", "id", 0),
            Field("dateTime", "Date       Time", -3),
            Field("temperature", "Temp", 1),
            Field("humidity", "Humid", 1),
            Field("pressure", "Pres", 2),
            Field("vaporPressure", "V Pres", 2),
            Field("dewPoint", "D Point", 1),
            Field("densityAltitude", "D Alt", 0),
            Field("windSpeed", "W Speed", 0),
            Field("windDirection", "W Dir", 0),
            Field("windGust", "G Speed", 0),
            Field("windGustDirection", "G Dir", 0),
            Field("relAirDensity", "R Den", 1),
            Field("dynoCorrectionFactor", "Dyno", 3),
            Field("relativeHP", "R HP", 1),
            Field("virtualTemp", "V Temp", 1),
            Field("samples", "Sam", 0)
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
    Observation(double t, double h, double p);
    explicit Observation();

    void overrideObservation(double t,
                             double h,
                             double p,
                             int wd,
                             int ws);

    void calcDA();
};


class NAROBCORESHARED_EXPORT ObservationsModel : public ModelBase
{
    Q_OBJECT

public:
    explicit ObservationsModel(QObject *parent = nullptr);

    Observation lastObservation();
    Observation observationForTime(QDateTime dateTime);
    std::unique_ptr<std::vector<std::unique_ptr<Observation>>> observationsForDays(const int days);
};


#endif // OBSERVATIONS_H
