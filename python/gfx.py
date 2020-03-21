import zx


def init_solid():
    zx.tex_load(file="data/gfx/solid.tga", name="solid")


def init_light():
    zx.tex_load(file="data/gfx/light.tga", name="light")


def init_64x16_ui():
    tiles = [
        "status-bar-11",
        "status-bar-10",
        "status-bar-9",
        "status-bar-8",
        "status-bar-7",
        "status-bar-6",
        "status-bar-5",
        "status-bar-4",
        "status-bar-3",
        "status-bar-2",
        "status-bar-1",
        "status-bar-0",
        "karma-status",
        "health-status",
        "defence-status",
        "magick-status",
        "anxiety-status",
        "attack-status",
        "zorbash-0",
        "zorbash-1",
        "zorbash-2",
        "blessings-0",
        "blessings-1",
        "curses-0",
        "curses-1",
        "curses-2",
        "inventory-0",
        "inventory-1",
        "inventory-2",
        "inventory-3",
        "inventory-4",
        "inventory-5",
        "karma-bar-11",
        "karma-bar-10",
        "karma-bar-9",
        "karma-bar-8",
        "karma-bar-7",
        "karma-bar-6",
        "karma-bar-5",
        "karma-bar-4",
        "karma-bar-3",
        "karma-bar-2",
        "karma-bar-1",
        "karma-bar-0",
    ]
    zx.tile_load_arr(
        file="data/gfx/ui_status_bar.tga",
        name="ui_status_bar", width=96, height=16, arr=tiles)

def init_title():
    tiles = [
        "title1", "title2", "title3", "title4",
        "title5", "title6", "title7", "title8",
        "title9", "title10", "title11", "title12",
        "title13", "title14", "title15", "title16",
        "title17", "title18", "title19", "title20",
        "title21", "title22", "title23", "title24",
        "title25", "title26", "title27", "title28",
        "title29", "title30", "title31", "title32",
        "title33", "title34", "title35", "title36",
        "title37", "title38", "title39", "title40",
        "title41", "title42", "title43", "title44",
        "title45", "title46", "title47", "title48",
        "title49", "title50", "title51", "title52",
        "title53", "title54", "title55", "title56",
        "title57", "title58", "title59", "title60",
        "title61", "title62", "title63", "title64",
    ]
    zx.tile_load_arr(
        file="data/gfx/zorbash.tga",
        name="title", width=112, height=84, arr=tiles)

def init_ui_dead():
    tiles = [
        "ui_dead",
    ]
    zx.tile_load_arr(
        file="data/gfx/rip.tga",
        name="ui_dead", width=80, height=100, arr=tiles)

def init_ui_action_bar():
    tiles = [
        "ui_action_bar",
    ]
    zx.tile_load_arr(
        file="data/gfx/ui_action_bar.tga",
        name="ui_action_bar", width=320, height=32, arr=tiles)

