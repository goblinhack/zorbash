//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_level.h"
#include "my_thing_template.h"
#include "my_depth.h"
#include "my_tile.h"
#include "my_dice.h"
#include "my_random.h"
#include "my_array_bounds_check.h"
#include "my_vector_bounds_check.h"
#include "my_thing.h"

static Tpidmap tp_blood;
static Tpidmap tp_blood_splatter;
static Tpidmap tp_deco;
static Tpidmap tp_dirt;
static Tpidmap tp_door;
static Tpidmap tp_ascend_dungeon;
static Tpidmap tp_descend_dungeon;
static Tpidmap tp_floor;
static Tpidmap tp_food;
static Tpidmap tp_gold;
static Tpidmap tp_key;
static Tpidmap tp_potion;
static Tpidmap tp_wand;
static Tpidmap tp_monst;
static Tpidmap tp_ripples;
static Tpidmap tp_rock;
static Tpidmap tp_secret_door;
static Tpidmap tp_generator;
static Tpidmap tp_ethereal_generator;
static Tpidmap tp_brazier;
static Tpidmap tp_barrel;
static Tpidmap tp_treasure;
static Tpidmap tp_item_class_a;
static Tpidmap tp_item_class_b;
static Tpidmap tp_item_class_c;
static Tpidmap tp_weapon_class_a;
static Tpidmap tp_weapon_class_b;
static Tpidmap tp_weapon_class_c;
static Tpidmap tp_wall_dungeon;
static Tpidmap tp_sewer_wall;
static Tpidmap tp_ascend_sewer;
static Tpidmap tp_descend_sewer;

void tp_random_init (void)
{_
    for (auto& tp : tp_id_map) {
        if (tp->is_blood())                     { tp_blood.push_back(tp); }
        if (tp->is_blood_splatter())            { tp_blood_splatter.push_back(tp); }
        if (tp->is_dirt())                      { tp_dirt.push_back(tp); }
        if (tp->is_door())                      { tp_door.push_back(tp); }
        if (tp->is_wall_dungeon())              { tp_wall_dungeon.push_back(tp); }
        if (tp->is_ascend_dungeon())            { tp_ascend_dungeon.push_back(tp); }
        if (tp->is_descend_dungeon())           { tp_descend_dungeon.push_back(tp); }
        if (tp->is_floor())                     { tp_floor.push_back(tp); }
        if (tp->is_floor_deco())                { tp_deco.push_back(tp); }
        if (tp->is_food())                      { tp_food.push_back(tp); }
        if (tp->is_gold())                      { tp_gold.push_back(tp); }
        if (tp->is_key())                       { tp_key.push_back(tp); }
        if (tp->is_minion_generator())          { tp_generator.push_back(tp); }
        if (tp->is_ethereal_minion_generator()) { tp_ethereal_generator.push_back(tp); }
        if (tp->is_potion())                    { tp_potion.push_back(tp); }
        if (tp->is_wand())                      { tp_wand.push_back(tp); }
        if (tp->is_ripple())                    { tp_ripples.push_back(tp); }
        if (tp->is_rock())                      { tp_rock.push_back(tp); }
        if (tp->is_secret_door())               { tp_secret_door.push_back(tp); }
        if (tp->is_ascend_sewer())              { tp_ascend_sewer.push_back(tp); }
        if (tp->is_descend_sewer())             { tp_descend_sewer.push_back(tp); }
        if (tp->is_sewer_wall())                { tp_sewer_wall.push_back(tp); }
        if (tp->is_brazier())                   { tp_brazier.push_back(tp); }
        if (tp->is_barrel())                    { tp_barrel.push_back(tp); }
        if (tp->is_treasure())                  { tp_treasure.push_back(tp); }
        if (tp->is_treasure_class_a())          { tp_item_class_a.push_back(tp); }
        if (tp->is_treasure_class_b())          { tp_item_class_b.push_back(tp); }
        if (tp->is_treasure_class_c())          { tp_item_class_c.push_back(tp); }

        if (tp->is_weapon()) {
            if (tp->is_treasure_class_a()) { tp_weapon_class_a.push_back(tp); }
            if (tp->is_treasure_class_b()) { tp_weapon_class_b.push_back(tp); }
            if (tp->is_treasure_class_c()) { tp_weapon_class_c.push_back(tp); }
        }

        if (!tp->is_minion()) {
            if (tp->is_monst()) {tp_monst.push_back(tp); }
        }
    }
}

