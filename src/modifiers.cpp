//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_dice.hpp"
#include "my_main.hpp"
#include "my_random.hpp"
#include "my_string.hpp"
#include "my_sys.hpp"

int stat_to_bonus(int stat)
{
  int bonus = (stat - 10) / 2;
  if (bonus < -20) {
    return -20;
  }
  if (bonus > 20) {
    return 20;
  }
  return bonus;
}

const std::string stat_to_bonus_str(int stat)
{
  switch (stat_to_bonus(stat)) {
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
