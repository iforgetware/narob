#include <QSqlQuery>
#include <QMessageBox>

#include "autotab.h"
#include "ui_autotab.h"
#include "settings.h"
#include "smtp.h"
#include "previouspredictionsdialog.h"
#include "databasemanager.h"

AutoTab::AutoTab(TicketsLogbookModel *tLModel,
                 std::shared_ptr<Vehicle> vehicle,
                 std::shared_ptr<Race> race,
                 QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AutoTab),
    mVehicleId(vehicle->value("id").toInt()),
    mTrackId(race->value("trackId").toInt()),
    mRaceId(race->value("id").toInt()),
    mCurrentPrediction(Prediction(tLModel,
                                  mVehicleId,
                                  mTrackId,
                                  mRaceId,
                                  0)),
    mPredictionsModel(new PredictionsModel(mVehicleId,
                                           mRaceId,
                                           0,
                                           this)),
    mTicketsLogbookModel(tLModel),
    mAutoTimer(new QTimer(this)),
    mFactorTimer(new QTimer(this)),
    mEChartView(new QChartView(new QChart(), this)),
    mQChartView(new QChartView(new QChart(), this)),
    mEighthMedian(new QLineSeries),
    mQuarterMedian(new QLineSeries),
    mEighthRunsScatter(new QScatterSeries),
    mQuarterRunsScatter(new QScatterSeries),
    mECPScatter(new QScatterSeries),
    mQCPScatter(new QScatterSeries),
    mEighthDAAxis(new QValueAxis(mEChartView)),
    mEighthETAxis(new QValueAxis(mEChartView)),
    mQuarterDAAxis(new QValueAxis(mQChartView)),
    mQuarterETAxis(new QValueAxis(mQChartView)),
    mEHoverInfo(new Callout(mEChartView->chart())),
    mQHoverInfo(new Callout(mQChartView->chart()))
{
    ui->setupUi(this);

    ui->gridLayout_6->addWidget(mEChartView, 1, 0, 1, 1);
    ui->gridLayout_6->addWidget(mQChartView, 1, 1, 1, 1);

    mEChartView->setRenderHint(QPainter::Antialiasing);
    mQChartView->setRenderHint(QPainter::Antialiasing);

    setupGraph();

    ui->vehicleWeightSpinBox->setValue(vehicle->value("weight").toInt());
    ui->riderWeightSpinBox->setValue(mTicketsLogbookModel->lastWeight());

    ui->weightAdjustmentSpinBox->setValue(vehicle->value("weightAdjustment")
                                          .toDouble());
    ui->windAdjustmentSpinBox->setValue(vehicle->value("windAdjustment")
                                        .toDouble());

    ui->textProviderComboBox->setCurrentText(vehicle->value("textProvider")
                                             .toString());
    ui->textNumberEdit->setText(vehicle->value("textNumber")
                                .toString());

    for(QLabel *label: {ui->temperatureLabel,
                        ui->sixtyT,
                        ui->threeThirtyT,
                        ui->eighthT,
                        ui->thousandT,
                        ui->quarterT}){
        label->setStyleSheet("color: " + T_COLOR.name());
    }

    for(QLabel *label: {ui->humidityLabel,
                        ui->sixtyH,
                        ui->threeThirtyH,
                        ui->eighthH,
                        ui->thousandH,
                        ui->quarterH}){
        label->setStyleSheet("color: " + H_COLOR.name());
    }

    for(QLabel *label: {ui->pressureLabel,
                        ui->sixtyP,
                        ui->threeThirtyP,
                        ui->eighthP,
                        ui->thousandP,
                        ui->quarterP}){
        label->setStyleSheet("color: " + P_COLOR.name());
    }

    for(QLabel *label: {ui->averageLabel,
                        ui->sixtyA,
                        ui->threeThirtyA,
                        ui->eighthA,
                        ui->thousandA,
                        ui->quarterA}){
        label->setStyleSheet("color: " + A_COLOR.name());
    }

    for(QLabel *label: {ui->densityALabel,
                        ui->sixtyD,
                        ui->threeThirtyD,
                        ui->eighthD,
                        ui->thousandD,
                        ui->quarterD}){
        label->setStyleSheet("color: " + D_COLOR.name());
    }

    connect(ui->autoPredictCheckBox,
            &QCheckBox::stateChanged,
            this,
            &AutoTab::onAutoCheckboxChange);

    connect(ui->vehicleWeightSpinBox,
            QOverload<int>::of(&QSpinBox::valueChanged),
            this,
            &AutoTab::onFactorChange);

    connect(ui->riderWeightSpinBox,
            QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this,
            &AutoTab::onFactorChange);

    connect(ui->windAdjustmentSpinBox,
            QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this,
            &AutoTab::onFactorChange);

    connect(ui->weightAdjustmentSpinBox,
            QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this,
            &AutoTab::onFactorChange);

    connect(ui->trackTicketsCheckBox,
            &QCheckBox::stateChanged,
            this,
            &AutoTab::onTrackTicketsCheckboxChange);

    connect(ui->vehicleTicketsCheckBox,
            &QCheckBox::stateChanged,
            this,
            &AutoTab::onVehicleTicketsCheckboxChange);

    connect(mFactorTimer, &QTimer::timeout,
            this, &AutoTab::makePrediction);

    connect(mAutoTimer, &QTimer::timeout,
            this, &AutoTab::autoPredict);

    connect(ui->previousPredictionsButton, &QPushButton::clicked,
            this, &AutoTab::onShowPreviousPredictionsClicked);

    connect(mEighthRunsScatter, &QScatterSeries::hovered,
            this, &AutoTab::onEPointHover);

    connect(mEighthRunsScatter, &QScatterSeries::clicked,
            this, &AutoTab::onEPointClick);

    connect(mQuarterRunsScatter, &QScatterSeries::hovered,
            this, &AutoTab::onQPointHover);

    connect(mQuarterRunsScatter, &QScatterSeries::clicked,
            this, &AutoTab::onQPointClick);

    startAutoTimer();
}