static Tpp tp_get_with_rarity_filter (Tpidmap &m)
{_
    int tries = 10000;
    while (tries--) {
        auto tp = get(m, myrand() % m.size());
        auto r = random_range(0, 1000);
        if (r < 800) {
            if (tp->rarity() != THING_RARITY_COMMON) {
                continue;
            }
            // CON("chose THING_RARITY_COMMON -- %s", tp->name().c_str());
        } else if (r < 900) {
            if (tp->rarity() != THING_RARITY_UNCOMMON) {
                continue;
            }
            // CON("chose THING_RARITY_UNCOMMON -- %s", tp->name().c_str());
        } else if (r < 950) {
            if (tp->rarity() != THING_RARITY_RARE) {
                continue;
            }
            // CON("chose THING_RARITY_RARE -- %s", tp->name().c_str());
        } else if (r < 990) {
            if (tp->rarity() != THING_RARITY_VERY_RARE) {
                continue;
            }
            // CON("chose THING_RARITY_VERY_RARE -- %s", tp->name().c_str());
        } else if (r == 999) {
            if (tp->rarity() != THING_RARITY_UNIQUE) {
                continue;
            }
            // CON("chose THING_RARITY_UNIQUE -- %s", tp->name().c_str());
        }
        return tp;
    }
    ERR("Could not find a thing according to rarity");
    return get(m, myrand() % m.size());
}

static Tpp tp_get_with_no_rarity_filter (Tpidmap &m)
{_
    return get(m, myrand() % m.size());
}

Tpp tp_random_monst (void)
{_
//CON("TODO using debug monster");
//return (tp_find("tentacleye"));
    if (unlikely(!tp_monst.size())) {
        ERR("No monsts found");
        return (nullptr);
    }
#if 0
for (auto i = 0; i < 1000; i++) {
    CON("%s",tp_get_with_rarity_filter(tp_monst)->name().c_str());
}
#endif
    return tp_get_with_rarity_filter(tp_monst);
}

Tpp tp_random_monst_easy (void)
{_
    return tp_random_monst();
}

Tpp tp_random_monst_hard (void)
{_
    return tp_random_monst();
}

Tpp Level::tp_random_monst (const point &p)
{_
    auto tries = 0U;
    for (;;) {
        if (tries++ > 1000) {
            return nullptr;
        }
        auto tpp = ::tp_random_monst();
        if (tpp->will_avoid_threat(this, p)) {
            continue;
        }

        return tpp;
    }
}

Tpp Level::tp_random_monst_easy (const point &p)
{_
    Thingp current_player = player;
    if (!current_player) {
        //
        // Try the current level
        //
        if (game->level) {
            current_player = game->level->player;
        }
        if (!current_player) {
            ERR("Cannot place easy monst if no player yet");
            return nullptr;
        }
    }

    auto player_danger_level = current_player->get_danger_level();

    auto tries = 0U;
    for (;;) {
        if (tries++ > 1000) {
            ERR("Cannot place easy monst");
            return nullptr;
        }
        auto tpp = ::tp_random_monst();
        if (tpp->will_avoid_threat(this, p)) {
            continue;
        }

        if (tpp->get_danger_level() > player_danger_level) {
            continue;
        }

        CON("Placed easy monst %s", tpp->name().c_str());
        return tpp;
    }
}

Tpp Level::tp_random_monst_hard (const point &p)
{_
    Thingp current_player = player;
    if (!current_player) {
        //
        // Try the current level
        //
        if (game->level) {
            current_player = game->level->player;
        }
        if (!current_player) {
            ERR("Cannot place hard monst if no player yet");
            return nullptr;
        }
    }

    auto player_danger_level = current_player->get_danger_level();

    auto tries = 0U;
    for (;;) {
        if (tries++ > 1000) {
            ERR("Cannot place hard monst");
            return nullptr;
        }
        auto tpp = ::tp_random_monst();
        if (tpp->will_avoid_threat(this, p)) {
            continue;
        }

        if (tpp->get_danger_level() < player_danger_level) {
            continue;
        }

        CON("Placed hard monst %s", tpp->name().c_str());
        return tpp;
    }
}