def init_16x16():
    tiles = [
            "player1.1", "player1.2", "player1.3", "player1.4", "player1.5", "player1.6", "", "player1.pose", "player1.dead", "sword1.1", "save", "load", "bug", "pause", "dead", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
            ########################################################
            "gem1.1", "gem1.2", "gem1.3", "gem1.4", "gem1.5", "gem1.6", "gem1.7", "slime1.1.100", "slime1.2.100", "slime1.3.100", "slime1.4.100", "slime1.1.75", "slime1.2.75", "slime1.3.75", "slime1.4.75", "slime1.1.50", "slime1.2.50", "slime1.3.50", "slime1.4.50", "slime1.1.25", "slime1.2.25", "slime1.3.25", "slime1.4.25", "slime1.dead", "", "", "", "key1.1", "key1.2", "key1.3", "key1.4", "key1.5",
            ########################################################
            "blood1a", "blood1.100", "blood2.100", "blood3.100", "blood4.100", "", "", "mummy1.1.100", "mummy1.2.100", "mummy1.3.100", "mummy1.1.dead", "mummy1.2.dead", "mummy1.3.dead", "mummy1.4.dead", "mummy1.5.dead", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
            ########################################################
            "", "blood1.75", "blood2.75", "blood3.75", "blood4.75", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
            ########################################################
            "", "blood1.50", "blood2.50", "blood3.50", "blood4.50", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
            ########################################################
            "", "blood1.25", "blood2.25", "blood3.25", "blood4.25", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
            ########################################################
            "food_frog1", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
            ########################################################
            "health5-icon", "health4-icon", "health3-icon", "health2-icon", "health1-icon", "dollar-icon", "defence-icon", "magic-icon", "karma-icon", "anxiety5-icon", "anxiety4-icon", "anxiety3-icon", "anxiety2-icon", "anxiety1-icon", "attack-icon", "cursor.1", "cursor.2", "cursor.3", "cursor.4", "cursor.5", "cursor.6", "cursor.7", "cursor.8", "cursor.9", "cursor.10", "cursor.11", "cursor.12", "cursor_path.1", "", "", "", "",
            ########################################################
            "floor3.1", "floor3.2", "floor3.3", "floor3.4", "floor3.5", "floor3.6", "floor3.7", "floor3.8", "floor3.9", "floor3.10", "floor3.11", "floor3.12", "floor3.13", "floor3.14", "floor3.15", "floor3.16", "floor3.17", "floor3.18", "floor3.19", "floor3.20", "floor3.21", "floor3.22", "floor3.23", "floor3.24", "floor3.25", "floor3.26", "floor3.27", "floor3.28", "floor3.29", "floor3.30", "floor3.31", "floor3.32",
            "floor4.1", "floor4.2", "floor4.3", "floor4.4", "floor4.5", "floor4.6", "floor4.7", "floor4.8", "floor4.9", "floor4.10", "floor4.11", "floor4.12", "floor4.13", "floor4.14", "floor4.15", "floor4.16", "floor4.17", "floor4.18", "floor4.19", "floor4.20", "floor4.21", "floor4.22", "floor4.23", "floor4.24", "floor4.25", "floor4.26", "floor4.27", "floor4.28", "floor4.29", "floor4.30", "floor4.31", "floor4.32",
            "floor5.1", "floor5.2", "floor5.3", "floor5.4", "floor5.5", "floor5.6", "floor5.7", "floor5.8", "floor5.9", "floor5.10", "floor5.11", "floor5.12", "floor5.13", "floor5.14", "floor5.15", "floor5.16", "floor5.17", "floor5.18", "floor5.19", "floor5.20", "floor5.21", "floor5.22", "floor5.23", "floor5.24", "floor5.25", "floor5.26", "floor5.27", "floor5.28", "floor5.29", "floor5.30", "floor5.31", "floor5.32",
            "floor6.1", "floor6.2", "floor6.3", "floor6.4", "floor6.5", "floor6.6", "floor6.7", "floor6.8", "floor6.9", "floor6.10", "floor6.11", "floor6.12", "floor6.13", "floor6.14", "floor6.15", "floor6.16", "floor6.17", "floor6.18", "floor6.19", "floor6.20", "floor6.21", "floor6.22", "floor6.23", "floor6.24", "floor6.25", "floor6.26", "floor6.27", "floor6.28", "floor6.29", "floor6.30", "floor6.31", "floor6.32",
            "floor7.1", "floor7.2", "floor7.3", "floor7.4", "floor7.5", "floor7.6", "floor7.7", "floor7.8", "floor7.9", "floor7.10", "floor7.11", "floor7.12", "floor7.13", "floor7.14", "floor7.15", "floor7.16", "floor7.17", "floor7.18", "floor7.19", "floor7.20", "floor7.21", "floor7.22", "floor7.23", "floor7.24", "floor7.25", "floor7.26", "floor7.27", "floor7.28", "floor7.29", "floor7.30", "floor7.31", "floor7.32",
            "floor8.1", "floor8.2", "floor8.3", "floor8.4", "floor8.5", "floor8.6", "floor8.7", "floor8.8", "floor8.9", "floor8.10", "floor8.11", "floor8.12", "floor8.13", "floor8.14", "floor8.15", "floor8.16", "floor8.17", "floor8.18", "floor8.19", "floor8.20", "floor8.21", "floor8.22", "floor8.23", "floor8.24", "floor8.25", "floor8.26", "floor8.27", "floor8.28", "floor8.29", "floor8.30", "floor8.31", "floor8.32",
            "floor9.1", "floor9.2", "floor9.3", "floor9.4", "floor9.5", "floor9.6", "floor9.7", "floor9.8", "floor9.9", "floor9.10", "floor9.11", "floor9.12", "floor9.13", "floor9.14", "floor9.15", "floor9.16", "floor9.17", "floor9.18", "floor9.19", "floor9.20", "floor9.21", "floor9.22", "floor9.23", "floor9.24", "floor9.25", "floor9.26", "floor9.27", "floor9.28", "floor9.29", "floor9.30", "floor9.31", "floor9.32",
            "corridor1.1", "corridor1.2", "corridor1.3", "corridor1.4", "corridor1.5", "corridor1.6", "corridor1.7", "corridor1.8", "corridor1.9", "corridor1.10", "corridor1.11", "corridor1.12", "corridor1.13", "corridor1.14", "corridor1.15", "corridor1.16", "corridor1.17", "corridor1.18", "corridor1.19", "corridor1.20", "corridor1.21", "corridor1.22", "corridor1.23", "corridor1.24", "corridor1.25", "corridor1.26", "corridor1.27", "corridor1.28", "corridor1.29", "corridor1.30", "corridor1.31", "corridor1.32",
            "dirt1.1", "dirt1.2", "dirt1.3", "dirt1.4", "dirt1.5", "dirt1.6", "dirt1.7", "dirt1.8", "dirt1.9", "dirt1.10", "dirt1.11", "dirt1.12", "dirt1.13", "dirt1.14", "dirt1.15", "dirt1.16", "dirt1.17", "dirt1.18", "dirt1.19", "dirt1.20", "dirt1.21", "dirt1.22", "dirt1.23", "dirt1.24", "dirt1.25", "dirt1.26", "dirt1.27", "dirt1.28", "dirt1.29", "dirt1.30", "dirt1.31", "dirt1.32",
            "dirt2.1", "dirt2.2", "dirt2.3", "dirt2.4", "dirt2.5", "dirt2.6", "dirt2.7", "dirt2.8", "dirt2.9", "dirt2.10", "dirt2.11", "dirt2.12", "dirt2.13", "dirt2.14", "dirt2.15", "dirt2.16", "dirt2.17", "dirt2.18", "dirt2.19", "dirt2.20", "dirt2.21", "dirt2.22", "dirt2.23", "dirt2.24", "dirt2.25", "dirt2.26", "dirt2.27", "dirt2.28", "dirt2.29", "dirt2.30", "dirt2.31", "dirt2.32",
            "dirt3.1", "dirt3.2", "dirt3.3", "dirt3.4", "dirt3.5", "dirt3.6", "dirt3.7", "dirt3.8", "dirt3.9", "dirt3.10", "dirt3.11", "dirt3.12", "dirt3.13", "dirt3.14", "dirt3.15", "dirt3.16", "dirt3.17", "dirt3.18", "dirt3.19", "dirt3.20", "dirt3.21", "dirt3.22", "dirt3.23", "dirt3.24", "dirt3.25", "dirt3.26", "dirt3.27", "dirt3.28", "dirt3.29", "dirt3.30", "dirt3.31", "dirt3.32",
            ########################################################
            "floor1.1.2x1.1", "floor1.1.2x1.2", "floor1.1.6x6.1", "floor1.1.6x6.2", "floor1.1.6x6.3", "floor1.1.6x6.4", "floor1.1.6x6.5", "floor1.1.6x6.6", "floor1.1.6x3.1", "floor1.1.6x3.2", "floor1.1.6x3.3", "floor1.1.6x3.4", "floor1.1.6x3.5", "floor1.1.6x3.6", "floor1.1.3x6.1", "floor1.1.3x6.2", "floor1.1.3x6.3", "floor1.1.2x2.1", "floor1.1.2x2.2", "", "", "", "", "", "", "", "", "", "", "", "", "",
            "floor1.1.1x2.1", "floor1.2.1x2.1", "floor1.1.6x6.7", "floor1.1.6x6.8", "floor1.1.6x6.9", "floor1.1.6x6.10", "floor1.1.6x6.11", "floor1.1.6x6.12", "floor1.1.6x3.7", "floor1.1.6x3.8", "floor1.1.6x3.9", "floor1.1.6x3.10", "floor1.1.6x3.11", "floor1.1.6x3.12", "floor1.1.3x6.4", "floor1.1.3x6.5", "floor1.1.3x6.6", "floor1.1.2x2.3", "floor1.1.2x2.4", "", "", "", "", "", "", "", "", "", "", "", "", "",
            "floor1.1.1x2.2", "floor1.2.1x2.2", "floor1.1.6x6.13", "floor1.1.6x6.14", "floor1.1.6x6.15", "floor1.1.6x6.16", "floor1.1.6x6.17", "floor1.1.6x6.18", "floor1.1.6x3.13", "floor1.1.6x3.14", "floor1.1.6x3.15", "floor1.1.6x3.16", "floor1.1.6x3.17", "floor1.1.6x3.18", "floor1.1.3x6.7", "floor1.1.3x6.8", "floor1.1.3x6.9", "floor1.2.2x2.1", "floor1.2.2x2.2", "", "", "", "", "", "", "", "", "", "", "", "", "",
            "floor1.2.2x1.1", "floor1.2.2x1.2", "floor1.1.6x6.19", "floor1.1.6x6.20", "floor1.1.6x6.21", "floor1.1.6x6.22", "floor1.1.6x6.23", "floor1.1.6x6.24", "floor1.1.3x3.1", "floor1.1.3x3.2", "floor1.1.3x3.3", "floor1.2.3x3.1", "floor1.2.3x3.2", "floor1.2.3x3.3", "floor1.1.3x6.10", "floor1.1.3x6.11", "floor1.1.3x6.12", "floor1.2.2x2.3", "floor1.2.2x2.4", "", "", "", "", "", "", "", "", "", "", "", "", "",
            "floor1.3.2x1.1", "floor1.3.2x1.2", "floor1.1.6x6.25", "floor1.1.6x6.26", "floor1.1.6x6.27", "floor1.1.6x6.28", "floor1.1.6x6.29", "floor1.1.6x6.30", "floor1.1.3x3.4", "floor1.1.3x3.5", "floor1.1.3x3.6", "floor1.2.3x3.4", "floor1.2.3x3.5", "floor1.2.3x3.6", "floor1.1.3x6.13", "floor1.1.3x6.14", "floor1.1.3x6.15", "floor1.3.2x2.1", "floor1.3.2x2.2", "", "", "", "", "", "", "", "", "", "", "", "", "",
            "floor1.4.2x1.1", "floor1.4.2x1.2", "floor1.1.6x6.31", "floor1.1.6x6.32", "floor1.1.6x6.33", "floor1.1.6x6.34", "floor1.1.6x6.35", "floor1.1.6x6.36", "floor1.1.3x3.7", "floor1.1.3x3.8", "floor1.1.3x3.9", "floor1.2.3x3.7", "floor1.2.3x3.8", "floor1.2.3x3.9", "floor1.1.3x6.16", "floor1.1.3x6.17", "floor1.1.3x6.18", "floor1.3.2x2.3", "floor1.3.2x2.4", "", "", "", "", "", "", "", "", "", "", "", "", "",
            "floor1.1", "floor1.2", "floor1.3", "floor1.4", "floor1.5", "floor1.6", "floor1.7", "floor1.8", "floor1.9", "floor1.10", "floor1.11", "floor1.12", "floor1.13", "floor1.14", "floor1.15", "floor1.16", "floor1.17", "floor1.18", "floor1.19", "floor1.20", "floor1.21", "floor1.22", "floor1.23", "floor1.24", "floor1.25", "floor1.26", "floor1.27", "floor1.28", "floor1.29", "floor1.30", "floor1.31", "floor1.32",
            ########################################################
            "floor2.1.2x1.1", "floor2.1.2x1.2", "floor2.1.6x6.1", "floor2.1.6x6.2", "floor2.1.6x6.3", "floor2.1.6x6.4", "floor2.1.6x6.5", "floor2.1.6x6.6", "floor2.1.6x3.1", "floor2.1.6x3.2", "floor2.1.6x3.3", "floor2.1.6x3.4", "floor2.1.6x3.5", "floor2.1.6x3.6", "floor2.1.3x6.1", "floor2.1.3x6.2", "floor2.1.3x6.3", "floor2.1.2x2.1", "floor2.1.2x2.2", "", "", "", "", "", "", "", "", "", "", "", "", "",
            "floor2.1.1x2.1", "floor2.2.1x2.1", "floor2.1.6x6.7", "floor2.1.6x6.8", "floor2.1.6x6.9", "floor2.1.6x6.10", "floor2.1.6x6.11", "floor2.1.6x6.12", "floor2.1.6x3.7", "floor2.1.6x3.8", "floor2.1.6x3.9", "floor2.1.6x3.10", "floor2.1.6x3.11", "floor2.1.6x3.12", "floor2.1.3x6.4", "floor2.1.3x6.5", "floor2.1.3x6.6", "floor2.1.2x2.3", "floor2.1.2x2.4", "", "", "", "", "", "", "", "", "", "", "", "", "",
            "floor2.1.1x2.2", "floor2.2.1x2.2", "floor2.1.6x6.13", "floor2.1.6x6.14", "floor2.1.6x6.15", "floor2.1.6x6.16", "floor2.1.6x6.17", "floor2.1.6x6.18", "floor2.1.6x3.13", "floor2.1.6x3.14", "floor2.1.6x3.15", "floor2.1.6x3.16", "floor2.1.6x3.17", "floor2.1.6x3.18", "floor2.1.3x6.7", "floor2.1.3x6.8", "floor2.1.3x6.9", "floor2.2.2x2.1", "floor2.2.2x2.2", "", "", "", "", "", "", "", "", "", "", "", "", "",
            "floor2.2.2x1.1", "floor2.2.2x1.2", "floor2.1.6x6.19", "floor2.1.6x6.20", "floor2.1.6x6.21", "floor2.1.6x6.22", "floor2.1.6x6.23", "floor2.1.6x6.24", "floor2.1.3x3.1", "floor2.1.3x3.2", "floor2.1.3x3.3", "floor2.2.3x3.1", "floor2.2.3x3.2", "floor2.2.3x3.3", "floor2.1.3x6.10", "floor2.1.3x6.11", "floor2.1.3x6.12", "floor2.2.2x2.3", "floor2.2.2x2.4", "", "", "", "", "", "", "", "", "", "", "", "", "",
            "floor2.3.2x1.1", "floor2.3.2x1.2", "floor2.1.6x6.25", "floor2.1.6x6.26", "floor2.1.6x6.27", "floor2.1.6x6.28", "floor2.1.6x6.29", "floor2.1.6x6.30", "floor2.1.3x3.4", "floor2.1.3x3.5", "floor2.1.3x3.6", "floor2.2.3x3.4", "floor2.2.3x3.5", "floor2.2.3x3.6", "floor2.1.3x6.13", "floor2.1.3x6.14", "floor2.1.3x6.15", "floor2.3.2x2.1", "floor2.3.2x2.2", "", "", "", "", "", "", "", "", "", "", "", "", "",
            "floor2.4.2x1.1", "floor2.4.2x1.2", "floor2.1.6x6.31", "floor2.1.6x6.32", "floor2.1.6x6.33", "floor2.1.6x6.34", "floor2.1.6x6.35", "floor2.1.6x6.36", "floor2.1.3x3.7", "floor2.1.3x3.8", "floor2.1.3x3.9", "floor2.2.3x3.7", "floor2.2.3x3.8", "floor2.2.3x3.9", "floor2.1.3x6.16", "floor2.1.3x6.17", "floor2.1.3x6.18", "floor2.3.2x2.3", "floor2.3.2x2.4", "", "", "", "", "", "", "", "", "", "", "", "", "",
            "floor2.1", "floor2.2", "floor2.3", "floor2.4", "floor2.5", "floor2.6", "floor2.7", "floor2.8", "floor2.9", "floor2.10", "floor2.11", "floor2.12", "floor2.13", "floor2.14", "floor2.15", "floor2.16", "floor2.17", "floor2.18", "floor2.19", "floor2.20", "floor2.21", "floor2.22", "floor2.23", "floor2.24", "floor2.25", "floor2.26", "floor2.27", "floor2.28", "floor2.29", "floor2.30", "floor2.31", "floor2.32",
            ########################################################
            "wall1.1.2x1.1", "wall1.1.2x1.2", "wall1.1.6x6.1", "wall1.1.6x6.2", "wall1.1.6x6.3", "wall1.1.6x6.4", "wall1.1.6x6.5", "wall1.1.6x6.6", "wall1.1.6x3.1", "wall1.1.6x3.2", "wall1.1.6x3.3", "wall1.1.6x3.4", "wall1.1.6x3.5", "wall1.1.6x3.6", "wall1.1.3x6.1", "wall1.1.3x6.2", "wall1.1.3x6.3", "wall1.1.2x2.1", "wall1.1.2x2.2", "", "", "", "", "", "", "", "", "", "", "", "", "",
            "wall1.1.1x2.1", "wall1.2.1x2.1", "wall1.1.6x6.7", "wall1.1.6x6.8", "wall1.1.6x6.9", "wall1.1.6x6.10", "wall1.1.6x6.11", "wall1.1.6x6.12", "wall1.1.6x3.7", "wall1.1.6x3.8", "wall1.1.6x3.9", "wall1.1.6x3.10", "wall1.1.6x3.11", "wall1.1.6x3.12", "wall1.1.3x6.4", "wall1.1.3x6.5", "wall1.1.3x6.6", "wall1.1.2x2.3", "wall1.1.2x2.4", "", "", "", "", "", "", "", "", "", "", "", "", "",
            "wall1.1.1x2.2", "wall1.2.1x2.2", "wall1.1.6x6.13", "wall1.1.6x6.14", "wall1.1.6x6.15", "wall1.1.6x6.16", "wall1.1.6x6.17", "wall1.1.6x6.18", "wall1.1.6x3.13", "wall1.1.6x3.14", "wall1.1.6x3.15", "wall1.1.6x3.16", "wall1.1.6x3.17", "wall1.1.6x3.18", "wall1.1.3x6.7", "wall1.1.3x6.8", "wall1.1.3x6.9", "wall1.1", "wall1.2", "", "", "", "", "", "", "", "", "", "", "", "", "",
            "wall1.2.2x1.1", "wall1.2.2x1.2", "wall1.1.6x6.19", "wall1.1.6x6.20", "wall1.1.6x6.21", "wall1.1.6x6.22", "wall1.1.6x6.23", "wall1.1.6x6.24", "wall1.1.3x3.1", "wall1.1.3x3.2", "wall1.1.3x3.3", "wall1.2.3x3.1", "wall1.2.3x3.2", "wall1.2.3x3.3", "wall1.1.3x6.10", "wall1.1.3x6.11", "wall1.1.3x6.12", "wall1.3", "wall1.4", "", "", "", "", "", "", "", "", "", "", "", "", "",
            "", "", "wall1.1.6x6.25", "wall1.1.6x6.26", "wall1.1.6x6.27", "wall1.1.6x6.28", "wall1.1.6x6.29", "wall1.1.6x6.30", "wall1.1.3x3.4", "wall1.1.3x3.5", "wall1.1.3x3.6", "wall1.2.3x3.4", "wall1.2.3x3.5", "wall1.2.3x3.6", "wall1.1.3x6.13", "wall1.1.3x6.14", "wall1.1.3x6.15", "wall1.5", "wall1.6", "", "", "", "", "", "", "", "", "", "", "", "", "",
            "", "", "wall1.1.6x6.31", "wall1.1.6x6.32", "wall1.1.6x6.33", "wall1.1.6x6.34", "wall1.1.6x6.35", "wall1.1.6x6.36", "wall1.1.3x3.7", "wall1.1.3x3.8", "wall1.1.3x3.9", "wall1.2.3x3.7", "wall1.2.3x3.8", "wall1.2.3x3.9", "wall1.1.3x6.16", "wall1.1.3x6.17", "wall1.1.3x6.18", "wall1.7", "wall1.8", "", "", "", "", "", "", "", "", "", "", "", "", "",
            ########################################################
            "wall1.3.2x1.1", "wall1.3.2x1.2", "wall1.2.6x6.1", "wall1.2.6x6.2", "wall1.2.6x6.3", "wall1.2.6x6.4", "wall1.2.6x6.5", "wall1.2.6x6.6", "wall1.2.6x3.1", "wall1.2.6x3.2", "wall1.2.6x3.3", "wall1.2.6x3.4", "wall1.2.6x3.5", "wall1.2.6x3.6", "wall1.2.3x6.1", "wall1.2.3x6.2", "wall1.2.3x6.3", "wall1.2.2x2.1", "wall1.2.2x2.2", "", "", "", "", "", "", "", "", "", "", "", "", "",
            "wall1.3.1x2.1", "wall1.4.1x2.1", "wall1.2.6x6.7", "wall1.2.6x6.8", "wall1.2.6x6.9", "wall1.2.6x6.10", "wall1.2.6x6.11", "wall1.2.6x6.12", "wall1.2.6x3.7", "wall1.2.6x3.8", "wall1.2.6x3.9", "wall1.2.6x3.10", "wall1.2.6x3.11", "wall1.2.6x3.12", "wall1.2.3x6.4", "wall1.2.3x6.5", "wall1.2.3x6.6", "wall1.2.2x2.3", "wall1.2.2x2.4", "", "", "", "", "", "", "", "", "", "", "", "", "",
            "wall1.3.1x2.2", "wall1.4.1x2.2", "wall1.2.6x6.13", "wall1.2.6x6.14", "wall1.2.6x6.15", "wall1.2.6x6.16", "wall1.2.6x6.17", "wall1.2.6x6.18", "wall1.2.6x3.13", "wall1.2.6x3.14", "wall1.2.6x3.15", "wall1.2.6x3.16", "wall1.2.6x3.17", "wall1.2.6x3.18", "wall1.2.3x6.7", "wall1.2.3x6.8", "wall1.2.3x6.9", "wall1.9", "wall1.10", "", "", "", "", "", "", "", "", "", "", "", "", "",
            "wall1.4.2x1.1", "wall1.4.2x1.2", "wall1.2.6x6.19", "wall1.2.6x6.20", "wall1.2.6x6.21", "wall1.2.6x6.22", "wall1.2.6x6.23", "wall1.2.6x6.24", "wall1.3.3x3.1", "wall1.3.3x3.2", "wall1.3.3x3.3", "wall1.4.3x3.1", "wall1.4.3x3.2", "wall1.4.3x3.3", "wall1.2.3x6.10", "wall1.2.3x6.11", "wall1.2.3x6.12", "wall1.11", "wall1.12", "", "", "", "", "", "", "", "", "", "", "", "", "",
            "", "", "wall1.2.6x6.25", "wall1.2.6x6.26", "wall1.2.6x6.27", "wall1.2.6x6.28", "wall1.2.6x6.29", "wall1.2.6x6.30", "wall1.3.3x3.4", "wall1.3.3x3.5", "wall1.3.3x3.6", "wall1.4.3x3.4", "wall1.4.3x3.5", "wall1.4.3x3.6", "wall1.2.3x6.13", "wall1.2.3x6.14", "wall1.2.3x6.15", "wall1.13", "wall1.14", "", "", "", "", "", "", "", "", "", "", "", "", "",
            "", "", "wall1.2.6x6.31", "wall1.2.6x6.32", "wall1.2.6x6.33", "wall1.2.6x6.34", "wall1.2.6x6.35", "wall1.2.6x6.36", "wall1.3.3x3.7", "wall1.3.3x3.8", "wall1.3.3x3.9", "wall1.4.3x3.7", "wall1.4.3x3.8", "wall1.4.3x3.9", "wall1.2.3x6.16", "wall1.2.3x6.17", "wall1.2.3x6.18", "wall1.15", "wall1.16", "", "", "", "", "", "", "", "", "", "", "", "", "",
            ########################################################
            "wall2.1.2x1.1", "wall2.1.2x1.2", "wall2.1.6x6.1", "wall2.1.6x6.2", "wall2.1.6x6.3", "wall2.1.6x6.4", "wall2.1.6x6.5", "wall2.1.6x6.6", "wall2.1.6x3.1", "wall2.1.6x3.2", "wall2.1.6x3.3", "wall2.1.6x3.4", "wall2.1.6x3.5", "wall2.1.6x3.6", "wall2.1.3x6.1", "wall2.1.3x6.2", "wall2.1.3x6.3", "wall2.1.2x2.1", "wall2.1.2x2.2", "", "", "", "", "", "", "", "", "", "", "", "", "",
            "wall2.1.1x2.1", "wall2.2.1x2.1", "wall2.1.6x6.7", "wall2.1.6x6.8", "wall2.1.6x6.9", "wall2.1.6x6.10", "wall2.1.6x6.11", "wall2.1.6x6.12", "wall2.1.6x3.7", "wall2.1.6x3.8", "wall2.1.6x3.9", "wall2.1.6x3.10", "wall2.1.6x3.11", "wall2.1.6x3.12", "wall2.1.3x6.4", "wall2.1.3x6.5", "wall2.1.3x6.6", "wall2.1.2x2.3", "wall2.1.2x2.4", "", "", "", "", "", "", "", "", "", "", "", "", "",
            "wall2.1.1x2.2", "wall2.2.1x2.2", "wall2.1.6x6.13", "wall2.1.6x6.14", "wall2.1.6x6.15", "wall2.1.6x6.16", "wall2.1.6x6.17", "wall2.1.6x6.18", "wall2.1.6x3.13", "wall2.1.6x3.14", "wall2.1.6x3.15", "wall2.1.6x3.16", "wall2.1.6x3.17", "wall2.1.6x3.18", "wall2.1.3x6.7", "wall2.1.3x6.8", "wall2.1.3x6.9", "wall2.1", "wall2.2", "", "", "", "", "", "", "", "", "", "", "", "", "",
            "wall2.2.2x1.1", "wall2.2.2x1.2", "wall2.1.6x6.19", "wall2.1.6x6.20", "wall2.1.6x6.21", "wall2.1.6x6.22", "wall2.1.6x6.23", "wall2.1.6x6.24", "wall2.1.3x3.1", "wall2.1.3x3.2", "wall2.1.3x3.3", "wall2.2.3x3.1", "wall2.2.3x3.2", "wall2.2.3x3.3", "wall2.1.3x6.10", "wall2.1.3x6.11", "wall2.1.3x6.12", "wall2.3", "wall2.4", "", "", "", "", "", "", "", "", "", "", "", "", "",
            "", "", "wall2.1.6x6.25", "wall2.1.6x6.26", "wall2.1.6x6.27", "wall2.1.6x6.28", "wall2.1.6x6.29", "wall2.1.6x6.30", "wall2.1.3x3.4", "wall2.1.3x3.5", "wall2.1.3x3.6", "wall2.2.3x3.4", "wall2.2.3x3.5", "wall2.2.3x3.6", "wall2.1.3x6.13", "wall2.1.3x6.14", "wall2.1.3x6.15", "wall2.5", "wall2.6", "", "", "", "", "", "", "", "", "", "", "", "", "",
            "", "", "wall2.1.6x6.31", "wall2.1.6x6.32", "wall2.1.6x6.33", "wall2.1.6x6.34", "wall2.1.6x6.35", "wall2.1.6x6.36", "wall2.1.3x3.7", "wall2.1.3x3.8", "wall2.1.3x3.9", "wall2.2.3x3.7", "wall2.2.3x3.8", "wall2.2.3x3.9", "wall2.1.3x6.16", "wall2.1.3x6.17", "wall2.1.3x6.18", "wall2.7", "wall2.8", "", "", "", "", "", "", "", "", "", "", "", "", "",
            ########################################################
            "wall2.3.2x1.1", "wall2.3.2x1.2", "wall2.2.6x6.1", "wall2.2.6x6.2", "wall2.2.6x6.3", "wall2.2.6x6.4", "wall2.2.6x6.5", "wall2.2.6x6.6", "wall2.2.6x3.1", "wall2.2.6x3.2", "wall2.2.6x3.3", "wall2.2.6x3.4", "wall2.2.6x3.5", "wall2.2.6x3.6", "wall2.2.3x6.1", "wall2.2.3x6.2", "wall2.2.3x6.3", "wall2.2.2x2.1", "wall2.2.2x2.2", "", "", "", "", "", "", "", "", "", "", "", "", "",
            "wall2.3.1x2.1", "wall2.4.1x2.1", "wall2.2.6x6.7", "wall2.2.6x6.8", "wall2.2.6x6.9", "wall2.2.6x6.10", "wall2.2.6x6.11", "wall2.2.6x6.12", "wall2.2.6x3.7", "wall2.2.6x3.8", "wall2.2.6x3.9", "wall2.2.6x3.10", "wall2.2.6x3.11", "wall2.2.6x3.12", "wall2.2.3x6.4", "wall2.2.3x6.5", "wall2.2.3x6.6", "wall2.2.2x2.3", "wall2.2.2x2.4", "", "", "", "", "", "", "", "", "", "", "", "", "",
            "wall2.3.1x2.2", "wall2.4.1x2.2", "wall2.2.6x6.13", "wall2.2.6x6.14", "wall2.2.6x6.15", "wall2.2.6x6.16", "wall2.2.6x6.17", "wall2.2.6x6.18", "wall2.2.6x3.13", "wall2.2.6x3.14", "wall2.2.6x3.15", "wall2.2.6x3.16", "wall2.2.6x3.17", "wall2.2.6x3.18", "wall2.2.3x6.7", "wall2.2.3x6.8", "wall2.2.3x6.9", "wall2.9", "wall2.10", "", "", "", "", "", "", "", "", "", "", "", "", "",
            "wall2.4.2x1.1", "wall2.4.2x1.2", "wall2.2.6x6.19", "wall2.2.6x6.20", "wall2.2.6x6.21", "wall2.2.6x6.22", "wall2.2.6x6.23", "wall2.2.6x6.24", "wall2.3.3x3.1", "wall2.3.3x3.2", "wall2.3.3x3.3", "wall2.4.3x3.1", "wall2.4.3x3.2", "wall2.4.3x3.3", "wall2.2.3x6.10", "wall2.2.3x6.11", "wall2.2.3x6.12", "wall2.11", "wall2.12", "", "", "", "", "", "", "", "", "", "", "", "", "",
            "", "", "wall2.2.6x6.25", "wall2.2.6x6.26", "wall2.2.6x6.27", "wall2.2.6x6.28", "wall2.2.6x6.29", "wall2.2.6x6.30", "wall2.3.3x3.4", "wall2.3.3x3.5", "wall2.3.3x3.6", "wall2.4.3x3.4", "wall2.4.3x3.5", "wall2.4.3x3.6", "wall2.2.3x6.13", "wall2.2.3x6.14", "wall2.2.3x6.15", "wall2.13", "wall2.14", "", "", "", "", "", "", "", "", "", "", "", "", "",
            "", "", "wall2.2.6x6.31", "wall2.2.6x6.32", "wall2.2.6x6.33", "wall2.2.6x6.34", "wall2.2.6x6.35", "wall2.2.6x6.36", "wall2.3.3x3.7", "wall2.3.3x3.8", "wall2.3.3x3.9", "wall2.4.3x3.7", "wall2.4.3x3.8", "wall2.4.3x3.9", "wall2.2.3x6.16", "wall2.2.3x6.17", "wall2.2.3x6.18", "wall2.15", "wall2.16", "", "", "", "", "", "", "", "", "", "", "", "", "",
            ########################################################
            "", "", "wall_deco1.tl.1", "wall_deco1.top.1", "wall_deco1.top.2", "wall_deco1.top.3", "wall_deco1.tr.1", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
            "", "", "wall_deco1.left.1", "wall_deco1.top.4", "wall_deco1.top.5", "wall_deco1.top.6", "wall_deco1.right.1", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
            "", "", "wall_deco1.left.2", "wall_deco1.top.7", "wall_deco1.top.8", "wall_deco1.top.9", "wall_deco1.right.2", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
            "", "", "wall_deco1.left.3", "wall_deco1.bot.1", "wall_deco1.bot.2", "wall_deco1.bot.3", "wall_deco1.right.3", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
            "", "", "wall_deco1.bl.1", "wall_deco1.bot.4", "wall_deco1.bot.5", "wall_deco1.bot.6", "wall_deco1.br.1", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
            "", "", "", "wall_deco1.bot.7", "wall_deco1.bot.8", "wall_deco1.bot.9", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
            "", "", "", "wall_deco1.bot.10", "wall_deco1.bot.11", "wall_deco1.bot.12", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
            "", "", "", "wall_deco1.bot.13", "wall_deco1.bot.14", "wall_deco1.bot.15", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
            ########################################################
            "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
            "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
            "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
            "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
            "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
            "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
            ########################################################
            "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
            "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
            "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
            "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
            "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
            "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
            ########################################################
            "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
            "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
            "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
            "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
            "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
            "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
            ########################################################
            "rock1.1.2x1.1", "rock1.1.2x1.2", "rock1.1.6x6.1", "rock1.1.6x6.2", "rock1.1.6x6.3", "rock1.1.6x6.4", "rock1.1.6x6.5", "rock1.1.6x6.6", "rock1.1.6x3.1", "rock1.1.6x3.2", "rock1.1.6x3.3", "rock1.1.6x3.4", "rock1.1.6x3.5", "rock1.1.6x3.6", "rock1.1.3x6.1", "rock1.1.3x6.2", "rock1.1.3x6.3", "rock1.1.2x2.1", "rock1.1.2x2.2", "", "", "", "", "", "", "", "", "", "", "", "", "",
            "rock1.1.1x2.1", "rock1.2.1x2.1", "rock1.1.6x6.7", "rock1.1.6x6.8", "rock1.1.6x6.9", "rock1.1.6x6.10", "rock1.1.6x6.11", "rock1.1.6x6.12", "rock1.1.6x3.7", "rock1.1.6x3.8", "rock1.1.6x3.9", "rock1.1.6x3.10", "rock1.1.6x3.11", "rock1.1.6x3.12", "rock1.1.3x6.4", "rock1.1.3x6.5", "rock1.1.3x6.6", "rock1.1.2x2.3", "rock1.1.2x2.4", "", "", "", "", "", "", "", "", "", "", "", "", "",
            "rock1.1.1x2.2", "rock1.2.1x2.2", "rock1.1.6x6.13", "rock1.1.6x6.14", "rock1.1.6x6.15", "rock1.1.6x6.16", "rock1.1.6x6.17", "rock1.1.6x6.18", "rock1.1.6x3.13", "rock1.1.6x3.14", "rock1.1.6x3.15", "rock1.1.6x3.16", "rock1.1.6x3.17", "rock1.1.6x3.18", "rock1.1.3x6.7", "rock1.1.3x6.8", "rock1.1.3x6.9", "rock1.1", "rock1.2", "", "", "", "", "", "", "", "", "", "", "", "", "",
            "rock1.2.2x1.1", "rock1.2.2x1.2", "rock1.1.6x6.19", "rock1.1.6x6.20", "rock1.1.6x6.21", "rock1.1.6x6.22", "rock1.1.6x6.23", "rock1.1.6x6.24", "rock1.1.3x3.1", "rock1.1.3x3.2", "rock1.1.3x3.3", "rock1.2.3x3.1", "rock1.2.3x3.2", "rock1.2.3x3.3", "rock1.1.3x6.10", "rock1.1.3x6.11", "rock1.1.3x6.12", "rock1.3", "rock1.4", "", "", "", "", "", "", "", "", "", "", "", "", "",
            "", "", "rock1.1.6x6.25", "rock1.1.6x6.26", "rock1.1.6x6.27", "rock1.1.6x6.28", "rock1.1.6x6.29", "rock1.1.6x6.30", "rock1.1.3x3.4", "rock1.1.3x3.5", "rock1.1.3x3.6", "rock1.2.3x3.4", "rock1.2.3x3.5", "rock1.2.3x3.6", "rock1.1.3x6.13", "rock1.1.3x6.14", "rock1.1.3x6.15", "rock1.5", "rock1.6", "", "", "", "", "", "", "", "", "", "", "", "", "",
            "", "", "rock1.1.6x6.31", "rock1.1.6x6.32", "rock1.1.6x6.33", "rock1.1.6x6.34", "rock1.1.6x6.35", "rock1.1.6x6.36", "rock1.1.3x3.7", "rock1.1.3x3.8", "rock1.1.3x3.9", "rock1.2.3x3.7", "rock1.2.3x3.8", "rock1.2.3x3.9", "rock1.1.3x6.16", "rock1.1.3x6.17", "rock1.1.3x6.18", "rock1.7", "rock1.8", "", "", "", "", "", "", "", "", "", "", "", "", "",
            ########################################################
            "rock1.3.2x1.1", "rock1.3.2x1.2", "rock1.2.6x6.1", "rock1.2.6x6.2", "rock1.2.6x6.3", "rock1.2.6x6.4", "rock1.2.6x6.5", "rock1.2.6x6.6", "rock1.2.6x3.1", "rock1.2.6x3.2", "rock1.2.6x3.3", "rock1.2.6x3.4", "rock1.2.6x3.5", "rock1.2.6x3.6", "rock1.2.3x6.1", "rock1.2.3x6.2", "rock1.2.3x6.3", "rock1.2.2x2.1", "rock1.2.2x2.2", "", "", "", "", "", "", "", "", "", "", "", "", "",
            "rock1.3.1x2.1", "rock1.4.1x2.1", "rock1.2.6x6.7", "rock1.2.6x6.8", "rock1.2.6x6.9", "rock1.2.6x6.10", "rock1.2.6x6.11", "rock1.2.6x6.12", "rock1.2.6x3.7", "rock1.2.6x3.8", "rock1.2.6x3.9", "rock1.2.6x3.10", "rock1.2.6x3.11", "rock1.2.6x3.12", "rock1.2.3x6.4", "rock1.2.3x6.5", "rock1.2.3x6.6", "rock1.2.2x2.3", "rock1.2.2x2.4", "", "", "", "", "", "", "", "", "", "", "", "", "",
            "rock1.3.1x2.2", "rock1.4.1x2.2", "rock1.2.6x6.13", "rock1.2.6x6.14", "rock1.2.6x6.15", "rock1.2.6x6.16", "rock1.2.6x6.17", "rock1.2.6x6.18", "rock1.2.6x3.13", "rock1.2.6x3.14", "rock1.2.6x3.15", "rock1.2.6x3.16", "rock1.2.6x3.17", "rock1.2.6x3.18", "rock1.2.3x6.7", "rock1.2.3x6.8", "rock1.2.3x6.9", "rock1.9", "rock1.10", "", "", "", "", "", "", "", "", "", "", "", "", "",
            "rock1.4.2x1.1", "rock1.4.2x1.2", "rock1.2.6x6.19", "rock1.2.6x6.20", "rock1.2.6x6.21", "rock1.2.6x6.22", "rock1.2.6x6.23", "rock1.2.6x6.24", "rock1.3.3x3.1", "rock1.3.3x3.2", "rock1.3.3x3.3", "rock1.4.3x3.1", "rock1.4.3x3.2", "rock1.4.3x3.3", "rock1.2.3x6.10", "rock1.2.3x6.11", "rock1.2.3x6.12", "rock1.11", "rock1.12", "", "", "", "", "", "", "", "", "", "", "", "", "",
            "", "", "rock1.2.6x6.25", "rock1.2.6x6.26", "rock1.2.6x6.27", "rock1.2.6x6.28", "rock1.2.6x6.29", "rock1.2.6x6.30", "rock1.3.3x3.4", "rock1.3.3x3.5", "rock1.3.3x3.6", "rock1.4.3x3.4", "rock1.4.3x3.5", "rock1.4.3x3.6", "rock1.2.3x6.13", "rock1.2.3x6.14", "rock1.2.3x6.15", "rock1.13", "rock1.14", "", "", "", "", "", "", "", "", "", "", "", "", "",
            "", "", "rock1.2.6x6.31", "rock1.2.6x6.32", "rock1.2.6x6.33", "rock1.2.6x6.34", "rock1.2.6x6.35", "rock1.2.6x6.36", "rock1.3.3x3.7", "rock1.3.3x3.8", "rock1.3.3x3.9", "rock1.4.3x3.7", "rock1.4.3x3.8", "rock1.4.3x3.9", "rock1.2.3x6.16", "rock1.2.3x6.17", "rock1.2.3x6.18", "rock1.15", "rock1.16", "", "", "", "", "", "", "", "", "", "", "", "", "",
            ########################################################
            "rock2.1.2x1.1", "rock2.1.2x1.2", "rock2.1.6x6.1", "rock2.1.6x6.2", "rock2.1.6x6.3", "rock2.1.6x6.4", "rock2.1.6x6.5", "rock2.1.6x6.6", "rock2.1.6x3.1", "rock2.1.6x3.2", "rock2.1.6x3.3", "rock2.1.6x3.4", "rock2.1.6x3.5", "rock2.1.6x3.6", "rock2.1.3x6.1", "rock2.1.3x6.2", "rock2.1.3x6.3", "rock2.1.2x2.1", "rock2.1.2x2.2", "", "", "", "", "", "", "", "", "", "", "", "", "",
            "rock2.1.1x2.1", "rock2.2.1x2.1", "rock2.1.6x6.7", "rock2.1.6x6.8", "rock2.1.6x6.9", "rock2.1.6x6.10", "rock2.1.6x6.11", "rock2.1.6x6.12", "rock2.1.6x3.7", "rock2.1.6x3.8", "rock2.1.6x3.9", "rock2.1.6x3.10", "rock2.1.6x3.11", "rock2.1.6x3.12", "rock2.1.3x6.4", "rock2.1.3x6.5", "rock2.1.3x6.6", "rock2.1.2x2.3", "rock2.1.2x2.4", "", "", "", "", "", "", "", "", "", "", "", "", "",
            "rock2.1.1x2.2", "rock2.2.1x2.2", "rock2.1.6x6.13", "rock2.1.6x6.14", "rock2.1.6x6.15", "rock2.1.6x6.16", "rock2.1.6x6.17", "rock2.1.6x6.18", "rock2.1.6x3.13", "rock2.1.6x3.14", "rock2.1.6x3.15", "rock2.1.6x3.16", "rock2.1.6x3.17", "rock2.1.6x3.18", "rock2.1.3x6.7", "rock2.1.3x6.8", "rock2.1.3x6.9", "rock2.1", "rock2.2", "", "", "", "", "", "", "", "", "", "", "", "", "",
            "rock2.2.2x1.1", "rock2.2.2x1.2", "rock2.1.6x6.19", "rock2.1.6x6.20", "rock2.1.6x6.21", "rock2.1.6x6.22", "rock2.1.6x6.23", "rock2.1.6x6.24", "rock2.1.3x3.1", "rock2.1.3x3.2", "rock2.1.3x3.3", "rock2.2.3x3.1", "rock2.2.3x3.2", "rock2.2.3x3.3", "rock2.1.3x6.10", "rock2.1.3x6.11", "rock2.1.3x6.12", "rock2.3", "rock2.4", "", "", "", "", "", "", "", "", "", "", "", "", "",
            "", "", "rock2.1.6x6.25", "rock2.1.6x6.26", "rock2.1.6x6.27", "rock2.1.6x6.28", "rock2.1.6x6.29", "rock2.1.6x6.30", "rock2.1.3x3.4", "rock2.1.3x3.5", "rock2.1.3x3.6", "rock2.2.3x3.4", "rock2.2.3x3.5", "rock2.2.3x3.6", "rock2.1.3x6.13", "rock2.1.3x6.14", "rock2.1.3x6.15", "rock2.5", "rock2.6", "", "", "", "", "", "", "", "", "", "", "", "", "",
            "", "", "rock2.1.6x6.31", "rock2.1.6x6.32", "rock2.1.6x6.33", "rock2.1.6x6.34", "rock2.1.6x6.35", "rock2.1.6x6.36", "rock2.1.3x3.7", "rock2.1.3x3.8", "rock2.1.3x3.9", "rock2.2.3x3.7", "rock2.2.3x3.8", "rock2.2.3x3.9", "rock2.1.3x6.16", "rock2.1.3x6.17", "rock2.1.3x6.18", "rock2.7", "rock2.8", "", "", "", "", "", "", "", "", "", "", "", "", "",
            ########################################################
            "rock2.3.2x1.1", "rock2.3.2x1.2", "rock2.2.6x6.1", "rock2.2.6x6.2", "rock2.2.6x6.3", "rock2.2.6x6.4", "rock2.2.6x6.5", "rock2.2.6x6.6", "rock2.2.6x3.1", "rock2.2.6x3.2", "rock2.2.6x3.3", "rock2.2.6x3.4", "rock2.2.6x3.5", "rock2.2.6x3.6", "rock2.2.3x6.1", "rock2.2.3x6.2", "rock2.2.3x6.3", "rock2.2.2x2.1", "rock2.2.2x2.2", "", "", "", "", "", "", "", "", "", "", "", "", "",
            "rock2.3.1x2.1", "rock2.4.1x2.1", "rock2.2.6x6.7", "rock2.2.6x6.8", "rock2.2.6x6.9", "rock2.2.6x6.10", "rock2.2.6x6.11", "rock2.2.6x6.12", "rock2.2.6x3.7", "rock2.2.6x3.8", "rock2.2.6x3.9", "rock2.2.6x3.10", "rock2.2.6x3.11", "rock2.2.6x3.12", "rock2.2.3x6.4", "rock2.2.3x6.5", "rock2.2.3x6.6", "rock2.2.2x2.3", "rock2.2.2x2.4", "", "", "", "", "", "", "", "", "", "", "", "", "",
            "rock2.3.1x2.2", "rock2.4.1x2.2", "rock2.2.6x6.13", "rock2.2.6x6.14", "rock2.2.6x6.15", "rock2.2.6x6.16", "rock2.2.6x6.17", "rock2.2.6x6.18", "rock2.2.6x3.13", "rock2.2.6x3.14", "rock2.2.6x3.15", "rock2.2.6x3.16", "rock2.2.6x3.17", "rock2.2.6x3.18", "rock2.2.3x6.7", "rock2.2.3x6.8", "rock2.2.3x6.9", "rock2.9", "rock2.10", "", "", "", "", "", "", "", "", "", "", "", "", "",
            "rock2.4.2x1.1", "rock2.4.2x1.2", "rock2.2.6x6.19", "rock2.2.6x6.20", "rock2.2.6x6.21", "rock2.2.6x6.22", "rock2.2.6x6.23", "rock2.2.6x6.24", "rock2.3.3x3.1", "rock2.3.3x3.2", "rock2.3.3x3.3", "rock2.4.3x3.1", "rock2.4.3x3.2", "rock2.4.3x3.3", "rock2.2.3x6.10", "rock2.2.3x6.11", "rock2.2.3x6.12", "rock2.11", "rock2.12", "", "", "", "", "", "", "", "", "", "", "", "", "",
            "", "", "rock2.2.6x6.25", "rock2.2.6x6.26", "rock2.2.6x6.27", "rock2.2.6x6.28", "rock2.2.6x6.29", "rock2.2.6x6.30", "rock2.3.3x3.4", "rock2.3.3x3.5", "rock2.3.3x3.6", "rock2.4.3x3.4", "rock2.4.3x3.5", "rock2.4.3x3.6", "rock2.2.3x6.13", "rock2.2.3x6.14", "rock2.2.3x6.15", "rock2.13", "rock2.14", "", "", "", "", "", "", "", "", "", "", "", "", "",
            "", "", "rock2.2.6x6.31", "rock2.2.6x6.32", "rock2.2.6x6.33", "rock2.2.6x6.34", "rock2.2.6x6.35", "rock2.2.6x6.36", "rock2.3.3x3.7", "rock2.3.3x3.8", "rock2.3.3x3.9", "rock2.4.3x3.7", "rock2.4.3x3.8", "rock2.4.3x3.9", "rock2.2.3x6.16", "rock2.2.3x6.17", "rock2.2.3x6.18", "rock2.15", "rock2.16", "", "", "", "", "", "", "", "", "", "", "", "", "",
            ########################################################
    ]

    zx.tile_load_arr_color_and_black_and_white(
        file="data/gfx/16x16.tga",
        name="16x16", width=16, height=16, arr=tiles)

