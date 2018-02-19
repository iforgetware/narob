#ifndef VEHICLE_H
#define VEHICLE_H

#include <QString>

#include "narob-core_global.h"

class NAROBCORESHARED_EXPORT Vehicle
{
public:
    explicit Vehicle();
    explicit Vehicle(const Vehicle &vehicle);

    int id() const { return mId; }
    void setId(const int &id) { mId = id; }

    QString number() const { return mNumber; }
    void setNumber(const QString &number) { mNumber = number; }

    QString compClass() const { return mCompClass; }
    void setCompClass(const QString &compClass) { mCompClass = compClass; }

    int weight() const { return mWeight; }
    void setWeight(const int &weight) { mWeight = weight; }

private:
    int mId;

    QString mNumber;
    QString mCompClass;
    int mWeight;
};

#endif // VEHICLE_H