Tpp tp_random_food (void)
{_
    if (unlikely(!tp_food.size())) {
        ERR("No foods found");
        return (nullptr);
    }
    return tp_get_with_rarity_filter(tp_food);
}

Tpp tp_random_gold (void)
{_
    if (unlikely(!tp_gold.size())) {
        ERR("No golds found");
        return (nullptr);
    }
    return tp_get_with_rarity_filter(tp_gold);
}

Tpp tp_random_treasure (void)
{_
    if (unlikely(!tp_treasure.size())) {
        ERR("No treasures found");
        return (nullptr);
    }
    return tp_get_with_rarity_filter(tp_treasure);
}

Tpp tp_random_item_class_a (void)
{_
    if (unlikely(!tp_item_class_a.size())) {
        ERR("No item_class_a found");
        return (nullptr);
    }
    return tp_get_with_rarity_filter(tp_item_class_a);
}

Tpp tp_random_item_class_b (void)
{_
    if (unlikely(!tp_item_class_b.size())) {
        ERR("No item_class_b found");
        return (nullptr);
    }
    return tp_get_with_rarity_filter(tp_item_class_b);
}

Tpp tp_random_item_class_c (void)
{_
    if (unlikely(!tp_item_class_c.size())) {
        ERR("No item_class_c found");
        return (nullptr);
    }
    return tp_get_with_rarity_filter(tp_item_class_c);
}

Tpp tp_random_weapon_class_a (void)
{_
    if (unlikely(!tp_weapon_class_a.size())) {
        ERR("No weapon_class_a found");
        return (nullptr);
    }
    return tp_get_with_rarity_filter(tp_weapon_class_a);
}

Tpp tp_random_weapon_class_b (void)
{_
    if (unlikely(!tp_weapon_class_b.size())) {
        ERR("No weapon_class_b found");
        return (nullptr);
    }
    return tp_get_with_rarity_filter(tp_weapon_class_b);
}

Tpp tp_random_weapon_class_c (void)
{_
    if (unlikely(!tp_weapon_class_c.size())) {
        ERR("No weapon_class_c found");
        return (nullptr);
    }
    return tp_get_with_rarity_filter(tp_weapon_class_c);
}

Tpp tp_random_dirt (void)
{_
    if (unlikely(!tp_dirt.size())) {
        ERR("No dirts found");
        return (nullptr);
    }
    return tp_get_with_no_rarity_filter(tp_dirt);
}

Tpp tp_random_ripple (void)
{_
    if (unlikely(!tp_ripples.size())) {
        ERR("No ripples found");
        return (nullptr);
    }
    return tp_get_with_no_rarity_filter(tp_ripples);
}

Tpp tp_random_blood_splatter (void)
{_
    if (unlikely(!tp_blood_splatter.size())) {
        ERR("No blood_splatter found");
        return (nullptr);
    }
    return tp_get_with_no_rarity_filter(tp_blood_splatter);
}

Tpp tp_random_key (void)
{_
    if (unlikely(!tp_key.size())) {
        ERR("No key found");
        return (nullptr);
    }
    return tp_get_with_no_rarity_filter(tp_key);
}

Tpp tp_random_potion (void)
{_
    if (unlikely(!tp_potion.size())) {
        ERR("No potion found");
        return (nullptr);
    }
    return tp_get_with_rarity_filter(tp_potion);
}

Tpp tp_random_wand (void)
{_
    if (unlikely(!tp_wand.size())) {
        ERR("No wand found");
        return (nullptr);
    }
    return tp_get_with_rarity_filter(tp_wand);
}

Tpp tp_random_ascend_dungeon (void)
{_
    if (unlikely(!tp_ascend_dungeon.size())) {
        ERR("No entrance found");
        return (nullptr);
    }
    return tp_get_with_no_rarity_filter(tp_ascend_dungeon);
}

Tpp tp_random_descend_dungeon (void)
{_
    if (unlikely(!tp_descend_dungeon.size())) {
        ERR("No exit found");
        return (nullptr);
    }
    return tp_get_with_no_rarity_filter(tp_descend_dungeon);
}

