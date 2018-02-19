#include "vehicledialog.h"
#include "ui_vehicledialog.h"

VehicleDialog::VehicleDialog(VehiclesModel *model, int row, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VehicleDialog),
    mVehiclesModel(model)
{
    ui->setupUi(this);

    setupModel();

    if(row == -1){
        Vehicle vehicle;
        QModelIndex tIdx = mVehiclesModel->addVehicle(vehicle);
        mVehiclesModel->select();
        mMapper->setCurrentModelIndex(tIdx);
        connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &VehicleDialog::clearEmptyAdd);
    }else{
        mMapper->setCurrentModelIndex(mVehiclesModel->index(row, 0));
    }

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &VehicleDialog::onButtonBoxAccepted);

    createUi();
}

VehicleDialog::~VehicleDialog()
{
    delete ui;
}

void VehicleDialog::setupModel()
{
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
}

void VehicleDialog::clearEmptyAdd()
{
    mVehiclesModel->removeRow(mVehiclesModel->rowCount()-1);
}
