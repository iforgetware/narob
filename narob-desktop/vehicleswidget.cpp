#include "vehicleswidget.h"

#include "vehicledialog.h"

VehiclesWidget::VehiclesWidget(QWidget *parent) : TableEditWidgetBase(parent)
{
    setTitle("Vehicles");

    mVehiclesModel = new VehiclesModel(ui->tableView);

    // are both of these needed?

    mModel = mVehiclesModel;

    ui->tableView->setModel(mVehiclesModel);

    connect(ui->addButton, &QPushButton::clicked,
            this, &VehiclesWidget::addVehicle);

    connect(ui->editButton, &QPushButton::clicked,
            this, &VehiclesWidget::editVehicle);

    connect(ui->deleteButton, &QPushButton::clicked,
            this, &VehiclesWidget::deleteVehicle);

    setupColumns(mVehiclesModel->mFields);

    initTable();
}

void VehiclesWidget::addVehicle()
{
    VehicleDialog *vehicleDialog = new VehicleDialog(mVehiclesModel, -1, this);

    vehicleDialog->exec();
}

void VehiclesWidget::editVehicle()
{
    if(selected()){
        int tRow = getSelection();

        VehicleDialog *vehicleDialog = new VehicleDialog(mVehiclesModel, tRow, this);

        vehicleDialog->exec();
    }
}

void VehiclesWidget::deleteVehicle()
{
    if(selected()){
        int tRow = getSelection();

        mVehiclesModel->removeRow(tRow);
        mVehiclesModel->select();
    }
}

Vehicle *VehiclesWidget::getSelectedVehicle()
{
    return mVehiclesModel->getVehicle(getSelection());
}
