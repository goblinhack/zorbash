//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_wid_topcon.h"
#include "my_wid_botcon.h"
#include "my_wid_popup.h"
#include "my_wid_thing_info.h"
#include "my_tile.h"
#include "my_wid_console.h"
#include "my_wid_bag.h"
#include "my_traceback.h"
#include "my_monst.h"
#include "my_thing.h"
#include "my_ui.h"

std::list<WidPopup *> wid_thing_info_window;

void wid_thing_info_fini (void)
{_
    if (game->bag_primary) {
        delete game->bag_primary;
        game->bag_primary = nullptr;
    }

    if (game->bag_secondary) {
        delete game->bag_secondary;
        game->bag_secondary = nullptr;
    }

    game->wid_thing_info_clear_popup();
}

uint8_t wid_thing_info_init (void)
{_
    return true;
}

void Game::wid_thing_info_destroy_immediate (void)
{_
    if (game->request_remake_inventory) {
        //
        // Continue
        //
    } else if (game->state == Game::STATE_COLLECTING_ITEMS) {
        return;
    } else if (game->state == Game::STATE_MOVING_ITEMS) {
        return;
    }

    wid_thing_info_fini();
}

void Game::wid_thing_info_destroy_deferred (void)
{_
    request_destroy_thing_info = time_get_time_ms_cached();
}

WidPopup *Game::wid_thing_info_create_popup (Thingp t, point tl, point br)
{_
    auto player = game->level->player;
    if (!player) {
        return nullptr;
    }

    auto tp = t->tp();
    auto tiles = &tp->tiles;
    auto tile = tile_first(tiles);
    if (!tile) {
        t->err("No tile for thing info");
        return nullptr;
    }

    auto wid_popup_window = new WidPopup("Thing info", tl, br, 
                                         nullptr, "", true, false);

    wid_popup_window->t = t;

    wid_raise(wid_popup_window->wid_popup_container);

    {_
        auto w = wid_new_plain(
                    wid_popup_window->wid_popup_container, "ui-circle");
        point tl = make_point(11 + 1, 1);
        point br = make_point(11 + 6, 6);
        wid_set_ignore_events(w, true);
        wid_set_pos(w, tl, br);
        wid_set_bg_tilename(w, "ui_circle");
        wid_set_color(w, WID_COLOR_BG, WHITE);
        wid_set_style(w, UI_WID_STYLE_SPARSE_NONE);
    }

    {_
        auto w = wid_new_plain(
                    wid_popup_window->wid_popup_container, "ui-circle");
        point tl = make_point(11 + 2, 2);
        point br = make_point(11 + 5, 5);
        wid_set_ignore_events(w, true);
        wid_set_pos(w, tl, br);
        wid_set_bg_tilename(w, "ui_tile_bg");
        wid_set_fg_tilename(w, tile->name);
        wid_set_color(w, WID_COLOR_BG, WHITE);
        wid_set_style(w, UI_WID_STYLE_SPARSE_NONE);
    }

    wid_popup_window->log(" ");
    wid_popup_window->log(" ");
    wid_popup_window->log(" ");
    wid_popup_window->log(" ");
    wid_popup_window->log(" ");
    wid_popup_window->log(" ");
    wid_popup_window->log(" ");

    wid_popup_window->log(tp->long_text_description());
    wid_popup_window->log(" ");

    wid_thing_info_add_item_rarity(wid_popup_window, t);
    wid_thing_info_add_monst_rarity(wid_popup_window, t);
    wid_thing_info_add_gold_value(wid_popup_window, t);
    wid_thing_info_add_nutrition(wid_popup_window, t);
    wid_thing_info_add_health(wid_popup_window, t);
    wid_thing_info_add_melee_damage(wid_popup_window, t);
    wid_thing_info_add_bite_damage(wid_popup_window, t);
    wid_thing_info_add_attack(wid_popup_window, t);
    wid_thing_info_add_defence(wid_popup_window, t);
    wid_thing_info_add_strength(wid_popup_window, t);
    wid_thing_info_add_constitution(wid_popup_window, t);
    wid_thing_info_add_charge_count(wid_popup_window, t);
    wid_thing_info_add_danger_level(wid_popup_window, t);
    t->show_botcon_description();

    return wid_popup_window;
}

