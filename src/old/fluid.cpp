/*
 * Copyright (C) 2017 goblinhack@gmail.com
 *
 * See the README file for license info.
 */

#include "my_main.h"
#include "my_game.h"
#include "my_fluid.h"
#include "my_thing.h"

static void fluid_place_water (int x, int y)
{
    uint16_t fx;
    uint16_t fy;

    for (fx = x * FLUID_RESOLUTION;
            fx < (x * FLUID_RESOLUTION) + FLUID_RESOLUTION;
            fx++) {
        for (fy = y * FLUID_RESOLUTION;
                fy < (y * FLUID_RESOLUTION) + FLUID_RESOLUTION;
                fy++) {

            world->fluid[fx][fy].mass = FLUID_MAX_MASS;
            world->fluid[fx][fy].type = FLUID_IS_WATER;
        }
    }
}

void fluid_init (void)
{
    int no_random_water = false;
    uint16_t x, y, z;

    memset(world->fluid, 0, sizeof(world->fluid));

    z = MAP_DEPTH_WATER;
    {
        for (y = 0; y < CHUNK_HEIGHT; y++) {
            for (x = 0; x < CHUNK_WIDTH; x++) {
                for (auto p : world->all_things_at[x][y][z]) {
                    auto t = p.second;
                    if (tp_is_water(t->tp) || tp_is_deep_water(t->tp)) {
                        t->dead("place water");
                        fluid_place_water(x, y);

                        no_random_water = true;
                    }
                }
            }
        }
    }

    for (x = 0; x < CHUNK_WIDTH; x++) {
        for (y = 0; y < CHUNK_HEIGHT; y++) {

            if (world->is_solid(x, y)) {
                fluid_place_water(x, y);
                uint16_t fx;
                uint16_t fy;

                for (fx = x * FLUID_RESOLUTION;
                     fx < (x * FLUID_RESOLUTION) + FLUID_RESOLUTION;
                     fx++) {
                    for (fy = y * FLUID_RESOLUTION;
                         fy < (y * FLUID_RESOLUTION) + FLUID_RESOLUTION;
                         fy++) {

                        world->fluid[fx][fy].mass = 0;
                        world->fluid[fx][fy].type = FLUID_IS_SOLID;
                    }
                }
            } else {

                if (no_random_water) {
                    continue;
                }

                uint16_t r;
                for (r = 0; r < 2; r++) {
                    uint16_t fx;
                    uint16_t fy;

                    fx = x * FLUID_RESOLUTION;
                    fy = y * FLUID_RESOLUTION;
                    fx += myrand() % FLUID_RESOLUTION;
                    fy += myrand() % FLUID_RESOLUTION;

                    world->fluid[fx][fy].mass = FLUID_MAX_MASS;
                    world->fluid[fx][fy].type = FLUID_IS_WATER;
                }
            }
        }
    }
}

void fluid_update (void)
{
    uint16_t x, y;

    for (x = 0; x < CHUNK_WIDTH; x++) {
        for (y = 0; y < CHUNK_HEIGHT; y++) {

            if (world->is_solid(x, y)) {
                uint16_t fx;
                uint16_t fy;

                for (fx = x * FLUID_RESOLUTION;
                     fx < (x * FLUID_RESOLUTION) + FLUID_RESOLUTION;
                     fx++) {
                    for (fy = y * FLUID_RESOLUTION;
                         fy < (y * FLUID_RESOLUTION) + FLUID_RESOLUTION;
                         fy++) {

                        world->fluid[fx][fy].mass = 0;
                        world->fluid[fx][fy].type = FLUID_IS_SOLID;
                    }
                }
            } else {
                uint16_t fx;
                uint16_t fy;

                for (fx = x * FLUID_RESOLUTION;
                     fx < (x * FLUID_RESOLUTION) + FLUID_RESOLUTION;
                     fx++) {
                    for (fy = y * FLUID_RESOLUTION;
                         fy < (y * FLUID_RESOLUTION) + FLUID_RESOLUTION;
                         fy++) {

                        if (world->fluid[fx][fy].type == FLUID_IS_SOLID) {
                            world->fluid[fx][fy].mass = 0;
                            world->fluid[fx][fy].type = FLUID_IS_AIR;
                        }
                    }
                }
            }
        }
    }
}

/*
 * Identify all the pools in a level and then just the surface tiles.
 */
