//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_main.hpp"
#include "my_sys.hpp"
#include "my_unicode.hpp"

wchar_t unicode_alias_to_char(const std::string &s)
{
  TRACE_AND_INDENT();

  if (s == "space") { return UNICODE_SPACE; }
  if (s == "exclamation_mark") { return UNICODE_EXCLAMATION_MARK; }
  if (s == "double_quote") { return UNICODE_DOUBLE_QUOTE; }
  if (s == "number") { return UNICODE_NUMBER; }
  if (s == "dollar") { return UNICODE_DOLLAR; }
  if (s == "percent") { return UNICODE_PERCENT; }
  if (s == "ampersand") { return UNICODE_AMPERSAND; }
  if (s == "single_quote") { return UNICODE_SINGLE_QUOTE; }
  if (s == "left_parenthesis") { return UNICODE_LEFT_PARENTHESIS; }
  if (s == "right_parenthesis") { return UNICODE_RIGHT_PARENTHESIS; }
  if (s == "asterisk") { return UNICODE_ASTERISK; }
  if (s == "plus") { return UNICODE_PLUS; }
  if (s == "comma") { return UNICODE_COMMA; }
  if (s == "minus") { return UNICODE_MINUS; }
  if (s == "period") { return UNICODE_PERIOD; }
  if (s == "slash") { return UNICODE_SLASH; }
  if (s == "zero") { return UNICODE_ZERO; }
  if (s == "one") { return UNICODE_ONE; }
  if (s == "two") { return UNICODE_TWO; }
  if (s == "three") { return UNICODE_THREE; }
  if (s == "four") { return UNICODE_FOUR; }
  if (s == "five") { return UNICODE_FIVE; }
  if (s == "six") { return UNICODE_SIX; }
  if (s == "seven") { return UNICODE_SEVEN; }
  if (s == "eight") { return UNICODE_EIGHT; }
  if (s == "nine") { return UNICODE_NINE; }
  if (s == "colon") { return UNICODE_COLON; }
  if (s == "semicolon") { return UNICODE_SEMICOLON; }
  if (s == "less_than") { return UNICODE_LESS_THAN; }
  if (s == "equality_sign") { return UNICODE_EQUALITY_SIGN; }
  if (s == "greater_than") { return UNICODE_GREATER_THAN; }
  if (s == "question_mark") { return UNICODE_QUESTION_MARK; }
  if (s == "at_sign") { return UNICODE_AT_SIGN; }
  if (s == "left_square_bracket") { return UNICODE_LEFT_SQUARE_BRACKET; }
  if (s == "backslash") { return UNICODE_BACKSLASH; }
  if (s == "right_square_bracket") { return UNICODE_RIGHT_SQUARE_BRACKET; }
  if (s == "caret") { return UNICODE_CARET; }
  if (s == "underscore") { return UNICODE_UNDERSCORE; }
  if (s == "grave") { return UNICODE_GRAVE; }
  if (s == "left_curly_bracket") { return UNICODE_LEFT_CURLY_BRACKET; }
  if (s == "vertical_bar") { return UNICODE_VERTICAL_BAR; }
  if (s == "right_curly_bracket") { return UNICODE_RIGHT_CURLY_BRACKET; }
  if (s == "tilde") { return UNICODE_TILDE; }
  if (s == "delete") { return UNICODE_DELETE; }
  if (s == "middle_dot") { return UNICODE_MIDDLE_DOT; }
  if (s == "four_dots") { return UNICODE_FOUR_DOTS; }
  if (s == "diamond") { return UNICODE_DIAMOND; }
  if (s == "inverted_v") { return UNICODE_INVERTED_V; }
  if (s == "aries") { return UNICODE_ARIES; }
  if (s == "ankh") { return UNICODE_ANKH; }
  if (s == "music_note") { return UNICODE_MUSIC_NOTE; }
  if (s == "circle") { return UNICODE_CIRCLE; }
  if (s == "solid_circle") { return UNICODE_SOLID_CIRCLE; }
  if (s == "lollipop") { return UNICODE_LOLLIPOP; }
  if (s == "three_dots") { return UNICODE_THREE_DOTS; }
  if (s == "up_arrow") { return UNICODE_UP_ARROW; }
  if (s == "down_arrow") { return UNICODE_DOWN_ARROW; }
  if (s == "left_arrow") { return UNICODE_LEFT_ARROW; }
  if (s == "right_arrow") { return UNICODE_RIGHT_ARROW; }
  if (s == "up_triangle") { return UNICODE_UP_TRIANGLE; }
  if (s == "down_triangle") { return UNICODE_DOWN_TRIANGLE; }
  if (s == "omega") { return UNICODE_OMEGA; }
  if (s == "theta") { return UNICODE_THETA; }
  if (s == "lambda") { return UNICODE_LAMBDA; }
  if (s == "strike") { return UNICODE_STRIKE; }
  if (s == "diamond_solid") { return UNICODE_DIAMOND_SOLID; }
  if (s == "cross") { return UNICODE_CROSS; }
  if (s == "cursor") { return UNICODE_CURSOR; }
  if (s == "block") { return UNICODE_BLOCK; }
  if (s == "pointer") { return UNICODE_POINTER; }
  if (s == "wtf") { return UNICODE_0xc3; }
  if (s == "newline") { return UNICODE_NEWLINE; }
  if (s == "halo") { return UNICODE_HALO; }

  if (s.size() > 1) { ERR("Bad unicode string [%s]", s.c_str()); }

  return s[ 0 ];
}
