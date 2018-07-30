#ifndef RACECONTROLTAB_H
#define RACECONTROLTAB_H

#include <QWidget>
//#include <QVector>

#include "vehicles.h"
#include "races.h"
#include "tickets.h"
#include "ticketentrytab.h"
#include "trackhistorytab.h"
#include "logbooktab.h"
#include "predictiontab.h"

namespace Ui {
class RaceControlTab;
}

class RaceControlTab : public QWidget
{
    Q_OBJECT

public:
    explicit RaceControlTab(Vehicle *vehicle, Race *race, QWidget *parent = 0);
    ~RaceControlTab();
    void updateAllModels();

private:
    Ui::RaceControlTab *ui;

    Vehicle* mVehicle;
    Race* mRace;
    TicketsModel* mTicketsModel;
    TicketEntryTab *mTicketEntryTab;
    TrackHistoryTab *mTrackHistoryTab;
    LogbookTab *mLogbookTab;
    PredictionTab *mPredictionTab;
};

#endif // RACECONTROLTAB_H
