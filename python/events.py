import my


def on_main_menu_select(unused):
    my.con("ON MAIN MENU")
    my.music_play(name="intro")


def on_initial_dungeon_menu_select(unused):
    my.con("ON INIT MENU")


def on_next_dungeon_menu_select(unused):
    my.con("ON NEXT MENU")
    my.music_play(name="relaxing")


def on_level_change(level_no, is_shop_level, is_crystal_level, is_boss_level, is_final_boss_level):
    my.con("ON LEVEL CHANGE")


def on_player_death(level_no):
    my.con("ON PLAYER DEATH")