def init_16x32():
    tiles = [
            ########################################################
            "smoke1.1",
            "smoke1.2",
            "smoke1.3",
            "smoke1.4",
            "smoke1.5",
            "smoke1.6",
            "smoke1.7",
            "smoke1.8",
            "smoke1.9",
            "smoke1.10",
            "smoke1.11",
            "smoke1.12",
            "smoke1.13",
            "smoke1.14",
            "smoke1.15",
            "smoke1.16",
            "smoke1.17",
            "smoke1.18",
            "smoke1.19",
            "smoke1.20",
            "smoke1.21",
            "smoke1.22",
            "smoke1.23",
            "smoke1.24",
            "smoke1.25",
            "smoke1.26",
            "smoke1.27",
            "smoke1.28",
            "smoke1.29",
            "smoke1.30",
            "smoke1.31",
            "smoke1.32",
            ########################################################
            "brazier1.1",
            "brazier1.2",
            "brazier1.3",
            "brazier1.4",
            "brazier1.5",
            "brazier1.6",
            "brazier1.7",
            "brazier1.8",
            "brazier1.9",
            "brazier1.10",
            "brazier1.11",
            "brazier1.12",
            "brazier1.13",
            "brazier1.14",
            "brazier1.15",
            "brazier1.16",
            "brazier1.17",
            "brazier1.18",
            "brazier1.19",
            "brazier1.20",
            "brazier1.21",
            "brazier1.22",
            "brazier1.23",
            "brazier1.24",
            "brazier1.25",
            "brazier1.26",
            "brazier1.27",
            "brazier1.28",
            "brazier1.29",
            "brazier1.30",
            "brazier1.31",
            "brazier1.32",
    ]

    zx.tile_load_arr_color_and_black_and_white(
        file="data/gfx/16x32.tga",
        name="16x32", width=16, height=32, arr=tiles)

