//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_main.h"
#include "my_level.h"
#include "my_thing_template.h"
#include "my_depth.h"
#include "my_main.h"
#include "my_tile.h"
#include "my_dice.h"

Tpnamemap tp_name_map;
Tpidmap tp_id_map;

static Tpidmap tp_blood;
static Tpidmap tp_blood_splatter;
static Tpidmap tp_deco;
static Tpidmap tp_dirt;
static Tpidmap tp_door;
static Tpidmap tp_entrance;
static Tpidmap tp_exit;
static Tpidmap tp_floor;
static Tpidmap tp_food;
static Tpidmap tp_gold;
static Tpidmap tp_key;
static Tpidmap tp_potion;
static Tpidmap tp_monst;
static Tpidmap tp_ripples;
static Tpidmap tp_rock;
static Tpidmap tp_secret_door;
static Tpidmap tp_generator;
static Tpidmap tp_torch;
static Tpidmap tp_treasure;
static Tpidmap tp_item_class_a;
static Tpidmap tp_item_class_b;
static Tpidmap tp_wall;
static Tpidmap tp_wall_deco;

static uint8_t tp_init_done;

uint8_t tp_init (void)
{_
    tp_init_done = true;

    tp_init_after_loading();

    return (true);
}

void tp_fini (void)
{_
    if (tp_init_done) {
        tp_init_done = false;
    }
    for (auto& tp : tp_name_map) {
        delete tp.second;
    }
}

Tpp tp_load (int id, std::string const& name, std::string const& text_name)
{_
    if (tp_find(name)) {
        ERR("thing template name [%s] already used", name.c_str());
    }

    auto tp = new Tp();
    tp->set_name(name);
    tp->set_text_name(text_name);

    auto result = tp_name_map.insert(std::make_pair(name, tp));
    if (result.second == false) {
        ERR("thing insert name [%s] failed", name.c_str());
    }

    tp_id_map.push_back(tp);
    tp->id = tp_id_map.size();

    return (tp);
}

//
// Find an existing thing.
//
Tpp tp_find (uint32_t id)
{_
    auto result = get(tp_id_map, id - 1);
    if (!result) {
        ERR("thing template %" PRIx32 " not found", id);
    }

    return (result);
}

Tilep tp_first_tile (Tpp tp)
{_
    auto tiles = &tp->tiles;

    if (!tiles || tiles->empty()) {
        ERR("tp %s has no tiles", tp->name().c_str());
    }

    //
    // Get the first anim tile.
    //
    return (tile_first(tiles));
}