AutoTab::~AutoTab()
{
    delete mAutoTimer;
    delete mFactorTimer;
    delete ui;
}

void AutoTab::startAutoTimer()
{
    mAutoTimer->start(60000);
}

void AutoTab::stopAutoTimer()
{
    mAutoTimer->stop();
}

void AutoTab::updateAllModels()
{
    makePrediction();
    qDebug("auto tab update all models");
}

void AutoTab::autoPredict()
{
    if(ui->autoPredictCheckBox->isChecked()){
        makePrediction();
    }
}

void AutoTab::makePrediction()
{
    mCurrentPrediction.predictByTime(QDateTime(),
                                      ui->riderWeightSpinBox->value(),
                                      ui->vehicleWeightSpinBox->value(),
                                      ui->windAdjustmentSpinBox->value(),
                                      ui->weightAdjustmentSpinBox->value(),
                                      ui->vehicleTicketsCheckBox->isChecked(),
                                      ui->trackTicketsCheckBox->isChecked());

    int minute = mCurrentPrediction.value("dateTime")
                 .toDateTime()
                 .time()
                 .minute();

    if(minute % 5 == 0){
        writePredictionToDb();
    }

    updateDisplay();

    updateGraph();

    mFactorTimer->stop();
}

void AutoTab::setupGraph()
{
    mEighthDAAxis->setLinePenColor(Qt::black);
    mEighthDAAxis->setLabelFormat("%i");
    mEighthETAxis->setLinePenColor(Qt::black);
    mEighthETAxis->setLabelFormat("%5.2f");

    mEighthMedian->setName("Median");
    mEighthMedian->setColor(D_COLOR);
    mEighthRunsScatter->setName("Runs Used");
    mEighthRunsScatter->setColor(Qt::green);
    mECPScatter->setName("Current Prediction");
    mECPScatter->setColor(Qt::black);
    mECPScatter->setMarkerShape(QScatterSeries::MarkerShapeRectangle);

    mEChartView->chart()->addSeries(mEighthMedian);
    mEChartView->chart()->addSeries(mEighthRunsScatter);
    mEChartView->chart()->addSeries(mECPScatter);

    mEChartView->chart()->addAxis(mEighthDAAxis, Qt::AlignBottom);
    mEChartView->chart()->addAxis(mEighthETAxis, Qt::AlignLeft);

    mEighthMedian->attachAxis(mEighthDAAxis);
    mEighthMedian->attachAxis(mEighthETAxis);
    mEighthRunsScatter->attachAxis(mEighthDAAxis);
    mEighthRunsScatter->attachAxis(mEighthETAxis);
    mECPScatter->attachAxis(mEighthDAAxis);
    mECPScatter->attachAxis(mEighthETAxis);

    mQuarterDAAxis->setLinePenColor(Qt::black);
    mQuarterDAAxis->setLabelFormat("%i");
    mQuarterETAxis->setLinePenColor(Qt::black);
    mQuarterETAxis->setLabelFormat("%5.2f");

    mQuarterMedian->setName("Median");
    mQuarterMedian->setColor(D_COLOR);
    mQuarterRunsScatter->setName("Runs Used");
    mQuarterRunsScatter->setColor(Qt::green);
    mQCPScatter->setName("Current Prediction");
    mQCPScatter->setColor(Qt::black);
    mQCPScatter->setMarkerShape(QScatterSeries::MarkerShapeRectangle);

    mQChartView->chart()->addSeries(mQuarterMedian);
    mQChartView->chart()->addSeries(mQuarterRunsScatter);
    mQChartView->chart()->addSeries(mQCPScatter);

    mQChartView->chart()->addAxis(mQuarterDAAxis, Qt::AlignBottom);
    mQChartView->chart()->addAxis(mQuarterETAxis, Qt::AlignLeft);

    mQuarterMedian->attachAxis(mQuarterDAAxis);
    mQuarterMedian->attachAxis(mQuarterETAxis);
    mQuarterRunsScatter->attachAxis(mQuarterDAAxis);
    mQuarterRunsScatter->attachAxis(mQuarterETAxis);
    mQCPScatter->attachAxis(mQuarterDAAxis);
    mQCPScatter->attachAxis(mQuarterETAxis);

    mEHoverInfo->hide();
    mQHoverInfo->hide();
}

