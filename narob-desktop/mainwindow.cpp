#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    mDBM(new DatabaseManager()),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

   init();

    ui->tabWidget->setTabsClosable(true);

    ui->statusBar->showMessage("Waiting for weather station");

    connect(ui->tabWidget, &QTabWidget::tabCloseRequested,
            this, &MainWindow::handleCloseTab);

    connect(ui->dashboardTab, &DashboardTab::openRaceControl,
            this, &MainWindow::handleOpenRaceControl);
    connect(ui->weatherTab, &WeatherTab::sendStatus,
            this, &MainWindow::handleStatusUpdate);

    connect(ui->settingsTab, &SettingsTab::testWeather,
            this, &MainWindow::handleTestWeather);
    connect(ui->settingsTab, &SettingsTab::testWind,
            this, &MainWindow::handleTestWind);
    connect(ui->settingsTab, &SettingsTab::testWeight,
            this, &MainWindow::handleTestWeight);

    ui->tabWidget->setCurrentIndex(ui->tabWidget->indexOf(ui->dashboardTab));

    showMaximized();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    // Connect SQL logging and database state setting to main window
    //connect(&db, SIGNAL(dbChanged(bool)), this, SLOT(dbState(bool)));
    //connect(&db, SIGNAL(sqlExecuted(QString, int)), this, SLOT(logSql(QString,int)));

    setWindowTitle(QApplication::applicationName() + " by " + QApplication::organizationName());
}

void MainWindow::updateAllModels()
{
    ui->dashboardTab->updateAllModels();
    ui->weatherTab->updateAllModels();

    foreach(RaceControlTab *raceControlTab, mRaceControlTabList){
        raceControlTab->updateAllModels();
    }
}

void MainWindow::handleOpenRaceControl(Vehicle* vehicle, Race* race)
{
    RaceControlTab *raceControlTab = new RaceControlTab(vehicle, race, this);

    ui->tabWidget->addTab(raceControlTab,
                          vehicle->value("number").toString()
                          + " @ "
                          + race->value("name").toString());

    ui->tabWidget->setCurrentIndex(ui->tabWidget->indexOf(raceControlTab));
    mRaceControlTabList.append(raceControlTab);
}

void MainWindow::handleStatusUpdate(QString status)
{
    ui->statusBar->showMessage(status);
}

void MainWindow::handleCloseTab(int index)
{
    if(index != ui->tabWidget->indexOf(ui->dashboardTab)
       && index != ui->tabWidget->indexOf(ui->weatherTab)
       && index != ui->tabWidget->indexOf(ui->settingsTab)){
        delete ui->tabWidget->widget(index);
    }
}

void MainWindow::handleTestWeather()
{
    mDBM->testWeather();
    updateAllModels();
}

void MainWindow::handleTestWind()
{
    mDBM->testWind();
    updateAllModels();
}

void MainWindow::handleTestWeight()
{
    mDBM->testWeight();
    updateAllModels();
}
