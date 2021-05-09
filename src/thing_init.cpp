//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_level.h"
#include "my_depth.h"
#include "my_color.h"
#include "my_dmap.h"
#include "my_sprintf.h"
#include "my_thing.h"
#include "my_python.h"
#include "my_random.h"
#include "my_thing_template.h"
#include "my_array_bounds_check.h"
#include "my_ptrcheck.h"
#include "my_string.h"

Thingp Level::thing_new (Tpp tp, const point at)
{_
    if (!tp) {
        err("No tp provided for thing creation");
        return nullptr;
    }
    return thing_new(tp->name(), at);
}

Thingp Level::thing_new (Tpp tp, const fpoint at)
{_
    if (!tp) {
        err("No tp provided for thing creation");
        return nullptr;
    }
    return thing_new(tp->name(), at);
}

Thingp Level::thing_new (Tpp tp, const fpoint at, const fpoint jitter)
{_
    if (!tp) {
        err("No tp provided for thing creation");
        return nullptr;
    }
    return thing_new(tp->name(), at, jitter);
}

Thingp Level::thing_new (const std::string& tp_name, Thingp owner)
{_
    return thing_new(tp_name, owner->mid_at);
}

static const fpoint no_jitter(0, 0);

Thingp Level::thing_new (const std::string& name, const point at)
{_
    return thing_new(name, fpoint(at.x, at.y), no_jitter);
}

Thingp Level::thing_new (const std::string& name, const fpoint at)
{_
    return thing_new(name, at, no_jitter);
}

Thingp Level::thing_new (const std::string& name, const fpoint at, const fpoint jitter)
{_
    auto t = new struct Thing_();
    t->init(this, name, at, jitter);
    return (t);
}

Thing::Thing_ (void)
{_
    newptr(this, "thing");
}

void Thing::on_born (void)
{_
    auto on_born = tp()->on_born_do();
    if (std::empty(on_born)) {
        return;
    }

    auto t = split_tokens(on_born, '.');
    if (t.size() == 2) {
        auto mod = t[0];
        auto fn = t[1];
        std::size_t found = fn.find("()");
        if (found != std::string::npos) {
            fn = fn.replace(found, 2, "");
        }

        log("call %s.%s(%s, %d, %d)", mod.c_str(), fn.c_str(), to_string().c_str(), (int)mid_at.x, (int)mid_at.y);

        py_call_void_fn(mod.c_str(), fn.c_str(), id.id, (unsigned int)mid_at.x, (unsigned int)mid_at.y);
    } else {
        ERR("Bad on_born call [%s] expected mod:function, got %d elems",
            on_born.c_str(), (int)on_born.size());
    }
}

