#ifndef VEHICLEDIALOG_H
#define VEHICLEDIALOG_H

#include <QDialog>
#include <QDataWidgetMapper>

#include "vehicles.h"

namespace Ui {
class VehicleDialog;
}

class VehicleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit VehicleDialog(int row = -1, QWidget *parent = 0);
    ~VehicleDialog();

signals:
    void ready();

private slots:
    void onButtonBoxAccepted();

private:
    Ui::VehicleDialog *ui;
    VehiclesModel *mVehiclesModel;

    QDataWidgetMapper * mMapper;

    void setupModel();
    void createUi();
};

#endif // VEHICLEDIALOG_H
