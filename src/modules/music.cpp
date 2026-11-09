//
// Copyright goblinhack@gmail.com
//
// Converted from python/music.py
//

#include "my_native.hpp"

namespace mod_modules_music {





void module_init(void)
{
  my::music_load(44100, "data/music/DST-PhaserSwitch.ogg", "intro");
  my::music_load(44100, "data/music/DST-3rdBallad.ogg", "relaxing");
  my::music_load(44100, "data/music/DST-DoomCity.ogg", "boss");
}

} // namespace mod_modules_music
