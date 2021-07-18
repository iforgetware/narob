/********************************************************************************
** Form generated from reading UI file 'trackdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRACKDIALOG_H
#define UI_TRACKDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_TrackDialog
{
public:
    QFormLayout *formLayout;
    QLabel *nameLabel;
    QLineEdit *nameEdit;
    QLabel *elevationLabel;
    QLineEdit *elevationEdit;
    QLabel *bearingLabel;
    QLineEdit *bearingEdit;
    QLabel *radioLabel;
    QDialogButtonBox *buttonBox;
    QDoubleSpinBox *radioSpinBox;

    void setupUi(QDialog *TrackDialog)
    {
        if (TrackDialog->objectName().isEmpty())
            TrackDialog->setObjectName(QString::fromUtf8("TrackDialog"));
        TrackDialog->resize(400, 300);
        formLayout = new QFormLayout(TrackDialog);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        nameLabel = new QLabel(TrackDialog);
        nameLabel->setObjectName(QString::fromUtf8("nameLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, nameLabel);

        nameEdit = new QLineEdit(TrackDialog);
        nameEdit->setObjectName(QString::fromUtf8("nameEdit"));

        formLayout->setWidget(0, QFormLayout::FieldRole, nameEdit);

        elevationLabel = new QLabel(TrackDialog);
        elevationLabel->setObjectName(QString::fromUtf8("elevationLabel"));

        formLayout->setWidget(1, QFormLayout::LabelRole, elevationLabel);

        elevationEdit = new QLineEdit(TrackDialog);
        elevationEdit->setObjectName(QString::fromUtf8("elevationEdit"));

        formLayout->setWidget(1, QFormLayout::FieldRole, elevationEdit);

        bearingLabel = new QLabel(TrackDialog);
        bearingLabel->setObjectName(QString::fromUtf8("bearingLabel"));

        formLayout->setWidget(2, QFormLayout::LabelRole, bearingLabel);

        bearingEdit = new QLineEdit(TrackDialog);
        bearingEdit->setObjectName(QString::fromUtf8("bearingEdit"));

        formLayout->setWidget(2, QFormLayout::FieldRole, bearingEdit);

        radioLabel = new QLabel(TrackDialog);
        radioLabel->setObjectName(QString::fromUtf8("radioLabel"));

        formLayout->setWidget(3, QFormLayout::LabelRole, radioLabel);

        buttonBox = new QDialogButtonBox(TrackDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        formLayout->setWidget(4, QFormLayout::SpanningRole, buttonBox);

        radioSpinBox = new QDoubleSpinBox(TrackDialog);
        radioSpinBox->setObjectName(QString::fromUtf8("radioSpinBox"));
        radioSpinBox->setDecimals(1);
        radioSpinBox->setMinimum(87.500000000000000);
        radioSpinBox->setMaximum(107.900000000000006);
        radioSpinBox->setSingleStep(0.200000000000000);

        formLayout->setWidget(3, QFormLayout::FieldRole, radioSpinBox);

        QWidget::setTabOrder(nameEdit, elevationEdit);
        QWidget::setTabOrder(elevationEdit, bearingEdit);
        QWidget::setTabOrder(bearingEdit, radioSpinBox);

        retranslateUi(TrackDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), TrackDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), TrackDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(TrackDialog);
    } // setupUi

    void retranslateUi(QDialog *TrackDialog)
    {
        TrackDialog->setWindowTitle(QApplication::translate("TrackDialog", "Track", nullptr));
        nameLabel->setText(QApplication::translate("TrackDialog", "Name", nullptr));
        elevationLabel->setText(QApplication::translate("TrackDialog", "Elevation", nullptr));
        bearingLabel->setText(QApplication::translate("TrackDialog", "Bearing", nullptr));
        radioLabel->setText(QApplication::translate("TrackDialog", "Radio", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TrackDialog: public Ui_TrackDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRACKDIALOG_H
