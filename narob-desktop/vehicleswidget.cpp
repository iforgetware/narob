#include "vehicleswidget.h"

#include "vehicledialog.h"

VehiclesWidget::VehiclesWidget(QWidget *parent) :
    TableEditWidgetBase(parent)
{
    setTitle("Vehicles");

    mVehiclesModel = new VehiclesModel(ui->tableView);

    mModel = mVehiclesModel;

    ui->tableView->setModel(mVehiclesModel);

    setupColumns(mVehiclesModel->fields());

    initTable();

    connect(mAddButton, &QPushButton::clicked,
            this, &VehiclesWidget::addVehicle);

    connect(mEditButton, &QPushButton::clicked,
            this, &VehiclesWidget::editVehicle);

    connect(ui->tableView, &QTableView::doubleClicked,
            this, &VehiclesWidget::editVehicle);
}

void VehiclesWidget::addVehicle()
{
    VehicleDialog *vehicleDialog = new VehicleDialog(-1, this);
    connect(vehicleDialog, &VehicleDialog::ready,
            this, &VehiclesWidget::updateModel);

    vehicleDialog->exec();
}

void VehiclesWidget::editVehicle()
{
    if(selected()){
        int tRow = getSelection();

        VehicleDialog *vehicleDialog = new VehicleDialog(tRow, this);
        connect(vehicleDialog, &VehicleDialog::ready,
                this, &VehiclesWidget::updateModel);

        vehicleDialog->exec();
    }
}

Vehicle *VehiclesWidget::getSelectedVehicle()
{
    return mVehiclesModel->getVehicle(getSelection());
}
