#include <QDataWidgetMapper>

#include "predictiontab.h"
#include "ui_predictiontab.h"
#include "predictionswidget.h"
#include "predictions.h"

//#include "settingsmodel.h"
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
    mObservationsModel(new ObservationsModel(this)),
    mRefPTsModel(new RefPTsModel(this))
{








    // ???? add instantaneous prediction ????
    // would reset on any value change










    ui->setupUi(this);

    PredictionsWidget *predictionsWidget = new PredictionsWidget(mPredictionsModel,
                                                                 this);

    ui->gridLayout_2->addWidget(predictionsWidget, 0, 0);

    ui->vehicleWeightEdit->setText(QString::number(mVehicle->value("weight").toInt()));

//    SettingsModel* settingsModel = new SettingsModel();
//    mSettings = settingsModel->getSettings();

    ui->textProviderComboBox->setCurrentText("Verizon"); //mSettings->textProvider());
    ui->textNumberEdit->setText("5042895449"); //mSettings->textNumber());

    mAutoTimer = new QTimer(this);
    resetTimer(ui->minutesSpinBox->value());

    connect(mAutoTimer,
            &QTimer::timeout,
            this,
            &PredictionTab::makeAutoPrediction);
    connect(ui->makePredictionButton,
            &QPushButton::clicked,
            this,
            &PredictionTab::makeAutoPrediction);
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

    prediction.setValue("vehicleId", mVehicle->value("id").toInt());
    prediction.setValue("raceId", mRace->value("id").toInt());
    prediction.setValue("riderWeight", ui->riderWeightEdit->text().toDouble());
    prediction.setValue("vehicleWeight", ui->vehicleWeightEdit->text().toDouble());

    prediction.setValue("windFactor", ui->windFactorSpinBox->value());
    prediction.setValue("weightFactor", ui->weightFactorSpinBox->value());

    getWeather(prediction);
    predictEighth(prediction);
    predictQuarter(prediction);

    mPredictionsModel->addPrediction(prediction);

    if(ui->eToPhoneCheckBox->isChecked() ||
       ui->qToPhoneCheckBox->isChecked()){
        sendPage(prediction);
    }

}

void PredictionTab::getWeather(Prediction &prediction)
{
    Observation* observation = new Observation();

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

        qDebug("before distance checks");
        qDebug() << distance;
        qDebug() << valid;
        if(valid){
            if(distance == "eighth"){
                valid = ticket->value("eighthGood").toBool();
            }

            if(distance == "quarter"){
                valid = ticket->value("quarterGood").toBool();
            }
        }
        qDebug("after distance checks");
        qDebug() << valid;

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
            qDebug("denominator ZERO - WRITE CODE");
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
                                - (windCorrection(ticket->value("windSpeed").toInt(),
                                   ticket->value("windDirection").toInt())
                                   / 2)
                                + (weightCorrection(prediction.value("riderWeight").toDouble(),
                                                   ticket->value("riderWeight").toDouble())
                                   / 2);
        tPoints.append(QPointF(ticket->value("temperature").toDouble(), adjustedEighth));
        hPoints.append(QPointF(ticket->value("humidity").toDouble(), adjustedEighth));
        pPoints.append(QPointF(ticket->value("pressure").toDouble(), adjustedEighth));
        dPoints.append(QPointF(ticket->value("densityAltitude").toInt(), adjustedEighth));

        RefPT refPT;

        refPT.setValue("predictionId", prediction.value("id").toInt());
        refPT.setValue("ticketId", ticket->value("id").toInt());
        refPT.setValue("distance", "eighth");

        mRefPTsModel->addRefPT(refPT);
    }

    Line tLine(tPoints);
    Line hLine(hPoints);
    Line pLine(pPoints);
    Line dLine(dPoints);

    double wC = windCorrection(prediction.value("windSpeed").toInt(),
                               prediction.value("windDirection").toInt())
                / 2;

    prediction.setValue("eTp", wC + tLine.getYforX(prediction.value("temperature").toDouble()));
    prediction.setValue("eHp", wC + hLine.getYforX(prediction.value("humidity").toDouble()));
    prediction.setValue("ePp", wC + pLine.getYforX(prediction.value("pressure").toDouble()));
    prediction.setValue("eAp", ((prediction.value("eTp").toDouble()
                                  + prediction.value("eHp").toDouble()
                                  + prediction.value("ePp").toDouble()) / 3));
    prediction.setValue("eDp", wC + dLine.getYforX(prediction.value("densityAltitude").toInt()));
    prediction.setValue("windCorrectionEighth", wC);
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
                                 - windCorrection(ticket->value("windSpeed").toInt(),
                                                  ticket->value("windDirection").toInt())
                                 + weightCorrection(prediction.value("riderWeight").toDouble(),
                                                    ticket->value("riderWeight").toDouble());

        tPoints.append(QPointF(ticket->value("temperature").toDouble(), adjustedQuarter));
        hPoints.append(QPointF(ticket->value("humidity").toDouble(), adjustedQuarter));
        pPoints.append(QPointF(ticket->value("pressure").toDouble(), adjustedQuarter));
        dPoints.append(QPointF(ticket->value("densityAltitude").toInt(), adjustedQuarter));

        RefPT refPT;

        refPT.setValue("predictionId", prediction.value("id").toInt());
        refPT.setValue("ticketId", ticket->value("id").toInt());
        refPT.setValue("distance", "quarter");

        mRefPTsModel->addRefPT(refPT);
    }

    Line tLine(tPoints);
    Line hLine(hPoints);
    Line pLine(pPoints);
    Line dLine(dPoints);

    double wC = windCorrection(prediction.value("windSpeed").toInt(),
                               prediction.value("windDirection").toInt());

    prediction.setValue("qTp", wC + tLine.getYforX(prediction.value("temperature").toDouble()));
    prediction.setValue("qHp", wC + hLine.getYforX(prediction.value("humidity").toDouble()));
    prediction.setValue("qPp", wC + pLine.getYforX(prediction.value("pressure").toDouble()));
    prediction.setValue("qAp", (prediction.value("qTp").toDouble()
                                 + prediction.value("qHp").toDouble()
                                 + prediction.value("qPp").toDouble()) / 3);
    prediction.setValue("qDp", wC + dLine.getYforX(prediction.value("densityAltitude").toInt()));
    prediction.setValue("windCorrectionQuarter", wC);
}