WidPopup *Game::wid_thing_info_create_popup_compact (const std::vector<Thingp> &ts)
{_
    auto player = game->level->player;
    if (!player) {
        return nullptr;
    }

    auto height = TERM_HEIGHT - UI_TOPCON_VIS_HEIGHT;
    point tl = make_point(0, TERM_HEIGHT - 1 - height);
    point br = make_point(29, TERM_HEIGHT - 1);

    auto wid_popup_window = new WidPopup("Thing info", tl, br, 
                                         nullptr, "", false, false /* vert */);

    wid_raise(wid_popup_window->wid_popup_container);

    char tmp[40];

    for (auto t : ts) {
        auto name = t->short_text_capitalized();
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=white$%-28s%%fg=reset$", name.c_str());
        for (auto c = tmp; c < tmp + sizeof(tmp); c++) {
            if (*c == ' ') {
                *c = '`';
            }
        }
        wid_popup_window->log(tmp);

        wid_thing_info_add_item_rarity(wid_popup_window, t);
        wid_thing_info_add_monst_rarity(wid_popup_window, t);
        wid_thing_info_add_gold_value(wid_popup_window, t);
        wid_thing_info_add_nutrition(wid_popup_window, t);
        wid_thing_info_add_health(wid_popup_window, t);
        wid_thing_info_add_melee_damage(wid_popup_window, t);
        wid_thing_info_add_bite_damage(wid_popup_window, t);
        wid_thing_info_add_attack(wid_popup_window, t);
        wid_thing_info_add_defence(wid_popup_window, t);
        wid_thing_info_add_strength(wid_popup_window, t);
        wid_thing_info_add_constitution(wid_popup_window, t);
        wid_thing_info_add_charge_count(wid_popup_window, t);
        wid_thing_info_add_danger_level(wid_popup_window, t);
    }

    auto w = wid_popup_window;
    int utilized = w->wid_text_area->line_count;
    wid_move_delta(w->wid_popup_container, 0, height - utilized - 1);
    wid_resize(w->wid_popup_container, -1, utilized + 1);

    wid_update(w->wid_text_area->wid_text_area);
    wid_thing_info_window.push_back(wid_popup_window);

    return wid_popup_window;
}

bool Game::wid_thing_info_push_popup (Thingp t)
{_
    int existing_height = 0;
    for (const auto w : wid_thing_info_window) {
        existing_height += wid_get_height(w->wid_popup_container);

        if (w->t == t) {
            return true;
        }
    }

    if (t->long_text_description() == "") {
        return false;
    }

    auto height = TERM_HEIGHT - UI_TOPCON_VIS_HEIGHT;
    point tl = make_point(0, TERM_HEIGHT - 2 - height);
    point br = make_point(29, TERM_HEIGHT - 2);

    auto w = game->wid_thing_info_create_popup(t, tl, br);
    if (!w) {
        return false;
    }

    int utilized = w->wid_text_area->line_count;
    wid_move_delta(w->wid_popup_container, 0, height - utilized - existing_height - 1);
    wid_resize(w->wid_popup_container, -1, utilized + 1);

    for (auto w : wid_thing_info_window) {
        wid_update(w->wid_text_area->wid_text_area);
    }

    if (wid_get_tl_y(w->wid_popup_container) <= UI_TOPCON_VIS_HEIGHT) {
        delete w;
        return false;
    }

    wid_thing_info_window.push_back(w);
    return true;
}

void Game::wid_thing_info_clear_popup (void)
{_
    for (auto w : wid_thing_info_window) {
        delete w;
    }
    wid_thing_info_window.clear();
}

