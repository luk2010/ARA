////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Db/DbCondition.h
//! @date
//!     2023/12/21
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ARA_DB_DBCONDITION_H__
#define __ARA_DB_DBCONDITION_H__

#include "ARA/Db/DbConditionOperator.h"
#include "ARA/Db/DbData.h"

ARA_BEGIN_NAMESPACE

//! @brief 
//! Defines a single condition used when selecting a value from a 
//! DbResult, or for a DbRequest. 
//! 
class DbCondition 
{
    //! @brief 
    //! The field the condition refers to. If empty, the condition tries to take
    //! the slot index in `mSlot`.
    //! 
    std::string mField;

    //! @brief 
    //! The index of the slot to look for, if `mField` is empty.
    //! 
    DbId mSlotId; 

    //! @brief 
    //! The operator to fill the condition. 
    //! 
    DbConditionOperator mCndOp; 

    //! @brief 
    //! The data to compare to. 
    //! 
    DbData mData; 

public: 

    //! @brief 
    //! Creates a new condition. 
    //! 
    DbCondition(const std::string& field, DbConditionOperator op, const DbData& data);

    //! @brief 
    //! Creates a new condition. 
    //! 
    DbCondition(const std::string& field, const std::string& op, const DbData& data);

    //! @brief 
    //! Creates a new condition. 
    //! 
    DbCondition(DbId slot, DbConditionOperator op, const DbData& data);

    //! @brief 
    //! Creates a new condition. 
    //! 
    DbCondition(DbId slot, const std::string& op, const DbData& data);

    //! @brief 
    //! Returns the condition field. 
    //! 
    inline const std::string& field() const { return mField; }

    //! @brief 
    //! Returns the condition slot. 
    //! 
    inline DbId slot() const { return mSlotId; }

    //! @brief 
    //! Returns the condition operator. 
    //! 
    inline DbConditionOperator op() const { return mCndOp; }

    //! @brief 
    //! Returns the condition data. 
    //! 
    inline const DbData& data() const { return mData; }

    //! @brief 
    //! Returns true if the given data fullfills the condition. 
    //! 
    bool validate(const DbData& data) const; 
};

typedef std::vector < DbCondition > DbConditionList;

ARA_END_NAMESPACE

#endif 