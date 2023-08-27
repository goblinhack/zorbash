//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_sdl_event.hpp"

std::string to_string_ignoring_mods(const SDL_Keysym &k)
{
  if (k.sym == SDLK_AMPERSAND) {
    return "&";
  }

  if (k.sym == SDLK_ASTERISK) {
    return "*";
  }

  if (k.sym == SDLK_AT) {
    return "@";
  }

  if (k.sym == SDLK_CARET) {
    return "^";
  }

  if (k.sym == SDLK_COLON) {
    return ":";
  }

  if (k.sym == SDLK_DOLLAR) {
    return "$";
  }

  if (k.sym == SDLK_EXCLAIM) {
    return "!";
  }

  if (k.sym == SDLK_GREATER) {
    return ">";
  }

  if (k.sym == SDLK_HASH) {
    return "#";
  }

  if (k.sym == SDLK_LEFTPAREN) {
    return "(";
  }

  if (k.sym == SDLK_LESS) {
    return "<";
  }

  if (k.sym == SDLK_PERCENT) {
    return "%";
  }

  if (k.sym == SDLK_PLUS) {
    return "+";
  }

  if (k.sym == SDLK_QUESTION) {
    return "?";
  }

  if (k.sym == SDLK_QUOTEDBL) {
    return "\"";
  }

  if (k.sym == SDLK_RIGHTPAREN) {
    return ")";
  }

  if (k.sym == SDLK_UNDERSCORE) {
    return "_";
  }
  if ((k.scancode == SDL_SCANCODE_0) || (k.sym == SDLK_0)) {
    return "0";
  }

  if ((k.scancode == SDL_SCANCODE_1) || (k.sym == SDLK_1)) {
    return "1";
  }

  if ((k.scancode == SDL_SCANCODE_2) || (k.sym == SDLK_2)) {
    return "2";
  }

  if ((k.scancode == SDL_SCANCODE_3) || (k.sym == SDLK_3)) {
    return "3";
  }

  if ((k.scancode == SDL_SCANCODE_4) || (k.sym == SDLK_4)) {
    return "4";
  }

  if ((k.scancode == SDL_SCANCODE_5) || (k.sym == SDLK_5)) {
    return "5";
  }

  if ((k.scancode == SDL_SCANCODE_6) || (k.sym == SDLK_6)) {
    return "6";
  }

  if ((k.scancode == SDL_SCANCODE_7) || (k.sym == SDLK_7)) {
    return "7";
  }

  if ((k.scancode == SDL_SCANCODE_8) || (k.sym == SDLK_8)) {
    return "8";
  }

  if ((k.scancode == SDL_SCANCODE_9) || (k.sym == SDLK_9)) {
    return "9";
  }

  if ((k.scancode == SDL_SCANCODE_A) || (k.sym == SDLK_a)) {
    return "a";
  }

  if ((k.scancode == SDL_SCANCODE_AC_BACK) || (k.sym == SDLK_AC_BACK)) {
    return "<AC Back>";
  }

  if ((k.scancode == SDL_SCANCODE_AC_BOOKMARKS) || (k.sym == SDLK_AC_BOOKMARKS)) {
    return "<AC Bookmarks>";
  }

  if ((k.scancode == SDL_SCANCODE_AC_FORWARD) || (k.sym == SDLK_AC_FORWARD)) {
    return "<AC Forward>";
  }

  if ((k.scancode == SDL_SCANCODE_AC_HOME) || (k.sym == SDLK_AC_HOME)) {
    return "<AC Home>";
  }

  if ((k.scancode == SDL_SCANCODE_AC_REFRESH) || (k.sym == SDLK_AC_REFRESH)) {
    return "<AC Refresh>";
  }

  if ((k.scancode == SDL_SCANCODE_AC_SEARCH) || (k.sym == SDLK_AC_SEARCH)) {
    return "<AC Search>";
  }

  if ((k.scancode == SDL_SCANCODE_AC_STOP) || (k.sym == SDLK_AC_STOP)) {
    return "<AC Stop>";
  }

  if ((k.scancode == SDL_SCANCODE_AGAIN) || (k.sym == SDLK_AGAIN)) {
    return "<Again>";
  }

  if ((k.scancode == SDL_SCANCODE_ALTERASE) || (k.sym == SDLK_ALTERASE)) {
    return "<AltErase>";
  }

  if ((k.scancode == SDL_SCANCODE_APOSTROPHE) || (k.sym == SDLK_QUOTE)) {
    return "'";
  }

  if ((k.scancode == SDL_SCANCODE_APPLICATION) || (k.sym == SDLK_APPLICATION)) {
    return "<Application>";
  }

  if ((k.scancode == SDL_SCANCODE_AUDIOMUTE) || (k.sym == SDLK_AUDIOMUTE)) {
    return "<AudioMute>";
  }

  if ((k.scancode == SDL_SCANCODE_AUDIONEXT) || (k.sym == SDLK_AUDIONEXT)) {
    return "<AudioNext>";
  }

  if ((k.scancode == SDL_SCANCODE_AUDIOPLAY) || (k.sym == SDLK_AUDIOPLAY)) {
    return "<AudioPlay>";
  }

  if ((k.scancode == SDL_SCANCODE_AUDIOPREV) || (k.sym == SDLK_AUDIOPREV)) {
    return "<AudioPrev>";
  }

  if ((k.scancode == SDL_SCANCODE_AUDIOSTOP) || (k.sym == SDLK_AUDIOSTOP)) {
    return "<AudioStop>";
  }

  if ((k.scancode == SDL_SCANCODE_B) || (k.sym == SDLK_b)) {
    return "b";
  }

  if ((k.scancode == SDL_SCANCODE_BACKSLASH) || (k.sym == SDLK_BACKSLASH)) {
    return "\"";
  }

  if ((k.scancode == SDL_SCANCODE_BACKSPACE) || (k.sym == SDLK_BACKSPACE)) {
    return "<Backspace>";
  }

  if ((k.scancode == SDL_SCANCODE_BRIGHTNESSDOWN) || (k.sym == SDLK_BRIGHTNESSDOWN)) {
    return "<BrightnessDown>";
  }

  if ((k.scancode == SDL_SCANCODE_BRIGHTNESSUP) || (k.sym == SDLK_BRIGHTNESSUP)) {
    return "<BrightnessUp>";
  }

  if ((k.scancode == SDL_SCANCODE_C) || (k.sym == SDLK_c)) {
    return "c";
  }

  if ((k.scancode == SDL_SCANCODE_CALCULATOR) || (k.sym == SDLK_CALCULATOR)) {
    return "<Calculator>";
  }

  if ((k.scancode == SDL_SCANCODE_CANCEL) || (k.sym == SDLK_CANCEL)) {
    return "<Cancel>";
  }

  if ((k.scancode == SDL_SCANCODE_CAPSLOCK) || (k.sym == SDLK_CAPSLOCK)) {
    return "<CapsLock>";
  }

  if ((k.scancode == SDL_SCANCODE_CLEAR) || (k.sym == SDLK_CLEAR)) {
    return "<Clear>";
  }

  if ((k.scancode == SDL_SCANCODE_CLEARAGAIN) || (k.sym == SDLK_CLEARAGAIN)) {
    return "<Clear / Again>";
  }

  if ((k.scancode == SDL_SCANCODE_COMMA) || (k.sym == SDLK_COMMA)) {
    return ",";
  }

  if ((k.scancode == SDL_SCANCODE_COMPUTER) || (k.sym == SDLK_COMPUTER)) {
    return "<Computer>";
  }

  if ((k.scancode == SDL_SCANCODE_COPY) || (k.sym == SDLK_COPY)) {
    return "<Copy>";
  }

  if ((k.scancode == SDL_SCANCODE_CRSEL) || (k.sym == SDLK_CRSEL)) {
    return "<CrSel>";
  }

  if ((k.scancode == SDL_SCANCODE_CURRENCYSUBUNIT) || (k.sym == SDLK_CURRENCYSUBUNIT)) {
    return "<CurrencySubUnit>";
  }

  if ((k.scancode == SDL_SCANCODE_CURRENCYUNIT) || (k.sym == SDLK_CURRENCYUNIT)) {
    return "<CurrencyUnit>";
  }

  if ((k.scancode == SDL_SCANCODE_CUT) || (k.sym == SDLK_CUT)) {
    return "<Cut>";
  }

  if ((k.scancode == SDL_SCANCODE_D) || (k.sym == SDLK_d)) {
    return "d";
  }

  if ((k.scancode == SDL_SCANCODE_DECIMALSEPARATOR) || (k.sym == SDLK_DECIMALSEPARATOR)) {
    return "<DecimalSeparator>";
  }

  if ((k.scancode == SDL_SCANCODE_DELETE) || (k.sym == SDLK_DELETE)) {
    return "<Delete>";
  }

  if ((k.scancode == SDL_SCANCODE_DISPLAYSWITCH) || (k.sym == SDLK_DISPLAYSWITCH)) {
    return "<DisplaySwitch>";
  }

  if ((k.scancode == SDL_SCANCODE_DOWN) || (k.sym == SDLK_DOWN)) {
    return "<Down>";
  }

  if ((k.scancode == SDL_SCANCODE_E) || (k.sym == SDLK_e)) {
    return "e";
  }

  if ((k.scancode == SDL_SCANCODE_EJECT) || (k.sym == SDLK_EJECT)) {
    return "<Eject>";
  }

  if ((k.scancode == SDL_SCANCODE_END) || (k.sym == SDLK_END)) {
    return "<End>";
  }

  if ((k.scancode == SDL_SCANCODE_EQUALS) || (k.sym == SDLK_EQUALS)) {
    return "=";
  }

  if ((k.scancode == SDL_SCANCODE_ESCAPE) || (k.sym == SDLK_ESCAPE)) {
    return "<Escape>";
  }

  if ((k.scancode == SDL_SCANCODE_EXECUTE) || (k.sym == SDLK_EXECUTE)) {
    return "<Execute>";
  }

  if ((k.scancode == SDL_SCANCODE_EXSEL) || (k.sym == SDLK_EXSEL)) {
    return "<ExSel>";
  }

  if ((k.scancode == SDL_SCANCODE_F) || (k.sym == SDLK_f)) {
    return "f";
  }

  if ((k.scancode == SDL_SCANCODE_F1) || (k.sym == SDLK_F1)) {
    return "<F1>";
  }

  if ((k.scancode == SDL_SCANCODE_F10) || (k.sym == SDLK_F10)) {
    return "<F10>";
  }

  if ((k.scancode == SDL_SCANCODE_F11) || (k.sym == SDLK_F11)) {
    return "<F11>";
  }

  if ((k.scancode == SDL_SCANCODE_F12) || (k.sym == SDLK_F12)) {
    return "<F12>";
  }

  if ((k.scancode == SDL_SCANCODE_F13) || (k.sym == SDLK_F13)) {
    return "<F13>";
  }

  if ((k.scancode == SDL_SCANCODE_F14) || (k.sym == SDLK_F14)) {
    return "<F14>";
  }

  if ((k.scancode == SDL_SCANCODE_F15) || (k.sym == SDLK_F15)) {
    return "<F15>";
  }

  if ((k.scancode == SDL_SCANCODE_F16) || (k.sym == SDLK_F16)) {
    return "<F16>";
  }

  if ((k.scancode == SDL_SCANCODE_F17) || (k.sym == SDLK_F17)) {
    return "<F17>";
  }

  if ((k.scancode == SDL_SCANCODE_F18) || (k.sym == SDLK_F18)) {
    return "<F18>";
  }

  if ((k.scancode == SDL_SCANCODE_F19) || (k.sym == SDLK_F19)) {
    return "<F19>";
  }

  if ((k.scancode == SDL_SCANCODE_F2) || (k.sym == SDLK_F2)) {
    return "<F2>";
  }

  if ((k.scancode == SDL_SCANCODE_F20) || (k.sym == SDLK_F20)) {
    return "<F20>";
  }

  if ((k.scancode == SDL_SCANCODE_F21) || (k.sym == SDLK_F21)) {
    return "<F21>";
  }

  if ((k.scancode == SDL_SCANCODE_F22) || (k.sym == SDLK_F22)) {
    return "<F22>";
  }

  if ((k.scancode == SDL_SCANCODE_F23) || (k.sym == SDLK_F23)) {
    return "<F23>";
  }

  if ((k.scancode == SDL_SCANCODE_F24) || (k.sym == SDLK_F24)) {
    return "<F24>";
  }

  if ((k.scancode == SDL_SCANCODE_F3) || (k.sym == SDLK_F3)) {
    return "<F3>";
  }

  if ((k.scancode == SDL_SCANCODE_F4) || (k.sym == SDLK_F4)) {
    return "<F4>";
  }

  if ((k.scancode == SDL_SCANCODE_F5) || (k.sym == SDLK_F5)) {
    return "<F5>";
  }

  if ((k.scancode == SDL_SCANCODE_F6) || (k.sym == SDLK_F6)) {
    return "<F6>";
  }

  if ((k.scancode == SDL_SCANCODE_F7) || (k.sym == SDLK_F7)) {
    return "<F7>";
  }

  if ((k.scancode == SDL_SCANCODE_F8) || (k.sym == SDLK_F8)) {
    return "<F8>";
  }

  if ((k.scancode == SDL_SCANCODE_F9) || (k.sym == SDLK_F9)) {
    return "<F9>";
  }

  if ((k.scancode == SDL_SCANCODE_FIND) || (k.sym == SDLK_FIND)) {
    return "<Find>";
  }

  if ((k.scancode == SDL_SCANCODE_G) || (k.sym == SDLK_g)) {
    return "g";
  }

  if ((k.scancode == SDL_SCANCODE_GRAVE) || (k.sym == SDLK_BACKQUOTE)) {
    return "`";
  }

  if ((k.scancode == SDL_SCANCODE_H) || (k.sym == SDLK_h)) {
    return "h";
  }

  if ((k.scancode == SDL_SCANCODE_HELP) || (k.sym == SDLK_HELP)) {
    return "<Help>";
  }

  if ((k.scancode == SDL_SCANCODE_HOME) || (k.sym == SDLK_HOME)) {
    return "<Home>";
  }

  if ((k.scancode == SDL_SCANCODE_I) || (k.sym == SDLK_i)) {
    return "i";
  }

  if ((k.scancode == SDL_SCANCODE_INSERT) || (k.sym == SDLK_INSERT)) {
    return "<Insert>";
  }

  if ((k.scancode == SDL_SCANCODE_J) || (k.sym == SDLK_j)) {
    return "j";
  }

  if ((k.scancode == SDL_SCANCODE_K) || (k.sym == SDLK_k)) {
    return "k";
  }

  if ((k.scancode == SDL_SCANCODE_KBDILLUMDOWN) || (k.sym == SDLK_KBDILLUMDOWN)) {
    return "<KBDIllumDown>";
  }

  if ((k.scancode == SDL_SCANCODE_KBDILLUMTOGGLE) || (k.sym == SDLK_KBDILLUMTOGGLE)) {
    return "<KBDIllumToggle>";
  }

  if ((k.scancode == SDL_SCANCODE_KBDILLUMUP) || (k.sym == SDLK_KBDILLUMUP)) {
    return "<KBDIllumUp>";
  }

  if ((k.scancode == SDL_SCANCODE_KP_0) || (k.sym == SDLK_KP_0)) {
    return "<KP 0>";
  }

  if ((k.scancode == SDL_SCANCODE_KP_00) || (k.sym == SDLK_KP_00)) {
    return "<KP 00>";
  }

  if ((k.scancode == SDL_SCANCODE_KP_000) || (k.sym == SDLK_KP_000)) {
    return "<KP 000>";
  }

  if ((k.scancode == SDL_SCANCODE_KP_1) || (k.sym == SDLK_KP_1)) {
    return "<KP 1>";
  }

  if ((k.scancode == SDL_SCANCODE_KP_2) || (k.sym == SDLK_KP_2)) {
    return "<KP 2>";
  }

  if ((k.scancode == SDL_SCANCODE_KP_3) || (k.sym == SDLK_KP_3)) {
    return "<KP 3>";
  }

  if ((k.scancode == SDL_SCANCODE_KP_4) || (k.sym == SDLK_KP_4)) {
    return "<KP 4>";
  }

  if ((k.scancode == SDL_SCANCODE_KP_5) || (k.sym == SDLK_KP_5)) {
    return "<KP 5>";
  }

  if ((k.scancode == SDL_SCANCODE_KP_6) || (k.sym == SDLK_KP_6)) {
    return "<KP 6>";
  }

  if ((k.scancode == SDL_SCANCODE_KP_7) || (k.sym == SDLK_KP_7)) {
    return "<KP 7>";
  }

  if ((k.scancode == SDL_SCANCODE_KP_8) || (k.sym == SDLK_KP_8)) {
    return "<KP 8>";
  }

  if ((k.scancode == SDL_SCANCODE_KP_9) || (k.sym == SDLK_KP_9)) {
    return "<KP 9>";
  }

  if ((k.scancode == SDL_SCANCODE_KP_A) || (k.sym == SDLK_KP_A)) {
    return "<KP A>";
  }

  if ((k.scancode == SDL_SCANCODE_KP_AMPERSAND) || (k.sym == SDLK_KP_AMPERSAND)) {
    return "<KP &>";
  }

  if ((k.scancode == SDL_SCANCODE_KP_AT) || (k.sym == SDLK_KP_AT)) {
    return "<KP @>";
  }

  if ((k.scancode == SDL_SCANCODE_KP_B) || (k.sym == SDLK_KP_B)) {
    return "<KP B>";
  }

  if ((k.scancode == SDL_SCANCODE_KP_BACKSPACE) || (k.sym == SDLK_KP_BACKSPACE)) {
    return "<KP Backspace>";
  }

  if ((k.scancode == SDL_SCANCODE_KP_BINARY) || (k.sym == SDLK_KP_BINARY)) {
    return "<KP Binary>";
  }

  if ((k.scancode == SDL_SCANCODE_KP_C) || (k.sym == SDLK_KP_C)) {
    return "<KP C>";
  }

  if ((k.scancode == SDL_SCANCODE_KP_CLEAR) || (k.sym == SDLK_KP_CLEAR)) {
    return "<KP Clear>";
  }

  if ((k.scancode == SDL_SCANCODE_KP_COLON) || (k.sym == SDLK_KP_COLON)) {
    return "<KP :>";
  }

  if ((k.scancode == SDL_SCANCODE_KP_COMMA) || (k.sym == SDLK_KP_COMMA)) {
    return "<KP ,>";
  }

  if ((k.scancode == SDL_SCANCODE_KP_D) || (k.sym == SDLK_KP_D)) {
    return "<KP D>";
  }

  if ((k.scancode == SDL_SCANCODE_KP_DBLAMPERSAND) || (k.sym == SDLK_KP_DBLAMPERSAND)) {
    return "<KP &&>";
  }

  if ((k.scancode == SDL_SCANCODE_KP_DECIMAL) || (k.sym == SDLK_KP_DECIMAL)) {
    return "<KP Decimal>";
  }

  if ((k.scancode == SDL_SCANCODE_KP_DIVIDE) || (k.sym == SDLK_KP_DIVIDE)) {
    return "<KP />";
  }

  if ((k.scancode == SDL_SCANCODE_KP_E) || (k.sym == SDLK_KP_E)) {
    return "<KP E>";
  }

  if ((k.scancode == SDL_SCANCODE_KP_ENTER) || (k.sym == SDLK_KP_ENTER)) {
    return "<KP Enter>";
  }

  if ((k.scancode == SDL_SCANCODE_KP_EQUALS) || (k.sym == SDLK_KP_EQUALS)) {
    return "<KP =>";
  }

  if ((k.scancode == SDL_SCANCODE_KP_EQUALSAS400) || (k.sym == SDLK_KP_EQUALSAS400)) {
    return "<KP = (AS400)>";
  }

  if ((k.scancode == SDL_SCANCODE_KP_EXCLAM) || (k.sym == SDLK_KP_EXCLAM)) {
    return "<KP !>";
  }

  if ((k.scancode == SDL_SCANCODE_KP_F) || (k.sym == SDLK_KP_F)) {
    return "<KP F>";
  }

  if ((k.scancode == SDL_SCANCODE_KP_GREATER) || (k.sym == SDLK_KP_GREATER)) {
    return "<KP >>";
  }

  if ((k.scancode == SDL_SCANCODE_KP_HASH) || (k.sym == SDLK_KP_HASH)) {
    return "<KP #>";
  }

  if ((k.scancode == SDL_SCANCODE_KP_HEXADECIMAL) || (k.sym == SDLK_KP_HEXADECIMAL)) {
    return "<KP Hexadecimal>";
  }

  if ((k.scancode == SDL_SCANCODE_KP_LEFTBRACE) || (k.sym == SDLK_KP_LEFTBRACE)) {
    return "<KP {>";
  }

  if ((k.scancode == SDL_SCANCODE_KP_LEFTPAREN) || (k.sym == SDLK_KP_LEFTPAREN)) {
    return "<KP (>";
  }

  if ((k.scancode == SDL_SCANCODE_KP_LESS) || (k.sym == SDLK_KP_LESS)) {
    return "<KP <>";
  }

  if ((k.scancode == SDL_SCANCODE_KP_MEMADD) || (k.sym == SDLK_KP_MEMADD)) {
    return "<KP MemAdd>";
  }

  if ((k.scancode == SDL_SCANCODE_KP_MEMCLEAR) || (k.sym == SDLK_KP_MEMCLEAR)) {
    return "<KP MemClear>";
  }

  if ((k.scancode == SDL_SCANCODE_KP_MEMDIVIDE) || (k.sym == SDLK_KP_MEMDIVIDE)) {
    return "<KP MemDivide>";
  }

  if ((k.scancode == SDL_SCANCODE_KP_MEMMULTIPLY) || (k.sym == SDLK_KP_MEMMULTIPLY)) {
    return "<KP MemMultiply>";
  }

  if ((k.scancode == SDL_SCANCODE_KP_MEMRECALL) || (k.sym == SDLK_KP_MEMRECALL)) {
    return "<KP MemRecall>";
  }

  if ((k.scancode == SDL_SCANCODE_KP_MEMSTORE) || (k.sym == SDLK_KP_MEMSTORE)) {
    return "<KP MemStore>";
  }

  if ((k.scancode == SDL_SCANCODE_KP_MEMSUBTRACT) || (k.sym == SDLK_KP_MEMSUBTRACT)) {
    return "<KP MemSubtract>";
  }

  if ((k.scancode == SDL_SCANCODE_KP_MINUS) || (k.sym == SDLK_KP_MINUS)) {
    return "<KP ->";
  }

  if ((k.scancode == SDL_SCANCODE_KP_MULTIPLY) || (k.sym == SDLK_KP_MULTIPLY)) {
    return "<KP *>";
  }

  if ((k.scancode == SDL_SCANCODE_KP_OCTAL) || (k.sym == SDLK_KP_OCTAL)) {
    return "<KP Octal>";
  }

  if ((k.scancode == SDL_SCANCODE_KP_PERCENT) || (k.sym == SDLK_KP_PERCENT)) {
    return "<KP %>";
  }

  if ((k.scancode == SDL_SCANCODE_KP_PERIOD) || (k.sym == SDLK_KP_PERIOD)) {
    return "<KP .>";
  }

  if ((k.scancode == SDL_SCANCODE_KP_PLUS) || (k.sym == SDLK_KP_PLUS)) {
    return "<KP +>";
  }

  if ((k.scancode == SDL_SCANCODE_KP_PLUSMINUS) || (k.sym == SDLK_KP_PLUSMINUS)) {
    return "<KP +/->";
  }

  if ((k.scancode == SDL_SCANCODE_KP_POWER) || (k.sym == SDLK_KP_POWER)) {
    return "<KP ^>";
  }

  if ((k.scancode == SDL_SCANCODE_KP_RIGHTBRACE) || (k.sym == SDLK_KP_RIGHTBRACE)) {
    return "<KP }>";
  }

  if ((k.scancode == SDL_SCANCODE_KP_RIGHTPAREN) || (k.sym == SDLK_KP_RIGHTPAREN)) {
    return "<KP )>";
  }

  if ((k.scancode == SDL_SCANCODE_KP_SPACE) || (k.sym == SDLK_KP_SPACE)) {
    return "<KP Space>";
  }

  if ((k.scancode == SDL_SCANCODE_KP_TAB) || (k.sym == SDLK_KP_TAB)) {
    return "<KP Tab>";
  }

  if ((k.scancode == SDL_SCANCODE_KP_VERTICALBAR) || (k.sym == SDLK_KP_VERTICALBAR)) {
    return "<KP |>";
  }

  if ((k.scancode == SDL_SCANCODE_KP_XOR) || (k.sym == SDLK_KP_XOR)) {
    return "<KP XOR>";
  }

  if ((k.scancode == SDL_SCANCODE_L) || (k.sym == SDLK_l)) {
    return "l";
  }

  if ((k.scancode == SDL_SCANCODE_LEFTBRACKET) || (k.sym == SDLK_LEFTBRACKET)) {
    return "[";
  }

  if ((k.scancode == SDL_SCANCODE_M) || (k.sym == SDLK_m)) {
    return "m";
  }

  if ((k.scancode == SDL_SCANCODE_MAIL) || (k.sym == SDLK_MAIL)) {
    return "<Mail>";
  }

  if ((k.scancode == SDL_SCANCODE_MEDIASELECT) || (k.sym == SDLK_MEDIASELECT)) {
    return "<MediaSelect>";
  }

  if ((k.scancode == SDL_SCANCODE_MENU) || (k.sym == SDLK_MENU)) {
    return "<Menu>";
  }

  if ((k.scancode == SDL_SCANCODE_MINUS) || (k.sym == SDLK_MINUS)) {
    return "-";
  }

  if ((k.scancode == SDL_SCANCODE_MODE) || (k.sym == SDLK_MODE)) {
    return "<Mode>";
  }

  if ((k.scancode == SDL_SCANCODE_MUTE) || (k.sym == SDLK_MUTE)) {
    return "<Mute>";
  }

  if ((k.scancode == SDL_SCANCODE_N) || (k.sym == SDLK_n)) {
    return "n";
  }

  if ((k.scancode == SDL_SCANCODE_NUMLOCKCLEAR) || (k.sym == SDLK_NUMLOCKCLEAR)) {
    return "<Numlock>";
  }

  if ((k.scancode == SDL_SCANCODE_O) || (k.sym == SDLK_o)) {
    return "o";
  }

  if ((k.scancode == SDL_SCANCODE_OPER) || (k.sym == SDLK_OPER)) {
    return "<Oper>";
  }

  if ((k.scancode == SDL_SCANCODE_OUT) || (k.sym == SDLK_OUT)) {
    return "<Out>";
  }

  if ((k.scancode == SDL_SCANCODE_P) || (k.sym == SDLK_p)) {
    return "p";
  }

  if ((k.scancode == SDL_SCANCODE_PAGEDOWN) || (k.sym == SDLK_PAGEDOWN)) {
    return "<PageDown>";
  }

  if ((k.scancode == SDL_SCANCODE_PAGEUP) || (k.sym == SDLK_PAGEUP)) {
    return "<PageUp>";
  }

  if ((k.scancode == SDL_SCANCODE_PASTE) || (k.sym == SDLK_PASTE)) {
    return "<Paste>";
  }

  if ((k.scancode == SDL_SCANCODE_PAUSE) || (k.sym == SDLK_PAUSE)) {
    return "<Pause>";
  }

  if ((k.scancode == SDL_SCANCODE_PERIOD) || (k.sym == SDLK_PERIOD)) {
    return ".";
  }

  if ((k.scancode == SDL_SCANCODE_POWER) || (k.sym == SDLK_POWER)) {
    return "<Power>";
  }

  if ((k.scancode == SDL_SCANCODE_PRINTSCREEN) || (k.sym == SDLK_PRINTSCREEN)) {
    return "<PrintScreen>";
  }

  if ((k.scancode == SDL_SCANCODE_PRIOR) || (k.sym == SDLK_PRIOR)) {
    return "<Prior>";
  }

  if ((k.scancode == SDL_SCANCODE_Q) || (k.sym == SDLK_q)) {
    return "q";
  }

  if ((k.scancode == SDL_SCANCODE_R) || (k.sym == SDLK_r)) {
    return "r";
  }

  if ((k.scancode == SDL_SCANCODE_RETURN) || (k.sym == SDLK_RETURN)) {
    return "<Return>";
  }

  if ((k.scancode == SDL_SCANCODE_RETURN2) || (k.sym == SDLK_RETURN2)) {
    return "<Return>";
  }

  if ((k.scancode == SDL_SCANCODE_RIGHTBRACKET) || (k.sym == SDLK_RIGHTBRACKET)) {
    return "]";
  }

  if ((k.scancode == SDL_SCANCODE_S) || (k.sym == SDLK_s)) {
    return "s";
  }

  if ((k.scancode == SDL_SCANCODE_SCROLLLOCK) || (k.sym == SDLK_SCROLLLOCK)) {
    return "<ScrollLock>";
  }

  if ((k.scancode == SDL_SCANCODE_SELECT) || (k.sym == SDLK_SELECT)) {
    return "<Select>";
  }

  if ((k.scancode == SDL_SCANCODE_SEMICOLON) || (k.sym == SDLK_SEMICOLON)) {
    return ";";
  }

  if ((k.scancode == SDL_SCANCODE_SEPARATOR) || (k.sym == SDLK_SEPARATOR)) {
    return "<Separator>";
  }

  if ((k.scancode == SDL_SCANCODE_SLASH) || (k.sym == SDLK_SLASH)) {
    return "/";
  }

  if ((k.scancode == SDL_SCANCODE_SLEEP) || (k.sym == SDLK_SLEEP)) {
    return "<Sleep>";
  }

  if ((k.scancode == SDL_SCANCODE_SPACE) || (k.sym == SDLK_SPACE)) {
    return "<Space>";
  }

  if ((k.scancode == SDL_SCANCODE_STOP) || (k.sym == SDLK_STOP)) {
    return "<Stop>";
  }

  if ((k.scancode == SDL_SCANCODE_SYSREQ) || (k.sym == SDLK_SYSREQ)) {
    return "<SysReq>";
  }

  if ((k.scancode == SDL_SCANCODE_T) || (k.sym == SDLK_t)) {
    return "t";
  }

  if ((k.scancode == SDL_SCANCODE_TAB) || (k.sym == SDLK_TAB)) {
    return "<TAB>";
  }

  if ((k.scancode == SDL_SCANCODE_THOUSANDSSEPARATOR) || (k.sym == SDLK_THOUSANDSSEPARATOR)) {
    return "<ThousandsSeparator>";
  }

  if ((k.scancode == SDL_SCANCODE_U) || (k.sym == SDLK_u)) {
    return "u";
  }

  if ((k.scancode == SDL_SCANCODE_UNDO) || (k.sym == SDLK_UNDO)) {
    return "<Undo>";
  }

  if ((k.scancode == SDL_SCANCODE_UP) || (k.sym == SDLK_UP)) {
    return "<Up>";
  }

  if ((k.scancode == SDL_SCANCODE_V) || (k.sym == SDLK_v)) {
    return "v";
  }

  if ((k.scancode == SDL_SCANCODE_VOLUMEDOWN) || (k.sym == SDLK_VOLUMEDOWN)) {
    return "<VolumeDown>";
  }

  if ((k.scancode == SDL_SCANCODE_VOLUMEUP) || (k.sym == SDLK_VOLUMEUP)) {
    return "<VolumeUp>";
  }

  if ((k.scancode == SDL_SCANCODE_W) || (k.sym == SDLK_w)) {
    return "w";
  }

  if ((k.scancode == SDL_SCANCODE_WWW) || (k.sym == SDLK_WWW)) {
    return "<WWW>";
  }

  if ((k.scancode == SDL_SCANCODE_X) || (k.sym == SDLK_x)) {
    return "x";
  }

  if ((k.scancode == SDL_SCANCODE_Y) || (k.sym == SDLK_y)) {
    return "y";
  }

  if ((k.scancode == SDL_SCANCODE_Z) || (k.sym == SDLK_z)) {
    return "z";
  }

  return "";
}

