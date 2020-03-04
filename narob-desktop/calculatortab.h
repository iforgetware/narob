#ifndef CALCULATORTAB_H
#define CALCULATORTAB_H

#include <QWidget>

namespace Ui {
class CalculatorTab;
}

class CalculatorTab : public QWidget
{
    Q_OBJECT

public:
    explicit CalculatorTab(QWidget *parent = nullptr);
    ~CalculatorTab();

private:
    Ui::CalculatorTab *ui;
};

#endif // CALCULATORTAB_H