#define MAX_POOLS           4000
#define MAX_POOL_SURFACE    (FLUID_WIDTH * 10)

typedef struct {
    uint16_t x;
    uint16_t y;
} xy;

static uint16_t fluid_pool[FLUID_WIDTH][FLUID_HEIGHT];
static uint8_t fluid_pool_row[FLUID_HEIGHT];
static xy fluid_pool_surface[MAX_POOLS][MAX_POOL_SURFACE];
static uint16_t fluid_pool_surface_size[MAX_POOLS];
static uint16_t max_fluid_pools;

void fluid_mass_debug (void)
{
    fluid_mass_t total_mass = 0;
    uint16_t fx, fy;

    for (fy = 1; fy < FLUID_HEIGHT - 1; fy++) {
        for (fx = 1; fx < FLUID_WIDTH - 1; fx++) {

            fluid_t *f = &world->fluid[fx][fy];
            if (!f->mass) {
                continue;
            }

            total_mass += f->mass;
        }
    }

    CON("total mass %d", total_mass);
}

void fluid_debug (void)
{
    fluid_mass_t total_mass = 0;
    uint16_t fx, fy;

    printf("\n");

    for (fy = 1; fy < FLUID_HEIGHT - 1; fy++) {
        for (fx = 1; fx < FLUID_WIDTH - 1; fx++) {

            fluid_t *f = &world->fluid[fx][fy];
            if (!f->mass) {
                if (f->type == FLUID_IS_SOLID) {
                    printf("W");
                } else {
                    printf(" ");
                }
                continue;
            }
            printf("_");

            total_mass += f->mass;
        }

        printf("\n");
    }

    CON("total mass %d", total_mass);
}

void fluid_pool_debug (void)
{
    fluid_mass_t total_mass = 0;
    uint16_t fx, fy;

    printf("\n");

    for (fy = 1; fy < FLUID_HEIGHT - 1; fy++) {
        for (fx = 1; fx < FLUID_WIDTH - 1; fx++) {

            fluid_t *f = &world->fluid[fx][fy];
            if (!f->mass) {
                if (f->type == FLUID_IS_SOLID) {
                    printf("WWW");
                } else {
                    printf("   ");
                }
                continue;
            }

            total_mass += f->mass;

            printf("%3d", fluid_pool[fx][fy]);
        }

        printf("\n");
    }

    CON("total mass %d", total_mass);
}

/*
 * Flood all connecting tiles with the same fluid pool number.
 */
static void fluid_flood_fill (uint16_t x,
                              uint16_t y, uint8_t pool_num)
{
#define STACK_PUSH(dx, dy)                                  \
                                                            \
    if ((searching[dx][dy] != pool_num) &&                  \
        !fluid_pool[dx][dy] &&                              \
        world->fluid[dx][dy].mass) {                \
                                                            \
        searching[dx][dy] = pool_num;                       \
        stack[stack_size].x = dx;                           \
        stack[stack_size].y = dy;                           \
        stack_size++;                                       \
                                                            \
        if (stack_size >= ARRAY_SIZE(stack)) {              \
            ERR("ran out of stack");                        \
            return;                                         \
        }                                                   \
    }                                                       \

    static uint16_t searching[FLUID_WIDTH][FLUID_HEIGHT];
    static xy stack[FLUID_WIDTH * FLUID_HEIGHT];
    uint32_t stack_size = 0;

    STACK_PUSH(x, y)

    while (stack_size > 0) {
        /*
         * Pop the stack.
         */
        stack_size--;
        uint16_t x = stack[stack_size].x;
        uint16_t y = stack[stack_size].y;

        fluid_pool[x][y] = pool_num;

        if (x > 1) {
            uint16_t dx = x - 1;
            uint16_t dy = y;
            STACK_PUSH(dx, dy)
        }

        if (x < FLUID_WIDTH - 2) {
            uint16_t dx = x + 1;
            uint16_t dy = y;
            STACK_PUSH(dx, dy)
        }

        if (y > 1) {
            uint16_t dx = x;
            uint16_t dy = y - 1;
            STACK_PUSH(dx, dy)
        }

        if (y < FLUID_HEIGHT - 2) {
            uint16_t dx = x;
            uint16_t dy = y + 1;
            STACK_PUSH(dx, dy)
        }
    }
}

/*
 * Identify all adjoining pools
 */
