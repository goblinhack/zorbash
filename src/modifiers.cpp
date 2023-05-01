//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_dice.hpp"

// Roll -30 -> bonus -20
// Roll -29 -> bonus -19
// Roll -28 -> bonus -19
// Roll -27 -> bonus -18
// Roll -26 -> bonus -18
// Roll -25 -> bonus -17
// Roll -24 -> bonus -17
// Roll -23 -> bonus -16
// Roll -22 -> bonus -16
// Roll -21 -> bonus -15
// Roll -20 -> bonus -15
// Roll -19 -> bonus -14
// Roll -18 -> bonus -14
// Roll -17 -> bonus -13
// Roll -16 -> bonus -13
// Roll -15 -> bonus -12
// Roll -14 -> bonus -12
// Roll -13 -> bonus -11
// Roll -12 -> bonus -11
// Roll -11 -> bonus -10
// Roll -10 -> bonus -10
// Roll -9 ->  bonus -9
// Roll -8 ->  bonus -9
// Roll -7 ->  bonus -8
// Roll -6 ->  bonus -8
// Roll -5 ->  bonus -7
// Roll -4 ->  bonus -7
// Roll -3 ->  bonus -6
// Roll -2 ->  bonus -6
// Roll -1 ->  bonus -5
// Roll 0 ->   bonus -5
// Roll 1 ->   bonus -4
// Roll 2 ->   bonus -4
// Roll 3 ->   bonus -3
// Roll 4 ->   bonus -3
// Roll 5 ->   bonus -2
// Roll 6 ->   bonus -2
// Roll 7 ->   bonus -1
// Roll 8 ->   bonus -1
// Roll 9 ->   bonus +0
// Roll 10 ->  bonus +0
// Roll 11 ->  bonus +0
// Roll 12 ->  bonus +1
// Roll 13 ->  bonus +1
// Roll 14 ->  bonus +2
// Roll 15 ->  bonus +2
// Roll 16 ->  bonus +3
// Roll 17 ->  bonus +3
// Roll 18 ->  bonus +4
// Roll 19 ->  bonus +4
// Roll 20 ->  bonus +5
// Roll 21 ->  bonus +5
// Roll 22 ->  bonus +6
// Roll 23 ->  bonus +6
// Roll 24 ->  bonus +7
// Roll 25 ->  bonus +7
// Roll 26 ->  bonus +8
// Roll 27 ->  bonus +8
// Roll 28 ->  bonus +9
// Roll 29 ->  bonus +9
// Roll 30 ->  bonus +10
int stat_to_bonus(int stat)
{
  int bonus = (stat - 10) / 2;
  if (bonus < -20) {
    return -20;
  }
  if (bonus > 20) {
    return 20;
  }

#if 0
  //
  // Generate all rolls to see the bonus
  //
  static int first = true;
  if (first) {
    first = false;
    for (auto i = -30; i <= 30; i++) {
      printf("Roll %d -> bonus %d\n", i, stat_to_bonus(i));
    }
    DIE("See above rolls");
  }
#endif

  return bonus;
}

const std::string modifier_to_string(int stat)
{
  switch (stat) {
    case -20 : return "-20";
    case -19 : return "-19";
    case -18 : return "-18";
    case -17 : return "-17";
    case -16 : return "-16";
    case -15 : return "-15";
    case -14 : return "-14";
    case -13 : return "-13";
    case -12 : return "-12";
    case -11 : return "-11";
    case -10 : return "-10";
    case -9 : return "-9";
    case -8 : return "-8";
    case -7 : return "-7";
    case -6 : return "-6";
    case -5 : return "-5";
    case -4 : return "-4";
    case -3 : return "-3";
    case -2 : return "-2";
    case -1 : return "-1";
    case 0 : return "--";
    case 1 : return "+1";
    case 2 : return "+2";
    case 3 : return "+3";
    case 4 : return "+4";
    case 5 : return "+5";
    case 6 : return "+6";
    case 7 : return "+7";
    case 8 : return "+8";
    case 9 : return "+9";
    case 10 : return "+10";
    case 11 : return "+11";
    case 12 : return "+12";
    case 13 : return "+13";
    case 14 : return "+14";
    case 15 : return "+15";
    case 16 : return "+16";
    case 17 : return "+17";
    case 18 : return "+18";
    case 19 : return "+19";
    case 20 : return "+20";
    default : return "na";
  }
}

const std::string stat_to_bonus_string(int stat) { return modifier_to_string(stat_to_bonus(stat)); }

const std::string stat_to_bonus_slash_str(int stat)
{
  switch (stat_to_bonus(stat)) {
    case -20 : return "/-20";
    case -19 : return "/-19";
    case -18 : return "/-18";
    case -17 : return "/-17";
    case -16 : return "/-16";
    case -15 : return "/-15";
    case -14 : return "/-14";
    case -13 : return "/-13";
    case -12 : return "/-12";
    case -11 : return "/-11";
    case -10 : return "/-10";
    case -9 : return "/-9";
    case -8 : return "/-8";
    case -7 : return "/-7";
    case -6 : return "/-6";
    case -5 : return "/-5";
    case -4 : return "/-4";
    case -3 : return "/-3";
    case -2 : return "/-2";
    case -1 : return "/-1";
    case 0 : return "/--";
    case 1 : return "/+1";
    case 2 : return "/+2";
    case 3 : return "/+3";
    case 4 : return "/+4";
    case 5 : return "/+5";
    case 6 : return "/+6";
    case 7 : return "/+7";
    case 8 : return "/+8";
    case 9 : return "/+9";
    case 10 : return "/+10";
    case 11 : return "/+11";
    case 12 : return "/+12";
    case 13 : return "/+13";
    case 14 : return "/+14";
    case 15 : return "/+15";
    case 16 : return "/+16";
    case 17 : return "/+17";
    case 18 : return "/+18";
    case 19 : return "/+19";
    case 20 : return "/+20";
    default : return "/na";
  }
}
