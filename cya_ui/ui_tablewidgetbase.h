/********************************************************************************
** Form generated from reading UI file 'tablewidgetbase.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TABLEWIDGETBASE_H
#define UI_TABLEWIDGETBASE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TableWidgetBase
{
public:
    QGridLayout *gridLayout;
    QTableView *tableView;
    QLabel *title;

    void setupUi(QWidget *TableWidgetBase)
    {
        if (TableWidgetBase->objectName().isEmpty())
            TableWidgetBase->setObjectName(QString::fromUtf8("TableWidgetBase"));
        TableWidgetBase->resize(400, 300);
        gridLayout = new QGridLayout(TableWidgetBase);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tableView = new QTableView(TableWidgetBase);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        QFont font;
        font.setPointSize(9);
        tableView->setFont(font);

        gridLayout->addWidget(tableView, 1, 0, 1, 1);

        title = new QLabel(TableWidgetBase);
        title->setObjectName(QString::fromUtf8("title"));
        QFont font1;
        font1.setPointSize(25);
        font1.setBold(true);
        font1.setWeight(75);
        title->setFont(font1);

        gridLayout->addWidget(title, 0, 0, 1, 1, Qt::AlignHCenter);


        retranslateUi(TableWidgetBase);

        QMetaObject::connectSlotsByName(TableWidgetBase);
    } // setupUi

    void retranslateUi(QWidget *TableWidgetBase)
    {
        TableWidgetBase->setWindowTitle(QApplication::translate("TableWidgetBase", "Form", nullptr));
        title->setText(QApplication::translate("TableWidgetBase", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TableWidgetBase: public Ui_TableWidgetBase {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TABLEWIDGETBASE_H
