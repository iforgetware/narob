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

private slots:
    void onSaveButtonClicked();
    void onClearButtonClicked();
    void onUpdateLogbookButtonClicked();
    void onCleanDatabaseButtonClicked();
    void onTestWeatherButtonClicked();
    void onTestTPButtonClicked();
    void onTestWindButtonClicked();
    void onTestWeightButtonClicked();
    void displayUpdate();

signals:
    void updateLogbook();
    void testWeather();
    void testTP();
    void testWind();
    void testWeight();
};

#endif // SETTINGSTAB_H