void Thing::init (Levelp level,
                  const std::string& name,
                  const fpoint born, const fpoint jitter)
{_
    verify(this);

    this->level = level;
    mid_at      = born;
    last_mid_at = born;

    timestamp_next_frame = 0;
    if (name == "") {
        DIE("Thing template cannot be created: no name given");
    }

    const auto tpp = tp_find(name);
    if (unlikely(!tpp)) {
        ERR("Thing template [%s] not found", name.c_str());
        return;
    }

    tp_id = tpp->id;
    tp_or_update();

    //
    // Init the z depth
    //
    z_depth = tp()->z_depth;

    //
    // Start off up to data with the player
    //
    if (is_active()) {
        set_tick(game->tick_current);

        //
        // Newly spawned things, don't make them do something immediately
        // This can lead to recursion
        //
        set_tick_last_location_check(game->tick_current);
        set_tick_last_did_something(game->tick_current);
    }

    //
    // Must do this after TP assignment or logging will fail
    //
    game->world.alloc_thing_id(this);
    if (mid_at != fpoint(-1, -1)) {
        level_enter();
        level_push();
    }

    //
    // Add AI ability
    //
    if (tpp->is_monst()) {
        new_dmap_scent();
        new_age_map();
    }

    if (tpp->is_player()) {
        level->player = this;
        level->player_dmap_update();
    }

    if (tpp->is_monst() || tpp->is_player() || tpp->is_moveable()) {
        set_timestamp_born(time_get_time_ms_cached());
    }

    if (tpp->gfx_animated_can_hflip()) {
        dir            = THING_DIR_LEFT;
        is_facing_left = true;
    } else {
        dir            = THING_DIR_NONE;
        is_facing_left = false;
    }

    is_hungry = tpp->is_hunger_insatiable();

    {_
        auto v = tpp->get_health_initial();
        if (unlikely(v)) {
            set_health(v);
            set_health_max(v);
        }
    }

    {_
        auto v = tpp->stamina();
        if (unlikely(v)) {
            set_stamina(v);
            set_stamina_max(v);
        }
    }

    {_
        auto v = tpp->enchant_level();
        if (unlikely(v)) {
            set_enchant(v);
            set_enchant_max(v);
        }
    }

    {_
        auto v = tpp->enchant_max();
        if (unlikely(v)) {
            set_enchant_max(v);
        }
    }

    {_
        auto v = tpp->stat_defence();
        if (unlikely(v)) {
            set_stat_defence(v);
            set_stats_stats19(v);
        }
    }

    {_
        auto v = tpp->tick_rate_tenths();
        if (unlikely(v)) {
            set_tick_rate_tenths(v);
        }
    }

    {_
        auto v = tpp->lifespan();
        if (unlikely(v)) {
            set_lifespan(v);
        }
    }

    {_
        auto v = tpp->stats01();
        if (unlikely(v)) {
            set_stats01(v);
        }
    }

    {_
        auto v = tpp->stats02();
        if (unlikely(v)) {
            set_stats02(v);
        }
    }

    {_
        auto v = tpp->stats03();
        if (unlikely(v)) {
            set_stats03(v);
        }
    }

    {_
        auto v = tpp->stats04();
        if (unlikely(v)) {
            set_stats04(v);
        }
    }

    {_
        auto v = tpp->stats05();
        if (unlikely(v)) {
            set_stats05(v);
        }
    }

    {_
        auto v = tpp->stats06();
        if (unlikely(v)) {
            set_stats06(v);
        }
    }

    {_
        auto v = tpp->stats07();
        if (unlikely(v)) {
            set_stats07(v);
        }
    }

    {_
        auto v = tpp->stats08();
        if (unlikely(v)) {
            set_stats08(v);
        }
    }

    {_
        auto v = tpp->stats09();
        if (unlikely(v)) {
            set_stats09(v);
        }
    }

    {_
        auto v = tpp->stats10();
        if (unlikely(v)) {
            set_stats10(v);
        }
    }

    {_
        auto v = tpp->stats11();
        if (unlikely(v)) {
            set_stats11(v);
        }
    }

    {_
        auto v = tpp->stats12();
        if (unlikely(v)) {
            set_stats12(v);
        }
    }

    {_
        auto v = tpp->stat_constitution();
        if (unlikely(v)) {
            set_stat_constitution(v);
        }
    }

    {_
        auto v = tpp->stat_attack();
        if (unlikely(v)) {
            set_stat_attack(v);
        }
    }

    {_
        auto v = tpp->stat_constitution();
        if (unlikely(v)) {
            set_stat_constitution(v);
        }
    }

    {_
        auto v = tpp->stats17();
        if (unlikely(v)) {
            set_stats17(v);
        }
    }

    {_
        auto v = tpp->throw_distance();
        if (unlikely(v)) {
            set_throw_distance(v);
        }
    }

    {_
        auto v = tpp->stat_strength();
        if (unlikely(v)) {
            set_stat_strength(v);
        }
    }

    if (unlikely(tpp->is_ascend_dungeon())) {
        if (level->world_at.z > 1) {
            is_open = true;
        }
    }

    if (unlikely(tpp->charge_count())) {
        set_charge_count(tpp->charge_count());
    }

    auto tiles = &tpp->tiles;
    if (tpp->gfx_animated()) {
        auto tile = tile_first(tiles);
        if (tile) {
            tile_curr = tile->global_index;
        } else {
            tile_curr = 0;
        }
    } else {
        auto tile = tile_random(tiles);
        if (tile) {
            tile_curr = tile->global_index;
        } else {
            tile_curr = 0;
        }
    }

    if (tpp->is_loggable_for_unimportant_stuff()) {
        log("Created");
    }

#if 0
    //
    // Jitter makes the eating of blood by monsts problematic
    //
    if (unlikely(jitter != fpoint(0.0, 0.0))) {
        double dx = random_range(0, TILE_WIDTH);
        double dy = random_range(0, TILE_WIDTH);

        dx -= TILE_WIDTH / 2;
        dy -= TILE_WIDTH / 2;

        dx /= TILE_WIDTH;
        dy /= TILE_WIDTH;

        dx *= jitter.x;
        dy *= jitter.y;

        move_to_immediately(fpoint(mid_at.x + dx, mid_at.y + dy));
    }
#endif

    //
    // Set position prior to attach
    //
    if (mid_at != fpoint(-1, -1)) {
        set_interpolated_mid_at(mid_at);
        update_interpolated_position();
    }

    if (gfx_bounce_always()) {
        bounce(0.2, 1.0, 500 + random_range(0, 50), 99999);
    }

    //
    // Jitter the initial ticks so things don't all tick the same time
    //
    if (is_active()) {
        set_timestamp_unused2(time_get_time_ms_cached() +
                                random_range(0, get_tick_rate_tenths() * 100));
    }

    init_lights();

    auto on_birth = on_birth_do();
    if (!std::empty(on_birth)) {
        auto t = split_tokens(on_birth, '.');
        if (t.size() == 2) {
            auto mod = t[0];
            auto fn = t[1];
            std::size_t found = fn.find("()");
            if (found != std::string::npos) {
                fn = fn.replace(found, 2, "");
            }
            py_call_void_fn(mod.c_str(), fn.c_str(),
                            id.id, (unsigned int)mid_at.x, (unsigned int)mid_at.y);
        } else {
            ERR("Bad on_birth call [%s] expected mod:function, got %d elems",
                on_birth.c_str(), (int)on_birth.size());
        }
    }

    if (is_monst()) {
        level->monst_count++;
    }

    is_the_grid = tp()->is_the_grid();

    //
    // Auto carry of weapons?
    //
    if (is_weapon_wielder()) {
        if (is_carrier_of_treasure_class_a()) {
            auto W = level->thing_new(tp_random_weapon_class_a(), mid_at);
            if (W) {
                carry(W);
            }
        }
        if (is_carrier_of_treasure_class_b()) {
            auto W = level->thing_new(tp_random_weapon_class_b(), mid_at);
            if (W) {
                carry(W);
            }
        }
        if (is_carrier_of_treasure_class_c()) {
            auto W = level->thing_new(tp_random_weapon_class_c(), mid_at);
            if (W) {
                carry(W);
            }
        }
    }

    if (is_item_carrier()) {
        if (is_carrier_of_treasure_class_a()) {
            auto W = level->thing_new(tp_random_item_class_a(), mid_at);
            if (W) {
                carry(W);
            }
        }
        if (is_carrier_of_treasure_class_b()) {
            auto W = level->thing_new(tp_random_item_class_b(), mid_at);
            if (W) {
                carry(W);
            }
        }
        if (is_carrier_of_treasure_class_c()) {
            auto W = level->thing_new(tp_random_item_class_c(), mid_at);
            if (W) {
                carry(W);
            }
        }
    }

    on_born();
}

