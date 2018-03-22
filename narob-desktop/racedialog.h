#ifndef RACEDIALOG_H
#define RACEDIALOG_H

#include <QDialog>
#include <QDataWidgetMapper>

#include "races.h"

namespace Ui {
class RaceDialog;
}

class RaceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RaceDialog(int row = -1,
                        QWidget *parent = 0);
    ~RaceDialog();

signals:
    void ready();

private slots:
    void onButtonBoxAccepted();

private:
    Ui::RaceDialog *ui;
    RacesModel *mRacesModel;

    QDataWidgetMapper *mMapper;

    void setupModel();
    void createUi();
};

#endif // RACEDIALOG_H
