#ifndef OBSERVATIONSWIDGET_H
#define OBSERVATIONSWIDGET_H

#include "observations.h"
#include "tabledisplaywidgetbase.h"
#include "ui_tablewidgetbase.h"

class ObservationsWidget : public TableDisplayWidgetBase
{
    Q_OBJECT

public:
    explicit ObservationsWidget(QWidget *parent = 0);

public slots:
    void refresh() { mObservationsModel->select(); }

private:
    ObservationsModel *mObservationsModel;
};

#endif // OBSERVATIONSWIDGET_H
