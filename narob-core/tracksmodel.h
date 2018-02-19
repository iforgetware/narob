#ifndef TRACKSMODEL_H
#define TRACKSMODEL_H

#include <QVector>

#include "modelbase.h"

#include "narob-core_global.h"
#include "track.h"
#include "databasemanager.h"

class NAROBCORESHARED_EXPORT TracksModel : public ModelBase
{
    Q_OBJECT

public:
    TracksModel(QObject *parent = 0);

    Track* getTrack(const int id);
    QModelIndex addTrack(const Track &track);
//    void updateTrack(const Track *track);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    bool removeRows(int row, int count, const QModelIndex& parent) override;

private:
    DatabaseManager &mDb;
    QVector<Track*> mTracks;
};

#endif // TRACKSMODEL_H
