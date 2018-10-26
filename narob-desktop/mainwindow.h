#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

#include "vehicles.h"
#include "races.h"
#include "databasemanager.h"
#include "racecontroltab.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void init();
    void updateAllModels();

    DatabaseManager *mDBM;

    Ui::MainWindow *ui;
    QVector<RaceControlTab*> mRaceControlTabList;

public slots:
    void handleOpenRaceControl(Vehicle* vehicle, Race* race);
    void handleStatusUpdate(QString status);
    void handleCloseTab(int index);

    void handleUpdateLogbook();
    void handleTestWeather();
    void handleTestTP();
    void handleTestWind();
    void handleTestWeight();
};

#endif // MAINWINDOW_H
