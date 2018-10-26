#ifndef TICKETS_H
#define TICKETS_H

#include <QVector>
#include <QSortFilterProxyModel>

#include "dbtablebase.h"
#include "dbrecordbase.h"
#include "modelbase.h"
#include "vehicles.h"

#include "narob-core_global.h"

class Tickets : public DbTableBase
{
public:
    explicit Tickets();
};


class NAROBCORESHARED_EXPORT Ticket : public DbRecordBase
{
public:
    explicit Ticket();

    void setWeather();
};


class NAROBCORESHARED_EXPORT TicketsModel : public ModelBase
{
    Q_OBJECT

public:
    explicit TicketsModel(Vehicle *vehicle,
                          QObject *parent = 0);
    QVariant data(const QModelIndex &item, int role) const;

    QVector<Ticket*> tickets();
    double lastWeight();

private:
    Vehicle *mVehicle;
};


class NAROBCORESHARED_EXPORT TicketsRaceModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    TicketsRaceModel(int raceId, QObject* parent);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const;

private:
    int mRaceId;
};


class NAROBCORESHARED_EXPORT TicketsTrackModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    TicketsTrackModel(int trackId, QObject* parent);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const;

private:
    int mTrackId;
};

#endif // TICKETS_H
