#include "ticketentrytab.h"
#include "ui_ticketentrytab.h"
#include "ticketseditwidget.h"

TicketEntryTab::TicketEntryTab(TicketsModel* model,
                               Vehicle* vehicle,
                               Race* race,
                               QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TicketEntryTab)
{
    ui->setupUi(this);

    TicketsEditWidget *ticketsEditWidget = new TicketsEditWidget(model,
                                                                 vehicle,
                                                                 race,
                                                                 this);
    ui->gridLayout->addWidget(ticketsEditWidget, 0, 0);
}

TicketEntryTab::~TicketEntryTab()
{
    delete ui;
}
