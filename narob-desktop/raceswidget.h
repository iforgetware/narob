#ifndef RACESWIDGET_H
#define RACESWIDGET_H

#include <memory>

#include "races.h"
#include "tableeditwidgetbase.h"
#include "ui_tablewidgetbase.h"

class RacesWidget : public TableEditWidgetBase
{
    Q_OBJECT

public:
    explicit RacesWidget(QWidget *parent = nullptr);

    std::shared_ptr<Race> selectedRace() const;

private slots:
    void addRace();
    void editRace();

private:
    RacesModel *mRacesModel;
};

#endif // RACESWIDGET_H
