#ifndef DIALOGBASE_H
#define DIALOGBASE_H

#include <QDialog>
#include <QDataWidgetMapper>

#include "modelbase.h"

class DialogBase : public QDialog
{
    Q_OBJECT

public:
    DialogBase(QWidget *parent = 0);

    QModelIndex indexForField(const QString &field);

public slots:
    void onButtonBoxAccepted();

signals:
    void ready();

protected:
    void setModelRow(int row);

    ModelBase *mModel;
    QDataWidgetMapper *mMapper;
    int mRow;
};

#endif // DIALOGBASE_H
