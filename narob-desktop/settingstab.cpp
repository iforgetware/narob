#include "settingstab.h"
#include "ui_settingstab.h"
#include "settings.h"
#include "databasemanager.h"

#include <QSqlQuery>

#include <QDebug>

SettingsTab::SettingsTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsTab)
{
    ui->setupUi(this);

    mSettingsTable = new Settings();
    mSettings = mSettingsTable->getSettings();

    ui->windAdjustmentSpinBox->setValue(mSettings->value("windAdjustment").toDouble());
    ui->weightAdjustmentSpinBox->setValue(mSettings->value("weightAdjustment").toDouble());
    ui->textNumberEdit->setText(mSettings->value("textNumber").toString());
    ui->textProviderComboBox->setCurrentText(mSettings->value("textProvider").toString());
    ui->emailUserEdit->setText(mSettings->value("emailUser").toString());
    ui->emailPWEdit->setText(mSettings->value("emailPW").toString());
    ui->emailHostEdit->setText(mSettings->value("emailHost").toString());

    displayUpdate();

    connect(ui->saveButton, &QPushButton::clicked,
            this, &SettingsTab::onSaveButtonClicked);
    connect(ui->clearButton, &QPushButton::clicked,
            this, &SettingsTab::onClearButtonClicked);

    connect(ui->cleanDatabaseButton, &QPushButton::clicked,
            this, &SettingsTab::onCleanDatabaseButtonClicked);

    connect(ui->testWeatherButton, &QPushButton::clicked,
            this, &SettingsTab::onTestWeatherButtonClicked);
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
    mSettings->setValue("windAdjustment", ui->windAdjustmentSpinBox->value());

    mSettings->setValue("weightAdjustment", ui->weightAdjustmentSpinBox->value());

    if(ui->textNumberEdit->text().trimmed() != ""){
        mSettings->setValue("textNumber", ui->textNumberEdit->text());
    }

    mSettings->setValue("textProvider", ui->textProviderComboBox->currentText());

    if(ui->emailUserEdit->text().trimmed() != ""){
        mSettings->setValue("emailUser", ui->emailUserEdit->text());
    }

    if(ui->emailPWEdit->text().trimmed() != ""){
        mSettings->setValue("emailPW", ui->emailPWEdit->text());
    }

    if(ui->emailHostEdit->text().trimmed() != ""){
        mSettings->setValue("emailHost", ui->emailHostEdit->text());
    }

    mSettingsTable->updateSettings(mSettings);

    displayUpdate();
}

void SettingsTab::onClearButtonClicked()
{
    ui->emailUserEdit->clear();
    ui->emailPWEdit->clear();
    ui->emailHostEdit->clear();
    ui->textNumberEdit->clear();
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
                                     .arg(mSettings->value("windAdjustment").toString()));
    ui->weightAdjustmentLabel->setText(QString("ET adjustment per 1lb of weight -> %1")
                                       .arg(mSettings->value("weightAdjustment").toString()));
    ui->textNumberLabel->setText(QString("Texting number -> %1")
                                 .arg(mSettings->value("textNumber").toString()));
    ui->textProviderLabel->setText(QString("Text Provider -> %1")
                                   .arg(mSettings->value("textProvider").toString()));
    ui->emailUserLabel->setText(QString("Email username -> %1")
                                .arg(mSettings->value("emailUser").toString()));
    ui->emailPWLabel->setText(QString("Email password -> %1")
                              .arg(mSettings->value("emailPW").toString()));
    ui->emailHostLabel->setText(QString("Email host -> %1")
                                .arg(mSettings->value("emailHost").toString()));
}

