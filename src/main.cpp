/*
 * Copyright (C) 2011-2020 goblinhack@gmail.com
 *
 * See the LICENSE file for license.
 */

#define __MAIN__
#include "my_main.h"

#ifdef ENABLE_CRASH_HANDLER
#include <signal.h>
#endif
#include <stdlib.h>
#include <unistd.h>

#ifndef _MSC_VER
#include <libgen.h>
#endif

#include "my_slre.h"
#include "my_python.h"

#include "my_glapi.h"
#include "my_wid.h"
#include "my_wid_console.h"
#include "my_command.h"
#include "my_ttf.h"
#include "my_font.h"
#include "my_math_util.h"
#include "my_tex.h"
#include "my_wid_tiles.h"
#include "my_music.h"
#include "my_sound.h"
#include "my_tile.h"
#include "my_dir.h"
#include "my_file.h"
#include "my_ramdisk.h"
#include "my_term.h"

static char **ARGV;
char *EXEC_FULL_PATH_AND_NAME;
char *EXEC_DIR;
char *DATA_PATH;
char *WORLD_PATH;
char *PYTHON_PATH;
char *TTF_PATH;
char *GFX_PATH;
int debug;

FILE *LOG_STDOUT;
FILE *LOG_STDERR;

uint8_t quitting;

