#ifndef TICKETDIALOG_H
#define TICKETDIALOG_H

#include <QCheckBox>
#include <QLineEdit>
#include <QLabel>
#include <QTimer>

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
    QTimer *mDateTimer;
    QTimer *mFactorTimer;

    void formatDoubleEdit(const QString &field,
                          QLineEdit *edit,
                          const int decimals);
    void formatNumberLabel(const QVariant &value,
                           QLabel *label,
                           const int decimals);
    void formatClockEdit(const QString &field,
                         QLineEdit *edit,
                         QCheckBox *checkBox);
    void setupModel();
    void createUi();
    void handleClockGood(QLineEdit *edit, QCheckBox *checkBox);
    void updateWeather();
    void updateDisplay();

private slots:
    void onShowPredictionsClicked();
    void onDateChange();
    void onFactorChange();
    void onButtonBoxAccepted();
};

#endif // TICKETDIALOG_H