std::string to_string(const SDL_Keysym &k)
{
  std::string out;

  if (k.mod == KMOD_SHIFT) {
    out += "<Shift> ";
  } else {
    if (k.mod & KMOD_LSHIFT) {
      out += "<L-shift> ";
    }
    if (k.mod & KMOD_RSHIFT) {
      out += "<R-shift> ";
    }
  }

  if (k.mod == KMOD_CTRL) {
    out += "<Ctrl> ";
  } else {
    if (k.mod & KMOD_LCTRL) {
      out += "<L-ctrl> ";
    }
    if (k.mod & KMOD_RCTRL) {
      out += "<R-ctrl> ";
    }
  }

  if (k.mod == KMOD_ALT) {
    out += "<Alt> ";
  } else {
    if (k.mod & KMOD_LALT) {
      out += "<L-alt> ";
    }
    if (k.mod & KMOD_RALT) {
      out += "<R-alt> ";
    }
  }

  if (k.mod == KMOD_GUI) {
    out += "<Gui> ";
  } else {
    if (k.mod & KMOD_LGUI) {
      out += "<L-gui> ";
    }
    if (k.mod & KMOD_RGUI) {
      out += "<R-gui> ";
    }
  }

  if (k.mod == KMOD_NUM) {
    out += "<Numpad> ";
  }
  if (k.mod == KMOD_CAPS) {
    out += "<Caps> ";
  }

  if ((k.scancode == SDL_SCANCODE_LALT) || (k.sym == SDLK_LALT)) {
    out = "<L-Alt>";
  }

  if ((k.scancode == SDL_SCANCODE_LCTRL) || (k.sym == SDLK_LCTRL)) {
    out = "<L-Ctrl>";
  }

  if ((k.scancode == SDL_SCANCODE_LEFT) || (k.sym == SDLK_LEFT)) {
    out = "<Left>";
  }

  if ((k.scancode == SDL_SCANCODE_LGUI) || (k.sym == SDLK_LGUI)) {
    out = "<L-GUI>";
  }

  if ((k.scancode == SDL_SCANCODE_LSHIFT) || (k.sym == SDLK_LSHIFT)) {
    out = "<L-Shift>";
  }

  if ((k.scancode == SDL_SCANCODE_RALT) || (k.sym == SDLK_RALT)) {
    out = "<R-Alt>";
  }

  if ((k.scancode == SDL_SCANCODE_RCTRL) || (k.sym == SDLK_RCTRL)) {
    out = "<R-Ctrl>";
  }

  if ((k.scancode == SDL_SCANCODE_RGUI) || (k.sym == SDLK_RGUI)) {
    out = "<R-GUI>";
  }

  if ((k.scancode == SDL_SCANCODE_RIGHT) || (k.sym == SDLK_RIGHT)) {
    out = "<Right>";
  }

  if ((k.scancode == SDL_SCANCODE_RSHIFT) || (k.sym == SDLK_RSHIFT)) {
    out = "<R-Shift>";
  }

  return out + to_string_ignoring_mods(k);
}

