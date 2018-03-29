#include "dashboardtab.h"
#include "ui_dashboardtab.h"

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








        // write racesmodel->getTrackId accessor
        // use this to get id for tickets and predictions etc.
        // possibly only pass race and track id's instead of whole objects








        emit openRaceControl(ui->vehiclesWidget->getSelectedVehicle(),
                                ui->racesWidget->getSelectedRace());
    }else{
        qDebug("Vehicle and Race not selected - WRITE CODE");
    }
}

