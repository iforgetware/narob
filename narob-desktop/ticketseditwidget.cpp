#include    <QDebug>

#include "ticketseditwidget.h"

#include "ticketdialog.h"

TicketsEditWidget::TicketsEditWidget(TicketsModel *model,
                                     std::shared_ptr<Vehicle> vehicle,
                                     std::shared_ptr<Race> race,
                                     QWidget *parent) :
    TableEditWidgetBase("Tickets", parent),
    mTicketsModel(model),
    mVehicle(vehicle),
    mRace(race)
{
    mModel = mTicketsModel;

    mTicketsRaceModel = new TicketsRaceModel(mRace->value("id").toInt(), this);
    mTicketsRaceModel->setSourceModel(mTicketsModel);

    ui->tableView->setModel(mTicketsRaceModel);

    init();

    setupColumns(TICKET_FIELDS);

    connect(mAddButton, &QPushButton::clicked,
            this, &TicketsEditWidget::addTicket);

    connect(mEditButton, &QPushButton::clicked,
            this, &TicketsEditWidget::editTicket);

    connect(ui->tableView, &QTableView::doubleClicked,
            this, &TicketsEditWidget::editTicket);

    hide("vehicleId");
    hide("trackId");
    hide("raceId");
    hide("predictionId");
}

void TicketsEditWidget::addTicket()
{
    TicketDialog *ticketDialog = new TicketDialog(mVehicle,
                                                  mRace,
                                                  -1,
                                                  this);
    connect(ticketDialog, &TicketDialog::ready,
            this,&TicketsEditWidget::updateModel);

    ticketDialog->exec();
}

void TicketsEditWidget::editTicket()
{
    if(selected()){
        TicketDialog *ticketDialog = new TicketDialog(mVehicle,
                                                      mRace,
                                                      selectedRow(),
                                                      this);
        connect(ticketDialog, &TicketDialog::ready,
                this,&TicketsEditWidget::updateModel);

        ticketDialog->exec();
    }
}
