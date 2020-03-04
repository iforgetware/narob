#include "calculatortab.h"
#include "ui_calculatortab.h"
#include "settings.h"

CalculatorTab::CalculatorTab(TicketsModel *model,
                             std::shared_ptr<Vehicle> vehicle,
                             std::shared_ptr<Race> race,
                             QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CalculatorTab),
    mTicketsModel(model),
    mPredictionsModel(new PredictionsModel(vehicle->value("id").toInt(),
                                           race->value("id").toInt(),
                                           0,
                                           this)),
    mCurrentPrediction(Prediction(model,
                                  vehicle->value("id").toInt(),
                                  race->value("trackId").toInt(),
                                  race->value("id").toInt(),
                                  0)),
    mFactorTimer(new QTimer(this)),
    mChartView(new QChartView(new QChart(), this)),
    mEighthMedian(new QLineSeries),
    mQuarterMedian(new QLineSeries),
    mEighthRunsScatter(new QScatterSeries),
    mQuarterRunsScatter(new QScatterSeries),
    mEighthDAAxis(new QValueAxis(mChartView)),
    mEighthETAxis(new QValueAxis(mChartView)),
    mQuarterDAAxis(new QValueAxis(mChartView)),
    mQuarterETAxis(new QValueAxis(mChartView)),
    mQuarterGraph(true)
{
    ui->setupUi(this);

    ui->gridLayout_6->addWidget(mChartView, 1, 0, 1, -1);

    mChartView->setRenderHint(QPainter::Antialiasing);

    setupGraph();

    ui->vehicleWeightSpinBox->setValue(vehicle->value("weight").toInt());
    ui->riderWeightSpinBox->setValue(mTicketsModel->lastWeight());

    ui->weightAdjustmentSpinBox->setValue(vehicle->value("weightAdjustment")
                                          .toDouble());
    ui->windAdjustmentSpinBox->setValue(vehicle->value("windAdjustment")
                                        .toDouble());

    connect(ui->vehicleWeightSpinBox,
            QOverload<int>::of(&QSpinBox::valueChanged),
            this,
            &CalculatorTab::onFactorChange);

    connect(ui->riderWeightSpinBox,
            QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this,
            &CalculatorTab::onFactorChange);

    connect(ui->windAdjustmentSpinBox,
            QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this,
            &CalculatorTab::onFactorChange);

    connect(ui->weightAdjustmentSpinBox,
            QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this,
            &CalculatorTab::onFactorChange);

    connect(ui->trackTicketsCheckBox,
            &QCheckBox::stateChanged,
            this,
            &CalculatorTab::onTrackTicketsCheckboxChange);

    connect(ui->vehicleTicketsCheckBox,
            &QCheckBox::stateChanged,
            this,
            &CalculatorTab::onVehicleTicketsCheckboxChange);

    connect(ui->humidityEdit,
            &QLineEdit::textChanged,
            this,
            &CalculatorTab::onFactorChange);

    connect(ui->pressureEdit,
            &QLineEdit::textChanged,
            this,
            &CalculatorTab::onFactorChange);

    connect(mFactorTimer, &QTimer::timeout,
            this, &CalculatorTab::makePrediction);

    connect(ui->lengthToggleButton, &QPushButton::clicked,
            this, &CalculatorTab::onLengthToggle);

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
}

CalculatorTab::~CalculatorTab()
{
    delete mFactorTimer;
    delete ui;
}

void CalculatorTab::setupGraph()
{
    mEighthDAAxis->setLinePenColor(Qt::black);
    mEighthDAAxis->setLabelFormat("%i");
    mEighthETAxis->setLinePenColor(Qt::black);
    mEighthETAxis->setLabelFormat("%5.2f");
    mEighthMedian->setName("Median");
    mEighthMedian->setColor(Qt::blue);
    mEighthRunsScatter->setName("Runs Used");
    mEighthRunsScatter->setColor(Qt::red);

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
    mQuarterRunsScatter->setColor(Qt::red);

    mChartView->chart()->addSeries(mQuarterMedian);
    mChartView->chart()->addSeries(mQuarterRunsScatter);
    mChartView->chart()->addAxis(mQuarterDAAxis, Qt::AlignBottom);
    mChartView->chart()->addAxis(mQuarterETAxis, Qt::AlignLeft);
    mQuarterMedian->attachAxis(mQuarterDAAxis);
    mQuarterMedian->attachAxis(mQuarterETAxis);
    mQuarterRunsScatter->attachAxis(mQuarterDAAxis);
    mQuarterRunsScatter->attachAxis(mQuarterETAxis);

    mEighthRunsScatter->hide();
    mEighthMedian->hide();
    mEighthDAAxis->hide();
    mEighthETAxis->hide();
}


