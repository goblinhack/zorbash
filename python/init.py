import zx
import os
import fnmatch
from os.path import dirname, basename
import imp
import sys
import console


def find_plugins(directory, pattern):
    for root, dirs, files in os.walk(directory):
        for f in files:
            if fnmatch.fnmatch(f, pattern):
                filename = os.path.normcase(os.path.join(root, f))
                yield filename


def load_one_plugin(filename):
    if "rollbackBackupDirectory" in filename:
        return

    if basename(filename) == "init.py":
        return

    if basename(filename) == "tp.py":
        return

    zx.log("- loading init plugin: " + filename)

    mod_name, file_ext = os.path.splitext(os.path.split(filename)[-1])

    if file_ext.lower() == '.py':
        py_mod = imp.load_source(mod_name, filename)

    elif file_ext.lower() == '.pyc':
        py_mod = imp.load_compiled(mod_name, filename)

    #
    # Make aliases for imports so we can reference their functions
    #
    if basename(filename) == "my-config.py":
        global config
        config = py_mod

    if basename(filename) == "hooks.py":
        global hooks
        hooks = py_mod

    if basename(filename) == "game.py":
        global game
        game = py_mod


def load_all_plugins():
    plug_path = os.path.normcase(os.path.join(dirname(__file__), ""))
    zx.log("Init module, load all plugins from " + plug_path)
    for filename in find_plugins(plug_path, '*.py'):
        load_one_plugin(filename)


def load_plugin(plugin):
    for filename in find_plugins(os.getcwd(), plugin):
        load_one_plugin(filename)

    for filename in find_plugins(os.environ["APPDATA"], plugin):
        load_one_plugin(filename)


def init1():

    zx.con("Init module: running in: {}".format(os.getcwd()))

    if "APPDATA" not in os.environ:
        os.environ['APPDATA'] = "appdata"

    if not os.path.isdir(os.environ['APPDATA']):
        os.mkdir(os.environ['APPDATA'])

    os.environ['APPDATA'] = os.path.normcase(
            os.path.join(os.environ["APPDATA"], "zorbash"))

    if not os.path.isdir(os.environ['APPDATA']):
        os.mkdir(os.environ['APPDATA'])

    sys.stdout = open(os.path.normcase(
            os.path.join(os.environ["APPDATA"], "stdout.txt")), "a")

    sys.stderr = open(os.path.normcase(
            os.path.join(os.environ["APPDATA"], "stderr.txt")), "a")

    """ game defaults """
    zx.game_video_pix_width = 0
    zx.game_video_pix_height = 0
    zx.game_sound_volume = 10
    zx.game_music_volume = 5
    zx.game_display_sync = 1
    zx.game_full_screen = 0
    zx.game_fps_counter = 1
    zx.game_set_sdl_delay(0)
    zx.game_set_display_sync(1)

    load_plugin('my-config.py')
    load_plugin('zorbash-config.py')
    config.save_game_config()


def init2():

    load_all_plugins()

    (tile_width, tile_height) = zx.tile_size(name="door1")
    zx.game_tile_width = int(tile_width)
    zx.game_tile_height = int(tile_height)

    game.game_init()
    game.game_new_or_restore()

    zx.tip2("Welcome mortal, to Zorbash version " + zx.VERSION)
    console.hello()

init1()
