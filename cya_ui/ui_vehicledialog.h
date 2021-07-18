/********************************************************************************
** Form generated from reading UI file 'vehicledialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VEHICLEDIALOG_H
#define UI_VEHICLEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include "providerbox.h"

QT_BEGIN_NAMESPACE

class Ui_VehicleDialog
{
public:
    QGridLayout *gridLayout_2;
    QLabel *numberLabel;
    QLineEdit *numberEdit;
    QLabel *compClassLabel;
    QLineEdit *compClassEdit;
    QLabel *weightLabel;
    QLineEdit *weightEdit;
    QDialogButtonBox *buttonBox;
    QFrame *settingsFrame;
    QGridLayout *gridLayout;
    QGroupBox *predictionDefaults;
    QGridLayout *gridLayout_7;
    QLabel *weightAdjustmentLabel;
    QDoubleSpinBox *weightAdjustmentSpinBox;
    QDoubleSpinBox *windAdjustmentSpinBox;
    ProviderBox *textProviderComboBox;
    QLabel *windAdjustmentLabel;
    QLabel *textProviderLabel;
    QLabel *textNumberLabel;
    QLineEdit *textNumberEdit;
    QFrame *maintenanceFrame;
    QGridLayout *gridLayout_3;
    QGroupBox *maintenanceInfo;
    QGridLayout *gridLayout_4;
    QDateTimeEdit *lastOilChangeEdit;
    QLabel *lastOilChangeLabel;
    QDateTimeEdit *lastTireChangeEdit;
    QLabel *lastOilRunsLabel;
    QLabel *lastTireChangeLabel;
    QLabel *lastTireRunsLabel;

    void setupUi(QDialog *VehicleDialog)
    {
        if (VehicleDialog->objectName().isEmpty())
            VehicleDialog->setObjectName(QString::fromUtf8("VehicleDialog"));
        VehicleDialog->resize(536, 457);
        gridLayout_2 = new QGridLayout(VehicleDialog);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        numberLabel = new QLabel(VehicleDialog);
        numberLabel->setObjectName(QString::fromUtf8("numberLabel"));

        gridLayout_2->addWidget(numberLabel, 0, 0, 1, 1);

        numberEdit = new QLineEdit(VehicleDialog);
        numberEdit->setObjectName(QString::fromUtf8("numberEdit"));

        gridLayout_2->addWidget(numberEdit, 0, 1, 1, 1);

        compClassLabel = new QLabel(VehicleDialog);
        compClassLabel->setObjectName(QString::fromUtf8("compClassLabel"));

        gridLayout_2->addWidget(compClassLabel, 1, 0, 1, 1);

        compClassEdit = new QLineEdit(VehicleDialog);
        compClassEdit->setObjectName(QString::fromUtf8("compClassEdit"));

        gridLayout_2->addWidget(compClassEdit, 1, 1, 1, 1);

        weightLabel = new QLabel(VehicleDialog);
        weightLabel->setObjectName(QString::fromUtf8("weightLabel"));

        gridLayout_2->addWidget(weightLabel, 2, 0, 1, 1);

        weightEdit = new QLineEdit(VehicleDialog);
        weightEdit->setObjectName(QString::fromUtf8("weightEdit"));

        gridLayout_2->addWidget(weightEdit, 2, 1, 1, 1);

        buttonBox = new QDialogButtonBox(VehicleDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout_2->addWidget(buttonBox, 4, 1, 1, 1);

        settingsFrame = new QFrame(VehicleDialog);
        settingsFrame->setObjectName(QString::fromUtf8("settingsFrame"));
        settingsFrame->setFrameShape(QFrame::StyledPanel);
        settingsFrame->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(settingsFrame);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        predictionDefaults = new QGroupBox(settingsFrame);
        predictionDefaults->setObjectName(QString::fromUtf8("predictionDefaults"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(predictionDefaults->sizePolicy().hasHeightForWidth());
        predictionDefaults->setSizePolicy(sizePolicy);
        gridLayout_7 = new QGridLayout(predictionDefaults);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        weightAdjustmentLabel = new QLabel(predictionDefaults);
        weightAdjustmentLabel->setObjectName(QString::fromUtf8("weightAdjustmentLabel"));

        gridLayout_7->addWidget(weightAdjustmentLabel, 2, 0, 1, 1);

        weightAdjustmentSpinBox = new QDoubleSpinBox(predictionDefaults);
        weightAdjustmentSpinBox->setObjectName(QString::fromUtf8("weightAdjustmentSpinBox"));
        weightAdjustmentSpinBox->setDecimals(3);
        weightAdjustmentSpinBox->setMaximum(0.999000000000000);
        weightAdjustmentSpinBox->setSingleStep(0.001000000000000);

        gridLayout_7->addWidget(weightAdjustmentSpinBox, 3, 0, 1, 1);

        windAdjustmentSpinBox = new QDoubleSpinBox(predictionDefaults);
        windAdjustmentSpinBox->setObjectName(QString::fromUtf8("windAdjustmentSpinBox"));
        windAdjustmentSpinBox->setDecimals(3);
        windAdjustmentSpinBox->setMinimum(0.000000000000000);
        windAdjustmentSpinBox->setMaximum(0.999000000000000);
        windAdjustmentSpinBox->setSingleStep(0.001000000000000);

        gridLayout_7->addWidget(windAdjustmentSpinBox, 1, 0, 1, 1);

        textProviderComboBox = new ProviderBox(predictionDefaults);
        textProviderComboBox->setObjectName(QString::fromUtf8("textProviderComboBox"));

        gridLayout_7->addWidget(textProviderComboBox, 7, 0, 1, 1);

        windAdjustmentLabel = new QLabel(predictionDefaults);
        windAdjustmentLabel->setObjectName(QString::fromUtf8("windAdjustmentLabel"));

        gridLayout_7->addWidget(windAdjustmentLabel, 0, 0, 1, 1);

        textProviderLabel = new QLabel(predictionDefaults);
        textProviderLabel->setObjectName(QString::fromUtf8("textProviderLabel"));

        gridLayout_7->addWidget(textProviderLabel, 6, 0, 1, 1);

        textNumberLabel = new QLabel(predictionDefaults);
        textNumberLabel->setObjectName(QString::fromUtf8("textNumberLabel"));

        gridLayout_7->addWidget(textNumberLabel, 4, 0, 1, 1);

        textNumberEdit = new QLineEdit(predictionDefaults);
        textNumberEdit->setObjectName(QString::fromUtf8("textNumberEdit"));

        gridLayout_7->addWidget(textNumberEdit, 5, 0, 1, 1);


        gridLayout->addWidget(predictionDefaults, 0, 0, 1, 1);


        gridLayout_2->addWidget(settingsFrame, 3, 0, 1, 2);

        maintenanceFrame = new QFrame(VehicleDialog);
        maintenanceFrame->setObjectName(QString::fromUtf8("maintenanceFrame"));
        maintenanceFrame->setFrameShape(QFrame::StyledPanel);
        maintenanceFrame->setFrameShadow(QFrame::Raised);
        gridLayout_3 = new QGridLayout(maintenanceFrame);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        maintenanceInfo = new QGroupBox(maintenanceFrame);
        maintenanceInfo->setObjectName(QString::fromUtf8("maintenanceInfo"));
        gridLayout_4 = new QGridLayout(maintenanceInfo);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        lastOilChangeEdit = new QDateTimeEdit(maintenanceInfo);
        lastOilChangeEdit->setObjectName(QString::fromUtf8("lastOilChangeEdit"));

        gridLayout_4->addWidget(lastOilChangeEdit, 1, 0, 1, 1);

        lastOilChangeLabel = new QLabel(maintenanceInfo);
        lastOilChangeLabel->setObjectName(QString::fromUtf8("lastOilChangeLabel"));

        gridLayout_4->addWidget(lastOilChangeLabel, 0, 0, 1, 1);

        lastTireChangeEdit = new QDateTimeEdit(maintenanceInfo);
        lastTireChangeEdit->setObjectName(QString::fromUtf8("lastTireChangeEdit"));

        gridLayout_4->addWidget(lastTireChangeEdit, 4, 0, 1, 1);

        lastOilRunsLabel = new QLabel(maintenanceInfo);
        lastOilRunsLabel->setObjectName(QString::fromUtf8("lastOilRunsLabel"));

        gridLayout_4->addWidget(lastOilRunsLabel, 2, 0, 1, 1);

        lastTireChangeLabel = new QLabel(maintenanceInfo);
        lastTireChangeLabel->setObjectName(QString::fromUtf8("lastTireChangeLabel"));

        gridLayout_4->addWidget(lastTireChangeLabel, 3, 0, 1, 1);

        lastTireRunsLabel = new QLabel(maintenanceInfo);
        lastTireRunsLabel->setObjectName(QString::fromUtf8("lastTireRunsLabel"));

        gridLayout_4->addWidget(lastTireRunsLabel, 5, 0, 1, 1);


        gridLayout_3->addWidget(maintenanceInfo, 0, 0, 1, 1);


        gridLayout_2->addWidget(maintenanceFrame, 3, 2, 1, 1);

        QWidget::setTabOrder(numberEdit, compClassEdit);
        QWidget::setTabOrder(compClassEdit, weightEdit);

        retranslateUi(VehicleDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), VehicleDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), VehicleDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(VehicleDialog);
    } // setupUi

    void retranslateUi(QDialog *VehicleDialog)
    {
        VehicleDialog->setWindowTitle(QApplication::translate("VehicleDialog", "Vehicle", nullptr));
        numberLabel->setText(QApplication::translate("VehicleDialog", "Number", nullptr));
        compClassLabel->setText(QApplication::translate("VehicleDialog", "Class", nullptr));
        weightLabel->setText(QApplication::translate("VehicleDialog", "Weight", nullptr));
        predictionDefaults->setTitle(QApplication::translate("VehicleDialog", "Prediction defaults", nullptr));
        weightAdjustmentLabel->setText(QApplication::translate("VehicleDialog", "ET correction per 1lb of weight", nullptr));
        windAdjustmentLabel->setText(QApplication::translate("VehicleDialog", "ET correction per 1MPH of wind", nullptr));
        textProviderLabel->setText(QApplication::translate("VehicleDialog", "Text Provider", nullptr));
        textNumberLabel->setText(QApplication::translate("VehicleDialog", "Text Number", nullptr));
        maintenanceInfo->setTitle(QApplication::translate("VehicleDialog", "Maintenance Info", nullptr));
        lastOilChangeLabel->setText(QApplication::translate("VehicleDialog", "Last oil change", nullptr));
        lastOilRunsLabel->setText(QApplication::translate("VehicleDialog", "Runs 0", nullptr));
        lastTireChangeLabel->setText(QApplication::translate("VehicleDialog", "Last tire change", nullptr));
        lastTireRunsLabel->setText(QApplication::translate("VehicleDialog", "Runs 0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VehicleDialog: public Ui_VehicleDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VEHICLEDIALOG_H