double PredictionTab::windCorrection(int windSpeed, int windDirection)
{
    double correction = 0;
    double dFactor;

    if(windDirection < 50){
        dFactor = (50 - windDirection) * 0.02;
        correction = ui->windFactorSpinBox->value()
                     * 0.002
                     * windSpeed
                     * dFactor;
    }

    if(windDirection > 130){
        dFactor = (windDirection - 130) * -0.02;
        correction = ui->windFactorSpinBox->value()
                     * 0.002
                     * windSpeed
                     * dFactor;
    }

    return correction;
}

double PredictionTab::weightCorrection(double w1, double w2)
{
    return (w1 - w2) * ui->weightFactorSpinBox->value() * 0.001;
}

void PredictionTab::sendPage(const Prediction &prediction)
{
//    if(mSettings->emailUser() == ""
//       || mSettings->emailHost() == ""
//       || mSettings->emailPW() == ""){
//        qDebug("No email settings to page with - WRITE CODE");
//    }else{
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

        qDebug("predTab 387, set pw");

        Smtp *smtp = new Smtp("davesspeedshop@gmail.com", //mSettings->emailUser(),
                              "", //mSettings->emailPW(),
                              "smtp.gmail.com"); //mSettings->emailHost());
        //connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

        smtp->sendMail("davesspeedshop@gmail.com", //mSettings->emailUser(),
                       QString("%1%2").arg(ui->textNumberEdit->text()).arg(suffix),
                       "Weather",
                       body);
        //delete smtp;

        if(ui->eToPhoneCheckBox->isChecked()){
//            body.append(QString("By temp -> %1\n").arg(QString::number(prediction->eTp())));
//            body.append(QString("By humidity -> %1\n").arg(QString::number(prediction->eHp())));
//            body.append(QString("By pressure -> %1\n").arg(QString::number(prediction->ePp())));
            body.append(QString("Average -> %1\n").arg(QString::number(prediction.value("eAp").toDouble())));
            body.append(QString("By d alt -> %1\n").arg(QString::number(prediction.value("eDp").toDouble())));
            body.append(QString("Wind correction -> %1\n").arg(QString::number(prediction.value("windCorrectionEighth").toDouble())));

            qDebug("predTab 408, set pw");

            Smtp *smtpE = new Smtp("davesspeedshop@gmail.com", //mSettings->emailUser(),
                                  "", //mSettings->emailPW(),
                                  "smtp.gmail.com"); //mSettings->emailHost());
            //connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

            smtpE->sendMail("davesspeedshop@gmail.com", //mSettings->emailUser(),
                           QString("%1%2").arg(ui->textNumberEdit->text()).arg(suffix),
                           "Eighth",
                           body);
            //delete smtpE;
        }

        if(ui->qToPhoneCheckBox->isChecked()){
//            body.append(QString("By temp -> %1\n").arg(QString::number(prediction->qTp())));
//            body.append(QString("By humidity -> %1\n").arg(QString::number(prediction->qHp())));
//            body.append(QString("By pressure -> %1\n").arg(QString::number(prediction->qPp())));
            body.append(QString("Average -> %1\n").arg(QString::number(prediction.value("qAp").toDouble())));
            body.append(QString("By d alt -> %1\n").arg(QString::number(prediction.value("qDp").toDouble())));
            body.append(QString("Wind correction -> %1\n").arg(QString::number(prediction.value("windCorrectionEighth").toDouble())));

            qDebug("predTab 430, set pw");

            Smtp *smtpQ = new Smtp("davesspeedshop@gmail.com", //mSettings->emailUser(),
                                  "", //mSettings->emailPW(),
                                  "smtp.gmail.com"); //mSettings->emailHost());
            //connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

            smtpQ->sendMail("davesspeedshop.@gmail.com", //mSettings->emailUser(),
                           QString("%1%2").arg(ui->textNumberEdit->text()).arg(suffix),
                           "Quarter",
                           body);
            //delete smtpQ;

        }
//    }
}

void PredictionTab::mailSent(QString status)
{
    if(status == "Message sent")
    {
        qDebug("page sent");
    }
}
