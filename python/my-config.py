import zx
import os


def set_game_video_pix_width(value):
    zx.game_video_pix_width = value


def get_game_video_pix_width():
    return (zx.game_video_pix_width)


def set_game_video_pix_height(value):
    zx.game_video_pix_height = value


def get_game_video_pix_height():
    return (zx.game_video_pix_height)


def set_game_sound_volume(value):
    zx.game_sound_volume = value


def get_game_sound_volume():
    return (zx.game_sound_volume)


def set_game_music_volume(value):
    zx.game_music_volume = value


def get_game_music_volume():
    return (zx.game_music_volume)


def set_game_display_sync(value):
    zx.game_display_sync = value


def get_game_display_sync():
    return (zx.game_display_sync)


def set_game_full_screen(value):
    zx.game_full_screen = value


def get_game_full_screen():
    return (zx.game_full_screen)


def set_game_fps_counter(value):
    zx.game_fps_counter = value


def get_game_fps_counter():
    return (zx.game_fps_counter)


def save_game_config():
    with open(os.path.normcase(
               os.path.join(
                os.environ["APPDATA"], 'zorbash-config.py')), 'w') as f:

        f.write("import zx\n")
        f.write("zx.game_video_pix_width = %d\n" % zx.game_video_pix_width)
        f.write("zx.game_video_pix_height = %d\n" % zx.game_video_pix_height)
        f.write("zx.game_sound_volume = %d\n" % zx.game_sound_volume)
        f.write("zx.game_music_volume = %d\n" % zx.game_music_volume)
        f.write("zx.game_display_sync = %d\n" % zx.game_display_sync)
        f.write("zx.game_full_screen = %d\n" % zx.game_full_screen)
        f.write("zx.game_fps_counter = %d\n" % zx.game_fps_counter)
