//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_file.hpp"
#include "my_gl.hpp"
#include "my_main.hpp"
#include "my_math.hpp"
#include "my_pixel.hpp"
#include "my_ptrcheck.hpp"
#include "my_string.hpp"
#include "my_sys.hpp"
#include "my_tex.hpp"
#include "stb_image.hpp"

class Tex
{
public:
  Tex(std::string name) : name(name)
  {
    surface            = nullptr;
    gl_surface_binding = 0;
    newptr(MTYPE_TEX, this, "Tex");
  }

  ~Tex(void)
  {
    oldptr(MTYPE_TEX, this);

    if (surface) {
      verify(MTYPE_SDL, surface);
      SDL_FreeSurface(surface);
      oldptr(MTYPE_SDL, surface);
      surface = nullptr;
    }

    if (gl_surface_binding) {
      GLuint tmp;
      tmp = gl_surface_binding;
      glDeleteTextures(1, &tmp);
      gl_surface_binding = 0;
    }
  }

  std::string  name;
  uint32_t     width              = {};
  uint32_t     height             = {};
  int          gl_surface_binding = {};
  SDL_Surface *surface            = {};
};

static std::map< std::string, Texp > textures;
static std::map< std::string, Texp > textures_black_and_white;
static std::map< std::string, Texp > textures_mask;

uint8_t tex_init(void)
{
  TRACE_AND_INDENT();
  return true;
}

void tex_fini(void)
{
  TRACE_AND_INDENT();
  for (auto &t : textures) {
    delete t.second;
  }
  for (auto &t : textures_black_and_white) {
    delete t.second;
  }
  for (auto &t : textures_mask) {
    delete t.second;
  }
}

void tex_free(Texp tex)
{
  TRACE_AND_INDENT();
  textures.erase(tex->name);
  textures_black_and_white.erase(tex->name);
  textures_mask.erase(tex->name);
  delete (tex);
}

static unsigned char *load_raw_image(std::string filename, int *x, int *y, int *comp)
{
  TRACE_AND_INDENT();
  unsigned char *file_data;
  unsigned char *image_data = nullptr;
  int            len;

  file_data = file_load(filename.c_str(), &len);
  if (! file_data) {
    DIE("Could not read file, '%s'", filename.c_str());
  }

  image_data = stbi_load_from_memory(file_data, len, x, y, comp, 0);
  if (! image_data) {
    DIE("Could not read memory for file, '%s'", filename.c_str());
  }

  DBG2("loaded '%s', %ux%u", filename.c_str(), *x, *y);

  myfree(file_data);

  return (image_data);
}

static void free_raw_image(unsigned char *image_data)
{
  TRACE_AND_INDENT();
  stbi_image_free(image_data);
}

static SDL_Surface *load_image(std::string filename)
{
  TRACE_AND_INDENT();
  uint32_t       rmask, gmask, bmask, amask;
  unsigned char *image_data;
  SDL_Surface   *surf;
  int            x, y, comp;

  image_data = load_raw_image(filename, &x, &y, &comp);
  if (! image_data) {
    ERR("Could not read memory for file, '%s'", filename.c_str());
  }

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
  rmask = 0xff000000;
  gmask = 0x00ff0000;
  bmask = 0x0000ff00;
  amask = 0x000000ff;
#else
  rmask = 0x000000ff;
  gmask = 0x0000ff00;
  bmask = 0x00ff0000;
  amask = 0xff000000;
#endif

  if (comp == 4) {
    surf = SDL_CreateRGBSurface(0, x, y, 32, rmask, gmask, bmask, amask);
    newptr(MTYPE_SDL, surf, "SDL_CreateRGBSurface1");
  } else if (comp == 3) {
    surf = SDL_CreateRGBSurface(0, x, y, 24, rmask, gmask, bmask, 0);
    newptr(MTYPE_SDL, surf, "SDL_CreateRGBSurface2");
  } else if (comp == 2) {
    surf = SDL_CreateRGBSurface(0, x, y, 32, 0, 0, 0, 0);
    newptr(MTYPE_SDL, surf, "SDL_CreateRGBSurface3");
  } else {
    ERR("Could not handle image with %d components", comp);
    free_raw_image(image_data);
    return nullptr;
  }

  memcpy(surf->pixels, image_data, comp * x * y);

  if (comp == 2) {
    SDL_Surface *old_surf = surf;
    DBG2("- SDL_ConvertSurfaceFormat");
    surf = SDL_ConvertSurfaceFormat(old_surf, SDL_PIXELFORMAT_RGBA8888, 0);
    newptr(MTYPE_SDL, surf, "SDL_CreateRGBSurface4");
    oldptr(MTYPE_SDL, old_surf);
    SDL_FreeSurface(old_surf);
    SDL_SaveBMP(surf, filename.c_str());
  }

  free_raw_image(image_data);

  return (surf);
}

