////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Controls/Control.h
//! @date
//!     2023/12/10
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ARA_CONTROLS_CONTROL_H__
#define __ARA_CONTROLS_CONTROL_H__

#include "Platform.h"
#include "ControlActionMask.h"
#include "ControlActionValidator.h"
#include "ControlState.h"

ARA_CONTROLS_BEGIN_NS

//! @brief
//! A base class for every controls in this module.
//!
class Control : public ARA::Text::Element
{
    //! @brief
    //! A mask determining when the control should send its action.
    //!
    ControlActionMask mActionMask;
    
    //! @brief
    //! A validator that returns true if the control should send its action.
    //!
    ControlActionValidatorPtr mActionValidator;
    
    //! @brief
    //! The current control state.
    //!
    ControlState mState;
    
public:
    
    //! @brief
    //! Creates a new Control instance.
    //!
    Control(const Text::String& string);
    
    //! @brief
    //! A function a derived class should implement when the user actions the control.
    //!
    virtual bool action();
    
    //! @brief
    //! Returns a mask determining when the control should send its action.
    //!
    virtual ControlActionMask actionMask() const;
    
    //! @brief
    //! Sets a mask determining when the control should send its action.
    //!
    virtual void setActionMask(ControlActionMask mask);
    
    //! @brief
    //! Returns the custom action validator.
    //!
    virtual ControlActionValidatorPtr actionValidator() const;
    
    //! @brief
    //! Sets the current custom action validator.
    //!
    virtual void setActionValidator(const ControlActionValidatorPtr& validator);
    
    //! @brief
    //! Handles an event and calls the custom validator only if the event could not be
    //! proceeded by another function.
    //!
    virtual bool handleEvent(const Event& event);
    
    //! @brief
    //! Returns the current control state.
    //!
    virtual const ControlState& state() const;
    
protected:

    //! @brief
    //! Returns the current control state.
    //!
    virtual ControlState& state();
    
protected:
    
    //! @brief
    //! Responds to a MouseDown event.
    //!
    virtual bool onMouseDown(const MouseDownEvent& event);
    
    //! @brief
    //! Responds to a MouseUp event. If a MouseDown event was already registered, it calls the
    //! action if mActionMask has the Click (or RightClick) flag set.
    //!
    virtual bool onMouseUp(const MouseUpEvent& event);
    
    //! @brief
    //! Responds to a KeyDown event and updates the control state accordingly.
    //!
    virtual bool onKeyDown(const KeyEvent& event);
    
    //! @brief
    //! Responds to a KeyUp event and updates the control state accordingly.
    //!
    virtual bool onKeyUp(const KeyEvent& event);
    
    //! @brief
    //! Notifies the control its state has changed.
    //!
    virtual void onStateChange(const ControlState& state);
};

ARA_CONTROLS_END_NS

#endif
