#include "ticketentrytab.h"
#include "ui_ticketentrytab.h"

// #include "racecontroltab.h"

TicketEntryTab::TicketEntryTab(TicketsLogbookModel* tLModel,
                               std::shared_ptr<Vehicle> vehicle,
                               std::shared_ptr<Race> race,
                               QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TicketEntryTab),
    mTicketsLogbookModel(tLModel)
{
    ui->setupUi(this);


    mTicketsEditWidget = new TicketsEditWidget(mTicketsLogbookModel,
                                               vehicle,
                                               race,
                                               this);
    ui->gridLayout->addWidget(mTicketsEditWidget, 0, 0);

    connect(mTicketsEditWidget, &TicketsEditWidget::rowsUpdated,
            this, &TicketEntryTab::ticketsUpdated);
}

TicketEntryTab::~TicketEntryTab()
{
    delete ui;
}

void TicketEntryTab::updateAllModels()
{
    mTicketsEditWidget->updateModel();
    qDebug("tickets edit tab update all models");
}


