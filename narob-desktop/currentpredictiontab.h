#ifndef CURRENTPREDICTIONTAB_H
#define CURRENTPREDICTIONTAB_H

#include "predictions.h"

#include <QWidget>
#include <QLabel>
#include <QTimer>

namespace Ui {
class CurrentPredictionTab;
}

class CurrentPredictionTab : public QWidget
{
    Q_OBJECT

public:
    explicit CurrentPredictionTab(Prediction *prediction,
                                  TicketsLogbookModel *tLModel,
                                  PredictionsModel *pModel,
                                  std::shared_ptr<Vehicle> vehicle,
                                  QWidget *parent = nullptr);
    ~CurrentPredictionTab();

signals:
    void predictionUpdated();
    void predictionWrittenToDB();

private:
    void writePredictionToDb();
    void updateDisplay();
    void sendPage();
    void pageLine(QString line, QString field, int decimals);
    void mailSent(QString);
    void formatNumberLabel(const QVariant &value,
                           QLabel *label,
                           const int decimals);
    void updatePLabel(const QString &field,
                      QLabel *label);

    Ui::CurrentPredictionTab *ui;
    Prediction *mCurrentPrediction;
    PredictionsModel *mPredictionsModel;
    TicketsLogbookModel *mTicketsLogbookModel;
    QString mPage;
    QTimer *mAutoTimer;
    QTimer *mFactorTimer;

private slots:
    void makePrediction();
    void onTrackTicketsCheckboxChange();
    void onVehicleTicketsCheckboxChange();
    void onFactorChange();
};

#endif // CURRENTPREDICTIONTAB_H
