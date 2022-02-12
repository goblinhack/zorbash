//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_color.hpp"
#include "my_game.hpp"
#include "my_gl.hpp"
#include "my_random.hpp"
#include "my_sprintf.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

int Thing::torch_count_get(void)
{
  TRACE_NO_INDENT();
  int torch_count = 0;

  for (const auto o : item_vector_get()) {
    if (! o->is_torch()) {
      continue;
    }

    if (o->charge_count_get()) {
      torch_count += o->charge_count_get();
    } else {
      torch_count++;
    }
  }

  return torch_count;
}

void Thing::light_power_including_torch_effect_get(uint8_t &out_light_power)
{
  TRACE_NO_INDENT();

  static Tpp torch;
  if (! torch) {
    torch = tp_find("torch");
  }

  int light_power = initial_light_power_get();

  if (is_player()) {
    light_power = 0;
  }

  int torch_count = torch_count_get();
  light_power += torch->light_power() * torch_count;

  auto max_distance = tp()->distance_vision();
  if (light_power > max_distance) {
    light_power = max_distance;
  }

  if (torch_count == 0) {
    if (is_player()) {
      light_power = 1;
    }
  }

  if (light_power < 0) {
    light_power = 0;
  }

  out_light_power = light_power;
}

void Thing::update_light_power_including_torch_effect(uint8_t &out_light_power)
{
  TRACE_NO_INDENT();
  uint8_t light_power;

  light_power_including_torch_effect_get(light_power);

  auto prev = prev_light_power_get();
  if (prev) {
    if (light_power != prev) {
      if (light_power <= 1) {
        msg("You are plunged into darkness.");
      } else if (light_power < prev) {
        msg("It gets darker...");
      }

      //
      // This causes a flicker and I slightly like that without
      // this you see a bit more of the level before it goes dark.
      //
      game->request_update_same_level = true;
    }
  }

  prev_light_power_set(light_power);
  out_light_power = light_power;
}
