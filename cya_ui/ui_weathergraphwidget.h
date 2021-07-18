/********************************************************************************
** Form generated from reading UI file 'weathergraphwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WEATHERGRAPHWIDGET_H
#define UI_WEATHERGRAPHWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WeatherGraphWidget
{
public:
    QGridLayout *gridLayout;

    void setupUi(QWidget *WeatherGraphWidget)
    {
        if (WeatherGraphWidget->objectName().isEmpty())
            WeatherGraphWidget->setObjectName(QString::fromUtf8("WeatherGraphWidget"));
        WeatherGraphWidget->resize(400, 300);
        gridLayout = new QGridLayout(WeatherGraphWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));

        retranslateUi(WeatherGraphWidget);

        QMetaObject::connectSlotsByName(WeatherGraphWidget);
    } // setupUi

    void retranslateUi(QWidget *WeatherGraphWidget)
    {
        WeatherGraphWidget->setWindowTitle(QApplication::translate("WeatherGraphWidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WeatherGraphWidget: public Ui_WeatherGraphWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WEATHERGRAPHWIDGET_H
