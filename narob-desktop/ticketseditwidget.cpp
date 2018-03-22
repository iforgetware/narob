#include "ticketseditwidget.h"

#include "ticketdialog.h"

#include "delegates.h"

TicketsEditWidget::TicketsEditWidget(Vehicle *vehicle,
                                     Race *race,
                                     QWidget *parent) :
    TableEditWidgetBase(parent),
    mVehicle(vehicle),
    mRace(race)
{
    setTitle("Tickets");

    mTicketsModel = new TicketsModel(mVehicle, ui->tableView);

    mModel = mTicketsModel;

    mTicketsRaceModel = new TicketsRaceModel(mRace->value("id"), this);
    mTicketsRaceModel->setSourceModel(mTicketsModel);

    ui->tableView->setModel(mTicketsRaceModel);

    setupColumns(mTicketsModel->mFields);

    initTable();

    connect(ui->addButton, &QPushButton::clicked,
            this, &TicketsEditWidget::addTicket);

    connect(ui->editButton, &QPushButton::clicked,
            this, &TicketsEditWidget::editTicket);

    connect(ui->deleteButton, &QPushButton::clicked,
            this, &TicketsEditWidget::deleteTicket);

    connect(ui->tableView, &QTableView::doubleClicked,
            this, &TicketsEditWidget::editTrack);

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

void TicketsEditWidget::deleteTicket()
{
    if(selected()){
        int tRow = getSelection();

        mTicketsRaceModel->removeRow(tRow);
        mTicketsModel->select();
        updateModels();
    }
}

void TicketsEditWidget::updateModels()
{
    mTicketsModel->select();
}
