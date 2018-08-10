#include <QDataWidgetMapper>
#include <QSqlQuery>

#include "predictiontab.h"
#include "ui_predictiontab.h"
#include "predictions.h"

#include "settings.h"
#include "smtp.h"

#include <QTimer>
#include <QDebug>
#include <QVector>

PredictionTab::PredictionTab(TicketsModel* model,
                             Vehicle *vehicle,
                             Race *race,
                             QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PredictionTab),
    mVehicle(vehicle),
    mRace(race),
    mSettingsTable(new Settings),
    mPredictionsModel(new PredictionsModel(mVehicle, mRace, 0, this)),
    mTicketsModel(model)
{
    ui->setupUi(this);

    mPreviousPredictionsWidget = new PreviousPredictionsWidget(mPredictionsModel,
                                               this);

    ui->gridLayout_2->addWidget(mPreviousPredictionsWidget, 0, 0);

    mSettings = mSettingsTable->getSettings();

    ui->vehicleWeightSpinBox->setValue(mVehicle->value("weight").toInt());
    ui->riderWeightSpinBox->setValue(mTicketsModel->lastWeight());

    ui->weightAdjustmentSpinBox->setValue(mSettings->value("weightAdjustment").toDouble());
    ui->windAdjustmentSpinBox->setValue(mSettings->value("windAdjustment").toDouble());
    ui->textProviderComboBox->setCurrentText(mSettings->value("textProvider").toString());
    ui->textNumberEdit->setText(mSettings->value("textNumber").toString());

    mAutoTimer = new QTimer(this);
    mAutoTimer->start(60000);

    connect(mAutoTimer,
            &QTimer::timeout,
            this,
            &PredictionTab::makePrediction);
}

PredictionTab::~PredictionTab()
{
    delete mAutoTimer;
    delete ui;
}

void PredictionTab::UpdateAllModels()
{
    mPreviousPredictionsWidget->updateModel();
}

void PredictionTab::makePrediction()
{
    Prediction prediction;

    prediction.setValue("vehicleId", mVehicle->value("id").toInt());
    prediction.setValue("raceId", mRace->value("id").toInt());
    prediction.setValue("trackId", mRace->value("trackId").toInt());
    prediction.setValue("ticketId", 0);
    prediction.setValue("riderWeight", ui->riderWeightSpinBox->value());
    prediction.setValue("vehicleWeight", ui->vehicleWeightSpinBox->value());

    prediction.setValue("windAdjustment", ui->windAdjustmentSpinBox->value());
    prediction.setValue("weightAdjustment", ui->weightAdjustmentSpinBox->value());

    prediction.predictClocks(ui->vehicleTicketsCheckBox->isChecked(),
                             ui->trackTicketsCheckBox->isChecked(),
                             mTicketsModel);

    int minute = prediction.value("dateTime").toDateTime().time().minute();

    if(minute % 5 == 0){
        writePredictionToDb(prediction);
    }

    updateDisplay(prediction);
}

void PredictionTab::writePredictionToDb(Prediction &prediction)
{
    mPredictionsModel->addRow(prediction);

    if(ui->eToPhoneCheckBox->isChecked() ||
       ui->qToPhoneCheckBox->isChecked()){
        sendPage(prediction);
    }

    if(mPredictionsModel->rowCount(QModelIndex()) > 5){
        mPredictionsModel->removeRow(6);
        mPredictionsModel->submitAll();
        mPreviousPredictionsWidget->updateModel();
    }
}

QString PredictionTab::formatClock(const QVariant &clock)
{
    return QString::number(clock.toDouble(), 'f', 3);
}

void PredictionTab::updateDisplay(const Prediction &prediction)
{
    ui->sixtyD->setText(formatClock(prediction.value("sixtyD")));
    ui->threeThirtyD->setText(formatClock(prediction.value("threeThirtyD")));
    ui->eighthD->setText(formatClock(prediction.value("eighthD")));
    ui->thousandD->setText(formatClock(prediction.value("thousandD")));
    ui->quarterD->setText(formatClock(prediction.value("quarterD")));

    ui->sixtyA->setText(formatClock(prediction.value("sixtyA")));
    ui->threeThirtyA->setText(formatClock(prediction.value("threeThirtyA")));
    ui->eighthA->setText(formatClock(prediction.value("eighthA")));
    ui->thousandA->setText(formatClock(prediction.value("thousandA")));
    ui->quarterA->setText(formatClock(prediction.value("quarterA")));

    ui->sixtyT->setText(formatClock(prediction.value("sixtyT")));
    ui->threeThirtyT->setText(formatClock(prediction.value("threeThirtyT")));
    ui->eighthT->setText(formatClock(prediction.value("eighthT")));
    ui->thousandT->setText(formatClock(prediction.value("thousandT")));
    ui->quarterT->setText(formatClock(prediction.value("quarterT")));

    ui->sixtyH->setText(formatClock(prediction.value("sixtyH")));
    ui->threeThirtyH->setText(formatClock(prediction.value("threeThirtyH")));
    ui->eighthH->setText(formatClock(prediction.value("eighthH")));
    ui->thousandH->setText(formatClock(prediction.value("thousandH")));
    ui->quarterH->setText(formatClock(prediction.value("quarterH")));

    ui->sixtyP->setText(formatClock(prediction.value("sixtyP")));
    ui->threeThirtyP->setText(formatClock(prediction.value("threeThirtyP")));
    ui->eighthP->setText(formatClock(prediction.value("eighthP")));
    ui->thousandP->setText(formatClock(prediction.value("thousandP")));
    ui->quarterP->setText(formatClock(prediction.value("quarterP")));
}