def init_32x32():
    tiles = [
            "exit1.1",
            "exit1.2",
            "exit1.3",
            "exit1.4",
            "exit1.5",
            "exit1.6",
            "exit1.7",
            "exit1.8",
            "entrance1.1",
            "entrance1.2",
            "entrance1.3",
            "entrance1.4",
            "entrance1.5",
            "entrance1.6",
            "door1.1-closed",
            "door1.1-open",
            ########################################################
            "blood_splatter1.1",
            "blood_splatter1.2",
            "blood_splatter1.3",
            "blood_splatter1.4",
            "blood_splatter1.5",
            "blood_splatter1.6",
            "blood_splatter1.7",
            "blood_splatter1.8",
            "blood_splatter1.9",
            "blood_splatter1.10",
            "blood_splatter1.11",
            "blood_splatter1.12",
            "blood_splatter1.13",
            "blood_splatter1.14",
            "secret_door1.1-closed",
            "secret_door1.1-open",
            ########################################################
            "pillar1.1",
            "pillar1.2",
            "pillar1.3",
            "pillar1.4",
            "pillar1.5",
            "pillar1.6",
            "pillar1.7",
            "pillar1.8",
            "pillar1.9",
            "pillar1.10",
            "pillar1.11",
            "pillar1.12",
            "pillar1.13",
            "pillar1.14",
            "pillar1.15",
            "pillar1.16",
            ########################################################
            "pillar1.17",
            "pillar1.18",
            "pillar1.19",
            "pillar1.20",
            "pillar1.21",
            "pillar1.22",
            "pillar1.23",
            "pillar1.24",
            "pillar1.25",
            "pillar1.26",
            "pillar1.27",
            "pillar1.28",
            "pillar1.29",
            "pillar1.30",
            "pillar1.31",
            "pillar1.32",
            ########################################################
            "grate1.1",
            "grate2.1",
            "grate3.1",
            "grate4.1",
            "grate5.1",
            "grate6.1",
            "grate7.1",
            "grate8.1",
            "grate1.2",
            "grate2.2",
            "grate3.2",
            "grate4.2",
            "grate5.2",
            "grate6.2",
            "grate7.2",
            "grate8.2",
            ########################################################
            "slime2.1",
            "slime2.2",
            "slime2.3",
            "slime2.4",
            "slime2.5",
            "slime2.6",
            "slime2.7",
            "slime2.8",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            ########################################################
            "fire.1",
            "fire.2",
            "fire.3",
            "fire.4",
            "fire.5",
            "fire.6",
            "fire.7",
            "fire.8",
            "fire.9",
            "fire.10",
            "fire.11",
            "fire.12",
            "fire.13",
            "fire.14",
            "fire.15",
            "fire.16",
            ########################################################
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            ########################################################
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            ########################################################
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
    ]

    zx.tile_load_arr_color_and_black_and_white(
        file="data/gfx/32x32.tga",
        name="32x32", width=32, height=32, arr=tiles)

