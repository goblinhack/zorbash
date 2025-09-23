//
// Copyright goblinhack@gmail.com
//

#include <ctime>     // do not remove
#include <libgen.h>  // dirname
#include <random>    // std::default_random_engine
#include <signal.h>  // dirname
#include <string.h>  // do not remove
#include <strings.h> // do not remove
#include <time.h>    // do not remove
#include <unistd.h>  // do not remove

#include "my_audio.hpp"
#include "my_backtrace.hpp"
#include "my_command.hpp"
#include "my_dir.hpp"
#include "my_file.hpp"
#include "my_font.hpp"
#include "my_game.hpp"
#include "my_gfx.hpp"
#include "my_globals_extra.hpp"
#include "my_level_static.hpp"
#include "my_music.hpp"
#include "my_python.hpp"
#include "my_ramdisk.hpp"
#include "my_room.hpp"
#include "my_sdl_proto.hpp"
#include "my_sound.hpp"
#include "my_string.hpp"
#include "my_wid_actionbar.hpp"
#include "my_wid_botcon.hpp"
#include "my_wid_console.hpp"
#include "my_wid_topcon.hpp"

static char **ARGV;

static std::string original_program_name;
static bool        seed_manually_set {};

void quit(void)
{
  TRACE_AND_INDENT();
  LOG("FIN: Quitting, start cleanup");

  if (g_quitting) {
    LOG("FIN: Quitting, nested");
    return;
  }

  g_quitting = true;

#ifdef ENABLE_CRASH_HANDLER
  signal(SIGSEGV, nullptr); // uninstall our handler
  signal(SIGABRT, nullptr); // uninstall our handler
  signal(SIGINT, nullptr);  // uninstall our handler
#ifndef _WIN32
  signal(SIGPIPE, nullptr); // uninstall our handler
#endif
  signal(SIGFPE, nullptr); // uninstall our handler
#endif

  if (game) {
    game->fini();
  }

  LOG("FIN: room_fini");
  room_fini();

  LOG("FIN: level_fini");
  level_fini();

  LOG("FIN: sdl_exit");
  sdl_exit();

  LOG("FIN: tp_fini");
  tp_fini();

  LOG("FIN: wid_console_fini");
  wid_console_fini();

  LOG("FIN: wid_topcon_fini");
  wid_topcon_fini();

  LOG("FIN: wid_botcon_fini");
  wid_botcon_fini();

  LOG("FIN: command_fini");
  command_fini();

  LOG("FIN: wid_fini");
  wid_fini();

  LOG("FIN: font_fini");
  font_fini();

  LOG("FIN: tex_fini");
  tex_fini();

  LOG("FIN: wid_tiles_fini");
  wid_tiles_fini();

  LOG("FIN: tile_fini");
  tile_fini();

  LOG("FIN: blit_fini");
  blit_fini();

  LOG("FIN: color_fini");
  color_fini();

  LOG("FIN: audio_fini");
  audio_fini();

  LOG("FIN: music_fini");
  music_fini();

  LOG("FIN: sound_fini");
  sound_fini();

  LOG("FIN: sdl_fini");
  sdl_fini();

  if (EXEC_FULL_PATH_AND_NAME) {
    myfree(EXEC_FULL_PATH_AND_NAME);
    EXEC_FULL_PATH_AND_NAME = nullptr;
  }

  if (DATA_PATH) {
    myfree(DATA_PATH);
    DATA_PATH = nullptr;
  }

  if (EXEC_PYTHONPATH) {
    myfree(EXEC_PYTHONPATH);
    EXEC_PYTHONPATH = nullptr;
  }

  if (WORLD_PATH) {
    myfree(WORLD_PATH);
    WORLD_PATH = nullptr;
  }

  if (TTF_PATH) {
    myfree(TTF_PATH);
    TTF_PATH = nullptr;
  }

  if (GFX_PATH) {
    myfree(GFX_PATH);
    GFX_PATH = nullptr;
  }

  if (EXEC_DIR) {
    myfree(EXEC_DIR);
    EXEC_DIR = nullptr;
  }

#ifdef ENABLE_DEBUG_MEM_LEAKS
  if (! g_die_occurred) {
    ptrcheck_leak_print();
  }
#endif

  LOG("FIN: Cleanup done");

  LOG("FIN: py_fini");
  //
  // This might exit
  //
  py_fini();
}

