////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Controls/ControlActionValidator.h
//! @date
//!     2023/12/10
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ARA_CONTROLS_CONTROLACTIONVALIDATOR_H__
#define __ARA_CONTROLS_CONTROLACTIONVALIDATOR_H__

#include "Platform.h"

ARA_CONTROLS_BEGIN_NS

class Control;

//! @brief
//! A Validator class that returns true if a control should send its action.
//!
class ControlActionValidator
{
public:
    
    //! @brief
    //! Virtual destructor.
    //!
    virtual ~ControlActionValidator() = default;
    
    //! @brief
    //! Returns true if a control should send its action.
    //!
    //! @param control
    //!     The control to validate.
    //! @param event
    //!     The event to validate. Check the field `event.type` to know the current
    //!     event type and process it accordingly.
    //!
    //! @return
    //!     True if the control should send its action.
    //!
    virtual bool validate(const Control& control, const Event& event) = 0;
};

typedef ARA::Ptr < ControlActionValidator > ControlActionValidatorPtr;

ARA_CONTROLS_END_NS

#endif
