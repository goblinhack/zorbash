//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#ifndef _MY_THING_TILE_H
#define _MY_THING_TILE_H

#include <map>
#include <memory>

typedef class Tileinfo* Tileinfop;
typedef std::vector< class Tileinfo* > Tileinfomap;

#include "my_tile.h"

class Tileinfo {
private:

public:
    Tileinfo (void)
    {
        newptr(this, "Tileinfo");
    }

    ~Tileinfo (void)
    {
        oldptr(this);
    }

    uint32_t index {}; // key 
    std::string tilename;
    Tilep tile;

    //
    // Delay in ms between frames.
    //
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
    bool is_hp_25_percent {};
    bool is_hp_50_percent {};
    bool is_hp_75_percent {};
    bool is_hp_100_percent {};
    bool is_sleeping {};
    bool is_open {};
    bool is_dead {};
    bool is_end_of_anim {};
    bool is_dead_on_end_of_anim {};
    bool internal_has_dir_anim {};
};

void tile_info_free(Tileinfop);
std::string tile_info_name(Tileinfop);
uint32_t tile_info_delay_ms(Tileinfop);
uint32_t tile_info_move(Tileinfop);
uint8_t tile_info_is_moving(Tileinfop);
uint8_t tile_info_is_dir_up(Tileinfop);
uint8_t tile_info_is_dir_down(Tileinfop);
uint8_t tile_info_is_dir_left(Tileinfop);
uint8_t tile_info_is_dir_right(Tileinfop);
uint8_t tile_info_is_dir_none(Tileinfop);
uint8_t tile_info_is_dir_tl(Tileinfop);
uint8_t tile_info_is_dir_bl(Tileinfop);
uint8_t tile_info_is_dir_tr(Tileinfop);
uint8_t tile_info_is_dir_br(Tileinfop);
uint8_t tile_info_is_yyy5(Tileinfop);
uint8_t tile_info_is_yyy6(Tileinfop);
uint8_t tile_info_is_yyy7(Tileinfop);
uint8_t tile_info_is_yyy8(Tileinfop);
uint8_t tile_info_is_yyy9(Tileinfop);
uint8_t tile_info_is_yyy10(Tileinfop);
uint8_t tile_info_is_hp_25_percent(Tileinfop);
uint8_t tile_info_is_hp_50_percent(Tileinfop);
uint8_t tile_info_is_hp_75_percent(Tileinfop);
uint8_t tile_info_is_hp_100_percent(Tileinfop);
uint8_t tile_info_is_moving(Tileinfop);
uint8_t tile_info_is_sleeping(Tileinfop);
uint8_t tile_info_is_open(Tileinfop);
uint8_t tile_info_is_dead(Tileinfop);
uint8_t tile_info_is_end_of_anim(Tileinfop);
uint8_t tile_info_is_dead_on_end_of_anim(Tileinfop);

Tileinfop tile_info_first(Tileinfomap *root);
Tileinfop tile_info_random(Tileinfomap *root);
Tileinfop tile_info_next(Tileinfomap *root, Tileinfop in);

#endif // THING_TILE_H 