void Game::wid_thing_info_create (Thingp t, bool when_hovering_over)
{_
    if (game->request_remake_inventory) {
        //
        // Continue
        //
        t->log("Remake thing info");
    } else if (game->state == Game::STATE_COLLECTING_ITEMS) {
        t->err("Ignore, already collecting items");
        return;
    } else if (game->state == Game::STATE_MOVING_ITEMS) {
        t->log("Ignore, already moving items");
        return;
    }

    t->log("Make thing info");

    if (wid_console_window && wid_console_window->visible) {
        t->log("Console visible");
        return;
    }

    if (when_hovering_over) {
        if (!level->is_lit(t->mid_at.x, t->mid_at.y)) {
            t->log("Do not show thing; not lit");
            return;
        }
    }

    if (!wid_thing_info_window.empty()) {
        t->log("Destroy window");
        wid_thing_info_destroy_immediate();
    }

    request_destroy_thing_info = 0;

    auto player = game->level->player;
    if (!player){
        game->change_state(Game::STATE_NORMAL);
        ERR("No player");
        return;
    }

    static bool recursion;
    if (recursion) {
        DIE("Recursion");
    }
    recursion = true;

    t->log("Thing info create window");
    wid_thing_info_push_popup(t);

    //
    // Prefer to show the thing we are moving
    //
    if (game->in_transit_item) {
        auto id = wid_get_thing_id_context(game->in_transit_item);
        auto o = game->thing_find(id);
        if (o) {
            wid_thing_info_push_popup(o);
        }
    }

    auto tp = t->tp();
    if ((t->get_top_owner() == player) || (t == player)) {
        t->log("Thing info create bags");

        point mid(TERM_WIDTH / 2, TERM_HEIGHT - 1);

        if (bag_primary) {
            delete bag_primary;
            bag_primary = nullptr;
        }

        if (bag_secondary) {
            delete bag_secondary;
            bag_secondary = nullptr;
        }

        {
            point tl = mid - point(player->bag_width() + 5, player->bag_height() + 1);
            point br = tl +  point(player->bag_width(), player->bag_height());
            bag_primary = new WidBag(player, tl, br, "Inventory");
        }

        if (t->is_bag()) {
            point tl = mid + point(0, - (t->bag_height() + 1));
            point br = tl +  point(t->bag_width(), t->bag_height());
            if (tp->bag_width() * tp->bag_height() < 100) {
                bag_secondary = new WidBag(t, tl, br, "Small bag");
            } else {
                bag_secondary = new WidBag(t, tl, br, "Big bag");
            }
        }
    }

    recursion = false;
}

void Game::wid_thing_info_create (const std::vector<Thingp> &ts)
{_
    if (game->request_remake_inventory) {
        //
        // Continue
        //
        LOG("Remake thing info");
    } else if (game->state == Game::STATE_COLLECTING_ITEMS) {
        ERR("Ignore, already collecting items");
        return;
    } else if (game->state == Game::STATE_MOVING_ITEMS) {
        LOG("Ignore, already moving items");
        return;
    }

    LOG("Make thing info");

    if (wid_console_window && wid_console_window->visible) {
        LOG("Console visible");
        return;
    }

    wid_thing_info_destroy_immediate();
    request_destroy_thing_info = 0;

    auto player = game->level->player;
    if (!player){
        game->change_state(Game::STATE_NORMAL);
        ERR("No player");
        return;
    }

    static bool recursion;
    if (recursion) {
        DIE("Recursion");
    }
    recursion = true;

    LOG("Thing info create window");

    //
    // If too many items, use a compressed form
    //
    bool compact = false;
    if (ts.size() > 2) {
        compact = true;
    }

    if (!compact) {
        int i = 0;
        for (auto t : ts) {
            i++;
            if (!wid_thing_info_push_popup(t)) {
                wid_thing_info_fini();
                compact = true;
                break;
            }
        }
    }

    if (compact) {
        if (!wid_thing_info_create_popup_compact(ts)) {
            wid_thing_info_fini();
        }
    }

    recursion = false;
}

void Game::wid_thing_info_create_when_hovering_over (Thingp t)
{
    wid_thing_info_create(t, true);
}

void Game::wid_thing_info_create_when_hovering_over (const std::vector<Thingp> & ts)
{
    wid_thing_info_create(ts);
}

