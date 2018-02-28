#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <memory>

#include <QString>
#include <QSqlDatabase>

#include "trackdao.h"
#include "racedao.h"
#include "vehicledao.h"
#include "ticketdao.h"
#include "observationdao.h"
#include "settingsdao.h"
#include "predictiondao.h"
#include "refptdao.h"

class QSqlQuery;

const QString DATABASE_FILENAME = "narob.sqlite";

class DatabaseManager
{
public:
    static DatabaseManager& instance();
    ~DatabaseManager();

    static void debugQuery(const QSqlQuery& query);

    QSqlDatabase database() { return *mDatabase; }

protected:
    DatabaseManager(const QString& path = DATABASE_FILENAME);
    DatabaseManager& operator=(const DatabaseManager& rhs);

private:
    std::unique_ptr<QSqlDatabase> mDatabase;

    void clearDatabase();
    void populateTables();
    void populateTracks();

public:
    const TrackDao trackDao;
    const RaceDao raceDao;
    const VehicleDao vehicleDao;
    const TicketDao ticketDao;
    const ObservationDao observationDao;
    const SettingsDao settingsDao;
    const PredictionDao predictionDao;
    const RefPTDao refPTDao;
};

#endif // DATABASEMANAGER_H
