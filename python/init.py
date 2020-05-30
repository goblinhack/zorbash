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

    zx.log("PYTHON: - loading init plugin: " + filename)

    mod_name, file_ext = os.path.splitext(os.path.split(filename)[-1])

    if file_ext.lower() == '.py':
        py_mod = imp.load_source(mod_name, filename)

        #for attr_name in dir(py_mod):
        #    attr_value = getattr(py_mod, attr_name)
        #    print(attr_name, attr_value, callable(attr_value))

    elif file_ext.lower() == '.pyc':
        py_mod = imp.load_compiled(mod_name, filename)

def load_all_plugins():
    plug_path = os.path.normcase(os.path.join(dirname(__file__), ""))
    zx.con("PYTHON: Init module, load all plugins from " + plug_path)
    for filename in find_plugins(plug_path, '*.py'):
        load_one_plugin(filename)


def load_plugin(plugin):
    for filename in find_plugins(os.getcwd(), plugin):
        load_one_plugin(filename)

def init1():

    zx.con("PYTHON: Init module: running in: {}".format(os.getcwd()))

def init2():

    load_all_plugins()

    zx.minicon("Welcome mortal, to Zorbash version " + zx.VERSION)
    console.hello()

init1()
