//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

int Thing::torch_count(void)
{
  TRACE_NO_INDENT();
  int torch_count = 0;

  for (const auto o : item_vector()) {
    if (! o->is_torch()) {
      continue;
    }

    if (o->charge_count()) {
      torch_count += o->charge_count();
    } else {
      torch_count++;
    }
  }

  return torch_count;
}

void Thing::light_dist_including_torch_effect_get(uint8_t &out_light_dist)
{
  TRACE_NO_INDENT();

  static Tpp torch;
  if (! torch) {
    torch = tp_find("torch");
  }

  int light_dist = initial_light_dist_get();
  if (is_player()) {
    light_dist = 0;
  }

  int count = torch_count();
  light_dist += torch->light_dist() * count;

  auto max_distance = tp()->distance_vision();
  if (light_dist > max_distance) {
    light_dist = max_distance;
  }

  if (count == 0) {
    if (is_player()) {
      light_dist = 1;
    }
  }

  if (light_dist < 0) {
    light_dist = 0;
  }

  out_light_dist = light_dist;
}

void Thing::light_dist_update_including_torch_effect(uint8_t &out_light_dist)
{
  TRACE_NO_INDENT();
  uint8_t light_dist;

  light_dist_including_torch_effect_get(light_dist);

  auto prev = prev_light_dist_get();
  if (prev) {
    if (light_dist != prev) {
      if (light_dist <= 1) {
        msg("You are plunged into darkness.");
      } else if (light_dist < prev) {
        msg("It gets darker...");
      }

      //
      // This causes a flicker and I slightly like that without
      // this you see a bit more of the level before it goes dark.
      //
      game->request_update_same_level = true;
    }
  }

  prev_light_dist_set(light_dist);
  out_light_dist = light_dist;
}
