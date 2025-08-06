//
// Copyright goblinhack@gmail.com
//

#include "my_dice.hpp"
#include "my_main.hpp"
#include "my_python.hpp"
#include "my_string.hpp"
#include "my_thing.hpp"

//
// Return true if we exceed the target roll
//
bool d20_ge(int stat_total, const int dice_roll_to_exceed, bool &fumble, bool &critical)
{
  int dice_roll = pcg_random_range_inclusive(1, 20);

  critical = false;
  fumble   = false;

  if (dice_roll == 20) {
    critical = true;
    return true;
  }

  if (dice_roll == 1) {
    fumble = true;
    return false;
  }

  return dice_roll + stat_to_bonus(stat_total) >= dice_roll_to_exceed;
}

//
// Roll for stat modifier "a" to see if it beats "b"
//
bool d20_ge(int stat_total, const int dice_roll_to_exceed)
{
  int dice_roll = pcg_random_range_inclusive(1, 20);

  if (dice_roll == 20) {
    DBG("d20: rolled a 20 => success");
    return true;
  }

  if (dice_roll == 1) {
    DBG("d20: fumble");
    return false;
  }

  DBG("d20: %d(rolled %d+%d) >= %d", dice_roll + stat_to_bonus(stat_total), dice_roll, stat_to_bonus(stat_total),
      dice_roll_to_exceed);

  dice_roll += stat_to_bonus(stat_total);

  return dice_roll >= dice_roll_to_exceed;
}

bool Thing::d20_ge(int stat_total, const int dice_roll_to_exceed)
{
  int dice_roll = pcg_random_range_inclusive(1, 20);

  if (dice_roll == 20) {
    dbg("d20: rolled a 20 => success");
    return true;
  }

  if (dice_roll == 1) {
    dbg("d20: fumble");
    return false;
  }

  dbg("d20: %d(rolled %d+%d) >= %d", dice_roll + stat_to_bonus(stat_total), dice_roll, stat_to_bonus(stat_total),
      dice_roll_to_exceed);

  dice_roll += stat_to_bonus(stat_total);

  return dice_roll >= dice_roll_to_exceed;
}

Dice::Dice(void) = default;

std::string Dice::to_string(void) const { return hd; }

Dice::Dice(std::string s)
{
  hd = s;

  //
  // Allow python function after ":" so "1d1+1:fire.call_me()" is allowed
  //
  for (auto d : split_tokens(s, ':')) {
    std::size_t found = d.find("()");
    if (found != std::string::npos) {
      //
      // Parse the python function call
      //
      auto bare_func = d.replace(found, 2, "");
      auto sp        = split_tokens(bare_func, '.');
      if (sp.size() == 2) {
        //
        // <module>.<func>()
        //
        python_mod  = sp[ 0 ];
        python_func = sp[ 1 ];
      } else {
        //
        // <func>()
        //
        python_func = sp[ 0 ];
      }
    } else {
      //
      // 1d6+1
      //
      for (auto x : split_tokens(d, '+')) {
        auto sp = split_tokens(x, 'd');
        if (sp.size() == 2) {
          //
          // 1d6
          // ^
          ndice = std::stoi(sp[ 0 ]);
          //
          // 1d6
          //   ^
          //
          sides = std::stoi(sp[ 1 ]);
        } else {
          //
          // +1
          //
          modifier += std::stoi(sp[ 0 ]);
        }
        // CON("new dice %dd%d+%d", ndice, sides, modifier);
      }
    }
  }
}

int Dice::roll(void) const
{
  int n   = ndice;
  int tot = 0;
  // CON("roll %dd%d+%d", ndice, sides, modifier);
  while (n-- > 0) {
    tot += pcg_random_range(0, sides) + 1;
  }
  tot += modifier;
  // CON("roll %dd%d+%d => %d", ndice, sides, modifier, tot);
  return tot;
}

int Dice::max_roll(void) const { return ndice * sides + modifier; }

int Dice::min_roll(void) const { return ndice * 1 + modifier; }

bool Dice::crit_roll(void) const
{
  auto r = roll();
  return r >= (ndice * sides);
}

int Dice::operator()() const { return (roll()); }

