#include "autotab.h"
#include "ui_autotab.h"
#include "settings.h"
#include "smtp.h"
#include "previouspredictionsdialog.h"

AutoTab::AutoTab(TicketsLogbookModel *tLModel,
                 std::shared_ptr<Vehicle> vehicle,
                 std::shared_ptr<Race> race,
                 QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AutoTab),
    mCurrentPrediction(Prediction(tLModel,
                                  vehicle->value("id").toInt(),
                                  race->value("trackId").toInt(),
                                  race->value("id").toInt(),
                                  0)),
    mPredictionsModel(new PredictionsModel(vehicle->value("id").toInt(),
                                           race->value("id").toInt(),
                                           0,
                                           this)),
    mTicketsLogbookModel(tLModel),
    mAutoTimer(new QTimer(this)),
    mFactorTimer(new QTimer(this)),
    mChartView(new QChartView(new QChart(), this)),
    mEighthMedian(new QLineSeries),
    mQuarterMedian(new QLineSeries),
    mEighthRunsScatter(new QScatterSeries),
    mQuarterRunsScatter(new QScatterSeries),
    mECPScatter(new QScatterSeries),
    mQCPScatter(new QScatterSeries),
    mEighthDAAxis(new QValueAxis(mChartView)),
    mEighthETAxis(new QValueAxis(mChartView)),
    mQuarterDAAxis(new QValueAxis(mChartView)),
    mQuarterETAxis(new QValueAxis(mChartView)),
    mQuarterGraph(true)
{
    ui->setupUi(this);

    ui->gridLayout_6->addWidget(mChartView, 2, 0, 1, -1);

    mChartView->setRenderHint(QPainter::Antialiasing);

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

    connect(ui->lengthToggleButton, &QPushButton::clicked,
            this, &AutoTab::onLengthToggle);

    connect(mAutoTimer, &QTimer::timeout,
            this, &AutoTab::autoPredict);

    connect(ui->previousPredictionsButton, &QPushButton::clicked,
            this, &AutoTab::onShowPreviousPredictionsClicked);






    // connect auto timer start to checking the on/off box
    // either don't allow AFV or AFT if off or turn it on when they
    // are selected








    mAutoTimer->start(60000);
}

AutoTab::~AutoTab()
{
    delete mAutoTimer;
    delete mFactorTimer;
    delete ui;
}

