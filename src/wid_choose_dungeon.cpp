//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include <SDL.h>
#include <map>

#include "my_array_bounds_check.hpp"
#include "my_color.hpp"
#include "my_game.hpp"
#include "my_main.hpp"
#include "my_math.hpp"
#include "my_ptrcheck.hpp"
#include "my_sys.hpp"
#include "my_template.hpp"
#include "my_thing.hpp"
#include "my_time.hpp"
#include "my_ui.hpp"
#include "my_wid.hpp"
#include "my_wid_choose_dungeon.hpp"
#include "my_wid_popup.hpp"

WidPopup *wid_level_contents;

void wid_show_dungeon_contents(Levelp l)
{
  TRACE_NO_INDENT();

  delete wid_level_contents;
  wid_level_contents = nullptr;

  std::map< std::string, int > monst_contents;
  std::map< std::string, int > treasure_contents;

  for (auto x = 0; x < MAP_WIDTH; x++) {
    for (auto y = 0; y < MAP_WIDTH; y++) {
      FOR_ALL_THINGS_THAT_INTERACT(l, t, x, y)
      {
        if (t->is_monst() || t->is_mob()) {
          monst_contents[ t->short_text_capitalise() ]++;
        }
        if (t->is_treasure()) {
          treasure_contents[ t->short_text_capitalise() ]++;
        }
      }
      FOR_ALL_THINGS_END();
    }
  }

  auto  total_size = monst_contents.size() + treasure_contents.size();
  point tl         = make_point(0, 3);
  point br         = make_point(40, total_size + 6);

  wid_level_contents = new WidPopup("Contents", tl, br, nullptr, "", true, false);
  wid_level_contents->log("%%fg=" UI_TEXT_HIGHLIGHT_COLOR_STR "$Contents");
  wid_level_contents->log(UI_LOGGING_EMPTY_LINE);

  char tmp[ MAXSHORTSTR ];
  {
    auto m = flip_map(monst_contents);
    for (auto p = m.rbegin(); p != m.rend(); ++p) {
      snprintf(tmp, sizeof(tmp) - 1, "%%fg=red$%d %s", p->first, p->second.c_str());
      wid_level_contents->log(tmp, true);
    }
  }
  {
    auto m = flip_map(treasure_contents);
    for (auto p = m.rbegin(); p != m.rend(); ++p) {
      snprintf(tmp, sizeof(tmp) - 1, "%%fg=gold$%d %s", p->first, p->second.c_str());
      wid_level_contents->log(tmp, true);
    }
  }

  wid_set_color(wid_level_contents->wid_popup_container, WID_COLOR_BG, GRAY30);
}
