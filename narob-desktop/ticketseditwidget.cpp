#include    <QDebug>

#include "ticketseditwidget.h"

#include "ticketdialog.h"

TicketsEditWidget::TicketsEditWidget(TicketsModel *model,
                                     Vehicle *vehicle,
                                     Race *race,
                                     QWidget *parent) :
    TableEditWidgetBase(parent),
    mTicketsModel(model),
    mVehicle(vehicle),
    mRace(race)
{
    setTitle("Tickets");

    //mTicketsModel = new TicketsModel(mVehicle, ui->tableView);

    mModel = mTicketsModel;

    mTicketsRaceModel = new TicketsRaceModel(mRace->value("id").toInt(), this);
    mTicketsRaceModel->setSourceModel(mTicketsModel);

    ui->tableView->setModel(mTicketsRaceModel);

    setupColumns(mTicketsModel->fields());

    initTable();

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
        QModelIndex tIndex = getSelectionIndex();
        int tRow = mTicketsRaceModel->mapToSource(tIndex).row();

        TicketDialog *ticketDialog = new TicketDialog(mVehicle,
                                                      mRace,
                                                      tRow,
                                                      this);
        connect(ticketDialog, &TicketDialog::ready,
                this,&TicketsEditWidget::updateModel);

        ticketDialog->exec();
    }
}
