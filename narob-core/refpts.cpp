#include "refpts.h"

Fields setRefPTFields()
{
    Fields retFields;

    retFields.append(Field("id", "id", 0, 0));
    retFields.append(Field("predictionId", "PredictionId", 0, 0));
    retFields.append(Field("ticketId", "TicketId", 0, 0));
    retFields.append(Field("distance", "Distance", 70, -4));

    return retFields;
}

Fields refPTFields = setRefPTFields();

RefPTs::RefPTs() :
    DbTableBase()
{
    mFields = refPTFields;
    mTable = "refPTs";
}


RefPT::RefPT() :
    DbRecordBase()
{
    mFields = refPTFields;
    init("refPTs");
}

RefPTsModel::RefPTsModel(QObject *parent) :
    ModelBase(parent)
{
    setTable("refPTs");

    select();
}

void RefPTsModel::addRefPT(RefPT &refPT)
{
    insertRecord(-1, refPT);
    submitAll();
    select();
}
