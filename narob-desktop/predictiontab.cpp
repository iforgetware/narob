//#include "prediction.h"
#include "predictiontab.h"
#include "ui_predictiontab.h"
#include "predictionswidget.h"
#include "predictionsmodel.h"

#include "settingsmodel.h"
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
    mPredictionsModel(new PredictionsModel(mVehicle, mRace, this)),
    mTicketsModel(model),
    mObservationModel(new ObservationsModel(this))
{
    ui->setupUi(this);

    PredictionsWidget *predictionsWidget = new PredictionsWidget(mPredictionsModel,
                                                                 this);

    ui->gridLayout_2->addWidget(predictionsWidget, 0, 0);

    ui->vehicleWeightEdit->setText(QString::number(mVehicle->weight()));

    SettingsModel* settingsModel = new SettingsModel();
    mSettings = settingsModel->getSettings();

    ui->textProviderComboBox->setCurrentText(mSettings->textProvider());
    ui->textNumberEdit->setText(mSettings->textNumber());

    ui->minutesSpinBox->setRange(1,15);

    //dev only, make 5
    ui->minutesSpinBox->setValue(1);
    mAutoTimer = new QTimer(this);
    resetTimer(1);

    connect(mAutoTimer, &QTimer::timeout, this, &PredictionTab::makeAutoPrediction);
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

void PredictionTab::resetTimer(int i)
{
    mAutoTimer->start(i * 60000);
}

void PredictionTab::makeAutoPrediction()
{
    Prediction prediction;

    prediction.setVehicleId(mVehicle->id());
    prediction.setRaceId(mRace->id());
    prediction.setRiderWeight(ui->riderWeightEdit->text().toDouble());
    prediction.setVehicleWeight(ui->vehicleWeightEdit->text().toDouble());

    getWeather(prediction);

    predictEighth(prediction);
    predictQuarter(prediction);

    mPredictionsModel->addPrediction(prediction);

    mPredictionsModel->select();

    if(ui->eToPhoneCheckBox->isChecked() ||
       ui->qToPhoneCheckBox->isChecked()){
        sendPage(prediction);
    }

}

void PredictionTab::getWeather(Prediction &prediction)
{
    Observation* observation = new Observation();

    if(prediction.date().isValid() && prediction.time().isValid()){
        observation = mObservationModel->observationForTime(prediction.date(),
                                                            prediction.time());
    }else{
        observation = mObservationModel->lastObservation();
        prediction.setDate(observation->date());
        prediction.setTime(observation->time());
    }

    if(observation){
        prediction.setTemperature(observation->temperature());
        prediction.setHumidity(observation->humidity());
        prediction.setPressure(observation->pressure());
        prediction.setVaporPressure(observation->vaporPressure());
        prediction.setDewPoint(observation->dewPoint());
        prediction.setDensityAltitude(observation->densityAltitude());
        prediction.setWindSpeed(observation->windSpeed());
        prediction.setWindGust(observation->windGust());
        prediction.setWindDirection(observation->windDirection());
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
        valid = false;

        if(!ui->vehicleTicketsCheckBox->isChecked()){
           valid = ticket->trackId() == mRace->trackId();
        }

        if(!ui->trackTicketsCheckBox->isChecked()){
           valid = ticket->raceId() == mRace->id();
        }

        if(valid){
            if(distance == "eighth"){
                valid = ticket->eighthGood();
            }

            if(distance == "quarter"){
                valid = ticket->quarterGood();
            }
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
        tPoints.append(QPointF(ticket->temperature(), ticket->eighth()));
        hPoints.append(QPointF(ticket->humidity(), ticket->eighth()));
        pPoints.append(QPointF(ticket->pressure(), ticket->eighth()));
        dPoints.append(QPointF(ticket->densityAltitude(), ticket->eighth()));

//        RefPT *refpt = new RefPT;

//        refpt->setPrediction(this);
//        refpt->setTicket(&ticket);
//        refpt->setDistance("eighth");

//        refpt->save();

//        delete refpt;
    }

    Line tLine(tPoints);
    Line hLine(hPoints);
    Line pLine(pPoints);
    Line dLine(dPoints);

    prediction.setETp(tLine.getYforX(prediction.temperature()));
    prediction.setEHp(hLine.getYforX(prediction.humidity()));
    prediction.setEPp(pLine.getYforX(prediction.pressure()));
    prediction.setEAp((prediction.eTp() + prediction.eHp() + prediction.ePp()) / 3);
    prediction.setEDp(dLine.getYforX(prediction.densityAltitude()));
}

void PredictionTab::predictQuarter(Prediction &prediction)
{
    Points tPoints;
    Points hPoints;
    Points pPoints;
    Points dPoints;

    QVector<Ticket*> tickets = validTickets("eighth");

    foreach(Ticket* ticket, tickets){
        tPoints.append(QPointF(ticket->temperature(), ticket->quarter()));
        hPoints.append(QPointF(ticket->humidity(), ticket->quarter()));
        pPoints.append(QPointF(ticket->pressure(), ticket->quarter()));
        dPoints.append(QPointF(ticket->densityAltitude(), ticket->quarter()));

//        RefPT *refpt = new RefPT;

//        refpt->setPrediction(this);
//        refpt->setTicket(&ticket);
//        refpt->setDistance("quarter");

//        refpt->save();

//        delete refpt;
    }

    Line tLine(tPoints);
    Line hLine(hPoints);
    Line pLine(pPoints);
    Line dLine(dPoints);

    prediction.setQTp(tLine.getYforX(prediction.temperature()));
    prediction.setQHp(hLine.getYforX(prediction.humidity()));
    prediction.setQPp(pLine.getYforX(prediction.pressure()));
    prediction.setQAp((prediction.qTp() + prediction.qHp() + prediction.qPp()) / 3);
    prediction.setQDp(dLine.getYforX(prediction.densityAltitude()));
}

void PredictionTab::sendPage(const Prediction &prediction)
{
    if(mSettings->emailUser() == ""
       || mSettings->emailHost() == ""
       || mSettings->emailPW() == ""){
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

        body = "Current weather\n";
        body.append(QString("Temp -> %1\n").arg(QString::number(prediction.temperature())));
        body.append(QString("Humid -> %1\n").arg(QString::number(prediction.humidity())));
        body.append(QString("Press -> %1\n").arg(QString::number(prediction.pressure())));
        body.append(QString("Vap P -> %1\n").arg(QString::number(prediction.vaporPressure())));
        body.append(QString("Dew P -> %1\n").arg(QString::number(prediction.dewPoint())));
        body.append(QString("D Alt -> %1\n").arg(QString::number(prediction.densityAltitude())));
        body.append(QString("W Speed -> %1\n").arg(QString::number(prediction.windSpeed())));
        body.append(QString("W Gust -> %1\n").arg(QString::number(prediction.windGust())));
        body.append(QString("W Dir -> %1\n").arg(QString::number(prediction.windDirection())));

        Smtp *smtp = new Smtp(mSettings->emailUser(),
                              mSettings->emailPW(),
                              mSettings->emailHost());
        //connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

        smtp->sendMail(mSettings->emailUser(),
                       QString("%1%2").arg(ui->textNumberEdit->text()).arg(suffix),
                       "Weather",
                       body);
        //delete smtp;

        if(ui->eToPhoneCheckBox->isChecked()){
            body = "Eighth predictions\n";
            body.append(QString("By temp -> %1\n").arg(QString::number(prediction.eTp())));
            body.append(QString("By humidity -> %1\n").arg(QString::number(prediction.eHp())));
            body.append(QString("By pressure -> %1\n").arg(QString::number(prediction.ePp())));
            body.append(QString("Average -> %1\n").arg(QString::number(prediction.eAp())));
            body.append(QString("By d alt -> %1\n").arg(QString::number(prediction.eDp())));

            Smtp *smtpE = new Smtp(mSettings->emailUser(),
                                   mSettings->emailPW(),
                                   mSettings->emailHost());
            //connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

            smtpE->sendMail(mSettings->emailUser(),
                           QString("%1%2").arg(ui->textNumberEdit->text()).arg(suffix),
                           "Eighth",
                           body);
            //delete smtpE;
        }

        if(ui->qToPhoneCheckBox->isChecked()){
            body = "Quarter predictions\n";
            body.append(QString("By temp -> %1\n").arg(QString::number(prediction.qTp())));
            body.append(QString("By humidity -> %1\n").arg(QString::number(prediction.qHp())));
            body.append(QString("By pressure -> %1\n").arg(QString::number(prediction.qPp())));
            body.append(QString("Average -> %1\n").arg(QString::number(prediction.qAp())));
            body.append(QString("By d alt -> %1\n").arg(QString::number(prediction.qDp())));

            Smtp *smtpQ = new Smtp(mSettings->emailUser(),
                                  mSettings->emailPW(),
                                  mSettings->emailHost());
            //connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

            smtpQ->sendMail(mSettings->emailUser(),
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
