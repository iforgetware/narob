#ifndef PREDICTIONS_H
#define PREDICTIONS_H

#include "dbtablebase.h"
#include "dbrecordbase.h"
#include "modelbase.h"

#include "tickets.h"
#include "vehicles.h"
#include "races.h"
//#include "refpts.h"

#include "narob-core_global.h"

class Predictions : public DbTableBase
{
public:
    explicit Predictions();
};


class NAROBCORESHARED_EXPORT Prediction : public DbRecordBase
{
public:
    explicit Prediction();
    void predictClocks(bool allForVehicle,
                       bool allForTrack,
                       TicketsModel *ticketsModel);
    double windCorrection(Ticket *ticket);
    double weightCorrection(Ticket *ticket);

private:
    QVector<Ticket*> validTickets(const QString &clock);
    void getWeather();
    void predictClock(const QString &clock);

    bool mAllForVehicle;
    bool mAllForTrack;
    TicketsModel *mTicketsModel;
//    QVector<RefPT> mRefPTList;
};


class NAROBCORESHARED_EXPORT PredictionsModel : public ModelBase
{
    Q_OBJECT

public:
    explicit PredictionsModel(Vehicle *vehicle,
                              Race *race,
                              int ticketId,
                              QObject *parent);
    QVariant data(const QModelIndex &item, int role) const;

private:
    Vehicle *mVehicle;
    Race *mRace;
    int mTicketId;
};

#endif // PREDICTIONS_H
