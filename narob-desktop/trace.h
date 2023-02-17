#ifndef TRACE_H
#define TRACE_H

#include <QObject>
#include <QChartView>
#include <QXYSeries>
#include <QLineSeries>
#include <QScatterSeries>
#include <QValueAxis>

QT_CHARTS_USE_NAMESPACE


class Trace : public QObject
{
    Q_OBJECT

public:
    Trace(QString type,
          QChartView *chartView,
          QAbstractAxis *xAxis,
          QString name,
          double edgeSpace,
          Qt::Alignment alignment,
          QColor color,
          QObject *parent = nullptr);
    ~Trace();

    void newPoint(double x, double y);
    void newPoint(QPointF p);
    void hide(){mSeries->hide(); mAxis->hide();}
    void clear();

private:
    QXYSeries *mSeries;
    QValueAxis *mAxis;

    double mEdgeSpace;
    double mMin;
    double mMax;
};

#endif // TRACE_H
