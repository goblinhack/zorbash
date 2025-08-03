//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_serialize.hpp"
#include "my_thing.hpp"

HiScores::HiScores(void)
{
  TRACE_AND_INDENT();
  if ((int) hiscores.size() > HiScore::max) {
    hiscores.resize(HiScore::max);
  } else {
    while ((int) hiscores.size() < HiScore::max) {
      hiscores.push_back(HiScore("Thy place awaits thee", "",
                                 0, // score
                                 0, // level_reached
                                 ""));
    }
  }
}

HiScores::~HiScores(void) { TRACE_AND_INDENT(); }

void HiScores::add_new_hiscore(Thingp player, const std::string &name, const std::string &defeated_by)
{
  TRACE_AND_INDENT();
  auto        h = hiscores.begin();
  std::string hiscore_name;

  if (game->robot_mode) {
    hiscore_name = std::string("Robot ") + name;
  } else {
    hiscore_name = name;
  }

  while (h != hiscores.end()) {
    if (player->score() > h->score) {
      hiscores.insert(h, HiScore(hiscore_name, current_date(), player->score(), player->level->num(), defeated_by));

      hiscores.resize(HiScore::max);

      game->save_config();
      return;
    }

    h++;
  }
}

bool HiScores::is_new_hiscore(Thingp player)
{
  TRACE_AND_INDENT();
  auto h = hiscores.begin();

  if (! player->score()) {
    //
    // Poor player.
    //
    return false;
  }

  while (h != hiscores.end()) {
    if (player->score() > h->score) {
      return true;
    }
    h++;
  }

  return false;
}

bool HiScores::is_new_highest_hiscore(Thingp player)
{
  auto h = hiscores.begin();

  if (! player->score()) {
    //
    // Poor player.
    //
    return false;
  }

  while (h != hiscores.end()) {
    return player->score() > h->score;
  }
  return false;
}

const char *HiScores::place_str(Thingp player)
{
  const char *which[ HiScore::max_displayed ] = {
      "first", "second", "third", "fourth", "fifth", "sixth", "seventh", "eighth", "ninth", "tenth",
      "11th",  "12th",   "13th",  "14th",   "15th",  "16th",  "17th",    "18th",   "19th",  "20th",
  };

  if (! player->score()) {
    //
    // Poor player.
    //
    return ("");
  }

  auto h = hiscores.begin();

  while (h != hiscores.end()) {
    if (player->score() > h->score) {
      return (which[ h - hiscores.begin() ]);
    }
    h++;
  }
  return ("");
}

std::istream &operator>>(std::istream &in, Bits< HiScore & > my)
{
  TRACE_AND_INDENT();
  in >> bits(my.t.name);
  in >> bits(my.t.when);
  in >> bits(my.t.defeated_by);
  in >> bits(my.t.score);
  in >> bits(my.t.level_reached);
  if (my.t.defeated_by.empty()) {
    my.t.defeated_by = "No one";
  }
  return in;
}

std::ostream &operator<<(std::ostream &out, Bits< const HiScore & > const my)
{
  TRACE_AND_INDENT();
  out << bits(my.t.name);
  out << bits(my.t.when);
  out << bits(my.t.defeated_by);
  out << bits(my.t.score);
  out << bits(my.t.level_reached);
  // CON("Saved Hiscore: %s, %d defeated  by %s, %s",
  //     my.t.name.c_str(), my.t.score, my.t.defeated_by.c_str(), my.t.when.c_str());
  return out;
}

std::istream &operator>>(std::istream &in, Bits< HiScores & > my)
{
  TRACE_AND_INDENT();
  my.t.hiscores.resize(0);
  in >> bits(my.t.hiscores);
  for (auto h : my.t.hiscores) {
    DBG3("Loaded Hiscore: %s, %d killed by %s, %s", h.name.c_str(), h.score, h.defeated_by.c_str(), h.when.c_str());
  }

  return in;
}

std::ostream &operator<<(std::ostream &out, Bits< const HiScores & > const my)
{
  TRACE_AND_INDENT();
  out << bits(my.t.hiscores);
  return out;
}
