#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tracks.h"

#include <QDebug>
#include <QFile>
#include <QTextStream>

using namespace std;

typedef struct {
    QString name;
    int pId;
    int m;
    int vm;
    int rm;
    int sm;
    int fm;
} processMem_t;

int getNumFromLine(QString l)
{
    QString num;
    for(int i = 0; i < l.length(); i++){
        QString c = l.mid(i, 1);
        if(c >= '0' && c <= '9'){
            num += c;
        }
    }

    return num.toInt();
}

processMem_t GetProcessMemory()
{
    QFile file("/proc/self/status");

    file.open(QIODevice::ReadOnly);

    QTextStream in(&file);
    QString line = in.readLine();
    processMem_t processMem;


    while (!line.isNull()) {
//        qDebug() << line;
        if(line.mid(0, 5) == "Name:"){
            processMem.name = line.mid(6);
        }else if(line.mid(0,4) == "Pid:"){
            processMem.pId = getNumFromLine(line);
        }else if(line.mid(0,7) == "VmSize:"){
            processMem.vm = getNumFromLine(line);
        }else if(line.mid(0,6) == "VmRSS:"){
            processMem.rm = getNumFromLine(line);
        }else if(line.mid(0,8) == "RssAnon:"){
            processMem.m = getNumFromLine(line);
        }else if(line.mid(0,8) == "RssFile:"){
            processMem.fm = getNumFromLine(line);
        }else if(line.mid(0,9) == "RssShmem:"){
            processMem.sm = getNumFromLine(line);
        }

        line = in.readLine();
    }

    file.close();

    return processMem;
}


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

    connect(ui->settingsTab, &SettingsTab::updateLogbook,
            this, &MainWindow::handleUpdateLogbook);

    connect(ui->settingsTab, &SettingsTab::testWeather,
            this, &MainWindow::handleTestWeather);
    connect(ui->settingsTab, &SettingsTab::testTP,
            this, &MainWindow::handleTestTP);
    connect(ui->settingsTab, &SettingsTab::testWind,
            this, &MainWindow::handleTestWind);
    connect(ui->settingsTab, &SettingsTab::testWeight,
            this, &MainWindow::handleTestWeight);


    // memory usage log

//    memTimer = new QTimer(this);
//    connect(memTimer, &QTimer::timeout,
//            this, &MainWindow::handleMemTimer);
//    memTimer->start(60000);


    QFile outFile("/tmp/narobmem.txt");
    outFile.open(QIODevice::WriteOnly);
    outFile.close();

    ui->tabWidget->setCurrentIndex(ui->tabWidget->indexOf(ui->dashboardTab));

    showMaximized();
}

void MainWindow::handleMemTimer()
{
    processMem_t mem;
    mem = GetProcessMemory();

    QFile outFile("/tmp/narobmem.txt");
    outFile.open(QIODevice::Append);
    QTextStream out(&outFile);

    // output format is
    // hh:mm PhysicalM VirtualM ResidentM SharedM

    out << QTime::currentTime().toString("hh:mm")
        << " "
        << QString::number(mem.m / 1024.0, 'f', 1)
        << " "
        << QString::number(mem.vm / 1024.0, 'f', 1)
        << " "
        << QString::number(mem.rm / 1024.0, 'f', 1)
        << " "
        << QString::number((mem.sm + mem.fm) / 1024.0, 'f', 1)
        << "\n";

    outFile.close();
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

    TracksModel tracksModel;
    Track *track = new Track();

    track = tracksModel.trackForId(race->value("trackId").toInt());

    ui->tabWidget->addTab(raceControlTab,
                          vehicle->value("number").toString()
                          + " @ "
                          + race->value("name").toString()
                          + " @ "
                          + track->value("name").toString());

    ui->tabWidget->setCurrentIndex(ui->tabWidget->indexOf(raceControlTab));
    mRaceControlTabList.append(raceControlTab);

    delete track;
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

void MainWindow::handleUpdateLogbook()
{
    mDBM->updateLogbook();
    updateAllModels();
}

void MainWindow::handleTestWeather()
{
    mDBM->testWeather();
    updateAllModels();
}

void MainWindow::handleTestTP()
{
    mDBM->testTP();
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
