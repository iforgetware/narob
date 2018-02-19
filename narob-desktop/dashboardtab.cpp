#include "dashboardtab.h"
#include "ui_dashboardtab.h"

#include <QDebug>

DashboardTab::DashboardTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DashboardTab)
{
    ui->setupUi(this);

    connect(ui->openRaceControlButton, &QPushButton::clicked, this, &DashboardTab::onOpenRaceControlButtonClicked);
}

DashboardTab::~DashboardTab()
{
    delete ui;
}

void DashboardTab::onOpenRaceControlButtonClicked()
{
    if(ui->vehiclesWidget->selected() && ui->racesWidget->selected()) {
        emit openRaceControl(ui->vehiclesWidget->getSelectedVehicle(),
                                ui->racesWidget->getSelectedRace());
    }else{
        qDebug("Vehicle and Race not selected - WRITE CODE");
    }
}

