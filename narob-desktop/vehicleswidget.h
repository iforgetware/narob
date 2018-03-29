#ifndef VEHICLESWIDGET_H
#define VEHICLESWIDGET_H

#include "vehicles.h"
#include "tableeditwidgetbase.h"
#include "ui_tablewidgetbase.h"

class VehiclesWidget : public TableEditWidgetBase
{
    Q_OBJECT

public:
    explicit VehiclesWidget(QWidget *parent = 0);

    Vehicle* getSelectedVehicle();

private slots:
    void addVehicle();
    void editVehicle();

private:
    VehiclesModel *mVehiclesModel;
};

#endif // VEHICLESWIDGET_H