def init_32x32_surface_effects():
    tiles = [
            "water1.1", "water1.2", "water1.3", "water1.4", "water1.5", "water1.6", "water1.7", "water1.8",
            "water1.9", "water1.10", "water1.11", "water1.12", "water1.13", "water1.14", "water1.15", "water1.16",
            "water_outline1.1", "water_outline1.2", "water_outline1.3", "water_outline1.4", "water_outline1.5", "water_outline1.6", "water_outline1.7", "water_outline1.8",
            "water_outline1.9", "water_outline1.10", "water_outline1.11", "water_outline1.12", "water_outline1.13", "water_outline1.14", "water_outline1.15", "water_outline1.16",
            "ripple1.1", "ripple1.2", "ripple1.3", "ripple1.4",
            "ripple1.5", "ripple1.6", "ripple1.7", "ripple1.8",
            "ripple2.1", "ripple2.2", "ripple2.3", "ripple2.4",
            "ripple2.5", "ripple2.6", "ripple2.7", "ripple2.8",
            "deep_water1.1", "deep_water1.2", "deep_water1.3", "deep_water1.4", "deep_water1.5", "deep_water1.6", "deep_water1.7", "deep_water1.8",
            "deep_water1.9", "deep_water1.10", "deep_water1.11", "deep_water1.12", "deep_water1.13", "deep_water1.14", "deep_water1.15", "deep_water1.16",
            "lava1.1", "lava1.2", "lava1.3", "lava1.4", "lava1.5", "lava1.6", "lava1.7", "lava1.8",
            "lava1.9", "lava1.10", "lava1.11", "lava1.12", "lava1.13", "lava1.14", "lava1.15", "lava1.16",
            "lava_outline1.1", "lava_outline1.2", "lava_outline1.3", "lava_outline1.4", "lava_outline1.5", "lava_outline1.6", "lava_outline1.7", "lava_outline1.8",
            "lava_outline1.9", "lava_outline1.10", "lava_outline1.11", "lava_outline1.12", "lava_outline1.13", "lava_outline1.14", "lava_outline1.15", "lava_outline1.16",
            "chasm1.1", "chasm1.2", "chasm1.3", "chasm1.4", "chasm1.5", "chasm1.6", "chasm1.7", "chasm1.8",
            "chasm1.9", "chasm1.10", "chasm1.11", "chasm1.12", "chasm1.13", "chasm1.14", "chasm1.15", "chasm1.16",
            "chasm_outline1.1", "chasm_outline1.2", "chasm_outline1.3", "chasm_outline1.4", "chasm_outline1.5", "chasm_outline1.6", "chasm_outline1.7", "chasm_outline1.8",
            "chasm_outline1.9", "chasm_outline1.10", "chasm_outline1.11", "chasm_outline1.12", "chasm_outline1.13", "chasm_outline1.14", "chasm_outline1.15", "chasm_outline1.16",
    ]

    zx.tile_load_arr_color_and_black_and_white(
        file="data/gfx/32x32_surface_effects.tga",
        name="32x32_surface_effects", width=32, height=32, arr=tiles)

