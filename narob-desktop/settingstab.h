









// remove maintenance and testing frames
// add color and size to highlight Save and Clear buttons






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
    explicit SettingsTab(QWidget *parent = nullptr);
    ~SettingsTab();

private:
    Ui::SettingsTab *ui;

private slots:
    void onSaveButtonClicked();
    void onClearButtonClicked();
    void onUpdateLogbookButtonClicked();
    void onCleanDatabaseButtonClicked();
    void onUpdateSplitsButtonClicked();
    void onTestWeatherButtonClicked();
    void onTestTPButtonClicked();
    void onTestWindButtonClicked();
    void onTestWeightButtonClicked();
    void displayUpdate();

signals:
    void updateSplits();
    void updateLogbook();
    void testWeather();
    void testTP();
    void testWind();
    void testWeight();
};

#endif // SETTINGSTAB_H
