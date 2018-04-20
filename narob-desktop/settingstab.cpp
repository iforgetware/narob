#include "settingstab.h"
#include "ui_settingstab.h"
#include "settings.h"

#include <QSqlQuery>

#include <QDebug>

SettingsTab::SettingsTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsTab)
//    mSettingsModel(new SettingsModel(this))
{
    ui->setupUi(this);

    mSettingsTable = new Settings();
    mSettings = mSettingsTable->getSettings();

    ui->emailUserEdit->setText(mSettings->value("emailUser").toString());
    ui->emailPWEdit->setText(mSettings->value("emailPW").toString());
    ui->emailHostEdit->setText(mSettings->value("emailHost").toString());
    ui->textNumberEdit->setText(mSettings->value("textNumber").toString());
    ui->textProviderComboBox->setCurrentText(mSettings->value("textProvider").toString());

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
        mSettings->setValue("emailUser", ui->emailUserEdit->text());
    }

    if(ui->emailPWEdit->text().trimmed() != ""){
        mSettings->setValue("emailPW", ui->emailPWEdit->text());
    }

    if(ui->emailHostEdit->text().trimmed() != ""){
        mSettings->setValue("emailHost", ui->emailHostEdit->text());
    }

    if(ui->textNumberEdit->text().trimmed() != ""){
        mSettings->setValue("textNumber", ui->textNumberEdit->text());
    }

    mSettings->setValue("textProvider", ui->textProviderComboBox->currentText());

    mSettingsTable->updateSettings(mSettings);

    displayUpdate();
}

void SettingsTab::displayUpdate()
{
    ui->emailUserLabel->setText(QString("Email username -> %1")
                                .arg(mSettings->value("emailUser").toString()));
    ui->emailPWLabel->setText(QString("Email password -> %1")
                              .arg(mSettings->value("emailPW").toString()));
    ui->emailHostLabel->setText(QString("Email host -> %1")
                                .arg(mSettings->value("emailHost").toString()));
    ui->textNumberLabel->setText(QString("Texting number -> %1")
                                 .arg(mSettings->value("textNumber").toString()));
    ui->textProviderLabel->setText(QString("Text Provider -> %1")
                                   .arg(mSettings->value("textProvider").toString()));
}

void SettingsTab::onClearButtonClicked()
{
    ui->emailUserEdit->clear();
    ui->emailPWEdit->clear();
    ui->emailHostEdit->clear();
    ui->textNumberEdit->clear();
}
