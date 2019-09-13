//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#ifndef _MY_GAME_H_
#define _MY_GAME_H_

#include "my_sdl.h"
#include "my_dmap.h"
#include "my_terrain.h"
#include <array>
#include <list>
#include <unordered_map>

struct Thing_;
class Light;

typedef class Light* Lightp;
typedef std::unordered_map< uint32_t, Lightp > Lights;

typedef class World* Worldp;

#include "my_thing.h"

enum {
    MAP_DEPTH_FLOOR,
    MAP_DEPTH_WATER,
    MAP_DEPTH_LAVA,
    MAP_DEPTH_BLOOD,
#define MAP_DEPTH_LAST_FLOOR_TYPE MAP_DEPTH_BLOOD
    MAP_DEPTH_SOIL,
    MAP_DEPTH_GRASS,
    MAP_DEPTH_GRAVEL,
    MAP_DEPTH_SNOW,
    MAP_DEPTH_FLOOR_DECO,
    MAP_DEPTH_WALLS,
    MAP_DEPTH_WALLS_DECO,
    MAP_DEPTH_EXIT,
    MAP_DEPTH_ITEM,
    MAP_DEPTH_FOOD,
    MAP_DEPTH_MONST,
    MAP_DEPTH_PLAYER,
    MAP_DEPTH_WEAPON,
    MAP_DEPTH,
};

class World {
private:
    //
    // These are caches for fast lookup in display code
    //
    std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> _is_wall;
    std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> _is_gfx_large_shadow_caster;
    std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> _is_light;
    std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> _is_floor;
    std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> _is_lava;
    std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> _is_blood;
    std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> _is_water;
    std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> _is_deep_water;
    std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> _is_corridor;
    std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> _is_dirt;
    std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> _is_grass;
    std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> _is_soil;
    std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> _is_gravel;
    std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> _is_snow;
    std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> _is_rock;
public:
    //
    // The player!
    //
    Thingp                     player = {};

    //
    // Global lights
    //
    Lights                     all_lights;

    //
    // Where we're looking in the map
    //
    fpoint                     map_at;
    fpoint                     map_wanted_at;
    point                      map_tile_over;

    //
    // World map
    //
    Terrainp                   terrain {};

    //
    // All things. The location forms the ID.
    //
    std::array<
      std::array<
        std::array<Thingp, MAP_SLOTS>, MAP_HEIGHT>, MAP_WIDTH> 
          all_thing_ptrs_at;
    //
    // All lights at a map cell
    //
    std::unordered_map<uint32_t, Lightp> lights[MAP_WIDTH][MAP_HEIGHT];

    //
    // All thing IDs
    //
    std::array<
      std::array<
        std::array<uint32_t, MAP_SLOTS>, MAP_HEIGHT>, MAP_WIDTH> 
          all_thing_ids_at;

    void put_thing_ptr(uint16_t x, uint16_t y, Thingp t);
    void remove_thing_ptr(Thingp t);

    static const uint32_t x_bits = 10;
    static const uint32_t x_mask = (1<<x_bits)-1;

    static const uint32_t y_bits = 10;
    static const uint32_t y_shift = x_bits;
    static const uint32_t y_mask = ((1<<y_bits)-1) << y_shift;

    static const uint32_t slots_bits = 4;
    static const uint32_t slots_shift = x_bits + y_bits;
    static const uint32_t slots_mask = ((1<<slots_bits)-1) << slots_shift;

    static const uint32_t r_shift = x_bits + y_bits + slots_bits;

    Thingp find_thing_ptr (uint32_t id)
    {
        uint32_t x = id & x_mask;
        uint32_t y = (id & y_mask) >> y_shift;
        uint32_t slot = (id & slots_mask) >> slots_shift;

        auto p = &all_thing_ptrs_at[x][y][slot];
        if (unlikely(!*p)) {
            DIE("thing ptr not found at x %u y %u slot %u for id %u", x, y, slot, id);
        }

        auto t = *p;
        if ((t->id != id)) {
            t->die("thing mismatch at x %u y %u slot %u, my id is %u, but on-map id is %u. Usually this means a thing was not removed cleanly at level end.", x, y, slot, t->id, id);
        }

        verify(t);
        return (t);
    }

