////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Db/DbCondition.cpp
//! @date
//!     2023/12/21
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ARA/Db/DbCondition.h"

ARA_BEGIN_NAMESPACE

static DbConditionOperator OperatorFromStr(const std::string& op) 
{
    if (op == "=")
        return DbConditionOperator::Equal; 
    else if (op == "!=")
        return DbConditionOperator::NotEqual;
    else if (op == ">")
        return DbConditionOperator::GreaterThan;
    else if (op == ">=")
        return DbConditionOperator::GreaterThanOrEqual;
    else if (op == "<")
        return DbConditionOperator::LessThan;
    else if (op == "<=")
        return DbConditionOperator::LessThanOrEqual;

    throw Error("[DbCondition] Operator Enum unrecognized.");
}

DbCondition::DbCondition(const std::string& field, DbConditionOperator op, const DbData& data):
mField(field), mSlotId(0), mCndOp(op), mData(data)
{
   
}

DbCondition::DbCondition(const std::string& field, const std::string& op, const DbData& data):
mField(field), mSlotId(0), mCndOp(OperatorFromStr(op)), mData(data)
{

}

DbCondition::DbCondition(DbId slot, DbConditionOperator op, const DbData& data):
mSlotId(slot), mCndOp(op), mData(data)
{

}

DbCondition::DbCondition(DbId slot, const std::string& op, const DbData& data):
mSlotId(slot), mCndOp(OperatorFromStr(op)), mData(data) 
{

}

bool DbCondition::validate(const DbData& data) const
{
    switch (mCndOp)
    {
        case DbConditionOperator::Equal:
            return mData == data;

        case DbConditionOperator::NotEqual:
            return !(mData == data);

        case DbConditionOperator::GreaterThan:
            return mData > data; 

        case DbConditionOperator::GreaterThanOrEqual:
            return mData > data || mData == data;

        case DbConditionOperator::LessThan:
            return !(mData > data || mData == data);

        case DbConditionOperator::LessThanOrEqual:
            return !(mData > data);
    }

    throw Error("[DbCondition] unreachable or passed DbConditionOperator is invalid.");
}

ARA_END_NAMESPACE