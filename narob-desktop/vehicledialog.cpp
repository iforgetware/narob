#include "vehicledialog.h"
#include "ui_vehicledialog.h"

VehicleDialog::VehicleDialog(int row, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VehicleDialog)
{
    ui->setupUi(this);

    setupModel();

    createUi();

    if(row == -1){
        mVehiclesModel->insertRow(mVehiclesModel->rowCount(QModelIndex()));
        mMapper->toLast();
    }else{
        mMapper->setCurrentModelIndex(mVehiclesModel->index(row, 0));
    }

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &VehicleDialog::onButtonBoxAccepted);
}

VehicleDialog::~VehicleDialog()
{
    delete ui;
}

void VehicleDialog::setupModel()
{
    mVehiclesModel = new VehiclesModel(this);

    mMapper = new QDataWidgetMapper(this);
    mMapper->setModel(mVehiclesModel);
    mMapper->addMapping(ui->numberEdit, 1);
    mMapper->addMapping(ui->compClassEdit, 2);
    mMapper->addMapping(ui->weightEdit, 3);

    mMapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
}

void VehicleDialog::createUi()
{
    ui->weightEdit->setValidator(new QIntValidator(ui->weightEdit));
}

void VehicleDialog::onButtonBoxAccepted()
{
    mMapper->submit();
    mVehiclesModel->submitAll();
    emit ready();
}
