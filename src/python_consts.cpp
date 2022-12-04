//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_py_level.hpp"

#include "my_ascii.hpp"
#include "my_depth.hpp"
#include "my_monst.hpp"
#include "my_py_sdl.hpp"
#include "my_sound.hpp"
#include "my_thing_template.hpp"

void py_my_module_add_stat_consts(void)
{
  TRACE_AND_INDENT();

  PyModule_AddIntConstant(my_mod, "CHANNEL_EXPLOSION", CHANNEL_EXPLOSION);
  PyModule_AddIntConstant(my_mod, "CHANNEL_FOOTSTEPS", CHANNEL_FOOTSTEPS);
  PyModule_AddIntConstant(my_mod, "CHANNEL_IMPACT", CHANNEL_IMPACT);
  PyModule_AddIntConstant(my_mod, "CHANNEL_MISC", CHANNEL_MISC);
  PyModule_AddIntConstant(my_mod, "CHANNEL_MONST_BIRTH", CHANNEL_MONST_BIRTH);
  PyModule_AddIntConstant(my_mod, "CHANNEL_MONST", CHANNEL_MONST);
  PyModule_AddIntConstant(my_mod, "CHANNEL_MONST_DEATH", CHANNEL_MONST_DEATH);
  PyModule_AddIntConstant(my_mod, "CHANNEL_WEAPON", CHANNEL_WEAPON);
  PyModule_AddIntConstant(my_mod, "MAP_DEPTH_CHASM", MAP_DEPTH_CHASM);
  PyModule_AddIntConstant(my_mod, "MAP_DEPTH_FLOOR2", MAP_DEPTH_FLOOR2);
  PyModule_AddIntConstant(my_mod, "MAP_DEPTH_FLOOR", MAP_DEPTH_FLOOR);
  PyModule_AddIntConstant(my_mod, "MAP_DEPTH_LIQUID", MAP_DEPTH_LIQUID);
  PyModule_AddIntConstant(my_mod, "MAP_DEPTH_OBJ", MAP_DEPTH_OBJ);
  PyModule_AddIntConstant(my_mod, "MAP_DEPTH_TOP", MAP_DEPTH_TOP);
  PyModule_AddIntConstant(my_mod, "MAP_HEIGHT", MAP_HEIGHT);
  PyModule_AddIntConstant(my_mod, "MAP_WIDTH", MAP_WIDTH);
  PyModule_AddIntConstant(my_mod, "MAP_TICK_PRIO_VERY_HIGH", MAP_TICK_PRIO_VERY_HIGH);
  PyModule_AddIntConstant(my_mod, "MAP_TICK_PRIO_HIGH", MAP_TICK_PRIO_HIGH);
  PyModule_AddIntConstant(my_mod, "MAP_TICK_PRIO_NORMAL", MAP_TICK_PRIO_NORMAL);
  PyModule_AddIntConstant(my_mod, "MAP_TICK_PRIO_LOW", MAP_TICK_PRIO_LOW);
  PyModule_AddIntConstant(my_mod, "MAP_Z_PRIO_ALWAYS_BEHIND", MAP_Z_PRIO_ALWAYS_BEHIND);
  PyModule_AddIntConstant(my_mod, "MAP_Z_PRIO_BARREL", MAP_Z_PRIO_BARREL);
  PyModule_AddIntConstant(my_mod, "MAP_Z_PRIO_BEHIND", MAP_Z_PRIO_BEHIND);
  PyModule_AddIntConstant(my_mod, "MAP_Z_PRIO_CARRY", MAP_Z_PRIO_CARRY);
  PyModule_AddIntConstant(my_mod, "MAP_Z_PRIO_CLOAK", MAP_Z_PRIO_CLOAK);
  PyModule_AddIntConstant(my_mod, "MAP_Z_PRIO_CONSUMER", MAP_Z_PRIO_CONSUMER);
  PyModule_AddIntConstant(my_mod, "MAP_Z_PRIO_CURSOR", MAP_Z_PRIO_CURSOR);
  PyModule_AddIntConstant(my_mod, "MAP_Z_PRIO_EFFECT", MAP_Z_PRIO_EFFECT);
  PyModule_AddIntConstant(my_mod, "MAP_Z_PRIO_FIRE", MAP_Z_PRIO_FIRE);
  PyModule_AddIntConstant(my_mod, "MAP_Z_PRIO_FOILAGE", MAP_Z_PRIO_FOILAGE);
  PyModule_AddIntConstant(my_mod, "MAP_Z_PRIO_ITEM", MAP_Z_PRIO_ITEM);
  PyModule_AddIntConstant(my_mod, "MAP_Z_PRIO_MONST", MAP_Z_PRIO_MONST);
  PyModule_AddIntConstant(my_mod, "MAP_Z_PRIO_BIG_MONST", MAP_Z_PRIO_BIG_MONST);
  PyModule_AddIntConstant(my_mod, "MAP_Z_PRIO_PLAYER", MAP_Z_PRIO_PLAYER);
  PyModule_AddIntConstant(my_mod, "MAP_Z_PRIO_RING", MAP_Z_PRIO_RING);
  PyModule_AddIntConstant(my_mod, "MAP_Z_PRIO_SWING", MAP_Z_PRIO_SWING);
  PyModule_AddIntConstant(my_mod, "MAP_Z_PRIO_WEB", MAP_Z_PRIO_WEB);
  PyModule_AddIntConstant(my_mod, "THING_SIZE_GARGANTUAN", THING_SIZE_GARGANTUAN);
  PyModule_AddIntConstant(my_mod, "THING_SIZE_GIANT", THING_SIZE_GIANT);
  PyModule_AddIntConstant(my_mod, "THING_SIZE_LARGE", THING_SIZE_LARGE);
  PyModule_AddIntConstant(my_mod, "THING_SIZE_NORMAL", THING_SIZE_NORMAL);
  PyModule_AddIntConstant(my_mod, "THING_SIZE_SMALL", THING_SIZE_SMALL);
  PyModule_AddIntConstant(my_mod, "THING_SIZE_TINY", THING_SIZE_TINY);
  PyModule_AddIntConstant(my_mod, "RARITY_COMMON", THING_RARITY_COMMON);
  PyModule_AddIntConstant(my_mod, "RARITY_RARE", THING_RARITY_RARE);
  PyModule_AddIntConstant(my_mod, "RARITY_UNCOMMON", THING_RARITY_UNCOMMON);
  PyModule_AddIntConstant(my_mod, "RARITY_UNIQUE", THING_RARITY_UNIQUE);
  PyModule_AddIntConstant(my_mod, "RARITY_VERY_RARE", THING_RARITY_VERY_RARE);
  PyModule_AddIntConstant(my_mod, "TERM_HEIGHT", TERM_HEIGHT);
  PyModule_AddIntConstant(my_mod, "TERM_WIDTH", TERM_WIDTH);
  PyModule_AddStringConstant(my_mod, "MYVER", MYVER);

  PyModule_AddIntConstant(my_mod, "KMOD_LSHIFT", KMOD_LSHIFT);
  PyModule_AddIntConstant(my_mod, "KMOD_RSHIFT", KMOD_RSHIFT);
  PyModule_AddIntConstant(my_mod, "KMOD_LALT", KMOD_LALT);
  PyModule_AddIntConstant(my_mod, "KMOD_RALT", KMOD_RALT);
  PyModule_AddIntConstant(my_mod, "KMOD_LCTRL", KMOD_LCTRL);
  PyModule_AddIntConstant(my_mod, "KMOD_RCTRL", KMOD_RCTRL);

  PyModule_AddIntConstant(my_mod, "SDLK_0", SDLK_0);
  PyModule_AddIntConstant(my_mod, "SDLK_1", SDLK_1);
  PyModule_AddIntConstant(my_mod, "SDLK_2", SDLK_2);
  PyModule_AddIntConstant(my_mod, "SDLK_3", SDLK_3);
  PyModule_AddIntConstant(my_mod, "SDLK_4", SDLK_4);
  PyModule_AddIntConstant(my_mod, "SDLK_5", SDLK_5);
  PyModule_AddIntConstant(my_mod, "SDLK_6", SDLK_6);
  PyModule_AddIntConstant(my_mod, "SDLK_7", SDLK_7);
  PyModule_AddIntConstant(my_mod, "SDLK_8", SDLK_8);
  PyModule_AddIntConstant(my_mod, "SDLK_9", SDLK_9);
  PyModule_AddIntConstant(my_mod, "SDLK_AMPERSAND", SDLK_AMPERSAND);
  PyModule_AddIntConstant(my_mod, "SDLK_ASTERISK", SDLK_ASTERISK);
  PyModule_AddIntConstant(my_mod, "SDLK_AT", SDLK_AT);
  PyModule_AddIntConstant(my_mod, "SDLK_BACKQUOTE", SDLK_BACKQUOTE);
  PyModule_AddIntConstant(my_mod, "SDLK_BACKSLASH", SDLK_BACKSLASH);
  PyModule_AddIntConstant(my_mod, "SDLK_BACKSPACE", SDLK_BACKSPACE);
  PyModule_AddIntConstant(my_mod, "SDLK_CARET", SDLK_CARET);
  PyModule_AddIntConstant(my_mod, "SDLK_COLON", SDLK_COLON);
  PyModule_AddIntConstant(my_mod, "SDLK_COMMA", SDLK_COMMA);
  PyModule_AddIntConstant(my_mod, "SDLK_DELETE", SDLK_DELETE);
  PyModule_AddIntConstant(my_mod, "SDLK_DOLLAR", SDLK_DOLLAR);
  PyModule_AddIntConstant(my_mod, "SDLK_EQUALS", SDLK_EQUALS);
  PyModule_AddIntConstant(my_mod, "SDLK_ESCAPE", SDLK_ESCAPE);
  PyModule_AddIntConstant(my_mod, "SDLK_EXCLAIM", SDLK_EXCLAIM);
  PyModule_AddIntConstant(my_mod, "SDLK_GREATER", SDLK_GREATER);
  PyModule_AddIntConstant(my_mod, "SDLK_HASH", SDLK_HASH);
  PyModule_AddIntConstant(my_mod, "SDLK_LEFTBRACKET", SDLK_LEFTBRACKET);
  PyModule_AddIntConstant(my_mod, "SDLK_LEFTPAREN", SDLK_LEFTPAREN);
  PyModule_AddIntConstant(my_mod, "SDLK_LESS", SDLK_LESS);
  PyModule_AddIntConstant(my_mod, "SDLK_MINUS", SDLK_MINUS);
  PyModule_AddIntConstant(my_mod, "SDLK_PERIOD", SDLK_PERIOD);
  PyModule_AddIntConstant(my_mod, "SDLK_PLUS", SDLK_PLUS);
  PyModule_AddIntConstant(my_mod, "SDLK_QUESTION", SDLK_QUESTION);
  PyModule_AddIntConstant(my_mod, "SDLK_QUOTE", SDLK_QUOTE);
  PyModule_AddIntConstant(my_mod, "SDLK_QUOTEDBL", SDLK_QUOTEDBL);
  PyModule_AddIntConstant(my_mod, "SDLK_RETURN", SDLK_RETURN);
  PyModule_AddIntConstant(my_mod, "SDLK_RIGHTBRACKET", SDLK_RIGHTBRACKET);
  PyModule_AddIntConstant(my_mod, "SDLK_RIGHTPAREN", SDLK_RIGHTPAREN);
  PyModule_AddIntConstant(my_mod, "SDLK_SEMICOLON", SDLK_SEMICOLON);
  PyModule_AddIntConstant(my_mod, "SDLK_SLASH", SDLK_SLASH);
  PyModule_AddIntConstant(my_mod, "SDLK_SPACE", SDLK_SPACE);
  PyModule_AddIntConstant(my_mod, "SDLK_TAB", SDLK_TAB);
  PyModule_AddIntConstant(my_mod, "SDLK_UNDERSCORE", SDLK_UNDERSCORE);
  PyModule_AddIntConstant(my_mod, "SDLK_a", SDLK_a);
  PyModule_AddIntConstant(my_mod, "SDLK_b", SDLK_b);
  PyModule_AddIntConstant(my_mod, "SDLK_c", SDLK_c);
  PyModule_AddIntConstant(my_mod, "SDLK_d", SDLK_d);
  PyModule_AddIntConstant(my_mod, "SDLK_e", SDLK_e);
  PyModule_AddIntConstant(my_mod, "SDLK_f", SDLK_f);
  PyModule_AddIntConstant(my_mod, "SDLK_g", SDLK_g);
  PyModule_AddIntConstant(my_mod, "SDLK_h", SDLK_h);
  PyModule_AddIntConstant(my_mod, "SDLK_i", SDLK_i);
  PyModule_AddIntConstant(my_mod, "SDLK_j", SDLK_j);
  PyModule_AddIntConstant(my_mod, "SDLK_k", SDLK_k);
  PyModule_AddIntConstant(my_mod, "SDLK_l", SDLK_l);
  PyModule_AddIntConstant(my_mod, "SDLK_m", SDLK_m);
  PyModule_AddIntConstant(my_mod, "SDLK_n", SDLK_n);
  PyModule_AddIntConstant(my_mod, "SDLK_o", SDLK_o);
  PyModule_AddIntConstant(my_mod, "SDLK_p", SDLK_p);
  PyModule_AddIntConstant(my_mod, "SDLK_q", SDLK_q);
  PyModule_AddIntConstant(my_mod, "SDLK_r", SDLK_r);
  PyModule_AddIntConstant(my_mod, "SDLK_s", SDLK_s);
  PyModule_AddIntConstant(my_mod, "SDLK_t", SDLK_t);
  PyModule_AddIntConstant(my_mod, "SDLK_u", SDLK_u);
  PyModule_AddIntConstant(my_mod, "SDLK_v", SDLK_v);
  PyModule_AddIntConstant(my_mod, "SDLK_w", SDLK_w);
  PyModule_AddIntConstant(my_mod, "SDLK_x", SDLK_x);
  PyModule_AddIntConstant(my_mod, "SDLK_y", SDLK_y);
  PyModule_AddIntConstant(my_mod, "SDLK_z", SDLK_z);

#if SDL_MAJOR_VERSION == 1 /* { */
  PyModule_AddIntConstant(my_mod, "SDLK_KP0", SDLK_KP0);
  PyModule_AddIntConstant(my_mod, "SDLK_KP1", SDLK_KP1);
  PyModule_AddIntConstant(my_mod, "SDLK_KP2", SDLK_KP2);
  PyModule_AddIntConstant(my_mod, "SDLK_KP3", SDLK_KP3);
  PyModule_AddIntConstant(my_mod, "SDLK_KP4", SDLK_KP4);
  PyModule_AddIntConstant(my_mod, "SDLK_KP5", SDLK_KP5);
  PyModule_AddIntConstant(my_mod, "SDLK_KP6", SDLK_KP6);
  PyModule_AddIntConstant(my_mod, "SDLK_KP7", SDLK_KP7);
  PyModule_AddIntConstant(my_mod, "SDLK_KP8", SDLK_KP8);
  PyModule_AddIntConstant(my_mod, "SDLK_KP9", SDLK_KP9);
#else
  PyModule_AddIntConstant(my_mod, "SDLK_KP0", SDLK_KP_0);
  PyModule_AddIntConstant(my_mod, "SDLK_KP1", SDLK_KP_1);
  PyModule_AddIntConstant(my_mod, "SDLK_KP2", SDLK_KP_2);
  PyModule_AddIntConstant(my_mod, "SDLK_KP3", SDLK_KP_3);
  PyModule_AddIntConstant(my_mod, "SDLK_KP4", SDLK_KP_4);
  PyModule_AddIntConstant(my_mod, "SDLK_KP5", SDLK_KP_5);
  PyModule_AddIntConstant(my_mod, "SDLK_KP6", SDLK_KP_6);
  PyModule_AddIntConstant(my_mod, "SDLK_KP7", SDLK_KP_7);
  PyModule_AddIntConstant(my_mod, "SDLK_KP8", SDLK_KP_8);
  PyModule_AddIntConstant(my_mod, "SDLK_KP9", SDLK_KP_9);
#endif

  PyModule_AddIntConstant(my_mod, "SDLK_KP_PERIOD", SDLK_KP_PERIOD);
  PyModule_AddIntConstant(my_mod, "SDLK_KP_DIVIDE", SDLK_KP_DIVIDE);
  PyModule_AddIntConstant(my_mod, "SDLK_KP_MULTIPLY", SDLK_KP_MULTIPLY);
  PyModule_AddIntConstant(my_mod, "SDLK_KP_MINUS", SDLK_KP_MINUS);
  PyModule_AddIntConstant(my_mod, "SDLK_KP_PLUS", SDLK_KP_PLUS);
  PyModule_AddIntConstant(my_mod, "SDLK_KP_ENTER", SDLK_KP_ENTER);
  PyModule_AddIntConstant(my_mod, "SDLK_KP_EQUALS", SDLK_KP_EQUALS);
  PyModule_AddIntConstant(my_mod, "SDLK_UP", SDLK_UP);
  PyModule_AddIntConstant(my_mod, "SDLK_DOWN", SDLK_DOWN);
  PyModule_AddIntConstant(my_mod, "SDLK_RIGHT", SDLK_RIGHT);
  PyModule_AddIntConstant(my_mod, "SDLK_LEFT", SDLK_LEFT);
  PyModule_AddIntConstant(my_mod, "SDLK_INSERT", SDLK_INSERT);
  PyModule_AddIntConstant(my_mod, "SDLK_HOME", SDLK_HOME);
  PyModule_AddIntConstant(my_mod, "SDLK_END", SDLK_END);
  PyModule_AddIntConstant(my_mod, "SDLK_PAGEUP", SDLK_PAGEUP);
  PyModule_AddIntConstant(my_mod, "SDLK_PAGEDOWN", SDLK_PAGEDOWN);
  PyModule_AddIntConstant(my_mod, "SDLK_F1", SDLK_F1);
  PyModule_AddIntConstant(my_mod, "SDLK_F2", SDLK_F2);
  PyModule_AddIntConstant(my_mod, "SDLK_F3", SDLK_F3);
  PyModule_AddIntConstant(my_mod, "SDLK_F4", SDLK_F4);
  PyModule_AddIntConstant(my_mod, "SDLK_F5", SDLK_F5);
  PyModule_AddIntConstant(my_mod, "SDLK_F6", SDLK_F6);
  PyModule_AddIntConstant(my_mod, "SDLK_F7", SDLK_F7);
  PyModule_AddIntConstant(my_mod, "SDLK_F8", SDLK_F8);
  PyModule_AddIntConstant(my_mod, "SDLK_F9", SDLK_F9);
  PyModule_AddIntConstant(my_mod, "SDLK_F10", SDLK_F10);
  PyModule_AddIntConstant(my_mod, "SDLK_F11", SDLK_F11);
  PyModule_AddIntConstant(my_mod, "SDLK_F12", SDLK_F12);
  PyModule_AddIntConstant(my_mod, "SDLK_F13", SDLK_F13);
  PyModule_AddIntConstant(my_mod, "SDLK_F14", SDLK_F14);
  PyModule_AddIntConstant(my_mod, "SDLK_F15", SDLK_F15);
  PyModule_AddIntConstant(my_mod, "SDLK_CAPSLOCK", SDLK_CAPSLOCK);
  PyModule_AddIntConstant(my_mod, "SDLK_RSHIFT", SDLK_RSHIFT);
  PyModule_AddIntConstant(my_mod, "SDLK_LSHIFT", SDLK_LSHIFT);
  PyModule_AddIntConstant(my_mod, "SDLK_RCTRL", SDLK_RCTRL);
  PyModule_AddIntConstant(my_mod, "SDLK_LCTRL", SDLK_LCTRL);
#if SDL_MAJOR_VERSION > 1
  PyModule_AddIntConstant(my_mod, "SDLK_RGUI", SDLK_RGUI);
  PyModule_AddIntConstant(my_mod, "SDLK_LGUI", SDLK_LGUI);
#else
  PyModule_AddIntConstant(my_mod, "SDLK_RGUI", -1);
  PyModule_AddIntConstant(my_mod, "SDLK_LGUI", -1);
#endif
  PyModule_AddIntConstant(my_mod, "SDLK_RALT", SDLK_RALT);
  PyModule_AddIntConstant(my_mod, "SDLK_LALT", SDLK_LALT);
  PyModule_AddIntConstant(my_mod, "SDLK_MODE", SDLK_MODE);
  PyModule_AddIntConstant(my_mod, "SDLK_HELP", SDLK_HELP);
  PyModule_AddIntConstant(my_mod, "SDLK_SYSREQ", SDLK_SYSREQ);
  PyModule_AddIntConstant(my_mod, "SDLK_MENU", SDLK_MENU);
  PyModule_AddIntConstant(my_mod, "SDLK_POWER", SDLK_POWER);
  PyModule_AddIntConstant(my_mod, "SDLK_UNDO", SDLK_UNDO);

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_0", SDLK_0);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_0", SDL_SCANCODE_0);
#endif

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_1", SDLK_1);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_1", SDL_SCANCODE_1);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_2", SDLK_2);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_2", SDL_SCANCODE_2);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_3", SDLK_3);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_3", SDL_SCANCODE_3);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_4", SDLK_4);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_4", SDL_SCANCODE_4);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_5", SDLK_5);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_5", SDL_SCANCODE_5);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_6", SDLK_6);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_6", SDL_SCANCODE_6);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_7", SDLK_7);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_7", SDL_SCANCODE_7);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_8", SDLK_8);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_8", SDL_SCANCODE_8);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_9", SDLK_9);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_9", SDL_SCANCODE_9);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_AMPERSAND", SDLK_AMPERSAND);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_AMPERSAND", SDL_SCANCODE_KP_AMPERSAND);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_AT", SDLK_AT);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_AT", SDL_SCANCODE_KP_AT);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_BACKSLASH", SDLK_BACKSLASH);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_BACKSLASH", SDL_SCANCODE_BACKSLASH);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_BACKSPACE", SDLK_BACKSPACE);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_BACKSPACE", SDL_SCANCODE_BACKSPACE);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_COMMA", SDLK_COMMA);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_COMMA", SDL_SCANCODE_COMMA);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_DELETE", SDLK_DELETE);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_DELETE", SDL_SCANCODE_DELETE);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_EQUALS", SDLK_EQUALS);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_EQUALS", SDL_SCANCODE_EQUALS);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_ESCAPE", SDLK_ESCAPE);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_ESCAPE", SDL_SCANCODE_ESCAPE);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_GREATER", SDLK_GREATER);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_GREATER", SDL_SCANCODE_KP_GREATER);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_HASH", SDLK_HASH);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_HASH", SDL_SCANCODE_KP_HASH);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_LEFTBRACKET", SDLK_LEFTBRACKET);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_LEFTBRACKET", SDL_SCANCODE_LEFTBRACKET);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_LEFTPAREN", SDLK_LEFTPAREN);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_LEFTPAREN", SDL_SCANCODE_KP_LEFTPAREN);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_LESS", SDLK_LESS);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_LESS", SDL_SCANCODE_KP_LESS);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_MINUS", SDLK_MINUS);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_MINUS", SDL_SCANCODE_MINUS);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_PERIOD", SDLK_PERIOD);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_PERIOD", SDL_SCANCODE_PERIOD);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_PLUS", SDLK_PLUS);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_PLUS", SDL_SCANCODE_KP_PLUS);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_RETURN", SDLK_RETURN);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_RETURN", SDL_SCANCODE_RETURN);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_RIGHTBRACKET", SDLK_RIGHTBRACKET);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_RIGHTBRACKET", SDL_SCANCODE_RIGHTBRACKET);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_RIGHTPAREN", SDLK_RIGHTPAREN);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_RIGHTPAREN", SDL_SCANCODE_KP_RIGHTPAREN);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_SEMICOLON", SDLK_SEMICOLON);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_SEMICOLON", SDL_SCANCODE_SEMICOLON);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_SLASH", SDLK_SLASH);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_SLASH", SDL_SCANCODE_SLASH);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_SPACE", SDLK_SPACE);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_SPACE", SDL_SCANCODE_SPACE);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_TAB", SDLK_TAB);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_TAB", SDL_SCANCODE_TAB);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_A", SDLK_a);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_A", SDL_SCANCODE_A);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_B", SDLK_b);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_B", SDL_SCANCODE_B);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_C", SDLK_c);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_C", SDL_SCANCODE_C);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_D", SDLK_d);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_D", SDL_SCANCODE_D);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_E", SDLK_e);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_E", SDL_SCANCODE_E);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_F", SDLK_f);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_F", SDL_SCANCODE_F);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_G", SDLK_g);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_G", SDL_SCANCODE_G);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_H", SDLK_h);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_H", SDL_SCANCODE_H);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_I", SDLK_i);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_I", SDL_SCANCODE_I);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_J", SDLK_j);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_J", SDL_SCANCODE_J);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_K", SDLK_k);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_K", SDL_SCANCODE_K);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_L", SDLK_l);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_L", SDL_SCANCODE_L);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_M", SDLK_m);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_M", SDL_SCANCODE_M);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_N", SDLK_n);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_N", SDL_SCANCODE_N);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_O", SDLK_o);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_O", SDL_SCANCODE_O);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_P", SDLK_p);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_P", SDL_SCANCODE_P);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_Q", SDLK_q);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_Q", SDL_SCANCODE_Q);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_R", SDLK_r);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_R", SDL_SCANCODE_R);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_S", SDLK_s);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_S", SDL_SCANCODE_S);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_T", SDLK_t);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_T", SDL_SCANCODE_T);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_U", SDLK_u);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_U", SDL_SCANCODE_U);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_V", SDLK_v);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_V", SDL_SCANCODE_V);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_W", SDLK_w);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_W", SDL_SCANCODE_W);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_X", SDLK_x);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_X", SDL_SCANCODE_X);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_Y", SDLK_y);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_Y", SDL_SCANCODE_Y);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_Z", SDLK_z);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_Z", SDL_SCANCODE_Z);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_KP0", SDLk_KP0);
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_KP1", SDLK_KP1);
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_KP2", SDLk_KP2);
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_KP3", SDLK_KP3);
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_KP4", SDLK_KP4);
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_KP5", SDLK_KP5);
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_KP6", SDLK_KP6);
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_KP7", SDLK_KP7);
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_KP8", SDLK_KP8);
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_KP9", SDLK_KP9);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_KP0", SDLK_KP_0);
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_KP1", SDLK_KP_1);
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_KP2", SDLK_KP_2);
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_KP3", SDLK_KP_3);
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_KP4", SDLK_KP_4);
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_KP5", SDLK_KP_5);
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_KP6", SDLK_KP_6);
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_KP7", SDLK_KP_7);
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_KP8", SDLK_KP_8);
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_KP9", SDLK_KP_9);
#endif

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_KP_PERIOD", SDLK_KP_PERIOD);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_KP_PERIOD", SDL_SCANCODE_KP_PERIOD);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_KP_DIVIDE", SDLK_KP_DIVIDE);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_KP_DIVIDE", SDL_SCANCODE_KP_DIVIDE);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_KP_MULTIPLY", SDLK_KP_MULTIPLY);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_KP_MULTIPLY", SDL_SCANCODE_KP_MULTIPLY);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_KP_MINUS", SDLK_KP_MINUS);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_KP_MINUS", SDL_SCANCODE_KP_MINUS);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_KP_PLUS", SDLK_KP_PLUS);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_KP_PLUS", SDL_SCANCODE_KP_PLUS);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_KP_ENTER", SDLK_KP_ENTER);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_KP_ENTER", SDL_SCANCODE_KP_ENTER);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_KP_EQUALS", SDLK_KP_EQUALS);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_KP_EQUALS", SDL_SCANCODE_KP_EQUALS);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_UP", SDLK_UP);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_UP", SDL_SCANCODE_UP);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_DOWN", SDLK_DOWN);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_DOWN", SDL_SCANCODE_DOWN);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_RIGHT", SDLK_RIGHT);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_RIGHT", SDL_SCANCODE_RIGHT);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_LEFT", SDLK_LEFT);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_LEFT", SDL_SCANCODE_LEFT);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_INSERT", SDLK_INSERT);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_INSERT", SDL_SCANCODE_INSERT);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_HOME", SDLK_HOME);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_HOME", SDL_SCANCODE_HOME);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_END", SDLK_END);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_END", SDL_SCANCODE_END);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_PAGEUP", SDLK_PAGEUP);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_PAGEUP", SDL_SCANCODE_PAGEUP);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_PAGEDOWN", SDLK_PAGEDOWN);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_PAGEDOWN", SDL_SCANCODE_PAGEDOWN);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_F1", SDLK_F1);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_F1", SDL_SCANCODE_F1);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_F2", SDLK_F2);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_F2", SDL_SCANCODE_F2);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_F3", SDLK_F3);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_F3", SDL_SCANCODE_F3);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_F4", SDLK_F4);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_F4", SDL_SCANCODE_F4);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_F5", SDLK_F5);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_F5", SDL_SCANCODE_F5);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_F6", SDLK_F6);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_F6", SDL_SCANCODE_F6);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_F7", SDLK_F7);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_F7", SDL_SCANCODE_F7);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_F8", SDLK_F8);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_F8", SDL_SCANCODE_F8);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_F9", SDLK_F9);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_F9", SDL_SCANCODE_F9);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_F10", SDLK_F10);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_F10", SDL_SCANCODE_F10);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_F11", SDLK_F11);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_F11", SDL_SCANCODE_F11);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_F12", SDLK_F12);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_F12", SDL_SCANCODE_F12);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_F13", SDLK_F13);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_F13", SDL_SCANCODE_F13);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_F14", SDLK_F14);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_F14", SDL_SCANCODE_F14);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_F15", SDLK_F15);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_F15", SDL_SCANCODE_F15);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_CAPSLOCK", SDLK_CAPSLOCK);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_CAPSLOCK", SDL_SCANCODE_CAPSLOCK);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_RSHIFT", SDLK_RSHIFT);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_RSHIFT", SDL_SCANCODE_RSHIFT);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_LSHIFT", SDLK_LSHIFT);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_LSHIFT", SDL_SCANCODE_LSHIFT);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_RCTRL", SDLK_RCTRL);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_RCTRL", SDL_SCANCODE_RCTRL);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_LCTRL", SDLK_LCTRL);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_LCTRL", SDL_SCANCODE_LCTRL);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_RALT", SDLK_RALT);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_RALT", SDL_SCANCODE_RALT);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_LALT", SDLK_LALT);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_LALT", SDL_SCANCODE_LALT);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_MODE", SDLK_MODE);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_MODE", SDL_SCANCODE_MODE);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_HELP", SDLK_HELP);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_HELP", SDL_SCANCODE_HELP);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_SYSREQ", SDLK_SYSREQ);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_SYSREQ", SDL_SCANCODE_SYSREQ);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_MENU", SDLK_MENU);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_MENU", SDL_SCANCODE_MENU);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_POWER", SDLK_POWER);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_POWER", SDL_SCANCODE_POWER);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_UNDO", SDLK_UNDO);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_UNDO", SDL_SCANCODE_UNDO);
#endif /* } */
}
