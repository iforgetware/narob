/********************************************************************************
** Form generated from reading UI file 'racecontroltab.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RACECONTROLTAB_H
#define UI_RACECONTROLTAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RaceControlTab
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;

    void setupUi(QWidget *RaceControlTab)
    {
        if (RaceControlTab->objectName().isEmpty())
            RaceControlTab->setObjectName(QString::fromUtf8("RaceControlTab"));
        RaceControlTab->resize(735, 585);
        verticalLayout = new QVBoxLayout(RaceControlTab);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tabWidget = new QTabWidget(RaceControlTab);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));

        verticalLayout->addWidget(tabWidget);


        retranslateUi(RaceControlTab);

        tabWidget->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(RaceControlTab);
    } // setupUi

    void retranslateUi(QWidget *RaceControlTab)
    {
        RaceControlTab->setWindowTitle(QApplication::translate("RaceControlTab", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RaceControlTab: public Ui_RaceControlTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RACECONTROLTAB_H