void Game::wid_thing_info_add_item_rarity (WidPopup *w, Thingp t) 
{_
    auto tp = t->tp();
    if (t->is_item()) {
        if (tp->rarity() == THING_RARITY_UNCOMMON) {
            w->log("Uncommon item");
        } else if (tp->rarity() == THING_RARITY_RARE) {
            w->log("Rare item");
        } else if (tp->rarity() == THING_RARITY_VERY_RARE) {
            w->log("Very rare item");
        } else if (tp->rarity() == THING_RARITY_UNIQUE) {
            w->log("Unique item");
        }
    }
}

void Game::wid_thing_info_add_monst_rarity (WidPopup *w, Thingp t) 
{_
    auto tp = t->tp();
    if (t->is_monst()) {
        if (tp->rarity() == THING_RARITY_UNCOMMON) {
            w->log("Uncommon monster");
        } else if (tp->rarity() == THING_RARITY_RARE) {
            w->log("Rare monster");
        } else if (tp->rarity() == THING_RARITY_VERY_RARE) {
            w->log("Very rare monster");
        } else if (tp->rarity() == THING_RARITY_UNIQUE) {
            w->log("Unique monster");
        }
    }
}

void Game::wid_thing_info_add_gold_value (WidPopup *w, Thingp t) 
{_
    char tmp[40];
    char tmp2[40];

    auto gold_value_dice = t->get_gold_value_dice();
    auto min_value = gold_value_dice.min_roll();
    auto max_value = gold_value_dice.max_roll();
    if (min_value > 0) {
        if (min_value == max_value) {
            snprintf(tmp2, sizeof(tmp2) - 1,
                     "(%s)",
                     t->get_gold_value_dice_str().c_str());
        } else {
            snprintf(tmp2, sizeof(tmp2) - 1,
                     "%d-%d(%s)",
                     min_value,
                     max_value,
                     t->get_gold_value_dice_str().c_str());
        }
        snprintf(tmp, sizeof(tmp) - 1,
                 "%%fg=gray$Gold  %15s ``````", tmp2);
        w->log(tmp);
    }
}

void Game::wid_thing_info_add_nutrition (WidPopup *w, Thingp t) 
{_
    char tmp[40];
    char tmp2[40];

    if (!game->level->player) {
        return;
    }

    if (game->level->player->can_eat(t)) {
        auto nutrition_dice = t->get_nutrition_dice();
        auto min_value = nutrition_dice.min_roll();
        auto max_value = nutrition_dice.max_roll();
        if (min_value > 0) {
            if (min_value == max_value) {
                snprintf(tmp2, sizeof(tmp2) - 1,
                         "(%s)",
                         t->get_nutrition_dice_str().c_str());
            } else {
                snprintf(tmp2, sizeof(tmp2) - 1,
                         "%d-%d(%s)",
                         min_value,
                         max_value,
                         t->get_nutrition_dice_str().c_str());
            }
            snprintf(tmp, sizeof(tmp) - 1,
                     "%%fg=gray$Food  %15s ``````", tmp2);
            w->log(tmp);
        }
    }
}

void Game::wid_thing_info_add_health (WidPopup *w, Thingp t) 
{_
    char tmp[40];
    char tmp2[40];

    if (t->is_alive_monst() || t->is_player()) {
        if (t->get_health() == t->get_health_max()) {
            snprintf(tmp, sizeof(tmp) - 1,
                     "%%fg=gray$Health%15d ``````", t->get_health());
        } else {
            snprintf(tmp2, sizeof(tmp2) - 1,
                     "%d/%d",
                     t->get_health(),
                     t->get_health_max());
            snprintf(tmp, sizeof(tmp) - 1,
                     "%%fg=gray$Health%15s ``````", tmp2);
        }
        w->log(tmp);
    }
}

