/*
 * Copyright (C) 2011-2020 goblinhack@gmail.com
 *
 * See the LICENSE file.
 */

#ifndef _MY_THING_TILE_H
#define _MY_THING_TILE_H

#include <map>

typedef std::shared_ptr< class thing_tile > thing_tilep;
typedef std::map< unsigned int, std::shared_ptr< class thing_tile > > thing_tiles;

#include "my_ptrcheck.h"
#include "my_tile.h"

class thing_tile {
private:

public:
    thing_tile (void)
    {
        newptr(this, "thing_tile");
    }

    ~thing_tile (void)
    {
        oldptr(this);
    }

    uint32_t index {}; /* key */
    std::string tilename;
    tilep tile;

    /*
     * Delay in ms between frames.
     */
    uint32_t delay_ms {};
    int dir {};

    bool is_join_node {};
    bool is_join_left {};
    bool is_join_bot {};
    bool is_join_right {};
    bool is_join_top {};
    bool is_join_horiz {};
    bool is_join_vert {};
    bool is_join_l90 {};
    bool is_join_l {};
    bool is_join_l270 {};
    bool is_join_l180 {};
    bool is_join_t270 {};
    bool is_join_t180 {};
    bool is_join_t90 {};
    bool is_join_t {};
    bool is_join_x {};

    bool is_moving {};
    bool is_yyy5 {};
    bool is_yyy6 {};
    bool is_yyy7 {};
    bool is_yyy8 {};
    bool is_yyy9 {};
    bool is_yyy10 {};
    bool is_yyy11 {};
    bool is_yyy12 {};
    bool is_yyy13 {};
    bool is_yyy14 {};
    bool is_sleeping {};
    bool is_open {};
    bool is_dead {};
    bool is_end_of_anim {};
    bool is_dead_on_end_of_anim {};
    bool has_dir_anim {};
};

void thing_tile_free(thing_tilep);
std::string thing_tile_name(thing_tilep);
uint32_t thing_tile_delay_ms(thing_tilep);
uint32_t thing_tile_move(thing_tilep);
uint8_t thing_tile_is_moving(thing_tilep);
uint8_t thing_tile_is_dir_up(thing_tilep);
uint8_t thing_tile_is_dir_down(thing_tilep);
uint8_t thing_tile_is_dir_left(thing_tilep);
uint8_t thing_tile_is_dir_right(thing_tilep);
uint8_t thing_tile_is_dir_none(thing_tilep);
uint8_t thing_tile_is_dir_tl(thing_tilep);
uint8_t thing_tile_is_dir_bl(thing_tilep);
uint8_t thing_tile_is_dir_tr(thing_tilep);
uint8_t thing_tile_is_dir_br(thing_tilep);
uint8_t thing_tile_is_yyy5(thing_tilep);
uint8_t thing_tile_is_yyy6(thing_tilep);
uint8_t thing_tile_is_yyy7(thing_tilep);
uint8_t thing_tile_is_yyy8(thing_tilep);
uint8_t thing_tile_is_yyy9(thing_tilep);
uint8_t thing_tile_is_yyy10(thing_tilep);
uint8_t thing_tile_is_yyy11(thing_tilep);
uint8_t thing_tile_is_yyy12(thing_tilep);
uint8_t thing_tile_is_yyy13(thing_tilep);
uint8_t thing_tile_is_yyy14(thing_tilep);
uint8_t thing_tile_is_moving(thing_tilep);
uint8_t thing_tile_is_sleeping(thing_tilep);
uint8_t thing_tile_is_open(thing_tilep);
uint8_t thing_tile_is_dead(thing_tilep);
uint8_t thing_tile_is_end_of_anim(thing_tilep);
uint8_t thing_tile_is_dead_on_end_of_anim(thing_tilep);

thing_tilep thing_tile_first(thing_tiles root);
thing_tilep thing_tile_random(thing_tiles root);
thing_tilep thing_tile_next(thing_tiles root, thing_tilep in);

#endif /* THING_TILE_H */
