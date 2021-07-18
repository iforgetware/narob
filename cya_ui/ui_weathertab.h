/********************************************************************************
** Form generated from reading UI file 'weathertab.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WEATHERTAB_H
#define UI_WEATHERTAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WeatherTab
{
public:
    QGridLayout *gridLayout;

    void setupUi(QWidget *WeatherTab)
    {
        if (WeatherTab->objectName().isEmpty())
            WeatherTab->setObjectName(QString::fromUtf8("WeatherTab"));
        WeatherTab->resize(604, 527);
        gridLayout = new QGridLayout(WeatherTab);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));

        retranslateUi(WeatherTab);

        QMetaObject::connectSlotsByName(WeatherTab);
    } // setupUi

    void retranslateUi(QWidget *WeatherTab)
    {
        WeatherTab->setWindowTitle(QApplication::translate("WeatherTab", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WeatherTab: public Ui_WeatherTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WEATHERTAB_H
