/********************************************************************************
** Form generated from reading UI file 'logbooktab.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGBOOKTAB_H
#define UI_LOGBOOKTAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LogbookTab
{
public:
    QGridLayout *gridLayout;

    void setupUi(QWidget *LogbookTab)
    {
        if (LogbookTab->objectName().isEmpty())
            LogbookTab->setObjectName(QString::fromUtf8("LogbookTab"));
        LogbookTab->resize(735, 585);
        gridLayout = new QGridLayout(LogbookTab);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));

        retranslateUi(LogbookTab);

        QMetaObject::connectSlotsByName(LogbookTab);
    } // setupUi

    void retranslateUi(QWidget *LogbookTab)
    {
        LogbookTab->setWindowTitle(QApplication::translate("LogbookTab", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LogbookTab: public Ui_LogbookTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGBOOKTAB_H
