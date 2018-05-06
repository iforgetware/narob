#ifndef TICKETDIALOG_H
#define TICKETDIALOG_H

#include "dialogbase.h"
#include "tickets.h"
#include "vehicles.h"
#include "races.h"
#include "tracks.h"
#include "observations.h"

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

    Vehicle *mVehicle;
    Race *mRace;
    ObservationsModel *mObservationsModel;

    void setupModel();
    void createUi();
    void setWeather(const QDateTime& dateTime);
};

#endif // TICKETDIALOG_H
