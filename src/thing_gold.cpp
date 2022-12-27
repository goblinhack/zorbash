//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_sound.hpp"
#include "my_thing.hpp"

const Dice &Thing::gold_value_dice(void)
{
  TRACE_NO_INDENT();
  return (tp()->gold_value_dice());
}

const std::string &Thing::gold_value_dice_str(void)
{
  TRACE_NO_INDENT();
  return (tp()->gold_value_dice_str());
}

int Thing::gold_value(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! _infop)) {
    new_infop();
  }
  if (infop()->gold == -1) {
    infop()->gold = tp()->gold_value_dice().roll();
  }
  return infop()->gold;
}

int Thing::is_collected_as_gold(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_collected_as_gold());
}

int Thing::is_gold(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_gold());
}

int Thing::gold(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->gold);
  }
  return 0;
}

int Thing::gold_set(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->gold = v);
  return n;
}

int Thing::gold_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->gold -= v);
  if (infop()->gold < 0) {
    infop()->gold = 0;
  }
  return n;
}

int Thing::gold_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->gold += v);
  sound_play("gold");
  return n;
}

int Thing::gold_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->gold--);
  if (infop()->gold < 0) {
    infop()->gold = 0;
  }
  return n;
}

int Thing::gold_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->gold++);
  sound_play("gold");
  return n;
}
