//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "stb_image_write.h"
#include "my_sys.h"
#include "my_game.h"
#include "my_gl.h"
#include "my_ascii.h"
#include "my_player.h"
#include "my_wid_console.h"
#include "my_string.h"
#include "my_ptrcheck.h"

void sdl_screenshot (void)
{_
    g_do_screenshot = 1;
}

void sdl_screenshot_do (void)
{_
    int fbo = FBO_FULLMAP;
    int w;
    int h;
    fbo_get_size(fbo, w, h);
    blit_fbo_bind(fbo);

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
    BOTCON("Screenshot: %s", png);
    myfree(png);
    blit_fbo_unbind();

    count++;
}

std::vector<uint8_t> sdl_fbo_save (int fbo)
{_
    int w;
    int h;
    fbo_get_size(fbo, w, h);
    GL_ERROR_CHECK();

    blit_fbo_bind(fbo);
    GL_ERROR_CHECK();

    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    GL_ERROR_CHECK();

    std::vector<uint8_t> pixels;
    pixels.resize(3 * w * h);

    glReadPixels(0, 0, w, h, GL_RGB, GL_UNSIGNED_BYTE, pixels.data());
    GL_ERROR_CHECK();

    blit_fbo_unbind();
    GL_ERROR_CHECK();

#if 0
    static int count = 0;
    int components = 3;
    char *png = dynprintf("screenshot.%d.png", count);
    stbi_write_png(png, w, h, components, pixels.data(), 3 * w);
    BOTCON("Screenshot: %s", png);
    myfree(png);
    count++;
#endif

    return pixels;
}

void sdl_fbo_load (int fbo, const std::vector<uint8_t> &pixels)
{_
    if (pixels.empty()) {
        return;
    }

    int w;
    int h;
    fbo_get_size(fbo, w, h);
    GL_ERROR_CHECK();

    blit_fbo_bind(fbo);
    GL_ERROR_CHECK();

    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    GL_ERROR_CHECK();

    glDrawPixels(w, h, GL_RGB, GL_UNSIGNED_BYTE, pixels.data());
    GL_ERROR_CHECK();

    blit_fbo_unbind();
    GL_ERROR_CHECK();
}

void sdl_fbo_dump (int fbo, const std::string &name)
{_
    int w;
    int h;
    fbo_get_size(fbo, w, h);
    GL_ERROR_CHECK();

    blit_fbo_bind(fbo);
    GL_ERROR_CHECK();

    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    GL_ERROR_CHECK();

    std::vector<uint8_t> pixels;
    pixels.resize(3 * w * h);

    glReadPixels(0, 0, w, h, GL_RGB, GL_UNSIGNED_BYTE, pixels.data());
    GL_ERROR_CHECK();

    blit_fbo_unbind();
    GL_ERROR_CHECK();

    static int count = 0;
    int components = 3;
    char *png = dynprintf("screenshot.%s.%03d.png", name.c_str(), count);
    stbi_write_png(png, w, h, components, pixels.data(), 3 * w);
    BOTCON("Screenshot: %s", png);
    myfree(png);
    count++;
}
