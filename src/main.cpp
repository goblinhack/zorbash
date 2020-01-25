//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#define __MAIN__

#include <libgen.h> // dirname
#include <signal.h>

#include "my_main.h"
#include "my_python.h"
#include "my_gl.h"
#include "my_wid_console.h"
#include "my_wid_minicon.h"
#include "my_wid_test.h"
#include "my_font.h"
#include "my_dir.h"
#include "my_file.h"
#include "my_charmap.h"
#include "my_game.h"
#include "my_room.h"
#include "my_level.h"
#include "my_traceback.h"
#include "my_ascii.h"

#include <random>       // std::default_random_engine
std::default_random_engine rng;
extern bool game_needs_restart;

static char **ARGV;
char *EXEC_FULL_PATH_AND_NAME;
char *EXEC_DIR;
char *DATA_PATH;
char *WORLD_PATH;
char *PYTHON_PATH;
char *TTF_PATH;
char *GFX_PATH;
static bool opt_new_game;
static bool opt_debug_mode;
static bool opt_arcade_mode;
static bool opt_arcade_mode_set;

FILE *LOG_STDOUT;
FILE *LOG_STDERR;

uint8_t quitting;

void callstack_dump (void)
{_
    fprintf(MY_STDERR, "code trace:\n");
    fprintf(MY_STDERR, "==========:\n");
    for (auto depth = 0; depth < callframes_depth; depth++) {
        auto iter = &callframes[depth];
        fprintf(MY_STDERR, "(stack) %d %s %s, line %u\n", depth, iter->file, iter->func, iter->line);
    }
}

#ifdef ENABLE_CRASH_HANDLER
static void segv_handler (int sig)
{_
    static int crashed;

    if (crashed) {
        fprintf(MY_STDERR, "Nested crash!!!");
        exit(1);
    }

    crashed = 1;
    fprintf(MY_STDERR, "Crash!!!");
    DIE("Crashed");
}

static void ctrlc_handler (int sig)
{_
    fprintf(MY_STDERR, "Interrupted!!!");
    DIE("Interrupted");
}
#endif

void quit (void)
{_
    if (croaked) {
        return;
    }

    if (quitting) {
        return;
    }

    quitting = true;

#ifdef ENABLE_CRASH_HANDLER
    signal(SIGSEGV, 0);   // uninstall our handler
    signal(SIGABRT, 0);   // uninstall our handler
    signal(SIGINT, 0);    // uninstall our handler
#endif

    if (game) {
        game->fini();
    }

    LOG("FINI: room_fini");
    room_fini();

    LOG("FINI: level_fini");
    level_fini();

    LOG("FINI: python_fini");
    python_fini();

    LOG("FINI: sdl_exit");
    sdl_exit();

    LOG("FINI: tp_fini");
    tp_fini();

    LOG("FINI: wid_console_fini");
    wid_console_fini();

    LOG("FINI: wid_minicon_fini");
    wid_minicon_fini();

    LOG("FINI: wid_test_fini");
    wid_test_fini();

    LOG("FINI: command_fini");
    command_fini();

    LOG("FINI: wid_fini");
    wid_fini();

    LOG("FINI: font_fini");
    font_fini();

    LOG("FINI: tex_fini");
    tex_fini();

    LOG("FINI: wid_tiles_fini");
    wid_tiles_fini();

    LOG("FINI: tile_fini");
    tile_fini();

    LOG("FINI: sdl_fini");
    sdl_fini();

    LOG("FINI: blit_fini");
    blit_fini();

    LOG("FINI: color_fini");
    color_fini();

    if (EXEC_FULL_PATH_AND_NAME) {
        myfree(EXEC_FULL_PATH_AND_NAME);
        EXEC_FULL_PATH_AND_NAME = 0;
    }

    if (DATA_PATH) {
        myfree(DATA_PATH);
        DATA_PATH = 0;
    }

    if (PYTHON_PATH) {
        myfree(PYTHON_PATH);
        PYTHON_PATH = 0;
    }

    if (WORLD_PATH) {
        myfree(WORLD_PATH);
        WORLD_PATH = 0;
    }

    if (TTF_PATH) {
        myfree(TTF_PATH);
        TTF_PATH = 0;
    }

    if (GFX_PATH) {
        myfree(GFX_PATH);
        GFX_PATH = 0;
    }

    if (EXEC_DIR) {
        myfree(EXEC_DIR);
        EXEC_DIR = 0;
    }

#ifdef ENABLE_PTRCHECK_LEAK
    if (!croaked) {
        ptrcheck_leak_print();
    }
#endif
}

void restart (void)
{_
    char *args[] = { 0, 0 };
    char *executable = ARGV[0];

    LOG("Run %s", executable);

    args[0] = executable;

    execve(executable, (char *const *) args, 0);
}

