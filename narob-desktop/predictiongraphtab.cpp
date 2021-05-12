#include "predictiongraphtab.h"
#include "ui_predictiongraphtab.h"

PredictionGraphTab::PredictionGraphTab(Prediction *prediction,
                                       QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PredictionGraphTab),
    mCurrentPrediction(prediction),
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

    ui->gridLayout_6->addWidget(mChartView, 1, 0, 1, -1);

    mChartView->setRenderHint(QPainter::Antialiasing);

    setupGraph();

    connect(ui->lengthToggleButton, &QPushButton::clicked,
            this, &PredictionGraphTab::onLengthToggle);

}

PredictionGraphTab::~PredictionGraphTab()
{
    delete ui;
}

void PredictionGraphTab::setupGraph()
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

void PredictionGraphTab::updateGraph()
{
    mEighthMedian->clear();
    mEighthRunsScatter->clear();
    mECPScatter->clear();

    mQuarterMedian->clear();
    mQuarterRunsScatter->clear();
    mQCPScatter->clear();

    double eDAMin = mCurrentPrediction->value("densityAltitude").toDouble();
    double eDAMax = eDAMin;
    double qDAMin = eDAMin;
    double qDAMax = eDAMin;

    mECPScatter->append(eDAMax,
                        mCurrentPrediction->value("eighthD").toDouble());

    mQCPScatter->append(qDAMax,
                        mCurrentPrediction->value("quarterD").toDouble());

    for(QPointF p : mCurrentPrediction->eighthPoints()){
        double x = p.x();

        if(x < eDAMin){
            eDAMin = x;
        }

        if(x > eDAMax){
            eDAMax = x;
        }

        mEighthRunsScatter->append(x, p.y());
    }

    for(QPointF p : mCurrentPrediction->quarterPoints()){
        double x = p.x();

        if(x < qDAMin){
            qDAMin = x;
        }

        if(x > qDAMax){
            qDAMax = x;
        }

        mQuarterRunsScatter->append(x, p.y());
    }

//    for(QPointF p : mCurrentPrediction->eighthPoints()){
//        double x = p.x();

//        if(eDAMin < -999999 || x < eDAMin){
//            eDAMin = x;
//        }

//        if(eDAMax > 999999 || x > eDAMax){
//            eDAMax = x;
//        }

//        mEighthRunsScatter->append(x, p.y());
//    }

//    for(QPointF p : mCurrentPrediction->quarterPoints()){
//        double x = p.x();

//        if(qDAMin < -999999 || x < qDAMin){
//            qDAMin = x;
//        }

//        if(qDAMax > 999999 || x > qDAMax){
//            qDAMax = x;
//        }

//        mQuarterRunsScatter->append(x, p.y());
//    }

    double eMDAMin = eDAMin - 100;
    double eMETMin = mCurrentPrediction->eighthLine().getYforX(eMDAMin);
    mEighthMedian->append(eMDAMin, eMETMin);

    double eMDAMax = eDAMax + 100;
    double eMETMax = mCurrentPrediction->eighthLine().getYforX(eMDAMax);
    mEighthMedian->append(eMDAMax, eMETMax);

    double qMDAMin = qDAMin - 100;
    double qMETMin = mCurrentPrediction->quarterLine().getYforX(qMDAMin);
    mQuarterMedian->append(qMDAMin, qMETMin);

    double qMDAMax = qDAMax + 100;
    double qMETMax = mCurrentPrediction->quarterLine().getYforX(qMDAMax);
    mQuarterMedian->append(qMDAMax, qMETMax);

    mEighthDAAxis->setRange(eMDAMin, eMDAMax);
    mEighthETAxis->setRange(eMETMin, eMETMax);

    mQuarterDAAxis->setRange(qMDAMin, qMDAMax);
    mQuarterETAxis->setRange(qMETMin, qMETMax);
}

void PredictionGraphTab::onLengthToggle()
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
