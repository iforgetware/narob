#include "vehicledialog.h"
#include "ui_vehicledialog.h"
#include "tickets.h"

#include "settings.h"

VehicleDialog::VehicleDialog(int row, QWidget *parent) :
    DialogBase(parent),
    ui(new Ui::VehicleDialog)
{
    ui->setupUi(this);

    setupModel();

    createUi();

    setModelRow(row);

    if(row == -1){
        ui->weightAdjustmentSpinBox->setValue(Settings::get("weightAdjustment").toDouble());
        ui->windAdjustmentSpinBox->setValue(Settings::get("windAdjustment").toDouble());
        ui->textNumberEdit->setText(Settings::get("textNumber").toString());
        ui->textProviderComboBox->setCurrentText(Settings::get("textProvider").toString());
    }

    connect(ui->buttonBox, &QDialogButtonBox::accepted,
            this, &DialogBase::onButtonBoxAccepted);

    connect(ui->lastOilChangeEdit, &QDateTimeEdit::dateTimeChanged,
            this, &VehicleDialog::updateRunCounts);

    connect(ui->lastTireChangeEdit, &QDateTimeEdit::dateTimeChanged,
            this, &VehicleDialog::updateRunCounts);

    updateRunCounts();
}

VehicleDialog::~VehicleDialog()
{
    delete ui;
}

void VehicleDialog::setupModel()
{
    mModel = new VehiclesModel(this);

    mMapper->setModel(mModel);
    mMapper->addMapping(ui->numberEdit, mModel->fieldIndex("number"));
    mMapper->addMapping(ui->compClassEdit, mModel->fieldIndex("compClass"));
    mMapper->addMapping(ui->weightEdit, mModel->fieldIndex("weight"));
    mMapper->addMapping(ui->windAdjustmentSpinBox, mModel->fieldIndex("windAdjustment"));
    mMapper->addMapping(ui->weightAdjustmentSpinBox, mModel->fieldIndex("weightAdjustment"));
    mMapper->addMapping(ui->textNumberEdit, mModel->fieldIndex("textNumber"));
    mMapper->addMapping(ui->textProviderComboBox, mModel->fieldIndex("textProvider"));
    mMapper->addMapping(ui->lastOilChangeEdit, mModel->fieldIndex("lastOilChange"));
    mMapper->addMapping(ui->lastTireChangeEdit, mModel->fieldIndex("lastTireChange"));
}

void VehicleDialog::createUi()
{
    ui->weightEdit->setValidator(new QIntValidator(ui->weightEdit));
}

void VehicleDialog::updateRunCounts(){
    int vehicleId = indexForField("id").data().toInt();

    TicketsModel ticketsModel(vehicleId, this);

    int oR = ticketsModel.ticketsSinceDateTime(ui->lastOilChangeEdit->dateTime());
    int tR = ticketsModel.ticketsSinceDateTime(ui->lastTireChangeEdit->dateTime());

    ui->lastOilRunsLabel->setText(QString::number(oR));
    ui->lastTireRunsLabel->setText(QString::number(tR));
}
