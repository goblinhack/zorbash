//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once
#ifndef _MY_TILE_H_
#define _MY_TILE_H_

#include "my_main.h"
#include "my_sdl.h"
#include "my_globals.h"
#include "my_point.h"
#include "my_color.h"

class Tile {
public:
    Tile (void) {
        newptr(this, "Tile");
    }
    ~Tile (void) {
        oldptr(this);
    }
    Tile (const class Tile *tile);

    std::string name;

    //
    // Grabbed by a template
    //
    uint8_t in_use {};
    uint16_t global_index;

    //
    // Index within the overall texture, left to right, top to bottom.
    //
    uint16_t index {};

    //
    // IF this tile has a specific outline pattern, like water ripples,
    // then this is the jump to that outline within the same texture
    //
    uint16_t gfx_outline_index_offset {};

    uint16_t pix_width {};
    uint16_t pix_height {};

    float pct_width {};
    float pct_height {};

    //
    // Texture co-ordinates within the image.
    //
    float x1 {};
    float y1 {};
    float x2 {};
    float y2 {};

#ifdef ENABLE_TILE_BOUNDS
    //
    // As above but not clipped 0.5 pixels. Actually we do not clip anymore,
    // it didn't help. Best to choose a resolution that works.
    //
    float ox1 {};
    float oy1 {};
    float ox2 {};
    float oy2 {};

    //
    // Percentage points that indicate the start of the pixels within the tile
    // texture for use in collisions.
    //
    float px1 {};
    float py1 {};
    float px2 {};
    float py2 {};
#endif

    Texp tex {};
    Texp tex_black_and_white {};

    std::array<std::array<uint8_t, TILE_HEIGHT_MAX>, TILE_WIDTH_MAX> pix {};

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
    bool is_outline {};

    bool is_moving {};
    bool is_yyy5 {};
    bool is_yyy6 {};
    bool is_yyy7 {};
    bool is_yyy8 {};
    bool is_yyy9 {};
    bool is_invisible {};
    bool is_hp_25_percent {};
    bool is_hp_50_percent {};
    bool is_hp_75_percent {};
    bool is_hp_100_percent {};
    bool is_sleeping {};
    bool is_open {};
    bool is_dead {};
    bool is_end_of_anim {};
    bool is_dead_on_end_of_anim {};
    bool is_resurrecting {};
    bool is_alive_on_end_of_anim {};
    bool internal_has_dir_anim {};

private:
    int32_t _gl_binding {};
    int32_t _gl_binding_black_and_white {};
public:
    int32_t gl_binding (void) const;
    void set_gl_binding (int32_t v);
    int32_t gl_binding_black_and_white (void) const;
    void set_gl_binding_black_and_white (int32_t v);
};

typedef class Tile* Tilep;

static inline Tilep tile_index_to_tile (uint16_t i)
{
    if (!i) {
        return (nullptr);
    } else {
        return all_tiles_array[i - 1 ];
    }
}

uint8_t tile_init(void);
void tile_fini(void);
void tile_load(std::string file, uint32_t width, uint32_t height,
               uint32_t nargs, ...);
void tile_load_arr(std::string file,
                   std::string tex_name,
                   uint32_t width, uint32_t height,
                   uint32_t nargs, const char * arr[]);
void tile_load_arr(std::string file,
                   std::string tex_name,
                   uint32_t width, uint32_t height,
                   std::vector<std::string> arr);
void tile_load_arr_color_and_black_and_white(std::string file,
                                             std::string tex_name,
                                             uint32_t width, uint32_t height,
                                             uint32_t nargs,
                                             const char * arr[]);
Tilep tile_find(std::string name);
Tilep tile_find_mand(std::string name);
Tilep tile_from_surface(SDL_Surface *surface,
                        std::string optional_file,
                        std::string name);
std::string tile_get_name(Tilep);
int32_t tile_get_width(Tilep);
int32_t tile_get_height(Tilep);
Texp tile_get_tex(Tilep);
uint32_t tile_get_index(Tilep);
Tilep string2tile(const char **s);
Tilep string2tile(std::string &s, int *len);
Tilep string2tile(std::wstring &s, int *len);
void tile_get_coords(Tilep, float *x1, float *y1, float *x2, float *y2);
void tile_blit_colored_fat(Tpp tp,
                           Tilep tile,
                           point tl,
                           point br,
                           color color_tl,
                           color color_tr,
                           color color_bl,
                           color color_br);
void tile_blit_colored(Tilep tile,
                       point tl,
                       point br,
                       color color_tl,
                       color color_tr,
                       color color_bl,
                       color color_br);

//
// Blits a whole tile. Y co-ords are inverted.
//
void tile_blit(const Tpp &tp,
               const Tilep &tile,
               const point &tl,
               const point &br);
void tile_blit(const Tpp &tp,
               uint16_t index,
               const point &tl,
               const point &br);
void tile_blit(const Tilep &tile,
               const point &tl,
               const point &br);
void tile_blit(const Tilep &tile,
               const point &tl,
               const point &tr,
               const point &bl,
               const point &br);
void tile_blit(uint16_t index,
               const point &tl,
               const point &br);
void tile_blit_section(const Tilep &tile,
                       const point &tile_tl,
                       const point &tile_br,
                       const point &tl,
                       const point &br);
