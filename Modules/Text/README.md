# ARA Text Module

The ARA text module defines interfaces and objects used to display
text into regions. The module consists in the following classes, all
in the `ARA::Text` namespace:

- `ARA::Text::Element`: A base element class that displays a text.
- `ARA::Text::Frame`: The class that holds a text in a frame.
- `ARA::Text::String`: The object that holds a string and attributes for
  this string.
- `ARA::Text::Paragraph`: A paragraph in a frame.
- `ARA::Text::Line`: A line in a paragraph.
- `ARA::Text::Run`: A list of Glyphes that share the same attributes in
  a line.

You create directly a `ARA::Text::Frame` and sets the string. Then, you
call `ARA::Text::Frame::layout()` to build the text frame. When inserting
a character in the String, call `didInsertCharacter` on the text frame
and when removing a character from the string, call `didRemoveCharacter`
to optimize the frame rebuilding.
