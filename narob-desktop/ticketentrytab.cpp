#include "ticketentrytab.h"
#include "ui_ticketentrytab.h"

TicketEntryTab::TicketEntryTab(TicketsModel* model,
                               std::shared_ptr<Vehicle> vehicle,
                               std::shared_ptr<Race> race,
                               QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TicketEntryTab)
{
    ui->setupUi(this);

    mTicketsEditWidget = new TicketsEditWidget(model,
                                               vehicle,
                                               race,
                                               this);
    ui->gridLayout->addWidget(mTicketsEditWidget, 0, 0);
}

TicketEntryTab::~TicketEntryTab()
{
    delete ui;
}

void TicketEntryTab::updateAllModels()
{
    mTicketsEditWidget->updateModel();
}
