/*
 * This game is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This game is distributed in the hope that it will be fun,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this game; if not, write to the Free
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * goblinhack@gmail.com
 */

#include <time.h>
#include <unistd.h>

#define MAZE_HOW_LONG_TO_SPEND_TRYING_TO_SOLVE_MAZE     100000
#define MAZE_MIN_DISTANCE_START_AND_END                 20
#define MAX_MAP_NUMBER_OF_TIMES_TO_TRY_AND_PLACE_FRAG   5

#undef MAZE_DEBUG_PRINT_EXITS
#undef MAZE_DEBUG_SHOW_AS_GENERATING
#undef MAZE_DEBUG_SHOW_AS_GENERATING_FRAGMENTS
#undef MAZE_DEBUG_SHOW_CONSOLE

#include "my_main.h"
#include "map_jigsaw.h"
#include "my_bits.h"
#include "my_color.h"
#include "my_dmap.h"
#include "my_thing.h"

/*
 * Creates a map somewhat like this
 *   
 *                                                                     
 *                 xxxxxxxxxxxxx             xxxxxxxxxxxxx             
 *                 xH..m......Hx             x...........x             
 *      ++++++++   xHxxxxxxxxxHx             x...........x   ++++++++  
 *      H,,,,,,H   xHxxxxxx.$xHx             xxxxx.......x   H,,,,,,H  
 *      H++++++H   xH....HxxxxHx             x...x.......x   H++++++H  
 *      H++++++H+++xxxxxxHx...Hx++++++++++++ x...xxxxxxxxx+++H++++++H  
 *      H,,,,,,H,,,......HxH.SH.,E,,,,H,,,,+ x............,,,H,,,,,,H  
 *      H++++++,+++xxxxxxxxHxxxx++++++H+++++ x...xxxxxxxxx+++,++++++H  
 *    ++H++++++,+  xxxxxxx.H...x      H      x....xxxxxxxx  +,++++++H++
 *    +,H,,,H,+++  xxxxx...H...x      H      xx....xxxxxxx  +++,H,,,H,+
 *    ++,+++H++    x.......H...x      H      x...........x    ++H+++,++
 *     +,+  H      x..m....H.m.x      H      x.....m....$x      H  +,+ 
 *     +++  H      xxxxxx.xxxxxx      H      xxxxxxxxxxxxx      H  +++ 
 *          H      xxxxxx.xxxxxx      H      x..xxxxxxxxxxxxxxxx.xxxxxx
 *     xxxxxHxxxxxxxxxxxx......x      H      x..m..H.....xx......xxxxxx
 *     xH...H.....xxxxxxxxx....x      H      xxxxxxHxxTTTxx....xxxxxxxx
 *     xH.xx.xxxx.xxxxxxx....xxx      H      xxxxx.H.xm.$xxxx....xxxxxx
 *     xH.........xxxxxxxx.....x xxxxxHxxx   xxx...H.xxxx.......xxxxxxx
 *     xH.xxxx.xx.xxx....xxx...x+xH..xH..x+++x.....H..........xxx....xx
 *     xH.........xx..m.........,,H...H..,,,,........m.............m..x
 *     xx..xHx...xxx.xxxxxxTTTTx+xHxxx...x+++xTTTTx.xxxxxxxTTTTxxxxxx.x
 *      x.xxHxx.xx x.xxxxxx...xx xH..x..xx   x....x.x....xxx...xxxxxx.x
 *      x.x H x.x  x.xxx$......x xHxxx...x   x....x.x....xx......$xxx.x
 *      xxx H xxx  x...xxxx....x xH...H..x   x....x.x....xx....xxxx...x
 *          H      x..m...xLLLLx xxxxxHxxx   xLLLLx.xWWWWxxLLLLx...m..x
 *          H      xxxxxx.xxxxxx      H      xxxxxx.xxxxxxxxxxxx.xxxxxx
 *          H            H       +++  H            H      ++++++H++++++
 *        ++H+++++  +++++H++     +,+  H            H      +,,,H,H,,,,,+
 *        +,H,,,,+  +,,,,H,+    ++,+++H++       +++H+++   +++,H+,++++++
 *       +++H+++,+  +,+++H+++   +,H,,,H,+++     H,,H,,H    H,,H+,++++  
 *       +,,H,,,H+  +H,,,H,,+   ++H++++++,+     H+++++H    H++++,,,,+  
 *     +++++,+++H++++H+++,+++++   H++++++,++++++H+++++H++++H +++,+++++ 
 *     +,,,,,,,,H,,,,H,,,,,,,,+   H,,,,,,H,,,,,,H,,+,,H,,,,H++,,,,,,,+ 
 *     +++,++++++++++++++++,+++   H++++++H+++++++++++++++++,++++++++++ 
 *       +++              +++     H++++++H                +,+          
 *                                H,,,,,,H                +++          
 *                                ++++++++                             
 *                                                                     
 */

#define tcup(x,y)           printf("\033[%d;%dH", y + 1, x + 1);

static int maze_seed;

/*
 * This is the buffer we print the jigsaw too.
 */
char map_jigsaw_buffer[MAP_WIDTH][MAP_HEIGHT];
static char map_jigsaw_buffer_old[MAP_WIDTH][MAP_HEIGHT];
static uint8_t map_jigsaw_buffer_fg[MAP_WIDTH][MAP_HEIGHT];
static uint8_t map_jigsaw_buffer_bg[MAP_WIDTH][MAP_HEIGHT];
static int map_jigsaw_buffer_water_depth[MAP_WIDTH][MAP_HEIGHT];
static int map_jigsaw_buffer_lava_depth[MAP_WIDTH][MAP_HEIGHT];
static int map_jigsaw_buffer_acid_depth[MAP_WIDTH][MAP_HEIGHT];
static int map_jigsaw_buffer_chasm_depth[MAP_WIDTH][MAP_HEIGHT];
static uint8_t map_jigsaw_buffer_action1[MAP_WIDTH][MAP_HEIGHT];
static uint8_t map_jigsaw_buffer_action2[MAP_WIDTH][MAP_HEIGHT];
static uint8_t map_jigsaw_buffer_action3[MAP_WIDTH][MAP_HEIGHT];
static const char *map_jigsaw_buffer_color[MAP_WIDTH][MAP_HEIGHT];
static uint8_t map_jigsaw_buffer_solved[MAP_WIDTH][MAP_HEIGHT];
static int32_t map_jigsaw_buffer_at_x;
static int32_t map_jigsaw_buffer_at_y;

/*
 * Global modes.
 */
static uint8_t jigpiece_horiz_flip;
static uint8_t jigpiece_vert_flip;
static uint8_t jigpiece_rotatable;

enum {
    TERM_COLOR_BLACK,
    TERM_COLOR_RED,
    TERM_COLOR_GREEN,
    TERM_COLOR_YELLOW,
    TERM_COLOR_BLUE,
    TERM_COLOR_PINK,
    TERM_COLOR_CYAN,
    TERM_COLOR_WHITE,
    TERM_COLOR_RESET,
    TERM_COLOR_MAX,
};

static uint8_t map_fg[MAP_MAX];
static uint8_t map_bg[MAP_MAX];
static uint8_t valid_frag_char[MAP_MAX];
static uint8_t valid_frag_alt_char[MAP_MAX];

enum {
    /*
     * Order is important so 3 - x == opposite dir
     */
    DIR_NORTH,
    DIR_EAST,
    DIR_WEST,
    DIR_SOUTH,
    DIR_MAX,
};

/*
 * A single jigpiece used to build the level.
 *
 * +---------+
 * |xxxxxxxxx|
 * |x.......x|
 * |x.......x|
 * |x.......x|
 * |D.......x|
 * |x.......x|
 * |x.......x|
 * |x.......x|
 * |xxxxxxxxx|
 * +---------+
 */
typedef struct {
    char c[JIGPIECE_WIDTH][JIGPIECE_HEIGHT];
    uint8_t minx;
    uint8_t maxx;
    uint8_t miny;
    uint8_t maxy;

    /*
     * A bitmap of exit directions.
     */
    int16_t exits[DIR_MAX];

    /*
     * What map types are in this piece?
     */
    int8_t has[MAP_MAX];

    uint8_t rotatable:1;
    uint8_t horiz_flip:1;
    uint8_t vert_flip:1;
    uint8_t empty:1;
    uint8_t set_min_max:1;
} jigpiece_t;

/*
 * A solvable maze, e.g.:
 * +---+---+---+---+---+---+---+---+---+---+---+---+
 * |   |                   |       |       |       |
 * +   +   +---+---+---+   +   +   +   +   +   +   +
 * | E |               |   |   |       |   |   |   |
 * +   +   +---+---+   +   +   +---+---+   +   +   +
 * | * |           |   |   |       |   |   |   |   |
 * +   +---+   +---+   +---+---+   +   +   +   +   +
 * | *   * |   |       |       |       |       |   |
 * +---+   +   +   +   +   +   +---+   +---+---+   +
 * |   | * |   |   |   |   |           |           |
 * +   +   +   +   +---+   +---+---+---+   +---+---+
 * | *   * |   |           |           |           |
 * +   +---+   +---+---+---+   +---+   +   +---+   +
 * | *   S |               |   |   |   |   |       |
 * +---+   +---+---+   +---+   +   +   +   +   +---+
 * |   |   |       |   |       |       |   |       |
 * +   +   +   +   +---+   +---+   +---+---+---+   +
 * |   |       |       |   |   |   |               |
 * +   +---+---+---+   +   +   +   +---+   +---+   +
 * |                       |               |       |
 * +---+---+---+---+---+---+---+---+---+---+---+---+
 */
typedef struct maze_cell_t_ {
    struct maze_cell_t_ *exit[4];
    int32_t possible_jigpieces[JIGPIECE_MAX];
    int32_t possible_jigpieces_size;
    int32_t jigpiece_index;
    jigpiece_t *jp;
    int32_t x;
    int32_t y;
    uint8_t exits:4;
    uint8_t walked:1;
    uint8_t dead:1;
    uint8_t start:1;
    uint8_t end:1;
    uint8_t solved:1;
    uint8_t best:1;
} maze_cell_t;

#define MAZE_CELL(c, x, y)          (c + (MAP_JIGSAW_PIECES_ACROSS * (y)) + (x))
#define MAZE_CAN_GO(c, dir)         (c->exit[dir] && !(c->exit[dir]->walked))
#define MAZE_HAS_EXIT(c, x, y, dir) (MAZE_CELL(c, (x), (y))->exits & (1<<(dir)))

#define MAZE_FRAG_DIRECTIONS 8

typedef struct {
    int32_t jigpieces_cnt;
    jigpiece_t jigpiece[JIGPIECE_MAX];

    /*
     * Fragments
     */
    int32_t frag_cnt;
    jigpiece_t frag[MAZE_FRAG_DIRECTIONS][JIGPIECE_MAX];
    int32_t frag_to_alt_base[JIGPIECE_MAX];
    int32_t frag_cnt_alts[JIGPIECE_MAX];
    int32_t frag_alt_cnt;
    jigpiece_t frag_alt[MAZE_FRAG_DIRECTIONS][JIGPIECE_MAX];

    /*
     * Triggers
     */
    int32_t trigger_fragment_cnt;
    jigpiece_t trigger_fragment[MAZE_FRAG_DIRECTIONS][JIGPIECE_MAX];
    int32_t trigger_fragment_to_alt_base[JIGPIECE_MAX];
    int32_t trigger_cnt_alts[JIGPIECE_MAX];
    int32_t action1_cnt_alts[JIGPIECE_MAX];
    int32_t action2_cnt_alts[JIGPIECE_MAX];
    int32_t action3_cnt_alts[JIGPIECE_MAX];
    int32_t trigger_cnt;
    int32_t action1_cnt;
    int32_t action2_cnt;
    int32_t action3_cnt;
    jigpiece_t trigger[MAZE_FRAG_DIRECTIONS][JIGPIECE_MAX];
    jigpiece_t action1[MAZE_FRAG_DIRECTIONS][JIGPIECE_MAX];
    jigpiece_t action2[MAZE_FRAG_DIRECTIONS][JIGPIECE_MAX];
    jigpiece_t action3[MAZE_FRAG_DIRECTIONS][JIGPIECE_MAX];
} frag_t;

typedef struct {
    uint32_t level;

    /*
     * Co-ords here are in terms of rooms, not characters.
     */
    uint32_t sx;
    uint32_t sy;
    uint32_t ex;
    uint32_t ey;

    /*
     * Keep this last as all things above get zeroed out as we build maze 
     * layers up successively.
     */
    maze_cell_t maze[MAP_JIGSAW_PIECES_ACROSS * MAP_JIGSAW_PIECES_DOWN];
} dungeon_t;

#ifdef MAZE_DEBUG_SHOW_AS_GENERATING
static void maze_debug(dungeon_t *dg);
#endif

static char *dieat (int32_t line, int32_t col, const char *why)
{
    DIE("Died at line %u, col %i: %s", line, col, why);
}

/*
 * map_jigsaw_buffer_goto
 */
static void map_jigsaw_buffer_goto (int32_t x, int32_t y)
{
    map_jigsaw_buffer_at_x = x;
    map_jigsaw_buffer_at_y = y;
}

/*
 * map_jigsaw_buffer_putchar
 */
static void map_jigsaw_buffer_putchar (int32_t m)
{
    if (map_jigsaw_buffer_at_x < 0) {
        return;
    }

    if (map_jigsaw_buffer_at_y < 0) {
        return;
    }

    if (map_jigsaw_buffer_at_x >= MAP_WIDTH) {
        return;
    }

    if (map_jigsaw_buffer_at_y >= MAP_HEIGHT) {
        return;
    }

    map_jigsaw_buffer_fg[map_jigsaw_buffer_at_x][map_jigsaw_buffer_at_y] = map_fg[m];
    map_jigsaw_buffer_bg[map_jigsaw_buffer_at_x][map_jigsaw_buffer_at_y] = map_bg[m];
    map_jigsaw_buffer[map_jigsaw_buffer_at_x++][map_jigsaw_buffer_at_y] = m;
}

/*
 * map_jigsaw_buffer_getchar
 */
uint8_t map_jigsaw_buffer_getchar (int32_t x, int32_t y)
{
    if (x < 0) {
        return (MAP_EMPTY);
    }

    if (y < 0) {
        return (MAP_EMPTY);
    }

    if (x >= MAP_WIDTH) {
        return (MAP_EMPTY);
    }

    if (y >= MAP_HEIGHT) {
        return (MAP_EMPTY);
    }

    return (map_jigsaw_buffer[x][y]);
}

/*
 * map_jigsaw_buffer_set_fgbg
 */
static void map_jigsaw_buffer_set_fgbg (uint8_t fg, uint8_t bg)
{
    static const char *data[] = {
            "[40;30m", "[40;31m", "[40;32m", "[40;33m",
            "[40;34m", "[40;35m", "[40;36m", "[40;37m",
            "[41;30m", "[41;31m", "[41;32m", "[41;33m",
            "[41;34m", "[41;35m", "[41;36m", "[41;37m",
            "[42;30m", "[42;31m", "[42;32m", "[42;33m",
            "[42;34m", "[42;35m", "[42;36m", "[42;37m",
            "[43;30m", "[43;31m", "[43;32m", "[43;33m",
            "[43;34m", "[43;35m", "[43;36m", "[43;37m",
            "[44;30m", "[44;31m", "[44;32m", "[44;33m",
            "[44;34m", "[44;35m", "[44;36m", "[44;37m",
            "[45;30m", "[45;31m", "[45;32m", "[45;33m",
            "[45;34m", "[45;35m", "[45;36m", "[45;37m",
            "[46;30m", "[46;31m", "[46;32m", "[46;33m",
            "[46;34m", "[46;35m", "[46;36m", "[46;37m",
            "[47;30m", "[47;31m", "[47;32m", "[47;33m",
            "[47;34m", "[47;35m", "[47;36m", "[47;37m",
    };

    printf("%s", data[(bg & 7) * 8 + (fg & 7)]);
}

/*
 * map_jigsaw_buffer_print
 */
void map_jigsaw_buffer_print(void);
void map_jigsaw_buffer_print (void)
{
    int32_t need_nl;
    int32_t x;
    int32_t y;
    int32_t fg;
    int32_t bg;

    need_nl = 0;

    tcup(0,0);

    for (y = 0; y < MAP_HEIGHT; y++) {
        for (x = 0; x < MAP_WIDTH; x++) {
            char c;

            c = map_jigsaw_buffer[x][y];
            fg = map_jigsaw_buffer_fg[x][y];
            bg = map_jigsaw_buffer_bg[x][y];

            if (!c) {
                fg = TERM_COLOR_WHITE;
                bg = TERM_COLOR_BLACK;
                c = ' ';
            }

            if ((c == MAP_FLOOR) | (c == MAP_CORRIDOR)) {
                if (map_jigsaw_buffer_solved[x][y]) {
                    c = '*';
                }
            }

            if (x == 0) {
                if (need_nl) {
                    putchar('\n');
                }
                need_nl = 1;
            }

            map_jigsaw_buffer_set_fgbg(fg, bg);
            putchar(c);
        }
    }
}

