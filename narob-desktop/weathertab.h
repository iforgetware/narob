#ifndef WEATHERTAB_H
#define WEATHERTAB_H

#include <QWidget>

#include "observations.h"
#include "observationswidget.h"
#include "weathergraphwidget.h"
#include "weatherstation.h"

//class WeatherStation;

namespace Ui {
class WeatherTab;
}

class WeatherTab : public QWidget
{
    Q_OBJECT

public:
    explicit WeatherTab(QWidget *parent = nullptr);
    ~WeatherTab();
    void updateAllModels();
//    ObservationsModel* getModel() { return mObservationsModel; }

signals:
    void sendStatus(QString status);

private:
    Ui::WeatherTab *ui;
    void startWeatherStation();

    ObservationsModel *mObservationsModel;
    QLabel *mAdjustmentLabel;
    ObservationsWidget *mObservationsWidget;
    WeatherGraphWidget *mWeatherGraphWidget;
    WeatherStation *mWeatherStation;

private slots:
    void updateAdjustmentDisplay();
};

#endif // WEATHERTAB_H
