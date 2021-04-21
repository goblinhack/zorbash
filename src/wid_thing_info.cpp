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

    BOTCON(" "); // Clear out existing message
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
        point tl = make_point(12 + 1, 1);
        point br = make_point(12 + 4, 4);
        wid_set_ignore_events(w, true);
        wid_set_pos(w, tl, br);
        wid_set_bg_tilename(w, "ui_circle");
        wid_set_color(w, WID_COLOR_BG, WHITE);
        wid_set_style(w, UI_WID_STYLE_SPARSE_NONE);
    }

    {_
        auto w = wid_new_plain(
                    wid_popup_window->wid_popup_container, "ui-circle");
        point tl = make_point(12 + 2, 2);
        point br = make_point(12 + 3, 3);
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
    wid_popup_window->log(" ");

    wid_popup_window->log(tp->long_text_description());

    if (t->is_item()) {
        if (tp->rarity() == THING_RARITY_UNCOMMON) {
            wid_popup_window->log("Uncommon item");
        } else if (tp->rarity() == THING_RARITY_RARE) {
            wid_popup_window->log("Rare item");
        } else if (tp->rarity() == THING_RARITY_VERY_RARE) {
            wid_popup_window->log("Very rare item");
        } else if (tp->rarity() == THING_RARITY_UNIQUE) {
            wid_popup_window->log("Unique item");
        }
    }

    if (t->is_monst()) {
        if (tp->rarity() == THING_RARITY_UNCOMMON) {
            wid_popup_window->log("Uncommon monster");
        } else if (tp->rarity() == THING_RARITY_RARE) {
            wid_popup_window->log("Rare monster");
        } else if (tp->rarity() == THING_RARITY_VERY_RARE) {
            wid_popup_window->log("Very rare monster");
        } else if (tp->rarity() == THING_RARITY_UNIQUE) {
            wid_popup_window->log("Unique monster");
        }
    }

    bool need_line = true;

    {
        auto gold_dice = t->get_gold_value_dice();
        auto min_value = gold_dice.min_roll();
        auto max_value = gold_dice.max_roll();
        if (min_value > 0) {
            if (need_line) {
                wid_popup_window->log(" ");
                need_line = false;
            }
            if (min_value == max_value) {
                wid_popup_window->log("%%fg=white$Gold value " + 
                                        t->get_gold_value_dice_str());
            } else {
                wid_popup_window->log("%%fg=white$Gold value " + 
                                        std::to_string(min_value) + "-" + 
                                        std::to_string(max_value) + " (" +
                                        t->get_gold_value_dice_str() + ")");
            }
        }
    }

    if (player->can_eat(t)) {
        auto nutrition_dice = t->get_nutrition_dice();
        auto min_value = nutrition_dice.min_roll();
        auto max_value = nutrition_dice.max_roll();
        if (min_value > 0) {
            if (need_line) {
                wid_popup_window->log(" ");
                need_line = false;
            }
            if (min_value == max_value) {
                wid_popup_window->log("%%fg=white$Nutrition " + 
                                      t->get_nutrition_dice_str());
            } else {
                wid_popup_window->log("%%fg=white$Nutrition " + 
                                      std::to_string(min_value) + "-" + 
                                      std::to_string(max_value) + " (" + 
                                      t->get_nutrition_dice_str() + ")");
            }
        }
    }
    
    char tmp[40];
    char tmp2[40];

    if (t->is_alive_monst() || t->is_player()) {
        if (need_line) {
            wid_popup_window->log(" ");
            need_line = false;
        }
        if (t->get_health() == t->get_health_max()) {
            snprintf(tmp, sizeof(tmp) - 1,
                     "%%fg=white$Health%15d ``````", t->get_health());
        } else {
            snprintf(tmp2, sizeof(tmp2) - 1,
                     "%d/%d",
                     t->get_health(),
                     t->get_health_max());
            snprintf(tmp, sizeof(tmp) - 1,
                     "%%fg=white$Health%15s ``````", tmp2);
        }
        wid_popup_window->log(tmp);
    }

    if (t->is_alive_monst() || t->is_player() || t->is_weapon()) {
        auto attack_melee_dice = t->get_damage_melee_dice();
        auto min_value = attack_melee_dice.min_roll();
        auto max_value = attack_melee_dice.max_roll();
        if (min_value > 0) {
            if (need_line) {
                wid_popup_window->log(" ");
                need_line = false;
            }
            if (min_value == max_value) {
                snprintf(tmp2, sizeof(tmp2) - 1, "%s",
                         t->get_damage_melee_dice_str().c_str());
                snprintf(tmp, sizeof(tmp) - 1,
                         "%%fg=white$Damage%15s ``````", tmp2);
            } else {
                snprintf(tmp2, sizeof(tmp2) - 1,
                         "%d-%d(%s)",
                         min_value,
                         max_value,
                         t->get_damage_melee_dice_str().c_str());
                snprintf(tmp, sizeof(tmp) - 1,
                         "%%fg=white$Damage%15s ``````", tmp2);
            }
            wid_popup_window->log(tmp);
        }
    }

    if (t->is_alive_monst() || t->is_player()) {
        auto attack_bite_dice = t->get_damage_bite_dice();
        auto min_value = attack_bite_dice.min_roll();
        auto max_value = attack_bite_dice.max_roll();
        if (min_value > 0) {
            if (need_line) {
                wid_popup_window->log(" ");
                need_line = false;
            }
            if (min_value == max_value) {
                snprintf(tmp2, sizeof(tmp2) - 1, "%s",
                         t->get_damage_bite_dice_str().c_str());
                snprintf(tmp, sizeof(tmp) - 1,
                         "%%fg=white$Bite  %21s", tmp2);
            } else {
                snprintf(tmp2, sizeof(tmp2) - 1,
                         "%d-%d(%s)",
                         min_value,
                         max_value,
                         t->get_damage_bite_dice_str().c_str());
                snprintf(tmp, sizeof(tmp) - 1,
                         "%%fg=white$Bite  %21s", tmp2);
            }
            wid_popup_window->log(tmp);
        }
    }

    if (t->is_alive_monst() || t->is_player()) {
        {
            auto stat = t->get_stat_attack();
            if (stat != 10) {
                snprintf(tmp, sizeof(tmp) - 1,
                        "%%fg=white$Attack          %2d%-3s to dmg",
                        stat,
                        stat_to_bonus_slash_str(stat).c_str());
                wid_popup_window->log(tmp);
            } else {
                snprintf(tmp, sizeof(tmp) - 1,
                        "%%fg=white$Attack          %2d/no bonus`",
                        stat);
                wid_popup_window->log(tmp);
            }
        }

        {
            auto stat = t->get_stat_defence();
            if (stat != 10) {
                snprintf(tmp, sizeof(tmp) - 1,
                        "%%fg=white$Defence         %2d%-3s to dmg",
                        stat,
                        stat_to_bonus_slash_str(stat).c_str());
                wid_popup_window->log(tmp);
            } else {
                snprintf(tmp, sizeof(tmp) - 1,
                        "%%fg=white$Defence         %2d/no bonus`",
                        stat);
                wid_popup_window->log(tmp);
            }
        }

        {
            auto stat = t->get_stat_strength();
            if (stat != 10) {
                snprintf(tmp, sizeof(tmp) - 1,
                        "%%fg=white$Strength        %2d%-3s to dmg",
                        stat,
                        stat_to_bonus_slash_str(stat).c_str());
                wid_popup_window->log(tmp);
            } else {
                snprintf(tmp, sizeof(tmp) - 1,
                        "%%fg=white$Strength        %2d/no bonus`",
                        stat);
                wid_popup_window->log(tmp);
            }
        }

        {
            auto stat = t->get_stat_constitution();
            if (stat != 10) {
                snprintf(tmp, sizeof(tmp) - 1,
                        "%%fg=white$Constitution    %2d%-3s to dmg",
                        stat,
                        stat_to_bonus_slash_str(stat).c_str());
                wid_popup_window->log(tmp);
            } else {
                snprintf(tmp, sizeof(tmp) - 1,
                        "%%fg=white$Constitution    %2d/no bonus`",
                        stat);
                wid_popup_window->log(tmp);
            }
        }
    }

    if (t->is_alive_monst()) {
        std::string danger_level = player->get_danger_level(t);
        wid_popup_window->log(" ");
        wid_popup_window->log(danger_level);

        auto max_damage = t->get_damage_max();
        if (max_damage > 0) {
            auto kill_count = player->get_health() / max_damage;

            //
            // Oh dear.
            //
            if (kill_count == 0) {
                kill_count = 1;
            }

            if (kill_count == 1) {
                wid_popup_window->log(" ");
                wid_popup_window->log("%%fg=red$Could kill you in");
                wid_popup_window->log("%%fg=red$" + std::to_string(kill_count) + 
                                      " hit!");
            } else if (kill_count <= 2) {
                wid_popup_window->log(" ");
                wid_popup_window->log("%%fg=red$Could kill you in");
                wid_popup_window->log("%%fg=red$" + std::to_string(kill_count) + 
                                      " hits");
            } else if (kill_count <= 5) {
                wid_popup_window->log(" ");
                wid_popup_window->log("%%fg=orange$Could kill you in");
                wid_popup_window->log("%%fg=orange$" + std::to_string(kill_count) + 
                                      " hits");
            } else if (kill_count <= 10) {
                wid_popup_window->log(" ");
                wid_popup_window->log("Could kill you in");
                wid_popup_window->log(std::to_string(kill_count) + " hits");
            }
        }
    }

    if (tp->charge_count()) {
        if (t->get_charge_count() > 1) {
            wid_popup_window->log(" ");
            wid_popup_window->log("Has " + 
                                  std::to_string(t->get_charge_count()) + " charges left");
        } else {
            wid_popup_window->log(" ");
            wid_popup_window->log("Has one charge left");
        }

        auto c = player->item_count_including_charges(t->tp());
        if (c > t->get_charge_count()) {
            wid_popup_window->log(" ");
            wid_popup_window->log("Total charges " + std::to_string(c));
        }
    } else {
        auto c = player->item_count_including_charges(t->tp());
        if (c > 1) {
            wid_popup_window->log(" ");
            wid_popup_window->log("Item count " + std::to_string(c));
        }

    }

    return wid_popup_window;
}

void Game::wid_thing_info_push_popup (Thingp t)
{_
    int utilized = 0;
    for (const auto w : wid_thing_info_window) {
        utilized += w->wid_text_area->line_count;

        if (w->t == t) {
            return;
        }
    }

    int height = 50;

    point tl = make_point(0, TERM_HEIGHT - 2 - height);
    point br = make_point(29, TERM_HEIGHT - 2);

    auto w2 = game->wid_thing_info_create_popup(t, tl, br);
    if (!w2) {
        return;
    }

    wid_thing_info_window.push_back(w2);

    int utilized2 = w2->wid_text_area->line_count;
    wid_move_delta(w2->wid_popup_container, 0, height - utilized2 - utilized + 1);
    wid_resize(w2->wid_popup_container, -1, utilized2 - 1);

    for (auto w : wid_thing_info_window) {
        wid_update(w->wid_text_area->wid_text_area);
    }
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
        if (t->is_hidden) {
            t->log("Do not show thing; hidden");
            return;
        }

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
        auto o = game->level->thing_find(id);
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

void Game::wid_thing_info_create_when_hovering_over (Thingp t)
{
    if (game->state == Game::STATE_CHOOSING_TARGET) {
        return;
    }
    wid_thing_info_create(t, true);
}
