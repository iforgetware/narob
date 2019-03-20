#include "vehicledialog.h"
#include "ui_vehicledialog.h"

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

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &DialogBase::onButtonBoxAccepted);
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
