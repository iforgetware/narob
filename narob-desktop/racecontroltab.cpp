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
    mLogbookTab(new LogbookTab(mTicketsLogbookModel,
                               this)),
    mAutoTab(new AutoTab(mTicketsLogbookModel,
                         vehicle,
                         race,
                         this)),
    mManualTab(new ManualTab(mTicketsLogbookModel,
                             vehicle,
                             race,
                             this))
{
    ui->setupUi(this);

    ui->tabWidget->setTabsClosable(false);

    ui->tabWidget->addTab(mTicketEntryTab, "Ticket Entry");
    ui->tabWidget->addTab(mTrackHistoryTab, "Track History");
    ui->tabWidget->addTab(mLogbookTab, "Logbook");
    ui->tabWidget->addTab(mAutoTab, "Auto Predictions");
    ui->tabWidget->addTab(mManualTab, "Manual Prediction");

    connect(mTicketEntryTab, &TicketEntryTab::ticketsUpdated,
            this, &RaceControlTab::updateAllModels);

    connect(mAutoTab, &AutoTab::selectionUpdated,
            this, &RaceControlTab::updateAllModels);
}

RaceControlTab::~RaceControlTab()
{
    delete mTicketsLogbookModel;

    delete mTicketEntryTab;
    delete mTrackHistoryTab;
    delete mLogbookTab;
    delete mAutoTab;
    delete mManualTab;

    delete ui;
}

void RaceControlTab::updateAllModels()
{
    mTicketEntryTab->updateAllModels();
    mTrackHistoryTab->updateAllModels();
    mLogbookTab->updateAllModels();
    mAutoTab->updateAllModels();
    mManualTab->updateAllModels();
    qDebug("race control tab update all models");
}