void CalculatorTab::makePrediction()
{
    mObservation.setValue("dateTime", QDateTime(QDate(0, 0, 0), QTime(0, 0)));
    mObservation.setValue("temperature", ui->temperatureEdit->text());
    mObservation.setValue("humidity", ui->humidityEdit->text());
    mObservation.setValue("pressure", ui->pressureEdit->text());
//    mObservation.setValue("vaporPressure", formatNum(mVPs / mSampleCount, 2));
//    mObservation.setValue("dewPoint", formatNum(mDPts / mSampleCount, 1));
//    mObservation.setValue("densityAltitude", dA);
//    mObservation.calcDA();
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

    mEighthMedian->clear();
    mEighthRunsScatter->clear();
    mQuarterMedian->clear();
    mQuarterRunsScatter->clear();

    double eDAMin = -1000000;
    double eDAMax = 1000000;

    double qDAMin = -1000000;
    double qDAMax = 1000000;

    for(QPointF p : mCurrentPrediction.eighthPoints()){
        double x = p.x();

        if(eDAMin < -999999 || x < eDAMin){
            eDAMin = x;
        }

        if(eDAMax > 999999 || x > eDAMax){
            eDAMax = x;
        }

        mEighthRunsScatter->append(x, p.y());
    }

    for(QPointF p : mCurrentPrediction.quarterPoints()){
        double x = p.x();

        if(qDAMin < -999999 || x < qDAMin){
            qDAMin = x;
        }

        if(qDAMax > 999999 || x > qDAMax){
            qDAMax = x;
        }

        mQuarterRunsScatter->append(x, p.y());
    }

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

    updateDisplay();

    mFactorTimer->stop();
}

void CalculatorTab::updateDisplay()
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

void CalculatorTab::updatePLabel(const QString &field, QLabel *label)
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

void CalculatorTab::onTrackTicketsCheckboxChange(){
    if(ui->trackTicketsCheckBox->isChecked()){
            ui->vehicleTicketsCheckBox->setCheckState(Qt::Unchecked);
    }

    onFactorChange();
}

void CalculatorTab::onVehicleTicketsCheckboxChange(){
    if(ui->vehicleTicketsCheckBox->isChecked()){
        ui->trackTicketsCheckBox->setCheckState(Qt::Unchecked);
    }

    onFactorChange();
}

void CalculatorTab::onFactorChange()
{
    mFactorTimer->start(CHANGE_DELAY);
}

void CalculatorTab::onLengthToggle()
{
    mQuarterGraph = !mQuarterGraph;

    if(mQuarterGraph){
        mEighthMedian->hide();
        mEighthRunsScatter->hide();
        mEighthDAAxis->hide();
        mEighthETAxis->hide();

        mQuarterMedian->show();
        mQuarterRunsScatter->show();
        mQuarterDAAxis->show();
        mQuarterETAxis->show();

        ui->lengthLabel->setText("1/4 Mile Predictions");
        ui->lengthToggleButton->setText("Show 1/8");
    }else{
        mQuarterMedian->hide();
        mQuarterRunsScatter->hide();
        mQuarterDAAxis->hide();
        mQuarterETAxis->hide();

        mEighthMedian->show();
        mEighthRunsScatter->show();
        mEighthDAAxis->show();
        mEighthETAxis->show();

        ui->lengthLabel->setText("1/8 Mile Predictions");
        ui->lengthToggleButton->setText("Show 1/4");
    }
}
