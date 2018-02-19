#include "settingstab.h"
#include "ui_settingstab.h"
#include "settings.h"
#include "settingsdao.h"

#include <QSqlQuery>

#include <QDebug>

SettingsTab::SettingsTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsTab),
    mSettingsModel(new SettingsModel(this))
{
    ui->setupUi(this);

    mSettings = mSettingsModel->getSettings();

//    ui->emailUserEdit->setText(mSettings->emailUser());
//    ui->emailPWEdit->setText(mSettings->emailPW());
//    ui->emailHostEdit->setText(mSettings->emailHost());
//    ui->textNumberEdit->setText(mSettings->textNumber());
    ui->textProviderComboBox->setCurrentText(mSettings->textProvider());

    displayUpdate();

    connect(ui->saveButton, &QPushButton::clicked, this, &SettingsTab::onSaveButtonClicked);
    connect(ui->clearButton, &QPushButton::clicked, this, &SettingsTab::onClearButtonClicked);
}

SettingsTab::~SettingsTab()
{
    delete ui;
}

void SettingsTab::onSaveButtonClicked()
{
    if(ui->emailUserEdit->text().trimmed() != ""){
        mSettings->setEmailUser(ui->emailUserEdit->text());
    }

    if(ui->emailPWEdit->text().trimmed() != ""){
        mSettings->setEmailPW(ui->emailPWEdit->text());
    }

    if(ui->emailHostEdit->text().trimmed() != ""){
        mSettings->setEmailHost(ui->emailHostEdit->text());
    }

    if(ui->textNumberEdit->text().trimmed() != ""){
        mSettings->setTextNumber(ui->textNumberEdit->text());
    }

    mSettings->setTextProvider(ui->textProviderComboBox->currentText());

    mSettingsModel->updateSettings(mSettings);

    displayUpdate();
}

void SettingsTab::displayUpdate()
{
    ui->emailUserLabel->setText(QString("Email username -> %1").arg(mSettings->emailUser()));
    ui->emailPWLabel->setText(QString("Email password -> %1").arg(mSettings->emailPW()));
    ui->emailHostLabel->setText(QString("Email host -> %1").arg(mSettings->emailHost()));
    ui->textNumberLabel->setText(QString("Texting number -> %1").arg(mSettings->textNumber()));
    ui->textProviderLabel->setText(QString("Text Provider -> %1").arg(mSettings->textProvider()));
}

void SettingsTab::onClearButtonClicked()
{
    ui->emailUserEdit->clear();
    ui->emailPWEdit->clear();
    ui->emailHostEdit->clear();
    ui->textNumberEdit->clear();
}