Tpp tp_random_brazier (void)
{_
    if (unlikely(!tp_brazier.size())) {
        ERR("No brazier found");
        return (nullptr);
    }
    return tp_get_with_no_rarity_filter(tp_brazier);
}

Tpp tp_random_barrel (void)
{_
    if (unlikely(!tp_barrel.size())) {
        ERR("No barrel found");
        return (nullptr);
    }
    return tp_get_with_no_rarity_filter(tp_barrel);
}

Tpp tp_random_door (void)
{_
    if (unlikely(!tp_door.size())) {
        ERR("No door found");
        return (nullptr);
    }
    return tp_get_with_no_rarity_filter(tp_door);
}

Tpp tp_random_secret_door (void)
{_
    if (unlikely(!tp_secret_door.size())) {
        ERR("No secret_door found");
        return (nullptr);
    }
    return tp_get_with_no_rarity_filter(tp_secret_door);
}

Tpp tp_random_minion_generator (void)
{_
    if (unlikely(!tp_generator.size())) {
        ERR("No generator found");
        return (nullptr);
    }
    return tp_get_with_rarity_filter(tp_generator);
}

Tpp tp_random_ethereal_minion_generator (void)
{_
    if (unlikely(!tp_ethereal_generator.size())) {
        ERR("No generator found");
        return (nullptr);
    }
    return tp_get_with_rarity_filter(tp_ethereal_generator);
}

Tpp tp_random_minion_generator_easy (void)
{
    return tp_random_minion_generator();
}

Tpp tp_random_minion_generator_hard (void)
{
    return tp_random_minion_generator();
}

Tpp Level::tp_random_minion_generator (const point &p)
{_
    auto tries = 0U;
    for (;;) {
        if (tries++ > 1000) {
            return nullptr;
        }
        auto tpp = ::tp_random_minion_generator();
        if (tpp->will_avoid_threat(this, p)) {
            continue;
        }
        return tpp;
    }
}

Tpp Level::tp_random_minion_generator_easy (const point &p)
{_
    return tp_random_minion_generator(p);
}

Tpp Level::tp_random_minion_generator_hard (const point &p)
{_
    return tp_random_minion_generator(p);
}

Tpp tp_random_blood (void)
{_
    if (unlikely(!tp_blood.size())) {
        ERR("No bloods found");
        return (nullptr);
    }
    return tp_get_with_no_rarity_filter(tp_blood);
}

Tpp tp_random_wall_dungeon (void)
{_
    if (unlikely(!tp_wall_dungeon.size())) {
        ERR("No dungeon walls found");
        return (nullptr);
    }
    return tp_get_with_no_rarity_filter(tp_wall_dungeon);
}

Tpp tp_random_sewer_wall (void)
{_
    if (unlikely(!tp_sewer_wall.size())) {
        ERR("No sewer walls found");
        return (nullptr);
    }
    return tp_get_with_no_rarity_filter(tp_sewer_wall);
}

Tpp tp_random_rock (void)
{_
    if (unlikely(!tp_rock.size())) {
        ERR("No rocks found");
        return (nullptr);
    }
    return tp_get_with_no_rarity_filter(tp_rock);
}

Tpp tp_random_floor (void)
{_
    if (unlikely(!tp_floor.size())) {
        ERR("No floors found");
        return (nullptr);
    }
    return tp_get_with_no_rarity_filter(tp_floor);
}

Tpp tp_random_deco (void)
{_
    if (unlikely(!tp_deco.size())) {
        ERR("No decos found");
        return (nullptr);
    }
    return tp_get_with_no_rarity_filter(tp_deco);
}

Tpp tp_random_ascend_sewer (void)
{_
    if (unlikely(!tp_ascend_sewer.size())) {
        ERR("No sewer entrances found");
        return (nullptr);
    }
    return tp_get_with_no_rarity_filter(tp_ascend_sewer);
}

Tpp tp_random_descend_sewer (void)
{_
    if (unlikely(!tp_descend_sewer.size())) {
        ERR("No sewer exits found");
        return (nullptr);
    }
    return tp_get_with_no_rarity_filter(tp_descend_sewer);
}
