#include "racecontroltab.h"
#include "ui_racecontroltab.h"
#include "tickets.h"

#include <QDebug>

RaceControlTab::RaceControlTab(std::shared_ptr<Vehicle> vehicle,
                               std::shared_ptr<Race> race,
                               QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RaceControlTab),
    mTicketsModel(new TicketsModel(vehicle->value("id").toInt(),
                                   this))
{
    ui->setupUi(this);

    ui->tabWidget->setTabsClosable(false);

    mTicketEntryTab = new TicketEntryTab(mTicketsModel,
                                         vehicle,
                                         race,
                                         this);

    mTrackHistoryTab = new TrackHistoryTab(mTicketsModel,
                                           race->value("trackId").toInt(),
                                           this);

    mLogbookTab = new LogbookTab(mTicketsModel, this);

    mPredictionTab = new PredictionTab(mTicketsModel,
                                       vehicle,
                                       race,
                                       this);

    ui->tabWidget->addTab(mTicketEntryTab, "Ticket Entry");
    ui->tabWidget->addTab(mTrackHistoryTab, "Track History");
    ui->tabWidget->addTab(mLogbookTab, "Logbook");
    ui->tabWidget->addTab(mPredictionTab, "Predictions");
}

RaceControlTab::~RaceControlTab()
{
    delete mPredictionTab;
    delete ui;
}

void RaceControlTab::updateAllModels()
{
    mTicketEntryTab->updateAllModels();
    mTrackHistoryTab->updateAllModels();
    mLogbookTab->updateAllModels();
    mPredictionTab->UpdateAllModels();
}
