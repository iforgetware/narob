#ifndef RACECONTROLTAB_H
#define RACECONTROLTAB_H

#include <QWidget>

#include "vehicle.h"
#include "race.h"
#include "ticketsmodel.h"

namespace Ui {
class RaceControlTab;
}

class RaceControlTab : public QWidget
{
    Q_OBJECT

public:
    explicit RaceControlTab(Vehicle *vehicle, Race *race, QWidget *parent = 0);
    ~RaceControlTab();

private:
    Ui::RaceControlTab *ui;

    Vehicle* mVehicle;
    Race* mRace;
    TicketsModel* mTicketsModel;

signals:
};

#endif // RACECONTROLTAB_H