void tile_blit_section(uint16_t index,
                       const point &tile_tl,
                       const point &tile_br,
                       const point &tl,
                       const point &br);
void tile_blit_section_colored(const Tilep &tile,
                               const fpoint &tile_tl,
                               const fpoint &tile_br,
                               const point &tl,
                               const point &br,
                               color color_bl, color color_br,
                               color color_tl, color color_tr);
void tile_blit_section_colored(uint16_t index,
                               const fpoint &tile_tl,
                               const fpoint &tile_br,
                               const point &tl,
                               const point &br,
                               color color_bl, color color_br,
                               color color_tl, color color_tr);
void tile_blit_outline_section_colored(const Tilep &tile,
                                       const fpoint &tile_tl,
                                       const fpoint &tile_br,
                                       const point &tl,
                                       const point &br,
                                       color color_bl, color color_br,
                                       color color_tl, color color_tr);
void tile_blit_outline_section_colored(uint16_t index,
                                       const fpoint &tile_tl,
                                       const fpoint &tile_br,
                                       const point &tl,
                                       const point &br,
                                       color color_bl, color color_br,
                                       color color_tl, color color_tr);
void tile_blit_outline_section_colored(const Tilep &tile,
                                       const fpoint &tile_tl,
                                       const fpoint &tile_br,
                                       const point &tl,
                                       const point &br,
                                       color color_bl, color color_br,
                                       color color_tl, color color_tr,
                                       float scale);
void tile_blit_outline_section_colored(uint16_t index,
                                       const fpoint &tile_tl,
                                       const fpoint &tile_br,
                                       const point &tl,
                                       const point &br,
                                       color color_bl, color color_br,
                                       color color_tl, color color_tr,
                                       float scale);
void tile_blit_outline(const Tilep &tile,
                       const point &tl,
                       const point &br,
                       const color &c);
void tile_blit_outline(const Tilep &tile,
                       const point &tl,
                       const point &br,
                       const color &c,
                       const color &o);
void tile_blit_outline(uint16_t index,
                       const point &tl,
                       const point &br,
                       const color &c);
void tile_blit_outline_section(uint16_t index,
                               const point &tile_tl,
                               const point &tile_br,
                               const point &tl,
                               const point &br);
void tile_blit_outline_section(const Tilep &tile,
                               const point &tile_tl,
                               const point &tile_br,
                               const point &tl,
                               const point &br);
void tile_blit_shadow(const Tpp &tp,
                      const Tilep &tile,
                      const point &tl,
                      const point &br);
void tile_blit_shadow(const Tpp &tp,
                      uint16_t index,
                      const point &tl,
                      const point &br);
void tile_blit_shadow_section(const Tpp &tp,
                              const Tilep &tile,
                              const point &tile_tl,
                              const point &tile_br,
                              const point &tl,
                              const point &br);
void tile_blit_shadow_section(const Tpp &tp,
                              uint16_t index,
                              const point &tile_tl,
                              const point &tile_br,
                              const point &tl,
                              const point &br);
void tile_blit_at(const Tilep &tile, const point tl, const point br);
void tile_blit_at(uint16_t index, const point tl, const point br);
void tile_blit(const Tilep &tile, const point at);
void tile_blit(uint16_t index, const point at);

void tile_free(Tilep);
std::string tile_name(Tilep);
uint32_t tile_delay_ms(Tilep);
uint32_t tile_move(Tilep);
uint8_t tile_is_moving(Tilep);
uint8_t tile_is_dir_up(Tilep);
uint8_t tile_is_dir_down(Tilep);
uint8_t tile_is_dir_left(Tilep);
uint8_t tile_is_dir_right(Tilep);
uint8_t tile_is_dir_none(Tilep);
uint8_t tile_is_dir_tl(Tilep);
uint8_t tile_is_dir_bl(Tilep);
uint8_t tile_is_dir_tr(Tilep);
uint8_t tile_is_dir_br(Tilep);
uint8_t tile_is_yyy5(Tilep);
uint8_t tile_is_yyy6(Tilep);
uint8_t tile_is_yyy7(Tilep);
uint8_t tile_is_yyy8(Tilep);
uint8_t tile_is_yyy9(Tilep);
uint8_t tile_is_invisible(Tilep);
uint8_t tile_is_hp_25_percent(Tilep);
uint8_t tile_is_hp_50_percent(Tilep);
uint8_t tile_is_hp_75_percent(Tilep);
uint8_t tile_is_hp_100_percent(Tilep);
uint8_t gfx_outline_index_offset(Tilep);
uint8_t tile_is_moving(Tilep);
uint8_t tile_is_sleeping(Tilep);
uint8_t tile_is_open(Tilep);
uint8_t tile_is_dead(Tilep);
uint8_t tile_is_end_of_anim(Tilep);
uint8_t tile_is_dead_on_end_of_anim(Tilep);
uint8_t tile_is_alive_on_end_of_anim(Tilep);
uint8_t tile_is_resurrecting(Tilep);

Tilep tile_first(Tilemap *root);
Tilep tile_random(Tilemap *root);
Tilep tile_n(Tilemap *root, int n);
Tilep tile_next(Tilemap *root, Tilep in);
#endif
