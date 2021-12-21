//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_color.hpp"
#include "my_depth.hpp"
#include "my_game.hpp"
#include "my_gl.hpp"
#include "my_level.hpp"
#include "my_monst.hpp"
#include "my_random.hpp"
#include "my_sprintf.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

int Thing::get_torch_count(void)
{
  TRACE_NO_INDENT();
  int torch_count = 0;

  for (const auto o : get_item_vector()) {
    if (! o->is_torch()) {
      continue;
    }

    if (o->get_charge_count()) {
      torch_count += o->get_charge_count();
    } else {
      torch_count++;
    }
  }

  return torch_count;
}

void Thing::get_light_strength_including_torch_effect(uint8_t &out_light_strength)
{
  TRACE_NO_INDENT();
  int light_strength = get_initial_light_strength();
  int torch_count    = get_torch_count();

  if (torch_count < 6) {
    light_strength -= 7 - torch_count;
  }

  if (torch_count == 0) {
    if (is_player()) {
      light_strength = 1;
    }
  }

  if (light_strength < 0) {
    light_strength = 0;
  }

  out_light_strength = light_strength;
}

void Thing::update_light_strength_including_torch_effect(uint8_t &out_light_strength)
{
  TRACE_NO_INDENT();
  uint8_t orig_light_strength = out_light_strength;
  uint8_t light_strength;

  get_light_strength_including_torch_effect(light_strength);

  if (orig_light_strength) {
    if (light_strength != orig_light_strength) {
      if (light_strength <= 1) {
        TOPCON("You are plunged into darkness.");
      } else if (light_strength < orig_light_strength) {
        TOPCON("It gets darker...");
      }

      //
      // This causes a flicker and I slightly like that without
      // this you see a bit more of the level before it goes dark.
      //
      game->request_update_same_level = true;
    }
  }

  out_light_strength = light_strength;
}
