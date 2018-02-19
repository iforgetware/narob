#ifndef VEHICLESWIDGET_H
#define VEHICLESWIDGET_H

#include "vehiclesmodel.h"
#include "tableeditwidgetbase.h"
#include "ui_tableeditwidgetbase.h"

class VehiclesWidget : public TableEditWidgetBase
{
    Q_OBJECT

public:
    explicit VehiclesWidget(QWidget *parent = 0);

    Vehicle* getSelectedVehicle();

private slots:
    void addVehicle();
    void editVehicle();
    void deleteVehicle();

private:
    VehiclesModel *mVehiclesModel;
};

#endif // VEHICLESWIDGET_H
