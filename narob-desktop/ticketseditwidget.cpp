#include    <QDebug>

#include "ticketseditwidget.h"

#include "ticketdialog.h"

TicketsEditWidget::TicketsEditWidget(TicketsLogbookModel *tLModel,
                                     std::shared_ptr<Vehicle> vehicle,
                                     std::shared_ptr<Race> race,
                                     QWidget *parent) :
    TableEditWidgetBase("Tickets", parent),
    mTicketsLogbookModel(tLModel),
    mTicketsRaceModel(new TicketsRaceModel(vehicle->value("id").toInt(),
                                           race->value("id").toInt(),
                                           this)),
    mVehicle(vehicle),
    mRace(race)
{
    mModel = mTicketsRaceModel;

    ui->tableView->setModel(mTicketsRaceModel);

    init();

    connect(mAddButton, &QPushButton::clicked,
            this, &TicketsEditWidget::addTicket);

    connect(mEditButton, &QPushButton::clicked,
            this, &TicketsEditWidget::editTicket);

    connect(ui->tableView, &QTableView::doubleClicked,
            this, &TicketsEditWidget::editTicket);

    setupColumns(TICKET_FIELDS);

    hide("vehicleId");
    hide("trackId");
    hide("raceId");
    hide("predictionId");

    mModel->sort(mModel->fieldIndex("dateTime"), Qt::DescendingOrder);
}

void TicketsEditWidget::addTicket()
{
    TicketDialog *ticketDialog = new TicketDialog(mTicketsLogbookModel,
                                                  mTicketsRaceModel,
                                                  mVehicle,
                                                  mRace,
                                                  -1,
                                                  this);
    connect(ticketDialog, &TicketDialog::ready,
            this,&TicketsEditWidget::updateModel);

    ticketDialog->exec();
    emit rowsUpdated();
}

void TicketsEditWidget::editTicket()
{
    if(selected()){
        TicketDialog *ticketDialog = new TicketDialog(mTicketsLogbookModel,
                                                      mTicketsRaceModel,
                                                      mVehicle,
                                                      mRace,
                                                      selectedRow(),
                                                      this);
        connect(ticketDialog, &TicketDialog::ready,
                this,&TicketsEditWidget::updateModel);

        ticketDialog->exec();
        emit rowsUpdated();
    }
}
