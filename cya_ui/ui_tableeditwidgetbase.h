/********************************************************************************
** Form generated from reading UI file 'tableeditwidgetbase.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TABLEEDITWIDGETBASE_H
#define UI_TABLEEDITWIDGETBASE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TableEditWidgetBase
{
public:
    QGridLayout *gridLayout;
    QLabel *title;
    QTableView *tableView;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QPushButton *addButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *editButton;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *deleteButton;

    void setupUi(QWidget *TableEditWidgetBase)
    {
        if (TableEditWidgetBase->objectName().isEmpty())
            TableEditWidgetBase->setObjectName(QString::fromUtf8("TableEditWidgetBase"));
        TableEditWidgetBase->resize(400, 300);
        gridLayout = new QGridLayout(TableEditWidgetBase);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        title = new QLabel(TableEditWidgetBase);
        title->setObjectName(QString::fromUtf8("title"));
        QFont font;
        font.setPointSize(25);
        font.setBold(true);
        font.setWeight(75);
        title->setFont(font);

        gridLayout->addWidget(title, 0, 0, 1, 1, Qt::AlignHCenter);

        tableView = new QTableView(TableEditWidgetBase);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        QFont font1;
        font1.setPointSize(9);
        tableView->setFont(font1);

        gridLayout->addWidget(tableView, 1, 0, 1, 1);

        frame = new QFrame(TableEditWidgetBase);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        addButton = new QPushButton(frame);
        addButton->setObjectName(QString::fromUtf8("addButton"));

        horizontalLayout->addWidget(addButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        editButton = new QPushButton(frame);
        editButton->setObjectName(QString::fromUtf8("editButton"));

        horizontalLayout->addWidget(editButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        deleteButton = new QPushButton(frame);
        deleteButton->setObjectName(QString::fromUtf8("deleteButton"));

        horizontalLayout->addWidget(deleteButton);


        gridLayout->addWidget(frame, 2, 0, 1, 1);

        QWidget::setTabOrder(tableView, addButton);
        QWidget::setTabOrder(addButton, editButton);
        QWidget::setTabOrder(editButton, deleteButton);

        retranslateUi(TableEditWidgetBase);

        QMetaObject::connectSlotsByName(TableEditWidgetBase);
    } // setupUi

    void retranslateUi(QWidget *TableEditWidgetBase)
    {
        TableEditWidgetBase->setWindowTitle(QApplication::translate("TableEditWidgetBase", "Form", nullptr));
        title->setText(QApplication::translate("TableEditWidgetBase", "TextLabel", nullptr));
        addButton->setText(QApplication::translate("TableEditWidgetBase", "Add", nullptr));
        editButton->setText(QApplication::translate("TableEditWidgetBase", "Edit", nullptr));
        deleteButton->setText(QApplication::translate("TableEditWidgetBase", "Delete", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TableEditWidgetBase: public Ui_TableEditWidgetBase {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TABLEEDITWIDGETBASE_H