void AutoTab::updateAllModels()
{
    makePrediction();
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
    mEighthMedian->setColor(Qt::blue);
    mEighthRunsScatter->setName("Runs Used");
    mEighthRunsScatter->setColor(Qt::green);

    mChartView->chart()->addSeries(mEighthMedian);
    mChartView->chart()->addSeries(mEighthRunsScatter);
    mChartView->chart()->addAxis(mEighthDAAxis, Qt::AlignBottom);
    mChartView->chart()->addAxis(mEighthETAxis, Qt::AlignLeft);
    mEighthMedian->attachAxis(mEighthDAAxis);
    mEighthMedian->attachAxis(mEighthETAxis);
    mEighthRunsScatter->attachAxis(mEighthDAAxis);
    mEighthRunsScatter->attachAxis(mEighthETAxis);

    mQuarterDAAxis->setLinePenColor(Qt::black);
    mQuarterDAAxis->setLabelFormat("%i");
    mQuarterETAxis->setLinePenColor(Qt::black);
    mQuarterETAxis->setLabelFormat("%5.2f");
    mQuarterMedian->setName("Median");
    mQuarterMedian->setColor(Qt::blue);
    mQuarterRunsScatter->setName("Runs Used");
    mQuarterRunsScatter->setColor(Qt::green);

    mChartView->chart()->addSeries(mQuarterMedian);
    mChartView->chart()->addSeries(mQuarterRunsScatter);
    mChartView->chart()->addAxis(mQuarterDAAxis, Qt::AlignBottom);
    mChartView->chart()->addAxis(mQuarterETAxis, Qt::AlignLeft);
    mQuarterMedian->attachAxis(mQuarterDAAxis);
    mQuarterMedian->attachAxis(mQuarterETAxis);
    mQuarterRunsScatter->attachAxis(mQuarterDAAxis);
    mQuarterRunsScatter->attachAxis(mQuarterETAxis);

    mECPScatter->setName("Current Prediction");
    mECPScatter->setColor(Qt::black);
    mECPScatter->setMarkerShape(QScatterSeries::MarkerShapeRectangle);

    mQCPScatter->setName("Current Prediction");
    mQCPScatter->setColor(Qt::black);
    mQCPScatter->setMarkerShape(QScatterSeries::MarkerShapeRectangle);

    mChartView->chart()->addSeries(mECPScatter);
    mECPScatter->attachAxis(mEighthDAAxis);
    mECPScatter->attachAxis(mEighthETAxis);

    mChartView->chart()->addSeries(mQCPScatter);
    mQCPScatter->attachAxis(mQuarterDAAxis);
    mQCPScatter->attachAxis(mQuarterETAxis);

    mEighthRunsScatter->hide();
    mEighthMedian->hide();
    mECPScatter->hide();
    mEighthDAAxis->hide();
    mEighthETAxis->hide();
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


    double eMDAMin = eDAMin - 100;
    double eMETMin = mCurrentPrediction.eighthLine().getYforX(eMDAMin);
    mEighthMedian->append(eMDAMin, eMETMin);

    double eMDAMax = eDAMax + 100;
    double eMETMax = mCurrentPrediction.eighthLine().getYforX(eMDAMax);
    mEighthMedian->append(eMDAMax, eMETMax);

    double qMDAMin = qDAMin - 100;
    double qMETMin = mCurrentPrediction.quarterLine().getYforX(qMDAMin);
    mQuarterMedian->append(qMDAMin, qMETMin);

    double qMDAMax = qDAMax + 100;
    double qMETMax = mCurrentPrediction.quarterLine().getYforX(qMDAMax);
    mQuarterMedian->append(qMDAMax, qMETMax);

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

void AutoTab::onTrackTicketsCheckboxChange(){
    if(ui->trackTicketsCheckBox->isChecked()){
            ui->vehicleTicketsCheckBox->setCheckState(Qt::Unchecked);
    }

    onFactorChange();
}

void AutoTab::onVehicleTicketsCheckboxChange(){
    if(ui->vehicleTicketsCheckBox->isChecked()){
        ui->trackTicketsCheckBox->setCheckState(Qt::Unchecked);
    }

    onFactorChange();
}

void AutoTab::onFactorChange()
{
    mFactorTimer->start(CHANGE_DELAY);
}

void AutoTab::onLengthToggle()
{
    mQuarterGraph = !mQuarterGraph;

    if(mQuarterGraph){
        mEighthMedian->hide();
        mEighthRunsScatter->hide();
        mEighthDAAxis->hide();
        mEighthETAxis->hide();
        mECPScatter->hide();

        mQuarterMedian->show();
        mQuarterRunsScatter->show();
        mQuarterDAAxis->show();
        mQuarterETAxis->show();
        mQCPScatter->show();

        ui->lengthLabel->setText("1/4 Mile Predictions");
        ui->lengthToggleButton->setText("Show 1/8");
    }else{
        mQuarterMedian->hide();
        mQuarterRunsScatter->hide();
        mQuarterDAAxis->hide();
        mQuarterETAxis->hide();
        mQCPScatter->hide();

        mEighthMedian->show();
        mEighthRunsScatter->show();
        mEighthDAAxis->show();
        mEighthETAxis->show();
        mECPScatter->show();

        ui->lengthLabel->setText("1/8 Mile Predictions");
        ui->lengthToggleButton->setText("Show 1/4");
    }
}

void AutoTab::onShowPreviousPredictionsClicked()
{
    PreviousPredictionsDialog *ticketPredictionsDialog
            = new PreviousPredictionsDialog(mPredictionsModel,
                                            this);

    ticketPredictionsDialog->exec();

    delete ticketPredictionsDialog;
}
