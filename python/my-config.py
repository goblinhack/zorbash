import mm
import os


def set_game_video_pix_width(value):
    mm.game_video_pix_width = value


def get_game_video_pix_width():
    return (mm.game_video_pix_width)


def set_game_video_pix_height(value):
    mm.game_video_pix_height = value


def get_game_video_pix_height():
    return (mm.game_video_pix_height)


def set_game_sound_volume(value):
    mm.game_sound_volume = value


def get_game_sound_volume():
    return (mm.game_sound_volume)


def set_game_music_volume(value):
    mm.game_music_volume = value


def get_game_music_volume():
    return (mm.game_music_volume)


def set_game_display_sync(value):
    mm.game_display_sync = value


def get_game_display_sync():
    return (mm.game_display_sync)


def set_game_full_screen(value):
    mm.game_full_screen = value


def get_game_full_screen():
    return (mm.game_full_screen)


def set_game_fps_counter(value):
    mm.game_fps_counter = value


def get_game_fps_counter():
    return (mm.game_fps_counter)


def save_game_config():
    with open(os.path.normcase(
               os.path.join(
                os.environ["APPDATA"], 'zorbash-config.py')), 'w') as f:

        f.write("import mm\n")
        f.write("mm.game_video_pix_width = %d\n" % mm.game_video_pix_width)
        f.write("mm.game_video_pix_height = %d\n" % mm.game_video_pix_height)
        f.write("mm.game_sound_volume = %d\n" % mm.game_sound_volume)
        f.write("mm.game_music_volume = %d\n" % mm.game_music_volume)
        f.write("mm.game_display_sync = %d\n" % mm.game_display_sync)
        f.write("mm.game_full_screen = %d\n" % mm.game_full_screen)
        f.write("mm.game_fps_counter = %d\n" % mm.game_fps_counter)