/*
 * map_jigsaw_buffer_print_file
 */
static void map_jigsaw_buffer_print_file (FILE *fpin, int final)
{
    char tmp[MAXSTR];
    int32_t need_nl;
    int32_t x;
    int32_t y;
    FILE *fp;

    snprintf(tmp, sizeof(tmp) - 1, "maps.small.%u", maze_seed);

    if (!fpin) {
        fp = fopen(tmp, "w");
        if (!fp) {
            MSG_BOX("can't write map file %s", tmp);
            return;
        }
    } else {
        fp = fpin;
    }

    need_nl = 0;

    for (y = 0; y < MAP_HEIGHT; y++) {
        for (x = 0; x < MAP_WIDTH; x++) {
            char c;

            c = map_jigsaw_buffer[x][y];

            if (!c) {
                c = ' ';
            }

            if (x == 0) {
                if (need_nl) {
                    fputc('\n', fp);
                }
                need_nl = 1;
            }

            fputc(c, fp);
        }
    }

    fputc('\n', fp);

    if (!fpin) {
        fclose(fp);
    }
}

/*
 * Read jigpiece data from a buffer.
 */
void jigpieces_read (frag_t *fragmap, char *buf)
{
    char *c = buf;
    int32_t cnt_cells_per_line;
    int32_t x;
    int32_t n;
    int32_t y;
    int32_t col;
    int32_t line;
    char command[80];
    char *s;
    int32_t reading_jigpieces;
    int32_t reading_frag;
    int32_t reading_frag_alt;
    int32_t reading_trigger_fragment;
    int32_t reading_trigger;
    int32_t reading_action1;
    int32_t reading_action2;
    int32_t reading_action3;

    reading_jigpieces = 0;
    reading_frag = 0;
    reading_frag_alt = 0;
    reading_trigger_fragment = 0;
    reading_trigger = 0;
    reading_action1 = 0;
    reading_action2 = 0;
    reading_action3 = 0;

    col = 1;
    line = 1;

    while (*c) {
        /*
         * Skip comments
         */
        if (*c == '#') {
            while (*c != '\n') {
                c++;
            }
            c++;
            col = 0;
            line++;
            continue;
        }

        /*
         * : begins commands.
         */
        if (*c == ':') {
            c++;
            s = command;

            memset(command, 0, sizeof(command));

            while ((*c != '\n') && (s < command + sizeof(command))) {
                *s++ = *c++;
            }

            if (!strcasecmp(command, "horiz-flip")) {
                jigpiece_horiz_flip =  true;
            } else if (!strcasecmp(command, "vert-flip")) {
                jigpiece_vert_flip = true;
            } else if (!strcasecmp(command, "rotatable")) {
                jigpiece_rotatable =  true;
            } else if (!strcasecmp(command, "reset")) {
                jigpiece_horiz_flip = false;
                jigpiece_vert_flip = false;
                jigpiece_rotatable = false;
            } else {
                reading_jigpieces = 0;
                reading_frag = 0;
                reading_frag_alt = 0;
                reading_trigger_fragment = 0;
                reading_trigger = 0;
                reading_action1 = 0;
                reading_action2 = 0;
                reading_action3 = 0;

                if (!strcasecmp(command, "jigpieces")) {
                    reading_jigpieces = 1;
                } else if (!strcasecmp(command, "fragment")) {
                    reading_frag = 1;
                } else if (!strcasecmp(command, "alternative")) {
                    reading_frag_alt = 1;
                } else if (!strcasecmp(command, "trigger-fragment")) {
                    reading_trigger_fragment = 1;
                } else if (!strcasecmp(command, "trigger")) {
                    reading_trigger = 1;
                } else if (!strcasecmp(command, "action1")) {
                    reading_action1 = 1;
                } else if (!strcasecmp(command, "action2")) {
                    reading_action2 = 1;
                } else if (!strcasecmp(command, "action3")) {
                    reading_action3 = 1;
                } else {
                    dieat(line, col, "unknown command");
                }
            }

            c++;
            col = 0;
            line++;
            continue;
        }

        /*
         * Read jigpiece header
         *
         * +--------+--------+...
         */
        if (*c != '+') {
            dieat(line, col, "expecting start of line");
        }

        if (!reading_jigpieces &&
            !reading_frag &&
            !reading_trigger_fragment &&
            !reading_trigger &&
            !reading_action1 &&
            !reading_action2 &&
            !reading_action3 &&
            !reading_frag_alt) {
            dieat(line, col,
                  "data found when no reading jigpieces or frag");
        }

        c++;
        col++;

        /*
         * Count the number of jigpiece across per line.
         */
        cnt_cells_per_line = 0;

        while (*c != '\n') {
            if (*c == '+') {
                cnt_cells_per_line++;
            }
            c++;
            col++;
        }

        if (*c != '\n') {
            dieat(line, col, "expecing end of line");
        }

        /*
         * Move onto the next line.
         */
        c++;
        col = 0;
        line++;

        if (*c == EOF) {
            return;
        }

        if (fragmap->jigpieces_cnt + cnt_cells_per_line >= JIGPIECE_MAX) {
            dieat(line, col, "too many jigpieces");
        }

        if (!*c) {
            return;
        }

        /*
         * Read one line of data
         * |........|........|...
         */
        col = 0;
        y = 0;

        for (y = 0; y < JIGPIECE_HEIGHT; y++) {
            for (n = 0; n < cnt_cells_per_line; n++) {

                if (*c != '|') {
                    ERR("Found char 0x%x '%c' when expecting | char", *c, *c);
                    dieat(line, col, "expecting start of jigpiece "
                          "data, found char");
                }

                c++;
                col++;

                for (x = 0; x < JIGPIECE_WIDTH; x++) {

                    if (*c == '\n') {
                        dieat(line, col, "premature end of jigpiece data");
                    }

                    if (reading_jigpieces) {
                        fragmap->jigpiece[fragmap->jigpieces_cnt + n].c[x][y] = *c;
                        fragmap->jigpiece[fragmap->jigpieces_cnt + n].rotatable = 
                                        jigpiece_rotatable;
                        fragmap->jigpiece[fragmap->jigpieces_cnt + n].horiz_flip = 
                                        jigpiece_horiz_flip;
                        fragmap->jigpiece[fragmap->jigpieces_cnt + n].vert_flip = 
                                        jigpiece_vert_flip;

                    } else if (reading_frag) {
                        fragmap->frag[0][fragmap->frag_cnt + n].c[x][y] = *c;
                        fragmap->frag[0][fragmap->frag_cnt + n].rotatable = 
                                        jigpiece_rotatable;
                        fragmap->frag[0][fragmap->frag_cnt + n].horiz_flip = 
                                        jigpiece_horiz_flip;
                        fragmap->frag[0][fragmap->frag_cnt + n].vert_flip = 
                                        jigpiece_vert_flip;

                    } else if (reading_frag_alt) {
                        fragmap->frag_alt[0][fragmap->frag_alt_cnt + n].c[x][y] = *c;
                        fragmap->frag_alt[0][fragmap->frag_alt_cnt + n].rotatable = 
                                        jigpiece_rotatable;
                        fragmap->frag_alt[0][fragmap->frag_alt_cnt + n].horiz_flip = 
                                        jigpiece_horiz_flip;
                        fragmap->frag_alt[0][fragmap->frag_alt_cnt + n].vert_flip = 
                                        jigpiece_vert_flip;

                    } else if (reading_trigger_fragment) {
                        fragmap->trigger_fragment[0][fragmap->trigger_fragment_cnt + n].c[x][y] = *c;
                        fragmap->trigger_fragment[0][fragmap->trigger_fragment_cnt + n].rotatable = 
                                        jigpiece_rotatable;
                        fragmap->trigger_fragment[0][fragmap->trigger_fragment_cnt + n].horiz_flip = 
                                        jigpiece_horiz_flip;
                        fragmap->trigger_fragment[0][fragmap->trigger_fragment_cnt + n].vert_flip = 
                                        jigpiece_vert_flip;

                    } else if (reading_trigger) {
                        fragmap->trigger[0][fragmap->trigger_cnt + n].c[x][y] = *c;
                        fragmap->trigger[0][fragmap->trigger_cnt + n].rotatable = 
                                        jigpiece_rotatable;
                        fragmap->trigger[0][fragmap->trigger_cnt + n].horiz_flip = 
                                        jigpiece_horiz_flip;
                        fragmap->trigger[0][fragmap->trigger_cnt + n].vert_flip = 
                                        jigpiece_vert_flip;

                    } else if (reading_action1) {
                        fragmap->action1[0][fragmap->action1_cnt + n].c[x][y] = *c;
                        fragmap->action1[0][fragmap->action1_cnt + n].rotatable = 
                                        jigpiece_rotatable;
                        fragmap->action1[0][fragmap->action1_cnt + n].horiz_flip = 
                                        jigpiece_horiz_flip;
                        fragmap->action1[0][fragmap->action1_cnt + n].vert_flip = 
                                        jigpiece_vert_flip;

                    } else if (reading_action2) {
                        fragmap->action2[0][fragmap->action2_cnt + n].c[x][y] = *c;
                        fragmap->action2[0][fragmap->action2_cnt + n].rotatable = 
                                        jigpiece_rotatable;
                        fragmap->action2[0][fragmap->action2_cnt + n].horiz_flip = 
                                        jigpiece_horiz_flip;
                        fragmap->action2[0][fragmap->action2_cnt + n].vert_flip = 
                                        jigpiece_vert_flip;

                    } else if (reading_action3) {
                        fragmap->action3[0][fragmap->action3_cnt + n].c[x][y] = *c;
                        fragmap->action3[0][fragmap->action3_cnt + n].rotatable = 
                                        jigpiece_rotatable;
                        fragmap->action3[0][fragmap->action3_cnt + n].horiz_flip = 
                                        jigpiece_horiz_flip;
                        fragmap->action3[0][fragmap->action3_cnt + n].vert_flip = 
                                        jigpiece_vert_flip;

                    } else {
                        ERR("bug");
                    }

                    c++;
                    col++;
                }
            }

            /*
             * Should be at the end of the line
             */
            if (*c != '|') {
                dieat(line, col, "premature end of file");
            }

            c++;
            col++;

            if (*c != '\n') {
                dieat(line, col, "expecting end of line");
            }

            /*
             * Move onto the next line.
             */
            c++;
            col = 0;
            line++;
        }

        if (reading_jigpieces) {
            fragmap->jigpieces_cnt += cnt_cells_per_line;
        } else if (reading_frag) {

            if (!fragmap->frag_to_alt_base[fragmap->frag_cnt]) {
                fragmap->frag_to_alt_base[fragmap->frag_cnt] = fragmap->frag_alt_cnt;
            }

            fragmap->frag_cnt += cnt_cells_per_line;
        } else if (reading_frag_alt) {
            fragmap->frag_alt_cnt += cnt_cells_per_line;

            fragmap->frag_cnt_alts[fragmap->frag_cnt-1] += cnt_cells_per_line;
        } else if (reading_trigger_fragment) {

            if (!fragmap->trigger_fragment_to_alt_base[fragmap->trigger_fragment_cnt]) {
                fragmap->trigger_fragment_to_alt_base[fragmap->trigger_fragment_cnt] = fragmap->trigger_cnt;
            }

            fragmap->trigger_fragment_cnt += cnt_cells_per_line;
        } else if (reading_trigger) {
            fragmap->trigger_cnt += cnt_cells_per_line;

            fragmap->trigger_cnt_alts[fragmap->trigger_fragment_cnt-1] += cnt_cells_per_line;
        } else if (reading_action1) {
            fragmap->action1_cnt += cnt_cells_per_line;

            fragmap->action1_cnt_alts[fragmap->trigger_fragment_cnt-1] += cnt_cells_per_line;
        } else if (reading_action2) {
            fragmap->action2_cnt += cnt_cells_per_line;

            fragmap->action2_cnt_alts[fragmap->trigger_fragment_cnt-1] += cnt_cells_per_line;
        } else if (reading_action3) {
            fragmap->action3_cnt += cnt_cells_per_line;

            fragmap->action3_cnt_alts[fragmap->trigger_fragment_cnt-1] += cnt_cells_per_line;
        }
    }
}

/*
 * jigpiece_char_is_occupiable
 */
static int32_t jigpiece_char_is_occupiable (char c)
{
    return (c == MAP_FLOOR)             ||
           (c == MAP_CORRIDOR)          ||
           (c == MAP_MONST)             ||
           (c == MAP_MONST_OR_MOB)      ||
           (c == MAP_GENERATOR)         ||
           (c == MAP_BRAZIER)           ||
           (c == MAP_TRIGGER_HERO)      ||
           (c == MAP_TRIGGER_MONST)     ||
           (c == MAP_TREASURE);
}

static int32_t jigpiece_char_is_passable (char c)
{
    return (c == MAP_FLOOR)             ||
           (c == MAP_CORRIDOR)          ||
           (c == MAP_MONST)             ||
           (c == MAP_START)             ||
           (c == MAP_END)               ||
           (c == MAP_MONST_OR_MOB)      ||
           (c == MAP_GENERATOR)         ||
           (c == MAP_DOOR)              ||
           (c == MAP_WEAPON)            ||
           (c == MAP_BRAZIER)           ||
           (c == MAP_POTION)            ||
           (c == MAP_TRIGGER_HERO)      ||
           (c == MAP_TRIGGER_MONST)     ||
           (c == MAP_TREASURE);
}

/*
 * jigpiece_char_is_monst
 */
static int32_t jigpiece_char_is_monst (char c)
{
    return ((c == MAP_MONST) ||
            (c == MAP_GENERATOR) ||
            (c == MAP_MONST_OR_MOB));
}

/*
 * jigpiece_char_is_dungeon_floor_or_corridor
 */
static int32_t jigpiece_char_is_dungeon_floor_or_corridor (char c)
{
    return (c == MAP_FLOOR) || (c == MAP_CORRIDOR);
}

/*
 * jigpiece_char_at
 */
static char jigpiece_char_at (frag_t *fragmap, int32_t which, int32_t x, int32_t y)
{
    if (x < 0) {
        return (MAP_PADDING);
    }

    if (y < 0) {
        return (MAP_PADDING);
    }

    if (x >= JIGPIECE_WIDTH) {
        return (MAP_PADDING);
    }

    if (y >= JIGPIECE_HEIGHT) {
        return (MAP_PADDING);
    }

    return (fragmap->jigpiece[which].c[x][y]);
}

/*
 * jigpiece_create_exits
 */
void jigpiece_create_exits (frag_t *fragmap)
{
    int32_t which;
    int32_t x;
    int32_t y;

    for (which = 0; which < fragmap->jigpieces_cnt; which++) {
        if (fragmap->jigpiece[which].empty) {
            continue;
        }

        /*
         * ?.......
         * ?.......
         * ?.......
         * ?.......
         * ?.......
         * ?.......
         * ?.......
         * ?.......
         */
        x = 0;
        for (y = 0; y < JIGPIECE_HEIGHT; y++) {
            if (jigpiece_char_is_occupiable(
                                        jigpiece_char_at(fragmap, which, x, y))) {
                fragmap->jigpiece[which].exits[DIR_WEST] |= 1<<y;
            }
        }

        /*
         * .......?
         * .......?
         * .......?
         * .......?
         * .......?
         * .......?
         * .......?
         * .......?
         */
        x = JIGPIECE_WIDTH-1;
        for (y = 0; y < JIGPIECE_HEIGHT; y++) {
            if (jigpiece_char_is_occupiable(
                                        jigpiece_char_at(fragmap, which, x, y))) {
                fragmap->jigpiece[which].exits[DIR_EAST] |= 1<<y;
            }
        }

        /*
         * ????????
         * ........
         * ........
         * ........
         * ........
         * ........
         * ........
         * ........
         */
        y = 0;
        for (x = 0; x < JIGPIECE_WIDTH; x++) {
            if (jigpiece_char_is_occupiable(
                                        jigpiece_char_at(fragmap, which, x, y))) {
                fragmap->jigpiece[which].exits[DIR_NORTH] |= 1<<x;
            }
        }

        /*
         * ........
         * ........
         * ........
         * ........
         * ........
         * ........
         * ........
         * ????????
         */
        y = JIGPIECE_HEIGHT-1;
        for (x = 0; x < JIGPIECE_WIDTH; x++) {
            if (jigpiece_char_is_occupiable(
                                        jigpiece_char_at(fragmap, which, x, y))) {
                fragmap->jigpiece[which].exits[DIR_SOUTH] |= 1<<x;
            }
        }
    }
}