def init_32x32_water():
    tiles = [
        "water1a", "water2a", "water3a", "water4a", "water5a", "water6a", "water7a", "water8a",
        "water1b", "water2b", "water3b", "water4b", "water5b", "water6b", "water7b", "water8b",
        "water1c", "water2c", "water3c", "water4c", "water5c", "water6c", "water7c", "water8c",
        "water1d", "water2d", "water3d", "water4d", "water5d", "water6d", "water7d", "water8d",
        "water1e", "water2e", "water3e", "water4e", "water5e", "water6e", "water7e", "water8e",
        "water1f", "water2f", "water3f", "water4f", "water5f", "water6f", "water7f", "water8f",
        "water1g", "water2g", "water3g", "water4g", "water5g", "water6g", "water7g", "water8g",
        "water1h", "water2h", "water3h", "water4h", "water5h", "water6h", "water7h", "water8h",
    ]

    zx.tile_load_arr_color_and_black_and_white(
        file="data/gfx/32x32_water.tga",
        name="32x32_water", width=32, height=32, arr=tiles)


def init_32x32_deep_water():
    tiles = [
        "deep_water1a", "deep_water2a", "deep_water3a", "deep_water4a", "deep_water5a", "deep_water6a", "deep_water7a", "deep_water8a",
        "deep_water1b", "deep_water2b", "deep_water3b", "deep_water4b", "deep_water5b", "deep_water6b", "deep_water7b", "deep_water8b",
        "deep_water1c", "deep_water2c", "deep_water3c", "deep_water4c", "deep_water5c", "deep_water6c", "deep_water7c", "deep_water8c",
        "deep_water1d", "deep_water2d", "deep_water3d", "deep_water4d", "deep_water5d", "deep_water6d", "deep_water7d", "deep_water8d",
        "deep_water1e", "deep_water2e", "deep_water3e", "deep_water4e", "deep_water5e", "deep_water6e", "deep_water7e", "deep_water8e",
        "deep_water1f", "deep_water2f", "deep_water3f", "deep_water4f", "deep_water5f", "deep_water6f", "deep_water7f", "deep_water8f",
        "deep_water1g", "deep_water2g", "deep_water3g", "deep_water4g", "deep_water5g", "deep_water6g", "deep_water7g", "deep_water8g",
        "deep_water1h", "deep_water2h", "deep_water3h", "deep_water4h", "deep_water5h", "deep_water6h", "deep_water7h", "deep_water8h",
    ]

    zx.tile_load_arr_color_and_black_and_white(
        file="data/gfx/32x32_deep_water.tga",
        name="32x32_deep_water", width=32, height=32, arr=tiles)