void die (void)
{_
    // quit();

    LOG("Bye, error exit");
    fprintf(MY_STDERR, "exit(1) error\n");

    exit(1);
}

//
// Find the binary we are running.
//
static void find_executable (void)
{_
    char *parent_dir = 0;
    char *curr_dir = 0;
    std::string exec_name = "";
    char *exec_expanded_name = 0;
    char *path = 0;
    char *tmp;

    exec_name = mybasename(ARGV[0], __FUNCTION__);

    //
    // Get the current directory, ending in a single /
    //
    curr_dir = dynprintf("%s" DSEP, dir_dot());
    tmp = strsub(curr_dir, DSEP DSEP, DSEP, "curr_dir");
    myfree(curr_dir);
    curr_dir = tmp;

    //
    // Get the parent directory, ending in a single /
    //
    parent_dir = dynprintf("%s" DSEP, dir_dotdot(dir_dot()));
    tmp = strsub(parent_dir, DSEP DSEP, DSEP, "parent_dir");
    myfree(parent_dir);
    parent_dir = tmp;

    //
    // Get rid of ../ from the program name and replace with the path.
    //
    exec_expanded_name = dupstr(ARGV[0], __FUNCTION__);
    if (*exec_expanded_name == '.') {
        tmp = strsub(exec_expanded_name, ".." DSEP, parent_dir, "exec_expanded_name");
        myfree(exec_expanded_name);
        exec_expanded_name = tmp;
    }

    //
    // Get rid of ./ from the program name.
    //
    if (*exec_expanded_name == '.') {
        tmp = strsub(exec_expanded_name, "." DSEP, "", "exec_expanded_name2");
        myfree(exec_expanded_name);
        exec_expanded_name = tmp;
    }

    //
    // Get rid of any // from th path
    //
    tmp = strsub(exec_expanded_name, DSEP DSEP, DSEP, "exec_expanded_name3");
    myfree(exec_expanded_name);
    exec_expanded_name = tmp;

    //
    // Look in the simplest case first.
    //
    EXEC_FULL_PATH_AND_NAME = dynprintf("%s%s", curr_dir, exec_name.c_str());
    if (file_exists(EXEC_FULL_PATH_AND_NAME)) {
        EXEC_DIR = dupstr(curr_dir, "exec dir 1");
        goto cleanup;
    }

    myfree(EXEC_FULL_PATH_AND_NAME);

    //
    // Try the parent dir.
    //
    EXEC_FULL_PATH_AND_NAME = dynprintf("%s%s", parent_dir, exec_name.c_str());
    if (file_exists(EXEC_FULL_PATH_AND_NAME)) {
        EXEC_DIR = dupstr(parent_dir, "exec dir 2");
        goto cleanup;
    }

    myfree(EXEC_FULL_PATH_AND_NAME);

    //
    // Try the PATH.
    //
    path = getenv("PATH");
    if (path) {
        char *dir = 0;

        path = dupstr(path, "path");

        for (dir = strtok(path, ":"); dir; dir = strtok(0, ":")) {
            EXEC_FULL_PATH_AND_NAME = dynprintf("%s" DSEP "%s", dir, exec_name.c_str());
            if (file_exists(EXEC_FULL_PATH_AND_NAME)) {
                EXEC_DIR = dynprintf("%s" DSEP, dir);
                goto cleanup;
            }

            myfree(EXEC_FULL_PATH_AND_NAME);
        }

        myfree(path);
        path = 0;
    }

    EXEC_FULL_PATH_AND_NAME = dupstr(exec_expanded_name, "full path");
    EXEC_DIR = dupstr(dirname(exec_expanded_name), "exec dir");

cleanup:
    DBG("Exec name   : \"%s\"", exec_name.c_str());
    DBG("Parent dir  : \"%s\"", parent_dir);
    DBG("Curr dir    : \"%s\"", curr_dir);
    DBG("Full name   : \"%s\"", exec_expanded_name);

    if (path) {
        myfree(path);
    }

    if (exec_expanded_name) {
        myfree(exec_expanded_name);
    }

    if (parent_dir) {
        myfree(parent_dir);
    }

    if (curr_dir) {
        myfree(curr_dir);
    }
}

//
// Find all installed file locations.
//
static void find_exec_dir (void)
{_
    find_executable();

    //
    // Make sure the exec dir ends in a /
    //
    auto tmp = dynprintf("%s" DSEP, EXEC_DIR);
    auto tmp2 = strsub(tmp, DSEP DSEP, DSEP, "EXEC_DIR");
    myfree(tmp);
    if (EXEC_DIR) {
        myfree(EXEC_DIR);
    }
    EXEC_DIR = tmp2;
}

