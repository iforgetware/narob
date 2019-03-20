#include "settingstab.h"
#include "ui_settingstab.h"
#include "settings.h"
#include "databasemanager.h"

#include <QDebug>

SettingsTab::SettingsTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsTab)
{
    ui->setupUi(this);


    ui->windAdjustmentSpinBox->setValue(Settings::get("windAdjustment").toDouble());
    ui->weightAdjustmentSpinBox->setValue(Settings::get("weightAdjustment").toDouble());
    ui->textNumberEdit->setText(Settings::get("textNumber").toString());
    ui->textProviderComboBox->setCurrentText(Settings::get("textProvider").toString());
    ui->emailUserEdit->setText(Settings::get("emailUser").toString());
    ui->emailPWEdit->setText(Settings::get("emailPW").toString());
    ui->emailHostEdit->setText(Settings::get("emailHost").toString());

    displayUpdate();

    connect(ui->saveButton, &QPushButton::clicked,
            this, &SettingsTab::onSaveButtonClicked);
    connect(ui->clearButton, &QPushButton::clicked,
            this, &SettingsTab::onClearButtonClicked);

    connect(ui->updateLogbookButton, &QPushButton::clicked,
            this, &SettingsTab::onUpdateLogbookButtonClicked);
    connect(ui->cleanDatabaseButton, &QPushButton::clicked,
            this, &SettingsTab::onCleanDatabaseButtonClicked);

    connect(ui->testWeatherButton, &QPushButton::clicked,
            this, &SettingsTab::onTestWeatherButtonClicked);
    connect(ui->testTPButton, &QPushButton::clicked,
            this, &SettingsTab::onTestTPButtonClicked);
    connect(ui->testWindButton, &QPushButton::clicked,
            this, &SettingsTab::onTestWindButtonClicked);
    connect(ui->testWeightButton, &QPushButton::clicked,
            this, &SettingsTab::onTestWeightButtonClicked);
}

SettingsTab::~SettingsTab()
{
    delete ui;
}

void SettingsTab::onSaveButtonClicked()
{
    Settings::set("windAdjustment", ui->windAdjustmentSpinBox->value());

    Settings::set("weightAdjustment", ui->weightAdjustmentSpinBox->value());

    if(ui->textNumberEdit->text().trimmed() != ""){
        Settings::set("textNumber", ui->textNumberEdit->text());
    }

    Settings::set("textProvider", ui->textProviderComboBox->currentText());

    if(ui->emailUserEdit->text().trimmed() != ""){
        Settings::set("emailUser", ui->emailUserEdit->text());
    }

    if(ui->emailPWEdit->text().trimmed() != ""){
        Settings::set("emailPW", ui->emailPWEdit->text());
    }

    if(ui->emailHostEdit->text().trimmed() != ""){
        Settings::set("emailHost", ui->emailHostEdit->text());
    }

    displayUpdate();
}

void SettingsTab::onClearButtonClicked()
{
    ui->emailUserEdit->clear();
    ui->emailPWEdit->clear();
    ui->emailHostEdit->clear();
    ui->textNumberEdit->clear();
}

void SettingsTab::onUpdateLogbookButtonClicked()
{
    if(ui->enableMaintenanceCheckBox->isChecked()){
        emit updateLogbook();
    }
}

void SettingsTab::onCleanDatabaseButtonClicked()
{
    // delete all weather observations that are more than a week old

    // make list of used predictions
    // delete all unused predictions that are more than a week old
}

void SettingsTab::onTestWeatherButtonClicked()
{
    if(ui->enableTestingCheckBox->isChecked()){
        emit testWeather();
    }
}

void SettingsTab::onTestTPButtonClicked()
{
    if(ui->enableTestingCheckBox->isChecked()){
        emit testTP();
    }
}

void SettingsTab::onTestWindButtonClicked()
{
    if(ui->enableTestingCheckBox->isChecked()){
        emit testWind();
    }
}

void SettingsTab::onTestWeightButtonClicked()
{
    if(ui->enableTestingCheckBox->isChecked()){
        emit testWeight();
    }
}

void SettingsTab::displayUpdate()
{
    ui->windAdjustmentLabel->setText(QString("ET adjustment per 1MPH of wind -> %1")
                                     .arg(Settings::get("windAdjustment").toString()));
    ui->weightAdjustmentLabel->setText(QString("ET adjustment per 1lb of weight -> %1")
                                       .arg(Settings::get("weightAdjustment").toString()));
    ui->textNumberLabel->setText(QString("Texting number -> %1")
                                 .arg(Settings::get("textNumber").toString()));
    ui->textProviderLabel->setText(QString("Text Provider -> %1")
                                   .arg(Settings::get("textProvider").toString()));
    ui->emailUserLabel->setText(QString("Email username -> %1")
                                .arg(Settings::get("emailUser").toString()));
    ui->emailPWLabel->setText(QString("Email password -> %1")
                              .arg(Settings::get("emailPW").toString()));
    ui->emailHostLabel->setText(QString("Email host -> %1")
                                .arg(Settings::get("emailHost").toString()));
}