SDL_Keysym sdlk_normalize(SDL_Keysym k_in)
{
  SDL_Keysym k = k_in;

  if ((k.mod & KMOD_LSHIFT) || (k.mod & KMOD_RSHIFT)) {
    k.mod &= ~KMOD_SHIFT;
    switch (k.sym) {
      case SDLK_COMMA :
        // <
        k.sym = SDLK_LESS;
        return k;
      case SDLK_MINUS :
        // _
        k.sym = SDLK_MINUS;
        return k;
      case SDLK_PERIOD :
        // >
        k.sym = SDLK_GREATER;
        return k;
      case SDLK_SLASH :
        // ?
        k.sym = SDLK_QUESTION;
        return k;
      case SDLK_EQUALS :
        // +
        k.sym = SDLK_PLUS;
        return k;
      case SDLK_0 :
        // )
        k.sym = SDLK_RIGHTPAREN;
        return k;
      case SDLK_1 :
        // !
        k.sym = SDLK_EXCLAIM;
        return k;
      case SDLK_2 :
        // @
        k.sym = SDLK_AT;
        return k;
      case SDLK_3 :
        // #
        k.sym = SDLK_HASH;
        return k;
      case SDLK_4 :
        // $
        k.sym = SDLK_DOLLAR;
        return k;
      case SDLK_5 :
        // %
        k.sym = SDLK_PERCENT;
        return k;
      case SDLK_6 :
        // ^
        k.sym = SDLK_CARET;
        return k;
      case SDLK_7 :
        // &
        k.sym = SDLK_AMPERSAND;
        return k;
      case SDLK_8 :
        // *
        k.sym = SDLK_ASTERISK;
        return k;
      case SDLK_9 :
        // (
        k.sym = SDLK_LEFTPAREN;
        return k;
      case SDLK_SEMICOLON :
        // :
        k.sym = SDLK_COLON;
        return k;
      case SDLK_LEFTBRACKET :
        // {
        k.sym = SDLK_LEFTBRACKET;
        return k;
      case SDLK_BACKSLASH :
        // |
        k.sym = SDLK_KP_VERTICALBAR;
        return k;
      case SDLK_RIGHTBRACKET :
        // }
        k.sym = SDLK_RIGHTBRACKET;
        return k;
      case SDLK_HASH :
        // ~
        //
        // Not sure about this one for tilde in US and UK keyboards
        //
        k.sym = SDLK_BACKQUOTE;
        return k;
    }
  }
  return k_in;
}

