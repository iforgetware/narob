#include "racecontroltab.h"
#include "ui_racecontroltab.h"
#include "tickets.h"

#include <QDebug>

RaceControlTab::RaceControlTab(Vehicle* vehicle,
                               Race* race,
                               QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RaceControlTab),
    mVehicle(vehicle),
    mRace(race),
    mTicketsModel(new TicketsModel(mVehicle, this))
{
    ui->setupUi(this);

    ui->tabWidget->setTabsClosable(false);

    mTicketEntryTab = new TicketEntryTab(mTicketsModel,
                                                        mVehicle,
                                                        mRace,
                                                        this);

    mTrackHistoryTab = new TrackHistoryTab(mTicketsModel,
                                                           mRace->value("trackId").toInt(),
                                                           this);


    mLogbookTab = new LogbookTab(mTicketsModel, this);

    mPredictionTab = new PredictionTab(mTicketsModel,
                                       mVehicle,
                                       mRace,
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
