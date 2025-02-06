import my
import os
import fnmatch
from os.path import dirname, basename
import sys

if sys.version_info[0] == 3:
    if sys.version_info[1] >= 5:
        import importlib.util
    elif sys.version_info[1] < 5:
        import importlib.machinery
elif sys.version_info[0] == 2:
    import imp

# import sys
import console
import time

# import logging
# import datetime

timeme_enabled = False

#
# Unused
#
# def my_formatter(verbosity=logging.INFO):
#     format_string = "%(asctime)s.%(msecs)03d "
#     format_string += "init.py: "
#     datefmt = "%d-%m-%Y %H:%M:%S"
#     format_string += "%(levelname)4s: "
#     format_string += "%(message)s"
#     return logging.Formatter(format_string, datefmt=datefmt)
#
# def my_logger:
#     log_handler = logging.StreamHandler()
#     log_handler.setLevel(logging.INFO)
#     log_handler.setFormatter(my_formatter(logging.DEBUG))
#     log_handler.setFormatter(my_formatter(logging.ERROR))
#     log_handler.setFormatter(my_formatter(logging.INFO))
#
#     logger = logging.getLogger(__name__)
#     logger.addHandler(log_handler)
#     logger.setLevel(logging.INFO)
#     logger.propagate = False  # avoid multiple logs:
#
# def my_arger:
#     arger = argparse.ArgumentParser()
#     arger.add_argument("--debug", default=False, action='store_true')
#     args = arger.parse_args(args)
#
# def unused:
#     my_logger()
#     my_arger()


def timeme(py_function):
    def timeme_wrapper(*args, **kwargs):
        global timeme_enabled
        if not timeme_enabled:
            return py_function(*args, **kwargs)

        start_time = time.time()
        return_code = py_function(*args, **kwargs)
        end_time = time.time()
        print(f"PYC: perf {py_function.__name__:s}({args}) {(end_time - start_time) * 1000.0:.3f} ms")
        return return_code

    return timeme_wrapper


def find_plugins(directory, pattern):
    all_files = []
    for root, dirs, files in os.walk(directory):
        for f in sorted(files):
            if fnmatch.fnmatch(f, pattern):
                filename = os.path.normcase(os.path.join(root, f))
                all_files.append(filename)

    all_files.sort()
    for f in all_files:
        yield f


@timeme
def load_one_plugin(filename):
    if "rollbackBackupDirectory" in filename:
        return

    if basename(filename) == "init.py":
        return

    if basename(filename) == "tp.py":
        return

    my.log("PYC: - loading init plugin: " + filename)

    mod_name, file_ext = os.path.splitext(os.path.split(filename)[-1])

    if file_ext.lower() == ".py":
        if sys.version_info[0] == 3:
            if sys.version_info[1] >= 5:
                spec = importlib.util.spec_from_file_location(mod_name, filename)
                module = importlib.util.module_from_spec(spec)
                spec.loader.exec_module(module)
            elif sys.version_info[1] < 5:
                loader = importlib.machinery.SourceFileLoader(mod_name, filename)
                loader.load_module()
        elif sys.version_info[0] == 2:
            imp.load_source(mod_name, filename)
        # load_source(mod_name, filename)

    elif file_ext.lower() == ".pyc":
        imp.load_compiled(mod_name, filename)


@timeme
def load_all_plugins():

    paths = [
        'things/keys',
        'things/mobs',
        'things/staffs',
        'things/armor',
        'things/monsters',
        'things/amulets',
        'things/traps',
        'things/player',
        'things/lasers',
        'things/bodyparts',
        'things/spells',
        'things/skills',
        'things/projectiles',
        'things/weapons',
        'things/debuffs',
        'things/food',
        'things/treasure',
        'things/buffs',
        'things/totem',
        'things/shield',
        'things/internal',
        'things/gauntlets',
        'things/effects',
        'things/boots',
        'things/items',
        'things/dungeon',
        'things/rings',
        'things/containers',
        'things/fungus',
        'things/cloaks',
        'things/potions',
        'things/doors',
    ]

    plug_path = os.path.normcase(os.path.join(dirname(__file__), ""))

    for path in paths:
        my.log("PYC: Add path " + os.path.join(plug_path, path))
        sys.path.append(os.path.join(plug_path, path))

    my.log("PYC: Init module, load all plugins from " + plug_path)
    for filename in find_plugins(plug_path, "*.py"):
        load_one_plugin(filename)


@timeme
def load_plugin(plugin):
    for filename in find_plugins(os.getcwd(), plugin):
        load_one_plugin(filename)


@timeme
def init1():
    my.log(f"PYC: Init module: running in: {os.getcwd()}")


def init2():
    load_all_plugins()
    console.hello()


init1()
