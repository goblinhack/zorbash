//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#define __MAIN__

#include <strings.h> // do not remove
#include <string.h> // do not remove
#include <time.h> // do not remove
#include <unistd.h> // do not remove
#include <libgen.h> // dirname
#include <signal.h> // dirname
#include <random>  // std::default_random_engine
std::default_random_engine rng;

#include "my_sys.h"
#include "my_main.h"
#include "my_game.h"
#include "my_music.h"
#include "my_audio.h"
#include "my_sound.h"
#include "my_thing_template.h"
#include "my_python.h"
#include "my_gl.h"
#include "my_wid_console.h"
#include "my_wid_topcon.h"
#include "my_wid_botcon.h"
#include "my_wid_actionbar.h"
#include "my_font.h"
#include "my_dir.h"
#include "my_file.h"
#include "my_room.h"
#include "my_level_static.h"
#include "my_gfx.h"
#include "my_random_name.h"
#include "my_random.h"
#include "my_globals.h"
#include "my_ptrcheck.h"
#include "my_string.h"
#include "my_sdl.h"
#include "my_ramdisk.h"

static char **ARGV;

void quit (void)
{_
    LOG("FINI: Quitting, start cleanup");

    if (g_die_occurred) {
        return;
    }

    if (g_quitting) {
        return;
    }

    g_quitting = true;

#ifdef ENABLE_CRASH_HANDLER
    signal(SIGSEGV, 0);   // uninstall our handler
    signal(SIGABRT, 0);   // uninstall our handler
    signal(SIGINT, 0);    // uninstall our handler
    signal(SIGPIPE, 0);   // uninstall our handler
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

    LOG("FINI: wid_topcon_fini");
    wid_topcon_fini();

    LOG("FINI: wid_botcon_fini");
    wid_botcon_fini();

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

    LOG("FINI: audio_fini");
    audio_fini();

    LOG("FINI: music_fini");
    music_fini();

    LOG("FINI: sound_fini");
    sound_fini();

    if (EXEC_FULL_PATH_AND_NAME) {
        myfree(EXEC_FULL_PATH_AND_NAME);
        EXEC_FULL_PATH_AND_NAME = 0;
    }

    if (DATA_PATH) {
        myfree(DATA_PATH);
        DATA_PATH = 0;
    }

    if (EXEC_PYTHONPATH) {
        myfree(EXEC_PYTHONPATH);
        EXEC_PYTHONPATH = 0;
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

#ifdef ENABLE_DEBUG_MEM_LEAKS
    if (!g_die_occurred) {
        ptrcheck_leak_print();
    }
#endif
    LOG("FINI: Clenup done");
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
    CON("INI: Will use EXEC_NAME as '%s'", exec_name.c_str());

    //
    // Get the current directory, ending in a single /
    //
    curr_dir = dynprintf("%s" DIR_SEP, dir_dot());
    tmp = strsub(curr_dir, DIR_SEP DIR_SEP, DIR_SEP, "curr_dir");
    myfree(curr_dir);
    curr_dir = tmp;

    //
    // Get the parent directory, ending in a single /
    //
    parent_dir = dynprintf("%s" DIR_SEP, dir_dotdot(dir_dot()));
    tmp = strsub(parent_dir, DIR_SEP DIR_SEP, DIR_SEP, "parent_dir");
    myfree(parent_dir);
    parent_dir = tmp;

    //
    // Get rid of ../ from the program name and replace with the path.
    //
    exec_expanded_name = dupstr(ARGV[0], __FUNCTION__);
    if (*exec_expanded_name == '.') {
        tmp = strsub(exec_expanded_name, ".." DIR_SEP, parent_dir, "exec_expanded_name");
        myfree(exec_expanded_name);
        exec_expanded_name = tmp;
    }

    //
    // Get rid of ./ from the program name.
    //
    if (*exec_expanded_name == '.') {
        tmp = strsub(exec_expanded_name, "." DIR_SEP, "", "exec_expanded_name2");
        myfree(exec_expanded_name);
        exec_expanded_name = tmp;
    }

    //
    // Get rid of any // from the path
    //
    tmp = strsub(exec_expanded_name, DIR_SEP DIR_SEP, DIR_SEP, "exec_expanded_name3");
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

        for (dir = strtok(path, PATHSEP); dir; dir = strtok(0, PATHSEP)) {
            EXEC_FULL_PATH_AND_NAME = dynprintf("%s" DIR_SEP "%s", dir, exec_name.c_str());
            if (file_exists(EXEC_FULL_PATH_AND_NAME)) {
                EXEC_DIR = dynprintf("%s" DIR_SEP, dir);
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
    auto new_EXEC_DIR = strsub(EXEC_DIR, "/", DIR_SEP, "EXEC_DIR");
    myfree(EXEC_DIR);
    EXEC_DIR = new_EXEC_DIR;

    DBG3("INI: EXEC_DIR set to %s", EXEC_DIR);
    DBG3("Parent dir  : \"%s\"", parent_dir);
    DBG3("Curr dir    : \"%s\"", curr_dir);
    DBG3("Full name   : \"%s\"", exec_expanded_name);

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
    auto tmp = dynprintf("%s" DIR_SEP, EXEC_DIR);
    auto tmp2 = strsub(tmp, "//", DIR_SEP, "EXEC_DIR");
    auto tmp3 = strsub(tmp2, "\\\\", DIR_SEP, "EXEC_DIR");
    auto tmp4 = strsub(tmp3, "/", DIR_SEP, "EXEC_DIR");
    auto tmp5 = strsub(tmp4, "\\", DIR_SEP, "EXEC_DIR");
    myfree(tmp);
    myfree(tmp2);
    myfree(tmp3);
    myfree(tmp4);
    if (EXEC_DIR) {
        myfree(EXEC_DIR);
    }
    EXEC_DIR = tmp5;

    CON("INI: Will use EXEC_DIR as '%s'", EXEC_DIR);
}

//
// Hunt down the data/ dir.
//
static void find_data_dir (void)
{_
    DATA_PATH = dynprintf("%sdata" DIR_SEP, EXEC_DIR);
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
    EXEC_PYTHONPATH = dynprintf("%spython%s" DIR_SEP, EXEC_DIR, PYVER);
}

//
// Hunt down the world/ dir.
//
static void find_world_dir (void)
{_
    WORLD_PATH = dynprintf("%sdata" DIR_SEP "world" DIR_SEP, EXEC_DIR);
    if (dir_exists(WORLD_PATH)) {
        return;
    }

    myfree(WORLD_PATH);

    WORLD_PATH = dupstr(EXEC_DIR, __FUNCTION__);
}

//
// Hunt down the fonts/ dir.
//
static void find_ttf_dir (void)
{_
    TTF_PATH = dynprintf("%sdata" DIR_SEP "ttf" DIR_SEP, EXEC_DIR);
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
    GFX_PATH = dynprintf("%sdata" DIR_SEP "gfx" DIR_SEP, EXEC_DIR);
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
    CON(" --quick-start");
    CON(" --player-name 'disco bob'");
    CON(" --debug                     // basic debug");
    CON(" --debug2                    // as above but includes log indentation and more detailed debugs");
    CON(" --debug3                    // as above but show the entire level");
    CON(" --debug4                    // as above but include memory checks");
    CON(" --debug5                    // as above but include out of bounds checks");
    CON(" --no-debug                  // disable debug");
    CON(" --seed <name/number>");
    CON(" ");
    CON("Written by goblinhack@gmail.com");
}

static void parse_args (int32_t argc, char *argv[])
{_
    int32_t i;

    //
    // Parse format args
    //
    LOG("INI: Parse command line arguments for '%s'", argv[0]);
    for (i = 1; i < argc; i++) {
        LOG("INI: + argument: \"%s\"", argv[i]);
    }

    if (argc) {
        g_opt_fast_start = true;
    }

    for (i = 1; i < argc; i++) {
        if (!strcasecmp(argv[i], "--quick-start") ||
            !strcasecmp(argv[i], "-quick-start") ||
            !strcasecmp(argv[i], "--quickstart") ||
            !strcasecmp(argv[i], "-quickstart")) {
            g_opt_new_game = true;
            continue;
        }

        if (!strcasecmp(argv[i], "--seed") ||
            !strcasecmp(argv[i], "-seed") ||
            !strcasecmp(argv[i], "-s")) {
            g_opt_seed_name = argv[i + 1];
            i++;
            continue;
        }

        if (!strcasecmp(argv[i], "--player-name") ||
            !strcasecmp(argv[i], "-player-name") ||
            !strcasecmp(argv[i], "--playername") ||
            !strcasecmp(argv[i], "-playername")) {
            g_opt_player_name = argv[i + 1];
            i++;
            continue;
        }

        if (!strcasecmp(argv[i], "--no-debug") ||
            !strcasecmp(argv[i], "-no-debug") ||
            !strcasecmp(argv[i], "--nodebug") ||
            !strcasecmp(argv[i], "-nodebug")) {
            g_opt_debug1 = false;
            g_opt_debug2 = false;
            g_opt_debug3 = false;
            g_opt_debug4 = false;
            g_opt_debug5 = false;
            g_opt_override_debug_level = true;
            continue;
        }

        if (!strcasecmp(argv[i], "--debug")  ||
            !strcasecmp(argv[i], "-debug")   ||
            !strcasecmp(argv[i], "--debug1") ||
            !strcasecmp(argv[i], "-debug1")) {
            g_opt_debug1 = true;
            g_opt_override_debug_level = true;
            continue;
        }

        if (!strcasecmp(argv[i], "--debug2") ||
            !strcasecmp(argv[i], "-debug2")) {
            g_opt_debug1 = true;
            g_opt_debug2 = true;
            g_opt_override_debug_level = true;
            continue;
        }

        if (!strcasecmp(argv[i], "--debug3") ||
            !strcasecmp(argv[i], "-debug3")) {
            g_opt_debug1 = true;
            g_opt_debug2 = true;
            g_opt_debug3 = true;
            g_opt_override_debug_level = true;
            continue;
        }

        if (!strcasecmp(argv[i], "--debug4") ||
            !strcasecmp(argv[i], "-debug4")) {
            g_opt_debug1 = true;
            g_opt_debug2 = true;
            g_opt_debug3 = true;
            g_opt_debug4 = true;
            g_opt_override_debug_level = true;
            continue;
        }

        if (!strcasecmp(argv[i], "--debug5") ||
            !strcasecmp(argv[i], "-debug5")) {
            g_opt_debug1 = true;
            g_opt_debug2 = true;
            g_opt_debug3 = true;
            g_opt_debug4 = true;
            g_opt_debug5 = true;
            g_opt_override_debug_level = true;
            continue;
        }

        //
        // Bad argument.
        //
        if (argv[i][0] == '-') {
            usage();
            DIE("Unknown format argument, %s", argv[i]);
        }

        usage();
        DIE("Unknown format argument, %s", argv[i]);
    }
}

//
// Where all logs go
//
static std::string create_appdata_dir (void)
{
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

    char *dir = dynprintf("%s%s%s", appdata, DIR_SEP, "zorbash");
#ifdef _WIN32
    mkdir(dir);
#else
    mkdir(dir, 0700);
#endif
    myfree(dir);

    char *out = dynprintf("%s%s%s%s%s", appdata, DIR_SEP, "zorbash", DIR_SEP, "stdout.txt");
    g_log_stdout = fopen(out, "w+");

    char *err = dynprintf("%s%s%s%s%s", appdata, DIR_SEP, "zorbash", DIR_SEP, "stderr.txt");
    g_log_stderr = fopen(err, "w+");

    LOG("INI: Will use STDOUT as '%s'", out);
    LOG("INI: Will use STDERR as '%s'", err);

    myfree(out);
    myfree(err);

    return std::string(appdata);
}

int32_t main (int32_t argc, char *argv[])
{_
    ARGV = argv;

    auto appdata = create_appdata_dir(); // Want this first so we get all logs

    LOG("INI: Greetings mortal");

    //////////////////////////////////////////////////////////////////////////////
    // Use LOG instead of CON until we set stdout or you see two logs
    // v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v
    //////////////////////////////////////////////////////////////////////////////
#ifdef _WIN32
    LOG("INI: Platform is _WIN32");
#endif
#ifdef __MINGW32__
    LOG("INI: Platform is __MINGW32__");
#endif
#ifdef __MINGW64__
    LOG("INI: Platform is __MINGW64__");
#endif
#ifdef __APPLE__
    LOG("INI: Platform is __APPLE__");
#endif
#ifdef __linux__
    LOG("INI: Platform is __linux__");
#endif

    parse_args(argc, argv);

    LOG("INI: Ramdisk");
    ramdisk_init();

    //////////////////////////////////////////////////////////////////////////////
    // ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ Use LOG
    // instead of CON until we set stdout or you see two logs
    //////////////////////////////////////////////////////////////////////////////

    LOG("INI: Create console");
    ascii_init();

    //
    // Need this to get the UTF on the console
    //
#ifndef _WIN32
    CON("INI: Set locale for console");
    std::locale loc("");
    std::ios_base::sync_with_stdio(false);
    std::wcout.imbue(loc);
#endif

    //
    // Create and load the last saved game
    //
    CON("INI: Load game config");
    game = new Game(std::string(appdata));
    game->load_config();
#if 0
    game->save_config();
    int x = 1;
    if (x) {
    exit(0);
    }
#endif

    if (unlikely(g_opt_debug2)) {
        if (game) {
            game->config.debug_mode = g_opt_debug2;
        }
    }

    CON("INI: SDL create window");
    if (!sdl_init()) {
        ERR("SDL init");
    }

    if (g_need_restart) {
        CON("FINI: Restart");
        g_need_restart = false;
        execv(argv[0], argv);
    }

    CON("INI: OpenGL enter 2D mode");
    gl_init_2d_mode();

    //
    // Disable vsync so the console is faster
    //
    SDL_GL_SetSwapInterval(0);

    CON("INI: Load early gfx tiles, text, UI etc...");
    gfx_init();

    //
    // Random number generators
    //
    CON("INI: Create random number generators");
    double mean = 1.0;
    double std = 0.5;
    std::normal_distribution<double> distribution;
    distribution.param(std::normal_distribution<double>(mean, std).param());
    rng.seed(std::random_device{}());

#ifdef ENABLE_CRASH_HANDLER
    //
    // Crash handlers
    CON("INI: Install crash handlers");
    signal(SIGSEGV, segv_handler);
    signal(SIGABRT, segv_handler);
    signal(SIGINT, ctrlc_handler);
    signal(SIGILL, ctrlc_handler);
    signal(SIGPIPE, ctrlc_handler);
#endif

    CON("INI: Create color names map");
    color_init();

#if 0
    extern int grid_test(void);
    grid_test();
    int x = 1;
    if (x) {
    DIE("X");
    }
#endif

#if 0
    extern int dungeon_test(void);
    dungeon_test();

    auto y = 1;
    if (y) {
    DIE("X");
    }
#endif

    CON("INI: Create UI fonts");
    if (!font_init()) {
        ERR("Font init");
    }

    CON("INI: Load UI widgets");
    if (!wid_init()) {
        ERR("Wid init");
    }

    CON("INI: Load UI console");
    if (!wid_console_init()) {
        ERR("Wid_console init");
    }
    wid_toggle_hidden(wid_console_window);
    sdl_flush_display();
    ////////////////////////////////////////////////////////////////////////////////////////////////////

    CON("INI: Load UI tiles");
    if (!wid_tiles_init()) {
        ERR("Wid tiles init");
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////

    CON("INI: Load UI and gfx tiles");
    if (!tile_init()) {
        ERR("Tile init");
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////

    CON("INI: Load textures");
    if (!tex_init()) {
        ERR("Tex init");
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    CON("INI: Init audio");
    if (!audio_init()) {
        ERR("Audio init");
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    CON("INI: Load music");
    if (!music_init()) {
        ERR("Music init");
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    CON("INI: Load sound");
    if (!sound_init()) {
        ERR("Sound init");
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    CON("INI: Load UI topcon");
    if (!wid_topcon_init()) {
        ERR("Wid_topcon init");
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    CON("INI: Load UI actionar");
    wid_actionbar_init();

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    CON("INI: Load UI botcon");
    if (!wid_botcon_init()) {
        ERR("Wid_botcon init");
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////

    CON("INI: Find resource locations for gfx and music");
    find_file_locations();
    ////////////////////////////////////////////////////////////////////////////////////////////////////

    CON("INI: Load UI commands");
    if (!command_init()) {
        ERR("Command init");
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////

    CON("INI: Load dungeon character maps");
    Charmap::init_charmaps();
    ////////////////////////////////////////////////////////////////////////////////////////////////////

    python_init(argv);
    py_call_void("init2");
    ////////////////////////////////////////////////////////////////////////////////////////////////////

    CON("INI: Load dungeon thing templates");
    tp_init();
    ////////////////////////////////////////////////////////////////////////////////////////////////////

    //
    // Create a fresh game if none was loaded
    //
    CON("INI: Load dungeon rooms");
    room_init();
    ////////////////////////////////////////////////////////////////////////////////////////////////////
  
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

    wid_topcon_flush();
    wid_botcon_flush();
    sdl_flush_display();
    ////////////////////////////////////////////////////////////////////////////////////////////////////

    if (g_opt_new_game) {
        CON("INI: New game");
        game->new_game();
    } else {
        CON("INI: Game menu");
        game->main_menu_select();
    }

    sdl_flush_display();
    ////////////////////////////////////////////////////////////////////////////////////////////////////

    wid_toggle_hidden(wid_console_window);

    config_gfx_vsync_update();

    g_opt_fast_start = false;
    sdl_loop();
    LOG("FINI: SDL loop finished");

    CON("FINI: Leave 2D mode");
    gl_leave_2d_mode();

    CON("FINI: Quit");
    quit();

    if (g_need_restart) {
        CON("FINI: Restart");
        g_need_restart = false;
        execv(argv[0], argv);
    }

    CON("FINI: Goodbye and take care until next time!");
    return (0);
}