void AutoTab::updateDisplay()
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

void AutoTab::updateGraph()
{
    mEighthMedian->clear();
    mEighthRunsScatter->clear();
    mECPScatter->clear();

    mQuarterMedian->clear();
    mQuarterRunsScatter->clear();
    mQCPScatter->clear();

    double eDAMin = mCurrentPrediction.value("densityAltitude").toDouble();
    double eDAMax = eDAMin;
    double qDAMin = eDAMin;
    double qDAMax = eDAMin;

    mECPScatter->append(eDAMax,
                        mCurrentPrediction.value("eighthD").toDouble());

    mQCPScatter->append(qDAMax,
                        mCurrentPrediction.value("quarterD").toDouble());

    for(QPointF p : mCurrentPrediction.eighthPoints()){
        double x = p.x();

        if(x < eDAMin){
            eDAMin = x;
        }

        if(x > eDAMax){
            eDAMax = x;
        }

        mEighthRunsScatter->append(x, p.y());
    }

    for(QPointF p : mCurrentPrediction.quarterPoints()){
        double x = p.x();

        if(x < qDAMin){
            qDAMin = x;
        }

        if(x > qDAMax){
            qDAMax = x;
        }

        mQuarterRunsScatter->append(x, p.y());
    }


    // had mod on butters...
    //
    // double edge = 0.25;
    // and edge was subtracted from ETMin's and added to ETMax's
    //


    double eMDAMin = eDAMin - 1000;
    double eMETMin = mCurrentPrediction.eighthLine().getYforX(eMDAMin);
    mEighthMedian->append(eMDAMin, eMETMin);

    double eMDAMax = eDAMax + 1000;
    double eMETMax = mCurrentPrediction.eighthLine().getYforX(eMDAMax);
    mEighthMedian->append(eMDAMax, eMETMax);

    double qMDAMin = qDAMin - 1000;
    double qMETMin = mCurrentPrediction.quarterLine().getYforX(qMDAMin);
    mQuarterMedian->append(qMDAMin, qMETMin);

    double qMDAMax = qDAMax + 1000;
    double qMETMax = mCurrentPrediction.quarterLine().getYforX(qMDAMax);
    mQuarterMedian->append(qMDAMax, qMETMax);

    if(eMETMin > eMETMax){
        double holder = eMETMin;
        eMETMin = eMETMax;
        eMETMax = holder;
    }

    if(qMETMin > qMETMax){
        double holder = qMETMin;
        qMETMin = qMETMax;
        qMETMax = holder;
    }

    mEighthDAAxis->setRange(eMDAMin, eMDAMax);
    mEighthETAxis->setRange(eMETMin, eMETMax);

    mQuarterDAAxis->setRange(qMDAMin, qMDAMax);
    mQuarterETAxis->setRange(qMETMin, qMETMax);
}