/*
 * jigpiece_print
 */
void jigpiece_print(frag_t *fragmap, int32_t which);
void jigpiece_print (frag_t *fragmap, int32_t which)
{
    int32_t x;
    int32_t y;

    for (y = 0; y < JIGPIECE_HEIGHT; y++) {
        for (x = 0; x < JIGPIECE_WIDTH; x++) {

#ifdef MAZE_DEBUG_PRINT_EXITS
            if (which) {
                if (x == 0) {
                    if (fragmap->jigpiece[which].exits[DIR_WEST] & (1 << y)) {
                        putchar(MAP_EXIT_WEST);
                        continue;
                    }
                } else if (x == JIGPIECE_WIDTH-1) {
                    if (fragmap->jigpiece[which].exits[DIR_EAST] & (1 << y)) {
                        putchar(MAP_EXIT_EAST);
                        continue;
                    }
                }

                if (y == 0) {
                    if (fragmap->jigpiece[which].exits[DIR_NORTH] & (1 << x)) {
                        putchar(MAP_EXIT_NORTH);
                        continue;
                    }
                } else if (y == JIGPIECE_HEIGHT-1) {
                    if (fragmap->jigpiece[which].exits[DIR_SOUTH] & (1 << x)) {
                        putchar(MAP_EXIT_SOUTH);
                        continue;
                    }
                }
            }
#endif
            putchar(fragmap->jigpiece[which].c[x][y]);
        }
        putchar('\n');
    }
    putchar('\n');
}

/*
 * frag_print
 */
void frag_print(frag_t *fragmap, int32_t dir, int32_t which);
void frag_print (frag_t *fragmap, int32_t dir, int32_t which)
{
    int32_t x;
    int32_t y;

    for (y = 0; y < JIGPIECE_HEIGHT; y++) {
        for (x = 0; x < JIGPIECE_WIDTH; x++) {
            putchar(fragmap->frag[dir][which].c[x][y]);
        }
        putchar('\n');
    }
    putchar('\n');
}

/*
 * jigpiece_printat
 */
static void jigpiece_printat (frag_t *fragmap, 
                              int32_t atx, int32_t aty, int32_t which)
{
    int32_t x;
    int32_t y;

    for (y = 0; y < JIGPIECE_HEIGHT; y++) {
        map_jigsaw_buffer_goto(atx, aty + y);

        for (x = 0; x < JIGPIECE_WIDTH; x++) {

#ifdef MAZE_DEBUG_PRINT_EXITS
            if (which) {
                if (x == 0) {
                    if (fragmap->jigpiece[which].exits[DIR_WEST] & (1 << y)) {
                        map_jigsaw_buffer_putchar(MAP_EXIT_WEST);
                        continue;
                    }
                } else if (x == JIGPIECE_WIDTH-1) {
                    if (fragmap->jigpiece[which].exits[DIR_EAST] & (1 << y)) {
                        map_jigsaw_buffer_putchar(MAP_EXIT_EAST);
                        continue;
                    }
                }

                if (y == 0) {
                    if (fragmap->jigpiece[which].exits[DIR_NORTH] & (1 << x)) {
                        map_jigsaw_buffer_putchar(MAP_EXIT_NORTH);
                        continue;
                    }
                } else if (y == JIGPIECE_HEIGHT-1) {
                    if (fragmap->jigpiece[which].exits[DIR_SOUTH] & (1 << x)) {
                        map_jigsaw_buffer_putchar(MAP_EXIT_SOUTH);
                        continue;
                    }
                }
            }
#endif

            map_jigsaw_buffer_putchar(fragmap->jigpiece[which].c[x][y]);
        }
    }
}

/*
 * jigpiece_printat_with_border
 */
void jigpiece_printat_with_border(frag_t *fragmap, int32_t atx, int32_t aty, int32_t which);
void jigpiece_printat_with_border (frag_t *fragmap, int32_t atx, int32_t aty, int32_t which)
{
    int32_t x;
    int32_t y;

    map_jigsaw_buffer_goto(atx, aty);

    for (x = 0; x < JIGPIECE_WIDTH + 2; x++) {
        map_jigsaw_buffer_putchar(MAP_PADDING);
    }

    map_jigsaw_buffer_goto(atx, aty+1);

    for (y = 0; y < JIGPIECE_HEIGHT; y++) {
        map_jigsaw_buffer_goto(atx, aty + y + 1);
        map_jigsaw_buffer_putchar(MAP_PADDING);

        for (x = 0; x < JIGPIECE_WIDTH; x++) {

            if (which == 0) {
                map_jigsaw_buffer_putchar(MAP_PADDING);
                continue;
            }

#ifdef MAZE_DEBUG_PRINT_EXITS
            if (x == 0) {
                if (fragmap->jigpiece[which].exits[DIR_WEST] & (1 << y)) {
                    map_jigsaw_buffer_putchar(MAP_EXIT_WEST);
                    continue;
                }
            } else if (x == JIGPIECE_WIDTH-1) {
                if (fragmap->jigpiece[which].exits[DIR_EAST] & (1 << y)) {
                    map_jigsaw_buffer_putchar(MAP_EXIT_EAST);
                    continue;
                }
            }

            if (y == 0) {
                if (fragmap->jigpiece[which].exits[DIR_NORTH] & (1 << x)) {
                    map_jigsaw_buffer_putchar(MAP_EXIT_NORTH);
                    continue;
                }
            } else if (y == JIGPIECE_HEIGHT-1) {
                if (fragmap->jigpiece[which].exits[DIR_SOUTH] & (1 << x)) {
                    map_jigsaw_buffer_putchar(MAP_EXIT_SOUTH);
                    continue;
                }
            }
#endif
            map_jigsaw_buffer_putchar(fragmap->jigpiece[which].c[x][y]);
        }

        map_jigsaw_buffer_putchar(MAP_PADDING);
    }

    map_jigsaw_buffer_goto(atx, aty + y + 1);

    for (x = 0; x < JIGPIECE_WIDTH + 2; x++) {
        map_jigsaw_buffer_putchar(MAP_PADDING);
    }
}

/*
 * jigpiece_count_char_types
 *
 * How many of whatever type of map char are in each which
 */
static void jigpiece_count_char_types (frag_t *fragmap, int32_t which)
{
    int32_t x;
    int32_t y;

    if (fragmap->jigpiece[which].empty) {
        return;
    }

    for (y = 0; y < JIGPIECE_HEIGHT; y++) {

        for (x = 0; x < JIGPIECE_WIDTH; x++) {

            if (which == 0) {
                continue;
            }

            if (x == 0) {
                if (fragmap->jigpiece[which].exits[DIR_WEST] & (1 << y)) {
                    fragmap->jigpiece[which].has[MAP_EXIT_WEST]++;
                    continue;
                }
            } else if (x == JIGPIECE_WIDTH-1) {
                if (fragmap->jigpiece[which].exits[DIR_EAST] & (1 << y)) {
                    fragmap->jigpiece[which].has[MAP_EXIT_EAST]++;
                    continue;
                }
            }

            if (y == 0) {
                if (fragmap->jigpiece[which].exits[DIR_NORTH] & (1 << x)) {
                    fragmap->jigpiece[which].has[MAP_EXIT_NORTH]++;
                    continue;
                }
            } else if (y == JIGPIECE_HEIGHT-1) {
                if (fragmap->jigpiece[which].exits[DIR_SOUTH] & (1 << x)) {
                    fragmap->jigpiece[which].has[MAP_EXIT_SOUTH]++;
                    continue;
                }
            }

            fragmap->jigpiece[which].has[(int32_t)fragmap->jigpiece[which].c[x][y]]++;
        }
    }
}

/*
 * maze_print_cells
 */
static inline void maze_print_cells (dungeon_t *dg)
{
    int32_t w = MAP_JIGSAW_PIECES_ACROSS;
    int32_t h = MAP_JIGSAW_PIECES_DOWN;
    char which;
    int32_t y;
    int32_t x;

    printf("\n\n");

    for (x = 0; x < w; x++) {
        printf("+---");
    }

    printf("+\n");

    for (y = 0; y < h; y++) {
        for (x = 0; x < w; x++) {
            maze_cell_t *c = MAZE_CELL(dg->maze, x, y);

            which = ' ';

            if (c->dead) {
                which = 'D';
            } else if (c->start) {
                which = 'S';
            } else if (c->end) {
                which = 'E';
            } else if (c->best) {
                which = '*';
            } else if (c->solved) {
                which = ' ';
            }

            if ((x > 0) && MAZE_HAS_EXIT(dg->maze, x, y, DIR_WEST)) {
                printf("  %c ", which);
            } else {
                printf("| %c ", which);
            }
        }

        printf("|\n");

        for (x = 0; x < w; x++) {
            if ((y < h) && MAZE_HAS_EXIT(dg->maze, x, y, DIR_SOUTH)) {
                printf("+   ");
            } else {
                printf("+---");
            }
        }

        printf("+\n");
    }
}

#if 0
/*
 * jigpiece_check_frag
 *
 * Sanity check
 */
static void jigpiece_check_frag (frag_t *fragmap)
{
    int32_t f;
    int32_t x;
    int32_t y;

    /*
     * For each frag.
     */
    for (f = 0; f < fragmap->frag_cnt; f++) {
        for (y = 0; y < JIGPIECE_HEIGHT; y++) {
            for (x = 0; x < JIGPIECE_WIDTH; x++) {
                uint32_t fragchar = fragmap->frag[0][f].c[x][y];

                if (!valid_frag_char[fragchar]) {
                    for (y = 0; y < JIGPIECE_HEIGHT; y++) {
                        for (x = 0; x < JIGPIECE_WIDTH; x++) {
                            uint32_t fragchar = fragmap->frag[0][f].c[x][y];

                            printf("%c", fragchar);
                        }
                        printf("\n");
                    }
                    printf("\n");

                    ERR("invalid fragment char [0x%x/%c] above", fragchar, fragchar);
                }
            }
        }
    }
}
#endif

void jigpiece_get_bounds (jigpiece_t *j)
{
    if (j->set_min_max) {
        return;
    }

    j->set_min_max = 1;
    j->minx = 255;
    j->miny = 255;
    j->maxx = 0;
    j->maxy = 0;

    int x, y;
                    
    for (x = 0; x < JIGPIECE_WIDTH; x++) {
        for (y = 0; y < JIGPIECE_HEIGHT; y++) {
            if (j->c[x][y] != MAP_EMPTY) {
                if (x < j->minx) {
                    j->minx = x;
                }

                if (x > j->maxx) {
                    j->maxx = x;
                }

                if (y < j->miny) {
                    j->miny = y;
                }

                if (y > j->maxy) {
                    j->maxy = y;
                }
            }
        }
    }

    if (j->minx == 255) {
        j->minx = 0;
    }

    if (j->miny == 255) {
        j->miny = 0;
    }
}

#if 0
/*
 * jigpiece_add_frag
 *
 * Replace a fragment of the maze to make it more interesting.
 */
static void jigpiece_add_frag (dungeon_t *dg, frag_t *fragmap, uint32_t chance)
{
    int32_t i;
    int32_t c;
    int32_t x;
    int32_t y;
    int32_t ax;
    int32_t ay;
    int32_t cx;
    int32_t cy;
    int32_t tries;
    int32_t dir;
    int32_t frag;
    int32_t alt;
    int32_t map;

    int F;

    for (F = 0; F < fragmap->frag_cnt; F++) {

        int f = myrand() % fragmap->frag_cnt;

        if ((myrand() % 100) > chance) {
            continue;
        }

        /*
         * For each orientation of a frag.
         */
        for (dir = 0; dir < MAZE_FRAG_DIRECTIONS; dir++) {

            if (fragmap->frag[dir][f].empty) {
                continue;
            }

            /*
             * For each orientation of a frag.
             */
            for (c = 0; c < fragmap->frag_cnt_alts[f]; c++) {
#ifdef MAZE_DEBUG_SHOW_AS_GENERATING_FRAGMENTS
                maze_print_cells(dg);
                map_jigsaw_buffer_print();
#endif
                jigpiece_t *j = &fragmap->frag[dir][f];

                /*
                 * Try and place the frag.
                 */
                tries = 0;
                while (tries++ < MAX_MAP_NUMBER_OF_TIMES_TO_TRY_AND_PLACE_FRAG) {

                    ax = myrand() % (MAP_WIDTH + JIGPIECE_WIDTH);
                    ay = myrand() % (MAP_HEIGHT + JIGPIECE_HEIGHT);
                    ax -= JIGPIECE_WIDTH;
                    ay -= JIGPIECE_HEIGHT;

                    jigpiece_get_bounds(j);
                    for (x = j->minx; x <= j->maxx; x++) {
                        for (y = j->miny; y <= j->maxy ; y++) {
                            /*
                             * Skip empty spaces.
                             */
                            frag = j->c[x][y];
                            if (frag == MAP_EMPTY) {
                                continue;
                            }

                            cx = ax + x;
                            cy = ay + y;

                            /*
                             * It's ok to be off map but only if a space.
                             */
                            if ((cx < 0) || (cx >= MAP_WIDTH) ||
                                (cy < 0) || (cy >= MAP_HEIGHT)) {
                                goto next;
                            }

                            /*
                             * Check the frag is an exact match.
                             */
                            map = map_jigsaw_buffer_getchar(cx, cy);
                            if (map != frag) {
                                /*
                                 * Allow the frag to force that spaces
                                 * must exist.
                                 */
                                if (frag == MAP_SPACE) {
                                    if (map == MAP_EMPTY) {
                                        continue;
                                    }
                                }
                                goto next;
                            }
                        }
                    }

                    /*
                     * Choose something to replace the frag.
                     */
                    do {
                        i = myrand() % fragmap->frag_cnt_alts[f];
                        i += fragmap->frag_to_alt_base[f];

                    } while (fragmap->frag_alt[dir][i].empty);

                    /*
                     * Place the frag.
                     */
                    for (x = 0; x < JIGPIECE_WIDTH; x++) {
                        for (y = 0; y < JIGPIECE_HEIGHT; y++) {
                            alt = fragmap->frag_alt[dir][i].c[x][y];
                            frag = fragmap->frag[dir][f].c[x][y];

                            cx = ax + x;
                            cy = ay + y;

                            /*
                             * Skip off map.
                             */
                            if ((cx < 0) || (cx >= MAP_WIDTH) ||
                                (cy < 0) || (cy >= MAP_HEIGHT)) {
                                continue;
                            }

                            /*
                             * If the alternative has space and the frag
                             * does not, overwrite it.
                             */
                            if (alt == MAP_EMPTY) {
                                if (frag == MAP_EMPTY) {
                                    continue;
                                }
                            }

                            map_jigsaw_buffer_goto(cx, cy);
                            map_jigsaw_buffer_putchar(alt);
                        }
                    }

                    break;
next:
                    continue;
                }
            }
        }
    }
}

/*
 * jigpiece_add_triggers
 *
 * Replace a fragment of the maze to make it more interesting.
 */