bool sdlk_eq(const SDL_Keysym &a, const SDL_Keysym &b)
{
  auto k1 = sdlk_normalize(a);
  auto k2 = sdlk_normalize(b);

  if (0) {
    fprintf(stderr, "ZZZ %s %s %d A [%s] B [%s]\n", __FILE__, __FUNCTION__, __LINE__, to_string(a).c_str(),
            to_string(b).c_str());
  }

  //
  // So either shift key works
  //
  if (k1.mod & KMOD_SHIFT)
    k1.mod |= KMOD_SHIFT;
  if (k2.mod & KMOD_SHIFT)
    k2.mod |= KMOD_SHIFT;

  if (k1.mod & KMOD_CTRL)
    k1.mod |= KMOD_CTRL;
  if (k2.mod & KMOD_CTRL)
    k2.mod |= KMOD_CTRL;

  //
  // The chromebook duet reports all keys as num lock on. I'm not sure
  // if I should generally ignore this or now.
  //
  k1.mod &= ~KMOD_NUM;
  k2.mod &= ~KMOD_NUM;

  return (k1.sym == k2.sym) && (k1.mod == k2.mod);
}

bool sdlk_eq(const SDL_Scancode s, const SDL_Keysym &k)
{
  if ((k.scancode == s) || ((s == SDL_SCANCODE_0) && (k.sym == SDLK_0))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_1) && (k.sym == SDLK_1))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_2) && (k.sym == SDLK_2))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_3) && (k.sym == SDLK_3))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_4) && (k.sym == SDLK_4))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_5) && (k.sym == SDLK_5))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_6) && (k.sym == SDLK_6))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_7) && (k.sym == SDLK_7))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_8) && (k.sym == SDLK_8))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_9) && (k.sym == SDLK_9))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_A) && (k.sym == SDLK_a))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_AC_BACK) && (k.sym == SDLK_AC_BACK))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_AC_BOOKMARKS) && (k.sym == SDLK_AC_BOOKMARKS))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_AC_FORWARD) && (k.sym == SDLK_AC_FORWARD))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_AC_HOME) && (k.sym == SDLK_AC_HOME))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_AC_REFRESH) && (k.sym == SDLK_AC_REFRESH))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_AC_SEARCH) && (k.sym == SDLK_AC_SEARCH))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_AC_STOP) && (k.sym == SDLK_AC_STOP))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_AGAIN) && (k.sym == SDLK_AGAIN))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_ALTERASE) && (k.sym == SDLK_ALTERASE))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_APOSTROPHE) && (k.sym == SDLK_QUOTE))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_APPLICATION) && (k.sym == SDLK_APPLICATION))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_AUDIOMUTE) && (k.sym == SDLK_AUDIOMUTE))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_AUDIONEXT) && (k.sym == SDLK_AUDIONEXT))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_AUDIOPLAY) && (k.sym == SDLK_AUDIOPLAY))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_AUDIOPREV) && (k.sym == SDLK_AUDIOPREV))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_AUDIOSTOP) && (k.sym == SDLK_AUDIOSTOP))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_B) && (k.sym == SDLK_b))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_BACKSLASH) && (k.sym == SDLK_BACKSLASH))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_BACKSPACE) && (k.sym == SDLK_BACKSPACE))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_BRIGHTNESSDOWN) && (k.sym == SDLK_BRIGHTNESSDOWN))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_BRIGHTNESSUP) && (k.sym == SDLK_BRIGHTNESSUP))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_C) && (k.sym == SDLK_c))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_CALCULATOR) && (k.sym == SDLK_CALCULATOR))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_CANCEL) && (k.sym == SDLK_CANCEL))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_CAPSLOCK) && (k.sym == SDLK_CAPSLOCK))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_CLEAR) && (k.sym == SDLK_CLEAR))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_CLEARAGAIN) && (k.sym == SDLK_CLEARAGAIN))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_COMMA) && (k.sym == SDLK_COMMA))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_COMPUTER) && (k.sym == SDLK_COMPUTER))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_COPY) && (k.sym == SDLK_COPY))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_CRSEL) && (k.sym == SDLK_CRSEL))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_CURRENCYSUBUNIT) && (k.sym == SDLK_CURRENCYSUBUNIT))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_CURRENCYUNIT) && (k.sym == SDLK_CURRENCYUNIT))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_CUT) && (k.sym == SDLK_CUT))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_D) && (k.sym == SDLK_d))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_DECIMALSEPARATOR) && (k.sym == SDLK_DECIMALSEPARATOR))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_DELETE) && (k.sym == SDLK_DELETE))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_DISPLAYSWITCH) && (k.sym == SDLK_DISPLAYSWITCH))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_DOWN) && (k.sym == SDLK_DOWN))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_E) && (k.sym == SDLK_e))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_EJECT) && (k.sym == SDLK_EJECT))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_END) && (k.sym == SDLK_END))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_EQUALS) && (k.sym == SDLK_EQUALS))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_ESCAPE) && (k.sym == SDLK_ESCAPE))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_EXECUTE) && (k.sym == SDLK_EXECUTE))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_EXSEL) && (k.sym == SDLK_EXSEL))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_F) && (k.sym == SDLK_f))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_F1) && (k.sym == SDLK_F1))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_F10) && (k.sym == SDLK_F10))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_F11) && (k.sym == SDLK_F11))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_F12) && (k.sym == SDLK_F12))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_F13) && (k.sym == SDLK_F13))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_F14) && (k.sym == SDLK_F14))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_F15) && (k.sym == SDLK_F15))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_F16) && (k.sym == SDLK_F16))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_F17) && (k.sym == SDLK_F17))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_F18) && (k.sym == SDLK_F18))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_F19) && (k.sym == SDLK_F19))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_F2) && (k.sym == SDLK_F2))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_F20) && (k.sym == SDLK_F20))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_F21) && (k.sym == SDLK_F21))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_F22) && (k.sym == SDLK_F22))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_F23) && (k.sym == SDLK_F23))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_F24) && (k.sym == SDLK_F24))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_F3) && (k.sym == SDLK_F3))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_F4) && (k.sym == SDLK_F4))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_F5) && (k.sym == SDLK_F5))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_F6) && (k.sym == SDLK_F6))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_F7) && (k.sym == SDLK_F7))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_F8) && (k.sym == SDLK_F8))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_F9) && (k.sym == SDLK_F9))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_FIND) && (k.sym == SDLK_FIND))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_G) && (k.sym == SDLK_g))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_GRAVE) && (k.sym == SDLK_BACKQUOTE))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_H) && (k.sym == SDLK_h))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_HELP) && (k.sym == SDLK_HELP))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_HOME) && (k.sym == SDLK_HOME))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_I) && (k.sym == SDLK_i))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_INSERT) && (k.sym == SDLK_INSERT))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_J) && (k.sym == SDLK_j))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_K) && (k.sym == SDLK_k))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_KBDILLUMDOWN) && (k.sym == SDLK_KBDILLUMDOWN))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_KBDILLUMTOGGLE) && (k.sym == SDLK_KBDILLUMTOGGLE))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_KBDILLUMUP) && (k.sym == SDLK_KBDILLUMUP))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_KP_0) && (k.sym == SDLK_KP_0))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_KP_00) && (k.sym == SDLK_KP_00))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_KP_000) && (k.sym == SDLK_KP_000))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_KP_1) && (k.sym == SDLK_KP_1))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_KP_2) && (k.sym == SDLK_KP_2))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_KP_3) && (k.sym == SDLK_KP_3))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_KP_4) && (k.sym == SDLK_KP_4))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_KP_5) && (k.sym == SDLK_KP_5))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_KP_6) && (k.sym == SDLK_KP_6))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_KP_7) && (k.sym == SDLK_KP_7))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_KP_8) && (k.sym == SDLK_KP_8))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_KP_9) && (k.sym == SDLK_KP_9))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_KP_A) && (k.sym == SDLK_KP_A))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_KP_AMPERSAND) && (k.sym == SDLK_KP_AMPERSAND))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_KP_AT) && (k.sym == SDLK_KP_AT))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_KP_B) && (k.sym == SDLK_KP_B))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_KP_BACKSPACE) && (k.sym == SDLK_KP_BACKSPACE))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_KP_BINARY) && (k.sym == SDLK_KP_BINARY))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_KP_C) && (k.sym == SDLK_KP_C))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_KP_CLEAR) && (k.sym == SDLK_KP_CLEAR))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_KP_COLON) && (k.sym == SDLK_KP_COLON))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_KP_COMMA) && (k.sym == SDLK_KP_COMMA))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_KP_D) && (k.sym == SDLK_KP_D))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_KP_DBLAMPERSAND) && (k.sym == SDLK_KP_DBLAMPERSAND))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_KP_DECIMAL) && (k.sym == SDLK_KP_DECIMAL))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_KP_DIVIDE) && (k.sym == SDLK_KP_DIVIDE))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_KP_E) && (k.sym == SDLK_KP_E))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_KP_ENTER) && (k.sym == SDLK_KP_ENTER))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_KP_EQUALS) && (k.sym == SDLK_KP_EQUALS))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_KP_EQUALSAS400) && (k.sym == SDLK_KP_EQUALSAS400))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_KP_EXCLAM) && (k.sym == SDLK_KP_EXCLAM))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_KP_F) && (k.sym == SDLK_KP_F))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_KP_GREATER) && (k.sym == SDLK_KP_GREATER))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_KP_HASH) && (k.sym == SDLK_KP_HASH))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_KP_HEXADECIMAL) && (k.sym == SDLK_KP_HEXADECIMAL))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_KP_LEFTBRACE) && (k.sym == SDLK_KP_LEFTBRACE))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_KP_LEFTPAREN) && (k.sym == SDLK_KP_LEFTPAREN))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_KP_LESS) && (k.sym == SDLK_KP_LESS))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_KP_MEMADD) && (k.sym == SDLK_KP_MEMADD))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_KP_MEMCLEAR) && (k.sym == SDLK_KP_MEMCLEAR))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_KP_MEMDIVIDE) && (k.sym == SDLK_KP_MEMDIVIDE))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_KP_MEMMULTIPLY) && (k.sym == SDLK_KP_MEMMULTIPLY))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_KP_MEMRECALL) && (k.sym == SDLK_KP_MEMRECALL))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_KP_MEMSTORE) && (k.sym == SDLK_KP_MEMSTORE))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_KP_MEMSUBTRACT) && (k.sym == SDLK_KP_MEMSUBTRACT))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_KP_MINUS) && (k.sym == SDLK_KP_MINUS))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_KP_MULTIPLY) && (k.sym == SDLK_KP_MULTIPLY))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_KP_OCTAL) && (k.sym == SDLK_KP_OCTAL))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_KP_PERCENT) && (k.sym == SDLK_KP_PERCENT))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_KP_PERIOD) && (k.sym == SDLK_KP_PERIOD))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_KP_PLUS) && (k.sym == SDLK_KP_PLUS))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_KP_PLUSMINUS) && (k.sym == SDLK_KP_PLUSMINUS))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_KP_POWER) && (k.sym == SDLK_KP_POWER))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_KP_RIGHTBRACE) && (k.sym == SDLK_KP_RIGHTBRACE))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_KP_RIGHTPAREN) && (k.sym == SDLK_KP_RIGHTPAREN))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_KP_SPACE) && (k.sym == SDLK_KP_SPACE))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_KP_TAB) && (k.sym == SDLK_KP_TAB))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_KP_VERTICALBAR) && (k.sym == SDLK_KP_VERTICALBAR))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_KP_XOR) && (k.sym == SDLK_KP_XOR))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_L) && (k.sym == SDLK_l))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_LALT) && (k.sym == SDLK_LALT))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_LCTRL) && (k.sym == SDLK_LCTRL))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_LEFT) && (k.sym == SDLK_LEFT))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_LEFTBRACKET) && (k.sym == SDLK_LEFTBRACKET))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_LGUI) && (k.sym == SDLK_LGUI))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_LSHIFT) && (k.sym == SDLK_LSHIFT))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_M) && (k.sym == SDLK_m))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_MAIL) && (k.sym == SDLK_MAIL))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_MEDIASELECT) && (k.sym == SDLK_MEDIASELECT))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_MENU) && (k.sym == SDLK_MENU))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_MINUS) && (k.sym == SDLK_MINUS))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_MODE) && (k.sym == SDLK_MODE))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_MUTE) && (k.sym == SDLK_MUTE))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_N) && (k.sym == SDLK_n))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_NUMLOCKCLEAR) && (k.sym == SDLK_NUMLOCKCLEAR))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_O) && (k.sym == SDLK_o))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_OPER) && (k.sym == SDLK_OPER))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_OUT) && (k.sym == SDLK_OUT))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_P) && (k.sym == SDLK_p))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_PAGEDOWN) && (k.sym == SDLK_PAGEDOWN))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_PAGEUP) && (k.sym == SDLK_PAGEUP))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_PASTE) && (k.sym == SDLK_PASTE))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_PAUSE) && (k.sym == SDLK_PAUSE))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_PERIOD) && (k.sym == SDLK_PERIOD))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_POWER) && (k.sym == SDLK_POWER))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_PRINTSCREEN) && (k.sym == SDLK_PRINTSCREEN))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_PRIOR) && (k.sym == SDLK_PRIOR))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_Q) && (k.sym == SDLK_q))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_R) && (k.sym == SDLK_r))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_RALT) && (k.sym == SDLK_RALT))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_RCTRL) && (k.sym == SDLK_RCTRL))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_RETURN) && (k.sym == SDLK_RETURN))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_RETURN2) && (k.sym == SDLK_RETURN2))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_RGUI) && (k.sym == SDLK_RGUI))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_RIGHT) && (k.sym == SDLK_RIGHT))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_RIGHTBRACKET) && (k.sym == SDLK_RIGHTBRACKET))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_RSHIFT) && (k.sym == SDLK_RSHIFT))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_S) && (k.sym == SDLK_s))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_SCROLLLOCK) && (k.sym == SDLK_SCROLLLOCK))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_SELECT) && (k.sym == SDLK_SELECT))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_SEMICOLON) && (k.sym == SDLK_SEMICOLON))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_SEPARATOR) && (k.sym == SDLK_SEPARATOR))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_SLASH) && (k.sym == SDLK_SLASH))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_SLEEP) && (k.sym == SDLK_SLEEP))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_SPACE) && (k.sym == SDLK_SPACE))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_STOP) && (k.sym == SDLK_STOP))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_SYSREQ) && (k.sym == SDLK_SYSREQ))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_T) && (k.sym == SDLK_t))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_TAB) && (k.sym == SDLK_TAB))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_THOUSANDSSEPARATOR) && (k.sym == SDLK_THOUSANDSSEPARATOR))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_U) && (k.sym == SDLK_u))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_UNDO) && (k.sym == SDLK_UNDO))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_UP) && (k.sym == SDLK_UP))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_V) && (k.sym == SDLK_v))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_VOLUMEDOWN) && (k.sym == SDLK_VOLUMEDOWN))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_VOLUMEUP) && (k.sym == SDLK_VOLUMEUP))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_W) && (k.sym == SDLK_w))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_WWW) && (k.sym == SDLK_WWW))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_X) && (k.sym == SDLK_x))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_Y) && (k.sym == SDLK_y))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_Z) && (k.sym == SDLK_z))) {
    return true;
  }

  if ((k.scancode == s) || ((s == SDL_SCANCODE_UNKNOWN) && (k.sym == SDLK_UNKNOWN))) {
    return true;
  }

  return false;
}