void callstack::dump (void)
{_
    int i = 1;

    fprintf(MY_STDERR, "code trace:\n");
    fprintf(MY_STDERR, "========================================================\n");
    for (auto iter = my_stack.rbegin(); iter != my_stack.rend(); iter++) {
        fprintf(MY_STDERR, "(stack) %d %s %s, line %u\n", i++, iter->file, iter->func, iter->line);
    }
    fprintf(MY_STDERR, "========================================================\n");

    fprintf(MY_STDOUT, "code trace:\n");
    fprintf(MY_STDOUT, "========================================================\n");
    for (auto iter = my_stack.rbegin(); iter != my_stack.rend(); iter++) {
        fprintf(MY_STDOUT, "(stack) %d %s %s, line %u\n", i++, iter->file, iter->func, iter->line);
    }
    fprintf(MY_STDOUT, "========================================================\n");

    printf("code trace:\n");
    printf("========================================================\n");
    for (auto iter = my_stack.rbegin(); iter != my_stack.rend(); iter++) {
        printf("(stack) %d %s %s, line %u\n", i++, iter->file, iter->func, iter->line);
    }
    printf("========================================================\n");
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
    if (quitting) {
        return;
    }

    quitting = true;

#ifdef ENABLE_CRASH_HANDLER
    signal(SIGSEGV, 0);   // uninstall our handler
    signal(SIGABRT, 0);   // uninstall our handler
    signal(SIGINT, 0);    // uninstall our handler
#endif

    /*
     * Save the player name.
     */
{_
    config_save();
}

{_
    python_fini();
}


{_
    LOG("Finishing: sdl_exit");
    sdl_exit();
}

{_
    LOG("Finishing: tp_fini");
    tp_fini();
}

{_
    LOG("Finishing: thing_fini");
    thing_fini();
}

{_
    LOG("Finishing: wid_console_fini");
    wid_console_fini();
}

{_
    LOG("Finishing: command_fini");
    command_fini();
}

{_
    LOG("Finishing: wid_fini");
    wid_fini();
}

{_
    LOG("Finishing: font_fini");
    font_fini();
}

{_
    LOG("Finishing: tex_fini");
    tex_fini();
}

{_
    LOG("Finishing: wid_tiles_fini");
    wid_tiles_fini();
}

{_
    LOG("Finishing: music_fini");
    music_fini();
}

{_
    LOG("Finishing: sound_fini");
    sound_fini();
}

{_
    LOG("Finishing: tile_fini");
    tile_fini();
}

{_
    LOG("Finishing: sdl_fini");
    sdl_fini();
}

{_
    LOG("Finishing: config_fini");
    config_fini();
}

{_
    LOG("Finishing: blit_fini");
    blit_fini();
}

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

#ifdef ENABLE_LEAKCHECK
    if (!croaked) {
        ptrcheck_fini();
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
    quit();

    LOG("Bye, error exit");
    fprintf(MY_STDERR, "exit(1) error\n");

    exit(1);
}

/*
 * Find the binary we are running.
 */
static void find_executable (void)
{_
    char *parent_dir = 0;
    char *curr_dir = 0;
    std::string exec_name = "";
    char *exec_expanded_name = 0;
    char *path = 0;
    char *tmp;

    exec_name = mybasename(ARGV[0], __FUNCTION__);

    /*
     * Get the current directory, ending in a single /
     */
    curr_dir = dynprintf("%s" DSEP, dir_dot());
    tmp = strsub(curr_dir, DSEP DSEP, DSEP);
    myfree(curr_dir);
    curr_dir = tmp;

    /*
     * Get the parent directory, ending in a single /
     */
    parent_dir = dynprintf("%s" DSEP, dir_dotdot(dir_dot()));
    tmp = strsub(parent_dir, DSEP DSEP, DSEP);
    myfree(parent_dir);
    parent_dir = tmp;

    /*
     * Get rid of ../ from the program name and replace with the path.
     */
    exec_expanded_name = dupstr(ARGV[0], __FUNCTION__);
    if (*exec_expanded_name == '.') {
        tmp = strsub(exec_expanded_name, ".." DSEP, parent_dir);
        myfree(exec_expanded_name);
        exec_expanded_name = tmp;
    }

    /*
     * Get rid of ./ from the program name.
     */
    if (*exec_expanded_name == '.') {
        tmp = strsub(exec_expanded_name, "." DSEP, "");
        myfree(exec_expanded_name);
        exec_expanded_name = tmp;
    }

    /*
     * Get rid of any // from th path
     */
    tmp = strsub(exec_expanded_name, DSEP DSEP, DSEP);
    myfree(exec_expanded_name);
    exec_expanded_name = tmp;

    /*
     * Look in the simplest case first.
     */
    EXEC_FULL_PATH_AND_NAME = dynprintf("%s%s", curr_dir, exec_name.c_str());
    if (file_exists(EXEC_FULL_PATH_AND_NAME)) {
        EXEC_DIR = dupstr(curr_dir, "exec dir 1");
        goto cleanup;
    }

    myfree(EXEC_FULL_PATH_AND_NAME);

    /*
     * Try the parent dir.
     */
    EXEC_FULL_PATH_AND_NAME = dynprintf("%s%s", parent_dir, exec_name.c_str());
    if (file_exists(EXEC_FULL_PATH_AND_NAME)) {
        EXEC_DIR = dupstr(parent_dir, "exec dir 2");
        goto cleanup;
    }

    myfree(EXEC_FULL_PATH_AND_NAME);

    /*
     * Try the PATH.
     */
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
}

/*
 * Find all installed file locations.
 */
static void find_exec_dir (void)
{_
    char *tmp;

    find_executable();

    /*
     * Make sure the exec dir ends in a /
     */
    tmp = dynprintf("%s" DSEP, EXEC_DIR);
    EXEC_DIR = strsub(tmp, DSEP DSEP, DSEP);
    myfree(tmp);
}

/*
 * Hunt down the data/ dir.
 */
static void find_data_dir (void)
{_
    DATA_PATH = dynprintf("%sdata" DSEP, EXEC_DIR);
    if (dir_exists(DATA_PATH)) {
        return;
    }

    myfree(DATA_PATH);

    DATA_PATH = dupstr(EXEC_DIR, __FUNCTION__);
}

/*
 * Hunt down the python/ dir.
 */
static void find_python_dir (void)
{_
    PYTHON_PATH = dynprintf("%spython" DSEP, EXEC_DIR);
    if (dir_exists(PYTHON_PATH)) {
        return;
    }

    myfree(PYTHON_PATH);

    PYTHON_PATH = dupstr(EXEC_DIR, __FUNCTION__);
}

/*
 * Hunt down the world/ dir.
 */
static void find_world_dir (void)
{_
    WORLD_PATH = dynprintf("%sdata" DSEP "world" DSEP, EXEC_DIR);
    if (dir_exists(WORLD_PATH)) {
        return;
    }

    myfree(WORLD_PATH);

    WORLD_PATH = dupstr(EXEC_DIR, __FUNCTION__);
}

/*
 * Hunt down the ttf/ dir.
 */
static void find_ttf_dir (void)
{_
    TTF_PATH = dynprintf("%sdata" DSEP "ttf" DSEP, EXEC_DIR);
    if (dir_exists(TTF_PATH)) {
        return;
    }

    myfree(TTF_PATH);

    TTF_PATH = dupstr(EXEC_DIR, __FUNCTION__);
}

/*
 * Hunt down the gfx/ dir.
 */
static void find_gfx_dir (void)
{_
    GFX_PATH = dynprintf("%sdata" DSEP "gfx" DSEP, EXEC_DIR);
    if (dir_exists(GFX_PATH)) {
        return;
    }

    myfree(GFX_PATH);

    GFX_PATH = dupstr(EXEC_DIR, __FUNCTION__);
}

/*
 * Find all installed file locations.
 */
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

    LOG("Greetings mortal");

    /*
     * Parse format args
     */
    LOG("Program name: \"%s\"", argv[0]);
    for (i = 1; i < argc; i++) {
        CON("  arg: \"%s\"", argv[i]);
    }

    for (i = 1; i < argc; i++) {

        /*
         * Bad argument.
         */
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
#if 1
    extern int cereal_test(void);
    cereal_test();
    exit(0);
#endif
    /*
    mcheck(0);
     */

#ifdef ENABLE_CRASH_HANDLER
    signal(SIGSEGV, segv_handler);   // install our handler
    signal(SIGABRT, segv_handler);   // install our handler
    signal(SIGINT, ctrlc_handler);   // install our handler
#endif

    const char *appdata;

    mysrand(time(0));

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
    myfree(dir);

    char *out = dynprintf("%s%s%s%s%s", appdata, DSEP, "zorbash", DSEP, "stdout.txt");
    LOG_STDOUT = fopen(out, "w+");
    myfree(out);

    char *err = dynprintf("%s%s%s%s%s", appdata, DSEP, "zorbash", DSEP, "stderr.txt");
    LOG_STDERR = fopen(err, "w+");
    myfree(err);

    ramdisk_init();

    ARGV = argv;

    dospath2unix(ARGV[0]);

    parse_args(argc, argv);

    math_init();

    color_init();

    find_file_locations();

    python_init(argv);

    if (!config_init()) {
	ERR("Config init");
    }

    if (!config_load()) {
	ERR("Config read");
    }

    if (!sdl_init()) {
	ERR("SDL init");
    }

    if (!tex_init()) {
	ERR("tex init");
    }

    if (!wid_tiles_init()) {
	ERR("wid tiles init");
    }

    if (!music_init()) {
	ERR("music init");
    }

    if (!sound_init()) {
	ERR("sound init");
    }

    if (!tile_init()) {
	ERR("tile init");
    }

    if (!font_init()) {
	ERR("Font init");
    }

    if (!wid_init()) {
	ERR("wid init");
    }

#ifdef ENABLE_LEAKCHECK
    ptrcheck_leak_snapshot();
#endif

    if (!wid_console_init()) {
	ERR("wid_console init");
    }

    if (!command_init()) {
	ERR("command init");
    }

#ifdef ENABLE_LEAKCHECK
    if (!ptrcheck_init()) {
	ERR("ptrcheck init");
    }
#endif

    py_call_void("init2");

    tp_init();
    thing_init();

    gl_init_2d_mode();
    sdl_loop();
    gl_leave_2d_mode();

    quit();

    LOG("Goodbye cruel world");
    fprintf(MY_STDOUT, "Exited\n");

    return (0);
}