static void jigpiece_add_triggers (dungeon_t *dg, frag_t *fragmap)
{
    int32_t f;
    int32_t i;
    int32_t c;
    int32_t x;
    int32_t y;
    int32_t ax;
    int32_t ay;
    int32_t cx;
    int32_t cy;
    int32_t tries;
    int32_t dir;
    int32_t frag;
    int32_t action1;
    int32_t action2;
    int32_t action3;
    int32_t alt;
    int32_t map;
    int32_t color_n = 0;
    const char *color;

    memset(map_jigsaw_buffer_action1, 0, sizeof(map_jigsaw_buffer_action1));
    memset(map_jigsaw_buffer_action2, 0, sizeof(map_jigsaw_buffer_action2));
    memset(map_jigsaw_buffer_action3, 0, sizeof(map_jigsaw_buffer_action3));
    memset(map_jigsaw_buffer_color, 0, sizeof(map_jigsaw_buffer_color));
    memset(map_jigsaw_buffer_solved, 0, sizeof(map_jigsaw_buffer_solved));

    /*
     * For each frag.
     */
    for (f = 0; f < fragmap->trigger_fragment_cnt; f++) {

        for (y = 0; y < JIGPIECE_HEIGHT; y++) {
            for (x = 0; x < JIGPIECE_WIDTH; x++) {
                uint32_t fragchar = fragmap->frag[0][f].c[x][y];

                if (!valid_frag_char[fragchar]) {
                    for (y = 0; y < JIGPIECE_HEIGHT; y++) {
                        for (x = 0; x < JIGPIECE_WIDTH; x++) {
                            uint32_t fragchar = fragmap->frag[0][f].c[x][y];

                            printf("%c", fragchar);
                        }
                        printf("\n");
                    }
                    printf("\n");

                    ERR("invalid fragment char [0x%x/%c] above", fragchar, fragchar);
                }
            }
        }
    }

    int F;

    for (F = 0; F < fragmap->trigger_fragment_cnt; F++) {

        int f = myrand() % fragmap->trigger_fragment_cnt;

        if ((myrand() % 100) > 5) {
            continue;
        }

        /*
         * For each orientation of a frag.
         */
        for (dir = 0; dir < MAZE_FRAG_DIRECTIONS; dir++) {

            if (fragmap->frag[dir][f].empty) {
                continue;
            }

            /*
             * For each orientation of a frag.
             */
            for (c = 0; c < fragmap->trigger_cnt_alts[f]; c++) {
#ifdef MAZE_DEBUG_SHOW_AS_GENERATING_FRAGMENTS
                maze_print_cells(dg);
                map_jigsaw_buffer_print();
#endif
                /*
                 * Try and place the frag.
                 */
                tries = 0;
                while (tries++ < MAX_MAP_NUMBER_OF_TIMES_TO_TRY_AND_PLACE_FRAG) {

                    ax = myrand() % (MAP_WIDTH + JIGPIECE_WIDTH);
                    ay = myrand() % (MAP_HEIGHT + JIGPIECE_HEIGHT);
                    ax -= JIGPIECE_WIDTH;
                    ay -= JIGPIECE_HEIGHT;

                    for (x = 0; x < JIGPIECE_WIDTH; x++) {
                        for (y = 0; y < JIGPIECE_HEIGHT; y++) {
                            /*
                             * Skip empty spaces.
                             */
                            frag = fragmap->trigger_fragment[dir][f].c[x][y];
                            if (frag == MAP_EMPTY) {
                                continue;
                            }

                            cx = ax + x;
                            cy = ay + y;

                            /*
                             * It's ok to be off map but only if a space.
                             */
                            if ((cx < 0) || (cx >= MAP_WIDTH) ||
                                (cy < 0) || (cy >= MAP_HEIGHT)) {
                                goto next;
                            }

                            /*
                             * Check the frag is an exact match.
                             */
                            map = map_jigsaw_buffer_getchar(cx, cy);
                            if (map != frag) {
                                /*
                                 * Allow the frag to force that spaces
                                 * must exist.
                                 */
                                if (frag == MAP_SPACE) {
                                    if (map == MAP_EMPTY) {
                                        continue;
                                    }
                                }
                                goto next;
                            }
                        }
                    }

                    /*
                     * Choose something to replace the frag.
                     */
                    do {
                        i = myrand() % fragmap->trigger_cnt_alts[f];
                        i += fragmap->trigger_fragment_to_alt_base[f];

                    } while (fragmap->trigger[dir][i].empty);

                    color = color_find_nth(color_n++);

                    /*
                     * Place the frag.
                     */
                    for (x = 0; x < JIGPIECE_WIDTH; x++) {
                        for (y = 0; y < JIGPIECE_HEIGHT; y++) {
                            frag = fragmap->trigger_fragment[dir][f].c[x][y];
                            alt = fragmap->trigger[dir][i].c[x][y];
                            action1 = fragmap->action1[dir][i].c[x][y];
                            action2 = fragmap->action2[dir][i].c[x][y];
                            action3 = fragmap->action3[dir][i].c[x][y];

                            cx = ax + x;
                            cy = ay + y;

                            /*
                             * Skip off map.
                             */
                            if ((cx < 0) || (cx >= MAP_WIDTH) ||
                                (cy < 0) || (cy >= MAP_HEIGHT)) {
                                continue;
                            }

                            map_jigsaw_buffer_goto(cx, cy);

                            if (alt != frag) {
                                map_jigsaw_buffer_putchar(alt);
                                map_jigsaw_buffer_at_x--;
                            }

                            if (action1 != frag) {
                                map_jigsaw_buffer_action1[map_jigsaw_buffer_at_x][map_jigsaw_buffer_at_y] = 
                                            action1;
                            }

                            if (action2 != frag) {
                                map_jigsaw_buffer_action2[map_jigsaw_buffer_at_x][map_jigsaw_buffer_at_y] = 
                                            action2;
                            }

                            if (action3 != frag) {
                                map_jigsaw_buffer_action3[map_jigsaw_buffer_at_x][map_jigsaw_buffer_at_y] = 
                                            action3;
                            }

                            map_jigsaw_buffer_color[map_jigsaw_buffer_at_x][map_jigsaw_buffer_at_y] = 
                                            color;

                        }
                    }

                    break;
next:
                    continue;
                }
            }
        }
    }
}
#endif

/*
 * jigpiece_create_mirrored_pieces
 */
void jigpiece_create_mirrored_pieces (frag_t *fragmap)
{
    int32_t c;
    int32_t x;
    int32_t y;
    int32_t r;
    int32_t origs_cnt;
    int32_t prev;

    origs_cnt = fragmap->jigpieces_cnt;

    for (c = 0; c < origs_cnt; c++) {

        /*
         * How many doors etc... are in each jigpiece? We use this to avoid
         * flipping some jigpiece types.
         */
        jigpiece_count_char_types(fragmap, c);

        /*
         * Generate 3 rotations
         */
        prev = c;
        for (r=0; r<3; r++) {
            /*
             * Rotate 90 degrees
             */
            if (fragmap->jigpieces_cnt >= JIGPIECE_MAX) {
                ERR("Too many jigpiece to mirror");
            }

            for (x = 0; x < JIGPIECE_WIDTH; x++) {
                for (y = 0; y < JIGPIECE_HEIGHT; y++) {

                    if (fragmap->jigpiece[c].rotatable) {
                        fragmap->jigpiece[fragmap->jigpieces_cnt].c[JIGPIECE_WIDTH - 1 - y][x] =
                                fragmap->jigpiece[prev].c[x][y];
                    } else {
                        fragmap->jigpiece[fragmap->jigpieces_cnt].c[x][y] =
                                fragmap->jigpiece[prev].c[x][y];
                        fragmap->jigpiece[fragmap->jigpieces_cnt].empty = true;
                    }
                }
            }

            jigpiece_count_char_types(fragmap, fragmap->jigpieces_cnt);
            prev = fragmap->jigpieces_cnt++;
        }

        /*
         * Mirror horizontally
         */
        if (fragmap->jigpieces_cnt >= JIGPIECE_MAX) {
            ERR("Too many jigpiece to mirror");
        }

        for (x = 0; x < JIGPIECE_WIDTH; x++) {
            for (y = 0; y < JIGPIECE_HEIGHT; y++) {

                if (fragmap->jigpiece[c].horiz_flip) {
                    fragmap->jigpiece[fragmap->jigpieces_cnt].c[JIGPIECE_WIDTH - 1 - x][y] =
                            fragmap->jigpiece[c].c[x][y];
                } else {
                    fragmap->jigpiece[fragmap->jigpieces_cnt].c[x][y] =
                            fragmap->jigpiece[c].c[x][y];
                    fragmap->jigpiece[fragmap->jigpieces_cnt].empty = true;
                }
            }
        }

        jigpiece_count_char_types(fragmap, fragmap->jigpieces_cnt);
        fragmap->jigpieces_cnt++;

        /*
         * Mirror vertically
         */
        if (fragmap->jigpieces_cnt >= JIGPIECE_MAX) {
            ERR("Too many jigpiece to mirror");
        }

        for (x = 0; x < JIGPIECE_WIDTH; x++) {
            for (y = 0; y < JIGPIECE_HEIGHT; y++) {

                if (fragmap->jigpiece[c].vert_flip) {
                    fragmap->jigpiece[fragmap->jigpieces_cnt].c[x][JIGPIECE_HEIGHT - 1 - y] =
                            fragmap->jigpiece[c].c[x][y];
                } else {
                    fragmap->jigpiece[fragmap->jigpieces_cnt].c[x][y] =
                            fragmap->jigpiece[c].c[x][y];
                    fragmap->jigpiece[fragmap->jigpieces_cnt].empty = true;
                }
            }
        }

        jigpiece_count_char_types(fragmap, fragmap->jigpieces_cnt);
        fragmap->jigpieces_cnt++;

        /*
         * Mirror horizontally and vertically
         */
        if (fragmap->jigpieces_cnt >= JIGPIECE_MAX - 1) {
            ERR("Too many jigpiece to mirror");
        }

        for (x = 0; x < JIGPIECE_WIDTH; x++) {
            for (y = 0; y < JIGPIECE_HEIGHT; y++) {

                /*
                 * Bit of a hack, use the next jigpiece as scratch space else
                 * we end up overwriting what we are mirroring vertically
                 * below.
                 */
                if (fragmap->jigpiece[c].vert_flip && 
                    fragmap->jigpiece[c].horiz_flip) {

                    fragmap->jigpiece[fragmap->jigpieces_cnt+1].c[JIGPIECE_WIDTH - 1 - x][y] =
                            fragmap->jigpiece[c].c[x][y];
                } else {
                    fragmap->jigpiece[fragmap->jigpieces_cnt+1].c[x][y] =
                            fragmap->jigpiece[c].c[x][y];
                    fragmap->jigpiece[fragmap->jigpieces_cnt+1].empty = true;
                }
            }
        }

        for (x = 0; x < JIGPIECE_WIDTH; x++) {
            for (y = 0; y < JIGPIECE_HEIGHT; y++) {

                if (fragmap->jigpiece[c].vert_flip && 
                    fragmap->jigpiece[c].horiz_flip) {

                    fragmap->jigpiece[fragmap->jigpieces_cnt].c[x][JIGPIECE_HEIGHT - 1 - y] =
                            fragmap->jigpiece[fragmap->jigpieces_cnt+1].c[x][y];
                } else {
                    fragmap->jigpiece[fragmap->jigpieces_cnt].c[x][y] =
                            fragmap->jigpiece[fragmap->jigpieces_cnt+1].c[x][y];
                    fragmap->jigpiece[fragmap->jigpieces_cnt].empty = true;
                }
            }
        }

        jigpiece_count_char_types(fragmap, fragmap->jigpieces_cnt);
        fragmap->jigpieces_cnt++;
    }
}

/*
 * jigpiece_create_mirrored_frag
 */
void jigpiece_create_mirrored_frag (frag_t *fragmap)
{
    int32_t c;
    int32_t x;
    int32_t y;
    int32_t dir;

    for (c = 0; c < fragmap->frag_cnt; c++) {
        /*
         * Generate 3 rotations
         */
        for (dir=1; dir<4; dir++) {
            /*
             * Rotate 90 degrees
             */
            for (x = 0; x < JIGPIECE_WIDTH; x++) {
                for (y = 0; y < JIGPIECE_HEIGHT; y++) {

                    if (fragmap->frag[0][c].rotatable) {
                        fragmap->frag[dir][c].c[JIGPIECE_WIDTH - 1 - y][x] =
                                        fragmap->frag[dir-1][c].c[x][y];
                    } else {
                        fragmap->frag[dir][c].c[x][y] =
                                        fragmap->frag[dir-1][c].c[x][y];
                        fragmap->frag[dir][c].empty = true;
                    }
                }
            }
        }

        /*
         * Mirror horizontally
         */
        for (x = 0; x < JIGPIECE_WIDTH; x++) {
            for (y = 0; y < JIGPIECE_HEIGHT; y++) {

                if (fragmap->frag[0][c].horiz_flip) {
                    fragmap->frag[dir][c].c[JIGPIECE_WIDTH - 1 - x][y] =
                                    fragmap->frag[0][c].c[x][y];
                } else {
                    fragmap->frag[dir][c].c[x][y] =
                                    fragmap->frag[0][c].c[x][y];
                    fragmap->frag[dir][c].empty = true;
                }
            }
        }

        /*
         * Mirror vertically
         */
        dir++;

        for (x = 0; x < JIGPIECE_WIDTH; x++) {
            for (y = 0; y < JIGPIECE_HEIGHT; y++) {

                if (fragmap->frag[0][c].vert_flip) {

                    fragmap->frag[dir][c].c[x][JIGPIECE_HEIGHT - 1 - y] =
                                fragmap->frag[0][c].c[x][y];
                } else {
                    fragmap->frag[dir][c].c[x][y] =
                                fragmap->frag[0][c].c[x][y];
                    fragmap->frag[dir][c].empty = true;
                }
            }
        }

        /*
         * Mirror horizontally and vertically
         */
        dir++;

        for (x = 0; x < JIGPIECE_WIDTH; x++) {
            for (y = 0; y < JIGPIECE_HEIGHT; y++) {

                /*
                 * Bit of a hack, use the next frag as scratch space else
                 * we end up overwriting what we are mirroring vertically
                 * below.
                 */
                if (fragmap->frag[0][c].vert_flip &&
                    fragmap->frag[0][c].horiz_flip) {

                    fragmap->frag[dir][c+1].c[JIGPIECE_WIDTH - 1 - x][y] =
                                        fragmap->frag[0][c].c[x][y];
                } else {
                    fragmap->frag[dir][c+1].c[x][y] =
                                        fragmap->frag[0][c].c[x][y];
                    fragmap->frag[dir][c+1].empty = true;
                }
            }
        }

        for (x = 0; x < JIGPIECE_WIDTH; x++) {
            for (y = 0; y < JIGPIECE_HEIGHT; y++) {

                if (fragmap->frag[0][c].vert_flip &&
                    fragmap->frag[0][c].horiz_flip) {

                    fragmap->frag[dir][c].c[x][JIGPIECE_HEIGHT - 1 - y] =
                                        fragmap->frag[dir][c+1].c[x][y];
                } else {
                    fragmap->frag[dir][c].c[x][y] =
                                        fragmap->frag[dir][c+1].c[x][y];
                    fragmap->frag[dir][c].empty = true;
                }
            }
        }
    }
}

/*
 * jigpiece_create_mirrored_frag_alt
 */
void jigpiece_create_mirrored_frag_alt (frag_t *fragmap)
{
    int32_t c;
    int32_t x;
    int32_t y;
    int32_t dir;

    for (c = 0; c < fragmap->frag_alt_cnt; c++) {

        for (y = 0; y < JIGPIECE_HEIGHT; y++) {
            for (x = 0; x < JIGPIECE_WIDTH; x++) {
                uint32_t alt = fragmap->frag_alt[0][c].c[x][y];

                if (!valid_frag_alt_char[alt]) {
                    for (y = 0; y < JIGPIECE_HEIGHT; y++) {
                        for (x = 0; x < JIGPIECE_WIDTH; x++) {
                            uint32_t alt = fragmap->frag_alt[0][c].c[x][y];

                            printf("%c", alt);
                        }

                        printf("\n");
                    }
                    printf("\n");

                    ERR("invalid fragment alt char [0x%x/%c] above", alt, alt);
                }
            }
        }

        /*
         * Generate 3 rotations
         */
        for (dir=1; dir<4; dir++) {
            /*
             * Rotate 90 degrees
             */
            for (x = 0; x < JIGPIECE_WIDTH; x++) {
                for (y = 0; y < JIGPIECE_HEIGHT; y++) {

                    if (fragmap->frag_alt[0][c].rotatable) {
                        fragmap->frag_alt[dir][c].c[JIGPIECE_WIDTH - 1 - y][x] =
                                        fragmap->frag_alt[dir-1][c].c[x][y];
                    } else {
                        fragmap->frag_alt[dir][c].c[x][y] =
                                        fragmap->frag_alt[dir-1][c].c[x][y];
                        fragmap->frag_alt[dir][c].empty = true;
                    }
                }
            }
        }

        /*
         * Mirror horizontally
         */
        for (x = 0; x < JIGPIECE_WIDTH; x++) {
            for (y = 0; y < JIGPIECE_HEIGHT; y++) {

                if (fragmap->frag_alt[0][c].horiz_flip) {

                    fragmap->frag_alt[dir][c].c[JIGPIECE_WIDTH - 1 - x][y] =
                                    fragmap->frag_alt[0][c].c[x][y];
                } else {
                    fragmap->frag_alt[dir][c].c[x][y] =
                                    fragmap->frag_alt[0][c].c[x][y];
                    fragmap->frag_alt[dir][c].empty = true;
                }
            }
        }

        /*
         * Mirror vertically
         */
        dir++;

        for (x = 0; x < JIGPIECE_WIDTH; x++) {
            for (y = 0; y < JIGPIECE_HEIGHT; y++) {

                if (fragmap->frag_alt[0][c].vert_flip) {

                    fragmap->frag_alt[dir][c].c[x][JIGPIECE_HEIGHT - 1 - y] =
                                fragmap->frag_alt[0][c].c[x][y];
                } else {
                    fragmap->frag_alt[dir][c].c[x][y] =
                                fragmap->frag_alt[0][c].c[x][y];
                    fragmap->frag_alt[dir][c].empty = true;
                }
            }
        }

        /*
         * Mirror horizontally and vertically
         */
        dir++;

        for (x = 0; x < JIGPIECE_WIDTH; x++) {
            for (y = 0; y < JIGPIECE_HEIGHT; y++) {

                /*
                 * Bit of a hack, use the next frag as scratch space else
                 * we end up overwriting what we are mirroring vertically
                 * below.
                 */
                if (fragmap->frag_alt[0][c].vert_flip &&
                    fragmap->frag_alt[0][c].horiz_flip) {

                    fragmap->frag_alt[dir][c+1].c[JIGPIECE_WIDTH - 1 - x][y] =
                                        fragmap->frag_alt[0][c].c[x][y];
                } else {
                    fragmap->frag_alt[dir][c+1].c[x][y] =
                                        fragmap->frag_alt[0][c].c[x][y];
                    fragmap->frag_alt[dir][c+1].empty = true;
                }
            }
        }

        for (x = 0; x < JIGPIECE_WIDTH; x++) {
            for (y = 0; y < JIGPIECE_HEIGHT; y++) {

                if (fragmap->frag_alt[0][c].vert_flip &&
                    fragmap->frag_alt[0][c].horiz_flip) {

                    fragmap->frag_alt[dir][c].c[x][JIGPIECE_HEIGHT - 1 - y] =
                                        fragmap->frag_alt[dir][c+1].c[x][y];
                } else {
                    fragmap->frag_alt[dir][c].c[x][y] =
                                        fragmap->frag_alt[dir][c+1].c[x][y];
                    fragmap->frag_alt[dir][c].empty = true;
                }
            }
        }
    }
}