void AutoTab::updatePLabel(const QString &field, QLabel *label)
{
    if(mCurrentPrediction.value(field).toDouble() == 0.0){
        label->setText("");
    }else{
        label->setText(QString::number(mCurrentPrediction.value(field)
                                       .toDouble(),
                                       'f',
                                       3));
    }
}

void AutoTab::writePredictionToDb()
{
    if(mCurrentPrediction.value("temperature").toDouble() > 0){
        mPredictionsModel->addRow(mCurrentPrediction);

        if(ui->eToPhoneCheckBox->isChecked() || ui->qToPhoneCheckBox->isChecked()){
            sendPage();
        }

        while(mPredictionsModel->rowCount(QModelIndex()) > 11){
            mPredictionsModel->removeRow(mPredictionsModel->rowCount(QModelIndex()) - 1);
            mPredictionsModel->submitAll();
        }
    }
}

void AutoTab::pageLine(QString line, QString field, int decimals)
{
    if(decimals == -3){
        mPage.append(QString(line)
                     .arg(QString(mCurrentPrediction.value(field)
                             .toTime().toString("hh:mm"))));
    }else if(decimals == 0){
        mPage.append(QString(line)
                     .arg(QString::number(mCurrentPrediction.value(field)
                                                            .toInt())));
    }else{
        mPage.append(QString(line)
                     .arg(QString::number(mCurrentPrediction.value(field)
                                                            .toDouble(),
                                          'f',
                                          decimals)));
    }
}

void AutoTab::sendPage()
{
    if(Settings::get("emailUser").toString() == ""
       || Settings::get("emailHost").toString() == ""
       || Settings::get("emailPW").toString() == ""){
        qDebug("No email settings to page with - WRITE CODE");
    }else{
        mPage = "\n";

        QString suffix = QString("@%1")
                         .arg(TEXT_SUFFIXES
                              .value(ui->textProviderComboBox->currentText()));

        pageLine("%1\n", "dateTime", -3);
        pageLine("Temp -> %1\n", "temperature", 1);
        pageLine("Humid -> %1\n", "humidity", 1);
        pageLine("Press -> %1\n", "pressure", 2);
        pageLine("Vap P -> %1\n", "vaporPressure", 2);
        pageLine("Dew P -> %1\n", "dewPoint", 1);
        pageLine("D Alt -> %1\n", "densityAltitude", 0);
        pageLine("W Speed -> %1\n", "windSpeed", 0);
        pageLine("W Gust -> %1\n", "windGust", 0);
        pageLine("W Dir -> %1\n", "windDirection", 0);

        Smtp *smtpW = new Smtp(this);
        //connect(smtpW, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

        smtpW->sendMail(QString("%1%2")
                        .arg(ui->textNumberEdit->text())
                        .arg(suffix),
                        "Weather",
                        mPage);

        mPage = "\n";

        if(ui->eToPhoneCheckBox->isChecked()){
            pageLine("%1\n", "dateTime", -3);
            pageLine("By d alt -> %1\n", "eighthD", 3);
            pageLine("Average -> %1\n", "eighthA", 3);

            Smtp *smtpE = new Smtp(this);
            //connect(smtpE, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

            smtpE->sendMail(QString("%1%2")
                            .arg(ui->textNumberEdit->text())
                            .arg(suffix),
                            "1/8",
                            mPage);
        }

        mPage = "\n";

        if(ui->qToPhoneCheckBox->isChecked()){
            pageLine("%1\n", "dateTime", -3);
            pageLine("By d alt -> %1\n", "quarterD", 3);
            pageLine("Average -> %1\n", "quarterA", 3);

            Smtp *smtpQ = new Smtp(this);
            //connect(smtpQ, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

            smtpQ->sendMail(QString("%1%2")
                            .arg(ui->textNumberEdit->text())
                            .arg(suffix),
                            "1/4",
                            mPage);
        }
    }
}

void AutoTab::mailSent(QString status)
{
    if(status == "Message sent")
    {
        qDebug("page sent");
    }
}

void AutoTab::onAutoCheckboxChange(){
    if(ui->autoPredictCheckBox->isChecked()){
        startAutoTimer();
        onFactorChange();
    }else{
        stopAutoTimer();
    }
}

