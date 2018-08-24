#ifndef TICKETDIALOG_H
#define TICKETDIALOG_H

#include <QCheckBox>
#include <QLineEdit>
#include <QLabel>

#include "dialogbase.h"
#include "tickets.h"
#include "vehicles.h"
#include "races.h"
#include "tracks.h"
#include "observations.h"
#include "predictions.h"
#include "settings.h"
//#include "refpts.h"

namespace Ui {
class TicketDialog;
}

class TicketDialog : public DialogBase
{
    Q_OBJECT

public:
    explicit TicketDialog(Vehicle* vehicle,
                          Race* race,
                          int row = -1,
                          QWidget *parent = 0);
    ~TicketDialog();

private:
    Ui::TicketDialog *ui;

    Settings *mSettingsTable;
    DbRecordBase *mSettings;
    int mId;
    Vehicle *mVehicle;
    Race *mRace;
    ObservationsModel *mObservationsModel;
    PredictionsModel *mPredictionsModel;
//    RefPTsModel *mRefPTsModel;

    void formatDoubleEdit(const QString &field,
                          QLineEdit *edit,
                          const int decimals);
    void formatDoubleLabel(const QString &field,
                           QLabel *label,
                           const int decimals);
    void formatClockEdit(const QString &field,
                         QLineEdit *edit,
                         QCheckBox *checkBox);
    QString formatClock(const QVariant &clock);
    void setupModel();
    void createUi();
    void setWeather(const QDateTime& dateTime);
    void handleClockGood(QLineEdit *edit, QCheckBox *checkBox);
    void onButtonBoxAccepted();
    void updatePredictionDisplay(Prediction &prediction);

private slots:
    void onComparePredictionClicked();
    void onShowPredictionsClicked();
};

#endif // TICKETDIALOG_H
