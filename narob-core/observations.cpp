#include <QSqlQuery>

#include <QThread>

#include "observations.h"

using namespace std;

Observations::Observations() :
    DbTableBase("observations",
                OBSERVATION_FIELDS)
{
}


Observation::Observation() :
    DbRecordBase("observations",
                 OBSERVATION_FIELDS)
{
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

unique_ptr<vector<unique_ptr<Observation>>> ObservationsModel::observationsForToday()
{
    auto observationsVector = make_unique<vector<unique_ptr<Observation>>>();

    QDate date = QDate::currentDate();

    for(int row = rowCount() - 1; row >= 0 ; row--){
        if(record(row).value("dateTime").toDate() == date)
        {
            auto observation = make_unique<Observation>();

            observation->populate(record(row));

            observationsVector->push_back(move(observation));
        }
    }

    return observationsVector;
}
