#ifndef RACEDIALOG_H
#define RACEDIALOG_H

#include <QDialog>
#include <QDataWidgetMapper>

#include "racesmodel.h"

namespace Ui {
class RaceDialog;
}

class RaceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RaceDialog(RacesModel *model, int row = -1, QWidget *parent = 0);
    ~RaceDialog();

private slots:
    void onButtonBoxAccepted();
    void clearEmptyAdd();

private:
    Ui::RaceDialog *ui;
    RacesModel *mRacesModel;

    QDataWidgetMapper *mMapper;

    void setupModel();
    void createUi();
};

#endif // RACEDIALOG_H
