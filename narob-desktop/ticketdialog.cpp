#include "ticketdialog.h"
#include "ui_ticketdialog.h"

TicketDialog::TicketDialog(TicketsModel *model,
                           Vehicle* vehicle,
                           Race* race,
                           int row,
                           QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TicketDialog),
    mTicketsModel(model)
{
    ui->setupUi(this);

    setupModel();

    if(row == -1){
        Ticket ticket;

        ticket.setVehicleId(vehicle->id());
        ticket.setTrackId(race->trackId());
        ticket.setRaceId(race->id());

        QModelIndex idx = mTicketsModel->addTicket(ticket);
        mTicketsModel->select();
        mMapper->setCurrentModelIndex(idx);
        connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &TicketDialog::clearEmptyAdd);
    }else{
        mMapper->setCurrentModelIndex(mTicketsModel->index(row, 0));
    }

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &TicketDialog::onButtonBoxAccepted);

    createUi();
}

TicketDialog::~TicketDialog()
{
    delete ui;
}

void TicketDialog::setupModel()
{
    mMapper = new QDataWidgetMapper(this);

    mMapper->setModel(mTicketsModel);
    mMapper->addMapping(ui->dateEdit, mTicketsModel->fieldIndex("date"));
    mMapper->addMapping(ui->timeEdit, mTicketsModel->fieldIndex("time"));
    mMapper->addMapping(ui->laneComboBox, mTicketsModel->fieldIndex("lane"));
    mMapper->addMapping(ui->dialEdit, mTicketsModel->fieldIndex("dial"));
    mMapper->addMapping(ui->reactionEdit, mTicketsModel->fieldIndex("reaction"));
    mMapper->addMapping(ui->sixtyEdit, mTicketsModel->fieldIndex("sixty"));
    mMapper->addMapping(ui->threeThirtyEdit, mTicketsModel->fieldIndex("threeThirty"));
    mMapper->addMapping(ui->eighthEdit, mTicketsModel->fieldIndex("eighth"));
    mMapper->addMapping(ui->eighthMPHEdit, mTicketsModel->fieldIndex("eighthMPH"));
    mMapper->addMapping(ui->eighthGoodCheckBox, mTicketsModel->fieldIndex("eighthGood"));
    mMapper->addMapping(ui->thousandEdit, mTicketsModel->fieldIndex("thousand"));
    mMapper->addMapping(ui->quarterEdit, mTicketsModel->fieldIndex("quarter"));
    mMapper->addMapping(ui->quarterMPHEdit, mTicketsModel->fieldIndex("quarterMPH"));
    mMapper->addMapping(ui->quarterGoodCheckBox, mTicketsModel->fieldIndex("quarterGood"));
    mMapper->addMapping(ui->delayEdit, mTicketsModel->fieldIndex("delay"));
    mMapper->addMapping(ui->vehicleWeightEdit, mTicketsModel->fieldIndex("vehicleWeight"));
    mMapper->addMapping(ui->riderWeightEdit, mTicketsModel->fieldIndex("riderWeight"));

    mMapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
}

void vInt(QLineEdit *edit)
{
    edit->setValidator(new QIntValidator(edit));
}

void vDouble(QLineEdit *edit, int d)
{
    edit->setValidator(new QDoubleValidator(0, 1000, d, edit));
}

void TicketDialog::createUi()
{
    vDouble(ui->delayEdit, 3);
    vInt(ui->vehicleWeightEdit);
    vDouble(ui->riderWeightEdit, 1);
    ui->laneComboBox->addItems(QStringList() << "Left" << "Right");
    vDouble(ui->dialEdit, 2);
    vDouble(ui->reactionEdit, 3);
    vDouble(ui->sixtyEdit, 3);
    vDouble(ui->threeThirtyEdit, 3);
    vDouble(ui->eighthEdit, 3);
    vDouble(ui->eighthMPHEdit, 2);
    vDouble(ui->thousandEdit, 3);
    vDouble(ui->quarterEdit, 3);
    vDouble(ui->quarterMPHEdit, 2);
}

void TicketDialog::onButtonBoxAccepted()
{
    mMapper->submit();
    mTicketsModel->submitAll();
}

void TicketDialog::clearEmptyAdd()
{
    mTicketsModel->removeRow(mTicketsModel->rowCount()-1);
}