void Game::wid_thing_info_add_melee_damage (WidPopup *w, Thingp t) 
{_
    char tmp[40];
    char tmp2[40];

    if (t->is_alive_monst() || t->is_player() || t->is_weapon()) {
        auto attack_melee_dice = t->get_damage_melee_dice();
        auto min_value = attack_melee_dice.min_roll();
        auto max_value = attack_melee_dice.max_roll();
        if (min_value > 0) {
            if (min_value == max_value) {
                snprintf(tmp2, sizeof(tmp2) - 1, "%s",
                         t->get_damage_melee_dice_str().c_str());
                snprintf(tmp, sizeof(tmp) - 1,
                         "%%fg=gray$Melee %15s ``````", tmp2);
            } else {
                snprintf(tmp2, sizeof(tmp2) - 1,
                         "%d-%d(%s)",
                         min_value,
                         max_value,
                         t->get_damage_melee_dice_str().c_str());
                snprintf(tmp, sizeof(tmp) - 1,
                         "%%fg=gray$Melee %15s ``````", tmp2);
            }
            w->log(tmp);
        }
    }
}

void Game::wid_thing_info_add_bite_damage (WidPopup *w, Thingp t) 
{_
    char tmp[40];
    char tmp2[40];

    if (t->is_alive_monst() || t->is_player()) {
        auto attack_bite_dice = t->get_damage_bite_dice();
        auto min_value = attack_bite_dice.min_roll();
        auto max_value = attack_bite_dice.max_roll();
        if (min_value > 0) {
            if (min_value == max_value) {
                snprintf(tmp2, sizeof(tmp2) - 1, "%s",
                         t->get_damage_bite_dice_str().c_str());
                snprintf(tmp, sizeof(tmp) - 1,
                         "%%fg=gray$Bite  %21s", tmp2);
            } else {
                snprintf(tmp2, sizeof(tmp2) - 1,
                         "%d-%d(%s)",
                         min_value,
                         max_value,
                         t->get_damage_bite_dice_str().c_str());
                snprintf(tmp, sizeof(tmp) - 1,
                         "%%fg=gray$Bite  %21s", tmp2);
            }
            w->log(tmp);
        }
    }
}

void Game::wid_thing_info_add_attack (WidPopup *w, Thingp t) 
{_
    char tmp[40];

    if (t->is_alive_monst() || t->is_player()) {
        auto stat = t->get_stat_attack();
        if (stat != 10) {
            snprintf(tmp, sizeof(tmp) - 1,
                    "%%fg=gray$Attack          %2d%-3s to dmg",
                    stat,
                    stat_to_bonus_slash_str(stat).c_str());
            w->log(tmp);
        } else {
            snprintf(tmp, sizeof(tmp) - 1,
                    "%%fg=gray$Attack          %2d/no bonus`",
                    stat);
            w->log(tmp);
        }
    }
}

void Game::wid_thing_info_add_defence (WidPopup *w, Thingp t) 
{_
    char tmp[40];

    if (t->is_alive_monst() || t->is_player()) {
        auto stat = t->get_stat_defence();
        if (stat != 10) {
            snprintf(tmp, sizeof(tmp) - 1,
                    "%%fg=gray$Defence         %2d%-3s to dmg",
                    stat,
                    stat_to_bonus_slash_str(stat).c_str());
            w->log(tmp);
        } else {
            snprintf(tmp, sizeof(tmp) - 1,
                    "%%fg=gray$Defence         %2d/no bonus`",
                    stat);
            w->log(tmp);
        }
    }
}

void Game::wid_thing_info_add_strength (WidPopup *w, Thingp t) 
{_
    char tmp[40];

    if (t->is_alive_monst() || t->is_player()) {
        auto stat = t->get_stat_strength();
        if (stat != 10) {
            snprintf(tmp, sizeof(tmp) - 1,
                    "%%fg=gray$Strength        %2d%-3s to dmg",
                    stat,
                    stat_to_bonus_slash_str(stat).c_str());
            w->log(tmp);
        } else {
            snprintf(tmp, sizeof(tmp) - 1,
                    "%%fg=gray$Strength        %2d/no bonus`",
                    stat);
            w->log(tmp);
        }
    }
}

