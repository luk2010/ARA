////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Core/ARAEventEmitter.cpp
//! @date
//!     2023/12/11
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ARA/Core/ARAEventEmitter.h"

ARA_BEGIN_NAMESPACE

void EventEmitter::addListener(const EventListenerPtr& listener)
{
    auto found = std::find_if(mListeners.begin(), mListeners.end(), [&listener](auto& wk){
        return wk.lock() == listener;
    });
    
    if (found == mListeners.end())
        mListeners.push_back(listener);
}

void EventEmitter::removeListener(const EventListenerPtr& listener)
{
    auto found = std::find_if(mListeners.begin(), mListeners.end(), [&listener](auto& wk){
        return wk.lock() == listener;
    });
    
    if (found != mListeners.end())
        mListeners.erase(found);
}

bool EventEmitter::sendEvent(const Event& event)
{
    bool handled = false;
    
    for (auto& listener : mListeners)
    {
        auto ptr = listener.lock();
        if (ptr)
            handled |= ptr->handleEvent(event);
    }
    
    return handled;
}

ARA_END_NAMESPACE
