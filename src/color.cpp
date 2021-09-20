//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include <strings.h> // do not remove, strcasecmp
#include <string.h> // do not remove
#include "my_sys.h"
#include "my_gl.h"
#include "my_ui.h"
#include "my_string.h"
#include "my_main.h"

typedef std::map< std::string, color > colors;

colors color_map;
static bool color_init_done;

void color_set (std::string name,
        color *c,
        uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{_
  c->r = r;
  c->g = g;
  c->b = b;
  c->a = a;

  auto result = color_map.insert(std::make_pair(name, *c));
  if (result.second == false) {
    ERR("Color insert name [%s] failed", name.c_str());
  }
}

void color_init (void)
{_
  color_init1();
  color_init2();
  color_init3();
  color_init4();
  color_init_done = true;
}

void color_fini (void)
{_
  color_map.clear();
}

color gl_save_color(255, 255, 255, 255);
color gl_last_color(255, 255, 255, 255);

void glcolor_save (void)
{_
  gl_save_color = gl_last_color;
}

void glcolor_restore (void)
{_
  color s = gl_last_color = gl_save_color;

  glColor4ub(s.r, s.g, s.b, s.a);
}

color gl_color_current (void)
{
  return (gl_last_color);
}

color string2color (const char **s)
{_
  static char tmp[MAXSHORTSTR];
  static const char *eo_tmp = tmp + sizeof(tmp);
  const char *c = *s;
  char *t = tmp;

  while (t < eo_tmp) {
    if ((*c == '\0') || (*c == '$')) {
      break;
    }

    *t++ = *c++;
  }

  if (c == eo_tmp) {
    return (WHITE);
  }

  *t++ = '\0';
  *s += (t - tmp);

  if (!strcasecmp(tmp, "reset")) {
    return (UI_TEXT_COLOR);
  }

  auto result = color_map.find(std::string(tmp));

  if (result == color_map.end()) {
    if (color_init_done) { // avoids color warnings due to very early errors
      LOG("Unknown color [%s]", tmp);
    }
    return (WHITE);
  }

  return (result->second);
}

color string2color (const wchar_t **s)
{_
  static wchar_t tmp[MAXSHORTSTR];
  static const wchar_t *eo_tmp = tmp + MAXSHORTSTR - 1;
  const wchar_t *c = *s;
  wchar_t *t = tmp;

  while (t < eo_tmp) {
    if ((*c == '\0') || (*c == '$')) {
      break;
    }

    *t++ = *c++;
  }

  if (c == eo_tmp) {
    return (WHITE);
  }

  *t++ = '\0';
  *s += (t - tmp);

  if (!wcscmp(tmp, L"reset")) {
    return (UI_TEXT_COLOR);
  }

  std::string f = wstring_to_string(std::wstring(tmp));
  auto result = color_map.find(f);

  if (result == color_map.end()) {
    if (color_init_done) { // avoids color warnings due to very early errors
      LOG("Unknown color [%s]", f.c_str());
    }
    return (WHITE);
  }

  return (result->second);
}

color string2color (std::string &s, int *len)
{_
  auto iter = s.begin();
  std::string out;

  while (iter != s.end()) {
    auto c = *iter;

    if ((c == '\0') || (c == '$')) {
      break;
    }

    out += c;
    iter++;
  }

  if (len) {
    *len = iter - s.begin();
  }

  if (out == "reset") {
    return (UI_TEXT_COLOR);
  }

  auto result = color_map.find(out);

  if (result == color_map.end()) {
    if (color_init_done) { // avoids color warnings due to very early errors
      LOG("Unknown color [%s]", out.c_str());
    }
    return (WHITE);
  }

  return (result->second);
}

color string2color (std::string &s)
{
  auto iter = s.begin();
  std::string out;

  while (iter != s.end()) {
    auto c = *iter;

    if ((c == '\0') || (c == '$')) {
      break;
    }

    out += c;
    iter++;
  }

  if (out == "reset") {
    return (UI_TEXT_COLOR);
  }

  auto result = color_map.find(out);

  if (result == color_map.end()) {
    if (color_init_done) { // avoids color warnings due to very early errors
      LOG("Unknown color [%s]", out.c_str());
    }
    return (WHITE);
  }

  return (result->second);
}

color string2color (std::wstring &s, int *len)
{_
  auto v = wstring_to_string(s);
  return (string2color(v, len));
}

const char *string2colorname (const char **s)
{_
  static char tmp[MAXSHORTSTR];
  static const char *eo_tmp = tmp + MAXSHORTSTR - 1;
  const char *c = *s;
  char *t = tmp;

  while (t < eo_tmp) {
    if ((*c == '\0') || (*c == '$')) {
      break;
    }

    *t++ = *c++;
  }

  if (c == eo_tmp) {
    return (0);
  }

  *t++ = '\0';
  *s += (t - tmp);

  if (!strcasecmp(tmp, "reset")) {
    return (UI_TEXT_COLOR_STR);
  }

  auto result = color_map.find(std::string(tmp));

  if (result == color_map.end()) {
    if (color_init_done) { // avoids color warnings due to very early errors
      LOG("Unknown color [%s]", tmp);
    }
    return ("");
  }

  return (tmp);
}

std::string string2colorname (std::string &s)
{_
  auto iter = s.begin();
  std::string out;

  if (s == "") {
    return ("white");
  }

  while (iter != s.end()) {
    auto c = *iter;

    if ((c == '\0') || (c == '$')) {
      break;
    }

    out += c;
    iter++;
  }

  if (out == "reset") {
    return (UI_TEXT_COLOR_STR);
  }

  auto result = color_map.find(out);

  if (result == color_map.end()) {
    if (color_init_done) { // avoids color warnings due to very early errors
      LOG("Unknown color [%s]", out.c_str());
    }
    return ("");
  }

  return (out);
}

color color_find (const char *s)
{_
  if (!s) {
    return (WHITE);
  }

  if (!strcmp(s, "")) {
    return (WHITE);
  }

  auto result = color_map.find(std::string(s));

  if (result == color_map.end()) {
    if (color_init_done) { // avoids color warnings due to very early errors
      LOG("Unknown color [%s]", s);
    }
    return (WHITE);
  }

  return (result->second);
}

color color_to_mono (color a)
{_
  float avg = (a.r + a.g + a.b) / 3.0;

  a.r = avg;
  a.g = avg;
  a.b = avg;

  return (a);
}
