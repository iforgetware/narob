#include "vehicleswidget.h"

#include "vehicledialog.h"

VehiclesWidget::VehiclesWidget(QWidget *parent) :
    TableEditWidgetBase("Vehicles", parent)
{
    mVehiclesModel = new VehiclesModel(ui->tableView);

    mModel = mVehiclesModel;

    ui->tableView->setModel(mVehiclesModel);







    // add columns for passes since last oil and tire changes






    init();

    connect(mAddButton, &QPushButton::clicked,
            this, &VehiclesWidget::addVehicle);

    connect(mEditButton, &QPushButton::clicked,
            this, &VehiclesWidget::editVehicle);

    connect(ui->tableView, &QTableView::doubleClicked,
            this, &VehiclesWidget::editVehicle);

    setupColumns(VEHICLE_FIELDS);

    hide("weight");
    hide("windAdjustment");
    hide("weightAdjustment");
    hide("textNumber");
    hide("textProvider");
    hide("lastOilChange");
    hide("lastTireChange");
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
        VehicleDialog *vehicleDialog = new VehicleDialog(selectedRow(),
                                                         this);
        connect(vehicleDialog, &VehicleDialog::ready,
                this, &VehiclesWidget::updateModel);

        vehicleDialog->exec();
    }
}

std::shared_ptr<Vehicle> VehiclesWidget::selectedVehicle() const
{
    return mVehiclesModel->vehicleForRow(selectedRow());
}