/*
 * jigpiece_intersect_score
 */
static int32_t jigpiece_intersect_score (frag_t *fragmap, int32_t a, int32_t dir, int32_t b)
{
    return (
        (fragmap->jigpiece[a].exits[dir] == fragmap->jigpiece[b].exits[3 - dir]) ?
            1 : 0);
}

/*
 * maze_generate_all_random_directions
 */
static void maze_generate_all_random_directions (dungeon_t *dg, maze_cell_t * c)
{
    int32_t dir;
    int32_t any_dir;
    int32_t new_dir;

    c->walked = 1;

    while (1) {
        /*
         * Check we have somewhere we can go to.
         */
        for (dir = 0, any_dir = 0; dir < 4; dir++) {
            any_dir += MAZE_CAN_GO(c, dir);
        }

        /*
         * At the end of the maze?
         */
        if (!any_dir) {
            return;
        }

        /*
         * Choose a random dir to walk.
         */
        do {
            new_dir = myrand() % 4;
        } while (!MAZE_CAN_GO(c, new_dir));


        c->exits |= (1 << new_dir);
        c->exit[new_dir]->exits |= (1 << (3 - new_dir));

        /*
         * Fork chance
         */
        if ((myrand() % 100) < dg->level) {
            do {
                new_dir = myrand() % 4;
            } while (!MAZE_CAN_GO(c, new_dir));

            c->exits |= (1 << new_dir);
            c->exit[new_dir]->exits |= (1 << (3 - new_dir));
        }

        maze_generate_all_random_directions(dg, c->exit[new_dir]);
    }
}

/*
 * Wrap all corridors in walls
 */
void maze_add_borders_around_rooms_and_corridors (void)
{
    int32_t x;
    int32_t y;
    int32_t dx;
    int32_t dy;

    for (x = 1; x < MAP_WIDTH - 1; x++) {
        for (y = 1; y < MAP_HEIGHT - 1; y++) {

            if ((map_jigsaw_buffer_getchar(x, y) != MAP_CORRIDOR)) {
                continue;
            }

            for (dx = -1; dx <=1; dx++) {
                for (dy = -1; dy <=1; dy++) {
                    if (map_jigsaw_buffer_getchar(x+dx, y+dy) == MAP_EMPTY) {
                        map_jigsaw_buffer_goto(x+dx, y+dy);
                        map_jigsaw_buffer_putchar(MAP_HARD_WALL);
                    }
                }
            }
        }
    }

    LOG("Maze: Added corridor walls");
    map_jigsaw_buffer_print_file(MY_STDOUT, 0 /* final */);

    /*
     * Make sure all floor tiles have a wall around them.
     */
    for (x = 1; x < MAP_WIDTH - 1; x++) {
        for (y = 1; y < MAP_HEIGHT - 1; y++) {

            if ((map_jigsaw_buffer_getchar(x, y) != MAP_FLOOR)) {
                continue;
            }

            for (dx = -1; dx <=1; dx++) {
                for (dy = -1; dy <=1; dy++) {
                    if (map_jigsaw_buffer_getchar(x+dx, y+dy) == MAP_EMPTY) {
                        map_jigsaw_buffer_goto(x+dx, y+dy);
                        map_jigsaw_buffer_putchar(MAP_WALL);
                    }
                }
            }
        }
    }

    LOG("Maze: Added walls around floor tiles");
    map_jigsaw_buffer_print_file(MY_STDOUT, 0 /* final */);
}

/*
 * Wrap all corridors in walls
 */
void maze_add_final_borders (void)
{
    int x, y;

    for (x = 0; x < MAP_WIDTH; x++) {
        if (jigpiece_char_is_occupiable(map_jigsaw_buffer_getchar(x, 0))) {
            map_jigsaw_buffer_goto(x, 0);
            map_jigsaw_buffer_putchar(MAP_WALL);
        }

        if (jigpiece_char_is_occupiable(map_jigsaw_buffer_getchar(x, MAP_HEIGHT - 1))) {
            map_jigsaw_buffer_goto(x, MAP_HEIGHT - 1);
            map_jigsaw_buffer_putchar(MAP_WALL);
        }
    }

    for (y = 0; y < MAP_HEIGHT; y++) {
        if (jigpiece_char_is_occupiable(map_jigsaw_buffer_getchar(0, y))) {
            map_jigsaw_buffer_goto(0, y);
            map_jigsaw_buffer_putchar(MAP_WALL);
        }

        if (jigpiece_char_is_occupiable(map_jigsaw_buffer_getchar(MAP_WIDTH - 1, y))) {
            map_jigsaw_buffer_goto(MAP_WIDTH - 1, y);
            map_jigsaw_buffer_putchar(MAP_WALL);
        }
    }

    LOG("Maze: Added maze border");
    map_jigsaw_buffer_print_file(MY_STDOUT, 0 /* final */);
}

static int maze_flood_find (int32_t x, int32_t y, char find, int depth)
{
    static char walked[MAP_WIDTH][MAP_HEIGHT];

    if (!depth) {
        memset(walked, ' ', sizeof(walked));
        memset(map_jigsaw_buffer_solved, 0, sizeof(map_jigsaw_buffer_solved));
    }

    if (walked[x][y] != ' ') {
        return (false);
    }

    if (map_jigsaw_buffer_getchar(x, y) == find) {
        map_jigsaw_buffer_solved[x][y] = 1;
        return (depth);
    }

    walked[x][y] = '.';

    if (jigpiece_char_is_passable(map_jigsaw_buffer_getchar(x-1, y))) {
        int solved = maze_flood_find(x-1, y, find, depth + 1);
        if (solved) {
            map_jigsaw_buffer_solved[x][y] = 1;
            return (solved);
        }
    }

    if (jigpiece_char_is_passable(map_jigsaw_buffer_getchar(x+1, y))) {
        int solved = maze_flood_find(x+1, y, find, depth + 1);
        if (solved) {
            map_jigsaw_buffer_solved[x][y] = 1;
            return (solved);
        }
    }

    if (jigpiece_char_is_passable(map_jigsaw_buffer_getchar(x, y-1))) {
        int solved = maze_flood_find(x, y-1, find, depth + 1);
        if (solved) {
            map_jigsaw_buffer_solved[x][y] = 1;
            return (solved);
        }
    }

    if (jigpiece_char_is_passable(map_jigsaw_buffer_getchar(x, y+1))) {
        int solved = maze_flood_find(x, y+1, find, depth + 1);
        if (solved) {
            map_jigsaw_buffer_solved[x][y] = 1;
            return (solved);
        }
    }

    return (false);
}

static int maze_check_exit_can_be_reached (void)
{
    int32_t x;
    int32_t y;
    int32_t sx;
    int32_t sy;
    int found_start = 0;

    y = 1;
    for (x = 1; x < MAP_WIDTH - 1; x++) {
        for (y = 1; y < MAP_HEIGHT - 1; y++) {

            if ((map_jigsaw_buffer_getchar(x, y) == MAP_START)) {
                found_start = 1;
                break;
            }
        }

        if (found_start) {
            break;
        }
    }

    if (!found_start) {
        return (false);
    }

    sx = x;
    sy = y;

    int found_end = 0;

    for (x = 1; x < MAP_WIDTH - 1; x++) {
        for (y = 1; y < MAP_HEIGHT - 1; y++) {

            if ((map_jigsaw_buffer_getchar(x, y) == MAP_END)) {
                found_end = 1;
                break;
            }
        }

        if (found_end) {
            break;
        }
    }

    if (!found_end) {
        return (false);
    }

    int depth = maze_flood_find(sx, sy, MAP_END, 0);
    if (depth <= MAZE_MIN_DISTANCE_START_AND_END) {
        return (false);
    }

    return (true);
}

/*
 * Find "old" in a room and replace with "new"
 */
static uint8_t 
maze_replace_room_char (char new_char)
{
    uint32_t tries = MAP_WIDTH * MAP_HEIGHT * 10;

    while (tries--) {
        uint32_t cx = myrand() % MAP_WIDTH;
        uint32_t cy = myrand() % MAP_HEIGHT;
        
        if (jigpiece_char_is_dungeon_floor_or_corridor(map_jigsaw_buffer_getchar(cx, cy)) &&
            jigpiece_char_is_dungeon_floor_or_corridor(map_jigsaw_buffer_getchar(cx - 1, cy)) &&
            jigpiece_char_is_dungeon_floor_or_corridor(map_jigsaw_buffer_getchar(cx, cy - 1)) &&
            jigpiece_char_is_dungeon_floor_or_corridor(map_jigsaw_buffer_getchar(cx + 1, cy)) &&
            jigpiece_char_is_dungeon_floor_or_corridor(map_jigsaw_buffer_getchar(cx, cy + 1)) &&
            !jigpiece_char_is_monst((map_jigsaw_buffer_getchar(cx-1, cy))) &&
            !jigpiece_char_is_monst((map_jigsaw_buffer_getchar(cx-2, cy))) &&
            !jigpiece_char_is_monst((map_jigsaw_buffer_getchar(cx+1, cy))) &&
            !jigpiece_char_is_monst((map_jigsaw_buffer_getchar(cx+2, cy)))) {

            map_jigsaw_buffer_goto(cx, cy);
            map_jigsaw_buffer_putchar(new_char);

            return (true);
        }
    }

    return (false);
}

static void maze_check_teleports (void)
{
    int32_t x;
    int32_t y;
    int teleport = 0;

    for (x = 1; x < MAP_WIDTH - 1; x++) {
        for (y = 1; y < MAP_HEIGHT - 1; y++) {

            if ((map_jigsaw_buffer_getchar(x, y) == MAP_TELEPORT)) {
                teleport++;
            }
        }
    }

    if (teleport > 1) {
        return;
    }

    for (x = 1; x < MAP_WIDTH - 1; x++) {
        for (y = 1; y < MAP_HEIGHT - 1; y++) {
            if ((map_jigsaw_buffer_getchar(x, y) == MAP_TELEPORT)) {
                map_jigsaw_buffer_goto(x, y);
                map_jigsaw_buffer_putchar(MAP_ROCK);
            }
        }
    }
}

/*
 * maze_dump_jigpieces_to_map
 */
static void dump_jigpieces_to_map (dungeon_t *dg, frag_t *fragmap)
{
    int32_t w = MAP_JIGSAW_PIECES_ACROSS;
    int32_t h = MAP_JIGSAW_PIECES_DOWN;
    int32_t y;
    int32_t x;

    /*
     * Offset the map by an amount so we can have a border.
     */
    int dx = ((MAP_WIDTH - (JIGPIECE_WIDTH * MAP_JIGSAW_PIECES_ACROSS)) / 2);
    int dy = ((MAP_HEIGHT - (JIGPIECE_HEIGHT * MAP_JIGSAW_PIECES_DOWN)) / 2);

    for (y = 0; y < MAP_HEIGHT; y++) {
        for (x = 0; x < MAP_WIDTH; x++) {
            map_jigsaw_buffer_goto(x, y);
            map_jigsaw_buffer_putchar(MAP_EMPTY);
        }
    }

    for (y = 0; y < h; y++) {
        for (x = 0; x < w; x++) {

            maze_cell_t *c = MAZE_CELL(dg->maze, x, y);

            if (c->jigpiece_index) {
                jigpiece_printat(fragmap,
                                (JIGPIECE_WIDTH * x) + dx,
                                (JIGPIECE_HEIGHT * y) + dy, c->jigpiece_index);
            }
        }
    }
}

#ifdef MAZE_DEBUG_SHOW_AS_GENERATING
/*
 * maze_debug
 */
static void maze_debug (dungeon_t *dg)
{
    dump_jigpieces_to_map(dg);

    map_jigsaw_buffer_print();

    memset(map_jigsaw_buffer, 0, sizeof(map_jigsaw_buffer));
    putchar('\n');
    map_jigsaw_buffer_set_fgbg(TERM_COLOR_WHITE, TERM_COLOR_BLACK);

    putchar('\n');
}
#endif

void maze_add_random_junk (void)
{
    int x, y;

    /*
     * Add random junk outside the level
     */
    for (x = 0; x <= MAP_WIDTH - 1; x++) {
        for (y = 0; y <= MAP_HEIGHT - 1; y++) {

            if (map_jigsaw_buffer_getchar(x, y) != MAP_EMPTY) {
                continue;
            }

            map_jigsaw_buffer_goto(x, y);

            int r = myrand() % 1000;
            if (r < 450) {
                map_jigsaw_buffer_putchar(MAP_ROCK);
            } else if (r < 252) {
                map_jigsaw_buffer_putchar(MAP_GENERATOR);
            } else if (r < 255) {
                map_jigsaw_buffer_putchar(MAP_LAVA);
            } else if (r < 257) {
                map_jigsaw_buffer_putchar(MAP_TRAP);
            } else if (r < 258) {
                map_jigsaw_buffer_putchar(MAP_TREASURE);
            } else {
                /*
                 * space
                 */
            }
        }
    }

    LOG("Maze: Added random junk in outside of level");
    map_jigsaw_buffer_print_file(MY_STDOUT, 0 /* final */);
}

/*
 * maze_convert_to_map
 */
static void maze_convert_to_map (dungeon_t *dg)
{
    int x, y, dx, dy;

    for (x = 1; x < MAP_WIDTH - 1; x++) {
        for (y = 1; y < MAP_HEIGHT - 1; y++) {

            if ((map_jigsaw_buffer_getchar(x, y) != MAP_CORRIDOR)) {
                continue;
            }

            for (dx = -1; dx <=1; dx++) {
                for (dy = -1; dy <=1; dy++) {
                    if (map_jigsaw_buffer_getchar(x+dx, y+dy) == MAP_EMPTY) {
                        map_jigsaw_buffer_goto(x+dx, y+dy);
                        map_jigsaw_buffer_putchar(MAP_HARD_WALL);
                    }
                }
            }
        }
    }
}

/*
 * maze_jigsaw_generate_all_possible_pieces
 *
 * Make a list of all the jigpiece that satisfy the connection needs of this
 * maze cell.
 */