static void fluid_find_pools (void)
{
    memset(fluid_pool, 0, sizeof(fluid_pool));

    uint16_t x, y;

    max_fluid_pools = 0;

    for (y = 1; y < FLUID_HEIGHT - 1; y++) {
        if (!fluid_pool_row[y]) {
            continue;
        }

        for (x = 1; x < FLUID_WIDTH - 1; x++) {

            fluid_t *f = &world->fluid[x][y];
            if (!f->mass) {
                continue;
            }

            if (fluid_pool[x][y]) {
                if (!f->mass) {
                    DIE("pool set but no mass");
                }
                continue;
            }

            if (!world->fluid[x][y+1].mass) {
                continue;
            }

            max_fluid_pools++;
            if (max_fluid_pools >= MAX_POOLS) {
                ERR("ran out of fluid pools");
                return;
            }

            fluid_flood_fill(x, y, max_fluid_pools);
        }
    }
}

/*
 * If there is a surface tile above others, then try and push the mass to the
 * lower surface tiles.
 */
static void fluid_push_down (void)
{
    uint16_t pool_num;

    for (pool_num = 1; pool_num <= max_fluid_pools; pool_num++) {

        uint16_t surface_size = fluid_pool_surface_size[pool_num];
        if (surface_size < 2) {
            continue;
        }

        int mass_at_depth[FLUID_HEIGHT];
        int mass_at_depth_cnt[FLUID_HEIGHT];

        memset(mass_at_depth, 0, sizeof(mass_at_depth));
        memset(mass_at_depth_cnt, 0, sizeof(mass_at_depth_cnt));

        uint16_t depth;
        uint16_t s;

        /*
         * Find the total mass at each line of depth for this pool.
         */
        for (s = 0; s < surface_size; s++) {
            uint16_t x = fluid_pool_surface[pool_num][s].x;
            uint16_t y = fluid_pool_surface[pool_num][s].y;

            mass_at_depth[y] += world->fluid[x][y].mass;
            mass_at_depth_cnt[y]++;
        }

#define MASS_TRANSFER(src, nbr)                                     \
            if ((nbr->type == src->type) ||                         \
                (nbr->type == FLUID_IS_AIR)) {                      \
                                                                    \
                int16_t space_left =                                \
                    FLUID_MAX_MASS - (int)nbr->mass;                \
                                                                    \
                if (space_left > 0) {                               \
                    int16_t move_mass =                             \
                      std::min((int)remaining_mass, (int)space_left); \
                    remaining_mass -= move_mass;                    \
                    src->mass = remaining_mass;                     \
                                                                    \
                    nbr->mass += move_mass;                         \
                    nbr->type = src->type;                          \
                }                                                   \
            }                                                       \

        /*
         * Now try and move mass from upper depths to lower ones.
         */
        for (depth = 0; depth < FLUID_HEIGHT; depth++) {
            if (!mass_at_depth_cnt[depth]) {
                continue;
            }

            for (s = 0; s < surface_size; s++) {
                uint16_t fx = fluid_pool_surface[pool_num][s].x;
                uint16_t fy = fluid_pool_surface[pool_num][s].y;

                if (fy != depth) {
                    continue;
                }

                fluid_t *f = &world->fluid[fx][fy];
                fluid_mass_t remaining_mass = f->mass;

                {
                    uint16_t depth2;
                    for (depth2 = FLUID_HEIGHT - 1; depth2 > depth; depth2--) {
                        if (!mass_at_depth_cnt[depth2]) {
                            continue;
                        }

                        uint16_t si;
                        for (si = 0; si < surface_size; si++) {
                            uint16_t x = fluid_pool_surface[pool_num][si].x;
                            uint16_t y = fluid_pool_surface[pool_num][si].y;

                            if (y != depth2) {
                                continue;
                            }

                            fluid_t *nbr = &world->fluid[x][y];

                            MASS_TRANSFER(f, nbr);

                            if (!remaining_mass) {
                                break;
                            }

                            nbr = &world->fluid[x][y - 1];

                            MASS_TRANSFER(f, nbr);

                            if (nbr->mass) {
                                nbr->is_surface = 1;
                                f->is_surface = 0;
                            }

                            if (!remaining_mass) {
                                break;
                            }
                        }

                        if (!remaining_mass) {
                            break;
                        }
                    }
                }

                f->mass = remaining_mass;
            }
        }
    }
}