int d10000(void) { return pcg_random_range_inclusive(1, 10000); }
int d1000(void) { return pcg_random_range_inclusive(1, 1000); }
int d100(void) { return pcg_random_range_inclusive(1, 100); }
int d10(void) { return pcg_random_range_inclusive(1, 10); }
int d11(void) { return pcg_random_range_inclusive(1, 11); }
int d12(void) { return pcg_random_range_inclusive(1, 12); }
int d13(void) { return pcg_random_range_inclusive(1, 13); }
int d14(void) { return pcg_random_range_inclusive(1, 14); }
int d15(void) { return pcg_random_range_inclusive(1, 15); }
int d16(void) { return pcg_random_range_inclusive(1, 16); }
int d17(void) { return pcg_random_range_inclusive(1, 17); }
int d18(void) { return pcg_random_range_inclusive(1, 18); }
int d19(void) { return pcg_random_range_inclusive(1, 19); }
int d20(void) { return pcg_random_range_inclusive(1, 20); }
int d2(void) { return pcg_random_range_inclusive(1, 2); }
int d3(void) { return pcg_random_range_inclusive(1, 3); }
int d4(void) { return pcg_random_range_inclusive(1, 4); }
int d50(void) { return pcg_random_range_inclusive(1, 50); }
int d5(void) { return pcg_random_range_inclusive(1, 5); }
int d6(void) { return pcg_random_range_inclusive(1, 6); }
int d7(void) { return pcg_random_range_inclusive(1, 7); }
int d8(void) { return pcg_random_range_inclusive(1, 8); }
int d9(void) { return pcg_random_range_inclusive(1, 9); }

PyObject *py_d10000(PyObject *obj, PyObject *args, PyObject *keywds) { return Py_BuildValue("i", d10000()); }
PyObject *py_d1000(PyObject *obj, PyObject *args, PyObject *keywds) { return Py_BuildValue("i", d1000()); }
PyObject *py_d100(PyObject *obj, PyObject *args, PyObject *keywds) { return Py_BuildValue("i", d100()); }
PyObject *py_d10(PyObject *obj, PyObject *args, PyObject *keywds) { return Py_BuildValue("i", d10()); }
PyObject *py_d11(PyObject *obj, PyObject *args, PyObject *keywds) { return Py_BuildValue("i", d11()); }
PyObject *py_d12(PyObject *obj, PyObject *args, PyObject *keywds) { return Py_BuildValue("i", d12()); }
PyObject *py_d13(PyObject *obj, PyObject *args, PyObject *keywds) { return Py_BuildValue("i", d13()); }
PyObject *py_d14(PyObject *obj, PyObject *args, PyObject *keywds) { return Py_BuildValue("i", d14()); }
PyObject *py_d15(PyObject *obj, PyObject *args, PyObject *keywds) { return Py_BuildValue("i", d15()); }
PyObject *py_d16(PyObject *obj, PyObject *args, PyObject *keywds) { return Py_BuildValue("i", d16()); }
PyObject *py_d17(PyObject *obj, PyObject *args, PyObject *keywds) { return Py_BuildValue("i", d17()); }
PyObject *py_d18(PyObject *obj, PyObject *args, PyObject *keywds) { return Py_BuildValue("i", d18()); }
PyObject *py_d19(PyObject *obj, PyObject *args, PyObject *keywds) { return Py_BuildValue("i", d19()); }
PyObject *py_d20(PyObject *obj, PyObject *args, PyObject *keywds) { return Py_BuildValue("i", d20()); }
PyObject *py_d2(PyObject *obj, PyObject *args, PyObject *keywds) { return Py_BuildValue("i", d2()); }
PyObject *py_d3(PyObject *obj, PyObject *args, PyObject *keywds) { return Py_BuildValue("i", d3()); }
PyObject *py_d4(PyObject *obj, PyObject *args, PyObject *keywds) { return Py_BuildValue("i", d4()); }
PyObject *py_d50(PyObject *obj, PyObject *args, PyObject *keywds) { return Py_BuildValue("i", d50()); }
PyObject *py_d5(PyObject *obj, PyObject *args, PyObject *keywds) { return Py_BuildValue("i", d5()); }
PyObject *py_d6(PyObject *obj, PyObject *args, PyObject *keywds) { return Py_BuildValue("i", d6()); }
PyObject *py_d7(PyObject *obj, PyObject *args, PyObject *keywds) { return Py_BuildValue("i", d7()); }
PyObject *py_d8(PyObject *obj, PyObject *args, PyObject *keywds) { return Py_BuildValue("i", d8()); }
PyObject *py_d9(PyObject *obj, PyObject *args, PyObject *keywds) { return Py_BuildValue("i", d9()); }
