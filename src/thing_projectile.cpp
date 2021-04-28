//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_level.h"
#include "my_thing.h"
#include "my_tile.h"

bool Thing::fire_projectile_at_and_choose_target (Thingp item)
{_
    log("Trying to projectile with: %s", item->to_string().c_str());

    if (item->projectile_name().empty()) {
        if (is_player()) {
            TOPCON("I don't know how to fire %s.", item->text_the().c_str());
            game->tick_begin("player tried to use something they could not");
        }
        return false;
    }

    if (!target_select(item)) {
        return false;
    }

    game->request_to_fire_item = item;

    return target_select(item);
}

bool Thing::projectile_fire (Thingp item, Thingp target)
{_
    log("Firing projectile with: %s at %s", item->to_string().c_str(),
        target->to_string().c_str());

    if (item->projectile_name().empty()) {
        if (is_player()) {
            TOPCON("I don't know how to fire %s.", item->text_the().c_str());
            game->tick_begin("player tried to use something they could not");
        }
        return false;
    }

    if (!game->request_to_fire_item) {
        ERR("No projectile to fire");
        return false;
    }

    //
    // Check not out of range
    //
    bool too_far = false;
    auto dist = distance(mid_at, target->mid_at);

    if (game->request_to_fire_item) {
        if (dist > item->range_max()) {
            too_far = true;
        }
    }

    if (too_far) {
        if (is_player()) {
            TOPCON("That target is out of range of %s.", 
                   item->text_the().c_str());
        }
        return false;
    }

    if (is_player()) {
        game->tick_begin("player fired projectile");
    }

    if (game->state == Game::STATE_CHOOSING_TARGET) {
        game->change_state(Game::STATE_NORMAL);
    }

    auto start = last_blit_at;
    auto end = target->last_blit_at;

    if (!start.x && !start.y) {
        return false;
    }

    if (!end.x && !end.y) {
        return false;
    }

    level->new_projectile(item->id, start, end, 1500);

    used(item, target, true /* remove_after_use */);

    return true;
}

bool Thing::projectile_fire_monst (const std::string &projectile, Thingp target)
{_
    auto item = level->thing_new(projectile, mid_at);
    if (!item) {
        return false;
    }

    item->set_owner(this);

    log("Firing projectile with: %s at %s", item->to_string().c_str(),
        target->to_string().c_str());

    if (item->projectile_name().empty()) {
        if (is_player()) {
            TOPCON("I don't know how to fire %s.", item->text_the().c_str());
            game->tick_begin("player tried to use something they could not");
        }
        return false;
    }

    if (is_player()) {
        game->tick_begin("player fired projectile");
    }

    auto start = last_blit_at;
    auto end = target->last_blit_at;

    if (!start.x && !start.y) {
        return false;
    }

    if (!end.x && !end.y) {
        return false;
    }

    level->new_projectile(item->id, start, end, 150);

    on_use(item, target);

    item->dead("fired");

    return true;
}
