//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_thing.hpp"

bool Thing::torch_tick(void)
{
  if (is_torch()) {
    return false;
  }

  if (is_monst() || is_player()) {
    return false;
  }

  if (is_able_to_melt() || is_burnable() || is_combustible() || is_very_combustible()) {
    //
    // Keep going
    //
  } else {
    return false;
  }

  if (! level->is_torch(curr_at)) {
    return false;
  }

  dbg("Torch hit");
  TRACE_AND_INDENT();

  if (! is_on_fire()) {
    on_fire_set("caught fire");
  }

  if (! level->is_smoke(curr_at)) {
    auto smoke = level->thing_new("smoke", curr_at);
    smoke->lifespan_set(pcg_random_range(1, 10));
  }

  return true;
}

int Thing::torch_count(void)
{
  TRACE_NO_INDENT();
  int torch_count = 0;

  for (const auto o : carried_item_only_vector()) {
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

//
// Get the light strength, taking into account the torch count
//
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

  //
  // Make torches brighter
  //
  light_dist += torch->light_dist() * count * 3;

  //
  // You can see further in the chasms
  //
  if (level->biome == BIOME_CHASMS) {
    light_dist *= 2;
  }

  auto max_distance = tp()->distance_vision();

  //
  // You can see further in the chasms
  //
  if (level->biome == BIOME_CHASMS) {
    max_distance *= 2;
  }

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

//
// Check for changes in our torch count
//
void Thing::light_distance_upd_with_torch_effect(uint8_t &out_light_dist)
{
  TRACE_NO_INDENT();
  uint8_t light_dist;

  light_dist_including_torch_effect_get(light_dist);

  auto prev = prev_light_dist_get();
  if (prev) {
    if (light_dist != prev) {
      if (light_dist <= 1) {
        msg("%%fg=red$Your last torch goes out. You are plunged into darkness!%%fg=reset$");
        if (is_on_fire()) {
          msg("Luckily, your burning body provides some light!");
        }
      } else if (light_dist < prev) {
        msg("One of your torches fizzles out. It gets darker...");
      }

      //
      // This causes a flicker and I slightly like that without
      // this you see a bit more of the level before it goes dark.
      //
      game->set_request_to_update_same_level();
    }
  }

  prev_light_dist_set(light_dist);
  out_light_dist = light_dist + (is_on_fire() ? 2 : 0);
}
