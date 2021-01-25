//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_main.h"
#include "my_game.h"
#include "my_gl.h"
#include "my_ascii.h"
#include "my_thing.h"
#include "my_player.h"
#include "my_wid_console.h"
#include "stb_image_write.h"

void sdl_screenshot (void)
{_
    g_do_screenshot = 1;
}

void sdl_screenshot_do (void)
{_
    int w = game->config.outer_pix_width;
    int h = game->config.outer_pix_height;

    static int count = 1;

    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glReadBuffer(GL_BACK_LEFT);

    std::vector<uint8_t> pixels(3 * w * h);
    glReadPixels(0, 0, w, h, GL_RGB, GL_UNSIGNED_BYTE, pixels.data());

    for(int line = 0; line != h/2; ++line) {
        std::swap_ranges(pixels.begin() + 3 * w * line,
                         pixels.begin() + 3 * w * (line+1),
                         pixels.begin() + 3 * w * (h-line-1));
    }

    int components = 3;

    char *png = dynprintf("screenshot.%d.png", count);
    stbi_write_png(png, w, h, components, pixels.data(), 3 * w);
    MINICON("Screenshot: %s", png);
    myfree(png);

    if (0) {
        char *tga = dynprintf("screenshot.%d.tga", count);
        stbi_write_tga(tga, w, h, components, pixels.data());
        MINICON("Screenshot: %s", tga);
        myfree(tga);
    }

    count++;
}
