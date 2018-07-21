/*
 * Copyright (C) 2011-2020 goblinhack@gmail.com
 *
 * See the LICENSE file for license.
 */

#include "my_main.h"
#include "my_thing_tile.h"
#include "my_tile.h"

thing_templates thing_templates_map;
thing_templates_create_order thing_templates_create_order_map;

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

tpp tp_load (int id, std::string name)
{_
    if (tp_find(name)) {
        ERR("thing template name [%s] already used", name.c_str());
    }

    if (id >= TP_MAX - 1) {
        ERR("too many thing templates");
    }

    auto t = std::make_shared< class thing_template >();

    {
        auto result = thing_templates_map.insert(std::make_pair(name, t));

        if (result.second == false) {
            DIE("thing insert name [%s] failed", name.c_str());
        }
    }

    {
        static unsigned int id;
        id++;

        auto result = thing_templates_create_order_map.insert(std::make_pair(id, t));
        if (result.second == false) {
            ERR("thing template insert create order [%s] failed", name.c_str());
        }
    }

    t->tp_id = id;

    return (t);
}

void tp_update (tpp t)
{_
    /*
     * Hook point to modify tps post python config.
     */
}

/*
 * Find an existing thing.
 */
tpp tp_find (std::string name)
{_
    if (name == "") {
        ERR("no name for tp find");
    }

    auto result = thing_templates_map.find(name);

    if (result == thing_templates_map.end()) {
        return (0);
    }

    return (result->second);
}

tpp tp_find_short_name (std::string name)
{_
    for (auto ti : thing_templates_map) {
        auto tpp = ti.second;

        if (!strcasecmp(name.c_str(), tpp->short_name.c_str())) {
            return (tpp);
        }
    }

    ERR("did not find short template name \"%s\"", name.c_str());

    return (0);
}

std::string tp_name (tpp t)
{_
    return (t->short_name);
}

std::string tp_short_name (tpp t)
{_
    return (t->short_name);
}

std::string tp_raw_name (tpp t)
{_
    return (t->raw_name);
}

thing_tiles tp_get_tiles (tpp t)
{_
    return (t->tiles);
}

thing_tiles tp_get_left_tiles (tpp t)
{_
    return (t->left_tiles);
}

thing_tiles tp_get_right_tiles (tpp t)
{_
    return (t->right_tiles);
}

thing_tiles tp_get_top_tiles (tpp t)
{_
    return (t->top_tiles);
}

thing_tiles tp_get_bot_tiles (tpp t)
{_
    return (t->bot_tiles);
}

thing_tiles tp_get_tl_tiles (tpp t)
{_
    return (t->tl_tiles);
}

thing_tiles tp_get_tr_tiles (tpp t)
{_
    return (t->tr_tiles);
}

thing_tiles tp_get_bl_tiles (tpp t)
{_
    return (t->bl_tiles);
}

thing_tiles tp_get_br_tiles (tpp t)
{_
    return (t->br_tiles);
}

thing_tiles tp_get_horiz_tiles (tpp t)
{_
    return (t->horiz_tiles);
}

thing_tiles tp_get_vert_tiles (tpp t)
{_
    return (t->vert_tiles);
}

thing_tiles tp_get_l90_tiles (tpp t)
{_
    return (t->l90_tiles);
}

thing_tiles tp_get_l180_tiles (tpp t)
{_
    return (t->l180_tiles);
}

thing_tiles tp_get_l_tiles (tpp t)
{_
    return (t->l_tiles);
}

thing_tiles tp_get_l270_tiles (tpp t)
{_
    return (t->l270_tiles);
}

thing_tiles tp_get_t_tiles (tpp t)
{_
    return (t->t_tiles);
}

thing_tiles tp_get_t90_tiles (tpp t)
{_
    return (t->t90_tiles);
}

thing_tiles tp_get_t180_tiles (tpp t)
{_
    return (t->t180_tiles);
}

thing_tiles tp_get_t270_tiles (tpp t)
{_
    return (t->t270_tiles);
}

thing_tiles tp_get_x_tiles (tpp t)
{_
    return (t->x_tiles);
}

tilep tp_first_tile (tpp tp)
{_
    auto tiles = tp_get_tiles(tp);

    if (tiles.empty()) {
        DIE("tp %s has no tiles", tp_name(tp).c_str());
    }

    /*
     * Get the first anim tile.
     */
    auto thing_tile = thing_tile_first(tiles);

    return (thing_tile->tile);
}