void AutoTab::onTrackTicketsCheckboxChange(){
    if(ui->trackTicketsCheckBox->isChecked()){
        startAutoTimer();
        ui->vehicleTicketsCheckBox->setCheckState(Qt::Unchecked);
    }

    onFactorChange();
}

void AutoTab::onVehicleTicketsCheckboxChange(){
    if(ui->vehicleTicketsCheckBox->isChecked()){
        startAutoTimer();
        ui->trackTicketsCheckBox->setCheckState(Qt::Unchecked);
    }

    onFactorChange();
}

void AutoTab::onFactorChange()
{
    mFactorTimer->start(CHANGE_DELAY);
}

void AutoTab::onShowPreviousPredictionsClicked()
{
    PreviousPredictionsDialog *ticketPredictionsDialog
            = new PreviousPredictionsDialog(mPredictionsModel,
                                            this);

    ticketPredictionsDialog->exec();

    delete ticketPredictionsDialog;
}

void AutoTab::onEPointHover(QPointF point, bool state)
{
    if(state){
        mEHoverInfo->setText(QString("DA: %1 \nET: %2 ").arg(point.x()).arg(point.y()));
        mEHoverInfo->setAnchor(point);
        mEHoverInfo->setZValue(1000);
        mEHoverInfo->updateGeometry();
        mEHoverInfo->show();
    }else{
        mEHoverInfo->hide();
    }
}

void AutoTab::onEPointClick(QPointF point)
{
    QSqlQuery query;
    QString queryText = QString("SELECT * FROM tickets "
                                "WHERE vehicleId = %1 "
                                "AND densityAltitude = %2")
            .arg(mVehicleId)
            .arg(point.x());

    if(!ui->vehicleTicketsCheckBox->isChecked()){
        queryText.append(QString(" AND trackId = %1").arg(mTrackId));

        if(!ui->trackTicketsCheckBox->isChecked()){
            queryText.append(QString(" AND raceId = %1").arg(mRaceId));
        }
    }

    query.exec(queryText);
//    DatabaseManager::debugQuery(query);

    QString ticketInfo;
    QSqlRecord ticket;

    if(query.next()){
         ticket = query.record();

        QString t = ticket.value("temperatureM")
                .toDouble()!=0.0?ticket.value("temperatureM").toString()
                               :ticket.value("temperature").toString();
        QString h = ticket.value("humidityM")
                .toDouble()!=0.0?ticket.value("humidityM").toString()
                               :ticket.value("humidity").toString();
        QString p = ticket.value("pressureM")
                .toDouble()!=0.0?ticket.value("pressureM").toString()
                               :ticket.value("pressure").toString();
        QString ws = ticket.value("windSpeedM")
                .toDouble()!=0.0?ticket.value("windSpeedM").toString()
                               :ticket.value("windSpeed").toString();
        QString wd = ticket.value("windDirectionM")
                .toDouble()!=0.0?ticket.value("windDirectionM").toString()
                               :ticket.value("windDirection").toString();

        ticketInfo.append(QString("DA\t: %1\n"
                                  "Temp\t: %2\n"
                                  "Humid\t: %3\n"
                                  "Pressure\t: %4\n"
                                  "Vapor P\t: %5\n"
                                  "W Speed\t: %6\n"
                                  "W Dir\t: %7\n"
                                  "G Speed\t: %8\n"
                                  "G Dir\t: %9\n"
                                  "1/8\t: %10\n "
                                  "1/4\t: %11\n"
                                  "%12")
                          .arg(ticket.value("densityAltitude").toString(),
                               t,
                               h,
                               p,
                               ticket.value("vaporPressure").toString(),
                               ws,
                               wd,
                               ticket.value("windGust").toString(),
                               ticket.value("windGustDirection").toString(),
                               ticket.value("eighth").toString(),
                               ticket.value("quarter").toString(),
                               ticket.value("notes").toString()));
    }

    QMessageBox clocksInvalid;
    clocksInvalid.setWindowTitle("Remove Ticket");
    clocksInvalid.setText(ticketInfo);
    clocksInvalid.setStandardButtons(QMessageBox::Yes);
    clocksInvalid.addButton(QMessageBox::No);
    clocksInvalid.setDefaultButton(QMessageBox::No);

    if(clocksInvalid.exec() == QMessageBox::Yes){
        query.clear();
        queryText = QString("UPDATE tickets SET "
                            "sixty=-ABS(sixty),"
                            "threeThirty=-ABS(threeThirty),"
                            "eighth=-ABS(eighth),"
                            "thousand=-ABS(thousand),"
                            "quarter=-ABS(quarter) "
                            "WHERE id = %1")
                .arg(ticket.value("id").toInt());
        query.exec(queryText);
        DatabaseManager::debugQuery(query);
        query.clear();
        emit selectionUpdated();
    }
}

