#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include "tracks.h"
#include "races.h"
#include "vehicles.h"
#include "tickets.h"
#include "observations.h"
#include "predictions.h"
#include "refpts.h"

#include <QObject>
#include <QSqlDatabase>

class QSqlQuery;

const QString DATABASE_FILENAME = "narob.sqlite";

class DatabaseManager : public QObject
{
    Q_OBJECT

public:
    explicit DatabaseManager(QObject *parent = 0);
    ~DatabaseManager();

    static void debugQuery(const QSqlQuery& query);

private:
    QSqlDatabase mDatabase;

public:
    Tracks tracks;
    Races races;
    Vehicles vehicles;
    Tickets tickets;
    Observations observations;
    Predictions predictions;
    RefPTs refPTs;
};

#endif // DATABASEMANAGER_H
