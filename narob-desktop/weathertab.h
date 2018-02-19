#ifndef WEATHERTAB_H
#define WEATHERTAB_H

#include "observationsmodel.h"
#include "observationswidget.h"
#include "weatherstation.h"

#include <QWidget>

class WeatherStation;

namespace Ui {
class WeatherTab;
}

class WeatherTab : public QWidget
{
    Q_OBJECT

public:
    explicit WeatherTab(QWidget *parent = 0);
    ~WeatherTab();
    ObservationsModel* getModel() { return mObservationsModel; }

signals:
    void sendStatus(QString status);

private:
    Ui::WeatherTab *ui;

    void startWeatherStation();

    ObservationsModel *mObservationsModel;
    ObservationsWidget *mObservationsWidget;
    WeatherStation *mWeatherStation;
};

#endif // WEATHERTAB_H
