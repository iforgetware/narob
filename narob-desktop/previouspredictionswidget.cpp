#include "previouspredictionswidget.h"

PreviousPredictionsWidget::PreviousPredictionsWidget(PredictionsModel *model,
                                     QWidget *parent) :
    TableDisplayWidgetBase(parent),
    mPredictionsModel(model)
{
    setTitle("Previous Predictions");

    mModel = mPredictionsModel;

    ui->tableView->setModel(mPredictionsModel);

    setupColumns(mPredictionsModel->fields());

    hide("raceId");
    hide("vehicleId");
    hide("trackId");
    hide("ticketId");

    QVector<QString> types;
    types.append("D");
    types.append("A");
    types.append("T");
    types.append("H");
    types.append("P");

    foreach(QString type, types){
        hide("sixty" + type);
        hide("threeThirty" + type);
        hide("thousand" + type);
    }





    // make info dialog that opens on doubleclick






    initTable();
}
