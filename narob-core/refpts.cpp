#include "refpts.h"

Fields refPTFields()
{
    Fields f;

    f.append(Field("id", "id", 0, 0));
    f.append(Field("predictionId", "PredictionId", 0, 0));
    f.append(Field("ticketId", "TicketId", 0, 0));
    f.append(Field("distance", "Distance", 70, -4));

    return f;
}

RefPTs::RefPTs() :
    DbTableBase()
{
    mFields = refPTFields();
    mTable = "refPTs";
}


RefPT::RefPT() :
    DbRecordBase()
{
    mFields = refPTFields();
    init("refPTs");
}

RefPTsModel::RefPTsModel(QObject *parent) :
    ModelBase("refPTs",
              refPTFields(),
              parent)
{
}