/*
 * How deep is each tile so we can color is accordingly.
 */
static void fluid_set_depth (void)
{
    uint16_t fx, fy;
    uint8_t depth;

    memset(world->is_water, 0, sizeof(world->is_water));

    memset(fluid_pool_row, 0, sizeof(fluid_pool_row));
    memset(fluid_pool_surface_size, 0, sizeof(fluid_pool_surface_size));

    for (fx = 1; fx < FLUID_WIDTH - 1; fx++) {
        depth = 0;

        for (fy = 1; fy < FLUID_HEIGHT - 1; fy++) {
            fluid_t *f = &world->fluid[fx][fy];
            f->is_surface = 0;

            if (!f->mass) {
                depth = 0;
                continue;
            }

            world->is_water(fx / FLUID_RESOLUTION, fy / FLUID_RESOLUTION) = true;

            fluid_pool_row[fy] = 1;

            fluid_t *g = &world->fluid[fx][fy + 1];
            if (!g->mass) {
                depth = 0;
                continue;
            }

            /*
             * If this is the surface, take note of it as we will need this to
             * even out surface fluids later.
             */
            if (depth == 0) {
                uint16_t pool_num = fluid_pool[fx][fy];
                uint16_t surface_size = fluid_pool_surface_size[pool_num];

                if (surface_size < MAX_POOL_SURFACE) {
                    fluid_pool_surface[pool_num][surface_size].x = fx;
                    fluid_pool_surface[pool_num][surface_size].y = fy;
                    fluid_pool_surface_size[pool_num]++;
                    f->is_surface = 1;
                } else {
                    DIE("too much surface area in pool");
                }
            }

            depth++;
        }
    }
}

void fluid_add_droplets (void)
{
    uint16_t x = (myrand() % (CHUNK_WIDTH - 4)) + 1;
    uint16_t y = (myrand() % (CHUNK_HEIGHT - 4)) + 1;

    if (x >= CHUNK_WIDTH) {
        DIE("overflow on x when adding droplets");
    }

    if (y >= CHUNK_HEIGHT) {
        DIE("overflow on y");
    }

    if (y == 0) {
        DIE("underflow on y");
    }

    if (!world->is_solid(x, y) &&
         world->is_solid(x, y - 1)) {

        uint16_t r;

        for (r = 0; r < 1; r++) {
            uint16_t fx;
            uint16_t fy;

            fx = x * FLUID_RESOLUTION;
            fy = y * FLUID_RESOLUTION;
            fx += myrand() % FLUID_RESOLUTION;
            fy += myrand() % FLUID_RESOLUTION;

            if (fx >= FLUID_WIDTH) {
                DIE("overflow fx fluid");
            }

            if (fy >= FLUID_HEIGHT) {
                DIE("overflow fx fluid");
            }

            world->fluid[fx][fy].mass = 10;
            world->fluid[fx][fy].type = FLUID_IS_WATER;
        }
    }
}

void fluid_remove_water_radius (int x, int y, int radius)
{
    int ix = x * FLUID_RESOLUTION;
    int iy = y * FLUID_RESOLUTION;
    radius *= FLUID_RESOLUTION;

    for (x = 0; x < FLUID_RESOLUTION * CHUNK_WIDTH; x++) {
        for (y = 0; y < FLUID_RESOLUTION * CHUNK_WIDTH; y++) {
            if (DISTANCE(ix, iy, x, y) < radius) {
                world->fluid[x][y].mass = 0;
                world->fluid[x][y].type = 0;
            }
        }
    }
}

