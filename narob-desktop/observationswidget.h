#ifndef OBSERVATIONSWIDGET_H
#define OBSERVATIONSWIDGET_H

#include "observationsmodel.h"
#include "tablewidgetbase.h"
#include "ui_tablewidgetbase.h"

class ObservationsWidget : public TableWidgetBase
{
    Q_OBJECT

public:
    explicit ObservationsWidget(ObservationsModel *model, QWidget *parent = 0);

    void setModel(ObservationsModel *model);

public slots:
    void refresh() { mObservationsModel->select(); }

private:
    ObservationsModel *mObservationsModel;
};

#endif // OBSERVATIONSWIDGET_H
