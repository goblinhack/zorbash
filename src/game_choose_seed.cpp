//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include <SDL_mixer.h>
#include "my_sys.h"
#include "my_game.h"
#include "my_globals.h"
#include "my_wid_popup.h"
#include "my_wid_rightbar.h"
#include "my_wid_leftbar.h"
#include "my_wid_inventory.h"
#include "my_wid_skillbox.h"
#include "my_wid_thing_info.h"
#include "my_wid_thing_collect.h"
#include "my_wid_keyboard.h"
#include "my_string.h"
#include "my_sdl.h"
#include "my_wid.h"
#include "my_ui.h"

static Widp wid_keyboard_choose_seed;

static void selected (Widp w, const std::wstring& text)
{
    wid_destroy(&wid_keyboard_choose_seed);
    g_opt_seed_name = wstring_to_string(text);
    game->save_config();
    game->main_menu_select();
}

static void cancelled (Widp w, const std::wstring& text)
{
    wid_destroy(&wid_keyboard_choose_seed);
    game->main_menu_select();
}

void Game::choose_seed_select (void)
{_
    CON("Choose seed menu");

    wid_rightbar_fini();
    wid_leftbar_fini();
    wid_inventory_fini();
    wid_skillbox_fini();
    wid_thing_info_fini();
    wid_thing_collect_fini();

    wid_keyboard_choose_seed = 
        wid_keyboard(string_to_wstring(g_opt_seed_name),
                     L"Enter a name or number for the dungeon seed", selected, cancelled);
}
