#ifndef RACEDIALOG_H
#define RACEDIALOG_H

#include "dialogbase.h"
#include "races.h"

namespace Ui {
class RaceDialog;
}

class RaceDialog : public DialogBase
{
    Q_OBJECT

public:
    explicit RaceDialog(int row = -1,
                        QWidget *parent = nullptr);
    ~RaceDialog();

private:
    Ui::RaceDialog *ui;

    void setupModel();
    void createUi();
};

#endif // RACEDIALOG_H