    void remove_thing(int x, int y, uint32_t id);
    void remove_thing(point p, uint32_t id);

    void put_thing(int x, int y, uint32_t id);
    void put_thing(point p, uint32_t id);

    #define JOIN1(X,Y) X##Y
    #define JOIN(X,Y) JOIN1(X,Y)

    //
    // Display depth filter
    //
    #define FOR_ALL_THINGS(world, t, x, y, z)                          \
        static std::vector<Thingp> JOIN1(tmp, __LINE__);               \
        world->get_all_things_at_depth(x, y, z, JOIN1(tmp, __LINE__)); \
        for (auto t : JOIN1(tmp, __LINE__))
    void get_all_things_at_depth(int x, int y, int z, std::vector<Thingp> &);

    //
    // Things that move around and things that do not, but are interesting,
    // like food
    //
    #define FOR_ALL_INTERESTING_THINGS(world, t, x, y)                    \
        static std::vector<Thingp> JOIN1(tmp, __LINE__);                  \
        world->get_all_interesting_things_at(x, y, JOIN1(tmp, __LINE__)); \
        for (auto t : JOIN1(tmp, __LINE__))
    void get_all_interesting_things_at(int x, int y, std::vector<Thingp> &);

    //
    // Things that move around
    //
    #define FOR_ALL_ACTIVE_THINGS(world, t, x, y)                    \
        static std::vector<Thingp> JOIN1(tmp, __LINE__);             \
        world->get_all_active_things_at(x, y, JOIN1(tmp, __LINE__)); \
        for (auto t : JOIN1(tmp, __LINE__))
    void get_all_active_things_at(int x, int y, std::vector<Thingp> &);

    //
    // Things that block progress
    //
    #define FOR_ALL_OBSTACLE_THINGS(world, t, x, y)                    \
        static std::vector<Thingp> JOIN1(tmp, __LINE__);               \
        world->get_all_obstacle_things_at(x, y, JOIN1(tmp, __LINE__)); \
        for (auto t : JOIN1(tmp, __LINE__))
    void get_all_obstacle_things_at(int x, int y, std::vector<Thingp> &);

    bool is_anything_at(const int x, const int y);
    bool is_anything_at(const point &p);
    bool is_blood(const int x, const int y);
    bool is_blood(const point &p);
    bool is_corridor(const int x, const int y);
    bool is_corridor(const point &p);
    bool is_deep_water(const int x, const int y);
    bool is_deep_water(const point &p);
    bool is_dirt(const int x, const int y);
    bool is_dirt(const point &p);
    bool is_door(const int x, const int y);
    bool is_door(const point &p);
    bool is_floor(const int x, const int y);
    bool is_floor(const point &p);
    bool is_food(const int x, const int y);
    bool is_food(const point &p);
    bool is_gfx_large_shadow_caster(const int x, const int y);
    bool is_gfx_large_shadow_caster(const point &p);
    bool is_grass(const int x, const int y);
    bool is_grass(const point &p);
    bool is_gravel(const int x, const int y);
    bool is_gravel(const point &p);
    bool is_key(const int x, const int y);
    bool is_key(const point &p);
    bool is_lava(const int x, const int y);
    bool is_lava(const point &p);
    bool is_light(const int x, const int y);
    bool is_light(const point &p);
    bool is_monst(const int x, const int y);
    bool is_monst(const point &p);
    bool is_oob(const fpoint p);
    bool is_oob(const int x, const int y);
    bool is_oob(const int x, const int y, const int z);
    bool is_oob(const point p);
    bool is_rock(const int x, const int y);
    bool is_rock(const point &p);
    bool is_snow(const int x, const int y);
    bool is_snow(const point &p);
    bool is_soil(const int x, const int y);
    bool is_soil(const point &p);
    bool is_wall(const int x, const int y);
    bool is_wall(const point &p);
    bool is_water(const int x, const int y);
    bool is_water(const point &p);
    void clear(void);
    void dir_sett(const int x, const int y);
    void set_blood(const int x, const int y);
    void set_corridor(const int x, const int y);
    void set_deep_water(const int x, const int y);
    void set_floor(const int x, const int y);
    void set_gfx_large_shadow_caster(const int x, const int y);
    void set_grass(const int x, const int y);
    void set_gravel(const int x, const int y);
    void set_lava(const int x, const int y);
    void set_light(const int x, const int y);
    void set_rock(const int x, const int y);
    void set_snow(const int x, const int y);
    void set_soil(const int x, const int y);
    void set_wall(const int x, const int y);
    void set_water(const int x, const int y);
    void undir_sett(const int x, const int y);
    void unset_blood(const int x, const int y);
    void unset_corridor(const int x, const int y);
    void unset_deep_water(const int x, const int y);
    void unset_floor(const int x, const int y);
    void unset_gfx_large_shadow_caster(const int x, const int y);
    void unset_grass(const int x, const int y);
    void unset_gravel(const int x, const int y);
    void unset_lava(const int x, const int y);
    void unset_light(const int x, const int y);
    void unset_rock(const int x, const int y);
    void unset_snow(const int x, const int y);
    void unset_soil(const int x, const int y);
    void unset_wall(const int x, const int y);
    void unset_water(const int x, const int y);

