import zx


def init_solid():
    zx.tex_load(file="data/gfx/solid.tga", name="solid")


def init_light():
    zx.tex_load(file="data/gfx/light.tga", name="light")


def init_bloom():
    zx.tex_load(file="data/gfx/bloom.tga", name="bloom")


def init_ui_status_bar():
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
    ]
    zx.tile_load_arr(
        file="data/gfx/ui_status_bar.tga",
        name="ui_status_bar", width=200, height=24, arr=tiles)

def init_ui_status_bar_title():
    tiles = [
        "zorbash-0",
        "zorbash-1",
        "zorbash-2",
    ]
    zx.tile_load_arr(
        file="data/gfx/zorbash_small.tga",
        name="status_bar_title", width=240, height=48, arr=tiles)

def init_ui_blood():
    tiles = [
        "blood-0",
        "blood-1",
        "blood-2",
        "blood-3",
    ]
    zx.tile_load_arr(
        file="data/gfx/blood.tga",
        name="blood", width=360, height=225, arr=tiles)

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
        "ui_action_bar0",
        "ui_action_bar1",
        "ui_action_bar2",
        "ui_action_bar3",
        "ui_action_bar4",
        "ui_action_bar5",
        "ui_action_bar6",
        "ui_action_bar7",
        "ui_action_bar8",
        "ui_action_bar9",
        "ui_action_bar10",
        "ui_action_bar11",
        "ui_action_bar12",
        "ui_action_bar13",
        "ui_action_bar14",
        "ui_action_bar15",
        "ui_action_bar16",
        "ui_action_bar17",
        "ui_action_bar18",
        "ui_action_bar19",
    ]
    zx.tile_load_arr(
        file="data/gfx/ui_action_bar.tga",
        name="ui_action_bar", width=60, height=72, arr=tiles)

def init_ui_action_bar_highlight():
    tiles = [
        "ui_action_bar_highlight0",
        "ui_action_bar_highlight1",
        "ui_action_bar_highlight2",
        "ui_action_bar_highlight3",
        "ui_action_bar_highlight4",
        "ui_action_bar_highlight5",
        "ui_action_bar_highlight6",
        "ui_action_bar_highlight7",
        "ui_action_bar_highlight8",
        "ui_action_bar_highlight9",
        "ui_action_bar_highlight10",
        "ui_action_bar_highlight11",
        "ui_action_bar_highlight12",
        "ui_action_bar_highlight13",
        "ui_action_bar_highlight14",
        "ui_action_bar_highlight15",
        "ui_action_bar_highlight16",
        "ui_action_bar_highlight17",
        "ui_action_bar_highlight18",
        "ui_action_bar_highlight19",
    ]
    zx.tile_load_arr(
        file="data/gfx/ui_action_bar_highlight.tga",
        name="ui_action_bar_highlight", width=60, height=72, arr=tiles)

