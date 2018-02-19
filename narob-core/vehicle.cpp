#include "vehicle.h"

Vehicle::Vehicle() :
    mId(-1),

    mNumber(""),
    mCompClass(""),
    mWeight(0)
{
}

Vehicle::Vehicle(const Vehicle &vehicle) :
    mId(vehicle.id()),

    mNumber(vehicle.number()),
    mCompClass(vehicle.compClass()),
    mWeight(vehicle.weight())
{
}
