#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "vehicle.h"
#include "race.h"

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

    Ui::MainWindow *ui;

public slots:
    void handleOpenRaceControl(Vehicle* vehicle, Race* race);
    void handleStatusUpdate(QString status);
    void handleCloseTab(int index);
};

#endif // MAINWINDOW_H