def init_32x32_lava():
    tiles = [
        "lava1a", "lava2a", "lava3a", "lava4a", "lava5a", "lava6a", "lava7a", "lava8a",
        "lava1b", "lava2b", "lava3b", "lava4b", "lava5b", "lava6b", "lava7b", "lava8b",
        "lava1c", "lava2c", "lava3c", "lava4c", "lava5c", "lava6c", "lava7c", "lava8c",
        "lava1d", "lava2d", "lava3d", "lava4d", "lava5d", "lava6d", "lava7d", "lava8d",
        "lava1e", "lava2e", "lava3e", "lava4e", "lava5e", "lava6e", "lava7e", "lava8e",
        "lava1f", "lava2f", "lava3f", "lava4f", "lava5f", "lava6f", "lava7f", "lava8f",
        "lava1g", "lava2g", "lava3g", "lava4g", "lava5g", "lava6g", "lava7g", "lava8g",
        "lava1h", "lava2h", "lava3h", "lava4h", "lava5h", "lava6h", "lava7h", "lava8h",
    ]

    zx.tile_load_arr_color_and_black_and_white(
        file="data/gfx/32x32_lava.tga",
        name="32x32_lava", width=32, height=32, arr=tiles)

def init_32x32_chasm():
    tiles = [
        "chasm1a", "chasm2a", "chasm3a", "chasm4a", "chasm5a", "chasm6a", "chasm7a", "chasm8a",
        "chasm1b", "chasm2b", "chasm3b", "chasm4b", "chasm5b", "chasm6b", "chasm7b", "chasm8b",
        "chasm1c", "chasm2c", "chasm3c", "chasm4c", "chasm5c", "chasm6c", "chasm7c", "chasm8c",
        "chasm1d", "chasm2d", "chasm3d", "chasm4d", "chasm5d", "chasm6d", "chasm7d", "chasm8d",
        "chasm1e", "chasm2e", "chasm3e", "chasm4e", "chasm5e", "chasm6e", "chasm7e", "chasm8e",
        "chasm1f", "chasm2f", "chasm3f", "chasm4f", "chasm5f", "chasm6f", "chasm7f", "chasm8f",
        "chasm1g", "chasm2g", "chasm3g", "chasm4g", "chasm5g", "chasm6g", "chasm7g", "chasm8g",
        "chasm1h", "chasm2h", "chasm3h", "chasm4h", "chasm5h", "chasm6h", "chasm7h", "chasm8h",
    ]

    zx.tile_load_arr_color_and_black_and_white(
        file="data/gfx/32x32_chasm.tga",
        name="32x32_chasm", width=32, height=32, arr=tiles)

