//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_main.h"
#include "my_tile.h"
#include "my_dice.h"

Tpmap tp_map;
static Tpmap_create_order tp_create_order_map;
static Tpmap_create_order tp_monst;
static Tpmap_create_order tp_food;
static Tpmap_create_order tp_dirt;
static Tpmap_create_order tp_grass;
static Tpmap_create_order tp_soil;
static Tpmap_create_order tp_gravel;
static Tpmap_create_order tp_snow;
static Tpmap_create_order tp_ripples;
static Tpmap_create_order tp_keys;
static Tpmap_create_order tp_blood;
static Tpmap_create_order tp_wall;
static Tpmap_create_order tp_floor;
static Tpmap_create_order tp_deco;
static Tpmap_create_order tp_wall_deco;

static uint8_t tp_init_done;

uint8_t tp_init (void)
{_
    tp_init_done = true;

    return (true);
}

void tp_fini (void)
{_
    if (tp_init_done) {
        tp_init_done = false;
    }
}

Tpp tp_load (int id, std::string name)
{_
    if (tp_find(name)) {
        ERR("thing template name [%s] already used", name.c_str());
    }

    if (id >= TP_MAX - 1) {
        ERR("too many thing templates");
    }

    auto t = new Tp();

    t->name = name;

    {
        auto result = tp_map.insert(std::make_pair(name, t));

        if (result.second == false) {
            DIE("thing insert name [%s] failed", name.c_str());
        }
    }

    tp_create_order_map.push_back(t);
    t->id = id;

    return (t);
}

void tp_update (Tpp t)
{_
    t->nutrition = Dice(t->nutrition_hd);
    t->bite_damage = Dice(t->bite_damage_hd);
}

//
// Find an existing thing.
//
Tpp tp_find (uint32_t id)
{_
    auto result = tp_create_order_map[id];
    if (!result) {
        DIE("thing template id %u not found", id);
    }

    return (result);
}

Tpp tp_find_name (std::string name)
{_
    for (auto ti : tp_map) {
        auto Tpp = ti.second;

        if (!strcasecmp(name.c_str(), Tpp->name.c_str())) {
            return (Tpp);
        }
    }

    ERR("did not find short template name \"%s\"", name.c_str());

    return (0);
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
    for (auto t : tp_map) {
        auto tp = t.second;
        if (tp_is_monst(tp)) {
            tp_monst.push_back(tp);
        }
        if (tp_is_food(tp)) {
            tp_food.push_back(tp);
        }
        if (tp_is_dirt(tp)) {
            tp_dirt.push_back(tp);
        }
        if (tp_is_grass(tp)) {
            tp_grass.push_back(tp);
        }
        if (tp_is_soil(tp)) {
            tp_soil.push_back(tp);
        }
        if (tp_is_gravel(tp)) {
            tp_gravel.push_back(tp);
        }
        if (tp_is_snow(tp)) {
            tp_snow.push_back(tp);
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
    return tp_monst[myrand() % tp_monst.size()];
}

Tpp tp_random_food (void)
{_
    return tp_food[myrand() % tp_food.size()];
}

Tpp tp_random_dirt (void)
{_
    return tp_dirt[myrand() % tp_dirt.size()];
}

Tpp tp_random_grass (void)
{_
    return tp_grass[myrand() % tp_grass.size()];
}

Tpp tp_random_soil (void)
{_
    return tp_soil[myrand() % tp_soil.size()];
}

Tpp tp_random_gravel (void)
{_
    return tp_gravel[myrand() % tp_gravel.size()];
}

Tpp tp_random_snow (void)
{_
    return tp_snow[myrand() % tp_snow.size()];
}

Tpp tp_random_ripple (void)
{_
    return tp_ripples[myrand() % tp_ripples.size()];
}

Tpp tp_random_key (void)
{_
    return tp_keys[myrand() % tp_keys.size()];
}

Tpp tp_random_blood (void)
{_
    return tp_blood[myrand() % tp_blood.size()];
}

Tpp tp_random_wall (void)
{_
    return tp_wall[myrand() % tp_wall.size()];
}

Tpp tp_random_floor (void)
{_
    return tp_floor[myrand() % tp_floor.size()];
}

Tpp tp_random_deco (void)
{_
    return tp_deco[myrand() % tp_deco.size()];
}

Tpp tp_random_wall_deco (void)
{_
    return tp_wall_deco[myrand() % tp_wall_deco.size()];
}