static void fluid_mass_transfer (void)
{
    uint16_t fx, fy;
    int r = myrand() % 100;

    memset(fluid_pool_row, 0, sizeof(fluid_pool_row));

    for (fy = FLUID_HEIGHT-2; fy > 0; fy--) {
        for (fx = 1; fx < FLUID_WIDTH-2; fx++) {

            fluid_t *f = &world->fluid[fx][fy];

            fluid_mass_t avg_mass;
            fluid_mass_t remaining_mass = f->mass;
            if (!remaining_mass) {
                continue;
            }

            fluid_pool_row[fy] = 1;

            fluid_t *d = &world->fluid[fx][fy+1];

#undef MASS_TRANSFER
#define MASS_TRANSFER(src, nbr)                                     \
            if ((nbr->type == src->type) ||                         \
                (nbr->type == FLUID_IS_AIR)) {                      \
                                                                    \
                int16_t space_left =                                \
                    FLUID_MAX_MASS - (int)nbr->mass;                \
                if (space_left > 0) {                               \
                    int16_t move_mass =                             \
                      std::min((int)remaining_mass, (int)space_left); \
                    remaining_mass -= move_mass;                    \
                    src->mass = remaining_mass;                     \
                                                                    \
                    nbr->mass += move_mass;                         \
                    nbr->type = src->type;                          \
                }                                                   \
                                                                    \
                if (!remaining_mass) {                              \
                    continue;                                       \
                }                                                   \
            }                                                       \

#undef MASS_TRANSFER_LR
#define MASS_TRANSFER_LR(src, nbr)                                  \
            if ((nbr->type == src->type) ||                         \
                (nbr->type == FLUID_IS_AIR)) {                      \
                                                                    \
                avg_mass = (nbr->mass + remaining_mass) / 2;        \
                remaining_mass = avg_mass;                          \
                src->mass = remaining_mass;                         \
                                                                    \
                nbr->mass = avg_mass;                               \
                nbr->type = src->type;                              \
                                                                    \
                if (!remaining_mass) {                              \
                    continue;                                       \
                }                                                   \
            }                                                       \

            MASS_TRANSFER(f, d);

            /*
             * Side viscoscity.
             */
            if (r < 25) {
                continue;
            }

            fluid_t *b = &world->fluid[fx-1][fy];
            fluid_t *c = &world->fluid[fx+1][fy];

            MASS_TRANSFER_LR(f, c);
            MASS_TRANSFER_LR(f, b);
        }
    }
}

void fluid_tick (void)
{
    fluid_mass_transfer();

    fluid_find_pools();

    static uint32_t ts;
    if (time_have_x_tenths_passed_since(1, ts)) {
        ts = time_get_time_ms();

        fluid_push_down();
    }

    fluid_set_depth();
    fluid_add_droplets();
    fluid_add_droplets();
    fluid_add_droplets();
    fluid_add_droplets();
    fluid_add_droplets();
    fluid_add_droplets();
    fluid_add_droplets();
    fluid_add_droplets();
    fluid_add_droplets();
    fluid_add_droplets();
    fluid_add_droplets();
    fluid_add_droplets();
}

#if 0
static int get_map_tl_br (double *tl_x, double *tl_y, double *br_x, double *br_y)
{
    widgridnode *node;
    tree_root **tree;

    {
        int x = 0;
        int y = 0;
        int z = MAP_DEPTH_WALL;
        int got = false;

        tree = w->grid->grid_of_trees[z] + (y * w->grid->width) + x;

        TREE_WALK_REVERSE_UNSAFE_INLINE(*tree, node, tree_prev_tree_wid_compare_func_fast) {
            widp w = node->wid;

            double otlx;
            double otly;
            double obrx;
            double obry;

            wid_get_tl_x_tl_y_br_x_br_y(w, &otlx, &otly, &obrx, &obry);

            widp p = w->parent;
            otlx += p->offset.x;
            otly += p->offset.y;
            obrx += p->offset.x;
            obry += p->offset.y;

            *tl_x = otlx;
            *tl_y = otly;

            got = true;
            break;
        }

        if (!got) {
            return (false);
        }
    }

    {
        int x = CHUNK_WIDTH - 1;
        int y = CHUNK_HEIGHT - 1;
        int z = MAP_DEPTH_WALL;
        int got = false;

        tree = w->grid->grid_of_trees[z] + (y * w->grid->width) + x;

        TREE_WALK_REVERSE_UNSAFE_INLINE(*tree, node, tree_prev_tree_wid_compare_func_fast) {
            widp w = node->wid;

            double otlx;
            double otly;
            double obrx;
            double obry;

            wid_get_tl_x_tl_y_br_x_br_y(w, &otlx, &otly, &obrx, &obry);

            widp p = w->parent;
            otlx += p->offset.x;
            otly += p->offset.y;
            obrx += p->offset.x;
            obry += p->offset.y;

            *br_x = obrx;
            *br_y = obry;

            got = true;
            break;
        }

        if (!got) {
            return (false);
        }
    }

    return (true);
}
#endif