static void load_images(SDL_Surface **surf1_out, SDL_Surface **surf2_out, std::string filename)
{
  TRACE_AND_INDENT();
  uint32_t       rmask, gmask, bmask, amask;
  unsigned char *image_data;
  SDL_Surface   *surf1 = nullptr;
  SDL_Surface   *surf2 = nullptr;
  int            x, y, comp;

  image_data = load_raw_image(filename, &x, &y, &comp);
  if (! image_data) {
    ERR("Could not read memory for file, '%s'", filename.c_str());
  }

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
  rmask = 0xff000000;
  gmask = 0x00ff0000;
  bmask = 0x0000ff00;
  amask = 0x000000ff;
#else
  rmask = 0x000000ff;
  gmask = 0x0000ff00;
  bmask = 0x00ff0000;
  amask = 0xff000000;
#endif

  if (comp == 4) {
    surf1 = SDL_CreateRGBSurface(0, x, y, 32, rmask, gmask, bmask, amask);
    newptr(MTYPE_SDL, surf1, "SDL_CreateRGBSurface5");
  } else if (comp == 3) {
    surf1 = SDL_CreateRGBSurface(0, x, y, 24, rmask, gmask, bmask, 0);
    newptr(MTYPE_SDL, surf1, "SDL_CreateRGBSurface6");
  } else if (comp == 2) {
    surf1 = SDL_CreateRGBSurface(0, x, y, 32, 0, 0, 0, 0);
    newptr(MTYPE_SDL, surf1, "SDL_CreateRGBSurface7");
  } else {
    ERR("Could not handle image with %d components", comp);
  }

  if (comp == 4) {
    surf2 = SDL_CreateRGBSurface(0, x, y, 32, rmask, gmask, bmask, amask);
    newptr(MTYPE_SDL, surf2, "SDL_CreateRGBSurface8");
  } else if (comp == 3) {
    surf2 = SDL_CreateRGBSurface(0, x, y, 24, rmask, gmask, bmask, 0);
    newptr(MTYPE_SDL, surf2, "SDL_CreateRGBSurface9");
  } else if (comp == 2) {
    surf2 = SDL_CreateRGBSurface(0, x, y, 32, 0, 0, 0, 0);
    newptr(MTYPE_SDL, surf2, "SDL_CreateRGBSurface10");
  } else {
    ERR("Could not handle image with %d components", comp);
  }

  memcpy(surf1->pixels, image_data, comp * x * y);
  memcpy(surf2->pixels, image_data, comp * x * y);

  if (comp == 2) {
    SDL_Surface *old_surf = surf1;
    DBG2("- SDL_ConvertSurfaceFormat");
    surf1 = SDL_ConvertSurfaceFormat(old_surf, SDL_PIXELFORMAT_RGBA8888, 0);
    newptr(MTYPE_SDL, surf1, "SDL_CreateRGBSurface14");
    oldptr(MTYPE_SDL, old_surf);
    SDL_FreeSurface(old_surf);
    SDL_SaveBMP(surf1, filename.c_str());
  }

  if (comp == 2) {
    SDL_Surface *old_surf = surf2;
    DBG2("- SDL_ConvertSurfaceFormat");
    surf2 = SDL_ConvertSurfaceFormat(old_surf, SDL_PIXELFORMAT_RGBA8888, 0);
    newptr(MTYPE_SDL, surf2, "SDL_CreateRGBSurface15");
    oldptr(MTYPE_SDL, old_surf);
    SDL_FreeSurface(old_surf);
    SDL_SaveBMP(surf2, filename.c_str());
  }

  free_raw_image(image_data);

  *surf1_out = surf1;
  *surf2_out = surf2;
}

//
// Load a texture
//
Texp tex_load(std::string file, std::string name, int mode)
{
  TRACE_AND_INDENT();
  Texp t = tex_find(name);

  if (t) {
    return t;
  }

  DBG2("Loading texture '%s', '%s'", file.c_str(), name.c_str());
  if (file == "") {
    if (name == "") {
      ERR("No file for tex");
      return nullptr;
    }
    ERR("No file for tex loading '%s'", name.c_str());
    return nullptr;
  }

  SDL_Surface *surface = nullptr;
  surface              = load_image(file);

  if (! surface) {
    ERR("Could not make surface from file '%s'", file.c_str());
  }

  t = tex_from_surface(surface, file, name, mode);

  DBG2("- loaded texture '%s', '%s'", file.c_str(), name.c_str());

  return t;
}

