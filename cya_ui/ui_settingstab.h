/********************************************************************************
** Form generated from reading UI file 'settingstab.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGSTAB_H
#define UI_SETTINGSTAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>
#include "providerbox.h"

QT_BEGIN_NAMESPACE

class Ui_SettingsTab
{
public:
    QGridLayout *gridLayout;
    QFrame *testingFrame;
    QGridLayout *gridLayout_4;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label;
    QLabel *warningLabel;
    QPushButton *testWeightButton;
    QPushButton *testWeatherButton;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *testWindButton;
    QPushButton *testTPButton;
    QCheckBox *enableTestingCheckBox;
    QFrame *maintenanceFrame;
    QGridLayout *gridLayout_5;
    QPushButton *updateLogbookButton;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *cleanDatabaseButton;
    QSpacerItem *horizontalSpacer_3;
    QCheckBox *enableMaintenanceCheckBox;
    QLabel *maintenanceLabel;
    QPushButton *updateSplitsButton;
    QFrame *setupFrame;
    QGridLayout *gridLayout_8;
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
    QGroupBox *paging;
    QGridLayout *gridLayout_6;
    QLabel *emailPWLabel;
    QLabel *emailUserLabel;
    QLabel *emailHostLabel;
    QLineEdit *emailUserEdit;
    QLineEdit *emailHostEdit;
    QLineEdit *emailPWEdit;
    QGroupBox *weather;
    QGridLayout *gridLayout_3;
    QLabel *humOffsetLabel;
    QCheckBox *useConsoleCheckBox;
    QDoubleSpinBox *humOffsetSpinBox;
    QLabel *tempOffsetLabel;
    QDoubleSpinBox *tempOffsetSpinBox;
    QCheckBox *useOffsetsCheckBox;
    QSpacerItem *verticalSpacer_2;
    QGroupBox *buttons;
    QGridLayout *gridLayout_2;
    QPushButton *clearButton;
    QSpacerItem *horizontalSpacer;
    QLabel *saveLabel;
    QPushButton *saveButton;
    QLabel *clearLabel;
    QLabel *setupLabel;

    void setupUi(QWidget *SettingsTab)
    {
        if (SettingsTab->objectName().isEmpty())
            SettingsTab->setObjectName(QString::fromUtf8("SettingsTab"));
        SettingsTab->resize(790, 809);
        gridLayout = new QGridLayout(SettingsTab);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        testingFrame = new QFrame(SettingsTab);
        testingFrame->setObjectName(QString::fromUtf8("testingFrame"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(testingFrame->sizePolicy().hasHeightForWidth());
        testingFrame->setSizePolicy(sizePolicy);
        testingFrame->setFrameShape(QFrame::Box);
        testingFrame->setFrameShadow(QFrame::Plain);
        testingFrame->setLineWidth(5);
        gridLayout_4 = new QGridLayout(testingFrame);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_5, 3, 0, 1, 1);

        label = new QLabel(testingFrame);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setPointSize(30);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);

        gridLayout_4->addWidget(label, 0, 0, 1, 7, Qt::AlignHCenter);

        warningLabel = new QLabel(testingFrame);
        warningLabel->setObjectName(QString::fromUtf8("warningLabel"));
        QFont font1;
        font1.setPointSize(16);
        warningLabel->setFont(font1);
        warningLabel->setTextFormat(Qt::AutoText);

        gridLayout_4->addWidget(warningLabel, 1, 0, 1, 7, Qt::AlignHCenter);

        testWeightButton = new QPushButton(testingFrame);
        testWeightButton->setObjectName(QString::fromUtf8("testWeightButton"));

        gridLayout_4->addWidget(testWeightButton, 3, 5, 1, 1);

        testWeatherButton = new QPushButton(testingFrame);
        testWeatherButton->setObjectName(QString::fromUtf8("testWeatherButton"));

        gridLayout_4->addWidget(testWeatherButton, 3, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_2, 3, 6, 1, 1);

        testWindButton = new QPushButton(testingFrame);
        testWindButton->setObjectName(QString::fromUtf8("testWindButton"));

        gridLayout_4->addWidget(testWindButton, 3, 4, 1, 1);

        testTPButton = new QPushButton(testingFrame);
        testTPButton->setObjectName(QString::fromUtf8("testTPButton"));

        gridLayout_4->addWidget(testTPButton, 3, 3, 1, 1);

        enableTestingCheckBox = new QCheckBox(testingFrame);
        enableTestingCheckBox->setObjectName(QString::fromUtf8("enableTestingCheckBox"));

        gridLayout_4->addWidget(enableTestingCheckBox, 2, 2, 1, 4, Qt::AlignHCenter);


        gridLayout->addWidget(testingFrame, 2, 0, 1, 1);

        maintenanceFrame = new QFrame(SettingsTab);
        maintenanceFrame->setObjectName(QString::fromUtf8("maintenanceFrame"));
        sizePolicy.setHeightForWidth(maintenanceFrame->sizePolicy().hasHeightForWidth());
        maintenanceFrame->setSizePolicy(sizePolicy);
        maintenanceFrame->setFrameShape(QFrame::Box);
        maintenanceFrame->setFrameShadow(QFrame::Plain);
        maintenanceFrame->setLineWidth(5);
        gridLayout_5 = new QGridLayout(maintenanceFrame);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        updateLogbookButton = new QPushButton(maintenanceFrame);
        updateLogbookButton->setObjectName(QString::fromUtf8("updateLogbookButton"));

        gridLayout_5->addWidget(updateLogbookButton, 2, 1, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer_4, 2, 0, 1, 1);

        cleanDatabaseButton = new QPushButton(maintenanceFrame);
        cleanDatabaseButton->setObjectName(QString::fromUtf8("cleanDatabaseButton"));

        gridLayout_5->addWidget(cleanDatabaseButton, 2, 2, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer_3, 2, 4, 1, 1);

        enableMaintenanceCheckBox = new QCheckBox(maintenanceFrame);
        enableMaintenanceCheckBox->setObjectName(QString::fromUtf8("enableMaintenanceCheckBox"));

        gridLayout_5->addWidget(enableMaintenanceCheckBox, 1, 0, 1, 5, Qt::AlignHCenter);

        maintenanceLabel = new QLabel(maintenanceFrame);
        maintenanceLabel->setObjectName(QString::fromUtf8("maintenanceLabel"));
        maintenanceLabel->setFont(font);

        gridLayout_5->addWidget(maintenanceLabel, 0, 0, 1, 5, Qt::AlignHCenter);

        updateSplitsButton = new QPushButton(maintenanceFrame);
        updateSplitsButton->setObjectName(QString::fromUtf8("updateSplitsButton"));

        gridLayout_5->addWidget(updateSplitsButton, 2, 3, 1, 1);


        gridLayout->addWidget(maintenanceFrame, 1, 0, 1, 1);

        setupFrame = new QFrame(SettingsTab);
        setupFrame->setObjectName(QString::fromUtf8("setupFrame"));
        sizePolicy.setHeightForWidth(setupFrame->sizePolicy().hasHeightForWidth());
        setupFrame->setSizePolicy(sizePolicy);
        setupFrame->setFrameShape(QFrame::Box);
        setupFrame->setFrameShadow(QFrame::Plain);
        setupFrame->setLineWidth(5);
        gridLayout_8 = new QGridLayout(setupFrame);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        predictionDefaults = new QGroupBox(setupFrame);
        predictionDefaults->setObjectName(QString::fromUtf8("predictionDefaults"));
        sizePolicy.setHeightForWidth(predictionDefaults->sizePolicy().hasHeightForWidth());
        predictionDefaults->setSizePolicy(sizePolicy);
        predictionDefaults->setFlat(false);
        predictionDefaults->setCheckable(false);
        gridLayout_7 = new QGridLayout(predictionDefaults);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        weightAdjustmentLabel = new QLabel(predictionDefaults);
        weightAdjustmentLabel->setObjectName(QString::fromUtf8("weightAdjustmentLabel"));

        gridLayout_7->addWidget(weightAdjustmentLabel, 2, 0, 1, 1);

        weightAdjustmentSpinBox = new QDoubleSpinBox(predictionDefaults);
        weightAdjustmentSpinBox->setObjectName(QString::fromUtf8("weightAdjustmentSpinBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(weightAdjustmentSpinBox->sizePolicy().hasHeightForWidth());
        weightAdjustmentSpinBox->setSizePolicy(sizePolicy1);
        weightAdjustmentSpinBox->setDecimals(3);
        weightAdjustmentSpinBox->setMaximum(0.999000000000000);
        weightAdjustmentSpinBox->setSingleStep(0.001000000000000);

        gridLayout_7->addWidget(weightAdjustmentSpinBox, 3, 0, 1, 1);

        windAdjustmentSpinBox = new QDoubleSpinBox(predictionDefaults);
        windAdjustmentSpinBox->setObjectName(QString::fromUtf8("windAdjustmentSpinBox"));
        sizePolicy1.setHeightForWidth(windAdjustmentSpinBox->sizePolicy().hasHeightForWidth());
        windAdjustmentSpinBox->setSizePolicy(sizePolicy1);
        windAdjustmentSpinBox->setDecimals(3);
        windAdjustmentSpinBox->setMinimum(0.000000000000000);
        windAdjustmentSpinBox->setMaximum(0.999000000000000);
        windAdjustmentSpinBox->setSingleStep(0.001000000000000);

        gridLayout_7->addWidget(windAdjustmentSpinBox, 1, 0, 1, 1);

        textProviderComboBox = new ProviderBox(predictionDefaults);
        textProviderComboBox->setObjectName(QString::fromUtf8("textProviderComboBox"));
        sizePolicy1.setHeightForWidth(textProviderComboBox->sizePolicy().hasHeightForWidth());
        textProviderComboBox->setSizePolicy(sizePolicy1);

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


        gridLayout_8->addWidget(predictionDefaults, 1, 0, 1, 1);

        paging = new QGroupBox(setupFrame);
        paging->setObjectName(QString::fromUtf8("paging"));
        sizePolicy.setHeightForWidth(paging->sizePolicy().hasHeightForWidth());
        paging->setSizePolicy(sizePolicy);
        gridLayout_6 = new QGridLayout(paging);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        emailPWLabel = new QLabel(paging);
        emailPWLabel->setObjectName(QString::fromUtf8("emailPWLabel"));

        gridLayout_6->addWidget(emailPWLabel, 2, 0, 1, 1);

        emailUserLabel = new QLabel(paging);
        emailUserLabel->setObjectName(QString::fromUtf8("emailUserLabel"));

        gridLayout_6->addWidget(emailUserLabel, 0, 0, 1, 1);

        emailHostLabel = new QLabel(paging);
        emailHostLabel->setObjectName(QString::fromUtf8("emailHostLabel"));

        gridLayout_6->addWidget(emailHostLabel, 4, 0, 1, 1);

        emailUserEdit = new QLineEdit(paging);
        emailUserEdit->setObjectName(QString::fromUtf8("emailUserEdit"));

        gridLayout_6->addWidget(emailUserEdit, 1, 0, 1, 1);

        emailHostEdit = new QLineEdit(paging);
        emailHostEdit->setObjectName(QString::fromUtf8("emailHostEdit"));

        gridLayout_6->addWidget(emailHostEdit, 5, 0, 1, 1);

        emailPWEdit = new QLineEdit(paging);
        emailPWEdit->setObjectName(QString::fromUtf8("emailPWEdit"));

        gridLayout_6->addWidget(emailPWEdit, 3, 0, 1, 1);


        gridLayout_8->addWidget(paging, 1, 1, 1, 1);

        weather = new QGroupBox(setupFrame);
        weather->setObjectName(QString::fromUtf8("weather"));
        sizePolicy.setHeightForWidth(weather->sizePolicy().hasHeightForWidth());
        weather->setSizePolicy(sizePolicy);
        gridLayout_3 = new QGridLayout(weather);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        humOffsetLabel = new QLabel(weather);
        humOffsetLabel->setObjectName(QString::fromUtf8("humOffsetLabel"));

        gridLayout_3->addWidget(humOffsetLabel, 3, 0, 1, 1);

        useConsoleCheckBox = new QCheckBox(weather);
        useConsoleCheckBox->setObjectName(QString::fromUtf8("useConsoleCheckBox"));

        gridLayout_3->addWidget(useConsoleCheckBox, 6, 0, 1, 1);

        humOffsetSpinBox = new QDoubleSpinBox(weather);
        humOffsetSpinBox->setObjectName(QString::fromUtf8("humOffsetSpinBox"));
        sizePolicy1.setHeightForWidth(humOffsetSpinBox->sizePolicy().hasHeightForWidth());
        humOffsetSpinBox->setSizePolicy(sizePolicy1);
        humOffsetSpinBox->setDecimals(3);
        humOffsetSpinBox->setMinimum(-9.999000000000001);
        humOffsetSpinBox->setMaximum(9.999000000000001);
        humOffsetSpinBox->setSingleStep(0.010000000000000);

        gridLayout_3->addWidget(humOffsetSpinBox, 4, 0, 1, 1);

        tempOffsetLabel = new QLabel(weather);
        tempOffsetLabel->setObjectName(QString::fromUtf8("tempOffsetLabel"));

        gridLayout_3->addWidget(tempOffsetLabel, 1, 0, 1, 1);

        tempOffsetSpinBox = new QDoubleSpinBox(weather);
        tempOffsetSpinBox->setObjectName(QString::fromUtf8("tempOffsetSpinBox"));
        sizePolicy1.setHeightForWidth(tempOffsetSpinBox->sizePolicy().hasHeightForWidth());
        tempOffsetSpinBox->setSizePolicy(sizePolicy1);
        tempOffsetSpinBox->setDecimals(3);
        tempOffsetSpinBox->setMinimum(-9.999000000000001);
        tempOffsetSpinBox->setMaximum(9.999000000000001);
        tempOffsetSpinBox->setSingleStep(0.010000000000000);

        gridLayout_3->addWidget(tempOffsetSpinBox, 2, 0, 1, 1);

        useOffsetsCheckBox = new QCheckBox(weather);
        useOffsetsCheckBox->setObjectName(QString::fromUtf8("useOffsetsCheckBox"));

        gridLayout_3->addWidget(useOffsetsCheckBox, 0, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_2, 5, 0, 1, 1);


        gridLayout_8->addWidget(weather, 1, 2, 1, 1);

        buttons = new QGroupBox(setupFrame);
        buttons->setObjectName(QString::fromUtf8("buttons"));
        sizePolicy.setHeightForWidth(buttons->sizePolicy().hasHeightForWidth());
        buttons->setSizePolicy(sizePolicy);
        buttons->setFlat(false);
        gridLayout_2 = new QGridLayout(buttons);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        clearButton = new QPushButton(buttons);
        clearButton->setObjectName(QString::fromUtf8("clearButton"));
        QSizePolicy sizePolicy2(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(clearButton->sizePolicy().hasHeightForWidth());
        clearButton->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(clearButton, 1, 3, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 1, 2, 1, 1);

        saveLabel = new QLabel(buttons);
        saveLabel->setObjectName(QString::fromUtf8("saveLabel"));

        gridLayout_2->addWidget(saveLabel, 1, 0, 1, 1);

        saveButton = new QPushButton(buttons);
        saveButton->setObjectName(QString::fromUtf8("saveButton"));
        sizePolicy2.setHeightForWidth(saveButton->sizePolicy().hasHeightForWidth());
        saveButton->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(saveButton, 1, 1, 1, 1);

        clearLabel = new QLabel(buttons);
        clearLabel->setObjectName(QString::fromUtf8("clearLabel"));

        gridLayout_2->addWidget(clearLabel, 1, 4, 1, 1, Qt::AlignLeft);


        gridLayout_8->addWidget(buttons, 2, 0, 1, 3);

        setupLabel = new QLabel(setupFrame);
        setupLabel->setObjectName(QString::fromUtf8("setupLabel"));
        setupLabel->setFont(font);

        gridLayout_8->addWidget(setupLabel, 0, 0, 1, 3, Qt::AlignHCenter);


        gridLayout->addWidget(setupFrame, 0, 0, 1, 1);

        QWidget::setTabOrder(saveButton, clearButton);

        retranslateUi(SettingsTab);

        QMetaObject::connectSlotsByName(SettingsTab);
    } // setupUi

    void retranslateUi(QWidget *SettingsTab)
    {
        SettingsTab->setWindowTitle(QApplication::translate("SettingsTab", "Form", nullptr));
        label->setText(QApplication::translate("SettingsTab", "Testing", nullptr));
        warningLabel->setText(QApplication::translate("SettingsTab", "WARNING!  These buttons will clear and repopulate the database.", nullptr));
        testWeightButton->setText(QApplication::translate("SettingsTab", "Test Weight", nullptr));
        testWeatherButton->setText(QApplication::translate("SettingsTab", "Test Weather", nullptr));
        testWindButton->setText(QApplication::translate("SettingsTab", "Test Wind", nullptr));
        testTPButton->setText(QApplication::translate("SettingsTab", "Test Ticket With Predictions", nullptr));
        enableTestingCheckBox->setText(QApplication::translate("SettingsTab", "Enable Testing", nullptr));
        updateLogbookButton->setText(QApplication::translate("SettingsTab", "Update Logbook", nullptr));
        cleanDatabaseButton->setText(QApplication::translate("SettingsTab", "Clean Database", nullptr));
        enableMaintenanceCheckBox->setText(QApplication::translate("SettingsTab", "Enable Maintenance", nullptr));
        maintenanceLabel->setText(QApplication::translate("SettingsTab", "Maintenance", nullptr));
        updateSplitsButton->setText(QApplication::translate("SettingsTab", "Update Splits", nullptr));
        predictionDefaults->setTitle(QApplication::translate("SettingsTab", "Prediction defaults", nullptr));
        weightAdjustmentLabel->setText(QApplication::translate("SettingsTab", "ET correction per 1lb of weight", nullptr));
        windAdjustmentLabel->setText(QApplication::translate("SettingsTab", "ET correction per 1MPH of wind", nullptr));
        textProviderLabel->setText(QApplication::translate("SettingsTab", "Text Provider", nullptr));
        textNumberLabel->setText(QApplication::translate("SettingsTab", "Text Number", nullptr));
        paging->setTitle(QApplication::translate("SettingsTab", "Paging", nullptr));
        emailPWLabel->setText(QApplication::translate("SettingsTab", "Email PW", nullptr));
        emailUserLabel->setText(QApplication::translate("SettingsTab", "Email User", nullptr));
        emailHostLabel->setText(QApplication::translate("SettingsTab", "Email Host", nullptr));
        weather->setTitle(QApplication::translate("SettingsTab", "Weather", nullptr));
        humOffsetLabel->setText(QApplication::translate("SettingsTab", "Humidity Offset", nullptr));
        useConsoleCheckBox->setText(QApplication::translate("SettingsTab", "Use Values From Console", nullptr));
        tempOffsetLabel->setText(QApplication::translate("SettingsTab", "Temperature Offset", nullptr));
        useOffsetsCheckBox->setText(QApplication::translate("SettingsTab", "Use Value Offsets", nullptr));
        buttons->setTitle(QString());
        clearButton->setText(QApplication::translate("SettingsTab", "Clear All", nullptr));
        saveLabel->setText(QApplication::translate("SettingsTab", "Enter any new values and click to", nullptr));
        saveButton->setText(QApplication::translate("SettingsTab", "Save Changes", nullptr));
        clearLabel->setText(QApplication::translate("SettingsTab", "< DOES NOT SAVE VALUES!", nullptr));
        setupLabel->setText(QApplication::translate("SettingsTab", "Setup", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingsTab: public Ui_SettingsTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSTAB_H
