#ifndef DASHBOARDTAB_H
#define DASHBOARDTAB_H

#include <memory>

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
    explicit DashboardTab(QWidget *parent = nullptr);
    ~DashboardTab();
    void updateAllModels();

private:
    Ui::DashboardTab *ui;

private slots:
    void onOpenRaceControlButtonClicked();

signals:
    void openRaceControl(std::shared_ptr<Vehicle>,
                         std::shared_ptr<Race>);
};

#endif // DASHBOARDTAB_H