//
// Hunt down the data/ dir.
//
static void find_data_dir (void)
{_
    DATA_PATH = dynprintf("%sdata" DSEP, EXEC_DIR);
    if (dir_exists(DATA_PATH)) {
        return;
    }

    myfree(DATA_PATH);

    DATA_PATH = dupstr(EXEC_DIR, __FUNCTION__);
}

//
// Hunt down the python/ dir.
//
static void find_python_dir (void)
{_
    PYTHON_PATH = dynprintf("%spython" DSEP, EXEC_DIR);
    if (dir_exists(PYTHON_PATH)) {
        return;
    }

    myfree(PYTHON_PATH);

    PYTHON_PATH = dupstr(EXEC_DIR, __FUNCTION__);
}

//
// Hunt down the world/ dir.
//
static void find_world_dir (void)
{_
    WORLD_PATH = dynprintf("%sdata" DSEP "world" DSEP, EXEC_DIR);
    if (dir_exists(WORLD_PATH)) {
        return;
    }

    myfree(WORLD_PATH);

    WORLD_PATH = dupstr(EXEC_DIR, __FUNCTION__);
}

//
// Hunt down the ttf/ dir.
//
static void find_ttf_dir (void)
{_
    TTF_PATH = dynprintf("%sdata" DSEP "ttf" DSEP, EXEC_DIR);
    if (dir_exists(TTF_PATH)) {
        return;
    }

    myfree(TTF_PATH);

    TTF_PATH = dupstr(EXEC_DIR, __FUNCTION__);
}

//
// Hunt down the gfx/ dir.
//
static void find_gfx_dir (void)
{_
    GFX_PATH = dynprintf("%sdata" DSEP "gfx" DSEP, EXEC_DIR);
    if (dir_exists(GFX_PATH)) {
        return;
    }

    myfree(GFX_PATH);

    GFX_PATH = dupstr(EXEC_DIR, __FUNCTION__);
}

//
// Find all installed file locations.
//
static void find_file_locations (void)
{_
    find_exec_dir();
    find_data_dir();
    find_python_dir();
    find_world_dir();
    find_ttf_dir();
    find_gfx_dir();

    DBG("Gfx path    : \"%s\"", GFX_PATH);
    DBG("Font path   : \"%s\"", TTF_PATH);
}

static void usage (void)
{_
    static int whinged;

    if (whinged) {
        return;
    }
    whinged = true;

    CON("zorbash, options:");
    CON(" ");
    CON("Written by goblinhack@gmail.com");
}

static void parse_args (int32_t argc, char *argv[])
{_
    int32_t i;

    CON("Greetings mortal");

    //
    // Parse format args
    //
    CON("Program name: \"%s\"", argv[0]);
    for (i = 1; i < argc; i++) {
        CON("  arg: \"%s\"", argv[i]);
    }

    for (i = 1; i < argc; i++) {
        //
        // Bad argument.
        //
        if (!strcasecmp(argv[i], "--new-game") ||
            !strcasecmp(argv[i], "-new-game")) {
            opt_new_game = true;
            continue;
        }

        if (!strcasecmp(argv[i], "--debug-mode") ||
            !strcasecmp(argv[i], "-debug-mode")) {
            opt_debug_mode = true;
            continue;
        }

        if (!strcasecmp(argv[i], "--arcade-mode") ||
            !strcasecmp(argv[i], "-arcade-mode")) {
            opt_arcade_mode = true;
            opt_arcade_mode_set = true;
            continue;
        }

        if (!strcasecmp(argv[i], "--rogue-mode") ||
            !strcasecmp(argv[i], "-rogue-mode")) {
            opt_arcade_mode = false;
            opt_arcade_mode_set = true;
            continue;
        }

        //
        // Bad argument.
        //
        if (argv[i][0] == '-') {
            usage();
            WARN("unknown format argument, %s", argv[i]);
            continue;
        }

        usage();
        WARN("unknown format argument, %s", argv[i]);
    }
}

