//
// Copyright goblinhack@gmail.com
//

#include "my_game.hpp"
#include <SDL_mixer.h>

uint8_t audio_init_done;

void audio_fini(void)
{
  TRACE_AND_INDENT();
  Mix_CloseAudio();
}

bool audio_init(void)
{
  TRACE_AND_INDENT();
  //
  // Output sampling freq in samples per second (Hz).
  // you might use MIX_DEFAULT_FREQUENCY(22050) since that is a good value
  // for most games.
  //
  int audio_freq   = MIX_DEFAULT_FREQUENCY;
  int audio_format = MIX_DEFAULT_FORMAT;

  //
  // Number of sound channels in output.
  // Set to 2 for stereo, 1 for mono. This has nothing to do with
  // mixing channels.
  //
  int channels = 2;

  //
  // chunksize is the size of each mixed sample. The smaller this is the
  // more your hooks will be called. If make this too small on a slow
  // system, sound may skip. If made to large, sound effects will lag
  // behind the action more. You want a happy medium for your target
  // computer. You also may make this 4096, or larger, if you are just
  // playing music.
  //
  // int chunksize = 4096;
  int chunksize = 1024; // less latency but might be choppy

  if (! audio_init_done) {
    if (Mix_OpenAudio(audio_freq, audio_format, channels, chunksize) != 0) {

      ERR("Mix_OpenAudio fail: %s %s", Mix_GetError(), SDL_GetError());
      SDL_ClearError();
      return false;
    }

    audio_init_done = true;
  }

  return true;
}
