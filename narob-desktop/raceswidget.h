#ifndef RACESWIDGET_H
#define RACESWIDGET_H

#include "races.h"
#include "tableeditwidgetbase.h"
#include "ui_tablewidgetbase.h"

class RacesWidget : public TableEditWidgetBase
{
    Q_OBJECT

public:
    explicit RacesWidget(QWidget *parent = 0);

    Race* getSelectedRace();

private slots:
    void addRace();
    void editRace();
    void deleteRace();

    void updateModels();

private:
    RacesModel *mRacesModel;
};

#endif // RACESWIDGET_H