static uint8_t maze_jigsaw_generate_all_possible_pieces (dungeon_t *dg, 
                                                         frag_t *fragmap)
{
    int32_t w = MAP_JIGSAW_PIECES_ACROSS;
    int32_t h = MAP_JIGSAW_PIECES_DOWN;
    maze_cell_t *mcell;
    int32_t dir;
    int32_t x;
    int32_t y;
    int32_t c;
    int32_t a;
    int32_t b;

    for (y = 0; y < h; y++) {
        for (x = 0; x < w; x++) {

            mcell = MAZE_CELL(dg->maze, x, y);
            mcell->possible_jigpieces_size = 0;
            mcell->x = x;
            mcell->y = y;

            for (c = 1; c < fragmap->jigpieces_cnt; c++) {

                /*
                 * DOn't have dead end corridors, so filter out all jigpieces 
                 * that are just corridors where the maze cell has only one 
                 * exit, i.e. it's a dead end.
                 */
                if (!MULTIPLE_BITS((int)mcell->exits)) {
                    if (fragmap->jigpiece[c].has[MAP_CORRIDOR]) {
                        continue;
                    }
                }

                for (dir = 0; dir < DIR_MAX; dir++) {
                    /*
                     * Filter to pieces that have at least one exit in each of
                     * all the directions needed.
                     */
                    a = fragmap->jigpiece[c].exits[dir] ? 1 : 0;
                    b = MAZE_HAS_EXIT(dg->maze, x, y, dir) ? 1 : 0;

                    if (a != b) {
                        break;
                    }
                }

                if (dir == DIR_MAX) {
                    mcell->possible_jigpieces[mcell->possible_jigpieces_size++] = c;
                }
            }

            if (!mcell->possible_jigpieces_size) {
                printf("cell %d %d\n",x,y);
                maze_print_cells(dg);

                return (false);
            }
        }
    }

    return (true);
}

/*
 * maze_generate_jigpiece_find
 *
 * Returns 0 on failure. 1 on being able to fill the maze with jigsaw pieces.
 */
static int32_t
maze_generate_jigpiece_find (dungeon_t *dg, 
                             frag_t *fragmap,
                             maze_cell_t *mcell,
                             uint32_t *count)
{
    int32_t intersect_list[mcell->possible_jigpieces_size];
    int32_t intersect_list_size;
    maze_cell_t *ocell;
    int32_t dir;
    int32_t exits;
    int32_t p;
    int32_t c;
    int32_t ok = 0;
    uint32_t i;

    (*count)++;

    /*
     * Tried to long to solve this maze? Try another.
     */
    if (*count > MAZE_HOW_LONG_TO_SPEND_TRYING_TO_SOLVE_MAZE) {
        return (0);
    }

#ifdef MAZE_DEBUG_SHOW_AS_GENERATING
    maze_debug(dg);
#endif

    /*
     * Already solved this cell?
     */
    if (mcell->jigpiece_index) {
        return (1);
    }

    c = 0;
    intersect_list_size = 0;

    /*
     * +---+---+
     * | M |   |
     * +   +   +
     * | O |   |
     * +   +   +
     * |       |
     * +---+---+
     *
     * mcell == M
     * ocell == O
     */
    for (p = 0; p < mcell->possible_jigpieces_size; p++) {

        c = mcell->possible_jigpieces[p];

        /*
         * Filter to only cells that satisfy all direction exits.
         */
        for (dir = 0; dir < DIR_MAX; dir++) {

            /*
             * Try to satisfy M and create a cell that joins onto all its
             * neighbors.
             */
            if (!(mcell->exits & (1 << dir))) {
                continue;
            }

            ocell = mcell->exit[dir];
            if (!ocell) {
                continue;
            }

            /*
             * If no neighbor in a given direction, we can't determine what to
             * put.
             */
            if (!ocell->jigpiece_index) {
                continue;
            }

            /*
             * No rooms next to other rooms just to cut the number of rooms in
             * half.
             */
#if 0
            if (fragmap->jigpiece[c].has[MAP_FLOOR]) {
                if (fragmap->jigpiece[ocell->jigpiece_index].has[MAP_FLOOR]) {
                    if ((myrand() % 100) > fragmap->level * 2) {
                        break;
                    }
                }
            }
#endif

            /*
             * If the cells join exactly then this is a possibility.
             */
            if (!jigpiece_intersect_score(fragmap, c, dir, ocell->jigpiece_index)) {
                break;
            }
        }

        if (dir == DIR_MAX) {
            intersect_list[intersect_list_size++] = c;
        }
    }

    if (!intersect_list_size) {
        mcell->jigpiece_index = 0;
        return (0);
    }

    /*
     * Choose a random jigsaw piece. 
     */
    for (i=0; i < 1 + (myrand() % 3); i++) {

        uint32_t j = intersect_list[myrand() % intersect_list_size];
        jigpiece_t *jp = &fragmap->jigpiece[j];

        /*
         * Only allow one shop per level.
         */
        int skip = false;
        int m;

        if (jp->has[MAP_SHOP_FLOOR]) {
            for (m = 0; m < MAP_JIGSAW_PIECES_ACROSS * MAP_JIGSAW_PIECES_DOWN; m++) {
                uint32_t k = dg->maze[m].jigpiece_index;
                if (k) {
                    jigpiece_t *kp = &fragmap->jigpiece[k];
                    if (kp->has[MAP_SHOP_FLOOR]) {
                        skip = true;
                    }
                }
            }
        }

        if (skip) {
            continue;
        }

        mcell->jigpiece_index = j;
        mcell->jp = jp;

        exits = 0;
        ok = 1;

        /*
         * And now make sure it fits all adjoining exits.
         */
        for (dir = 0; dir < DIR_MAX; dir++) {
            if (!(mcell->exits & (1 << dir))) {
                continue;
            }

            ocell = mcell->exit[dir];
            if (!ocell) {
                continue;
            }

            if (ocell->jigpiece_index) {
                continue;
            }

            exits = 1;

            /*
             * If it does not fit any one direction, abort.
             */
            if (!maze_generate_jigpiece_find(dg, fragmap, ocell, count)) {
                ok = 0;
                break;
            }
        }

        /*
         * If there were no adjoining pieces, then we pass automatically.
         */
        if (!exits) {
            return (1);
        }

        if (!ok) {
            /*
             * This piece does not fit. Try another.
             */
            continue;
        }

        /*
         * This piece fits
         */
        return (1);
    }

    mcell->jigpiece_index = 0;

    return (ok);
}

/*
 * maze_jigsaw_solve
 */
static int32_t maze_jigsaw_solve (dungeon_t *dg, frag_t *fragmap)
{
    int32_t w = MAP_JIGSAW_PIECES_ACROSS;
    int32_t h = MAP_JIGSAW_PIECES_DOWN;
    maze_cell_t *mcell;
    maze_cell_t *ocell;
    int32_t x, y;
    int32_t dir;
    int32_t c;

    for (;;) {
        x = myrand() % MAP_JIGSAW_PIECES_ACROSS;
        y = myrand() % MAP_JIGSAW_PIECES_DOWN;

        mcell = MAZE_CELL(dg->maze, x, y);
        if (!mcell->dead) {
            if (mcell->exits) {
                break;
            }
        }
    }

    for (c = 1; c < mcell->possible_jigpieces_size; c++) {

        /*
         * Reset the maze.
         */
        for (y = 0; y < h; y++) {
            for (x = 0; x < w; x++) {
                ocell = MAZE_CELL(dg->maze, x, y);
                ocell->jigpiece_index = 0;
            }
        }

        x = 0;
        y = 0;
        mcell->jigpiece_index =
            mcell->possible_jigpieces[myrand() % mcell->possible_jigpieces_size];

        for (dir = 0; dir < DIR_MAX; dir++) {
            if (!(mcell->exits & (1 << dir))) {
                continue;
            }

            ocell = mcell->exit[dir];
            if (!ocell) {
                continue;
            }

            /*
             * Recursively try to solve the maze jigsaw.
             */
            uint32_t count = 0;

            if (!maze_generate_jigpiece_find(dg, fragmap, ocell, &count)) {
                break;
            }
        }

        /*
         * If we satisfy all directions, we have a complete solution.
         */
        if (dir == DIR_MAX) {
            return (1);
        }
    }

    return (0);
}

/*
 * maze_solve_search
 */
static int32_t maze_solve_search (dungeon_t *dg, maze_cell_t *c)
{
    int32_t dir;

    if (c->solved) {
        return (0);
    }

    c->solved = 1;
    c->best = 1;

    if (c->end) {
        return (1);
    }

    for (dir = 0; dir < 4; dir++) {
        if (c->exits & (1 << dir)) {
            if (maze_solve_search(dg, c->exit[dir])) {
                return (1);
            }
        }
    }

    c->best = 0;
    return (0);
}


/*
 * maze_solve
 */
static int32_t maze_solve (dungeon_t *dg, int32_t w, int32_t h)
{
    int32_t x, y;
    maze_cell_t *s = 0;
    maze_cell_t *e = 0;
    maze_cell_t *c;
    int count = 0;

    /*
     * Assign a random start and exit.
     */
    while (1) {
        x = myrand() % w;
        y = myrand() % h;

        if (count++ > 10000) {
            return (0);
        }

        c = MAZE_CELL(dg->maze, x, y);

        if (!c->exits) {
            continue;
        }

        if (c == s) {
            continue;
        }

        if (c == e) {
            continue;
        }

        if (!s) {
            s = c;
            dg->sx = x;
            dg->sy = y;
            continue;
        }

        if (!e) {
            e = c;
            dg->ex = x;
            dg->ey = y;

            s->start = 1;
            e->end = 1;

            if (maze_solve_search(dg, s)) {
                return (1);
            }

            s->start = 0;
            e->end = 0;

            return (0);
        }
    }
}

/*
 * maze_generate_and_solve
 */
static uint8_t maze_generate_and_solve (dungeon_t *dg)
{
    int32_t y;
    int32_t x;
    int32_t w = MAP_JIGSAW_PIECES_ACROSS;
    int32_t h = MAP_JIGSAW_PIECES_DOWN;

    for (y = 0; y < h; y++) {
        for (x = 0; x < w; x++) {
            maze_cell_t * c = MAZE_CELL(dg->maze, x, y);

            c->exits = 0;
            c->exit[DIR_NORTH] = y > 0 ?
                            MAZE_CELL(dg->maze,   x  , y - 1) : 0;
            c->exit[DIR_SOUTH] = y < h-1 ?
                            MAZE_CELL(dg->maze,   x  , y + 1) : 0;
            c->exit[DIR_WEST]  = x > 0 ?
                            MAZE_CELL(dg->maze, x - 1,   y  ) : 0;
            c->exit[DIR_EAST]  = x < w-1 ?
                            MAZE_CELL(dg->maze, x + 1,   y  ) : 0;
        }
    }

    x = MAP_JIGSAW_PIECES_ACROSS / 2;
    y = MAP_JIGSAW_PIECES_DOWN / 2;

    maze_generate_all_random_directions(dg, MAZE_CELL(dg->maze, x, y));

    if (!maze_solve(dg, w, h)) {
        return (false);
    }

    return (true);
}

#if 0
/*
 * generate_fragmap
 */
static frag_t * generate_fragmap (const char *jigsaw_map)
{
    int32_t c;

    char *buf;

    frag_t *fragmap = (typeof(fragmap)) myzalloc(sizeof(frag_t), __FUNCTION__);

    /*
     * Read in the jigsaw pieces.
     */
    buf = filetobuf(jigsaw_map);
    if (!buf) {
        DIE("no jigsaw buffer");
    }

    jigpieces_read(fragmap, buf);
    myfree(buf);
    LOG("Maze: Read jigpieces");

    for (c = 0; c < fragmap->jigpieces_cnt; c++) {
        jigpiece_count_char_types(fragmap, c);
    }

    jigpiece_create_mirrored_pieces(fragmap);
    LOG("Maze: Created mirrored pieces");

    jigpiece_create_exits(fragmap);
    LOG("Maze: Created fragment exits");

    jigpiece_create_mirrored_frag(fragmap);
    jigpiece_create_mirrored_frag_alt(fragmap);
    jigpiece_check_frag(fragmap);

    return (fragmap);
}
#endif

/*
 * generate_level
 */
int32_t generate_level (dungeon_t *dg, frag_t *fragmap)
{
    for (;;) {
        if (!maze_generate_and_solve(dg)) {
            LOG("Maze: Generate failed, cannot generate");
            return (0);
        }

        if (!maze_jigsaw_generate_all_possible_pieces(dg, fragmap)) {
            LOG("Maze: Generate failed, cannot generate maze pieces");
            map_jigsaw_buffer_print_file(MY_STDOUT, 0 /* final */);
            return (0);
        }

        if (!maze_jigsaw_solve(dg, fragmap)) {
            LOG("Maze: Generate failed, cannot solve maze");
            map_jigsaw_buffer_print_file(MY_STDOUT, 0 /* final */);
            return (0);
        }

        break;
    }

    dump_jigpieces_to_map(dg, fragmap);

    maze_convert_to_map(dg);

    map_jigsaw_buffer_print_file(MY_STDOUT, 0 /* final */);

#ifdef MAZE_DEBUG_SHOW_CONSOLE
    map_jigsaw_buffer_print();
#endif

    return (1);
}

#if 0
/*
 * generate_add_frags
 */
static int32_t generate_add_frags (dungeon_t *dg,
                                   frag_t *fragmap,
                                   int cnt, 
                                   uint32_t chance)
{
    int i = 0;
    while (cnt--) {
        i++;

        jigpiece_add_triggers(dg, fragmap);

        jigpiece_add_frag(dg, fragmap, chance);
    }

    maze_convert_to_map(dg);

    map_jigsaw_buffer_print_file(MY_STDOUT, 0 /* final */);

#ifdef MAZE_DEBUG_SHOW_CONSOLE
    map_jigsaw_buffer_print();
#endif

    return (1);
}
#endif

/*
 * finalize_level
 */
int32_t finalize_level (dungeon_t *dg)
{
    LOG("Maze: Finalize level");

    if (!maze_replace_room_char(MAP_START)) {
        LOG("Maze: Generate failed, cannot place start");
        map_jigsaw_buffer_print_file(MY_STDOUT, 0 /* final */);
        return (false);
    }

    if (!maze_replace_room_char(MAP_END)) {
        LOG("Maze: Generate failed, cannot place exit");
        map_jigsaw_buffer_print_file(MY_STDOUT, 0 /* final */);
        return (false);
    }

    LOG("Maze: Added start and exit");
    map_jigsaw_buffer_print_file(MY_STDOUT, 0 /* final */);

    if (!maze_check_exit_can_be_reached()) {
        LOG("Maze: Generate failed, exit cannot be reached");
        map_jigsaw_buffer_print_file(MY_STDOUT, 0 /* final */);
        return (false);
    }

    LOG("Maze: Checked exit can be reached");
    map_jigsaw_buffer_print_file(MY_STDOUT, 0 /* final */);

    /*
     * Check at least 2 teleports.
     */
    maze_check_teleports();
    LOG("Maze: Checked teleports work");

    LOG("Maze: Final maze");
    map_jigsaw_buffer_print_file(MY_STDOUT, 1 /* final */);

#ifdef MAZE_DEBUG_SHOW_CONSOLE
    map_jigsaw_buffer_print();
#endif

    LOG("Maze: Created");

    return (1);
}