//
// Returns two textures
// 1 - black and white tile used in backgrounds
// 2 - mask for sprites
//
static std::pair< Texp, Texp > tex_sprite(SDL_Surface *in, std::string file, std::string name, int mode)
{
  auto n1 = name + "_black_and_white";
  auto n2 = name + "_mask";
  Texp t1 = new Tex(n1);
  Texp t2 = new Tex(n2);
  textures_black_and_white.insert(std::make_pair(n1, t1));
  textures_mask.insert(std::make_pair(n2, t2));
  uint32_t rmask, gmask, bmask, amask;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
  rmask = 0xff000000;
  gmask = 0x00ff0000;
  bmask = 0x0000ff00;
  amask = 0x000000ff;
#else
  rmask = 0x000000ff;
  gmask = 0x0000ff00;
  bmask = 0x00ff0000;
  amask = 0xff000000;
#endif

  uint32_t iwidth  = in->w;
  uint32_t iheight = in->h;
  //
  // Subtract space for the single pixel padding and make a surface to
  // copy pixels to.
  //
  uint32_t owidth  = iwidth;
  uint32_t oheight = iheight;

  int      ix;
  int      iy;
  uint32_t ox;
  uint32_t oy;

  SDL_Surface *out1 = SDL_CreateRGBSurface(0, owidth, oheight, 32, rmask, gmask, bmask, amask);
  newptr(MTYPE_SDL, out1, "SDL_CreateRGBSurface17");
  SDL_Surface *out2 = SDL_CreateRGBSurface(0, owidth, oheight, 32, rmask, gmask, bmask, amask);
  newptr(MTYPE_SDL, out2, "SDL_CreateRGBSurface18");

  oy = 0;
  for (iy = 0; iy < (int) iheight; iy++) {
    ox = 0;
    for (ix = 0; ix < (int) iwidth; ix++) {
      color c1;
      getPixelFast(in, ix, iy, c1);
      color   c2  = c1;
      uint8_t avg = ((int) c1.r + (int) c1.g + (int) c1.b) / 3;
      c1.r        = avg;
      c1.g        = avg;
      c1.b        = avg;

      putPixel(out1, ox, oy, c1);

      if (c2.a == 0) {
        c2.r = 0;
        c2.g = 0;
        c2.b = 0;
        c2.a = 0;
      } else if ((c2.r > 1) || (c2.g > 1) || (c2.b > 1)) {
        c2.r = 255;
        c2.g = 255;
        c2.b = 255;
        c2.a = 255;
      } else {
        c2.r = 0;
        c2.g = 0;
        c2.b = 0;
        c2.a = 0;
      }

      putPixel(out2, ox, oy, c2);
      ox++;
    }
    oy++;
  }

  SDL_FreeSurface(in);
  oldptr(MTYPE_SDL, in);

  t1 = tex_from_surface(out1, file, n1, mode);
  t2 = tex_from_surface(out2, file, n2, mode);

  return (std::make_pair(t1, t2));
}

void tex_load(Texp *tex, Texp *tex_black_and_white, Texp *tex_mask, std::string file, std::string name, int mode)
{
  TRACE_AND_INDENT();
  Texp t = tex_find(name);
  if (t) {
    ERR("Tex already eciste '%s'", name.c_str());
  }

  DBG2("Loading texture '%s', '%s'", file.c_str(), name.c_str());
  if (file == "") {
    if (name == "") {
      ERR("No file for tex");
    } else {
      ERR("No file for tex loading '%s'", name.c_str());
    }
  }

  DBG2("- create textures '%s', '%s'", file.c_str(), name.c_str());
  SDL_Surface *surface                 = nullptr;
  SDL_Surface *surface_black_and_white = nullptr;

  load_images(&surface, &surface_black_and_white, file);

  if (! surface) {
    ERR("Could not make surface from file '%s'", file.c_str());
  }

  if (! surface_black_and_white) {
    ERR("Could not make black and white surface from file '%s'", file.c_str());
  }

  *tex                 = tex_from_surface(surface, file, name, mode);
  auto p               = tex_sprite(surface_black_and_white, file, name, mode);
  *tex_black_and_white = p.first;
  *tex_mask            = p.second;

  DBG2("- loaded texture '%s', '%s'", file.c_str(), name.c_str());
}

