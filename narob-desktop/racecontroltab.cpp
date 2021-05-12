#include "racecontroltab.h"
#include "ui_racecontroltab.h"
#include "tickets.h"

#include <QDebug>

RaceControlTab::RaceControlTab(std::shared_ptr<Vehicle> vehicle,
                               std::shared_ptr<Race> race,
                               QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RaceControlTab),
    mTicketsLogbookModel(new TicketsLogbookModel(vehicle->value("id").toInt(),
                                                 this)),
    mTicketEntryTab(new TicketEntryTab(mTicketsLogbookModel,
                                       vehicle,
                                       race,
                                       this)),
    mTrackHistoryTab(new TrackHistoryTab(vehicle,
                                         race->value("trackId").toInt(),
                                         this)),
    mLogbookTab(new LogbookTab(mTicketsLogbookModel, this)),
    mPredictionTab(new PredictionTab(mTicketsLogbookModel,
                                     vehicle,
                                     race,
                                     this)),
    mCalculatorTab(new CalculatorTab(mTicketsLogbookModel,
                                     vehicle,
                                     race,
                                     this))
{
    ui->setupUi(this);

    ui->tabWidget->setTabsClosable(false);

    ui->tabWidget->addTab(mTicketEntryTab, "Ticket Entry");
    ui->tabWidget->addTab(mTrackHistoryTab, "Track History");
    ui->tabWidget->addTab(mLogbookTab, "Logbook");
    ui->tabWidget->addTab(mPredictionTab, "Predictions");
    ui->tabWidget->addTab(mCalculatorTab, "Calculators");

    connect(mTicketEntryTab, &TicketEntryTab::ticketsUpdated,
            this, &RaceControlTab::updateAllModels);
}

RaceControlTab::~RaceControlTab()
{
    delete mTicketsLogbookModel;

    delete mTicketEntryTab;
    delete mTrackHistoryTab;
    delete mLogbookTab;
    delete mPredictionTab;
    delete mCalculatorTab;

    delete ui;
}

void RaceControlTab::updateAllModels()
{
//    mTicketEntryTab->updateAllModels();
    mTrackHistoryTab->updateAllModels();
    mLogbookTab->updateAllModels();
    mPredictionTab->UpdateAllModels();
}
