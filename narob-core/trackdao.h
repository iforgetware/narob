#ifndef TRACKDAO_H
#define TRACKDAO_H

#include <QSqlDatabase>
#include <QVector>

#include "track.h"

class TrackDao
{
public:
    TrackDao(QSqlDatabase &database);
    void init() const;

    void addTrack(Track &track) const;
//    void updateTrack(const Track *track) const;
    void removeTrack(int id) const;
    QVector<Track*> tracks() const;

private:
    QSqlDatabase &mDatabase;
};

#endif // TRACKDAO_H
