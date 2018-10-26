#include "predictiontab.h"
#include "ui_predictiontab.h"
#include "predictions.h"
#include "settings.h"
#include "smtp.h"

#include <QDebug>
#include <QVector>

PredictionTab::PredictionTab(TicketsModel *model,
                             Vehicle *vehicle,
                             Race *race,
                             QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PredictionTab),
    mVehicle(vehicle),
    mRace(race),
    mSettingsTable(new Settings),
    mSettings(mSettingsTable->getSettings()),
    mPredictionsModel(new PredictionsModel(mVehicle, mRace, 0, this)),
    mTicketsModel(model),
    mAutoTimer(new QTimer(this)),
    mFactorTimer(new QTimer(this))
{
    ui->setupUi(this);

    mPreviousPredictionsWidget = new PreviousPredictionsWidget(
                                     mPredictionsModel,
                                     this);

    ui->gridLayout_2->addWidget(mPreviousPredictionsWidget, 0, 0);

//    mSettings = mSettingsTable->getSettings();

    ui->vehicleWeightSpinBox->setValue(mVehicle->value("weight").toInt());
    ui->riderWeightSpinBox->setValue(mTicketsModel->lastWeight());

    ui->weightAdjustmentSpinBox->setValue(mVehicle->value("weightAdjustment")
                                          .toDouble());
    ui->windAdjustmentSpinBox->setValue(mVehicle->value("windAdjustment")
                                        .toDouble());
    ui->textProviderComboBox->setCurrentText(mVehicle->value("textProvider")
                                             .toString());
    ui->textNumberEdit->setText(mVehicle->value("textNumber")
                                .toString());

    mCurrentPrediction = new Prediction(mVehicle->value("id").toInt(),
                                        mRace->value("trackId").toInt(),
                                        mRace->value("id").toInt(),
                                        0);

    connect(ui->vehicleWeightSpinBox,
            QOverload<int>::of(&QSpinBox::valueChanged),
            this,
            &PredictionTab::onFactorChange);

    connect(ui->riderWeightSpinBox,
            QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this,
            &PredictionTab::onFactorChange);

    connect(ui->windAdjustmentSpinBox,
            QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this,
            &PredictionTab::onFactorChange);

    connect(ui->weightAdjustmentSpinBox,
            QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this,
            &PredictionTab::onFactorChange);

    connect(mAutoTimer, &QTimer::timeout,
            this, &PredictionTab::makePrediction);

    connect(mFactorTimer, &QTimer::timeout,
            this, &PredictionTab::makePrediction);

    mAutoTimer->start(60000);
}

PredictionTab::~PredictionTab()
{
    delete mAutoTimer;
    delete mFactorTimer;
    delete ui;
}

void PredictionTab::UpdateAllModels()
{
    mPreviousPredictionsWidget->updateModel();
}

void PredictionTab::onFactorChange()
{
    mFactorTimer->start(CHANGE_DELAY);
}

void PredictionTab::makePrediction()
{
    mCurrentPrediction->setValue("dateTime", QDateTime());
    mCurrentPrediction->setValue("riderWeight", ui->riderWeightSpinBox->value());
    mCurrentPrediction->setValue("vehicleWeight", ui->vehicleWeightSpinBox->value());
    mCurrentPrediction->setValue("windAdjustment", ui->windAdjustmentSpinBox->value());
    mCurrentPrediction->setValue("weightAdjustment", ui->weightAdjustmentSpinBox->value());

    mCurrentPrediction->predictClocks(ui->vehicleTicketsCheckBox->isChecked(),
                             ui->trackTicketsCheckBox->isChecked(),
                             mTicketsModel);

    int minute = mCurrentPrediction->value("dateTime")
                 .toDateTime()
                 .time()
                 .minute();

    if(minute % 5 == 0){
        writePredictionToDb();
    }

    updateDisplay();

    mFactorTimer->stop();
}

void PredictionTab::writePredictionToDb()
{
    mPredictionsModel->addRow(*mCurrentPrediction);

    if(ui->eToPhoneCheckBox->isChecked() || ui->qToPhoneCheckBox->isChecked()){
        sendPage();
    }

    while(mPredictionsModel->rowCount(QModelIndex()) > 5){
        mPredictionsModel->removeRow(mPredictionsModel->rowCount(QModelIndex()) - 1);
        mPredictionsModel->submitAll();
        mPreviousPredictionsWidget->updateModel();
    }
}