def init_16x16():
    tiles = [
      "health5-icon",        "health4-icon",        "health3-icon",        "health2-icon",
      "health1-icon",        "dollar-icon",         "defence-icon",        "weight-icon",
      "attack-icon",         "magic-icon",          "karma-icon",          "save",
      "load",                "bug",                 "pause",               "dead",
      "",                    "",                    "",
      ##############################################################################################################################################
      "nothing",             "cursor.1",            "cursor.2",            "cursor.3",
      "cursor.4",            "cursor.5",            "cursor.6",            "cursor.7",
      "cursor.8",            "cursor.9",            "cursor.10",           "cursor.11",
      "cursor.12",           "cursor_path.1",       "ai_path1.1",          "ai_path2.1",
      "",                    "",                    "",
      ##############################################################################################################################################
      "",
      "blood1.100",          "blood2.100",          "blood3.100",          "blood4.100",
      "blood1.75",           "blood2.75",           "blood3.75",           "blood4.75",
      "blood1.50",           "blood2.50",           "blood3.50",           "blood4.50",
      "blood1.25",           "blood2.25",           "blood3.25",           "blood4.25",
      "",                    "",
      ##############################################################################################################################################
      "key1.1",              "key1.2",              "key1.3",              "key1.4",
      "key1.5",              "key1.6",              "key1.7",              "key1.8",
      "",                    "",                    "",                    "",
      "",                    "",                    "",                    "",
      "",                    "",                    "",
      ##############################################################################################################################################
      "ascii.key1.1",        "ascii.key1.2",        "ascii.key1.3",        "ascii.key1.4",
      "ascii.key1.5",        "ascii.key1.6",        "ascii.key1.7",        "ascii.key1.8",
      "",                    "",                    "",                    "",
      "",                    "",                    "",                    "",
      "",                    "",                    "",
      ##############################################################################################################################################
      "gold1.1",             "gold1.2",             "gold1.3",             "gold1.4",
      "gold1.5",             "gold1.6",             "gold1.7",             "gold1.8",
      "food_frog1",          "",                    "",                    "",
      "",                    "",                    "",                    "",
      "",                    "",                    "",
      ##############################################################################################################################################
      "ascii.gold1.1",       "ascii.gold1.2",       "ascii.gold1.3",       "ascii.gold1.4",
      "ascii.gold1.5",       "ascii.gold1.6",       "ascii.gold1.7",       "ascii.gold1.8",
      "ascii.food_frog1",    "",                    "",                    "",
      "",                    "",                    "",                    "",
      "",                    "",                    "",
      ##############################################################################################################################################
      "player1.1",           "player1.2",           "player1.3",           "player1.4",
      "player1.5",           "player1.6",           "",                    "player1.pose",
      "player1.dead",        "sword1.1",            "",                    "",
      "",                    "",                    "",                    "",
      "",                    "",                    "",
      ##############################################################################################################################################
      "ascii.player1.1",     "ascii.player1.2",     "ascii.player1.3",     "ascii.player1.4",
      "ascii.player1.5",     "ascii.player1.6",     "",                    "ascii.player1.pose",
      "ascii.player1.dead",  "",                    "",                    "",
      "",                    "",                    "",                    "",
      "",                    "",                    "",
      ##############################################################################################################################################
      "mummy1.1.100",        "mummy1.2.100",        "mummy1.3.100",        "mummy1.1.dead",
      "mummy1.2.dead",       "mummy1.3.dead",       "mummy1.4.dead",       "mummy1.5.dead",
      "",                    "",                    "",                    "",
      "",                    "",                    "",                    "",
      "",                    "",                    "",
      ##############################################################################################################################################
      "ascii.mummy1.1.100",  "ascii.mummy1.2.100",  "ascii.mummy1.3.100",  "ascii.mummy1.1.dead",
      "ascii.mummy1.2.dead", "ascii.mummy1.3.dead", "ascii.mummy1.4.dead", "ascii.mummy1.5.dead",
      "",                    "",                    "",                    "",
      "",                    "",                    "",                    "",
      "",                    "",                    "",
      ##############################################################################################################################################
      "slime1.1.100",        "slime1.2.100",        "slime1.3.100",        "slime1.4.100",
      "slime1.1.75",         "slime1.2.75",         "slime1.3.75",         "slime1.4.75",
      "slime1.1.50",         "slime1.2.50",         "slime1.3.50",         "slime1.4.50",
      "slime1.1.25",         "slime1.2.25",         "slime1.3.25",         "slime1.4.25",
      "slime1.dead",         "",                    "",
      ##############################################################################################################################################
      "ascii.slime1.1.100",  "ascii.slime1.2.100",  "ascii.slime1.3.100",  "ascii.slime1.4.100",
      "ascii.slime1.1.75",   "ascii.slime1.2.75",   "ascii.slime1.3.75",   "ascii.slime1.4.75",
      "ascii.slime1.1.50",   "ascii.slime1.2.50",   "ascii.slime1.3.50",   "ascii.slime1.4.50",
      "ascii.slime1.1.25",   "ascii.slime1.2.25",   "ascii.slime1.3.25",   "ascii.slime1.4.25",
      "ascii.slime1.dead",   "",                    "",
      ##############################################################################################################################################
      "torch1.1",            "torch1.2",            "torch1.3",            "torch1.4",
      "torch1.5",            "torch1.6",            "torch1.7",            "torch1.8",
      "torch1.9",            "torch1.10",           "torch1.11",           "torch1.12",
      "torch1.13",           "torch1.14",           "torch1.15",           "torch1.16",
      "torch1.17",           "torch1.18",           "torch1.dead",
      ##############################################################################################################################################
      "ascii.torch1.1",      "ascii.torch1.2",      "ascii.torch1.3",      "ascii.torch1.4",
      "ascii.torch1.5",      "ascii.torch1.6",      "ascii.torch1.7",      "ascii.torch1.8",
      "ascii.torch1.9",      "ascii.torch1.10",     "ascii.torch1.11",     "ascii.torch1.12",
      "ascii.torch1.13",     "ascii.torch1.14",     "ascii.torch1.15",     "ascii.torch1.16",
      "ascii.torch1.17",     "ascii.torch1.18",     "ascii.torch1.dead",
      ##############################################################################################################################################
      "",                    "",                    "",                    "",
      "",                    "",                    "",                    "",
      "",                    "",                    "",                    "",
      "",                    "",                    "",                    "",
      "",                    "",                    "",
      ##############################################################################################################################################
      "small_fire.1",        "small_fire.2",        "small_fire.3",        "small_fire.4",
      "small_fire.5",        "small_fire.6",        "small_fire.7",        "small_fire.8",
      "small_fire.9",        "small_fire.10",       "small_fire.11",       "small_fire.12",
      "small_fire.13",       "small_fire.14",       "small_fire.15",       "small_fire.16",
      "small_fire.17",       "small_fire.18",       "small_fire.dead",
      ##############################################################################################################################################
      "smoke1.1",            "smoke1.2",            "smoke1.3",            "smoke1.4",
      "smoke1.5",            "smoke1.6",            "smoke1.7",            "smoke1.8",
      "smoke1.9",            "smoke1.10",           "smoke1.11",           "smoke1.12",
      "smoke1.13",           "smoke1.14",           "smoke1.15",           "smoke1.16",
      "smoke1.17",           "smoke1.18",           "smoke1.19",
      ##############################################################################################################################################
      "gem1.1",              "gem2.1",              "gem3.1",              "gem4.1",
      "gem5.1",              "gem6.1",              "gem7.1",              "gem8.1",
      "",                    "",                    "",                    "",
      "",                    "",                    "",                    "",
      "",                    "",                    "",
      ##############################################################################################################################################
      "gem1.2",              "gem2.2",              "gem3.2",              "gem4.2",
      "gem5.2",              "gem6.2",              "gem7.2",              "gem8.2",
      "",                    "",                    "",                    "",
      "",                    "",                    "",                    "",
      "",                    "",                    "",
      ##############################################################################################################################################
      "gem1.3",              "gem2.3",              "gem3.3",              "gem4.3",
      "gem5.3",              "gem6.3",              "gem7.3",              "gem8.3",
      "",                    "",                    "",                    "",
      "",                    "",                    "",                    "",
      "",                    "",                    "",
      ##############################################################################################################################################
      # floor1
      ##############################################################################################################################################
      "floor1.1.2x1.1", "floor1.1.2x1.2", "floor1.1.6x6.1",
      "floor1.1.6x6.2", "floor1.1.6x6.3", "floor1.1.6x6.4",
      "floor1.1.6x6.5", "floor1.1.6x6.6", "floor1.1.6x3.1",
      "floor1.1.6x3.2", "floor1.1.6x3.3", "floor1.1.6x3.4",
      "floor1.1.6x3.5", "floor1.1.6x3.6", "floor1.1.3x6.1",
      "floor1.1.3x6.2", "floor1.1.3x6.3", "floor1.1.2x2.1",
      "floor1.1.2x2.2",
      #-------------------------------------------------------
      "floor1.1.1x2.1", "floor1.2.1x2.1", "floor1.1.6x6.7",
      "floor1.1.6x6.8", "floor1.1.6x6.9", "floor1.1.6x6.10",
      "floor1.1.6x6.11", "floor1.1.6x6.12", "floor1.1.6x3.7",
      "floor1.1.6x3.8", "floor1.1.6x3.9", "floor1.1.6x3.10",
      "floor1.1.6x3.11", "floor1.1.6x3.12", "floor1.1.3x6.4",
      "floor1.1.3x6.5", "floor1.1.3x6.6", "floor1.1.2x2.3",
      "floor1.1.2x2.4",
      #-------------------------------------------------------
      "floor1.1.1x2.2", "floor1.2.1x2.2", "floor1.1.6x6.13",
      "floor1.1.6x6.14", "floor1.1.6x6.15", "floor1.1.6x6.16",
      "floor1.1.6x6.17", "floor1.1.6x6.18", "floor1.1.6x3.13",
      "floor1.1.6x3.14", "floor1.1.6x3.15", "floor1.1.6x3.16",
      "floor1.1.6x3.17", "floor1.1.6x3.18", "floor1.1.3x6.7",
      "floor1.1.3x6.8", "floor1.1.3x6.9", "floor1.2.2x2.1",
      "floor1.2.2x2.2",
      #-------------------------------------------------------
      "floor1.2.2x1.1", "floor1.2.2x1.2", "floor1.1.6x6.19",
      "floor1.1.6x6.20", "floor1.1.6x6.21", "floor1.1.6x6.22",
      "floor1.1.6x6.23", "floor1.1.6x6.24", "floor1.1.3x3.1",
      "floor1.1.3x3.2", "floor1.1.3x3.3", "floor1.2.3x3.1",
      "floor1.2.3x3.2", "floor1.2.3x3.3", "floor1.1.3x6.10",
      "floor1.1.3x6.11", "floor1.1.3x6.12", "floor1.2.2x2.3",
      "floor1.2.2x2.4",
      #-------------------------------------------------------
      "floor1.3.2x1.1", "floor1.3.2x1.2", "floor1.1.6x6.25",
      "floor1.1.6x6.26", "floor1.1.6x6.27", "floor1.1.6x6.28",
      "floor1.1.6x6.29", "floor1.1.6x6.30", "floor1.1.3x3.4",
      "floor1.1.3x3.5", "floor1.1.3x3.6", "floor1.2.3x3.4",
      "floor1.2.3x3.5", "floor1.2.3x3.6", "floor1.1.3x6.13",
      "floor1.1.3x6.14", "floor1.1.3x6.15", "floor1.3.2x2.1",
      "floor1.3.2x2.2",
      #-------------------------------------------------------
      "floor1.4.2x1.1", "floor1.4.2x1.2", "floor1.1.6x6.31",
      "floor1.1.6x6.32", "floor1.1.6x6.33", "floor1.1.6x6.34",
      "floor1.1.6x6.35", "floor1.1.6x6.36", "floor1.1.3x3.7",
      "floor1.1.3x3.8", "floor1.1.3x3.9", "floor1.2.3x3.7",
      "floor1.2.3x3.8", "floor1.2.3x3.9", "floor1.1.3x6.16",
      "floor1.1.3x6.17", "floor1.1.3x6.18", "floor1.3.2x2.3",
      "floor1.3.2x2.4",
      #-------------------------------------------------------
      "floor1.1", "floor1.2", "floor1.3", "floor1.4", "floor1.5",
      "floor1.6", "floor1.7", "floor1.8", "floor1.9", "floor1.10",
      "floor1.11", "floor1.12", "floor1.13", "floor1.14", "floor1.15",
      "floor1.16", "floor1.17", "floor1.18", "floor1.19",
      ##############################################################################################################################################
      # floor2
      ##############################################################################################################################################
      "floor2.1.2x1.1", "floor2.1.2x1.2", "floor2.1.6x6.1",
      "floor2.1.6x6.2", "floor2.1.6x6.3", "floor2.1.6x6.4",
      "floor2.1.6x6.5", "floor2.1.6x6.6", "floor2.1.6x3.1",
      "floor2.1.6x3.2", "floor2.1.6x3.3", "floor2.1.6x3.4",
      "floor2.1.6x3.5", "floor2.1.6x3.6", "floor2.1.3x6.1",
      "floor2.1.3x6.2", "floor2.1.3x6.3", "floor2.1.2x2.1",
      "floor2.1.2x2.2",
      #-------------------------------------------------------
      "floor2.1.1x2.1", "floor2.2.1x2.1", "floor2.1.6x6.7",
      "floor2.1.6x6.8", "floor2.1.6x6.9", "floor2.1.6x6.10",
      "floor2.1.6x6.11", "floor2.1.6x6.12", "floor2.1.6x3.7",
      "floor2.1.6x3.8", "floor2.1.6x3.9", "floor2.1.6x3.10",
      "floor2.1.6x3.11", "floor2.1.6x3.12", "floor2.1.3x6.4",
      "floor2.1.3x6.5", "floor2.1.3x6.6", "floor2.1.2x2.3",
      "floor2.1.2x2.4",
      #-------------------------------------------------------
      "floor2.1.1x2.2", "floor2.2.1x2.2", "floor2.1.6x6.13",
      "floor2.1.6x6.14", "floor2.1.6x6.15", "floor2.1.6x6.16",
      "floor2.1.6x6.17", "floor2.1.6x6.18", "floor2.1.6x3.13",
      "floor2.1.6x3.14", "floor2.1.6x3.15", "floor2.1.6x3.16",
      "floor2.1.6x3.17", "floor2.1.6x3.18", "floor2.1.3x6.7",
      "floor2.1.3x6.8", "floor2.1.3x6.9", "floor2.2.2x2.1",
      "floor2.2.2x2.2",
      #-------------------------------------------------------
      "floor2.2.2x1.1", "floor2.2.2x1.2", "floor2.1.6x6.19",
      "floor2.1.6x6.20", "floor2.1.6x6.21", "floor2.1.6x6.22",
      "floor2.1.6x6.23", "floor2.1.6x6.24", "floor2.1.3x3.1",
      "floor2.1.3x3.2", "floor2.1.3x3.3", "floor2.2.3x3.1",
      "floor2.2.3x3.2", "floor2.2.3x3.3", "floor2.1.3x6.10",
      "floor2.1.3x6.11", "floor2.1.3x6.12", "floor2.2.2x2.3",
      "floor2.2.2x2.4",
      #-------------------------------------------------------
      "floor2.3.2x1.1", "floor2.3.2x1.2", "floor2.1.6x6.25",
      "floor2.1.6x6.26", "floor2.1.6x6.27", "floor2.1.6x6.28",
      "floor2.1.6x6.29", "floor2.1.6x6.30", "floor2.1.3x3.4",
      "floor2.1.3x3.5", "floor2.1.3x3.6", "floor2.2.3x3.4",
      "floor2.2.3x3.5", "floor2.2.3x3.6", "floor2.1.3x6.13",
      "floor2.1.3x6.14", "floor2.1.3x6.15", "floor2.3.2x2.1",
      "floor2.3.2x2.2",
      #-------------------------------------------------------
      "floor2.4.2x1.1", "floor2.4.2x1.2", "floor2.1.6x6.31",
      "floor2.1.6x6.32", "floor2.1.6x6.33", "floor2.1.6x6.34",
      "floor2.1.6x6.35", "floor2.1.6x6.36", "floor2.1.3x3.7",
      "floor2.1.3x3.8", "floor2.1.3x3.9", "floor2.2.3x3.7",
      "floor2.2.3x3.8", "floor2.2.3x3.9", "floor2.1.3x6.16",
      "floor2.1.3x6.17", "floor2.1.3x6.18", "floor2.3.2x2.3",
      "floor2.3.2x2.4",
      #-------------------------------------------------------
      "floor2.1", "floor2.2", "floor2.3", "floor2.4", "floor2.5",
      "floor2.6", "floor2.7", "floor2.8", "floor2.9", "floor2.10",
      "floor2.11", "floor2.12", "floor2.13", "floor2.14", "floor2.15",
      "floor2.16", "floor2.17", "floor2.18", "floor2.19",
      ##############################################################################################################################################
      # wall1, for normal walls
      ##############################################################################################################################################
      "wall1.1.2x1.1", "wall1.1.2x1.2", "wall1.1.6x6.1",
      "wall1.1.6x6.2", "wall1.1.6x6.3", "wall1.1.6x6.4",
      "wall1.1.6x6.5", "wall1.1.6x6.6", "wall1.1.6x3.1",
      "wall1.1.6x3.2", "wall1.1.6x3.3", "wall1.1.6x3.4",
      "wall1.1.6x3.5", "wall1.1.6x3.6", "wall1.1.3x6.1",
      "wall1.1.3x6.2", "wall1.1.3x6.3", "wall1.1.2x2.1",
      "wall1.1.2x2.2",
      #-------------------------------------------------------
      "wall1.1.1x2.1", "wall1.2.1x2.1", "wall1.1.6x6.7",
      "wall1.1.6x6.8", "wall1.1.6x6.9", "wall1.1.6x6.10",
      "wall1.1.6x6.11", "wall1.1.6x6.12", "wall1.1.6x3.7",
      "wall1.1.6x3.8", "wall1.1.6x3.9", "wall1.1.6x3.10",
      "wall1.1.6x3.11", "wall1.1.6x3.12", "wall1.1.3x6.4",
      "wall1.1.3x6.5", "wall1.1.3x6.6", "wall1.1.2x2.3",
      "wall1.1.2x2.4",
      #-------------------------------------------------------
      "wall1.1.1x2.2", "wall1.2.1x2.2", "wall1.1.6x6.13",
      "wall1.1.6x6.14", "wall1.1.6x6.15", "wall1.1.6x6.16",
      "wall1.1.6x6.17", "wall1.1.6x6.18", "wall1.1.6x3.13",
      "wall1.1.6x3.14", "wall1.1.6x3.15", "wall1.1.6x3.16",
      "wall1.1.6x3.17", "wall1.1.6x3.18", "wall1.1.3x6.7",
      "wall1.1.3x6.8", "wall1.1.3x6.9", "wall1.2.2x2.1",
      "wall1.2.2x2.2",
      #-------------------------------------------------------
      "wall1.2.2x1.1", "wall1.2.2x1.2", "wall1.1.6x6.19",
      "wall1.1.6x6.20", "wall1.1.6x6.21", "wall1.1.6x6.22",
      "wall1.1.6x6.23", "wall1.1.6x6.24", "wall1.1.3x3.1",
      "wall1.1.3x3.2", "wall1.1.3x3.3", "wall1.2.3x3.1",
      "wall1.2.3x3.2", "wall1.2.3x3.3", "wall1.1.3x6.10",
      "wall1.1.3x6.11", "wall1.1.3x6.12", "wall1.2.2x2.3",
      "wall1.2.2x2.4",
      #-------------------------------------------------------
      "wall1.3.2x1.1", "wall1.3.2x1.2", "wall1.1.6x6.25",
      "wall1.1.6x6.26", "wall1.1.6x6.27", "wall1.1.6x6.28",
      "wall1.1.6x6.29", "wall1.1.6x6.30", "wall1.1.3x3.4",
      "wall1.1.3x3.5", "wall1.1.3x3.6", "wall1.2.3x3.4",
      "wall1.2.3x3.5", "wall1.2.3x3.6", "wall1.1.3x6.13",
      "wall1.1.3x6.14", "wall1.1.3x6.15", "wall1.3.2x2.1",
      "wall1.3.2x2.2",
      #-------------------------------------------------------
      "wall1.4.2x1.1", "wall1.4.2x1.2", "wall1.1.6x6.31",
      "wall1.1.6x6.32", "wall1.1.6x6.33", "wall1.1.6x6.34",
      "wall1.1.6x6.35", "wall1.1.6x6.36", "wall1.1.3x3.7",
      "wall1.1.3x3.8", "wall1.1.3x3.9", "wall1.2.3x3.7",
      "wall1.2.3x3.8", "wall1.2.3x3.9", "wall1.1.3x6.16",
      "wall1.1.3x6.17", "wall1.1.3x6.18", "wall1.3.2x2.3",
      "wall1.3.2x2.4",
      #-------------------------------------------------------
      "wall1.1", "wall1.2", "wall1.3", "wall1.4", "wall1.5",
      "wall1.6", "wall1.7", "wall1.8", "wall1.9", "wall1.10",
      "wall1.11", "wall1.12", "wall1.13", "wall1.14", "wall1.15",
      "wall1.16", "wall1.17", "wall1.18", "wall1.19",
      ##############################################################################################################################################
      # wall2, for normal walls
      ##############################################################################################################################################
      "wall2.1.2x1.1", "wall2.1.2x1.2", "wall2.1.6x6.1",
      "wall2.1.6x6.2", "wall2.1.6x6.3", "wall2.1.6x6.4",
      "wall2.1.6x6.5", "wall2.1.6x6.6", "wall2.1.6x3.1",
      "wall2.1.6x3.2", "wall2.1.6x3.3", "wall2.1.6x3.4",
      "wall2.1.6x3.5", "wall2.1.6x3.6", "wall2.1.3x6.1",
      "wall2.1.3x6.2", "wall2.1.3x6.3", "wall2.1.2x2.1",
      "wall2.1.2x2.2",
      #-------------------------------------------------------
      "wall2.1.1x2.1", "wall2.2.1x2.1", "wall2.1.6x6.7",
      "wall2.1.6x6.8", "wall2.1.6x6.9", "wall2.1.6x6.10",
      "wall2.1.6x6.11", "wall2.1.6x6.12", "wall2.1.6x3.7",
      "wall2.1.6x3.8", "wall2.1.6x3.9", "wall2.1.6x3.10",
      "wall2.1.6x3.11", "wall2.1.6x3.12", "wall2.1.3x6.4",
      "wall2.1.3x6.5", "wall2.1.3x6.6", "wall2.1.2x2.3",
      "wall2.1.2x2.4",
      #-------------------------------------------------------
      "wall2.1.1x2.2", "wall2.2.1x2.2", "wall2.1.6x6.13",
      "wall2.1.6x6.14", "wall2.1.6x6.15", "wall2.1.6x6.16",
      "wall2.1.6x6.17", "wall2.1.6x6.18", "wall2.1.6x3.13",
      "wall2.1.6x3.14", "wall2.1.6x3.15", "wall2.1.6x3.16",
      "wall2.1.6x3.17", "wall2.1.6x3.18", "wall2.1.3x6.7",
      "wall2.1.3x6.8", "wall2.1.3x6.9", "wall2.2.2x2.1",
      "wall2.2.2x2.2",
      #-------------------------------------------------------
      "wall2.2.2x1.1", "wall2.2.2x1.2", "wall2.1.6x6.19",
      "wall2.1.6x6.20", "wall2.1.6x6.21", "wall2.1.6x6.22",
      "wall2.1.6x6.23", "wall2.1.6x6.24", "wall2.1.3x3.1",
      "wall2.1.3x3.2", "wall2.1.3x3.3", "wall2.2.3x3.1",
      "wall2.2.3x3.2", "wall2.2.3x3.3", "wall2.1.3x6.10",
      "wall2.1.3x6.11", "wall2.1.3x6.12", "wall2.2.2x2.3",
      "wall2.2.2x2.4",
      #-------------------------------------------------------
      "wall2.3.2x1.1", "wall2.3.2x1.2", "wall2.1.6x6.25",
      "wall2.1.6x6.26", "wall2.1.6x6.27", "wall2.1.6x6.28",
      "wall2.1.6x6.29", "wall2.1.6x6.30", "wall2.1.3x3.4",
      "wall2.1.3x3.5", "wall2.1.3x3.6", "wall2.2.3x3.4",
      "wall2.2.3x3.5", "wall2.2.3x3.6", "wall2.1.3x6.13",
      "wall2.1.3x6.14", "wall2.1.3x6.15", "wall2.3.2x2.1",
      "wall2.3.2x2.2",
      #-------------------------------------------------------
      "wall2.4.2x1.1", "wall2.4.2x1.2", "wall2.1.6x6.31",
      "wall2.1.6x6.32", "wall2.1.6x6.33", "wall2.1.6x6.34",
      "wall2.1.6x6.35", "wall2.1.6x6.36", "wall2.1.3x3.7",
      "wall2.1.3x3.8", "wall2.1.3x3.9", "wall2.2.3x3.7",
      "wall2.2.3x3.8", "wall2.2.3x3.9", "wall2.1.3x6.16",
      "wall2.1.3x6.17", "wall2.1.3x6.18", "wall2.3.2x2.3",
      "wall2.3.2x2.4",
      #-------------------------------------------------------
      "wall2.1", "wall2.2", "wall2.3", "wall2.4", "wall2.5",
      "wall2.6", "wall2.7", "wall2.8", "wall2.9", "wall2.10",
      "wall2.11", "wall2.12", "wall2.13", "wall2.14", "wall2.15",
      "wall2.16", "wall2.17", "wall2.18", "wall2.19",
      ##############################################################################################################################################
      # rock1, for normal rocks
      ##############################################################################################################################################
      "rock1.1.2x1.1", "rock1.1.2x1.2", "rock1.1.6x6.1",
      "rock1.1.6x6.2", "rock1.1.6x6.3", "rock1.1.6x6.4",
      "rock1.1.6x6.5", "rock1.1.6x6.6", "rock1.1.6x3.1",
      "rock1.1.6x3.2", "rock1.1.6x3.3", "rock1.1.6x3.4",
      "rock1.1.6x3.5", "rock1.1.6x3.6", "rock1.1.3x6.1",
      "rock1.1.3x6.2", "rock1.1.3x6.3", "rock1.1.2x2.1",
      "rock1.1.2x2.2",
      #-------------------------------------------------------
      "rock1.1.1x2.1", "rock1.2.1x2.1", "rock1.1.6x6.7",
      "rock1.1.6x6.8", "rock1.1.6x6.9", "rock1.1.6x6.10",
      "rock1.1.6x6.11", "rock1.1.6x6.12", "rock1.1.6x3.7",
      "rock1.1.6x3.8", "rock1.1.6x3.9", "rock1.1.6x3.10",
      "rock1.1.6x3.11", "rock1.1.6x3.12", "rock1.1.3x6.4",
      "rock1.1.3x6.5", "rock1.1.3x6.6", "rock1.1.2x2.3",
      "rock1.1.2x2.4",
      #-------------------------------------------------------
      "rock1.1.1x2.2", "rock1.2.1x2.2", "rock1.1.6x6.13",
      "rock1.1.6x6.14", "rock1.1.6x6.15", "rock1.1.6x6.16",
      "rock1.1.6x6.17", "rock1.1.6x6.18", "rock1.1.6x3.13",
      "rock1.1.6x3.14", "rock1.1.6x3.15", "rock1.1.6x3.16",
      "rock1.1.6x3.17", "rock1.1.6x3.18", "rock1.1.3x6.7",
      "rock1.1.3x6.8", "rock1.1.3x6.9", "rock1.2.2x2.1",
      "rock1.2.2x2.2",
      #-------------------------------------------------------
      "rock1.2.2x1.1", "rock1.2.2x1.2", "rock1.1.6x6.19",
      "rock1.1.6x6.20", "rock1.1.6x6.21", "rock1.1.6x6.22",
      "rock1.1.6x6.23", "rock1.1.6x6.24", "rock1.1.3x3.1",
      "rock1.1.3x3.2", "rock1.1.3x3.3", "rock1.2.3x3.1",
      "rock1.2.3x3.2", "rock1.2.3x3.3", "rock1.1.3x6.10",
      "rock1.1.3x6.11", "rock1.1.3x6.12", "rock1.2.2x2.3",
      "rock1.2.2x2.4",
      #-------------------------------------------------------
      "rock1.3.2x1.1", "rock1.3.2x1.2", "rock1.1.6x6.25",
      "rock1.1.6x6.26", "rock1.1.6x6.27", "rock1.1.6x6.28",
      "rock1.1.6x6.29", "rock1.1.6x6.30", "rock1.1.3x3.4",
      "rock1.1.3x3.5", "rock1.1.3x3.6", "rock1.2.3x3.4",
      "rock1.2.3x3.5", "rock1.2.3x3.6", "rock1.1.3x6.13",
      "rock1.1.3x6.14", "rock1.1.3x6.15", "rock1.3.2x2.1",
      "rock1.3.2x2.2",
      #-------------------------------------------------------
      "rock1.4.2x1.1", "rock1.4.2x1.2", "rock1.1.6x6.31",
      "rock1.1.6x6.32", "rock1.1.6x6.33", "rock1.1.6x6.34",
      "rock1.1.6x6.35", "rock1.1.6x6.36", "rock1.1.3x3.7",
      "rock1.1.3x3.8", "rock1.1.3x3.9", "rock1.2.3x3.7",
      "rock1.2.3x3.8", "rock1.2.3x3.9", "rock1.1.3x6.16",
      "rock1.1.3x6.17", "rock1.1.3x6.18", "rock1.3.2x2.3",
      "rock1.3.2x2.4",
      #-------------------------------------------------------
      "rock1.1", "rock1.2", "rock1.3", "rock1.4", "rock1.5",
      "rock1.6", "rock1.7", "rock1.8", "rock1.9", "rock1.10",
      "rock1.11", "rock1.12", "rock1.13", "rock1.14", "rock1.15",
      "rock1.16", "rock1.17", "rock1.18", "rock1.19",
      ##############################################################################################################################################
      # rock2, for normal rocks
      ##############################################################################################################################################
      "rock2.1.2x1.1", "rock2.1.2x1.2", "rock2.1.6x6.1",
      "rock2.1.6x6.2", "rock2.1.6x6.3", "rock2.1.6x6.4",
      "rock2.1.6x6.5", "rock2.1.6x6.6", "rock2.1.6x3.1",
      "rock2.1.6x3.2", "rock2.1.6x3.3", "rock2.1.6x3.4",
      "rock2.1.6x3.5", "rock2.1.6x3.6", "rock2.1.3x6.1",
      "rock2.1.3x6.2", "rock2.1.3x6.3", "rock2.1.2x2.1",
      "rock2.1.2x2.2",
      #-------------------------------------------------------
      "rock2.1.1x2.1", "rock2.2.1x2.1", "rock2.1.6x6.7",
      "rock2.1.6x6.8", "rock2.1.6x6.9", "rock2.1.6x6.10",
      "rock2.1.6x6.11", "rock2.1.6x6.12", "rock2.1.6x3.7",
      "rock2.1.6x3.8", "rock2.1.6x3.9", "rock2.1.6x3.10",
      "rock2.1.6x3.11", "rock2.1.6x3.12", "rock2.1.3x6.4",
      "rock2.1.3x6.5", "rock2.1.3x6.6", "rock2.1.2x2.3",
      "rock2.1.2x2.4",
      #-------------------------------------------------------
      "rock2.1.1x2.2", "rock2.2.1x2.2", "rock2.1.6x6.13",
      "rock2.1.6x6.14", "rock2.1.6x6.15", "rock2.1.6x6.16",
      "rock2.1.6x6.17", "rock2.1.6x6.18", "rock2.1.6x3.13",
      "rock2.1.6x3.14", "rock2.1.6x3.15", "rock2.1.6x3.16",
      "rock2.1.6x3.17", "rock2.1.6x3.18", "rock2.1.3x6.7",
      "rock2.1.3x6.8", "rock2.1.3x6.9", "rock2.2.2x2.1",
      "rock2.2.2x2.2",
      #-------------------------------------------------------
      "rock2.2.2x1.1", "rock2.2.2x1.2", "rock2.1.6x6.19",
      "rock2.1.6x6.20", "rock2.1.6x6.21", "rock2.1.6x6.22",
      "rock2.1.6x6.23", "rock2.1.6x6.24", "rock2.1.3x3.1",
      "rock2.1.3x3.2", "rock2.1.3x3.3", "rock2.2.3x3.1",
      "rock2.2.3x3.2", "rock2.2.3x3.3", "rock2.1.3x6.10",
      "rock2.1.3x6.11", "rock2.1.3x6.12", "rock2.2.2x2.3",
      "rock2.2.2x2.4",
      #-------------------------------------------------------
      "rock2.3.2x1.1", "rock2.3.2x1.2", "rock2.1.6x6.25",
      "rock2.1.6x6.26", "rock2.1.6x6.27", "rock2.1.6x6.28",
      "rock2.1.6x6.29", "rock2.1.6x6.30", "rock2.1.3x3.4",
      "rock2.1.3x3.5", "rock2.1.3x3.6", "rock2.2.3x3.4",
      "rock2.2.3x3.5", "rock2.2.3x3.6", "rock2.1.3x6.13",
      "rock2.1.3x6.14", "rock2.1.3x6.15", "rock2.3.2x2.1",
      "rock2.3.2x2.2",
      #-------------------------------------------------------
      "rock2.4.2x1.1", "rock2.4.2x1.2", "rock2.1.6x6.31",
      "rock2.1.6x6.32", "rock2.1.6x6.33", "rock2.1.6x6.34",
      "rock2.1.6x6.35", "rock2.1.6x6.36", "rock2.1.3x3.7",
      "rock2.1.3x3.8", "rock2.1.3x3.9", "rock2.2.3x3.7",
      "rock2.2.3x3.8", "rock2.2.3x3.9", "rock2.1.3x6.16",
      "rock2.1.3x6.17", "rock2.1.3x6.18", "rock2.3.2x2.3",
      "rock2.3.2x2.4",
      #-------------------------------------------------------
      "rock2.1", "rock2.2", "rock2.3", "rock2.4", "rock2.5",
      "rock2.6", "rock2.7", "rock2.8", "rock2.9", "rock2.10",
      "rock2.11", "rock2.12", "rock2.13", "rock2.14", "rock2.15",
      "rock2.16", "rock2.17", "rock2.18", "rock2.19",
      ##############################################################################################################################################
      # deco for above
      ##############################################################################################################################################
      "wall_deco1.tl.1", "wall_deco1.tl.2", "wall_deco1.tl.3",
      "wall_deco1.tl.4", "wall_deco1.tl.5", "wall_deco1.tl.6",
      "wall_deco1.top.1", "wall_deco1.top.2", "wall_deco1.top.3",
      "wall_deco1.top.4", "wall_deco1.top.5", "wall_deco1.top.6",
      "wall_deco1.top.7",
      "wall_deco1.tr.1", "wall_deco1.tr.2", "wall_deco1.tr.3",
      "wall_deco1.tr.4", "wall_deco1.tr.5", "wall_deco1.tr.6",
      #-------------------------------------------------------
      "wall_deco1.left.1", "wall_deco1.left.2", "wall_deco1.left.3",
      "wall_deco1.left.4", "wall_deco1.left.5", "wall_deco1.left.6",
      "", "", "", "", "", "", "",
      "wall_deco1.right.1", "wall_deco1.right.2", "wall_deco1.right.3",
      "wall_deco1.right.4", "wall_deco1.right.5", "wall_deco1.right.6",
      #-------------------------------------------------------
      "wall_deco1.bl.1", "wall_deco1.bl.2", "wall_deco1.bl.3",
      "wall_deco1.bl.4", "wall_deco1.bl.5", "wall_deco1.bl.6",
      "wall_deco1.bot.1", "wall_deco1.bot.2", "wall_deco1.bot.3",
      "wall_deco1.bot.4", "wall_deco1.bot.5", "wall_deco1.bot.6",
      "wall_deco1.bot.7",
      "wall_deco1.br.1", "wall_deco1.br.2", "wall_deco1.br.3",
      "wall_deco1.br.4", "wall_deco1.br.5", "wall_deco1.br.6",
      ##############################################################################################################################################
      # shadow deco
      ##############################################################################################################################################
      "wall_shadow_deco1.tl.1", "wall_shadow_deco1.tl.2", "wall_shadow_deco1.tl.3",
      "wall_shadow_deco1.tl.4", "wall_shadow_deco1.tl.5", "wall_shadow_deco1.tl.6",
      "wall_shadow_deco1.top.1", "wall_shadow_deco1.top.2", "wall_shadow_deco1.top.3",
      "wall_shadow_deco1.top.4", "wall_shadow_deco1.top.5", "wall_shadow_deco1.top.6",
      "wall_shadow_deco1.top.7",
      "wall_shadow_deco1.tr.1", "wall_shadow_deco1.tr.2", "wall_shadow_deco1.tr.3",
      "wall_shadow_deco1.tr.4", "wall_shadow_deco1.tr.5", "wall_shadow_deco1.tr.6",
      #-------------------------------------------------------
      "wall_shadow_deco1.left.1", "wall_shadow_deco1.left.2", "wall_shadow_deco1.left.3",
      "wall_shadow_deco1.left.4", "wall_shadow_deco1.left.5", "wall_shadow_deco1.left.6",
      "", "", "", "", "", "", "",
      "wall_shadow_deco1.right.1", "wall_shadow_deco1.right.2", "wall_shadow_deco1.right.3",
      "wall_shadow_deco1.right.4", "wall_shadow_deco1.right.5", "wall_shadow_deco1.right.6",
      #-------------------------------------------------------
      "wall_shadow_deco1.bl.1", "wall_shadow_deco1.bl.2", "wall_shadow_deco1.bl.3",
      "wall_shadow_deco1.bl.4", "wall_shadow_deco1.bl.5", "wall_shadow_deco1.bl.6",
      "wall_shadow_deco1.bot.1", "wall_shadow_deco1.bot.2", "wall_shadow_deco1.bot.3",
      "wall_shadow_deco1.bot.4", "wall_shadow_deco1.bot.5", "wall_shadow_deco1.bot.6",
      "wall_shadow_deco1.bot.7",
      "wall_shadow_deco1.br.1", "wall_shadow_deco1.br.2", "wall_shadow_deco1.br.3",
      "wall_shadow_deco1.br.4", "wall_shadow_deco1.br.5", "wall_shadow_deco1.br.6",
      ##############################################################################################################################################
      "floor3.1", "floor3.2", "floor3.3", "floor3.4", "floor3.5",
      "floor3.6", "floor3.7", "floor3.8", "floor3.9", "floor3.10",
      "floor3.11", "floor3.12", "floor3.13", "floor3.14", "floor3.15",
      "floor3.16", "floor3.17", "floor3.18", "floor3.19",
      ##############################################################################################################################################
      "floor4.1", "floor4.2", "floor4.3", "floor4.4", "floor4.5",
      "floor4.6", "floor4.7", "floor4.8", "floor4.9", "floor4.10",
      "floor4.11", "floor4.12", "floor4.13", "floor4.14", "floor4.15",
      "floor4.16", "floor4.17", "floor4.18", "floor4.19",
      ##############################################################################################################################################
      "floor5.1", "floor5.2", "floor5.3", "floor5.4", "floor5.5",
      "floor5.6", "floor5.7", "floor5.8", "floor5.9", "floor5.10",
      "floor5.11", "floor5.12", "floor5.13", "floor5.14", "floor5.15",
      "floor5.16", "floor5.17", "floor5.18", "floor5.19",
      ##############################################################################################################################################
      "floor6.1", "floor6.2", "floor6.3", "floor6.4", "floor6.5",
      "floor6.6", "floor6.7", "floor6.8", "floor6.9", "floor6.10",
      "floor6.11", "floor6.12", "floor6.13", "floor6.14", "floor6.15",
      "floor6.16", "floor6.17", "floor6.18", "floor6.19",
      ##############################################################################################################################################
      "floor7.1", "floor7.2", "floor7.3", "floor7.4", "floor7.5",
      "floor7.6", "floor7.7", "floor7.8", "floor7.9", "floor7.10",
      "floor7.11", "floor7.12", "floor7.13", "floor7.14", "floor7.15",
      "floor7.16", "floor7.17", "floor7.18", "floor7.19",
      ##############################################################################################################################################
      "floor8.1", "floor8.2", "floor8.3", "floor8.4", "floor8.5",
      "floor8.6", "floor8.7", "floor8.8", "floor8.9", "floor8.10",
      "floor8.11", "floor8.12", "floor8.13", "floor8.14", "floor8.15",
      "floor8.16", "floor8.17", "floor8.18", "floor8.19",
      ##############################################################################################################################################
      "floor9.1", "floor9.2", "floor9.3", "floor9.4", "floor9.5",
      "floor9.6", "floor9.7", "floor9.8", "floor9.9", "floor9.10",
      "floor9.11", "floor9.12", "floor9.13", "floor9.14", "floor9.15",
      "floor9.16", "floor9.17", "floor9.18", "floor9.19",
      ##############################################################################################################################################
      "corridor1.1", "corridor1.2", "corridor1.3", "corridor1.4",
      "corridor1.5", "corridor1.6", "corridor1.7", "corridor1.8",
      "corridor1.9", "corridor1.10", "corridor1.11", "corridor1.12",
      "corridor1.13", "corridor1.14", "corridor1.15", "corridor1.16",
      "corridor1.17", "corridor1.18", "corridor1.19",
      ##############################################################################################################################################
      "dirt1.1", "dirt1.2", "dirt1.3", "dirt1.4", "dirt1.5",
      "dirt1.6", "dirt1.7", "dirt1.8", "dirt1.9", "dirt1.10",
      "dirt1.11", "dirt1.12", "dirt1.13", "dirt1.14", "dirt1.15",
      "dirt1.16", "dirt1.17", "dirt1.18", "dirt1.19",
      ##############################################################################################################################################
      "dirt2.1", "dirt2.2", "dirt2.3", "dirt2.4", "dirt2.5",
      "dirt2.6", "dirt2.7", "dirt2.8", "dirt2.9", "dirt2.10",
      "dirt2.11", "dirt2.12", "dirt2.13", "dirt2.14", "dirt2.15",
      "dirt2.16", "dirt2.17", "dirt2.18", "dirt2.19",
      ##############################################################################################################################################
      "dirt3.1", "dirt3.2", "dirt3.3", "dirt3.4", "dirt3.5",
      "dirt3.6", "dirt3.7", "dirt3.8", "dirt3.9", "dirt3.10",
      "dirt3.11", "dirt3.12", "dirt3.13", "dirt3.14", "dirt3.15",
      "dirt3.16", "dirt3.17", "dirt3.18", "dirt3.19",
    ]

    zx.tile_load_arr_color_and_black_and_white(
        file="data/gfx/16x16.tga",
        name="16x16", width=16, height=16, arr=tiles)

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
            "entrance1.open",
            "",
            ##############################################################################################################################################
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
            ##############################################################################################################################################
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
            ##############################################################################################################################################
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
            ##############################################################################################################################################
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
            ##############################################################################################################################################
            "slime2.1.100",
            "slime2.2.100",
            "slime2.3.100",
            "slime2.4.100",
            "slime2.5.100",
            "slime2.6.100",
            "slime2.7.100",
            "slime2.8.100",
            "slime2.1.75",
            "slime2.2.75",
            "slime2.3.75",
            "slime2.4.75",
            "slime2.5.75",
            "slime2.6.75",
            "slime2.7.75",
            "slime2.8.75",
            "slime2.1.50",
            "slime2.2.50",
            "slime2.3.50",
            "slime2.4.50",
            "slime2.5.50",
            "slime2.6.50",
            "slime2.7.50",
            "slime2.8.50",
            "slime2.1.25",
            "slime2.2.25",
            "slime2.3.25",
            "slime2.4.25",
            "slime2.5.25",
            "slime2.6.25",
            "slime2.7.25",
            "slime2.8.25",
            ##############################################################################################################################################
            "ascii.slime2.1.100",
            "ascii.slime2.2.100",
            "ascii.slime2.3.100",
            "ascii.slime2.4.100",
            "ascii.slime2.5.100",
            "ascii.slime2.6.100",
            "ascii.slime2.7.100",
            "ascii.slime2.8.100",
            "ascii.slime2.1.75",
            "ascii.slime2.2.75",
            "ascii.slime2.3.75",
            "ascii.slime2.4.75",
            "ascii.slime2.5.75",
            "ascii.slime2.6.75",
            "ascii.slime2.7.75",
            "ascii.slime2.8.75",
            "ascii.slime2.1.50",
            "ascii.slime2.2.50",
            "ascii.slime2.3.50",
            "ascii.slime2.4.50",
            "ascii.slime2.5.50",
            "ascii.slime2.6.50",
            "ascii.slime2.7.50",
            "ascii.slime2.8.50",
            "ascii.slime2.1.25",
            "ascii.slime2.2.25",
            "ascii.slime2.3.25",
            "ascii.slime2.4.25",
            "ascii.slime2.5.25",
            "ascii.slime2.6.25",
            "ascii.slime2.7.25",
            "ascii.slime2.8.25",
            ##############################################################################################################################################
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
            ##############################################################################################################################################
            "door1.100",
            "door1.75",
            "door1.50",
            "door1.25",
            "door1.dead",
            "door1.open",
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
            ##############################################################################################################################################
            "splat1.1", "splat1.2", "splat1.3", "splat1.4",
            "splat1.5", "splat1.6", "splat1.7", "splat1.8",
            "splat1.9", "splat1.10", "splat1.11", "splat1.12",
            "splat1.13", "splat1.14",
            "",
            "",
            ##############################################################################################################################################
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
            "", "", "", "", "", "", "", "",
            "", "", "", "", "", "", "", "",
            "ripple1.1", "ripple1.2", "ripple1.3", "ripple1.4",
            "ripple1.5", "ripple1.6", "ripple1.7", "ripple1.8",
            "ripple2.1", "ripple2.2", "ripple2.3", "ripple2.4",
            "ripple2.5", "ripple2.6", "ripple2.7", "ripple2.8",
            "deep_water1.1", "deep_water1.2", "deep_water1.3", "deep_water1.4", "deep_water1.5", "deep_water1.6", "deep_water1.7", "deep_water1.8",
            "deep_water1.9", "deep_water1.10", "deep_water1.11", "deep_water1.12", "deep_water1.13", "deep_water1.14", "deep_water1.15", "deep_water1.16",
            "lava1.1", "lava1.2", "lava1.3", "lava1.4", "lava1.5", "lava1.6", "lava1.7", "lava1.8",
            "lava1.9", "lava1.10", "lava1.11", "lava1.12", "lava1.13", "lava1.14", "lava1.15", "lava1.16",
            "chasm1.1", "chasm1.2", "chasm1.3", "chasm1.4", "chasm1.5", "chasm1.6", "chasm1.7", "chasm1.8",
            "chasm1.9", "chasm1.10", "chasm1.11", "chasm1.12", "chasm1.13", "chasm1.14", "chasm1.15", "chasm1.16",
            "", "", "", "", "", "", "", "",
            "", "", "", "", "", "", "", "",
            "", "", "", "", "", "", "", "",
            "", "", "", "", "", "", "", "",
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
            "sword1_carry.1",
            "sword1_carry.2",
            "sword1_swing_left.1",
            "sword1_swing_left.2",
            "sword1_swing_left.3",
            "sword1_swing_left.4",
            "sword1_swing_left.5",
            "sword1_swing_left.6",
            ################################################################################################################################################
            "",
            "",
            "",
            "sword1_swing_up.1",
            "sword1_swing_up.2",
            "sword1_swing_up.3",
            "sword1_swing_up.4",
            "sword1_swing_up.5",
            "sword1_swing_up.6",
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
        "claws1.49", "claws1.50", "claws1.51", "claws1.52",
    ]

    zx.tile_load_arr_color_and_black_and_white(
        file="data/gfx/hit_claws_50x50px.tga",
        name="claws", width=25, height=25, arr=tiles)

init_solid()
init_title()
init_light()
init_bloom()
init_ui_status_bar()
init_ui_status_bar_title()
init_ui_dead()
init_ui_action_bar()
init_ui_action_bar_highlight()
init_16x16()
init_32x32()
init_32x32_water()
init_32x32_lava()
init_32x32_chasm()
init_32x32_deep_water()
init_32x32_surface_effects()
init_weapons_tiles()
init_claws_tiles()
init_ui_blood()
