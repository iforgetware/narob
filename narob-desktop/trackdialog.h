#ifndef TRACKDIALOG_H
#define TRACKDIALOG_H

#include "dialogbase.h"
#include "tracks.h"

namespace Ui {
class TrackDialog;
}

class TrackDialog : public DialogBase
{
    Q_OBJECT

public:
    explicit TrackDialog(int row = -1,
                         QWidget *parent = nullptr);
    ~TrackDialog();

private:
    Ui::TrackDialog *ui;

    void setupModel();
    void createUi();
};

#endif // TRACKDIALOG_H
