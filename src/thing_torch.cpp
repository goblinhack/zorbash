//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_color.h"
#include "my_depth.h"
#include "my_dmap.h"
#include "my_game.h"
#include "my_gl.h"
#include "my_level.h"
#include "my_monst.h"
#include "my_random.h"
#include "my_sprintf.h"
#include "my_sys.h"
#include "my_thing.h"
#include "my_thing_template.h"

void Thing::get_light_strength_including_torch_effect(int &out_light_strength)
{
  TRACE_AND_INDENT();
  auto light_strength = get_initial_light_strength();

  auto torch_count = 0;

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

  if (torch_count < 6) {
    light_strength -= 7 - torch_count;
  }

  if (torch_count == 0) {
    light_strength = 1;
  }

  out_light_strength = light_strength;
}

void Thing::update_light_strength_including_torch_effect(int &out_light_strength)
{
  TRACE_AND_INDENT();
  auto orig_light_strength = out_light_strength;
  int  light_strength;

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
