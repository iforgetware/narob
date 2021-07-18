/********************************************************************************
** Form generated from reading UI file 'trackhistorytab.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRACKHISTORYTAB_H
#define UI_TRACKHISTORYTAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TrackHistoryTab
{
public:
    QGridLayout *gridLayout;

    void setupUi(QWidget *TrackHistoryTab)
    {
        if (TrackHistoryTab->objectName().isEmpty())
            TrackHistoryTab->setObjectName(QString::fromUtf8("TrackHistoryTab"));
        TrackHistoryTab->resize(735, 585);
        gridLayout = new QGridLayout(TrackHistoryTab);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));

        retranslateUi(TrackHistoryTab);

        QMetaObject::connectSlotsByName(TrackHistoryTab);
    } // setupUi

    void retranslateUi(QWidget *TrackHistoryTab)
    {
        TrackHistoryTab->setWindowTitle(QApplication::translate("TrackHistoryTab", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TrackHistoryTab: public Ui_TrackHistoryTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRACKHISTORYTAB_H