SDL_Scancode sdlk_to_scancode(const SDL_Keysym &k)
{
  if (k.sym == SDLK_0) {
    return SDL_SCANCODE_0;
  }

  if (k.sym == SDLK_1) {
    return SDL_SCANCODE_1;
  }

  if (k.sym == SDLK_2) {
    return SDL_SCANCODE_2;
  }

  if (k.sym == SDLK_3) {
    return SDL_SCANCODE_3;
  }

  if (k.sym == SDLK_4) {
    return SDL_SCANCODE_4;
  }

  if (k.sym == SDLK_5) {
    return SDL_SCANCODE_5;
  }

  if (k.sym == SDLK_6) {
    return SDL_SCANCODE_6;
  }

  if (k.sym == SDLK_7) {
    return SDL_SCANCODE_7;
  }

  if (k.sym == SDLK_8) {
    return SDL_SCANCODE_8;
  }

  if (k.sym == SDLK_9) {
    return SDL_SCANCODE_9;
  }

  if (k.sym == SDLK_a) {
    return SDL_SCANCODE_A;
  }

  if (k.sym == SDLK_AC_BACK) {
    return SDL_SCANCODE_AC_BACK;
  }

  if (k.sym == SDLK_AC_BOOKMARKS) {
    return SDL_SCANCODE_AC_BOOKMARKS;
  }

  if (k.sym == SDLK_AC_FORWARD) {
    return SDL_SCANCODE_AC_FORWARD;
  }

  if (k.sym == SDLK_AC_HOME) {
    return SDL_SCANCODE_AC_HOME;
  }

  if (k.sym == SDLK_AC_REFRESH) {
    return SDL_SCANCODE_AC_REFRESH;
  }

  if (k.sym == SDLK_AC_SEARCH) {
    return SDL_SCANCODE_AC_SEARCH;
  }

  if (k.sym == SDLK_AC_STOP) {
    return SDL_SCANCODE_AC_STOP;
  }

  if (k.sym == SDLK_AGAIN) {
    return SDL_SCANCODE_AGAIN;
  }

  if (k.sym == SDLK_ALTERASE) {
    return SDL_SCANCODE_ALTERASE;
  }

  if (k.sym == SDLK_QUOTE) {
    return SDL_SCANCODE_APOSTROPHE;
  }

  if (k.sym == SDLK_APPLICATION) {
    return SDL_SCANCODE_APPLICATION;
  }

  if (k.sym == SDLK_AUDIOMUTE) {
    return SDL_SCANCODE_AUDIOMUTE;
  }

  if (k.sym == SDLK_AUDIONEXT) {
    return SDL_SCANCODE_AUDIONEXT;
  }

  if (k.sym == SDLK_AUDIOPLAY) {
    return SDL_SCANCODE_AUDIOPLAY;
  }

  if (k.sym == SDLK_AUDIOPREV) {
    return SDL_SCANCODE_AUDIOPREV;
  }

  if (k.sym == SDLK_AUDIOSTOP) {
    return SDL_SCANCODE_AUDIOSTOP;
  }

  if (k.sym == SDLK_b) {
    return SDL_SCANCODE_B;
  }

  if (k.sym == SDLK_BACKSLASH) {
    return SDL_SCANCODE_BACKSLASH;
  }

  if (k.sym == SDLK_BACKSPACE) {
    return SDL_SCANCODE_BACKSPACE;
  }

  if (k.sym == SDLK_BRIGHTNESSDOWN) {
    return SDL_SCANCODE_BRIGHTNESSDOWN;
  }

  if (k.sym == SDLK_BRIGHTNESSUP) {
    return SDL_SCANCODE_BRIGHTNESSUP;
  }

  if (k.sym == SDLK_c) {
    return SDL_SCANCODE_C;
  }

  if (k.sym == SDLK_CALCULATOR) {
    return SDL_SCANCODE_CALCULATOR;
  }

  if (k.sym == SDLK_CANCEL) {
    return SDL_SCANCODE_CANCEL;
  }

  if (k.sym == SDLK_CAPSLOCK) {
    return SDL_SCANCODE_CAPSLOCK;
  }

  if (k.sym == SDLK_CLEAR) {
    return SDL_SCANCODE_CLEAR;
  }

  if (k.sym == SDLK_CLEARAGAIN) {
    return SDL_SCANCODE_CLEARAGAIN;
  }

  if (k.sym == SDLK_COMMA) {
    return SDL_SCANCODE_COMMA;
  }

  if (k.sym == SDLK_COMPUTER) {
    return SDL_SCANCODE_COMPUTER;
  }

  if (k.sym == SDLK_COPY) {
    return SDL_SCANCODE_COPY;
  }

  if (k.sym == SDLK_CRSEL) {
    return SDL_SCANCODE_CRSEL;
  }

  if (k.sym == SDLK_CURRENCYSUBUNIT) {
    return SDL_SCANCODE_CURRENCYSUBUNIT;
  }

  if (k.sym == SDLK_CURRENCYUNIT) {
    return SDL_SCANCODE_CURRENCYUNIT;
  }

  if (k.sym == SDLK_CUT) {
    return SDL_SCANCODE_CUT;
  }

  if (k.sym == SDLK_d) {
    return SDL_SCANCODE_D;
  }

  if (k.sym == SDLK_DECIMALSEPARATOR) {
    return SDL_SCANCODE_DECIMALSEPARATOR;
  }

  if (k.sym == SDLK_DELETE) {
    return SDL_SCANCODE_DELETE;
  }

  if (k.sym == SDLK_DISPLAYSWITCH) {
    return SDL_SCANCODE_DISPLAYSWITCH;
  }

  if (k.sym == SDLK_DOWN) {
    return SDL_SCANCODE_DOWN;
  }

  if (k.sym == SDLK_e) {
    return SDL_SCANCODE_E;
  }

  if (k.sym == SDLK_EJECT) {
    return SDL_SCANCODE_EJECT;
  }

  if (k.sym == SDLK_END) {
    return SDL_SCANCODE_END;
  }

  if (k.sym == SDLK_EQUALS) {
    return SDL_SCANCODE_EQUALS;
  }

  if (k.sym == SDLK_ESCAPE) {
    return SDL_SCANCODE_ESCAPE;
  }

  if (k.sym == SDLK_EXECUTE) {
    return SDL_SCANCODE_EXECUTE;
  }

  if (k.sym == SDLK_EXSEL) {
    return SDL_SCANCODE_EXSEL;
  }

  if (k.sym == SDLK_f) {
    return SDL_SCANCODE_F;
  }

  if (k.sym == SDLK_F1) {
    return SDL_SCANCODE_F1;
  }

  if (k.sym == SDLK_F10) {
    return SDL_SCANCODE_F10;
  }

  if (k.sym == SDLK_F11) {
    return SDL_SCANCODE_F11;
  }

  if (k.sym == SDLK_F12) {
    return SDL_SCANCODE_F12;
  }

  if (k.sym == SDLK_F13) {
    return SDL_SCANCODE_F13;
  }

  if (k.sym == SDLK_F14) {
    return SDL_SCANCODE_F14;
  }

  if (k.sym == SDLK_F15) {
    return SDL_SCANCODE_F15;
  }

  if (k.sym == SDLK_F16) {
    return SDL_SCANCODE_F16;
  }

  if (k.sym == SDLK_F17) {
    return SDL_SCANCODE_F17;
  }

  if (k.sym == SDLK_F18) {
    return SDL_SCANCODE_F18;
  }

  if (k.sym == SDLK_F19) {
    return SDL_SCANCODE_F19;
  }

  if (k.sym == SDLK_F2) {
    return SDL_SCANCODE_F2;
  }

  if (k.sym == SDLK_F20) {
    return SDL_SCANCODE_F20;
  }

  if (k.sym == SDLK_F21) {
    return SDL_SCANCODE_F21;
  }

  if (k.sym == SDLK_F22) {
    return SDL_SCANCODE_F22;
  }

  if (k.sym == SDLK_F23) {
    return SDL_SCANCODE_F23;
  }

  if (k.sym == SDLK_F24) {
    return SDL_SCANCODE_F24;
  }

  if (k.sym == SDLK_F3) {
    return SDL_SCANCODE_F3;
  }

  if (k.sym == SDLK_F4) {
    return SDL_SCANCODE_F4;
  }

  if (k.sym == SDLK_F5) {
    return SDL_SCANCODE_F5;
  }

  if (k.sym == SDLK_F6) {
    return SDL_SCANCODE_F6;
  }

  if (k.sym == SDLK_F7) {
    return SDL_SCANCODE_F7;
  }

  if (k.sym == SDLK_F8) {
    return SDL_SCANCODE_F8;
  }

  if (k.sym == SDLK_F9) {
    return SDL_SCANCODE_F9;
  }

  if (k.sym == SDLK_FIND) {
    return SDL_SCANCODE_FIND;
  }

  if (k.sym == SDLK_g) {
    return SDL_SCANCODE_G;
  }

  if (k.sym == SDLK_BACKQUOTE) {
    return SDL_SCANCODE_GRAVE;
  }

  if (k.sym == SDLK_h) {
    return SDL_SCANCODE_H;
  }

  if (k.sym == SDLK_HELP) {
    return SDL_SCANCODE_HELP;
  }

  if (k.sym == SDLK_HOME) {
    return SDL_SCANCODE_HOME;
  }

  if (k.sym == SDLK_i) {
    return SDL_SCANCODE_I;
  }

  if (k.sym == SDLK_INSERT) {
    return SDL_SCANCODE_INSERT;
  }

  if (k.sym == SDLK_j) {
    return SDL_SCANCODE_J;
  }

  if (k.sym == SDLK_k) {
    return SDL_SCANCODE_K;
  }

  if (k.sym == SDLK_KBDILLUMDOWN) {
    return SDL_SCANCODE_KBDILLUMDOWN;
  }

  if (k.sym == SDLK_KBDILLUMTOGGLE) {
    return SDL_SCANCODE_KBDILLUMTOGGLE;
  }

  if (k.sym == SDLK_KBDILLUMUP) {
    return SDL_SCANCODE_KBDILLUMUP;
  }

  if (k.sym == SDLK_KP_0) {
    return SDL_SCANCODE_KP_0;
  }

  if (k.sym == SDLK_KP_00) {
    return SDL_SCANCODE_KP_00;
  }

  if (k.sym == SDLK_KP_000) {
    return SDL_SCANCODE_KP_000;
  }

  if (k.sym == SDLK_KP_1) {
    return SDL_SCANCODE_KP_1;
  }

  if (k.sym == SDLK_KP_2) {
    return SDL_SCANCODE_KP_2;
  }

  if (k.sym == SDLK_KP_3) {
    return SDL_SCANCODE_KP_3;
  }

  if (k.sym == SDLK_KP_4) {
    return SDL_SCANCODE_KP_4;
  }

  if (k.sym == SDLK_KP_5) {
    return SDL_SCANCODE_KP_5;
  }

  if (k.sym == SDLK_KP_6) {
    return SDL_SCANCODE_KP_6;
  }

  if (k.sym == SDLK_KP_7) {
    return SDL_SCANCODE_KP_7;
  }

  if (k.sym == SDLK_KP_8) {
    return SDL_SCANCODE_KP_8;
  }

  if (k.sym == SDLK_KP_9) {
    return SDL_SCANCODE_KP_9;
  }

  if (k.sym == SDLK_KP_A) {
    return SDL_SCANCODE_KP_A;
  }

  if (k.sym == SDLK_KP_AMPERSAND) {
    return SDL_SCANCODE_KP_AMPERSAND;
  }

  if (k.sym == SDLK_KP_AT) {
    return SDL_SCANCODE_KP_AT;
  }

  if (k.sym == SDLK_KP_B) {
    return SDL_SCANCODE_KP_B;
  }

  if (k.sym == SDLK_KP_BACKSPACE) {
    return SDL_SCANCODE_KP_BACKSPACE;
  }

  if (k.sym == SDLK_KP_BINARY) {
    return SDL_SCANCODE_KP_BINARY;
  }

  if (k.sym == SDLK_KP_C) {
    return SDL_SCANCODE_KP_C;
  }

  if (k.sym == SDLK_KP_CLEAR) {
    return SDL_SCANCODE_KP_CLEAR;
  }

  if (k.sym == SDLK_KP_COLON) {
    return SDL_SCANCODE_KP_COLON;
  }

  if (k.sym == SDLK_KP_COMMA) {
    return SDL_SCANCODE_KP_COMMA;
  }

  if (k.sym == SDLK_KP_D) {
    return SDL_SCANCODE_KP_D;
  }

  if (k.sym == SDLK_KP_DBLAMPERSAND) {
    return SDL_SCANCODE_KP_DBLAMPERSAND;
  }

  if (k.sym == SDLK_KP_DECIMAL) {
    return SDL_SCANCODE_KP_DECIMAL;
  }

  if (k.sym == SDLK_KP_DIVIDE) {
    return SDL_SCANCODE_KP_DIVIDE;
  }

  if (k.sym == SDLK_KP_E) {
    return SDL_SCANCODE_KP_E;
  }

  if (k.sym == SDLK_KP_ENTER) {
    return SDL_SCANCODE_KP_ENTER;
  }

  if (k.sym == SDLK_KP_EQUALS) {
    return SDL_SCANCODE_KP_EQUALS;
  }

  if (k.sym == SDLK_KP_EQUALSAS400) {
    return SDL_SCANCODE_KP_EQUALSAS400;
  }

  if (k.sym == SDLK_KP_EXCLAM) {
    return SDL_SCANCODE_KP_EXCLAM;
  }

  if (k.sym == SDLK_KP_F) {
    return SDL_SCANCODE_KP_F;
  }

  if (k.sym == SDLK_KP_GREATER) {
    return SDL_SCANCODE_KP_GREATER;
  }

  if (k.sym == SDLK_KP_HASH) {
    return SDL_SCANCODE_KP_HASH;
  }

  if (k.sym == SDLK_KP_HEXADECIMAL) {
    return SDL_SCANCODE_KP_HEXADECIMAL;
  }

  if (k.sym == SDLK_KP_LEFTBRACE) {
    return SDL_SCANCODE_KP_LEFTBRACE;
  }

  if (k.sym == SDLK_KP_LEFTPAREN) {
    return SDL_SCANCODE_KP_LEFTPAREN;
  }

  if (k.sym == SDLK_KP_LESS) {
    return SDL_SCANCODE_KP_LESS;
  }

  if (k.sym == SDLK_KP_MEMADD) {
    return SDL_SCANCODE_KP_MEMADD;
  }

  if (k.sym == SDLK_KP_MEMCLEAR) {
    return SDL_SCANCODE_KP_MEMCLEAR;
  }

  if (k.sym == SDLK_KP_MEMDIVIDE) {
    return SDL_SCANCODE_KP_MEMDIVIDE;
  }

  if (k.sym == SDLK_KP_MEMMULTIPLY) {
    return SDL_SCANCODE_KP_MEMMULTIPLY;
  }

  if (k.sym == SDLK_KP_MEMRECALL) {
    return SDL_SCANCODE_KP_MEMRECALL;
  }

  if (k.sym == SDLK_KP_MEMSTORE) {
    return SDL_SCANCODE_KP_MEMSTORE;
  }

  if (k.sym == SDLK_KP_MEMSUBTRACT) {
    return SDL_SCANCODE_KP_MEMSUBTRACT;
  }

  if (k.sym == SDLK_KP_MINUS) {
    return SDL_SCANCODE_KP_MINUS;
  }

  if (k.sym == SDLK_KP_MULTIPLY) {
    return SDL_SCANCODE_KP_MULTIPLY;
  }

  if (k.sym == SDLK_KP_OCTAL) {
    return SDL_SCANCODE_KP_OCTAL;
  }

  if (k.sym == SDLK_KP_PERCENT) {
    return SDL_SCANCODE_KP_PERCENT;
  }

  if (k.sym == SDLK_KP_PERIOD) {
    return SDL_SCANCODE_KP_PERIOD;
  }

  if (k.sym == SDLK_KP_PLUS) {
    return SDL_SCANCODE_KP_PLUS;
  }

  if (k.sym == SDLK_KP_PLUSMINUS) {
    return SDL_SCANCODE_KP_PLUSMINUS;
  }

  if (k.sym == SDLK_KP_POWER) {
    return SDL_SCANCODE_KP_POWER;
  }

  if (k.sym == SDLK_KP_RIGHTBRACE) {
    return SDL_SCANCODE_KP_RIGHTBRACE;
  }

  if (k.sym == SDLK_KP_RIGHTPAREN) {
    return SDL_SCANCODE_KP_RIGHTPAREN;
  }

  if (k.sym == SDLK_KP_SPACE) {
    return SDL_SCANCODE_KP_SPACE;
  }

  if (k.sym == SDLK_KP_TAB) {
    return SDL_SCANCODE_KP_TAB;
  }

  if (k.sym == SDLK_KP_VERTICALBAR) {
    return SDL_SCANCODE_KP_VERTICALBAR;
  }

  if (k.sym == SDLK_KP_XOR) {
    return SDL_SCANCODE_KP_XOR;
  }

  if (k.sym == SDLK_l) {
    return SDL_SCANCODE_L;
  }

  if (k.sym == SDLK_LALT) {
    return SDL_SCANCODE_LALT;
  }

  if (k.sym == SDLK_LCTRL) {
    return SDL_SCANCODE_LCTRL;
  }

  if (k.sym == SDLK_LEFT) {
    return SDL_SCANCODE_LEFT;
  }

  if (k.sym == SDLK_LEFTBRACKET) {
    return SDL_SCANCODE_LEFTBRACKET;
  }

  if (k.sym == SDLK_LGUI) {
    return SDL_SCANCODE_LGUI;
  }

  if (k.sym == SDLK_LSHIFT) {
    return SDL_SCANCODE_LSHIFT;
  }

  if (k.sym == SDLK_m) {
    return SDL_SCANCODE_M;
  }

  if (k.sym == SDLK_MAIL) {
    return SDL_SCANCODE_MAIL;
  }

  if (k.sym == SDLK_MEDIASELECT) {
    return SDL_SCANCODE_MEDIASELECT;
  }

  if (k.sym == SDLK_MENU) {
    return SDL_SCANCODE_MENU;
  }

  if (k.sym == SDLK_MINUS) {
    return SDL_SCANCODE_MINUS;
  }

  if (k.sym == SDLK_MODE) {
    return SDL_SCANCODE_MODE;
  }

  if (k.sym == SDLK_MUTE) {
    return SDL_SCANCODE_MUTE;
  }

  if (k.sym == SDLK_n) {
    return SDL_SCANCODE_N;
  }

  if (k.sym == SDLK_NUMLOCKCLEAR) {
    return SDL_SCANCODE_NUMLOCKCLEAR;
  }

  if (k.sym == SDLK_o) {
    return SDL_SCANCODE_O;
  }

  if (k.sym == SDLK_OPER) {
    return SDL_SCANCODE_OPER;
  }

  if (k.sym == SDLK_OUT) {
    return SDL_SCANCODE_OUT;
  }

  if (k.sym == SDLK_p) {
    return SDL_SCANCODE_P;
  }

  if (k.sym == SDLK_PAGEDOWN) {
    return SDL_SCANCODE_PAGEDOWN;
  }

  if (k.sym == SDLK_PAGEUP) {
    return SDL_SCANCODE_PAGEUP;
  }

  if (k.sym == SDLK_PASTE) {
    return SDL_SCANCODE_PASTE;
  }

  if (k.sym == SDLK_PAUSE) {
    return SDL_SCANCODE_PAUSE;
  }

  if (k.sym == SDLK_PERIOD) {
    return SDL_SCANCODE_PERIOD;
  }

  if (k.sym == SDLK_POWER) {
    return SDL_SCANCODE_POWER;
  }

  if (k.sym == SDLK_PRINTSCREEN) {
    return SDL_SCANCODE_PRINTSCREEN;
  }

  if (k.sym == SDLK_PRIOR) {
    return SDL_SCANCODE_PRIOR;
  }

  if (k.sym == SDLK_q) {
    return SDL_SCANCODE_Q;
  }

  if (k.sym == SDLK_r) {
    return SDL_SCANCODE_R;
  }

  if (k.sym == SDLK_RALT) {
    return SDL_SCANCODE_RALT;
  }

  if (k.sym == SDLK_RCTRL) {
    return SDL_SCANCODE_RCTRL;
  }

  if (k.sym == SDLK_RETURN) {
    return SDL_SCANCODE_RETURN;
  }

  if (k.sym == SDLK_RETURN2) {
    return SDL_SCANCODE_RETURN2;
  }

  if (k.sym == SDLK_RGUI) {
    return SDL_SCANCODE_RGUI;
  }

  if (k.sym == SDLK_RIGHT) {
    return SDL_SCANCODE_RIGHT;
  }

  if (k.sym == SDLK_RIGHTBRACKET) {
    return SDL_SCANCODE_RIGHTBRACKET;
  }

  if (k.sym == SDLK_RSHIFT) {
    return SDL_SCANCODE_RSHIFT;
  }

  if (k.sym == SDLK_s) {
    return SDL_SCANCODE_S;
  }

  if (k.sym == SDLK_SCROLLLOCK) {
    return SDL_SCANCODE_SCROLLLOCK;
  }

  if (k.sym == SDLK_SELECT) {
    return SDL_SCANCODE_SELECT;
  }

  if (k.sym == SDLK_SEMICOLON) {
    return SDL_SCANCODE_SEMICOLON;
  }

  if (k.sym == SDLK_SEPARATOR) {
    return SDL_SCANCODE_SEPARATOR;
  }

  if (k.sym == SDLK_SLASH) {
    return SDL_SCANCODE_SLASH;
  }

  if (k.sym == SDLK_SLEEP) {
    return SDL_SCANCODE_SLEEP;
  }

  if (k.sym == SDLK_SPACE) {
    return SDL_SCANCODE_SPACE;
  }

  if (k.sym == SDLK_STOP) {
    return SDL_SCANCODE_STOP;
  }

  if (k.sym == SDLK_SYSREQ) {
    return SDL_SCANCODE_SYSREQ;
  }

  if (k.sym == SDLK_t) {
    return SDL_SCANCODE_T;
  }

  if (k.sym == SDLK_TAB) {
    return SDL_SCANCODE_TAB;
  }

  if (k.sym == SDLK_THOUSANDSSEPARATOR) {
    return SDL_SCANCODE_THOUSANDSSEPARATOR;
  }

  if (k.sym == SDLK_u) {
    return SDL_SCANCODE_U;
  }

  if (k.sym == SDLK_UNDO) {
    return SDL_SCANCODE_UNDO;
  }

  if (k.sym == SDLK_UP) {
    return SDL_SCANCODE_UP;
  }

  if (k.sym == SDLK_v) {
    return SDL_SCANCODE_V;
  }

  if (k.sym == SDLK_VOLUMEDOWN) {
    return SDL_SCANCODE_VOLUMEDOWN;
  }

  if (k.sym == SDLK_VOLUMEUP) {
    return SDL_SCANCODE_VOLUMEUP;
  }

  if (k.sym == SDLK_w) {
    return SDL_SCANCODE_W;
  }

  if (k.sym == SDLK_WWW) {
    return SDL_SCANCODE_WWW;
  }

  if (k.sym == SDLK_x) {
    return SDL_SCANCODE_X;
  }

  if (k.sym == SDLK_y) {
    return SDL_SCANCODE_Y;
  }

  if (k.sym == SDLK_z) {
    return SDL_SCANCODE_Z;
  }

  return SDL_SCANCODE_UNKNOWN;
}
