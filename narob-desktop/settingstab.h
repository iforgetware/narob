#ifndef SETTINGSTAB_H
#define SETTINGSTAB_H

#include "settings.h"

#include <QWidget>

namespace Ui {
class SettingsTab;
}

class SettingsTab : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsTab(QWidget *parent = 0);
    ~SettingsTab();

private:
    Ui::SettingsTab *ui;

    Settings *mSettingsTable;
    DbRecordBase *mSettings;
//    SettingsModel *mSettingsModel;

//    Setting *mSetting;

private slots:
    void onSaveButtonClicked();
    void onClearButtonClicked();
    void displayUpdate();
};

#endif // SETTINGSTAB_H
