/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include "dashboardtab.h"
#include "settingstab.h"
#include "weathertab.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QTabWidget *tabWidget;
    DashboardTab *dashboardTab;
    WeatherTab *weatherTab;
    SettingsTab *settingsTab;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1024, 768);
        MainWindow->setMinimumSize(QSize(0, 0));
        tabWidget = new QTabWidget(MainWindow);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        dashboardTab = new DashboardTab();
        dashboardTab->setObjectName(QString::fromUtf8("dashboardTab"));
        tabWidget->addTab(dashboardTab, QString());
        weatherTab = new WeatherTab();
        weatherTab->setObjectName(QString::fromUtf8("weatherTab"));
        tabWidget->addTab(weatherTab, QString());
        settingsTab = new SettingsTab();
        settingsTab->setObjectName(QString::fromUtf8("settingsTab"));
        tabWidget->addTab(settingsTab, QString());
        MainWindow->setCentralWidget(tabWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(dashboardTab), QApplication::translate("MainWindow", "Dashboard", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(weatherTab), QApplication::translate("MainWindow", "Weather", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(settingsTab), QApplication::translate("MainWindow", "Settings", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
