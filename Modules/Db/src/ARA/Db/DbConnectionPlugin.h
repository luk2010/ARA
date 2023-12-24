////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Db/DbConnectionPlugin.h
//! @date
//!     2023/12/24
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ARA_DB_DBCONNECTIONPLUGIN_H__
#define __ARA_DB_DBCONNECTIONPLUGIN_H__

#include "ARA/Core/ARAPlugin.h"
#include "ARA/Db/DbConnection.h"

ARA_BEGIN_NAMESPACE

//! @brief 
//! Defines a plugin that creates a DbConnection.
//!
class DbConnectionPlugin : public Plugin < DbConnection > 
{
public: 

    using Plugin::Plugin;
};

ARA_END_NAMESPACE

#endif