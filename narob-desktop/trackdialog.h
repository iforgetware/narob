#ifndef TRACKDIALOG_H
#define TRACKDIALOG_H

#include <QDialog>
#include <QDataWidgetMapper>
//#include <QMessageBox>

#include "tracksmodel.h"

namespace Ui {
class TrackDialog;
}

class TrackDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TrackDialog(TracksModel *model, int row = -1, QWidget *parent = 0);
    ~TrackDialog();

signals:
//    void ready();

private slots:
    void onButtonBoxAccepted();
    void clearEmptyAdd();

private:
    Ui::TrackDialog *ui;
    TracksModel *mTracksModel;

    QDataWidgetMapper *mMapper;

    void setupModel();
    void createUi();
};

#endif // TRACKDIALOG_H