void Thing::reinit (void)
{_
    verify(this);
    const auto tpp = tp_or_update();
    if (unlikely(!tpp)) {
        ERR("No tp found for reinitialized thing ID %x tp_id %d", id.id, tp_id);
        return;
    }

    game->world.realloc_thing_id(this);

    //
    // Probably safest to reset this else things might expire on load
    //
    timestamp_next_frame = 0;
    if (is_monst() || is_player()) {
        set_timestamp_born(time_get_time_ms_cached());
    }

    if (unlikely(is_player())) {
        if (level->player && (level->player != this)) {
            DIE("Player exists in multiple places on map, %f, %f and %f, %f",
                level->player->mid_at.x, level->player->mid_at.y,
                mid_at.x, mid_at.y);
            return;
        }
        level->player = this;
    }

    point new_at((int)mid_at.x, (int)mid_at.y);
    if ((new_at.x >= MAP_WIDTH) || (new_at.y >= MAP_HEIGHT)) {
        DIE("New thing is oob at %d, %d", new_at.x, new_at.y);
        return;
    }

    if (is_loggable_for_unimportant_stuff()) {
        log("Recreated");
    }

    //
    // Upon a load it was attached at save time but not now
    //
    if (is_attached) {
        level_enter();
        level_push();
    }

    //
    // Add AI ability
    //
    if (tpp->is_monst()) {
        new_dmap_scent();
        new_age_map();
    }

    //
    // Relearn the cursor after loading.
    //
    if (is_cursor()) {
        if (level->cursor) {
            dead("by already exists");
        } else {
            level->cursor = this;
        }
    }

    init_lights();
}
