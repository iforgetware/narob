#include "racecontroltab.h"
#include "ui_racecontroltab.h"
#include "ticketsmodel.h"
#include "ticketentrytab.h"
#include "trackhistorytab.h"
#include "logbooktab.h"
#include "predictiontab.h"

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

    TicketEntryTab* ticketEntryTab = new TicketEntryTab(mTicketsModel,
                                                        mVehicle,
                                                        mRace,
                                                        this);


    TrackHistoryTab* trackHistoryTab = new TrackHistoryTab(mTicketsModel,
                                                           mRace->trackId(),
                                                           this);


    LogbookTab* logbookTab = new LogbookTab(mTicketsModel, this);

    PredictionTab* predictionTab = new PredictionTab(mTicketsModel,
                                                     mVehicle,
                                                     mRace,
                                                     this);

    ui->tabWidget->addTab(ticketEntryTab, "Ticket Entry");
    ui->tabWidget->addTab(trackHistoryTab, "Track History");
    ui->tabWidget->addTab(logbookTab, "Logbook");
    ui->tabWidget->addTab(predictionTab, "Predictions");
}

RaceControlTab::~RaceControlTab()
{
    delete ui;
}
