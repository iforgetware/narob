#include "predictiontab.h"
#include "ui_predictiontab.h"
#include "predictions.h"
#include "settings.h"
#include "smtp.h"

#include <QDebug>
#include <QVector>

PredictionTab::PredictionTab(TicketsModel *model,
                             std::shared_ptr<Vehicle> vehicle,
                             std::shared_ptr<Race> race,
                             QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PredictionTab),
    mTicketsModel(model),
    mPredictionsModel(new PredictionsModel(vehicle->value("id").toInt(),
                                           race->value("id").toInt(),
                                           0,
                                           this)),
    mPreviousPredictionsWidget(new PreviousPredictionsWidget(
                                   mPredictionsModel,
                                   this)),
    mCurrentPrediction(Prediction(model,
                                  vehicle->value("id").toInt(),
                                  race->value("trackId").toInt(),
                                  race->value("id").toInt(),
                                  0)),
    mAutoTimer(new QTimer(this)),
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

    ui->gridLayout_2->addWidget(mPreviousPredictionsWidget, 0, 0);

    ui->gridLayout_6->addWidget(mChartView, 1, 0, 1, -1);

    mChartView->setRenderHint(QPainter::Antialiasing);

    setupGraph();

    ui->vehicleWeightSpinBox->setValue(vehicle->value("weight").toInt());
    ui->riderWeightSpinBox->setValue(mTicketsModel->lastWeight());

    ui->weightAdjustmentSpinBox->setValue(vehicle->value("weightAdjustment")
                                          .toDouble());
    ui->windAdjustmentSpinBox->setValue(vehicle->value("windAdjustment")
                                        .toDouble());
    ui->textProviderComboBox->setCurrentText(vehicle->value("textProvider")
                                             .toString());
    ui->textNumberEdit->setText(vehicle->value("textNumber")
                                .toString());

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

    connect(ui->trackTicketsCheckBox,
            &QCheckBox::stateChanged,
            this,
            &PredictionTab::onTrackTicketsCheckboxChange);

    connect(ui->vehicleTicketsCheckBox,
            &QCheckBox::stateChanged,
            this,
            &PredictionTab::onVehicleTicketsCheckboxChange);

    connect(mAutoTimer, &QTimer::timeout,
            this, &PredictionTab::makePrediction);

    connect(mFactorTimer, &QTimer::timeout,
            this, &PredictionTab::makePrediction);

    connect(ui->lengthToggleButton, &QPushButton::clicked,
            this, &PredictionTab::onLengthToggle);

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

    mAutoTimer->start(60000);
}

PredictionTab::~PredictionTab()
{
    delete mAutoTimer;
    delete mFactorTimer;
    delete ui;
}

void PredictionTab::setupGraph()
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

void PredictionTab::UpdateAllModels()
{
    mPreviousPredictionsWidget->updateModel();
}

void PredictionTab::makePrediction()
{
    mCurrentPrediction.predictClocks(QDateTime(),
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

    int minute = mCurrentPrediction.value("dateTime")
                 .toDateTime()
                 .time()
                 .minute();

    if(minute % 5 == 0){// DEV ONLY - set back to 5
        writePredictionToDb();
    }

    updateDisplay();

    mFactorTimer->stop();
}

void PredictionTab::writePredictionToDb()
{
    if(mCurrentPrediction.value("temperature").toDouble() > 0){
        mPredictionsModel->addRow(mCurrentPrediction);

        if(ui->eToPhoneCheckBox->isChecked() || ui->qToPhoneCheckBox->isChecked()){
            sendPage();
        }

        while(mPredictionsModel->rowCount(QModelIndex()) > 5){
            mPredictionsModel->removeRow(mPredictionsModel->rowCount(QModelIndex()) - 1);
            mPredictionsModel->submitAll();
            mPreviousPredictionsWidget->updateModel();
        }
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

void PredictionTab::pageLine(QString line, QString field, int decimals)
{
    if(decimals == -3){
        mPage.append(QString(line)
                     .arg(QString(mCurrentPrediction.value(field)
                             .toTime().toString("hh:mm"))));
    }else if(decimals == 0){
        mPage.append(QString(line)
                     .arg(QString::number(mCurrentPrediction
                                     .value(field)
                                     .toInt())));
    }else{
        mPage.append(QString(line)
                     .arg(QString::number(mCurrentPrediction
                                         .value(field)
                                         .toDouble()
                                          ,'f',
                                          decimals)));
    }
}

void PredictionTab::sendPage()
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

void PredictionTab::mailSent(QString status)
{
    if(status == "Message sent")
    {
        qDebug("page sent");
    }
}

void PredictionTab::updatePLabel(const QString &field, QLabel *label)
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

void PredictionTab::onTrackTicketsCheckboxChange(){
    if(ui->trackTicketsCheckBox->isChecked()){
            ui->vehicleTicketsCheckBox->setCheckState(Qt::Unchecked);
    }

    onFactorChange();
}

void PredictionTab::onVehicleTicketsCheckboxChange(){
    if(ui->vehicleTicketsCheckBox->isChecked()){
        ui->trackTicketsCheckBox->setCheckState(Qt::Unchecked);
    }

    onFactorChange();
}

void PredictionTab::onFactorChange()
{
    mFactorTimer->start(CHANGE_DELAY);
}

void PredictionTab::onLengthToggle()
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
