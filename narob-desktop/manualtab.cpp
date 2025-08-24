#include "manualtab.h"
#include "ui_manualtab.h"

ManualTab::ManualTab(TicketsLogbookModel *tLModel,
                     std::shared_ptr<Vehicle> vehicle,
                     std::shared_ptr<Race> race,
                     QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManualTab),
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
            &ManualTab::onFactorChange);

    connect(ui->riderWeightSpinBox,
            QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this,
            &ManualTab::onFactorChange);

    connect(ui->windAdjustmentSpinBox,
            QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this,
            &ManualTab::onFactorChange);

    connect(ui->weightAdjustmentSpinBox,
            QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this,
            &ManualTab::onFactorChange);

    connect(ui->trackTicketsCheckBox,
            &QCheckBox::checkStateChanged,
            this,
            &ManualTab::onTrackTicketsCheckboxChange);

    connect(ui->vehicleTicketsCheckBox,
            &QCheckBox::checkStateChanged,
            this,
            &ManualTab::onVehicleTicketsCheckboxChange);

    connect(mFactorTimer, &QTimer::timeout,
            this, &ManualTab::makePrediction);

    connect(ui->lengthToggleButton, &QPushButton::clicked,
            this, &ManualTab::onLengthToggle);

    connect(ui->temperatureEdit,
            &QLineEdit::textChanged,
            this,
            &ManualTab::onFactorChange);

    connect(ui->humidityEdit,
            &QLineEdit::textChanged,
            this,
            &ManualTab::onFactorChange);

    connect(ui->pressureEdit,
            &QLineEdit::textChanged,
            this,
            &ManualTab::onFactorChange);

    connect(ui->windSpeedEdit,
            &QLineEdit::textChanged,
            this,
            &ManualTab::onFactorChange);

    connect(ui->windDirectionEdit,
            &QLineEdit::textChanged,
            this,
            &ManualTab::onFactorChange);
}

ManualTab::~ManualTab()
{
    delete mFactorTimer;
    delete ui;
}

void ManualTab::updateAllModels()
{
    makePrediction();
    qDebug("manual tab update all models");
}

void ManualTab::makePrediction()
{
    mObservation.setValue("dateTime", QDateTime(QDate(0, 0, 0), QTime(0, 0)));
    mObservation.setValue("temperature", ui->temperatureEdit->text());
    mObservation.setValue("humidity", ui->humidityEdit->text());
    mObservation.setValue("pressure", ui->pressureEdit->text());
    mObservation.calcDA();
    mObservation.setValue("windSpeed", ui->windSpeedEdit->text());
    mObservation.setValue("windDirection", ui->windDirectionEdit->text());
    mObservation.setValue("windGust", 0);
    mObservation.setValue("windGustDirection", 0);
    mObservation.setValue("samples", 1);

    mCurrentPrediction.predictByObservation(mObservation,
                                            ui->riderWeightSpinBox->value(),
                                            ui->vehicleWeightSpinBox->value(),
                                            ui->windAdjustmentSpinBox->value(),
                                            ui->weightAdjustmentSpinBox->value(),
                                            ui->vehicleTicketsCheckBox->isChecked(),
                                            ui->trackTicketsCheckBox->isChecked());

    ui->vaporPressure->setText(mObservation.value("vaporPressure").toString());
    ui->densityAltitude->setText(mObservation.value("densityAltitude").toString());

    updateDisplay();

    updateGraph();

    mFactorTimer->stop();
}

void ManualTab::setupGraph()
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

void ManualTab::updateDisplay()
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

void ManualTab::updateGraph()
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

void ManualTab::updatePLabel(const QString &field, QLabel *label)
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

void ManualTab::onTrackTicketsCheckboxChange(){
    if(ui->trackTicketsCheckBox->isChecked()){
            ui->vehicleTicketsCheckBox->setCheckState(Qt::Unchecked);
    }

    onFactorChange();
}

void ManualTab::onVehicleTicketsCheckboxChange(){
    if(ui->vehicleTicketsCheckBox->isChecked()){
        ui->trackTicketsCheckBox->setCheckState(Qt::Unchecked);
    }

    onFactorChange();
}

void ManualTab::onFactorChange()
{
    mFactorTimer->start(CHANGE_DELAY);
}

void ManualTab::onLengthToggle()
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
