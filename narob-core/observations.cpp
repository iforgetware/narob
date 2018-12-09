#include <QSqlQuery>

#include "observations.h"

Observations::Observations() :
    DbTableBase("observations",
                OBSERVATION_FIELDS)
{
}


Observation::Observation() :
    DbRecordBase("observations",
                 OBSERVATION_FIELDS)
{
    init();
}

ObservationsModel::ObservationsModel(QObject *parent) :
    ModelBase("observations",
              OBSERVATION_FIELDS,
              parent)
{
    setSort(fieldIndex("dateTime"), Qt::DescendingOrder);

    select();
}

Observation ObservationsModel::lastObservation()
{
    Observation observation;
    observation.populate(record(0));

    return observation;
}

Observation ObservationsModel::observationForTime(QDateTime dateTime)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM observations "
                  "WHERE dateTime = :dateTime");
    query.bindValue(":dateTime", dateTime);

    query.exec();

    Observation observation;

    if(query.next()){
        observation.populate(query.record());

    }
    // this needs a proper error handler
//    }else{
//        qDebug("Weather not found in Observation Model");
//    }

    query.clear();

    return observation;
}
