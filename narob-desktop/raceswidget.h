#ifndef RACESWIDGET_H
#define RACESWIDGET_H

#include "racesmodel.h"
#include "tableeditwidgetbase.h"
#include "ui_tableeditwidgetbase.h"

class RacesWidget : public TableEditWidgetBase
{
    Q_OBJECT

public:
    RacesWidget(QWidget *parent = 0);

    Race* getSelectedRace();

private slots:
    void addRace();
    void editRace();
    void deleteRace();

private:
    RacesModel *mRacesModel;
};

#endif // RACESWIDGET_H