void PredictionTab::sendPage(const Prediction &prediction)
{
    if(mSettings->value("emailUser").toString() == ""
       || mSettings->value("emailHost").toString() == ""
       || mSettings->value("emailPW").toString() == ""){
        qDebug("No email settings to page with - WRITE CODE");
    }else{
        QMap<QString, QString> *suffixes = new QMap<QString, QString>;

        suffixes->insert("Alltel", "message.alltel.com");
        suffixes->insert("AT&T", "txt.att.net");
        suffixes->insert("Boost Mobile", "myboostmobile.com");
        suffixes->insert("Cricket Wireless", "mms.cricketwireless.net");
        suffixes->insert("Sprint", "messaging.sprintpcs.com");
        suffixes->insert("T-Mobile", "momail.net");
        suffixes->insert("U.S. Cellular", "email.uscc.net");
        suffixes->insert("Verizon", "vtext.com");
        suffixes->insert("Virgin Mobile", "vmobl.com");
        suffixes->insert("Republic Wireless", "text.republicwireless.com");

        QString suffix = QString("@%1")
                         .arg(suffixes->value(ui->textProviderComboBox->currentText()));

        QString body;

        body.append(QString("Temp -> %1\n").arg(QString::number(prediction.value("temperature").toDouble())));
        body.append(QString("Humid -> %1\n").arg(QString::number(prediction.value("humidity").toDouble())));
        body.append(QString("Press -> %1\n").arg(QString::number(prediction.value("pressure").toDouble())));
        body.append(QString("Vap P -> %1\n").arg(QString::number(prediction.value("vaporPressure").toDouble())));
        body.append(QString("Dew P -> %1\n").arg(QString::number(prediction.value("dewPoint").toDouble())));
        body.append(QString("D Alt -> %1\n").arg(QString::number(prediction.value("densityAltitude").toInt())));
        body.append(QString("W Speed -> %1\n").arg(QString::number(prediction.value("windSpeed").toInt())));
        body.append(QString("W Gust -> %1\n").arg(QString::number(prediction.value("windGust").toInt())));
        body.append(QString("W Dir -> %1\n").arg(QString::number(prediction.value("windDirection").toInt())));

        Smtp *smtp = new Smtp(mSettings->value("emailUser").toString(),
                              mSettings->value("emailPW").toString(),
                              mSettings->value("emailHost").toString());
        //connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

        smtp->sendMail(mSettings->value("emailUser").toString(),
                       QString("%1%2").arg(ui->textNumberEdit->text()).arg(suffix),
                       "Weather",
                       body);
        //delete smtp;

        body.clear();

        if(ui->eToPhoneCheckBox->isChecked()){
//            body.append(QString("By temp -> %1\n").arg(QString::number(prediction->eTp())));
//            body.append(QString("By humidity -> %1\n").arg(QString::number(prediction->eHp())));
//            body.append(QString("By pressure -> %1\n").arg(QString::number(prediction->ePp())));
            body.append(QString("Average -> %1\n").arg(QString::number(prediction.value("eAp").toDouble())));
            body.append(QString("By d alt -> %1\n").arg(QString::number(prediction.value("eDp").toDouble())));
            body.append(QString("Wind correction -> %1\n").arg(QString::number(prediction.value("windCorrectionEighth").toDouble())));

            Smtp *smtpE = new Smtp(mSettings->value("emailUser").toString(),
                                  mSettings->value("emailPW").toString(),
                                  mSettings->value("emailHost").toString());
            //connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

            smtpE->sendMail(mSettings->value("emailUser").toString(),
                           QString("%1%2").arg(ui->textNumberEdit->text()).arg(suffix),
                           "Eighth",
                           body);
            //delete smtpE;
        }

        body.clear();

        if(ui->qToPhoneCheckBox->isChecked()){
//            body.append(QString("By temp -> %1\n").arg(QString::number(prediction->qTp())));
//            body.append(QString("By humidity -> %1\n").arg(QString::number(prediction->qHp())));
//            body.append(QString("By pressure -> %1\n").arg(QString::number(prediction->qPp())));
            body.append(QString("Average -> %1\n").arg(QString::number(prediction.value("qAp").toDouble())));
            body.append(QString("By d alt -> %1\n").arg(QString::number(prediction.value("qDp").toDouble())));
            body.append(QString("Wind correction -> %1\n").arg(QString::number(prediction.value("windCorrectionEighth").toDouble())));

            Smtp *smtpQ = new Smtp(mSettings->value("emailUser").toString(),
                                   mSettings->value("emailPW").toString(),
                                   mSettings->value("emailHost").toString());
            //connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

            smtpQ->sendMail(mSettings->value("emailUser").toString(),
                           QString("%1%2").arg(ui->textNumberEdit->text()).arg(suffix),
                           "Quarter",
                           body);
            //delete smtpQ;

        }
    }
}

void PredictionTab::mailSent(QString status)
{
    if(status == "Message sent")
    {
        qDebug("page sent");
    }
}
