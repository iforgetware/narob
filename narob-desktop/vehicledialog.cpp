#include "vehicledialog.h"
#include "ui_vehicledialog.h"

VehicleDialog::VehicleDialog(int row, QWidget *parent) :
    DialogBase(parent),
    ui(new Ui::VehicleDialog),
    mSettingsTable(new Settings)
{
    ui->setupUi(this);

    setupModel();

    createUi();

    setModelRow(row);

    mSettings = mSettingsTable->getSettings();

    if(row == -1){
        ui->weightAdjustmentSpinBox->setValue(mSettings->value("weightAdjustment").toDouble());
        ui->windAdjustmentSpinBox->setValue(mSettings->value("windAdjustment").toDouble());
        ui->textNumberEdit->setText(mSettings->value("textNumber").toString());
        ui->textProviderComboBox->setCurrentText(mSettings->value("textProvider").toString());
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
}

void VehicleDialog::createUi()
{
    ui->weightEdit->setValidator(new QIntValidator(ui->weightEdit));
}
