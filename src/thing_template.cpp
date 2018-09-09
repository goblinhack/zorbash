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

    auto t = std::make_shared< class Tp >();

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

    t->tp_id = id;

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

std::string tp_name (Tpp t)
{_
    return (t->short_name);
}

std::string tp_short_name (Tpp t)
{_
    return (t->short_name);
}

std::string tp_raw_name (Tpp t)
{_
    return (t->raw_name);
}

Tileinfomap tp_get_tiles (Tpp t)
{_
    return (t->tiles);
}

Tileinfomap tp_get_left_tiles (Tpp t)
{_
    return (t->left_tiles);
}

Tileinfomap tp_get_right_tiles (Tpp t)
{_
    return (t->right_tiles);
}

Tileinfomap tp_get_top_tiles (Tpp t)
{_
    return (t->top_tiles);
}

Tileinfomap tp_get_bot_tiles (Tpp t)
{_
    return (t->bot_tiles);
}

Tileinfomap tp_get_tl_tiles (Tpp t)
{_
    return (t->tl_tiles);
}

Tileinfomap tp_get_tr_tiles (Tpp t)
{_
    return (t->tr_tiles);
}

Tileinfomap tp_get_bl_tiles (Tpp t)
{_
    return (t->bl_tiles);
}

Tileinfomap tp_get_br_tiles (Tpp t)
{_
    return (t->br_tiles);
}

Tileinfomap tp_get_block_1x2_tiles (Tpp t)
{_
    return (t->block_1x2_tiles);
}

Tileinfomap tp_get_block_2x1_tiles (Tpp t)
{_
    return (t->block_2x1_tiles);
}

Tileinfomap tp_get_block_2x2_tiles (Tpp t)
{_
    return (t->block_2x2_tiles);
}

Tileinfomap tp_get_block_3x3_tiles (Tpp t)
{_
    return (t->block_3x3_tiles);
}

Tileinfomap tp_get_block_6x3_tiles (Tpp t)
{_
    return (t->block_6x3_tiles);
}

Tileinfomap tp_get_block_3x6_tiles (Tpp t)
{_
    return (t->block_3x6_tiles);
}

Tileinfomap tp_get_block_6x6_tiles (Tpp t)
{_
    return (t->block_6x6_tiles);
}

Tileinfomap tp_get_horiz_tiles (Tpp t)
{_
    return (t->horiz_tiles);
}

Tileinfomap tp_get_vert_tiles (Tpp t)
{_
    return (t->vert_tiles);
}

Tileinfomap tp_get_l90_tiles (Tpp t)
{_
    return (t->l90_tiles);
}

Tileinfomap tp_get_l180_tiles (Tpp t)
{_
    return (t->l180_tiles);
}

Tileinfomap tp_get_l_tiles (Tpp t)
{_
    return (t->l_tiles);
}

Tileinfomap tp_get_l270_tiles (Tpp t)
{_
    return (t->l270_tiles);
}

Tileinfomap tp_get_t_tiles (Tpp t)
{_
    return (t->t_tiles);
}

Tileinfomap tp_get_t90_tiles (Tpp t)
{_
    return (t->t90_tiles);
}

Tileinfomap tp_get_t180_tiles (Tpp t)
{_
    return (t->t180_tiles);
}

Tileinfomap tp_get_t270_tiles (Tpp t)
{_
    return (t->t270_tiles);
}

Tileinfomap tp_get_x_tiles (Tpp t)
{_
    return (t->x_tiles);
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
