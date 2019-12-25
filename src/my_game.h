//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#ifndef _MY_GAME_H_
#define _MY_GAME_H_

#include "my_sdl.h"
#include "my_dmap.h"
#include <array>
#include <list>
#include <unordered_map>

struct Thing_;
class Light;

typedef class Light* Lightp;
typedef class World* Worldp;

#include "my_thing.h"

enum {
    MAP_DEPTH_FLOOR,
    MAP_DEPTH_WATER,
    MAP_DEPTH_LAVA,
    MAP_DEPTH_BLOOD,
#define MAP_DEPTH_LAST_FLOOR_TYPE MAP_DEPTH_BLOOD
    MAP_DEPTH_FLOOR_DECO,
    MAP_DEPTH_WALLS,
    MAP_DEPTH_WALLS_DECO,
    MAP_DEPTH_EXIT,
    MAP_DEPTH_ITEM,
    MAP_DEPTH_MONST,
    MAP_DEPTH_PLAYER,
    MAP_DEPTH_WEAPON,
    MAP_DEPTH_CURSOR,
    MAP_DEPTH,
};

class World {
private:
    //
    // These are caches for fast lookup in display code
    //
    std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> _is_blood {};
    std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> _is_corridor {};
    std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> _is_deep_water {};
    std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> _is_dirt {};
    std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> _is_floor {};
    std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> _is_gfx_large_shadow_caster {};
    std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> _is_lava {};
    std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> _is_rock {};
    std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> _is_visited {};
    std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> _is_dungeon {};
    std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> _is_wall {};
    std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> _is_water {};
public:
    //
    // When this world was made. Used to restore timestamps relative to this.
    //
    timestamp_t                   timestamp_dungeon_created {};
    timestamp_t                   timestamp_dungeon_saved {};

    bool                       cursor_needs_update = false;
    bool                       cursor_found = false;
    fpoint                     cursor_at;
    fpoint                     cursor_at_old;
    bool                       map_follow_player = true;
    fpoint                     map_at;        // map scroll currently st
    fpoint                     map_wanted_at; // map scroll desired at
    bool                       minimap_valid = false;
    int                        mouse {-1};    // ticks for every move
    int                        mouse_old {-1};
    uint8_t                    next_thing_id {};

    Thingp                     player = {};
    Thingp                     cursor = {};

    //
    // All things. The array index is part of the thing ID
    //
    struct Thing_entropy {
        Thingp   ptr;
        uint32_t id;
    };
    std::array<struct Thing_entropy, MAX_THINGS> all_thing_ptrs {};

    //
    // All thing IDs
    //
    std::array<
      std::array<
        std::array<uint32_t, MAP_SLOTS>, MAP_HEIGHT>, MAP_WIDTH> 
          all_thing_ids_at {};

    void alloc_thing_id(Thingp t);
    void realloc_thing_id(Thingp t);
    void free_thing_id(Thingp t);
    Thingp test_thing_ptr(uint32_t id);
    Thingp find_thing_ptr(uint32_t id);

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
    // Things that emit light
    //
    #define FOR_ALL_LIGHT_SOURCE_THINGS(world, t, x, y)                    \
        static std::vector<Thingp> JOIN1(tmp, __LINE__);                   \
        world->get_all_light_source_things_at(x, y, JOIN1(tmp, __LINE__)); \
        for (auto t : JOIN1(tmp, __LINE__))
    void get_all_light_source_things_at(int x, int y, std::vector<Thingp> &);

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

    void clear(void);
    bool is_anything_at(const int x, const int y);
    bool is_anything_at(const point &p);
    bool is_door(const int x, const int y);
    bool is_door(const point &p);
    bool is_food(const int x, const int y);
    bool is_food(const point &p);
    bool is_key(const int x, const int y);
    bool is_key(const point &p);
    bool is_monst(const int x, const int y);
    bool is_monst(const point &p);

    bool is_floor(const int x, const int y);
    bool is_floor(const point &p);
    void set_floor(const int x, const int y);
    void unset_floor(const int x, const int y);

    bool is_corridor(const int x, const int y);
    bool is_corridor(const point &p);
    void set_corridor(const int x, const int y);
    void unset_corridor(const int x, const int y);

    bool is_blood(const int x, const int y);
    bool is_blood(const point &p);
    void set_blood(const int x, const int y);
    void unset_blood(const int x, const int y);

