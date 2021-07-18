/********************************************************************************
** Form generated from reading UI file 'racedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RACEDIALOG_H
#define UI_RACEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_RaceDialog
{
public:
    QFormLayout *formLayout;
    QLabel *dateLabel;
    QDialogButtonBox *buttonBox;
    QLineEdit *nameEdit;
    QComboBox *trackComboBox;
    QLabel *nameLabel;
    QLabel *trackLabel;
    QDateEdit *dateEdit;

    void setupUi(QDialog *RaceDialog)
    {
        if (RaceDialog->objectName().isEmpty())
            RaceDialog->setObjectName(QString::fromUtf8("RaceDialog"));
        RaceDialog->resize(400, 300);
        formLayout = new QFormLayout(RaceDialog);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        dateLabel = new QLabel(RaceDialog);
        dateLabel->setObjectName(QString::fromUtf8("dateLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, dateLabel);

        buttonBox = new QDialogButtonBox(RaceDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        formLayout->setWidget(4, QFormLayout::SpanningRole, buttonBox);

        nameEdit = new QLineEdit(RaceDialog);
        nameEdit->setObjectName(QString::fromUtf8("nameEdit"));

        formLayout->setWidget(1, QFormLayout::FieldRole, nameEdit);

        trackComboBox = new QComboBox(RaceDialog);
        trackComboBox->setObjectName(QString::fromUtf8("trackComboBox"));

        formLayout->setWidget(2, QFormLayout::FieldRole, trackComboBox);

        nameLabel = new QLabel(RaceDialog);
        nameLabel->setObjectName(QString::fromUtf8("nameLabel"));

        formLayout->setWidget(1, QFormLayout::LabelRole, nameLabel);

        trackLabel = new QLabel(RaceDialog);
        trackLabel->setObjectName(QString::fromUtf8("trackLabel"));

        formLayout->setWidget(2, QFormLayout::LabelRole, trackLabel);

        dateEdit = new QDateEdit(RaceDialog);
        dateEdit->setObjectName(QString::fromUtf8("dateEdit"));

        formLayout->setWidget(0, QFormLayout::FieldRole, dateEdit);

        QWidget::setTabOrder(dateEdit, nameEdit);
        QWidget::setTabOrder(nameEdit, trackComboBox);

        retranslateUi(RaceDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), RaceDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), RaceDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(RaceDialog);
    } // setupUi

    void retranslateUi(QDialog *RaceDialog)
    {
        RaceDialog->setWindowTitle(QApplication::translate("RaceDialog", "Race", nullptr));
        dateLabel->setText(QApplication::translate("RaceDialog", "Date", nullptr));
        nameLabel->setText(QApplication::translate("RaceDialog", "Name", nullptr));
        trackLabel->setText(QApplication::translate("RaceDialog", "Track", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RaceDialog: public Ui_RaceDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RACEDIALOG_H