void map_init (void)
{
    map_fg[MAP_EMPTY]          = TERM_COLOR_BLACK;
    map_fg[MAP_SPACE]          = TERM_COLOR_WHITE;
    map_fg[MAP_WATER]          = TERM_COLOR_BLACK;
    map_fg[MAP_FLOOR]          = TERM_COLOR_WHITE;
    map_fg[MAP_SHOPKEEPER]     = TERM_COLOR_YELLOW;
    map_fg[MAP_SHOP_FLOOR]     = TERM_COLOR_GREEN;
    map_fg[MAP_ROCK]           = TERM_COLOR_BLUE;
    map_fg[MAP_WALL]           = TERM_COLOR_WHITE;
    map_fg[MAP_CORRIDOR]       = TERM_COLOR_YELLOW;
    map_fg[MAP_HARD_WALL]  = TERM_COLOR_BLUE;
    map_fg[MAP_MONST]          = TERM_COLOR_BLUE;
    map_fg[MAP_MONST_OR_MOB]   = TERM_COLOR_BLACK;
    map_fg[MAP_TRAP]           = TERM_COLOR_RED;
    map_fg[MAP_TELEPORT]       = TERM_COLOR_BLUE;
    map_fg[MAP_TREASURE]       = TERM_COLOR_WHITE;
    map_fg[MAP_FOOD]           = TERM_COLOR_GREEN;
    map_fg[MAP_LAVA]           = TERM_COLOR_YELLOW;
    map_fg[MAP_ACID]           = TERM_COLOR_GREEN;
    map_fg[MAP_CHASM]          = TERM_COLOR_GREEN;
    map_fg[MAP_EXIT_WEST]      = TERM_COLOR_BLUE;
    map_fg[MAP_EXIT_EAST]      = TERM_COLOR_BLUE;
    map_fg[MAP_EXIT_SOUTH]     = TERM_COLOR_BLUE;
    map_fg[MAP_EXIT_NORTH]     = TERM_COLOR_BLUE;
    map_fg[MAP_END]            = TERM_COLOR_BLUE;
    map_fg[MAP_START]          = TERM_COLOR_BLUE;
    map_fg[MAP_PADDING]        = TERM_COLOR_WHITE;
    map_fg[MAP_DOOR]           = TERM_COLOR_CYAN;
    map_fg[MAP_WEAPON]         = TERM_COLOR_GREEN;
    map_fg[MAP_GENERATOR]      = TERM_COLOR_CYAN;
    map_fg[MAP_BRAZIER]        = TERM_COLOR_YELLOW;
    map_fg[MAP_POTION]         = TERM_COLOR_CYAN;
    map_fg[MAP_TRIGGER_HERO]   = TERM_COLOR_RED;
    map_fg[MAP_TRIGGER_MONST]  = TERM_COLOR_RED;
    map_fg[MAP_ACTION_UP]      = TERM_COLOR_WHITE;
    map_fg[MAP_ACTION_DOWN]    = TERM_COLOR_WHITE;
    map_fg[MAP_ACTION_LEFT]    = TERM_COLOR_WHITE;
    map_fg[MAP_ACTION_RIGHT]   = TERM_COLOR_WHITE;
    map_fg[MAP_ACTION_SLEEP]   = TERM_COLOR_WHITE;
    map_fg[MAP_ACTION_ZAP]     = TERM_COLOR_WHITE;

    map_bg[MAP_EMPTY]          = TERM_COLOR_BLACK;
    map_bg[MAP_SPACE]          = TERM_COLOR_BLACK;
    map_bg[MAP_WATER]          = TERM_COLOR_CYAN;
    map_bg[MAP_FLOOR]          = TERM_COLOR_BLACK;
    map_bg[MAP_SHOPKEEPER]     = TERM_COLOR_BLACK;
    map_bg[MAP_SHOP_FLOOR]     = TERM_COLOR_BLACK;
    map_bg[MAP_ROCK]           = TERM_COLOR_BLACK;
    map_bg[MAP_WALL]           = TERM_COLOR_BLUE;
    map_bg[MAP_CORRIDOR]       = TERM_COLOR_BLACK;
    map_bg[MAP_HARD_WALL]  = TERM_COLOR_BLACK;
    map_bg[MAP_MONST]          = TERM_COLOR_BLACK;
    map_bg[MAP_MONST_OR_MOB]   = TERM_COLOR_RED;
    map_bg[MAP_TRAP]           = TERM_COLOR_BLACK;
    map_bg[MAP_TELEPORT]       = TERM_COLOR_BLACK;
    map_bg[MAP_TREASURE]       = TERM_COLOR_YELLOW;
    map_bg[MAP_FOOD]           = TERM_COLOR_BLACK;
    map_bg[MAP_LAVA]           = TERM_COLOR_BLACK;
    map_bg[MAP_ACID]           = TERM_COLOR_BLACK;
    map_bg[MAP_CHASM]          = TERM_COLOR_BLACK;
    map_bg[MAP_EXIT_WEST]      = TERM_COLOR_BLACK;
    map_bg[MAP_EXIT_EAST]      = TERM_COLOR_BLACK;
    map_bg[MAP_EXIT_SOUTH]     = TERM_COLOR_BLACK;
    map_bg[MAP_EXIT_NORTH]     = TERM_COLOR_BLACK;
    map_bg[MAP_END]            = TERM_COLOR_BLACK;
    map_bg[MAP_START]          = TERM_COLOR_BLACK;
    map_bg[MAP_PADDING]        = TERM_COLOR_BLACK;
    map_bg[MAP_DOOR]           = TERM_COLOR_CYAN;
    map_bg[MAP_BRAZIER]        = TERM_COLOR_YELLOW;
    map_bg[MAP_POTION]         = TERM_COLOR_CYAN;
    map_bg[MAP_TRIGGER_HERO]   = TERM_COLOR_BLACK;
    map_bg[MAP_TRIGGER_MONST]  = TERM_COLOR_BLACK;
    map_bg[MAP_ACTION_UP]      = TERM_COLOR_BLACK;
    map_bg[MAP_ACTION_DOWN]    = TERM_COLOR_BLACK;
    map_bg[MAP_ACTION_LEFT]    = TERM_COLOR_BLACK;
    map_bg[MAP_ACTION_RIGHT]   = TERM_COLOR_BLACK;
    map_bg[MAP_ACTION_SLEEP]   = TERM_COLOR_BLACK;
    map_bg[MAP_ACTION_ZAP]     = TERM_COLOR_BLACK;

    valid_frag_char[MAP_EMPTY]          = true;
    valid_frag_char[MAP_SPACE]          = true;
    valid_frag_char[MAP_WATER]          = true;
    valid_frag_char[MAP_FLOOR]          = true;
    valid_frag_char[MAP_SHOPKEEPER]     = true;
    valid_frag_char[MAP_SHOP_FLOOR]     = true;
    valid_frag_char[MAP_ROCK]           = true;
    valid_frag_char[MAP_WALL]           = true;
    valid_frag_char[MAP_CORRIDOR]       = true;
    valid_frag_char[MAP_HARD_WALL]  = false;
    valid_frag_char[MAP_MONST]          = true;
    valid_frag_char[MAP_MONST_OR_MOB]      = true;
    valid_frag_char[MAP_TRAP]           = true;
    valid_frag_char[MAP_TELEPORT]       = true;
    valid_frag_char[MAP_TREASURE]       = true;
    valid_frag_char[MAP_FOOD]           = true;
    valid_frag_char[MAP_ACID]           = true;
    valid_frag_char[MAP_CHASM]          = true;
    valid_frag_char[MAP_EXIT_WEST]      = false;
    valid_frag_char[MAP_EXIT_EAST]      = false;
    valid_frag_char[MAP_EXIT_SOUTH]     = false;
    valid_frag_char[MAP_EXIT_NORTH]     = false;
    valid_frag_char[MAP_END]            = false;
    valid_frag_char[MAP_START]          = false;
    valid_frag_char[MAP_PADDING]        = false;
    valid_frag_char[MAP_DOOR]           = true;
    valid_frag_char[MAP_POTION]         = true;
    valid_frag_char[MAP_WEAPON]         = true;
    valid_frag_char[MAP_GENERATOR]      = true;
    valid_frag_char[MAP_BRAZIER]        = true;

    valid_frag_alt_char[MAP_EMPTY]          = true;
    valid_frag_alt_char[MAP_SPACE]          = false;
    valid_frag_alt_char[MAP_WATER]          = true;
    valid_frag_alt_char[MAP_FLOOR]          = true;
    valid_frag_alt_char[MAP_SHOPKEEPER]     = true;
    valid_frag_alt_char[MAP_SHOP_FLOOR]     = true;
    valid_frag_alt_char[MAP_ROCK]           = true;
    valid_frag_alt_char[MAP_WALL]           = true;
    valid_frag_alt_char[MAP_CORRIDOR]       = true;
    valid_frag_alt_char[MAP_HARD_WALL]  = true;
    valid_frag_alt_char[MAP_MONST]          = true;
    valid_frag_alt_char[MAP_MONST_OR_MOB]   = true;
    valid_frag_alt_char[MAP_TRAP]           = true;
    valid_frag_alt_char[MAP_TELEPORT]       = true;
    valid_frag_alt_char[MAP_TREASURE]       = true;
    valid_frag_alt_char[MAP_FOOD]           = true;
    valid_frag_alt_char[MAP_LAVA]           = true;
    valid_frag_alt_char[MAP_ACID]           = true;
    valid_frag_alt_char[MAP_CHASM]          = true;
    valid_frag_alt_char[MAP_EXIT_WEST]      = false;
    valid_frag_alt_char[MAP_EXIT_EAST]      = false;
    valid_frag_alt_char[MAP_EXIT_SOUTH]     = false;
    valid_frag_alt_char[MAP_EXIT_NORTH]     = false;
    valid_frag_alt_char[MAP_END]            = false;
    valid_frag_alt_char[MAP_START]          = false;
    valid_frag_alt_char[MAP_PADDING]        = false;
    valid_frag_alt_char[MAP_DOOR]           = true;
    valid_frag_alt_char[MAP_POTION]         = true;
    valid_frag_alt_char[MAP_WEAPON]         = true;
    valid_frag_alt_char[MAP_GENERATOR]      = true;
    valid_frag_alt_char[MAP_BRAZIER]        = true;

    memset(map_jigsaw_buffer, 0, sizeof(map_jigsaw_buffer));
    memset(map_jigsaw_buffer_old, 0, sizeof(map_jigsaw_buffer_old));
    memset(map_jigsaw_buffer_fg, 0, sizeof(map_jigsaw_buffer_fg));
    memset(map_jigsaw_buffer_bg, 0, sizeof(map_jigsaw_buffer_bg));
    memset(map_jigsaw_buffer_water_depth, 0, sizeof(map_jigsaw_buffer_water_depth));
    memset(map_jigsaw_buffer_lava_depth, 0, sizeof(map_jigsaw_buffer_lava_depth));
    memset(map_jigsaw_buffer_acid_depth, 0, sizeof(map_jigsaw_buffer_acid_depth));
    memset(map_jigsaw_buffer_chasm_depth, 0, sizeof(map_jigsaw_buffer_chasm_depth));
    memset(map_jigsaw_buffer_action1, 0, sizeof(map_jigsaw_buffer_action1));
    memset(map_jigsaw_buffer_action2, 0, sizeof(map_jigsaw_buffer_action2));
    memset(map_jigsaw_buffer_action3, 0, sizeof(map_jigsaw_buffer_action3));
    memset(map_jigsaw_buffer_color, 0, sizeof(map_jigsaw_buffer_color));
    memset(map_jigsaw_buffer_solved, 0, sizeof(map_jigsaw_buffer_solved));
}