    bool is_wall(const int x, const int y);
    bool is_wall(const point &p);
    void set_wall(const int x, const int y);
    void unset_wall(const int x, const int y);

    bool is_water(const int x, const int y);
    bool is_water(const point &p);
    void set_water(const int x, const int y);
    void unset_water(const int x, const int y);

    bool is_gfx_large_shadow_caster(const int x, const int y);
    bool is_gfx_large_shadow_caster(const point &p);
    void set_gfx_large_shadow_caster(const int x, const int y);
    void unset_gfx_large_shadow_caster(const int x, const int y);

    bool is_lava(const int x, const int y);
    bool is_lava(const point &p);
    void set_lava(const int x, const int y);
    void unset_lava(const int x, const int y);

    bool is_deep_water(const int x, const int y);
    bool is_deep_water(const point &p);
    void set_deep_water(const int x, const int y);
    void unset_deep_water(const int x, const int y);

    bool is_dirt(const int x, const int y);
    bool is_dirt(const point &p);
    void set_dirt(const int x, const int y);
    void unset_dirt(const int x, const int y);

    bool is_rock(const int x, const int y);
    bool is_rock(const point &p);
    void set_rock(const int x, const int y);
    void unset_rock(const int x, const int y);

    bool is_visited(const int x, const int y);
    bool is_visited(const point &p);
    void set_visited(const int x, const int y);
    void unset_visited(const int x, const int y);

    bool is_dungeon(const int x, const int y);
    bool is_dungeon(const point &p);
    void set_dungeon(const int x, const int y);
    void unset_dungeon(const int x, const int y);

    static inline bool is_oob (const int x, const int y, const int z)
    {
        return ((x < 0) || (x >= MAP_WIDTH) ||
                (y < 0) || (y >= MAP_HEIGHT) ||
                (z < 0) || (z >= MAP_DEPTH));
    }

    static inline bool is_oob (const int x, const int y)
    {
        return ((x < 0) || (x >= MAP_WIDTH) ||
                (y < 0) || (y >= MAP_HEIGHT));
    }

    static inline bool is_oob (const fpoint p)
    {
        return ((p.x < 0) || (p.x >= MAP_WIDTH) ||
                (p.y < 0) || (p.y >= MAP_HEIGHT));
    }

    static inline bool is_oob (const point p)
    {
        return ((p.x < 0) || (p.x >= MAP_WIDTH) ||
                (p.y < 0) || (p.y >= MAP_HEIGHT));
    }

    void fini(void);
    void dump(std::string prefix, std::ostream &out);
    friend std::ostream& operator<<(std::ostream &out, Bits<const World & > const my);
    friend std::istream& operator>>(std::istream &in, Bits<World &> my);
};

typedef struct {
public:
    bool               fps_counter                  = true;
#ifdef ENABLE_INVERTED_GFX
    bool               gfx_inverted                 = true;
#else
    bool               gfx_inverted                 = false;
#endif
    bool               gfx_minimap                  = true;
    bool               gfx_show_hidden              = false;
    bool               gfx_lights                   = true;
    uint32_t           gfx_zoom                     = 4;
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
    void update_minimap(void);

    std::string        appdata;
    std::string        saved_dir;
    std::string        saved_file;

    Config             config;
    World              world;
    int                seed {};
    fpoint             mouse_over;
    uint32_t           fps_count = {};

    friend std::ostream& operator<<(std::ostream &out, 
                                    Bits<const class Game & > const my);
    friend std::istream& operator>>(std::istream &in, 
                                    Bits<class Game &> my);
    void dump(std::string prefix, std::ostream &out);
};

extern class Game *game;
extern class World *world;
extern bool thing_map_black_and_white;

uint8_t game_mouse_motion(int32_t x, int32_t y, int32_t wheelx, int32_t wheely);
void game_mouse_over(int32_t x, int32_t y, int32_t wheelx, int32_t wheely);
uint8_t game_mouse_down(int32_t x, int32_t y, uint32_t button);
uint8_t game_key_down(const struct SDL_KEYSYM *key);
void player_tick(void);

//
// Find an existing thing.
//
static inline Thingp thing_find (const uint32_t id)
{
    return (world->find_thing_ptr(id));
}

#define HEAP_ALLOC(var,size) \
    void *var; \
    posix_memalign(&var, sizeof(lzo_align_t), size + size / 16 + 64 + 3);

#endif
