#include "predictionswidget.h"

PredictionsWidget::PredictionsWidget(PredictionsModel *model,
                                     QWidget *parent) :
    TableDisplayWidgetBase("Predictions", parent),
    mPredictionsModel(model)
{
    mModel = mPredictionsModel;

    ui->tableView->setModel(mPredictionsModel);

    setupColumns(PREDICTION_FIELDS);

    hide("raceId");
    hide("vehicleId");
    hide("ticketId");
    hide("trackId"); // DEV ONLY - remove column from test databases

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





    // set colors base on *_COLOR globals

    // make info dialog that opens on doubleclick






    initTable();
}
