#ifndef VEHICLEDIALOG_H
#define VEHICLEDIALOG_H

#include "dialogbase.h"
#include "vehicles.h"
#include "settings.h"

namespace Ui {
class VehicleDialog;
}

class VehicleDialog : public DialogBase
{
    Q_OBJECT

public:
    explicit VehicleDialog(int row = -1,
                           QWidget *parent = 0);
    ~VehicleDialog();

private:
    Ui::VehicleDialog *ui;

    void setupModel();
    void createUi();

    Settings *mSettingsTable;
    DbRecordBase *mSettings;
};

#endif // VEHICLEDIALOG_H