void PredictionTab::updateDisplay()
{
    updatePLabel("sixtyD", ui->sixtyD);
    updatePLabel("threeThirtyD", ui->threeThirtyD);
    updatePLabel("eighthD", ui->eighthD);
    updatePLabel("thousandD", ui->thousandD);
    updatePLabel("quarterD", ui->quarterD);

    updatePLabel("sixtyA", ui->sixtyA);
    updatePLabel("threeThirtyA", ui->threeThirtyA);
    updatePLabel("eighthA", ui->eighthA);
    updatePLabel("thousandA", ui->thousandA);
    updatePLabel("quarterA", ui->quarterA);

    updatePLabel("sixtyT", ui->sixtyT);
    updatePLabel("threeThirtyT", ui->threeThirtyT);
    updatePLabel("eighthT", ui->eighthT);
    updatePLabel("thousandT", ui->thousandT);
    updatePLabel("quarterT", ui->quarterT);

    updatePLabel("sixtyH", ui->sixtyH);
    updatePLabel("threeThirtyH", ui->threeThirtyH);
    updatePLabel("eighthH", ui->eighthH);
    updatePLabel("thousandH", ui->thousandH);
    updatePLabel("quarterH", ui->quarterH);

    updatePLabel("sixtyP", ui->sixtyP);
    updatePLabel("threeThirtyP", ui->threeThirtyP);
    updatePLabel("eighthP", ui->eighthP);
    updatePLabel("thousandP", ui->thousandP);
    updatePLabel("quarterP", ui->quarterP);
}

void PredictionTab::updatePLabel(const QString &field, QLabel *label)
{
    label->setText(QString::number(mCurrentPrediction->value(field).toDouble(),
                                   'f',
                                   3));
}

void PredictionTab::sendPage()
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

        QString body("\n");

        body.append(QString("%1\n")
                    .arg(QString(mCurrentPrediction->value("dateTime")
                                 .toTime().toString("hh:mm"))));
        body.append(QString("Temp -> %1\n")
                    .arg(QString::number(mCurrentPrediction->value("temperature")
                                         .toDouble())));
        body.append(QString("Humid -> %1\n")
                    .arg(QString::number(mCurrentPrediction->value("humidity")
                                         .toDouble())));
        body.append(QString("Press -> %1\n")
                    .arg(QString::number(mCurrentPrediction->value("pressure")
                                         .toDouble())));
        body.append(QString("Vap P -> %1\n")
                    .arg(QString::number(mCurrentPrediction->value("vaporPressure")
                                         .toDouble())));
        body.append(QString("Dew P -> %1\n")
                    .arg(QString::number(mCurrentPrediction->value("dewPoint")
                                         .toDouble())));
        body.append(QString("D Alt -> %1\n")
                    .arg(QString::number(mCurrentPrediction->value("densityAltitude")
                                         .toInt())));
        body.append(QString("W Speed -> %1\n")
                    .arg(QString::number(mCurrentPrediction->value("windSpeed")
                                         .toInt())));
        body.append(QString("W Gust -> %1\n")
                    .arg(QString::number(mCurrentPrediction->value("windGust")
                                         .toInt())));
        body.append(QString("W Dir -> %1\n")
                    .arg(QString::number(mCurrentPrediction->value("windDirection")
                                         .toInt())));

        Smtp *smtpW = new Smtp(this);
        //connect(smtpW, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

        smtpW->sendMail(QString("%1%2")
                        .arg(ui->textNumberEdit->text())
                        .arg(suffix),
                        "Weather",
                        body);

        body.clear();

        if(ui->eToPhoneCheckBox->isChecked()){
            body.append("Predictions\n");
            body.append(QString("By d alt -> %1\n")
                        .arg(QString::number(mCurrentPrediction->value("eighthD")
                                             .toDouble())));
            body.append(QString("Average -> %1\n")
                        .arg(QString::number(mCurrentPrediction->value("eighthA")
                                             .toDouble())));

            Smtp *smtpE = new Smtp(this);
            //connect(smtpE, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

            smtpE->sendMail(QString("%1%2")
                            .arg(ui->textNumberEdit->text())
                            .arg(suffix),
                            "Eighth",
                            body);
        }

        body.clear();

        if(ui->qToPhoneCheckBox->isChecked()){
            body.append("Predictions\n");
            body.append(QString("By d alt -> %1\n")
                        .arg(QString::number(mCurrentPrediction->value("quarterD")
                                             .toDouble())));
            body.append(QString("Average -> %1\n")
                        .arg(QString::number(mCurrentPrediction->value("quarterA")
                                             .toDouble())));

            Smtp *smtpQ = new Smtp(this);
            //connect(smtpQ, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

            smtpQ->sendMail(QString("%1%2")
                            .arg(ui->textNumberEdit->text())
                            .arg(suffix),
                            "Quarter",
                            body);
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
