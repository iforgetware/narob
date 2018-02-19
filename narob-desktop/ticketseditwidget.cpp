#include "ticketseditwidget.h"

#include "ticketsracemodel.h"
#include "ticketdialog.h"

#include "delegates.h"

#include <QDebug>
#include <QSqlRecord>

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

    mModel = mTicketsModel;

    mTicketsRaceModel = new TicketsRaceModel(mRace->id(), this);
    mTicketsRaceModel->setSourceModel(mTicketsModel);

    ui->tableView->setModel(mTicketsRaceModel);

    connect(ui->addButton, &QPushButton::clicked,
            this, &TicketsEditWidget::addTicket);

    connect(ui->editButton, &QPushButton::clicked,
            this, &TicketsEditWidget::editTicket);

    connect(ui->deleteButton, &QPushButton::clicked,
            this, &TicketsEditWidget::deleteTicket);

    QSqlRecord row = mTicketsModel->record();
//    qDebug() << row.fieldName(1);
//    qDebug() << row.fieldName(2);
//    qDebug() << row.fieldName(3);
//    qDebug() << row.fieldName(4);

    setupColumns(mTicketsModel->mFields);

    hideColumn(mTicketsModel->fieldIndex("vehicleId"));
    hideColumn(mTicketsModel->fieldIndex("trackId"));
    hideColumn(mTicketsModel->fieldIndex("raceId"));
    hideColumn(mTicketsModel->fieldIndex("predictionId"));

    initTable();
}

void TicketsEditWidget::addTicket()
{
    TicketDialog *ticketDialog = new TicketDialog(mTicketsModel,
                                                  mVehicle,
                                                  mRace,
                                                  -1,
                                                  this);

    ticketDialog->exec();
}

void TicketsEditWidget::editTicket()
{
    if(selected()){
        int tRow = getSelection();

        TicketDialog *ticketDialog = new TicketDialog(mTicketsModel,
                                                      mVehicle,
                                                      mRace,
                                                      tRow,
                                                      this);

        ticketDialog->exec();
    }
}

void TicketsEditWidget::deleteTicket()
{
    if(selected()){
        int tRow = getSelection();

        mTicketsRaceModel->removeRow(tRow);
        mTicketsModel->select();
    }
}
