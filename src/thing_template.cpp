//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_main.h"
#include "my_tile.h"
#include "my_dice.h"

Tpnamemap tp_name_map;
Tpidmap tp_id_map;

static Tpidmap tp_monst;
static Tpidmap tp_food;
static Tpidmap tp_dirt;
static Tpidmap tp_ripples;
static Tpidmap tp_keys;
static Tpidmap tp_blood;
static Tpidmap tp_wall;
static Tpidmap tp_floor;
static Tpidmap tp_deco;
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
    for (auto t : tp_name_map) {
        delete t.second;
    }
}

Tpp tp_load (int id, std::string name)
{_
    if (tp_find(name)) {
        ERR("thing template name [%s] already used", name.c_str());
    }

    auto t = new Tp();
    t->name = name;

    auto result = tp_name_map.insert(std::make_pair(name, t));
    if (result.second == false) {
        DIE("thing insert name [%s] failed", name.c_str());
    }

    tp_id_map.push_back(t);
    t->id = tp_id_map.size();

    return (t);
}

void tp_update (Tpp t)
{_
    t->is_nutrition = Dice(t->is_nutrition_hd);
    t->bite_damage = Dice(t->bite_damage_hd);
}

//
// Find an existing thing.
//
Tpp tp_find (uint32_t id)
{_
    auto result = get(tp_id_map, id - 1);
    if (!result) {
        DIE("thing template id %08X not found", id);
    }

    return (result);
}

Tilep tp_first_tile (Tpp tp)
{_
    auto tiles = tp_tiles(tp);

    if (!tiles || tiles->empty()) {
        DIE("tp %s has no tiles", tp_name(tp).c_str());
    }

    //
    // Get the first anim tile.
    //
    return (tile_first(tiles));
}

void tp_init_after_loading (void)
{_
    for (auto tp : tp_id_map) {
        if (tp_is_monst(tp)) {
            tp_monst.push_back(tp);
        }
        if (tp_is_food(tp)) {
            tp_food.push_back(tp);
        }
        if (tp_is_dirt(tp)) {
            tp_dirt.push_back(tp);
        }
        if (tp_is_ripple(tp)) {
            tp_ripples.push_back(tp);
        }
        if (tp_is_key(tp)) {
            tp_keys.push_back(tp);
        }
        if (tp_is_blood(tp)) {
            tp_blood.push_back(tp);
        }
        if (tp_is_wall(tp)) {
            tp_wall.push_back(tp);
        }
        if (tp_is_floor(tp)) {
            tp_floor.push_back(tp);
        }
        if (tp_gfx_is_floor_deco(tp)) {
            tp_deco.push_back(tp);
        }
        if (tp_gfx_is_wall_deco(tp)) {
            tp_wall_deco.push_back(tp);
        }
    }
}

Tpp tp_random_monst (void)
{_
    return get(tp_monst, myrand() % tp_monst.size());
}

Tpp tp_random_food (void)
{_
    return get(tp_food, myrand() % tp_food.size());
}

Tpp tp_random_dirt (void)
{_
    return get(tp_dirt, myrand() % tp_dirt.size());
}

Tpp tp_random_ripple (void)
{_
    return get(tp_ripples, myrand() % tp_ripples.size());
}

Tpp tp_random_key (void)
{_
    return get(tp_keys, myrand() % tp_keys.size());
}

Tpp tp_random_blood (void)
{_
    return get(tp_blood, myrand() % tp_blood.size());
}

Tpp tp_random_wall (void)
{_
    return get(tp_wall, myrand() % tp_wall.size());
}

Tpp tp_random_floor (void)
{_
    return get(tp_floor, myrand() % tp_floor.size());
}

Tpp tp_random_deco (void)
{_
    return get(tp_deco, myrand() % tp_deco.size());
}

Tpp tp_random_wall_deco (void)
{_
    return get(tp_wall_deco, myrand() % tp_wall_deco.size());
}
