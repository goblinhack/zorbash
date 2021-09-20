//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
// Please use spaces indent of 2, no tabs and column width of 120 to view.
//

#include "my_sys.h"
#include "my_main.h"
#include "my_game.h"
#include "my_level.h"
#include "my_thing.h"
#include "my_hiscore.h"
#include "my_monst.h"
#include "my_ptrcheck.h"
#include "my_time.h"

HiScores::HiScores (void)
{_
  if ((int)hiscores.size() > HiScore::max) {
    hiscores.resize(HiScore::max);
  } else {
    while ((int)hiscores.size() < HiScore::max) {
      hiscores.push_back(HiScore("Thy place awaits thee",
                     "",
                     0, // score
                     0, // level_reached
                     ""));
    }
  }
}

HiScores::~HiScores (void)
{_
}

void HiScores::add_new_hiscore (Thingp player,
                const std::string &name,
                const std::string &killed_by)
{_
  std::vector<HiScore>::iterator h = hiscores.begin();
  std::string hiscore_name;

  if (game->robot_mode) {
    hiscore_name = std::string("Robot ") + name;
  } else {
    hiscore_name = name;
  }

  while (h != hiscores.end()) {
    if (player->get_score() > h->score) {
      hiscores.insert(h,
        HiScore(
          hiscore_name,
          current_date(),
          player->get_score(),
          (player->level->world_at.z + 1) / 2,
          killed_by));

      hiscores.resize(HiScore::max);

      game->save_config();
      return;
    }

    h++;
  }
}

bool HiScores::is_new_hiscore (Thingp player)
{_
  std::vector<HiScore>::iterator h = hiscores.begin();

  if (!player->get_score()) {
    //
    // Poor player.
    //
    return false;
  }

  while (h != hiscores.end()) {
    if (player->get_score() > h->score) {
      return true;
    }
    h++;
  }

  return false;
}

bool HiScores::is_new_highest_hiscore (Thingp player)
{
  std::vector<HiScore>::iterator h = hiscores.begin();

  if (!player->get_score()) {
    //
    // Poor player.
    //
    return false;
  }

  while (h != hiscores.end()) {
    if (player->get_score() > h->score) {
      return true;
    }
    return false;
  }
  return false;
}

const char *HiScores::place_str (Thingp player)
{
  const char *which[HiScore::max_displayed] = {
    "first",
    "second",
    "third",
    "fourth",
    "fifth",
    "sixth",
    "seventh",
    "eighth",
    "nineth",
    "tenth",
    "11th",
    "12th",
    "13th",
    "14th",
    "15th",
    "16th",
    "17th",
    "18th",
    "19th",
    "20th",
  };

  if (!player->get_score()) {
    //
    // Poor player.
    //
    return ("");
  }

  std::vector<HiScore>::iterator h = hiscores.begin();

  while (h != hiscores.end()) {
    if (player->get_score() > h->score) {
      return (which[h-hiscores.begin()]);
    }
    h++;
  }
  return ("");
}

std::istream& operator>>(std::istream &in, Bits<HiScore &> my)
{_
  in >> bits(my.t.name);
  in >> bits(my.t.when);
  in >> bits(my.t.killed_by);
  in >> bits(my.t.score);
  in >> bits(my.t.level_reached);
  if (my.t.killed_by.empty()) {
    my.t.killed_by = "No one";
  }
  return in;
}

std::ostream& operator<<(std::ostream &out, Bits<const HiScore & > const my)
{_
  out << bits(my.t.name);
  out << bits(my.t.when);
  out << bits(my.t.killed_by);
  out << bits(my.t.score);
  out << bits(my.t.level_reached);
  // CON("Saved Hiscore: %s, %d killed by %s, %s",
  //     my.t.name.c_str(), my.t.score, my.t.killed_by.c_str(), my.t.when.c_str());
  return (out);
}

std::ostream& operator<<(std::ostream &out, Bits<HiScore &> const my)
{_
  out << bits(my.t.name);
  out << bits(my.t.when);
  out << bits(my.t.killed_by);
  out << bits(my.t.score);
  out << bits(my.t.level_reached);
  // CON("Read Hiscore: %s, %d killed by %s, %s",
  //     my.t.name.c_str(), my.t.score, my.t.killed_by.c_str(), my.t.when.c_str());
  return (out);
}

std::istream& operator>>(std::istream &in, Bits<HiScores &> my)
{_
  my.t.hiscores.resize(0);
  in >> bits(my.t.hiscores);
  for (auto h : my.t.hiscores) {
    DBG3("Loaded Hiscore: %s, %d killed by %s, %s",
       h.name.c_str(), h.score, h.killed_by.c_str(), h.when.c_str());
  }

  return in;
}

std::ostream& operator<<(std::ostream &out, Bits<const HiScores & > const my)
{_
  out << bits(my.t.hiscores);
  return (out);
}
