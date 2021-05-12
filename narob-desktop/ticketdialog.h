#ifndef TICKETDIALOG_H
#define TICKETDIALOG_H

#include <memory>

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

namespace Ui {
class TicketDialog;
}

class TicketDialog : public DialogBase
{
    Q_OBJECT

public:
    explicit TicketDialog(TicketsLogbookModel *tLModel,
                          TicketsRaceModel *tRModel,
                          std::shared_ptr<Vehicle> vehicle,
                          std::shared_ptr<Race> race,
                          int row = -1,
                          QWidget *parent = nullptr);
    ~TicketDialog();

private:
    void setupModel();
    void createUi();
    void updateWeather();
    void updateSplits();
    void updatePrediction();
    void handleClockGood(QLineEdit *edit, QCheckBox *checkBox);
    void formatDoubleEdit(const QString &field,
                          QLineEdit *edit,
                          const int decimals);
    void formatNumberLabel(const QVariant &value,
                           QLabel *label,
                           const int decimals);
    void formatClockEdit(const QString &field,
                         QLineEdit *edit,
                         QCheckBox *checkBox);
    void updateWValue(const QString &field);
    void updateSValue(const QString &field,
                      double value);
    void updatePLabel(const QString &field,
                      QLabel *label);
    void updateWLabel(const QString &field,
                      QLabel *label,
                      const int decimals);
    void updateSLabel(const QString &field,
                      QLabel *label,
                      const int decimals);

    Ui::TicketDialog *ui;

    int mId;
    std::shared_ptr<Vehicle> mVehicle;
    std::shared_ptr<Race> mRace;
    Observation mObservation;
    Prediction *mPredictedRun;
    ObservationsModel *mObservationsModel;
    TicketsLogbookModel *mTicketsLogbookModel;
    TicketsRaceModel *mTicketsRaceModel;
    QTimer *mDateTimer;
    QTimer *mFactorTimer;

private slots:
    void onShowPredictionsClicked();
    void onDateChange();
    void onTrackTicketsCheckboxChange();
    void onVehicleTicketsCheckboxChange();
    void onFactorChange();
    void onButtonBoxAccepted();
};

#endif // TICKETDIALOG_H