int32_t main (int32_t argc, char *argv[])
{_
    CON("INIT: _WIN32");
#ifdef _WIN32
    CON("INIT: _WIN32");
#endif
#ifdef __MINGW32__
    CON("INIT: __MINGW32__");
#endif
#ifdef __MINGW64__
    CON("INIT: __MINGW64__");
#endif
#ifdef __APPLE__
    CON("INIT: __APPLE__");
#endif
#ifdef __linux__
    CON("INIT: __linux__");
#endif

    LOG("INIT: ascii");
    ascii_init();

    //
    // Need this to get the UTF on the console
    //
#ifndef _WIN32
    CON("INIT: locale");
    std::locale loc("");
    std::ios_base::sync_with_stdio(false);
    std::wcout.imbue(loc);
#endif

    //
    // Random numbers
    //
    LOG("INIT: random number generators");
    double mean = 1.0;
    double std = 0.5;
    std::normal_distribution<double> distribution;
    distribution.param(std::normal_distribution<double>(mean, std).param());
    rng.seed(std::random_device{}());
    mysrand(time(0));

#ifdef ENABLE_CRASH_HANDLER
    LOG("INIT: crash handlers");
    signal(SIGSEGV, segv_handler);   // install our handler
    signal(SIGABRT, segv_handler);   // install our handler
    signal(SIGINT, ctrlc_handler);   // install our handler
#endif

    LOG("INIT: set APPDATA location");
    const char *appdata;
    appdata = getenv("APPDATA");
    if (!appdata || !appdata[0]) {
        appdata = "appdata";
    }

#ifdef _WIN32
    mkdir(appdata);
#else
    mkdir(appdata, 0700);
#endif

    char *dir = dynprintf("%s%s%s", appdata, DSEP, "zorbash");
#ifdef _WIN32
    mkdir(dir);
#else
    mkdir(dir, 0700);
#endif
    LOG("INIT: APPDATA %s", dir);
    myfree(dir);

    char *out = dynprintf("%s%s%s%s%s", appdata, DSEP, "zorbash", DSEP, "stdout.txt");
    LOG("INIT: STDOUT %s", out);
    LOG_STDOUT = fopen(out, "w+");
    myfree(out);

    char *err = dynprintf("%s%s%s%s%s", appdata, DSEP, "zorbash", DSEP, "stderr.txt");
    LOG("INIT: STDERR %s", out);
    LOG_STDERR = fopen(err, "w+");
    myfree(err);

    ARGV = argv;
    //dospath2unix(ARGV[0]);
    //LOG("Set unix path to %s", ARGV[0]);

    CON("INIT: arguments");
    parse_args(argc, argv);

    CON("INIT: colors");
    color_init();

    CON("INIT: resource locations");
    find_file_locations();

    CON("INIT: charmaps");
    Charmap::init_charmaps();

    CON("INIT: python");
    python_init(argv);

#if 0
    extern int grid_test(void);
    grid_test();
    int x = 1;
    if (x) {
    DIE("x");
    }
#endif

#if 0
    extern int dungeon_test(void);
    dungeon_test();

    auto y = 1;
    if (y) {
    DIE("x");
    }
#endif

    //
    // Create and load the last saved game
    //
    CON("INIT: load game config");
    game = new Game(std::string(appdata));
    game->load_config();

    if (opt_debug_mode) {
        game->config.debug_mode = opt_debug_mode;
    }

    if (opt_arcade_mode_set) {
        game->config.arcade_mode = opt_arcade_mode;
    }

    CON("INIT: SDL");
    if (!sdl_init()) {
        ERR("SDL init");
    }

    CON("INIT: OpenGL 2D mode");
    gl_init_2d_mode();

    CON("INIT: textures");
    if (!tex_init()) {
        ERR("tex init");
    }

    CON("INIT: UI tiles");
    if (!wid_tiles_init()) {
        ERR("wid tiles init");
    }

    CON("INIT: tiles");
    if (!tile_init()) {
        ERR("tile init");
    }

    CON("INIT: fonts");
    if (!font_init()) {
        ERR("Font init");
    }

    CON("INIT: UI");
    if (!wid_init()) {
        ERR("wid init");
    }

    py_call_void("init2");

    CON("INIT: UI console");
    if (!wid_console_init()) {
        ERR("wid_console init");
    }

    CON("INIT: UI minicon");
    if (!wid_minicon_init()) {
        ERR("wid_minicon init");
    }

    CON("INIT: UI commands");
    if (!command_init()) {
        ERR("command init");
    }

    CON("INIT: thing templates");
    tp_init();

    //
    // Create a fresh game if none was loaded
    //
    CON("INIT: rooms");
    room_init();
#if 0
    game->init();
    game->load();
    game->init();
    game->fini();
    game->init();
    game->fini();
    game->init();
    game->save();
    game->fini();
    game->load();
#endif

#if 0
    if (!wid_test_init()) {
        ERR("wid_test init");
    }
#endif

    CON("Clear minicon");
    wid_minicon_flush();
    if (opt_new_game) {
        CON("Goto new game");
        game->new_game();
    } else {
        CON("Goto game menu");
        game->main_menu_select();
    }

    sdl_loop();

    CON("Leave 2D mode");
    gl_leave_2d_mode();

    CON("Quit");
    quit();

    LOG("Goodbye cruel world");

    if (game_needs_restart) {
        game_needs_restart = false;
        execv(argv[0], argv);
    }
    return (0);
}
