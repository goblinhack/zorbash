//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_ptrcheck.hpp"
#include "my_string.hpp"
#include "stb_image_write.hpp"

void sdl_screenshot(void)
{
  TRACE_AND_INDENT();
  g_do_screenshot = 1;
}

void sdl_screenshot_do(void)
{
  TRACE_AND_INDENT();
  GL_ERROR_CHECK();
  int fbo = FBO_FINAL;
  int w;
  int h;
  GL_ERROR_CHECK();
  fbo_get_size(fbo, w, h);
  GL_ERROR_CHECK();
  blit_fbo_bind(fbo);
  GL_ERROR_CHECK();

  static int count = 1;

  GL_ERROR_CHECK();
  glPixelStorei(GL_PACK_ALIGNMENT, 1);
  GL_ERROR_CHECK();

#if 0
  //
  // Not sure what this does and why I had it!
  //
  glReadBuffer(GL_BACK_LEFT);
  GL_ERROR_CHECK();
#endif

  std::vector< uint8_t > pixels(3 * w * h);
  glReadPixels(0, 0, w, h, GL_RGB, GL_UNSIGNED_BYTE, pixels.data());
  GL_ERROR_CHECK();

  for (int line = 0; line != h / 2; ++line) {
    std::swap_ranges(pixels.begin() + 3 * w * line, pixels.begin() + 3 * w * (line + 1),
                     pixels.begin() + 3 * w * (h - line - 1));
  }

  int components = 3;

  char *png = dynprintf("screenshot.%d.png", count);
  stbi_write_png(png, w, h, components, pixels.data(), 3 * w);
  GL_ERROR_CHECK();
  BOTCON("Screenshot: %s", png);
  myfree(png);
  blit_fbo_unbind();
  GL_ERROR_CHECK();

  count++;
}

std::vector< uint8_t > sdl_fbo_save(int fbo)
{
  TRACE_AND_INDENT();
  int w;
  int h;
  fbo_get_size(fbo, w, h);
  GL_ERROR_CHECK();

  blit_fbo_bind(fbo);
  GL_ERROR_CHECK();

  glPixelStorei(GL_PACK_ALIGNMENT, 1);
  GL_ERROR_CHECK();

  std::vector< uint8_t > pixels;
  pixels.resize(4 * w * h);

  glReadPixels(0, 0, w, h, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());
  GL_ERROR_CHECK();

  blit_fbo_unbind();
  GL_ERROR_CHECK();

  return pixels;
}

void sdl_fbo_load(int fbo, const std::vector< uint8_t > &pixels)
{
  TRACE_AND_INDENT();
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

  glDrawPixels(w, h, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());
  GL_ERROR_CHECK();

  blit_fbo_unbind();
  GL_ERROR_CHECK();
}

void sdl_fbo_dump(int fbo, const std::string &name)
{
  TRACE_AND_INDENT();
  int w;
  int h;
  fbo_get_size(fbo, w, h);
  GL_ERROR_CHECK();

  blit_fbo_bind(fbo);
  GL_ERROR_CHECK();

  glPixelStorei(GL_PACK_ALIGNMENT, 1);
  GL_ERROR_CHECK();

  std::vector< uint8_t > pixels;
  pixels.resize(4 * w * h);

  glReadPixels(0, 0, w, h, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());
  GL_ERROR_CHECK();

  blit_fbo_unbind();
  GL_ERROR_CHECK();

  static int count      = 0;
  int        components = 4;
  char      *png        = dynprintf("screenshot.%s.%03d.png", name.c_str(), count);
  stbi_write_png(png, w, h, components, pixels.data(), 4 * w);
  BOTCON("Screenshot: %s", png);
  myfree(png);
  count++;
}