#if 0
void fluid_render (widp w, int minx, int miny, int maxx, int maxy)
{
    if (player) {
        const uint32_t visible_width =
                TILES_SCREEN_WIDTH / 2 + TILES_SCREEN_FLUID_WIDTH_PAD;
        const uint32_t visible_height =
                TILES_SCREEN_HEIGHT / 2 + TILES_SCREEN_FLUID_HEIGHT_PAD;

        maxx = player->x + visible_width;
        minx = player->x - visible_width;
        maxy = player->y + visible_height;
        miny = player->y - visible_height;

        while (maxx > CHUNK_WIDTH) {
            maxx--;
            minx--;
        }
        while (maxy > CHUNK_HEIGHT) {
            maxy--;
            miny--;
        }
        while (minx < 0) {
            maxx++;
            minx++;
        }
        while (miny < 0) {
            maxy++;
            miny++;
        }
    } else {
        minx = 0;
        maxx = CHUNK_WIDTH;
        miny = 0;
        maxy = CHUNK_HEIGHT;
    }

    double tl_x;
    double tl_y;
    double br_x;
    double br_y;

    if (!get_map_tl_br(w, &tl_x, &tl_y, &br_x, &br_y)) {
        return;
    }

    uint16_t fx;
    uint16_t fy;

    fpoint tile_tl;
    fpoint tile_br;

    /*
     * Preload all the animation tiles for fluids.
     */
    static tilep water_tiles[MAX_FLUID_TILES];
    static int done = 0;

    if (!done) {
        done = 1;

        tree_rootp tiles = tp_tiles(tp_find("water1"));
        if (!tiles) {
            return;
        }

        int i;
        for (i = 0; i < MAX_FLUID_TILES; i++) {
            thing_tilep tile = (typeof(tile)) tree_root_get_nth(tiles, i);

            water_tiles[i] = tile_find(thing_tile_name(tile));
        }
    }

    /*
     * Move the animation on slowly.
     */
    static int anim_count = 0;

    {
        static uint32_t ts;
        if (time_have_x_tenths_passed_since(1, ts)) {
            ts = time_get_time_ms();
            anim_count++;
        }

        if (anim_count >= 64) {
            anim_count = 0;
        }
    }

    /*
     * Move the wave animation on.
     */
    static double wave;

    {
        static double wave_delta = 0.5;
        static int wave_dir;
        static uint32_t ts;

        if (time_have_x_hundredths_passed_since(5, ts)) {
            ts = time_get_time_ms();
            if (wave_dir) {
                wave += wave_delta;
            } else {
                wave -= wave_delta;
            }

            /*
             * Change wave direction sometimes.
             */
            if ((myrand() % 1000) < 2) {
                wave_dir = !wave_dir;
            }
        }
    }

    double tile_pix_w = (br_x - tl_x) / (double)FLUID_WIDTH;
    double tile_pix_h = (br_y - tl_y) / (double)FLUID_HEIGHT;
    double dy = ((double)tile_pix_h) / (FLUID_MAX_MASS / 2);

    minx *= FLUID_RESOLUTION;
    miny *= FLUID_RESOLUTION;
    maxx *= FLUID_RESOLUTION;
    maxy *= FLUID_RESOLUTION;

    /*
     * Make the fluid darker and more opaque with dept.
     */
    color c = WHITE;
    color bg_color_tl = c;
    color bg_color_tr = c;
    color bg_color_bl = c;
    color bg_color_br = c;

    bg_color_tl.a = 100;
    bg_color_tr.a = 100;
    bg_color_bl.a = 100;
    bg_color_br.a = 100;

    for (fy = miny; fy < maxy - 1; fy++) {

        if (!fluid_pool_row[fy]) {
            continue;
        }

        tile_tl.y = tl_y + fy * tile_pix_h;
        tile_br.x = tile_tl.x + tile_pix_w;
        tile_br.y = tile_tl.y + tile_pix_h;

        for (fx = minx; fx < maxx - 1; fx++) {

            fluid_t *f = &world->fluid[fx][fy];
            if (!f->mass) {
                continue;
            }

            tile_tl.x = tl_x + fx * tile_pix_w;
            tile_tl.y = tl_y + fy * tile_pix_h;
            tile_br.x = tile_tl.x + tile_pix_w;
            tile_br.y = tile_tl.y + tile_pix_h;

            /*
             * Tiles on the sureface have a sinusoidal wave effect.
             */
            if (unlikely(f->is_surface)) {
                static double dx = RAD_360 / ((double) FLUID_WIDTH / 40.0);
                double mass = f->mass / 2.0;
                double height = mass + (fsin(dx * (double) (fx + wave)) * (mass * 0.2));

                if (height < 1) {
                    height = 1;
                }

                tile_tl.y = tile_br.y - dy * ((double)height);

                bg_color_tl.a = 255;
                bg_color_tr.a = 255;
            } else {
                bg_color_tl.a = 100;
                bg_color_tr.a = 100;
            }

            tilep t = water_tiles[(anim_count + fx + fy) % MAX_FLUID_TILES];

            /*
             * Spread the animation graphic over a number of fluid cells
             */
            static const int fluid_anim_scale = FLUID_RESOLUTION * FLUID_VISIBLE_SCALE;
            double x1 = t->x1;
            double x2 = t->x2;
            double y1 = t->y1;
            double y2 = t->y2;
            double dx = (x2 - x1) / fluid_anim_scale;
            double dy = (y2 - y1) / fluid_anim_scale;

            double x = fx % fluid_anim_scale;
            double y = fy % fluid_anim_scale;

            double tx1 = x1 + (x * dx);
            double ty1 = y1 + (y * dy);
            double tx2 = x1 + ((x + 1) * dx);
            double ty2 = y1 + ((y + 1) * dy);

            blit_colored(t->gl_surface_binding,
                         tx1,
                         ty2,
                         tx2,
                         ty1,
                         tile_tl.x,
                         tile_br.y,
                         tile_br.x,
                         tile_tl.y,
                         bg_color_tl,
                         bg_color_tr,
                         bg_color_bl,
                         bg_color_br);
        }
    }
}
#endif

