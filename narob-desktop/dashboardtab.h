#ifndef DASHBOARDTAB_H
#define DASHBOARDTAB_H

#include <QWidget>

#include "vehicles.h"
#include "races.h"
#include "tracks.h"

namespace Ui {
class DashboardTab;
}

class DashboardTab : public QWidget
{
    Q_OBJECT

public:
    explicit DashboardTab(QWidget *parent = 0);
    ~DashboardTab();
    void updateAllModels();

private:
    Ui::DashboardTab *ui;

private slots:
    void onOpenRaceControlButtonClicked();

signals:
    void openRaceControl(Vehicle *vehicle, Race *race);
};

#endif // DASHBOARDTAB_H
