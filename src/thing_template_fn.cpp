//
// Copyright goblinhack@gmail.com
//

#include "my_thing_template.hpp"

bool Tp::has_temperature(void) { return _has_temperature; }

void Tp::temperature_set(int v)
{
  _temperature = v;
  if (! _initial_temperature_set) {
    _initial_temperature_set = true;
    _initial_temperature     = v;
  }
  _has_temperature = true;
}

void Tp::temperature_max_set(int v)
{
  _temperature_max_set = true;
  _temperature_max     = v;
}
void Tp::temperature_min_set(int v)
{
  _temperature_min_set = true;
  _temperature_min     = v;
}

bool Tp::initial_temperature_is_set(void) const { return _initial_temperature_set; }
bool Tp::temperature_min_is_set(void) const { return _temperature_min_set; }
bool Tp::temperature_max_is_set(void) const { return _temperature_max_set; }