    void fini(void);
    void dump(std::string prefix, std::ostream &out);
    friend std::ostream& operator<<(std::ostream &out, Bits<const World & > const my);
    friend std::istream& operator>>(std::istream &in, Bits<World &> my);
};

typedef struct {
public:
    bool               fps_counter                  = true;
    uint32_t           sound_volume                 = {};
    uint32_t           music_volume                 = {};
    bool               vsync_enable                 = true;
    bool               full_screen                  = false;
    int32_t            video_pix_width              = {};
    int32_t            video_pix_height             = {};
    double             video_gl_width               = {};
    double             video_gl_height              = {};
    double             video_w_h_ratio              = {};
    int32_t            drawable_gl_width            = {};
    int32_t            drawable_gl_height           = {};
    double             tile_gl_width                = {};
    double             tile_gl_height               = {};
    double             one_pixel_gl_width           = {};
    double             one_pixel_gl_height          = {};
    double             ascii_gl_width               = {};
    double             ascii_gl_height              = {};
    double             tile_pixel_width             = {};
    double             tile_pixel_height            = {};
    uint32_t           sdl_delay                    = 1;

    void fini(void);
    void dump(std::string prefix, std::ostream &out);
} Config;
std::ostream& operator<<(std::ostream &out, Bits<const Config & > const my);
std::istream& operator>>(std::istream &in, Bits<Config &> my);

class Game {
public:
    Game (void) {}
    Game (std::string appdata);
    void init(void);
    void fini(void);
    void save(void);
    void load(void);
    void display(void);

    std::string        appdata;
    std::string        saved_dir;
    std::string        saved_file;

    Config             config;
    World              world;
    int                seed {};
    uint32_t           fps_count = {};

    friend std::ostream& operator<<(std::ostream &out, 
                                    Bits<const class Game & > const my);
    friend std::istream& operator>>(std::istream &in, 
                                    Bits<class Game &> my);
    void dump(std::string prefix, std::ostream &out);
};

extern class Game *game;
extern class World *world;

uint8_t game_mouse_motion(int32_t x, int32_t y, int32_t wheelx, int32_t wheely);
void game_mouse_over(int32_t x, int32_t y, int32_t wheelx, int32_t wheely);
uint8_t game_mouse_down(int32_t x, int32_t y, uint32_t button);
uint8_t game_key_down(const struct SDL_KEYSYM *key);
void player_tick(void);

#endif
