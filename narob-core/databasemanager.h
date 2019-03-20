#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include "tracks.h"
#include "races.h"
#include "vehicles.h"
#include "tickets.h"
#include "observations.h"
#include "predictions.h"
#include "settings.h"

#include <QObject>
#include <QSqlDatabase>

class QSqlQuery;

const QString DATABASE_FILENAME = "narob.sqlite";

class NAROBCORESHARED_EXPORT DatabaseManager : public QObject
{
    Q_OBJECT

public:
    explicit DatabaseManager(QObject *parent = nullptr);
    ~DatabaseManager();

    static void debugQuery(const QSqlQuery& query);
    void updateLogbook();
    void testWeather();
    void testTP();
    void testWind();
    void testWeight();

private:
    QSqlDatabase mDatabase;
    void initTables();
    void clearDatabase();
    void setupTest();

    Tracks mTracks;
    Races mRaces;
    Vehicles mVehicles;
    Tickets mTickets;
    Observations mObservations;
    Predictions mPredictions;

signals:
    void dbUpdate();
};

#endif // DATABASEMANAGER_H
