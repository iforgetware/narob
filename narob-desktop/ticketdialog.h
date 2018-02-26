#ifndef TICKETDIALOG_H
#define TICKETDIALOG_H

#include <QDialog>
#include <QDataWidgetMapper>

#include "ticketsmodel.h"
#include "vehicle.h"
#include "race.h"

namespace Ui {
class TicketDialog;
}

class TicketDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TicketDialog(TicketsModel *model,
                          Vehicle* vehicle,
                          Race* race,
                          int row = -1,
                          QWidget *parent = 0);
    ~TicketDialog();

private slots:
    void onButtonBoxAccepted();
    void clearEmptyAdd();

private:
    Ui::TicketDialog *ui;
    TicketsModel *mTicketsModel;

    QDataWidgetMapper *mMapper;

    void setupModel();
    void createUi();
    void dateChanged(const QDate& date);
    void timeChanged(const QTime& time);
    void setWeather();
};

#endif // TICKETDIALOG_H
