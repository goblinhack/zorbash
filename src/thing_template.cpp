//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_level.h"
#include "my_thing_template.h"
#include "my_depth.h"
#include "my_tile.h"
#include "my_dice.h"
#include "my_random.h"
#include "my_array_bounds_check.h"
#include "my_vector_bounds_check.h"
#include "my_ptrcheck.h"
#include "my_thing_template.h"
#include "my_ptrcheck.h"

Tpnamemap tp_name_map;
Tpidmap tp_id_map;

static uint8_t tp_init_done;

Tp::Tp (void) {
    newptr(this, "Tp");
}

Tp::~Tp (void) {
    oldptr(this);
}

Tpp tp_find (const std::string &name)
{_
    auto result = tp_name_map.find(name);

    if (unlikely(result == tp_name_map.end())) {
        return (0);
    }

    return (result->second);
}

Tpp tp_find (uint32_t id)
{_
    auto result = get(tp_id_map, id - 1);
    if (!result) {
        ERR("Thing template %" PRIx32 " not found", id);
    }

    return (result);
}

uint8_t tp_init (void)
{_
    tp_init_done = true;

    tp_random_init();

    return true;
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

Tpp tp_load (int id, std::string const& name, 
             const std::string &text_name,
             const std::string &short_text_name)
{_
    if (tp_find(name)) {
        ERR("Thing template name [%s] already used", name.c_str());
    }

    auto tp = new Tp();
    tp->set_name(name);
    tp->set_text_name(text_name);
    tp->set_short_text_name(short_text_name);

    auto result = tp_name_map.insert(std::make_pair(name, tp));
    if (result.second == false) {
        ERR("Thing insert name [%s] failed", name.c_str());
    }

    tp_id_map.push_back(tp);
    tp->id = tp_id_map.size();

    return (tp);
}

Tilep tp_first_tile (Tpp tp)
{_
    auto tiles = &tp->tiles;

    if (!tiles || tiles->empty()) {
        ERR("Tp %s has no tiles", tp->name().c_str());
    }

    //
    // Get the first anim tile.
    //
    return (tile_first(tiles));
}