def init_weapons_tiles():
    tiles = [
            "",
            "sword1_carry_anim.1",
            "sword1_carry_anim.2",
            "sword1_swing_anim_left.1",
            "sword1_swing_anim_left.2",
            "sword1_swing_anim_left.3",
            "sword1_swing_anim_left.4",
            "sword1_swing_anim_left.5",
            "sword1_swing_anim_left.6",
            ##########################################################
            "",
            "",
            "",
            "sword1_swing_anim_up.1",
            "sword1_swing_anim_up.2",
            "sword1_swing_anim_up.3",
            "sword1_swing_anim_up.4",
            "sword1_swing_anim_up.5",
            "sword1_swing_anim_up.6",
    ]

    zx.tile_load_arr_color_and_black_and_white(
        file="data/gfx/weapons.tga",
        name="weapons", width=48, height=48, arr=tiles)

def init_claws_tiles():
    tiles = [
        "claws1.1", "claws1.2", "claws1.3", "claws1.4", "claws1.5", "claws1.6", "claws1.7", "claws1.8",
        "claws1.9", "claws1.10", "claws1.11", "claws1.12", "claws1.13", "claws1.14", "claws1.15", "claws1.16",
        "claws1.17", "claws1.18", "claws1.19", "claws1.20", "claws1.21", "claws1.22", "claws1.23", "claws1.24",
        "claws1.25", "claws1.26", "claws1.27", "claws1.28", "claws1.29", "claws1.30", "claws1.31", "claws1.32",
        "claws1.33", "claws1.34", "claws1.35", "claws1.36", "claws1.37", "claws1.38", "claws1.39", "claws1.40",
        "claws1.41", "claws1.42", "claws1.43", "claws1.44", "claws1.45", "claws1.46", "claws1.47", "claws1.48",
        "claws1.49", "claws1.50", "claws1.51", "claws1.52"
    ]

    zx.tile_load_arr_color_and_black_and_white(
        file="data/gfx/hit_claws_50x50px.tga",
        name="claws", width=25, height=25, arr=tiles)

init_solid()
init_light()
init_64x16_ui()
init_title()
init_ui_dead()
init_ui_action_bar()
init_16x16()
init_16x32()
init_32x32()
init_32x32_water()
init_32x32_deep_water()
init_32x32_surface_effects()
init_32x32_lava()
init_32x32_chasm()
init_weapons_tiles()
init_claws_tiles()
