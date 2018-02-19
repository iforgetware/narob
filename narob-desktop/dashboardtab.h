#ifndef DASHBOARDTAB_H
#define DASHBOARDTAB_H

#include <QWidget>

#include "vehicle.h"
#include "race.h"
#include "track.h"

namespace Ui {
class DashboardTab;
}

class DashboardTab : public QWidget
{
    Q_OBJECT

public:
    explicit DashboardTab(QWidget *parent = 0);
    ~DashboardTab();

private:
    Ui::DashboardTab *ui;

private slots:
    void onOpenRaceControlButtonClicked();

signals:
    void openRaceControl(Vehicle *vehicle, Race *race);
};

#endif // DASHBOARDTAB_H