int thing_submerged_depth (Thingp t)
{
    int x = t->mid_at.x * FLUID_RESOLUTION;
    int y = t->mid_at.y * FLUID_RESOLUTION;
    int dx = FLUID_RESOLUTION / 2;
    int dy = FLUID_RESOLUTION / 2;
    int water = 0;

    if (t->mid_at.x >= CHUNK_WIDTH) {
        return (false);
    }
    if (t->mid_at.y >= CHUNK_HEIGHT) {
        return (false);
    }
    if (t->mid_at.x < 0) {
        return (false);
    }
    if (t->mid_at.y < 0) {
        return (false);
    }

    while (y > 0) {
        if (world->fluid[x + dx][y + dy].mass > 0) {
            water++;
        }

        y--;
    }

    return (water);
}

int thing_is_submerged (Thingp t)
{
    int dx, dy;
    int x = t->mid_at.x * FLUID_RESOLUTION;
    int y = t->mid_at.y * FLUID_RESOLUTION;
    int water = 0;

    if (t->mid_at.x >= CHUNK_WIDTH) {
        return (false);
    }
    if (t->mid_at.y >= CHUNK_HEIGHT) {
        return (false);
    }
    if (t->mid_at.x < 0) {
        return (false);
    }
    if (t->mid_at.y < 0) {
        return (false);
    }

    for (dy = 0; dy < FLUID_RESOLUTION; dy++) {
        for (dx = 0; dx < FLUID_RESOLUTION; dx++) {
            if (world->fluid[x + dx][y + dy].mass > 0) {
                water++;
            }
        }
    }

    if (water >= FLUID_RESOLUTION * FLUID_RESOLUTION) {
        return (true);
    }

    return (false);
}

int thing_is_partially_or_fully_submerged (Thingp t)
{
    int dx, dy;
    int x = t->mid_at.x * FLUID_RESOLUTION;
    int y = t->mid_at.y * FLUID_RESOLUTION;
    int water = 0;

    if (t->mid_at.x >= CHUNK_WIDTH) {
        return (false);
    }
    if (t->mid_at.y >= CHUNK_HEIGHT) {
        return (false);
    }
    if (t->mid_at.x < 0) {
        return (false);
    }
    if (t->mid_at.y < 0) {
        return (false);
    }

    for (dy = 0; dy < FLUID_RESOLUTION; dy++) {
        for (dx = 0; dx < FLUID_RESOLUTION; dx++) {
            if (world->fluid[x + dx][y + dy].mass > 0) {
                water++;
            }
        }
    }

    if (water >= (FLUID_RESOLUTION * FLUID_RESOLUTION) / 2) {
        return (true);
    }

    return (false);
}
