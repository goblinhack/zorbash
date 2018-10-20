/*
 * Copyright (C) 2018 goblinhack@gmail.com
 *
 * See the LICENSE file for license.
 */

#include "my_main.h"
#include "my_tile_info.h"
#include "my_tile.h"

Tpmap tp_map;
Tpmap_create_order tp_create_order_map;

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

    {
        auto result = tp_map.insert(std::make_pair(name, t));

        if (result.second == false) {
            DIE("thing insert name [%s] failed", name.c_str());
        }
    }

    {
        static unsigned int id;
        id++;

        auto result = tp_create_order_map.insert(std::make_pair(id, t));
        if (result.second == false) {
            ERR("thing template insert create order [%s] failed", name.c_str());
        }
    }

    t->id = id;

    return (t);
}

void tp_update (Tpp t)
{_
    /*
     * Hook point to modify tps post python config.
     */
}

/*
 * Find an existing thing.
 */
Tpp tp_find (std::string name)
{_
    if (name == "") {
        ERR("no name for tp find");
    }

    auto result = tp_map.find(name);

    if (result == tp_map.end()) {
        return (0);
    }

    return (result->second);
}

/*
 * Find an existing thing.
 */
Tpp tp_find (uint32_t id)
{_
    auto result = tp_create_order_map[id];
    if (!result) {
        DIE("thing template id %u not found", id);
    }

    return (result);
}

Tpp tp_find_short_name (std::string name)
{_
    for (auto ti : tp_map) {
        auto Tpp = ti.second;

        if (!strcasecmp(name.c_str(), Tpp->short_name.c_str())) {
            return (Tpp);
        }
    }

    ERR("did not find short template name \"%s\"", name.c_str());

    return (0);
}

Tilep tp_first_tile (Tpp tp)
{_
    auto tiles = tp_get_tiles(tp);

    if (tiles.empty()) {
        DIE("tp %s has no tiles", tp_name(tp).c_str());
    }

    /*
     * Get the first anim tile.
     */
    auto Tileinfo = tile_info_first(tiles);

    return (Tileinfo->tile);
}
