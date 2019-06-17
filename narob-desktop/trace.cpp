#include "trace.h"

#include <QLineSeries>
#include <QScatterSeries>
#include <QDebug>

Trace::Trace(QString type,
             QChartView *chartView,
             QAbstractAxis *xAxis,
             QString name,
             double edgeSpace,
             Qt::Alignment alignment,
             QColor color,
             QObject *parent) :
    QObject(parent),
    mAxis(new QValueAxis(chartView)),
    mEdgeSpace(edgeSpace),
    mMin(-1000000),
    mMax(1000000)
{
    if(type == "L"){
        mSeries = new QLineSeries();
    }else if(type == "S"){
        mSeries = new QScatterSeries();
    }

    mSeries->setName(name);
    mSeries->setColor(color);
    mAxis->setLinePenColor(color);

    if(mEdgeSpace < 1){
        mAxis->setLabelFormat("%5.2f");
    }else{
        mAxis->setLabelFormat("%i");
    }

    chartView->chart()->addSeries(mSeries);

    chartView->chart()->addAxis(mAxis, alignment);

    mSeries->attachAxis(mAxis);
    mSeries->attachAxis(xAxis);
}

Trace::~Trace()
{
}

void Trace::newPoint(double x, double y)
{
    newPoint(QPointF(x, y));
}

void Trace::newPoint(QPointF p)
{
    double y = p.y();

    if(mMin < -999999 || y < (mMin + mEdgeSpace))
    {
        mMin = y - mEdgeSpace;
        mAxis->setMin(mMin);
    }

    if(mMax > 999999 || y > (mMax - mEdgeSpace))
    {
        mMax = y + mEdgeSpace;
        mAxis->setMax(mMax);
    }

    mSeries->append(p);
}