void tp_init_after_loading (void)
{_
    for (auto& tp : tp_id_map) {
        if (tp->is_blood())          { tp_blood.push_back(tp); }
        if (tp->is_blood_splatter()) { tp_blood_splatter.push_back(tp); }
        if (tp->is_dirt())           { tp_dirt.push_back(tp); }
        if (tp->is_door())           { tp_door.push_back(tp); }
        if (tp->is_entrance())       { tp_entrance.push_back(tp); }
        if (tp->is_exit())           { tp_exit.push_back(tp); }
        if (tp->is_floor())          { tp_floor.push_back(tp); }
        if (tp->is_floor_deco())     { tp_deco.push_back(tp); }
        if (tp->is_food())           { tp_food.push_back(tp); }
        if (tp->is_generator())      { tp_generator.push_back(tp); }
        if (tp->is_gold())           { tp_gold.push_back(tp); }
        if (tp->is_item_class_a())   { tp_item_class_a.push_back(tp); }
        if (tp->is_item_class_b())   { tp_item_class_b.push_back(tp); }
        if (tp->is_key())            { tp_key.push_back(tp); }
        if (tp->is_monst())          { tp_monst.push_back(tp); }
        if (tp->is_potion())         { tp_potion.push_back(tp); }
        if (tp->is_ripple())         { tp_ripples.push_back(tp); }
        if (tp->is_rock())           { tp_rock.push_back(tp); }
        if (tp->is_secret_door())    { tp_secret_door.push_back(tp); }
        if (tp->is_torch())          { tp_torch.push_back(tp); }
        if (tp->is_treasure())       { tp_treasure.push_back(tp); }
        if (tp->is_wall())           { tp_wall.push_back(tp); }
        if (tp->is_wall_deco())      { tp_wall_deco.push_back(tp); }

        if (tp->stats_stamina()) {
            tp->set_is_stamina_check(true);
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
    ERR("could not find a thing according to rarity");
    return get(m, myrand() % m.size());
}

static Tpp tp_get_with_no_rarity_filter (Tpidmap &m)
{_
    return get(m, myrand() % m.size());
}

Tpp tp_random_monst (void)
{_
//CON("TODO using debug monster");
//return (tp_find("cube1"));
    if (unlikely(!tp_monst.size())) {
        ERR("no monsts found");
        return (nullptr);
    }
    return tp_get_with_rarity_filter(tp_monst);
}

Tpp tp_random_food (void)
{_
    if (unlikely(!tp_food.size())) {
        ERR("no foods found");
        return (nullptr);
    }
    return tp_get_with_rarity_filter(tp_food);
}

Tpp tp_random_gold (void)
{_
    if (unlikely(!tp_gold.size())) {
        ERR("no golds found");
        return (nullptr);
    }
    return tp_get_with_rarity_filter(tp_gold);
}

Tpp tp_random_treasure (void)
{_
    if (unlikely(!tp_treasure.size())) {
        ERR("no treasures found");
        return (nullptr);
    }
    return tp_get_with_rarity_filter(tp_treasure);
}

Tpp tp_random_item_class_a (void)
{_
    if (unlikely(!tp_item_class_a.size())) {
        ERR("no item_class_a found");
        return (nullptr);
    }
    return tp_get_with_rarity_filter(tp_item_class_a);
}

Tpp tp_random_item_class_b (void)
{_
    if (unlikely(!tp_item_class_b.size())) {
        ERR("no item_class_b found");
        return (nullptr);
    }
    return tp_get_with_rarity_filter(tp_item_class_b);
}

Tpp tp_random_dirt (void)
{_
    if (unlikely(!tp_dirt.size())) {
        ERR("no dirts found");
        return (nullptr);
    }
    return tp_get_with_no_rarity_filter(tp_dirt);
}

Tpp tp_random_ripple (void)
{_
    if (unlikely(!tp_ripples.size())) {
        ERR("no ripples found");
        return (nullptr);
    }
    return tp_get_with_no_rarity_filter(tp_ripples);
}

Tpp tp_random_blood_splatter (void)
{_
    if (unlikely(!tp_blood_splatter.size())) {
        ERR("no blood_splatter found");
        return (nullptr);
    }
    return tp_get_with_no_rarity_filter(tp_blood_splatter);
}

Tpp tp_random_key (void)
{_
    if (unlikely(!tp_key.size())) {
        ERR("no key found");
        return (nullptr);
    }
    return tp_get_with_no_rarity_filter(tp_key);
}

Tpp tp_random_potion (void)
{_
    if (unlikely(!tp_potion.size())) {
        ERR("no potion found");
        return (nullptr);
    }
    return tp_get_with_rarity_filter(tp_potion);
}

Tpp tp_random_entrance (void)
{_
    if (unlikely(!tp_entrance.size())) {
        ERR("no entrance found");
        return (nullptr);
    }
    return tp_get_with_no_rarity_filter(tp_entrance);
}

Tpp tp_random_exit (void)
{_
    if (unlikely(!tp_exit.size())) {
        ERR("no exit found");
        return (nullptr);
    }
    return tp_get_with_no_rarity_filter(tp_exit);
}

Tpp tp_random_torch (void)
{_
    if (unlikely(!tp_torch.size())) {
        ERR("no torch found");
        return (nullptr);
    }
    return tp_get_with_no_rarity_filter(tp_torch);
}

Tpp tp_random_door (void)
{_
    if (unlikely(!tp_door.size())) {
        ERR("no door found");
        return (nullptr);
    }
    return tp_get_with_no_rarity_filter(tp_door);
}

Tpp tp_random_secret_door (void)
{_
    if (unlikely(!tp_secret_door.size())) {
        ERR("no secret_door found");
        return (nullptr);
    }
    return tp_get_with_no_rarity_filter(tp_secret_door);
}

Tpp tp_random_generator (void)
{_
    if (unlikely(!tp_generator.size())) {
        ERR("no generator found");
        return (nullptr);
    }
    return tp_get_with_rarity_filter(tp_generator);
}

Tpp tp_random_blood (void)
{_
    if (unlikely(!tp_blood.size())) {
        ERR("no bloods found");
        return (nullptr);
    }
    return tp_get_with_no_rarity_filter(tp_blood);
}

Tpp tp_random_wall (void)
{_
    if (unlikely(!tp_wall.size())) {
        ERR("no walls found");
        return (nullptr);
    }
    return tp_get_with_no_rarity_filter(tp_wall);
}

Tpp tp_random_rock (void)
{_
    if (unlikely(!tp_rock.size())) {
        ERR("no rocks found");
        return (nullptr);
    }
    return tp_get_with_no_rarity_filter(tp_rock);
}

Tpp tp_random_floor (void)
{_
    if (unlikely(!tp_floor.size())) {
        ERR("no floors found");
        return (nullptr);
    }
    return tp_get_with_no_rarity_filter(tp_floor);
}

Tpp tp_random_deco (void)
{_
    if (unlikely(!tp_deco.size())) {
        ERR("no decos found");
        return (nullptr);
    }
    return tp_get_with_no_rarity_filter(tp_deco);
}

Tpp tp_random_wall_deco (void)
{_
    if (unlikely(!tp_wall_deco.size())) {
        ERR("no wall_decos found");
        return (nullptr);
    }
    return tp_get_with_no_rarity_filter(tp_wall_deco);
}
