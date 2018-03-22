#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "vehicles.h"
#include "races.h"
#include "databasemanager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void init();

    DatabaseManager *mDBM;

    Ui::MainWindow *ui;

public slots:
    void handleOpenRaceControl(Vehicle* vehicle, Race* race);
    void handleStatusUpdate(QString status);
    void handleCloseTab(int index);
};

#endif // MAINWINDOW_H
