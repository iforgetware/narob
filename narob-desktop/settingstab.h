#ifndef SETTINGSTAB_H
#define SETTINGSTAB_H

#include "settingsmodel.h"

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

    SettingsModel *mSettingsModel;

    Settings *mSettings;

private slots:
    void onSaveButtonClicked();
    void onClearButtonClicked();
    void displayUpdate();
};

#endif // SETTINGSTAB_H