void AutoTab::onQPointHover(QPointF point, bool state)
{
    if(state){
        mQHoverInfo->setText(QString("DA: %1 \nET: %2 ").arg(point.x()).arg(point.y()));
        mQHoverInfo->setAnchor(point);
        mQHoverInfo->setZValue(1000);
        mQHoverInfo->updateGeometry();
        mQHoverInfo->show();
    }else{
        mQHoverInfo->hide();
    }
}

void AutoTab::onQPointClick(QPointF point)
{
    QSqlQuery query;
    QString queryText = QString("SELECT * FROM tickets "
                                "WHERE vehicleId = %1 "
                                "AND densityAltitude = %2")
            .arg(mVehicleId)
            .arg(point.x());

    if(!ui->vehicleTicketsCheckBox->isChecked()){
        queryText.append(QString(" AND trackId = %1").arg(mTrackId));

        if(!ui->trackTicketsCheckBox->isChecked()){
            queryText.append(QString(" AND raceId = %1").arg(mRaceId));
        }
    }

    query.exec(queryText);
//    DatabaseManager::debugQuery(query);

    QString ticketInfo;
    QSqlRecord ticket;

    if(query.next()){
         ticket = query.record();

        QString t = ticket.value("temperatureM")
                .toDouble()!=0.0?ticket.value("temperatureM").toString()
                               :ticket.value("temperature").toString();
        QString h = ticket.value("humidityM")
                .toDouble()!=0.0?ticket.value("humidityM").toString()
                               :ticket.value("humidity").toString();
        QString p = ticket.value("pressureM")
                .toDouble()!=0.0?ticket.value("pressureM").toString()
                               :ticket.value("pressure").toString();
        QString ws = ticket.value("windSpeedM")
                .toDouble()!=0.0?ticket.value("windSpeedM").toString()
                               :ticket.value("windSpeed").toString();
        QString wd = ticket.value("windDirectionM")
                .toDouble()!=0.0?ticket.value("windDirectionM").toString()
                               :ticket.value("windDirection").toString();

        ticketInfo.append(QString("DA\t: %1\n"
                                  "Temp\t: %2\n"
                                  "Humid\t: %3\n"
                                  "Pressure\t: %4\n"
                                  "Vapor P\t: %5\n"
                                  "W Speed\t: %6\n"
                                  "W Dir\t: %7\n"
                                  "G Speed\t: %8\n"
                                  "G Dir\t: %9\n"
                                  "1/8\t: %10\n "
                                  "1/4\t: %11\n"
                                  "%12")
                          .arg(ticket.value("densityAltitude").toString(),
                               t,
                               h,
                               p,
                               ticket.value("vaporPressure").toString(),
                               ws,
                               wd,
                               ticket.value("windGust").toString(),
                               ticket.value("windGustDirection").toString(),
                               ticket.value("eighth").toString(),
                               ticket.value("quarter").toString(),
                               ticket.value("notes").toString()));
    }

    QMessageBox clocksInvalid;
    clocksInvalid.setWindowTitle("Remove Selected Ticket");
    clocksInvalid.setText(ticketInfo);
    clocksInvalid.setStandardButtons(QMessageBox::Yes);
    clocksInvalid.addButton(QMessageBox::No);
    clocksInvalid.setDefaultButton(QMessageBox::No);

    if(clocksInvalid.exec() == QMessageBox::Yes){
        query.clear();
        queryText = QString("UPDATE tickets SET "
                            "sixty=-ABS(sixty),"
                            "threeThirty=-ABS(threeThirty),"
                            "eighth=-ABS(eighth),"
                            "thousand=-ABS(thousand),"
                            "quarter=-ABS(quarter) "
                            "WHERE id = %1")
                .arg(ticket.value("id").toInt());
        query.exec(queryText);
//        DatabaseManager::debugQuery(query);
        query.clear();
        emit selectionUpdated();
    }
}
