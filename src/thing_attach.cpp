//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"

void Thing::attach (void)
{_
    detach();

    auto p = std::make_pair(id, this);

    {
        auto root = &game.state.map.all_display_things_at[(int)mid_at.x][(int)mid_at.y][depth];
        struct ThingDisplaySortKey key = {(int16_t)(int)br.y, id};
        auto result = root->insert(std::make_pair(key, this));
        if (result.second == false) {
            die("failed to insert to game.state.map.all_things_at");
        }
    }

    {
        auto root = &game.state.map.all_things_at[(int)mid_at.x][(int)mid_at.y];
        auto result = root->insert(p);
        if (result.second == false) {
            die("failed to insert to game.state.map.all_things_at");
        }
    }

    if (is_active()) {
        auto root = &game.state.map.all_active_things_at[(int)mid_at.x][(int)mid_at.y];
        auto result = root->insert(p);
        if (result.second == false) {
            die("failed to insert to game.state.map.all_active_things_at");
        }
    }

    if (!does_nothing()) {
        auto root = &game.state.map.all_interesting_things_at[(int)mid_at.x][(int)mid_at.y];
        auto result = root->insert(p);
        if (result.second == false) {
            die("failed to insert to game.state.map.all_interesting_things_at");
        }
    }

    if (is_obstacle()) {
        auto root = &game.state.map.all_obstacle_things_at[(int)mid_at.x][(int)mid_at.y];
        auto result = root->insert(p);
        if (result.second == false) {
            die("failed to insert to game.state.map.all_obstacle_things_at");
        }
    }

    is_attached = true;
    last_attached = mid_at;
//log("attached at %d %d %d", (int)last_attached.x, (int)last_attached.y,
//depth);
}

void Thing::detach (void)
{_
    if (!is_attached) {
        return;
    }
    is_attached = false;
//log("detach from %d %d %d", (int)last_attached.x, (int)last_attached.y,
//depth);
    {
        auto root = &game.state.map.all_display_things_at[(int)last_attached.x]
                                                         [(int)last_attached.y][depth];
        struct ThingDisplaySortKey key = {(int16_t)(int)br.y, id};
        auto result = root->find(key);
        if (result == root->end()) {
            die("failed to remove from game.state.map.all_things_at");
        }

        root->erase(key);
    }

    {
        auto root = &game.state.map.all_things_at[(int)last_attached.x]
                                                 [(int)last_attached.y];
        auto result = root->find(id);
        if (result == root->end()) {
            die("failed to remove from game.state.map.all_things_at");
        }
        root->erase(id);
    }

    if (is_active()) {
        auto root = &game.state.map.all_active_things_at[(int)last_attached.x]
                                                        [(int)last_attached.y];
        auto result = root->find(id);
        if (result == root->end()) {
            die("failed to remove from game.state.map.all_active_things_at");
        }
        root->erase(id);
    }

    if (!does_nothing()) {
        auto root = &game.state.map.all_interesting_things_at[(int)last_attached.x]
                                                            [(int)last_attached.y];
        auto result = root->find(id);
        if (result == root->end()) {
            die("failed to remove from game.state.map.all_interesting_things_at");
        }
        root->erase(id);
    }

    if (is_obstacle()) {
        auto root = &game.state.map.all_obstacle_things_at[(int)last_attached.x]
                                                            [(int)last_attached.y];
        auto result = root->find(id);
        if (result == root->end()) {
            die("failed to remove from game.state.map.all_obstacle_things_at");
        }
        root->erase(id);
    }
}
