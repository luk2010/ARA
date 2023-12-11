# ARA Controls Module

This module defines multiple basic controls like buttons, and inputs. They
are all based on `ARA::Text::Element`, and thus the module `ARA::Text` must
be present.

## ARA::Controls::Control base class

All controls derive from the base class Control. The Control class ensure
the element has a string value retrievable.
