//
// Copyright goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_thing.hpp"

//
// Lower level function than dead. Adds the thing to gc.
//
void Thing::score_add(Thingp victim)
{
  TRACE_NO_INDENT();

  if (! is_player()) {
    return;
  }

  if (victim->is_monst()) {
    auto score = danger_initial_level(victim);
    if (score > 0) {
      if (health() < health_max() / 10) {
        if (is_player()) {
          popup("%%fg=red$Glory defeat x10 score!%%fg=reset$");
        }
        score_incr(score * 10);
      } else {
        score_incr(score);
      }
    } else {
      //
      // Give something, but not a lot as it was not a challenge
      //
      score_incr(victim->health_max());
    }
  }
}

////////////////////////////////////////////////////////////////////////////
// score
////////////////////////////////////////////////////////////////////////////
int Thing::score(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->score);
  }
  return 0;
}

int Thing::score_set(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  return infop()->score = v;
}

int Thing::score_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  return infop()->score += v;
}

int Thing::score_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  infop()->score -= v;

  if (infop()->score < 0) {
    infop()->score = 0;
  }

  return infop()->score;
}
