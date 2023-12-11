////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Core/ARAEventEmitter.h
//! @date
//!     2023/12/11
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ARA_CORE_EVENTEMITTER_H__
#define __ARA_CORE_EVENTEMITTER_H__

#include "ARA/Core/ARAEventListener.h"

ARA_BEGIN_NAMESPACE

//! @brief
//! Defines a base class for objects that can send events to EventListeners.
//!
class EventEmitter
{
    //! @brief
    //! The listeners registered.
    //!
    EventListenerWeakList mListeners;
    
public:
    
    //! @brief
    //! Virtual destructor.
    //!
    virtual ~EventEmitter() = default;
    
    //! @brief
    //! Registers a new event listener.
    //!
    virtual void addListener(const EventListenerPtr& listener);
    
    //! @brief
    //! Unregisters an event listener.
    //!
    virtual void removeListener(const EventListenerPtr& listener);
    
    //! @brief
    //! Sends an event to the registered listeners.
    //!
    virtual bool sendEvent(const Event& event);
};

ARA_END_NAMESPACE

#endif
