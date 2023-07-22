//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_main.hpp"
#include "my_sys.hpp"
#include "my_unicode.hpp"

wchar_t unicode_alias_to_char(const std::string &s)
{
  TRACE_AND_INDENT();

  if (s == "space") { return UNICODE_0x20; }
  if (s == "exclamation_mark") { return UNICODE_0x21; }
  if (s == "double_quote") { return UNICODE_0x22; }
  if (s == "number") { return UNICODE_0x23; }
  if (s == "dollar") { return UNICODE_0x24; }
  if (s == "percent") { return UNICODE_0x25; }
  if (s == "ampersand") { return UNICODE_0x26; }
  if (s == "single_quote") { return UNICODE_0x27; }
  if (s == "left_parenthesis") { return UNICODE_0x28; }
  if (s == "right_parenthesis") { return UNICODE_0x29; }
  if (s == "asterisk") { return UNICODE_0x2a; }
  if (s == "plus") { return UNICODE_0x2b; }
  if (s == "comma") { return UNICODE_0x2c; }
  if (s == "minus") { return UNICODE_0x2d; }
  if (s == "period") { return UNICODE_0x2e; }
  if (s == "slash") { return UNICODE_0x2f; }
  if (s == "zero") { return UNICODE_0x30; }
  if (s == "one") { return UNICODE_0x31; }
  if (s == "two") { return UNICODE_0x32; }
  if (s == "three") { return UNICODE_0x33; }
  if (s == "four") { return UNICODE_0x34; }
  if (s == "five") { return UNICODE_0x35; }
  if (s == "six") { return UNICODE_0x36; }
  if (s == "seven") { return UNICODE_0x37; }
  if (s == "eight") { return UNICODE_0x38; }
  if (s == "nine") { return UNICODE_0x39; }
  if (s == "colon") { return UNICODE_0x3a; }
  if (s == "semicolon") { return UNICODE_0x3b; }
  if (s == "less_than") { return UNICODE_0x3c; }
  if (s == "equality_sign") { return UNICODE_0x3d; }
  if (s == "greater_than") { return UNICODE_0x3e; }
  if (s == "question_mark") { return UNICODE_0x3f; }
  if (s == "at_sign") { return UNICODE_0x40; }
  if (s == "left_square_bracket") { return UNICODE_0x5b; }
  if (s == "backslash") { return UNICODE_0x5c; }
  if (s == "right_square_bracket") { return UNICODE_0x5d; }
  if (s == "caret") { return UNICODE_0x5e; }
  if (s == "underscore") { return UNICODE_0x5f; }
  if (s == "grave") { return UNICODE_0x60; }
  if (s == "left_curly_bracket") { return UNICODE_0x7b; }
  if (s == "vertical_bar") { return UNICODE_0x7c; }
  if (s == "right_curly_bracket") { return UNICODE_0x7d; }
  if (s == "tilde") { return UNICODE_0x7e; }
  if (s == "delete") { return UNICODE_0x7f; }
  if (s == "middle_dot") { return UNICODE_0x80; }
  if (s == "four_dots") { return UNICODE_0x81; }
  if (s == "diamond") { return UNICODE_0x82; }
  if (s == "inverted_v") { return UNICODE_0x83; }
  if (s == "aries") { return UNICODE_0x84; }
  if (s == "ankh") { return UNICODE_0x85; }
  if (s == "music_note") { return UNICODE_0x86; }
  if (s == "circle") { return UNICODE_0x87; }
  if (s == "solid_circle") { return UNICODE_0x89; }
  if (s == "lollipop") { return UNICODE_0x8a; }
  if (s == "three_dots") { return UNICODE_0x8e; }
  if (s == "up_arrow") { return UNICODE_0x90; }
  if (s == "down_arrow") { return UNICODE_0x91; }
  if (s == "left_arrow") { return UNICODE_0x92; }
  if (s == "right_arrow") { return UNICODE_0x93; }
  if (s == "up_triangle") { return UNICODE_0x94; }
  if (s == "down_triangle") { return UNICODE_0x95; }
  if (s == "omega") { return UNICODE_0x96; }
  if (s == "theta") { return UNICODE_0x97; }
  if (s == "lambda") { return UNICODE_0x98; }
  if (s == "strike") { return UNICODE_0x99; }
  if (s == "diamond_solid") { return UNICODE_0x9a; }
  if (s == "cross") { return UNICODE_0x9b; }
  if (s == "cursor") { return UNICODE_0xc0; }
  if (s == "block") { return UNICODE_0xc1; }
  if (s == "pointer") { return UNICODE_0xc2; }
  if (s == "wtf") { return UNICODE_0xc3; }
  if (s == "newline") { return UNICODE_0xc4; }

  if (s.size() > 1) { ERR("Bad unicode string [%s]", s.c_str()); }

  return s[ 0 ];
}
