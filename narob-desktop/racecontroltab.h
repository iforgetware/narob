#ifndef RACECONTROLTAB_H
#define RACECONTROLTAB_H

#include <memory>

#include <QWidget>

#include "vehicles.h"
#include "races.h"
#include "tickets.h"
#include "ticketentrytab.h"
#include "trackhistorytab.h"
#include "logbooktab.h"
#include "predictiontab.h"
#include "calculatortab.h"

namespace Ui {
class RaceControlTab;
}

class RaceControlTab : public QWidget
{
    Q_OBJECT

public:
    explicit RaceControlTab(std::shared_ptr<Vehicle> vehicle,
                            std::shared_ptr<Race> race,
                            QWidget *parent = nullptr);
    ~RaceControlTab();
    void updateAllModels();

private:
    Ui::RaceControlTab *ui;

    TicketsModel* mTicketsModel;
    TicketEntryTab *mTicketEntryTab;
    TrackHistoryTab *mTrackHistoryTab;
    LogbookTab *mLogbookTab;
    PredictionTab *mPredictionTab;
    CalculatorTab *mCalculatorTab;
};

#endif // RACECONTROLTAB_H
