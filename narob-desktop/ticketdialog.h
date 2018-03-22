#ifndef TICKETDIALOG_H
#define TICKETDIALOG_H

#include <QDialog>
#include <QDataWidgetMapper>

#include "tickets.h"
#include "vehicles.h"
#include "races.h"

namespace Ui {
class TicketDialog;
}

class TicketDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TicketDialog(Vehicle* vehicle,
                          Race* race,
                          int row = -1,
                          QWidget *parent = 0);
    ~TicketDialog();

signals:
    void ready();

private slots:
    void onButtonBoxAccepted();

private:
    Ui::TicketDialog *ui;
    TicketsModel *mTicketsModel;
    Vehicle mVehicle;

    QDataWidgetMapper *mMapper;

    void setupModel();
    void createUi();
    void dateTimeChanged(const QDateTime& dateTime);
    void setWeather();
};

#endif // TICKETDIALOG_H