#if 0
static tpp map_char_to_tp (int level,
                           char c,
                           int x,
                           int y,
                           int depth,
                           int shop_floor,
                           tpp *wall,
                           tpp *wall2,
                           tpp *door,
                           tpp *floor,
                           tpp *floor2,
                           tpp *floor3,
                           tpp *rock,
                           tpp *gen)
{
    tpp tp = 0;

    switch (c) {
    case MAP_WALL: 
        if (!*wall) {
            *wall = random_wall();
        }
        tp = *wall;
        break;

    case MAP_HARD_WALL: 
        if (!*wall2) {
            *wall2 = random_hard_wall();
        }
        tp = *wall2;
        break;

    case MAP_ROCK: 
        if (!*rock) {
            *rock = random_rock();
        }
        tp = *rock;
        break;

    case MAP_BRAZIER: 
        tp = tp_find("brazier");
        break;

    case MAP_MONST: 
        tp = random_monst(depth); 

        thing_new(tp_name(tp), level, x, y);

        tp = 0;
        break;

    case MAP_START: 
        /*
         * Find where the stairs from above lead onto this level.
         */
        tp = random_player(); 

        /*
         * If this is the current level, then create the player too.
         */
        if (gp->map.level == level) {
            player = thing_new(tp_name(tp), level, x, y);
        }

        /*
         * No stairs up on the top level.
         */
        if (level == 0) {
            tp = 0;
        } else {
            tp = tp_find("stairs_up");
        }

        break;

    case MAP_END: 
        tp = random_exit(); 
        break;

#if 0
    case MAP_DOOR: 
        if (!*door) {
            *door = random_door();
        }
        tp = *door;
        break;

    case MAP_LAVA:
        tp = random_lava();
        break;

    case MAP_TELEPORT:
        tp = tp_find("teleport1");
        break;

    case MAP_SHOP_FLOOR: 
        tp = tp_find("shop_floor1"); 
        if (level) {
            level_set_has_shop(level, true);
        }
        break;

    case MAP_SHOPKEEPER: 
        tp = tp_find("shopkeeper"); 
        break;

    case MAP_FOOD: 
        tp = random_food(); 
        break;

    case MAP_GENERATOR: 
        if (!*gen) {
            *gen = random_mob(depth); 
        }
        tp = *gen;
        break;

    case MAP_MONST_OR_MOB:
        if ((myrand() % 100) < 20) {
            /*
             * Nothing
             */
        } else if ((myrand() % 100) < 75) {
            tp = random_monst(depth); 
        } else {
            tp = random_mob(depth); 
        }
        break;

    case MAP_TRAP:
        {
            int r = myrand() % 100;

            if (r < 95) {
                tp = random_trap(depth); 
            } else {
                tp = random_lava();
            }
        }
        break;

    case MAP_WEAPON: 
        tp = random_weapon(shop_floor); 
        break;

    case MAP_POTION: 
        tp = random_potion(shop_floor); 
        break;

    case MAP_TREASURE: {
        int r = myrand() % 100;

        if (shop_floor) {
            tp = random_treasure(shop_floor);
        } else {
            if (r < 20) {
                tp = tp_find("brazier");
            } else if (r < 60) {
                tp = random_food();
            } else {
                tp = random_treasure(shop_floor);
            }
        }
        break;

    case MAP_TRIGGER_HERO:
        tp = tp_find("action_trigger_on_hero");
        break;

    case MAP_TRIGGER_MONST:
        tp = tp_find("action_trigger_on_monst");
        break;

    case MAP_ACTION_LEFT:
        tp = tp_find("action_left");
        break;

    case MAP_ACTION_RIGHT:
        tp = tp_find("action_right");
        break;

    case MAP_ACTION_UP:
        tp = tp_find("action_up");
        break;

    case MAP_ACTION_DOWN:
        tp = tp_find("action_down");
        break;

    case MAP_ACTION_SLEEP:
        tp = tp_find("action_sleep");
        break;

    case MAP_ACTION_ZAP:
        tp = tp_find("action_zap");
        break;
#endif

    default:
        break;
    }

    return (tp);
}
#endif

static void dmap_set_walls (dmap *d)
{
    int x, y;

    for (x = 0; x < MAP_WIDTH; x++) {
        for (y = 0; y < MAP_HEIGHT; y++) {

            if (!jigpiece_char_is_occupiable(
                map_jigsaw_buffer_getchar(x, y))) {

                d->val[x][y] = DMAP_IS_WALL;
            } else {
                d->val[x][y] = DMAP_IS_WALL - 1;
            }
        }
    }
}

void dmap_create_water (dungeon_t *dg)
{
    int x, y;

    if ((myrand() % 100) < 10) {
        for (x = 0; x < MAP_WIDTH; x++) {
            for (y = 0; y < MAP_HEIGHT; y++) {
                map_jigsaw_buffer_water_depth[x][y] = -1;
            }
        }
        return;
    }

    dmap d;

    memset(&d, 0, sizeof(d));

    dmap_set_walls(&d);

    int amount = myrand() % 3;

    while (amount--) {
        int x = myrand() % MAP_WIDTH;
        int y = myrand() % MAP_HEIGHT;

        int cluster = 30;
        int cluster_size = 20;
        while (cluster--) {
            int dx = (myrand() % cluster_size) - (cluster_size / 2);
            int dy = (myrand() % cluster_size) - (cluster_size / 2);

            int wx = x + dx;
            int wy = y + dy;

            if (jigpiece_char_is_occupiable(
                map_jigsaw_buffer_getchar(wx, wy))) {

                d.val[wx][wy] = 0;
            }
        }
    }

    dmap_process(&d);

    for (x = 0; x < MAP_WIDTH; x++) {
        for (y = 0; y < MAP_HEIGHT; y++) {
            if (d.val[x][y] < 10) {
                map_jigsaw_buffer_water_depth[x][y] = 10 - d.val[x][y];
            } else {
                map_jigsaw_buffer_water_depth[x][y] = -1;
            }
        }
    }
}

void dmap_create_lava (dungeon_t *dg)
{
    int x, y;

    if ((myrand() % 100) < 80) {
        for (x = 0; x < MAP_WIDTH; x++) {
            for (y = 0; y < MAP_HEIGHT; y++) {
                map_jigsaw_buffer_lava_depth[x][y] = -1;
            }
        }
        return;
    }

    dmap d;

    memset(&d, 0, sizeof(d));

    dmap_set_walls(&d);

    int amount = myrand() % 3;

    while (amount--) {
        int x = myrand() % MAP_WIDTH;
        int y = myrand() % MAP_HEIGHT;

        int cluster = 30;
        int cluster_size = 20;
        while (cluster--) {
            int dx = (myrand() % cluster_size) - (cluster_size / 2);
            int dy = (myrand() % cluster_size) - (cluster_size / 2);

            int wx = x + dx;
            int wy = y + dy;

            if (jigpiece_char_is_occupiable(
                map_jigsaw_buffer_getchar(wx, wy))) {

                d.val[wx][wy] = 0;
            }
        }
    }

    dmap_process(&d);

    for (x = 0; x < MAP_WIDTH; x++) {
        for (y = 0; y < MAP_HEIGHT; y++) {
            if (d.val[x][y] < 10) {
                map_jigsaw_buffer_lava_depth[x][y] = 10 - d.val[x][y];
            } else {
                map_jigsaw_buffer_lava_depth[x][y] = -1;
            }
        }
    }
}

void dmap_create_acid (dungeon_t *dg)
{
    int x, y;

    if ((myrand() % 100) < 90) {
        for (x = 0; x < MAP_WIDTH; x++) {
            for (y = 0; y < MAP_HEIGHT; y++) {
                map_jigsaw_buffer_acid_depth[x][y] = -1;
            }
        }
        return;
    }

    dmap d;

    memset(&d, 0, sizeof(d));

    dmap_set_walls(&d);

    int amount = myrand() % 3;

    while (amount--) {
        int x = myrand() % MAP_WIDTH;
        int y = myrand() % MAP_HEIGHT;

        int cluster = 30;
        int cluster_size = 20;
        while (cluster--) {
            int dx = (myrand() % cluster_size) - (cluster_size / 2);
            int dy = (myrand() % cluster_size) - (cluster_size / 2);

            int wx = x + dx;
            int wy = y + dy;

            if (jigpiece_char_is_occupiable(
                map_jigsaw_buffer_getchar(wx, wy))) {

                d.val[wx][wy] = 0;
            }
        }
    }

    dmap_process(&d);

    for (x = 0; x < MAP_WIDTH; x++) {
        for (y = 0; y < MAP_HEIGHT; y++) {
            if (d.val[x][y] < 10) {
                map_jigsaw_buffer_acid_depth[x][y] = 10 - d.val[x][y];
            } else {
                map_jigsaw_buffer_acid_depth[x][y] = -1;
            }
        }
    }
}

void dmap_create_chasm (dungeon_t *dg)
{
    int x, y;

    if ((myrand() % 100) < 90) {
        for (x = 0; x < MAP_WIDTH; x++) {
            for (y = 0; y < MAP_HEIGHT; y++) {
                map_jigsaw_buffer_chasm_depth[x][y] = -1;
            }
        }
        return;
    }

    dmap d;

    memset(&d, 0, sizeof(d));

    dmap_set_walls(&d);

    int amount = myrand() % 3;

    while (amount--) {
        int x = myrand() % MAP_WIDTH;
        int y = myrand() % MAP_HEIGHT;

        int cluster = 30;
        int cluster_size = 20;
        while (cluster--) {
            int dx = (myrand() % cluster_size) - (cluster_size / 2);
            int dy = (myrand() % cluster_size) - (cluster_size / 2);

            int wx = x + dx;
            int wy = y + dy;

            if (jigpiece_char_is_occupiable(
                map_jigsaw_buffer_getchar(wx, wy))) {

                d.val[wx][wy] = 0;
            }
        }
    }

    dmap_process(&d);

    for (x = 0; x < MAP_WIDTH; x++) {
        for (y = 0; y < MAP_HEIGHT; y++) {
            if (d.val[x][y] < 10) {
                map_jigsaw_buffer_chasm_depth[x][y] = 10 - d.val[x][y];
            } else {
                map_jigsaw_buffer_chasm_depth[x][y] = -1;
            }
        }
    }
}

#if 0
/*
 * map_jigsaw_generate
 */
void map_jigsaw_generate (int level)
{
    static tpp map_tp[MAP_WIDTH][MAP_HEIGHT][MAP_DEPTH];
    static thing_template_data map_tp_data[MAP_WIDTH][MAP_HEIGHT][MAP_DEPTH];
    static tpp map_tp_action1[MAP_WIDTH][MAP_HEIGHT];
    static tpp map_tp_action2[MAP_WIDTH][MAP_HEIGHT];
    static tpp map_tp_action3[MAP_WIDTH][MAP_HEIGHT];
    int got_start = 0;
    int got_end = 0;
    int x, y, z;

    memset(map_tp, 0, sizeof(map_tp));
    memset(map_tp_data, 0, sizeof(map_tp_data));
    memset(map_tp_action1, 0, sizeof(map_tp_action1));
    memset(map_tp_action2, 0, sizeof(map_tp_action2));
    memset(map_tp_action3, 0, sizeof(map_tp_action3));

    map_init();

    map_init_level(level);

    if (gp->map.seed) {
        maze_seed = gp->map.seed;
    } else {
        maze_seed = myrand() % 1000;
    }

    maze_seed += level * 1001;

    dungeon_t *dg;
    dg = (typeof(dg)) myzalloc(sizeof(*dg), __FUNCTION__);

    static frag_t *frag_main;
    static frag_t *frag_room_corners;
    static frag_t *frag_outside_rooms;
    static frag_t *frag_outside_junk;
    static frag_t *frag_monst;

    if (!frag_main) {
        frag_main = generate_fragmap("data/map/jigsaw.map");
    }

    if (!frag_room_corners) {
        frag_room_corners = generate_fragmap("data/map/room_corners.map");
    }

    if (!frag_outside_rooms) {
        frag_outside_rooms = generate_fragmap("data/map/outside_rooms.map");
    }

    if (!frag_outside_junk) {
        frag_outside_junk = generate_fragmap("data/map/outside_junk.map");
    }

    if (!frag_monst) {
        frag_monst = generate_fragmap("data/map/monst.map");
    }

    for (;;) {
        memset(dg, 0, sizeof(*dg));
        dg->level = level;

        mysrand(maze_seed);

        LOG("Maze: level %u, seed %u", level, maze_seed);

        if (!generate_level(dg, frag_main)) {                      
            continue;
        }

        if (!generate_add_frags(dg, frag_room_corners,
                                20 + (level * 20), // repeat count
                                100         // chance to place fragment
                                )) {
            maze_seed++;
            continue;
        }

        maze_add_borders_around_rooms_and_corridors();

        if (!generate_add_frags(dg, frag_outside_rooms,
                                1,     // repeat count
                                level  // chance to place fragment
                                )) {
            maze_seed++;
            continue;
        }

        if (!generate_add_frags(dg, frag_room_corners,
                                level, // repeat count
                                100         // chance to place fragment
                                )) {
            maze_seed++;
            continue;
        }

        maze_add_borders_around_rooms_and_corridors();

        if (!generate_add_frags(dg, frag_outside_junk,
                                1,     // repeat count
                                level  // chance to place fragment
                                )) {
            maze_seed++;
            continue;
        }

        if (!generate_add_frags(dg, frag_monst,
                                100, // repeat count
                                1000// chance to place fragment
                                )) {
            maze_seed++;
            continue;
        }

        maze_add_final_borders();

        maze_add_random_junk();

        dmap_create_water(dg);
        dmap_create_lava(dg);
        dmap_create_acid(dg);
        dmap_create_chasm(dg);

        if (!finalize_level(dg)) {
            maze_seed++;
            continue;
        }

        break;
    }

    tpp wall = 0;
    tpp wall2 = 0;
    tpp door = 0;
    tpp floor = 0;
    tpp floor2 = 0;
    tpp floor3 = 0;
    tpp rock = 0;
    tpp gen = 0;

    for (y = 0; y < MAP_HEIGHT; y++) {
        for (x = 0; x < MAP_WIDTH; x++) {
            tpp tp;

            char c = map_jigsaw_buffer[x][y];

            /*
             * Items in shops go on shop floors
             */
            int shop_floor = false;
            if ((x > 0) && (x < MAP_WIDTH - 1) && (y > 0) && (y < MAP_HEIGHT - 1)) {
                shop_floor  = (map_jigsaw_buffer[x][y] == '_') ? 1 : 0;
                shop_floor |= (map_jigsaw_buffer[x-1][y] == '_') ? 1 : 0;
                shop_floor |= (map_jigsaw_buffer[x+1][y] == '_') ? 1 : 0;
                shop_floor |= (map_jigsaw_buffer[x][y-1] == '_') ? 1 : 0;
                shop_floor |= (map_jigsaw_buffer[x][y+1] == '_') ? 1 : 0;
            }

            int corridor_floor = false;
            if ((x > 0) && (x < MAP_WIDTH - 1) && (y > 0) && (y < MAP_HEIGHT - 1)) {
                corridor_floor  = (map_jigsaw_buffer[x][y] == ',') ? 1 : 0;
                corridor_floor |= (map_jigsaw_buffer[x-1][y] == ',') ? 1 : 0;
                corridor_floor |= (map_jigsaw_buffer[x+1][y] == ',') ? 1 : 0;
                corridor_floor |= (map_jigsaw_buffer[x][y-1] == ',') ? 1 : 0;
                corridor_floor |= (map_jigsaw_buffer[x][y+1] == ',') ? 1 : 0;
            }

            int dirt_floor = false;
            if ((x > 0) && (x < MAP_WIDTH - 1) && (y > 0) && (y < MAP_HEIGHT - 1)) {
                dirt_floor  = (map_jigsaw_buffer[x][y] == ' ') ? 1 : 0;
                dirt_floor |= (map_jigsaw_buffer[x-1][y] == ' ') ? 1 : 0;
                dirt_floor |= (map_jigsaw_buffer[x+1][y] == ' ') ? 1 : 0;
                dirt_floor |= (map_jigsaw_buffer[x][y-1] == ' ') ? 1 : 0;
                dirt_floor |= (map_jigsaw_buffer[x][y+1] == ' ') ? 1 : 0;
            }

            int room_floor = false;
            if ((x > 0) && (x < MAP_WIDTH - 1) && (y > 0) && (y < MAP_HEIGHT - 1)) {
                room_floor  = (map_jigsaw_buffer[x][y] == '.') ? 1 : 0;
                room_floor |= (map_jigsaw_buffer[x-1][y] == '.') ? 1 : 0;
                room_floor |= (map_jigsaw_buffer[x+1][y] == '.') ? 1 : 0;
                room_floor |= (map_jigsaw_buffer[x][y-1] == '.') ? 1 : 0;
                room_floor |= (map_jigsaw_buffer[x][y+1] == '.') ? 1 : 0;
            }

            if (!floor) {
                floor = random_floor();
            }

            tp = floor;

            if (shop_floor) {
                tp = tp_find("shop_floor1");
            }

            if ((c == ',') || corridor_floor) {
                if (!floor2) {
                    floor2 = random_corridor();
                }

                tp = floor2;
            }

            if (dirt_floor) {
                if (!floor3) {
                    floor3 = random_dirt();
                }

                tp = floor3;
            }

            map_put_tp(level, x, y, tp, 0);

            tp = map_char_to_tp(level,
                                c, 
                                x, y,
                                level,
                                shop_floor,
                                &wall, &wall2, &door, 
                                &floor, &floor2, &floor3, 
                                &rock, 
                                &gen);

            if (tp) {
                map_put_tp(level, x, y, tp, 0);
            }

            if (map_jigsaw_buffer_water_depth[x][y] == -1) {
                // land
            } else if (map_jigsaw_buffer_water_depth[x][y] <= 1) {
                map_put_tp(level, x, y, id_to_tp(THING_WATER1), 0);
            } else if (map_jigsaw_buffer_water_depth[x][y] <= 2) {
                map_put_tp(level, x, y, id_to_tp(THING_WATER2), 0);
            } else if (map_jigsaw_buffer_water_depth[x][y] < 6) {
                map_put_tp(level, x, y, id_to_tp(THING_WATER3), 0);
            } else if (map_jigsaw_buffer_water_depth[x][y] <= 10) {
                map_put_tp(level, x, y, id_to_tp(THING_WATER4), 0);
            }

            if (map_jigsaw_buffer_lava_depth[x][y] == -1) {
                // land
            } else if (map_jigsaw_buffer_lava_depth[x][y] <= 1) {
                map_put_tp(level, x, y, id_to_tp(THING_LAVA1), 0);
            } else if (map_jigsaw_buffer_lava_depth[x][y] <= 2) {
                map_put_tp(level, x, y, id_to_tp(THING_LAVA2), 0);
            } else if (map_jigsaw_buffer_lava_depth[x][y] < 6) {
                map_put_tp(level, x, y, id_to_tp(THING_LAVA3), 0);
            } else if (map_jigsaw_buffer_lava_depth[x][y] <= 10) {
                map_put_tp(level, x, y, id_to_tp(THING_LAVA4), 0);
            }

            if (map_jigsaw_buffer_acid_depth[x][y] == -1) {
                // land
            } else if (map_jigsaw_buffer_acid_depth[x][y] <= 1) {
                map_put_tp(level, x, y, id_to_tp(THING_ACID1), 0);
            } else if (map_jigsaw_buffer_acid_depth[x][y] <= 2) {
                map_put_tp(level, x, y, id_to_tp(THING_ACID2), 0);
            } else if (map_jigsaw_buffer_acid_depth[x][y] < 6) {
                map_put_tp(level, x, y, id_to_tp(THING_ACID3), 0);
            } else if (map_jigsaw_buffer_acid_depth[x][y] <= 10) {
                map_put_tp(level, x, y, id_to_tp(THING_ACID4), 0);
            }

            if (map_jigsaw_buffer_chasm_depth[x][y] == -1) {
                // land
            } else {
                while (map_remove_top_tp(level, x, y)) {
                }
            }

            /*
             * Make sure nothing overlaps players
             */
            if (c == MAP_START) {
                got_start = 1;
                continue;
            }

            /*
             * Or exits
             */
            if (c == MAP_END) {
                got_end = 1;
                continue;
            }

            if (tp) {
                switch (c) {
                case MAP_TRIGGER_HERO:
                case MAP_TRIGGER_MONST:
                    {
                        const char *col_name = map_jigsaw_buffer_color[x][y];
                        map_tp_data[x][y][tp_get_z_depth(tp)].col_name = col_name;
                        map_tp_data[x][y][tp_get_z_depth(tp)].col = color_find(col_name);
                        break;
                    } 
                }
            }

            c = map_jigsaw_buffer_action1[x][y];
            if (c) {
                tp = map_char_to_tp(level,
                                    c, 
                                    x, y,
                                    level,
                                    shop_floor,
                                    &wall, &wall2, &door, 
                                    &floor, &floor2, &floor3,
                                    &rock, &gen);

                map_tp_action1[x][y] = tp;
            }

            c = map_jigsaw_buffer_action2[x][y];
            if (c) {
                tp = map_char_to_tp(level,
                                    c, 
                                    x, y,
                                    level,
                                    shop_floor,
                                    &wall, &wall2, &door, 
                                    &floor, &floor2, &floor3,
                                    &rock, &gen);

                map_tp_action2[x][y] = tp;
            }

            c = map_jigsaw_buffer_action3[x][y];
            if (c) {
                tp = map_char_to_tp(level,
                                    c, 
                                    x, y,
                                    level,
                                    shop_floor,
                                    &wall, &wall2, &door, 
                                    &floor, &floor2, &floor3,
                                    &rock, &gen);

                map_tp_action3[x][y] = tp;
            }
        }
    }

    int pass;
    int max_pass = 2;

    for (pass = 0; pass < max_pass; pass++) {
        for (y = 0; y < MAP_HEIGHT; y++) {
            for (x = 0; x < MAP_WIDTH; x++) {
                for (z = 0; z < MAP_DEPTH; z++) {
                    tpp tp = map_tp[x][y][z];
                    if (tp) {
                        tpp_data tp_data = &map_tp_data[x][y][tp_get_z_depth(tp)];

                        map_put_tp(level, x, y, tp, tp_data);
                    }
                }

                {
                    tpp tp;

                    thing_template_data tp_data;

                    memset(&tp_data, 0, sizeof(tp_data));

                    const char *col_name = map_jigsaw_buffer_color[x][y];
                    if (!col_name) {
                        continue;
                    }

                    tp_data.col_name = col_name;
                    tp_data.col = color_find(col_name);

                    tp = map_tp_action1[x][y];
                    if (tp) {
                        map_put_tp(level, x, y, tp, &tp_data);
                    }

                    tp = map_tp_action2[x][y];
                    if (tp) {
//CON("%d %d %s %s",x, y, col_name,tp_name(tp));
                        map_put_tp(level, x, y, tp, &tp_data);
                    }

                    tp = map_tp_action3[x][y];
                    if (tp) {
                        map_put_tp(level, x, y, tp, &tp_data);
                    }
                }
            }
        }
    }

    if (!got_start) {
        ERR("I made a level with no start!");
    }

    if (!got_end) {
        ERR("I made a level with no exit!");
    }
}
#endif