void restart(void)
{
  TRACE_AND_INDENT();
  char *args[] = {nullptr, nullptr};
  char *executable;

  wid_visible(wid_console_window);
  wid_raise(wid_console_window);
  wid_update(wid_console_window);

  executable = (char *) original_program_name.c_str();

#ifdef _WIN32
  //
  // Windows has spaces in the path name and that ends up being incorrectly
  // split by execve on the 2nd boot. So, just avoid the issue.
  //
  executable = (char *) "zorbash.exe";
#endif

  CON("FIN: Restarting the program... Wish me luck.");
  CON("FIN: Run \"%s\"", executable);
  sdl_flush_display(true);
  sleep(5);

  args[ 0 ] = executable;
  execve(executable, (char *const *) args, nullptr);
  DIE("Failed to restart");
}

void die(void)
{
  TRACE_AND_INDENT();
  quit();

  LOG("Bye, error exit");
  fprintf(MY_STDERR, "exit(1) error\n");

  exit(1);
}

//
// Find the binary we are running.
//
static void find_executable(void)
{
  TRACE_AND_INDENT();
  char       *parent_dir         = nullptr;
  char       *curr_dir           = nullptr;
  std::string exec_name          = "";
  char       *exec_expanded_name = nullptr;
  char       *path               = nullptr;
  char       *tmp;

  exec_name = mybasename(ARGV[ 0 ], __FUNCTION__);
  CON("INI: Will use EXEC_NAME as '%s'", exec_name.c_str());

  //
  // Get the current directory, ending in a single /
  //
  curr_dir = dynprintf("%s" DIR_SEP, dir_dot());
  tmp      = strsub(curr_dir, DIR_SEP DIR_SEP, DIR_SEP, "curr_dir");
  myfree(curr_dir);
  curr_dir = tmp;

  //
  // Get the parent directory, ending in a single /
  //
  parent_dir = dynprintf("%s" DIR_SEP, dir_dotdot(dir_dot()));
  tmp        = strsub(parent_dir, DIR_SEP DIR_SEP, DIR_SEP, "parent_dir");
  myfree(parent_dir);
  parent_dir = tmp;

  //
  // Get rid of ../ from the program name and replace with the path.
  //
  exec_expanded_name = dupstr(ARGV[ 0 ], __FUNCTION__);
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
    char *dir = nullptr;

    path = dupstr(path, "path");

    for (dir = strtok(path, PATHSEP); dir; dir = strtok(nullptr, PATHSEP)) {
      EXEC_FULL_PATH_AND_NAME = dynprintf("%s" DIR_SEP "%s", dir, exec_name.c_str());
      if (file_exists(EXEC_FULL_PATH_AND_NAME)) {
        EXEC_DIR = dynprintf("%s" DIR_SEP, dir);
        goto cleanup;
      }

      myfree(EXEC_FULL_PATH_AND_NAME);
    }

    myfree(path);
    path = nullptr;
  }

  EXEC_FULL_PATH_AND_NAME = dupstr(exec_expanded_name, "full path");
  EXEC_DIR                = dupstr(dirname(exec_expanded_name), "exec dir");

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
static void find_exec_dir(void)
{
  TRACE_AND_INDENT();
  find_executable();

  //
  // Make sure the exec dir ends in a /
  //
  auto tmp  = dynprintf("%s" DIR_SEP, EXEC_DIR);
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
static void find_data_dir(void)
{
  TRACE_AND_INDENT();
  DATA_PATH = dynprintf("%sdata" DIR_SEP, EXEC_DIR);
  if (dir_exists(DATA_PATH)) {
    return;
  }
  myfree(DATA_PATH);

  DATA_PATH = dynprintf(".." DIR_SEP "data");
  if (dir_exists(DATA_PATH)) {
    return;
  }
  myfree(DATA_PATH);

  DATA_PATH = dupstr(EXEC_DIR, __FUNCTION__);
}

//
// Hunt down the python/ dir.
//
static void find_python_dir(void)
{
  TRACE_AND_INDENT();
  EXEC_PYTHONPATH = dynprintf("%spython%s" DIR_SEP, EXEC_DIR, PYVER);
}

//
// Hunt down the world/ dir.
//
static void find_world_dir(void)
{
  TRACE_AND_INDENT();
  WORLD_PATH = dynprintf("%sdata" DIR_SEP "world" DIR_SEP, EXEC_DIR);
  if (dir_exists(WORLD_PATH)) {
    return;
  }
  myfree(WORLD_PATH);

  WORLD_PATH = dynprintf(".." DIR_SEP "world");
  if (dir_exists(WORLD_PATH)) {
    return;
  }
  myfree(WORLD_PATH);

  WORLD_PATH = dupstr(EXEC_DIR, __FUNCTION__);
}

//
// Hunt down the fonts/ dir.
//
static void find_ttf_dir(void)
{
  TRACE_AND_INDENT();
  TTF_PATH = dynprintf("%sdata" DIR_SEP "ttf" DIR_SEP, EXEC_DIR);
  if (dir_exists(TTF_PATH)) {
    return;
  }
  myfree(TTF_PATH);

  TTF_PATH = dynprintf(".." DIR_SEP "data" DIR_SEP "ttf" DIR_SEP);
  if (dir_exists(TTF_PATH)) {
    return;
  }
  myfree(TTF_PATH);

  TTF_PATH = dupstr(EXEC_DIR, __FUNCTION__);
}

//
// Hunt down the gfx/ dir.
//
static void find_gfx_dir(void)
{
  TRACE_AND_INDENT();
  GFX_PATH = dynprintf("%sdata" DIR_SEP "gfx" DIR_SEP, EXEC_DIR);
  if (dir_exists(GFX_PATH)) {
    return;
  }
  myfree(GFX_PATH);

  GFX_PATH = dynprintf(".." DIR_SEP "gfx" DIR_SEP);
  if (dir_exists(GFX_PATH)) {
    return;
  }
  myfree(GFX_PATH);

  GFX_PATH = dupstr(EXEC_DIR, __FUNCTION__);
}

//
// Find all installed file locations.
//
static void find_file_locations(void)
{
  TRACE_AND_INDENT();
  find_exec_dir();
  find_data_dir();
  find_python_dir();
  find_world_dir();
  find_ttf_dir();
  find_gfx_dir();

  DBG("Gfx path    : \"%s\"", GFX_PATH);
  DBG("Font path   : \"%s\"", TTF_PATH);
}

static void usage(void)
{
  TRACE_AND_INDENT();
  static int whinged;

  if (whinged) {
    return;
  }
  whinged = true;

  CON("Zorbash, options:");
  CON(" ");
  CON("Commonly used options:");
  CON(" --ascii                     -- Enable ascii graphics.");
  CON(" --pixelart                  -- Enable pixelart graphics.");
  CON(" --player-name 'disco bob'   -- Set your name.");
  CON(" --seed <name/number>        -- Set the random dungeon seed.");
  CON(" ");
  CON("Less commonly used options:");
  CON(" --monochrome                -- Enable monochrome graphics.");
  CON(" --silent                    -- No sound.");
  CON(" --resume                    -- Load last snapshot.");
  CON(" ");
  CON("Debugging options:");
  CON(" --debug                     -- Basic debug.");
  CON(" --debug2                    -- Most debugs. Most useful.");
  CON(" --debug3                    -- All debugs. Slow.");
  CON(" --no-debug                  -- Disable debugs.");
  CON(" ");
  CON("Testing options:");
  CON(" --dump-monsters             -- Dump monsters info");
  CON(" --dump-weapons              -- Dump weapons info");
  CON(" --test-biome-chasms         -- Test the chasms biome");
  CON(" --test-biome-flooded        -- Test the flooded biome");
  CON(" --test-biome-ice            -- Test the ice biome");
  CON(" --test-biome-lava           -- Test the lava biome");
  CON(" --test-biome-swamp          -- Test the swamp biome");
  CON(" --test-depth <number>       -- Set the level depth for testing");
  CON(" --test-dungeon              -- Generate lots of dungeons to check for errors");
  CON(" --test-save-load            -- Testing level save and load");
  CON(" --test-start                -- Skip menus, start the game at a test level.");
  CON(" ");
  CON("Written by goblinhack@gmail.com");
}

static void parse_args(int argc, char *argv[])
{
  TRACE_AND_INDENT();
  int i;

  //
  // Parse format args
  //
  LOG("INI: Parse command line arguments for '%s'", argv[ 0 ]);
  for (i = 1; i < argc; i++) {
    LOG("INI: + argument: \"%s\"", argv[ i ]);
  }

  if (argc) {
    g_opt_no_slow_log_flush = true;
  }

  for (i = 1; i < argc; i++) {
    if (! strcasecmp(argv[ i ], "--ascii") || ! strcasecmp(argv[ i ], "-ascii")) {
      g_opt_ascii          = true;
      g_opt_ascii_override = true;
      continue;
    }

    if (! strcasecmp(argv[ i ], "--pixelart") || ! strcasecmp(argv[ i ], "-pixelart")) {
      g_opt_ascii          = false;
      g_opt_ascii_override = true;
      continue;
    }

    if (! strcasecmp(argv[ i ], "--test-biome-swamp") || ! strcasecmp(argv[ i ], "-test-biome-swamp")) {
      g_opt_biome_swamp = true;
      continue;
    }

    if (! strcasecmp(argv[ i ], "--test-biome-flooded") || ! strcasecmp(argv[ i ], "-test-biome-flooded")) {
      g_opt_biome_flooded = true;
      continue;
    }

    if (! strcasecmp(argv[ i ], "--test-biome-ice") || ! strcasecmp(argv[ i ], "-test-biome-ice")) {
      g_opt_biome_ice = true;
      continue;
    }

    if (! strcasecmp(argv[ i ], "--dump-monsters") || ! strcasecmp(argv[ i ], "-dump-monsters")) {
      g_opt_dump_monsters = true;
      continue;
    }

    if (! strcasecmp(argv[ i ], "--dump-weapons") || ! strcasecmp(argv[ i ], "-dump-weapons")) {
      g_opt_dump_weapons = true;
      continue;
    }

    if (! strcasecmp(argv[ i ], "--test-biome-chasms") || ! strcasecmp(argv[ i ], "-test-biome-chasms")) {
      g_opt_biome_chasms = true;
      continue;
    }

    if (! strcasecmp(argv[ i ], "--test-biome-lava") || ! strcasecmp(argv[ i ], "-test-biome-lava")) {
      g_opt_biome_lava = true;
      continue;
    }

    if (! strcasecmp(argv[ i ], "--test-biome-resume") || ! strcasecmp(argv[ i ], "-test-biome-resume")) {
      g_opt_resume = true;
      continue;
    }

    if (! strcasecmp(argv[ i ], "--monochrome") || ! strcasecmp(argv[ i ], "-monochrome")) {
      g_opt_gfx_monochrome = true;
      continue;
    }

    if (! strcasecmp(argv[ i ], "--silent") || ! strcasecmp(argv[ i ], "-silent")) {
      g_opt_silent = true;
      continue;
    }

    if (! strcasecmp(argv[ i ], "--test-start") || ! strcasecmp(argv[ i ], "-test-start")) {
      g_opt_test_level_start    = true;
      g_opt_test_skip_main_menu = true;
      continue;
    }

    if (! strcasecmp(argv[ i ], "--test-depth") || ! strcasecmp(argv[ i ], "-test-depth")) {
      if (i == argc - 1) {
        usage();
        DIE("Missing parameter for argument, %s", argv[ i ]);
      }
      g_opt_test_level_start       = true;
      g_opt_test_skip_main_menu    = true;
      g_opt_test_level_start_depth = std::stoi(argv[ i + 1 ]);
      i++;
      continue;
    }

    if (! strcasecmp(argv[ i ], "--test-save-load") || ! strcasecmp(argv[ i ], "-test-save-load")) {
      g_opt_test_save_load = true;
      g_opt_tests          = true;
      continue;
    }

    if (! strcasecmp(argv[ i ], "--test-dungeon") || ! strcasecmp(argv[ i ], "-test-dungeon")) {
      g_opt_test_dungeon = true;
      g_opt_tests        = true;
      continue;
    }

    if (! strcasecmp(argv[ i ], "--seed") || ! strcasecmp(argv[ i ], "-seed")) {
      if (i == argc - 1) {
        usage();
        DIE("Missing parameter for argument, %s", argv[ i ]);
      }
      g_opt_seed_name   = argv[ i + 1 ];
      seed_manually_set = true;
      i++;
      continue;
    }

    if (! strcasecmp(argv[ i ], "--player-name") || ! strcasecmp(argv[ i ], "-player-name")
        || ! strcasecmp(argv[ i ], "--playername") || ! strcasecmp(argv[ i ], "-playername")) {
      if (i == argc - 1) {
        usage();
        DIE("Missing parameter for argument, %s", argv[ i ]);
      }
      g_opt_player_name = argv[ i + 1 ];
      i++;
      continue;
    }

    if (! strcasecmp(argv[ i ], "--no-debug") || ! strcasecmp(argv[ i ], "-no-debug")
        || ! strcasecmp(argv[ i ], "--nodebug") || ! strcasecmp(argv[ i ], "-nodebug")) {
      g_opt_debug1               = false;
      g_opt_debug2               = false;
      g_opt_debug3               = false;
      g_opt_override_debug_level = true;
      continue;
    }

    if (! strcasecmp(argv[ i ], "--debug") || ! strcasecmp(argv[ i ], "-debug") || ! strcasecmp(argv[ i ], "--debug1")
        || ! strcasecmp(argv[ i ], "-debug1")) {
      g_opt_debug1               = true;
      g_opt_override_debug_level = true;
      continue;
    }

    if (! strcasecmp(argv[ i ], "--debug2") || ! strcasecmp(argv[ i ], "-debug2")) {
      g_opt_debug1               = true;
      g_opt_debug2               = true;
      g_opt_override_debug_level = true;
      continue;
    }

    if (! strcasecmp(argv[ i ], "--debug3") || ! strcasecmp(argv[ i ], "-debug3")) {
      g_opt_debug1               = true;
      g_opt_debug2               = true;
      g_opt_debug3               = true;
      g_opt_override_debug_level = true;
      continue;
    }

    //
    // Bad argument.
    //
    if (argv[ i ][ 0 ] == '-') {
      usage();
      //
      // Win32 puts spaces in argv when we restart the process. I'm not sure
      // how to handle that, so don't fail the program. Warn and continue.
      //
      CON("Unknown format argument, %s", argv[ i ]);
#ifdef _WIN32
      return;
#else
      exit(1);
#endif
    }

    usage();
    CON("Unknown format argument, %s", argv[ i ]);
#ifdef _WIN32
    return;
#else
    exit(1);
#endif
  }
}

//
// Where all logs go
//
static std::string create_appdata_dir(void)
{
  const char *appdata;
  appdata = getenv("APPDATA");
  if (! appdata || ! appdata[ 0 ]) {
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

  char *out             = dynprintf("%s%s%s%s%s", appdata, DIR_SEP, "zorbash", DIR_SEP, "stdout.txt");
  g_log_stdout_filename = std::string(out);
  g_log_stdout          = fopen(out, "w+");

  char *err             = dynprintf("%s%s%s%s%s", appdata, DIR_SEP, "zorbash", DIR_SEP, "stderr.txt");
  g_log_stderr_filename = std::string(err);
  g_log_stderr          = fopen(err, "w+");

  CON("INI: Will use STDOUT as '%s'", out);
  CON("INI: Will use STDERR as '%s'", err);

  myfree(out);
  myfree(err);

  return std::string(appdata);
}

void flush_the_console(void)
{
  //
  // Easier to see progress on windows where there is no console
  //
#ifdef _WIN32
  wid_visible(wid_console_window);
  sdl_flush_display(true);
#endif
}

int main(int argc, char *argv[])
{
  TRACE_NO_INDENT();
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

  {
    TRACE_NO_INDENT();
    parse_args(argc, argv);
  }

  {
    LOG("INI: Ramdisk");
    TRACE_NO_INDENT();
    ramdisk_init();
  }

  //////////////////////////////////////////////////////////////////////////////
  // ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ Use LOG
  // instead of CON until we set stdout or you see two logs
  //////////////////////////////////////////////////////////////////////////////

  {
    LOG("INI: Create console");
    TRACE_NO_INDENT();
    ascii_init();
  }

  //
  // Need this to get the UTF on the console
  //
#ifndef _WIN32
  CON("INI: Set locale for console");
  std::locale loc("");
  std::ios_base::sync_with_stdio(false);
  std::wcout.imbue(loc);
#endif

#ifdef ENABLE_CRASH_HANDLER
  //
  // Crash handlers
  CON("INI: Install crash handlers");
  signal(SIGSEGV, segv_handler);
  signal(SIGABRT, segv_handler);
  signal(SIGFPE, segv_handler);
  signal(SIGILL, segv_handler);
#ifndef _WIN32
  signal(SIGPIPE, ctrlc_handler);
#endif
  signal(SIGINT, ctrlc_handler);
#endif

  //
  // Create and load the last saved game
  //
  {
    TRACE_NO_INDENT();
    CON("INI: Load config");
    game              = new Game(std::string(appdata));
    auto config_error = game->load_config();

    //
    // If the seed is set on the command line, make it stick
    //
    if (seed_manually_set) {
      game->seed_manually_set = true;
    }

    std::string version = "" MYVER "";

    if (game->config.version != version) {
      SDL_MSG_BOX("Config version change. Will need to reset config. Found version [%s]. Expected version [%s].",
                  game->config.version.c_str(), version.c_str());
      delete game;
      game = new Game(std::string(appdata));
      reset_globals();
      game->save_config();
      g_errored = false;
    } else if (! config_error.empty()) {
      SDL_MSG_BOX("Config error: %s. Will need to reset config.", config_error.c_str());
      delete game;
      reset_globals();
      game = new Game(std::string(appdata));
      game->save_config();
      g_errored = false;
    }
  }

  {
    if (! sdl_init()) {
      ERR("SDL: Init");
    }
  }

  //
  // For some reason this is needed on windows to force the console
  // to appear.
  //
  auto save_gfx_vsync_locked    = game->config.gfx_vsync_locked;
  game->config.gfx_vsync_locked = 1;

  //
  // Check for overrides.
  //
  if (g_opt_ascii_override) {
    parse_args(argc, argv);
  }

  TRACE_NO_INDENT();
  sdl_config_update_all();

  {
    TRACE_NO_INDENT();
    if (g_need_restart) {
      restart();
    }
  }

  {
    TRACE_NO_INDENT();
    gl_init_2d_mode();
  }

  //
  // Disable vsync so the console is faster
  //
  {
    TRACE_NO_INDENT();
    SDL_GL_SetSwapInterval(0);
  }

  {
    TRACE_NO_INDENT();
    CON("INI: Load early gfx tiles, text, UI etc...");
    gfx_init();
    LOG("INI: Loaded");
  }

  //
  // Random number
  //
  LOG("INI: Init random seed");
  non_pcg_srand((unsigned int) std::time(nullptr));

  color_init();

#if 0
  extern int grid_test(void);
  grid_test();
  int x = 1;
  if (x) {
  DIE("X");
  }
#endif

  {
    TRACE_NO_INDENT();
    CON("INI: Load fonts");
    if (! font_init()) {
      ERR("Font init");
    }
    LOG("INI: Loaded");
  }

  {
    TRACE_NO_INDENT();
    CON("INI: Load widgets");
    if (! wid_init()) {
      ERR("Wid init");
    }
    LOG("INI: Loaded");
  }

  {
    TRACE_NO_INDENT();
    CON("INI: Load console");
    if (! wid_console_init()) {
      ERR("Wid_console init");
    }
    LOG("INI: Loaded");
    wid_toggle_hidden(wid_console_window);
    flush_the_console();
  }

  //
  // Need to preserve spaces for restarting via exec
  //
  {
    TRACE_NO_INDENT();
    original_program_name = std::string(argv[ 0 ]);
    CON("INI: Original program name: %s", original_program_name.c_str());
    flush_the_console();
  }

  {
    TRACE_NO_INDENT();
    CON("INI: Load tiles");
    if (! wid_tiles_init()) {
      ERR("Wid tiles init");
    }
  }

  {
  }
  TRACE_NO_INDENT();
  if (! tile_init()) {
    ERR("Tile init");
  }
  LOG("INI: Loaded");
  flush_the_console();

  {
    TRACE_NO_INDENT();
    CON("INI: Load textures");
    if (! tex_init()) {
      ERR("Tex init");
    }
    LOG("INI: Loaded");
    flush_the_console();
  }

  {
    TRACE_NO_INDENT();
    CON("INI: Load audio");
    if (! audio_init()) {
      ERR("Audio init");
    }
    LOG("INI: Loaded");
    flush_the_console();
  }

  {
    TRACE_NO_INDENT();
    CON("INI: Load music");
    if (! music_init()) {
      ERR("Music init");
    }
    LOG("INI: Loaded");
    flush_the_console();
  }

  {
    TRACE_NO_INDENT();
    CON("INI: Load sound");
    if (! sound_init()) {
      ERR("Sound init");
    }
    LOG("INI: Loaded");
    flush_the_console();
  }

  {
    TRACE_NO_INDENT();
    LOG("INI: Init UI topcon");
    if (! wid_topcon_init()) {
      ERR("Wid_topcon init");
    }
  }

  {
    TRACE_NO_INDENT();
    LOG("INI: Init UI actionar");
    wid_actionbar_init();
  }

  {
    TRACE_NO_INDENT();
    LOG("INI: Init UI botcon");
    if (! wid_botcon_init()) {
      ERR("Wid_botcon init");
    }
  }

  {
    TRACE_NO_INDENT();
    LOG("INI: Find resource locations for gfx and music");
    find_file_locations();
    flush_the_console();
  }

  {
    TRACE_NO_INDENT();
    CON("INI: Load commands");
    if (! command_init()) {
      ERR("Command init");
    }
    LOG("INI: Loaded");
    flush_the_console();
  }

  {
    TRACE_NO_INDENT();
    CON("INI: Load dungeon character maps");
    Charmap::init_charmaps();
    LOG("INI: Loaded");
    flush_the_console();
  }

  {
    TRACE_NO_INDENT();
    CON("INI: Load python");
    py_init(argv);
    if (g_errored) {
      goto loop;
    }
    LOG("INI: Loaded");
    flush_the_console();
  }

  {
    TRACE_NO_INDENT();
    CON("INI: Load python modules");
    pcg_random_allowed++;
    py_call_void("init2");
    pcg_random_allowed--;
    LOG("INI: Loaded");
    flush_the_console();
  }

  {
    TRACE_NO_INDENT();
    CON("INI: Load monsters");
    pcg_random_allowed++;
    tp_init();
    pcg_random_allowed--;
    if (g_errored) {
      goto loop;
    }
    LOG("INI: Loaded");
    flush_the_console();

    if (g_opt_dump_monsters) {
      TRACE_NO_INDENT();
      wid_toggle_hidden(wid_console_window);
      tp_dump_monsters();
      quit();
      return 0;
    }

    if (g_opt_dump_weapons) {
      TRACE_NO_INDENT();
      wid_toggle_hidden(wid_console_window);
      tp_dump_weapons();
      quit();
      return 0;
    }
  }

  //
  // Create a fresh game if none was loaded
  //
  {
    TRACE_NO_INDENT();
    CON("INI: Load rooms");
    pcg_random_allowed++;
    room_init();
    pcg_random_allowed--;
    if (g_errored) {
      goto loop;
    }
    LOG("INI: Loaded");
    flush_the_console();
  }

  {
    TRACE_NO_INDENT();
    wid_topcon_flush();
    wid_botcon_flush();
    flush_the_console();

    //
    // Now all templates are loaded, make sure we have some default config.
    // for example, for bodyparts.
    //
    {
      TRACE_NO_INDENT();
      pcg_random_allowed++;
      game->config.final_init();
      pcg_random_allowed--;
    }

    if (g_opt_tests) {
      //
      // Run tests
      //
      TRACE_NO_INDENT();
      wid_toggle_hidden(wid_console_window);
    } else {
      //
      // Main menu
      //
      TRACE_NO_INDENT();
      if (g_opt_test_skip_main_menu) {
        CON("INI: New game");
        game->new_game();
      } else {
        CON("INI: Game menu");
        game->wid_main_menu_select();
      }

      if (g_opt_resume) {
        CON("INI: Load last snapshot");
        game->load_snapshot();
      }
    }
    flush_the_console();
  }

loop:

  wid_hide(wid_console_window);

  game->config.gfx_vsync_locked = save_gfx_vsync_locked;
  config_gfx_vsync_update();

  g_opt_no_slow_log_flush = false;

  TRACE_NO_INDENT();
  sdl_loop();
  LOG("FIN: SDL loop finished");
  flush_the_console();

  if (g_need_restart) {
    g_need_restart = false;
#ifdef _WIN32
    restart();
#else
    CON("FIN: Restart");
    execv(argv[ 0 ], argv);
#endif
  }

  LOG("FIN: Leave 2D mode");
  gl_leave_2d_mode();

  CON("FIN: Quit");
  quit();

  CON("FIN: Goodbye my friend and take care until next time!");
  return 0;
}
