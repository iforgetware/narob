/********************************************************************************
** Form generated from reading UI file 'ticketentrytab.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TICKETENTRYTAB_H
#define UI_TICKETENTRYTAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TicketEntryTab
{
public:
    QGridLayout *gridLayout;

    void setupUi(QWidget *TicketEntryTab)
    {
        if (TicketEntryTab->objectName().isEmpty())
            TicketEntryTab->setObjectName(QString::fromUtf8("TicketEntryTab"));
        TicketEntryTab->resize(400, 300);
        gridLayout = new QGridLayout(TicketEntryTab);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));

        retranslateUi(TicketEntryTab);

        QMetaObject::connectSlotsByName(TicketEntryTab);
    } // setupUi

    void retranslateUi(QWidget *TicketEntryTab)
    {
        TicketEntryTab->setWindowTitle(QApplication::translate("TicketEntryTab", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TicketEntryTab: public Ui_TicketEntryTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TICKETENTRYTAB_H