//
// Find an existing tex.
//
Texp tex_find(std::string file)
{
  TRACE_AND_INDENT();
  if (file == "") {
    ERR("No filename given for tex find");
  }

  auto result = textures.find(file);
  if (result == textures.end()) {
    return nullptr;
  }

  return (result->second);
}

//
// Creae a texture from a surface
//
Texp tex_from_surface(SDL_Surface *surface, std::string file, std::string name, int mode)
{
  TRACE_AND_INDENT();
  if (! surface) {
    ERR("Could not make surface from file, '%s'", file.c_str());
  }

  DBG2("Texture: '%s', %dx%d", file.c_str(), surface->w, surface->h);

  //
  // Get the number of channels in the SDL surface
  //
  int channels      = surface->format->BytesPerPixel;
  int textureFormat = 0;

  if (channels == 4) {
    //
    // Contains alpha channel
    //
    if (surface->format->Rmask == 0x000000ff) {
      textureFormat = GL_RGBA;
    } else {
      textureFormat = GL_BGRA;
    }
  } else if (channels == 3) {
    //
    // Contains no alpha channel
    //
    if (surface->format->Rmask == 0x000000ff) {
      textureFormat = GL_RGB;
    } else {
#ifdef GL_BGR
      textureFormat = GL_BGR;
#else
      ERR("'%s' need support for GL_BGR", file);
#endif
    }
  } else {
    ERR("'%s' is not truecolor, need %d bytes per pixel", file.c_str(), channels);
  }

  //
  // Create the tex
  //
  GLuint gl_surface_binding = 0;

  glEnable(GL_TEXTURE_2D); // Apparently needed for ATI drivers

  glGenTextures(1, &gl_surface_binding);

  //
  // Typical tex generation using data from the bitmap
  //
  glBindTexture(GL_TEXTURE_2D, gl_surface_binding);

  //
  // Generate the tex
  //
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, surface->w, surface->h, 0, textureFormat, GL_UNSIGNED_BYTE,
               surface->pixels);

  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  //
  // linear filtering. Nearest is meant to be quicker but I didn't see
  // that in reality.
  //
  if (mode == GL_NEAREST) {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  } else {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  }

  Texp t      = new Tex(name);
  auto result = textures.insert(std::make_pair(name, t));

  if (! result.second) {
    ERR("Tex insert name '%s' failed", name.c_str());
  }

  t->width              = surface->w;
  t->height             = surface->h;
  t->gl_surface_binding = gl_surface_binding;
  t->surface            = surface;

  return t;
}

int tex_get_gl_binding(Texp tex)
{
  TRACE_AND_INDENT();
  return (tex->gl_surface_binding);
}

uint32_t tex_get_width(Texp tex)
{
  TRACE_AND_INDENT();
  if (! tex) {
    ERR("No texture");
  }

  return (tex->width);
}

uint32_t tex_get_height(Texp tex)
{
  TRACE_AND_INDENT();
  if (! tex) {
    ERR("No texture");
  }

  return (tex->height);
}

SDL_Surface *tex_get_surface(Texp tex)
{
  TRACE_AND_INDENT();
  return (tex->surface);
}

Texp string2tex(const char **s)
{
  TRACE_AND_INDENT();
  static char        tmp[ MAXSHORTSTR ];
  static std::string eo_tmp = tmp + MAXSHORTSTR - 1;
  const char        *c      = *s;
  char              *t      = tmp;

  while (t < eo_tmp) {
    if ((*c == '\0') || (*c == '$')) {
      break;
    }

    *t++ = *c++;
  }

  if (c == eo_tmp) {
    return nullptr;
  }

  *t++ = '\0';
  *s += (t - tmp);

  auto result = textures.find(tmp);
  if (result == textures.end()) {
    ERR("Unknown tex '%s'", tmp);
  }

  return (result->second);
}

Texp string2tex(std::string &s, int *len)
{
  TRACE_AND_INDENT();
  auto        iter = s.begin();
  std::string out;

  while (iter != s.end()) {
    auto c = *iter;

    if ((c == '\0') || (c == '$')) {
      break;
    }

    out += c;
    iter++;
  }

  if (len) {
    *len = iter - s.begin();
  }

  if (iter == s.end()) {
    ERR("Unknown tex '%s'", out.c_str());
  }

  auto result = textures.find(out);
  if (result == textures.end()) {
    ERR("Unknown tex '%s'", out.c_str());
  }

  return (result->second);
}

Texp string2tex(std::wstring &s, int *len)
{
  TRACE_AND_INDENT();
  auto v = wstring_to_string(s);
  return (string2tex(v, len));
}
