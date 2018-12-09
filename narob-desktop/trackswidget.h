#ifndef TRACKSWIDGET_H
#define TRACKSWIDGET_H

#include "tracks.h"
#include "tableeditwidgetbase.h"
#include "ui_tablewidgetbase.h"

class TracksWidget : public TableEditWidgetBase
{
    Q_OBJECT

public:
    explicit TracksWidget(QWidget *parent = nullptr);

private slots:
    void addTrack();
    void editTrack();

private:
    TracksModel *mTracksModel;
};

#endif // TRACKSWIDGET_H
