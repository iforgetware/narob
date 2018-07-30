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
    mPredictionsModel(new PredictionsModel(mVehicle, mRace, this)),
    mTicketsModel(model),
    mObservationsModel(new ObservationsModel(this)),
    mRefPTsModel(new RefPTsModel(this))
{








    // ???? add instantaneous prediction ????
    // would reset on any value change










    ui->setupUi(this);

    mPredictionsWidget = new PredictionsWidget(mPredictionsModel,
                                               this);

    ui->gridLayout_2->addWidget(mPredictionsWidget, 0, 0);

    mSettings = mSettingsTable->getSettings();

    ui->vehicleWeightSpinBox->setValue(mVehicle->value("weight").toInt());
    ui->riderWeightSpinBox->setValue(mTicketsModel->lastWeight());

    ui->weightAdjustmentSpinBox->setValue(mSettings->value("weightAdjustment").toDouble());
    ui->windAdjustmentSpinBox->setValue(mSettings->value("windAdjustment").toDouble());
    ui->textProviderComboBox->setCurrentText(mSettings->value("textProvider").toString());
    ui->textNumberEdit->setText(mSettings->value("textNumber").toString());

    mAutoTimer = new QTimer(this);
    resetTimer(ui->minutesSpinBox->value());

    connect(mAutoTimer,
            &QTimer::timeout,
            this,
            &PredictionTab::makePrediction);
    connect(ui->makePredictionButton,
            &QPushButton::clicked,
            this,
            &PredictionTab::makePrediction);
    connect(ui->minutesSpinBox,
            static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this,
            &PredictionTab::resetTimer);
}

PredictionTab::~PredictionTab()
{
    delete mAutoTimer;
    delete ui;
}

void PredictionTab::UpdateAllModels()
{
    mPredictionsWidget->updateModel();
}

void PredictionTab::resetTimer(int i)
{
    mAutoTimer->start(i * 60000);
}

void PredictionTab::makePrediction()
{
    Prediction prediction;

    prediction.setValue("vehicleId", mVehicle->value("id").toInt());
    prediction.setValue("raceId", mRace->value("id").toInt());
    prediction.setValue("riderWeight", ui->riderWeightSpinBox->value());
    prediction.setValue("vehicleWeight", ui->vehicleWeightSpinBox->value());

    prediction.setValue("windAdjustment", ui->windAdjustmentSpinBox->value());
    prediction.setValue("weightAdjustment", ui->weightAdjustmentSpinBox->value());

    getWeather(prediction);
    predictEighth(prediction);
    predictQuarter(prediction);

    mPredictionsModel->addRow(prediction);

    int predictionId = mPredictionsModel->query().lastInsertId().toInt();

    foreach(RefPT refPT, mRefPTList){
        refPT.setValue("predictionId", predictionId);
        mRefPTsModel->addRow(refPT);
    }

    mRefPTList.clear();

    if(ui->eToPhoneCheckBox->isChecked() ||
       ui->qToPhoneCheckBox->isChecked()){
        sendPage(prediction);
    }

}

void PredictionTab::getWeather(Prediction &prediction)
{
    Observation* observation = new Observation();
    mObservationsModel->select();
    if(prediction.value("dateTime").toDateTime().isValid()){
        observation = mObservationsModel->observationForTime(prediction.value("dateTime").toDateTime());
    }else{
        observation = mObservationsModel->lastObservation();
        prediction.setValue("DateTime", observation->value("dateTime").toDateTime());
    }

    if(observation){
        prediction.setValue("temperature", observation->value("temperature"));
        prediction.setValue("humidity", observation->value("humidity"));
        prediction.setValue("pressure", observation->value("pressure"));
        prediction.setValue("vaporPressure", observation->value("vaporPressure"));
        prediction.setValue("dewPoint", observation->value("dewPoint"));
        prediction.setValue("densityAltitude" ,observation->value("densityAltitude"));
        prediction.setValue("windSpeed", observation->value("windSpeed"));
        prediction.setValue("windGust", observation->value("windGust"));
        prediction.setValue("windDirection", observation->value("windDirection"));
    }else{
        qDebug("Weather not found - WRITE CODE");
    }

    delete observation;
}

QVector<Ticket*> PredictionTab::validTickets(const QString &distance)
{
    QVector<Ticket*> tickets;

    bool valid;

    foreach(Ticket* ticket, mTicketsModel->tickets()){
        valid = true;

        if(!ui->vehicleTicketsCheckBox->isChecked()){
            valid = ticket->value("trackId") == mRace->value("trackId");

            if(!ui->trackTicketsCheckBox->isChecked()){
                valid = ticket->value("raceId") == mRace->value("id");
            }
        }

        if(valid){
            valid = ticket->value(distance + "Good").toBool();
        }

        if(valid){
            tickets.append(ticket);
        }
    }

    return tickets;
}

typedef QList<QPointF> Points;

struct Line
{
    double mSlope;
    double mIntercept;

    Line(Points &pts)
    {
        int nPoints = pts.size();

        qreal sumX = 0, sumY = 0, sumXY = 0, sumX2 = 0;

        for(int i = 0;i < nPoints; i++) {
            sumX += pts[i].rx();
            sumY += pts[i].ry();
            sumXY += pts[i].rx() * pts[i].ry();
            sumX2 += pts[i].rx() * pts[i].rx();
        }

        double xMean = sumX / nPoints;
        double yMean = sumY / nPoints;
        double denominator = sumX2 - sumX * xMean;

        if(!denominator){
            denominator = 0.000001;
            //qDebug("denominator ZERO - WRITE CODE");
        }

        mSlope = (sumXY - (sumX * yMean)) / denominator;
        mIntercept = yMean - (mSlope * xMean);
    }

