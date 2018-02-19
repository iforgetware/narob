#ifndef VEHICLEDIALOG_H
#define VEHICLEDIALOG_H

#include <QDialog>
#include <QDataWidgetMapper>
//#include <QMessageBox>

#include "vehiclesmodel.h"

namespace Ui {
class VehicleDialog;
}

class VehicleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit VehicleDialog(VehiclesModel *model, int row = -1, QWidget *parent = 0);
    ~VehicleDialog();

private slots:
    void onButtonBoxAccepted();
    void clearEmptyAdd();

private:
    Ui::VehicleDialog *ui;
    VehiclesModel *mVehiclesModel;

    QDataWidgetMapper * mMapper;

    void setupModel();
    void createUi();
};

#endif // VEHICLEDIALOG_H
