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

    hideColumn(mTicketsModel->fieldIndex("vehicleId"));
    hideColumn(mTicketsModel->fieldIndex("trackId"));
    hideColumn(mTicketsModel->fieldIndex("raceId"));
    hideColumn(mTicketsModel->fieldIndex("predictionId"));
}

void TicketsEditWidget::addTicket()
{
    TicketDialog *ticketDialog = new TicketDialog(mVehicle,
                                                  mRace,
                                                  -1,
                                                  this);
    connect(ticketDialog, &TicketDialog::ready,
            this,&TicketsEditWidget::updateModels);

    ticketDialog->exec();
}

void TicketsEditWidget::editTicket()
{
    if(selected()){
        int tRow = getSelection();

        TicketDialog *ticketDialog = new TicketDialog(mVehicle,
                                                      mRace,
                                                      tRow,
                                                      this);
        connect(ticketDialog, &TicketDialog::ready,
                this,&TicketsEditWidget::updateModels);

        ticketDialog->exec();
    }
}
