import my


def on_main_menu_select(unused):
    my.music_play(name="intro")


def on_initial_dungeon_menu_select(unused):
    return


def on_next_dungeon_menu_select(unused):
    my.music_play(name="relaxing")


def on_level_change(level_no, is_shop_level, is_crystal_level, is_boss_level, is_final_boss_level):
    return


def on_player_death(level_no):
    return