void Game::wid_thing_info_add_constitution (WidPopup *w, Thingp t) 
{_
    char tmp[40];

    if (t->is_alive_monst() || t->is_player()) {
        auto stat = t->get_stat_constitution();
        if (stat != 10) {
            snprintf(tmp, sizeof(tmp) - 1,
                    "%%fg=gray$Constitution    %2d%-3s to dmg",
                    stat,
                    stat_to_bonus_slash_str(stat).c_str());
            w->log(tmp);
        } else {
            snprintf(tmp, sizeof(tmp) - 1,
                    "%%fg=gray$Constitution    %2d/no bonus`",
                    stat);
            w->log(tmp);
        }
    }
}

void Game::wid_thing_info_add_danger_level (WidPopup *w, Thingp t) 
{_
    auto player = game->level->player;
    if (!player) {
        return;
    }

    if (!t->is_alive_monst()) {
        return;
    }

    const std::string danger_level = player->get_danger_level_str(t);
    w->log(" ");
    w->log(danger_level);

    auto monst_max_damage = t->get_damage_max();
    if (monst_max_damage != 0) {
        auto monst_kill_count = player->get_health() / monst_max_damage;

        //
        // Oh dear. You my friend are toast.
        //
        if (monst_kill_count == 0) {
            monst_kill_count = 1;
        }

        if (monst_kill_count == 1) {
            w->log(" ");
            w->log("%%fg=red$Could kill you in " + std::to_string(monst_kill_count) + " hit!");
        } else if (monst_kill_count <= 2) {
            w->log(" ");
            w->log("%%fg=red$Could kill you in " + std::to_string(monst_kill_count) + " hits");
        } else if (monst_kill_count <= 10) {
            w->log(" ");
            w->log("%%fg=orange$Could kill you in " + std::to_string(monst_kill_count) + " hits");
        } else {
            w->log(" ");
            w->log("Could kill you eventually...");
        }
    }

    auto player_max_damage = t->get_damage_max();
    if (player_max_damage != 0) {
        auto player_kill_count = t->get_health() / player->get_damage_max();

        //
        // Oh dear. The monst is toast.
        //
        if (player_kill_count == 0) {
            player_kill_count = 1;
        }

        if (player_kill_count == 1) {
            w->log(" ");
            w->log("You could kill it in " + std::to_string(player_kill_count) + " hit!");
            w->log("More likely, " + std::to_string(player_kill_count * 2) + " hits");
        } else if (player_kill_count <= 2) {
            w->log(" ");
            w->log("You could kill it in " + std::to_string(player_kill_count) + " hits");
            w->log("More likely, " + std::to_string(player_kill_count * 2) + " hits");
        } else if (player_kill_count <= 10) {
            w->log(" ");
            w->log("You could kill it in " + std::to_string(player_kill_count) + " hits");
            w->log("More likely, " + std::to_string(player_kill_count * 2) + " hits");
        } else {
            w->log(" ");
            w->log("%%fg=red$It will take many hits to kill...");
        }
    }
}

void Game::wid_thing_info_add_charge_count (WidPopup *w, Thingp t) 
{_
    char tmp[40];
    char tmp2[40];

    auto player = game->level->player;
    if (!player) {
        return;
    }

    auto tp = t->tp();
    if (tp->charge_count()) {
        auto c = player->item_count_including_charges(t->tp());
        if (c > t->get_charge_count()) {
            snprintf(tmp2, sizeof(tmp2) - 1, "%d(%d tot)", t->get_charge_count(), c);
            snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Count %15s ``````", tmp2);
            w->log(tmp);
        } else {
            snprintf(tmp2, sizeof(tmp2) - 1, "%d", t->get_charge_count());
            snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Count %15s ``````", tmp2);
            w->log(tmp);
        }
    } else {
        auto c = player->item_count_including_charges(t->tp());
        if (c > 1) {
            snprintf(tmp2, sizeof(tmp2) - 1, "%d", c);
            snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Count %15s ``````", tmp2);
            w->log(tmp);
        }
    }
}