    double getYforX(double x)
    {
        return (mSlope * x) + mIntercept;
    }
};

void PredictionTab::predictEighth(Prediction &prediction)
{
    Points tPoints;
    Points hPoints;
    Points pPoints;
    Points dPoints;

    QVector<Ticket*> tickets = validTickets("eighth");

    foreach(Ticket* ticket, tickets){
        double adjustedEighth = ticket->value("eighth").toDouble()
                                + (windCorrection(prediction, ticket) / 2)
                                + (weightCorrection(prediction, ticket) / 2);
        tPoints.append(QPointF(ticket->value("temperature").toDouble(), adjustedEighth));
        hPoints.append(QPointF(ticket->value("humidity").toDouble(), adjustedEighth));
        pPoints.append(QPointF(ticket->value("pressure").toDouble(), adjustedEighth));
        dPoints.append(QPointF(ticket->value("densityAltitude").toInt(), adjustedEighth));

        RefPT refPT;

        refPT.setValue("ticketId", ticket->value("id").toInt());
        refPT.setValue("distance", "eighth");

        mRefPTList.append(refPT);
    }

    Line tLine(tPoints);
    Line hLine(hPoints);
    Line pLine(pPoints);
    Line dLine(dPoints);

    prediction.setValue("eTp", tLine.getYforX(prediction.value("temperature").toDouble()));
    prediction.setValue("eHp", hLine.getYforX(prediction.value("humidity").toDouble()));
    prediction.setValue("ePp", pLine.getYforX(prediction.value("pressure").toDouble()));
    prediction.setValue("eAp", ((prediction.value("eTp").toDouble()
                                  + prediction.value("eHp").toDouble()
                                  + prediction.value("ePp").toDouble()) / 3));
    prediction.setValue("eDp", dLine.getYforX(prediction.value("densityAltitude").toInt()));
}

void PredictionTab::predictQuarter(Prediction &prediction)
{
    Points tPoints;
    Points hPoints;
    Points pPoints;
    Points dPoints;

    QVector<Ticket*> tickets = validTickets("quarter");

    foreach(Ticket* ticket, tickets){
        double adjustedQuarter = ticket->value("quarter").toDouble()
                                 + windCorrection(prediction, ticket)
                                 + weightCorrection(prediction, ticket);

        tPoints.append(QPointF(ticket->value("temperature").toDouble(), adjustedQuarter));
        hPoints.append(QPointF(ticket->value("humidity").toDouble(), adjustedQuarter));
        pPoints.append(QPointF(ticket->value("pressure").toDouble(), adjustedQuarter));
        dPoints.append(QPointF(ticket->value("densityAltitude").toInt(), adjustedQuarter));

        RefPT refPT;

        refPT.setValue("ticketId", ticket->value("id").toInt());
        refPT.setValue("distance", "quarter");

        mRefPTList.append(refPT);
    }

    Line tLine(tPoints);
    Line hLine(hPoints);
    Line pLine(pPoints);
    Line dLine(dPoints);

    prediction.setValue("qTp", tLine.getYforX(prediction.value("temperature").toDouble()));
    prediction.setValue("qHp", hLine.getYforX(prediction.value("humidity").toDouble()));
    prediction.setValue("qPp", pLine.getYforX(prediction.value("pressure").toDouble()));
    prediction.setValue("qAp", (prediction.value("qTp").toDouble()
                                 + prediction.value("qHp").toDouble()
                                 + prediction.value("qPp").toDouble()) / 3);
    prediction.setValue("qDp", dLine.getYforX(prediction.value("densityAltitude").toInt()));
}

double windFactor(int windSpeed, int windDirection)
{
    double wFactor = 0;
    double dFactor = 0;

    if(windDirection < 50){
        dFactor = (50 - windDirection) * 0.02;
    }

    if(windDirection > 130){
        dFactor = (windDirection - 130) * -0.02;
    }

    wFactor = windSpeed
              * dFactor;

    return wFactor;

}

double PredictionTab::windCorrection(Prediction &prediction, Ticket *ticket)
{
    // wind direction   0 = headwind ( higher ET )
    //                180 = tailwind ( lower ET )
    double correction = 0;
    double windDifference = 0;

    windDifference = windFactor(prediction.value("windSpeed").toInt(),
                                prediction.value("windDirection").toInt()) -
                     windFactor(ticket->value("windSpeed").toInt(),
                                 ticket->value("windDirection").toInt());
    correction = windDifference * ui->windAdjustmentSpinBox->value();

    return correction;
}

double PredictionTab::weightCorrection(Prediction &prediction, Ticket *ticket)
{
    double correction = 0;
    double weightDifference = 0;

    weightDifference = (prediction.value("riderWeight").toDouble() +
                        prediction.value("vehicleWeight").toDouble()) -
                       (ticket->value("riderWeight").toDouble() +
                        ticket->value("vehicleWeight").toDouble());
    correction = weightDifference * ui->weightAdjustmentSpinBox->value();

    return correction;
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
