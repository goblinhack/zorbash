/*
 * Copyright goblinhack@gmail.com
 * See the README file for license info.
 */

#include "my_game.h"
#include "my_dungeon.h"

std::ostream& operator<<(std::ostream &out, Bits<const Config & > const my)
{_
    out << bits(my.t.fps_counter);
    out << bits(my.t.sound_volume);
    out << bits(my.t.music_volume);
    out << bits(my.t.vsync_enable);
    out << bits(my.t.full_screen);
    out << bits(my.t.video_pix_width);
    out << bits(my.t.video_pix_height);
    out << bits(my.t.video_gl_width);
    out << bits(my.t.video_gl_height);
    out << bits(my.t.video_w_h_ratio);
    out << bits(my.t.drawable_gl_width);
    out << bits(my.t.drawable_gl_height);
    out << bits(my.t.tile_gl_width);
    out << bits(my.t.tile_gl_height);
    out << bits(my.t.one_pixel_gl_width);
    out << bits(my.t.one_pixel_gl_height);
    out << bits(my.t.ascii_gl_width);
    out << bits(my.t.ascii_gl_height);
    out << bits(my.t.tile_pixel_width);
    out << bits(my.t.tile_pixel_height);
    out << bits(my.t.sdl_delay);
    return (out);
}

std::istream& operator>>(std::istream &in, Bits<Config &> my)
{_
    in >> bits(my.t.fps_counter);
    in >> bits(my.t.sound_volume);
    in >> bits(my.t.music_volume);
    in >> bits(my.t.vsync_enable);
    in >> bits(my.t.full_screen);
    in >> bits(my.t.video_pix_width);
    in >> bits(my.t.video_pix_height);
    in >> bits(my.t.video_gl_width);
    in >> bits(my.t.video_gl_height);
    in >> bits(my.t.video_w_h_ratio);
    in >> bits(my.t.drawable_gl_width);
    in >> bits(my.t.drawable_gl_height);
    in >> bits(my.t.tile_gl_width);
    in >> bits(my.t.tile_gl_height);
    in >> bits(my.t.one_pixel_gl_width);
    in >> bits(my.t.one_pixel_gl_height);
    in >> bits(my.t.ascii_gl_width);
    in >> bits(my.t.ascii_gl_height);
    in >> bits(my.t.tile_pixel_width);
    in >> bits(my.t.tile_pixel_height);
    in >> bits(my.t.sdl_delay);
    return (in);
}

void Config::dump (std::string prefix, std::ostream &out)
{_
    out << prefix << "Config {" << std::endl;
    auto old_prefix = prefix;
    prefix += "  ";

    out << prefix << "fps_counter:         " << fps_counter << std::endl;
    out << prefix << "sound_volume:        " << sound_volume << std::endl;
    out << prefix << "music_volume:        " << music_volume << std::endl;
    out << prefix << "vsync_enable:        " << vsync_enable << std::endl;
    out << prefix << "full_screen:         " << full_screen << std::endl;
    out << prefix << "video_pix_width:     " << video_pix_width << std::endl;
    out << prefix << "video_pix_height:    " << video_pix_height << std::endl;
    out << prefix << "video_gl_width:      " << video_gl_width << std::endl;
    out << prefix << "video_gl_height:     " << video_gl_height << std::endl;
    out << prefix << "video_w_h_ratio:     " << video_w_h_ratio << std::endl;
    out << prefix << "drawable_gl_width:   " << drawable_gl_width << std::endl;
    out << prefix << "drawable_gl_height:  " << drawable_gl_height << std::endl;
    out << prefix << "tile_gl_width:       " << tile_gl_width << std::endl;
    out << prefix << "tile_gl_height:      " << tile_gl_height << std::endl;
    out << prefix << "one_pixel_gl_width:  " << one_pixel_gl_width << std::endl;
    out << prefix << "one_pixel_gl_height: " << one_pixel_gl_height << std::endl;
    out << prefix << "ascii_gl_width:      " << ascii_gl_width << std::endl;
    out << prefix << "ascii_gl_height:     " << ascii_gl_height << std::endl;
    out << prefix << "tile_pixel_width:    " << tile_pixel_width << std::endl;
    out << prefix << "tile_pixel_height:   " << tile_pixel_height << std::endl;
    out << prefix << "sdl_delay:           " << sdl_delay << std::endl;

    prefix = old_prefix;
    out << prefix << "}" << std::endl;
}

std::ostream& operator<<(std::ostream &out, 
                         Bits<const class Game & > const my)
{_
    out << bits(my.t.appdata);
    out << bits(my.t.saved_dir);
    out << bits(my.t.saved_file);
    out << bits(my.t.fps_count);
    out << bits(my.t.config);
    return (out);
}

std::istream& operator>>(std::istream &in, Bits<class Game &> my)
{_
    in >> bits(my.t.appdata);
    in >> bits(my.t.saved_dir);
    in >> bits(my.t.saved_file);
    in >> bits(my.t.fps_count);
    in >> bits(my.t.config);
    return (in);
}

void Game::dump (std::string prefix, std::ostream &out)
{
    out << prefix << "Game {" << std::endl;
    auto old_prefix = prefix;
    prefix += "  ";

    out << prefix << "appdata:     " << appdata << std::endl;
    out << prefix << "saved_dir:   " << saved_dir << std::endl;
    out << prefix << "sdaved_file: " << saved_file << std::endl;
    out << prefix << "fps_count:   " << fps_count << std::endl;
    config.dump(prefix, out);

    prefix = old_prefix;
    out << prefix << "}" << std::endl;
}
