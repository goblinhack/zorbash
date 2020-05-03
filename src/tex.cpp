//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "stb_image.h"
#include "my_main.h"
#include "my_gl.h"
#include "my_tex.h"
#include "my_ramdisk.h"
#include "my_pixel.h"
#include "my_math.h"
#include "my_string.h"

class Tex {
public:
    Tex (std::string name) : name(name)
    {
        surface = 0;
        gl_surface_binding = 0;
        newptr(this, "Tex");
    }

    ~Tex (void)
    {
        oldptr(this);

        if (surface) {
            verify(surface);
            SDL_FreeSurface(surface);
            oldptr(surface);
            surface = 0;
        }

        if (gl_surface_binding) {
            GLuint tmp;
            tmp = gl_surface_binding;
            glDeleteTextures(1, &tmp);
            gl_surface_binding = 0;
        }
    }

    std::string name;
    uint32_t    width = {};
    uint32_t    height = {};
    int32_t     gl_surface_binding = {};
    SDL_Surface *surface = {};
};

static std::map<std::string, Texp> textures;
static std::map<std::string, Texp> black_and_white_textures;

uint8_t tex_init (void)
{_
    return (true);
}

void tex_fini (void)
{_
    for (auto t : textures) {
        delete t.second;
    }
    for (auto t : black_and_white_textures) {
        delete t.second;
    }
}

void tex_free (Texp tex)
{_
    textures.erase(tex->name);
    black_and_white_textures.erase(tex->name);
    delete(tex);
}

static unsigned char *load_raw_image (std::string filename,
                                      int32_t *x,
                                      int32_t *y,
                                      int32_t *comp)
{_
    unsigned char *file_data;
    unsigned char *image_data = 0;
    int32_t len;

    file_data = file_load(filename.c_str(), &len);
    if (!file_data) {
        ERR("could not read file, '%s'", filename.c_str());
    }

    image_data = stbi_load_from_memory(file_data, len, x, y, comp, 0);
    if (!image_data) {
        ERR("could not read memory for file, '%s'", filename.c_str());
    }

    DBG("loaded '%s', %ux%u", filename.c_str(), *x, *y);

    myfree(file_data);

    return (image_data);
}

static void free_raw_image (unsigned char *image_data)
{_
    stbi_image_free(image_data);
}

static SDL_Surface *load_image (std::string filename)
{_
    uint32_t rmask, gmask, bmask, amask;
    unsigned char *image_data;
    SDL_Surface *surf;
    int32_t x, y, comp;

    image_data = load_raw_image(filename, &x, &y, &comp);
    if (!image_data) {
        ERR("could not read memory for file, '%s'", filename.c_str());
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

    LOG("- SDL_CreateRGBSurface");
    if (comp == 4) {
        surf = SDL_CreateRGBSurface(0, x, y, 32, rmask, gmask, bmask, amask);
        newptr(surf, "SDL_CreateRGBSurface");
    } else if (comp == 3) {
        surf = SDL_CreateRGBSurface(0, x, y, 24, rmask, gmask, bmask, 0);
        newptr(surf, "SDL_CreateRGBSurface");
    } else if (comp == 2) {
        surf = SDL_CreateRGBSurface(0, x, y, 32, 0, 0, 0, 0);
        newptr(surf, "SDL_CreateRGBSurface");
    } else {
        ERR("could not handle image with %d components", comp);
        free_raw_image(image_data);
        return (0);
    }

    memcpy(surf->pixels, image_data, comp * x * y);

    if (comp == 2) {
        SDL_Surface *old_surf = surf;
        LOG("- SDL_ConvertSurfaceFormat");
        surf = SDL_ConvertSurfaceFormat(old_surf, SDL_PIXELFORMAT_RGBA8888, 0);
        newptr(surf, "SDL_CreateRGBSurface");
        oldptr(old_surf);
        SDL_FreeSurface(old_surf);
        SDL_SaveBMP(surf, filename.c_str());
    }

    free_raw_image(image_data);

    return (surf);
}

static void load_image_pair (SDL_Surface **surf1_out,
                             SDL_Surface **surf2_out,
                             std::string filename)
{_
    uint32_t rmask, gmask, bmask, amask;
    unsigned char *image_data;
    SDL_Surface *surf1 = 0;
    SDL_Surface *surf2 = 0;
    int32_t x, y, comp;

    image_data = load_raw_image(filename, &x, &y, &comp);
    if (!image_data) {
        ERR("could not read memory for file, '%s'", filename.c_str());
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

    LOG("- SDL_CreateRGBSurface");
    if (comp == 4) {
        surf1 = SDL_CreateRGBSurface(0, x, y, 32, rmask, gmask, bmask, amask);
        newptr(surf1, "SDL_CreateRGBSurface");
    } else if (comp == 3) {
        surf1 = SDL_CreateRGBSurface(0, x, y, 24, rmask, gmask, bmask, 0);
        newptr(surf1, "SDL_CreateRGBSurface");
    } else if (comp == 2) {
        surf1 = SDL_CreateRGBSurface(0, x, y, 32, 0, 0, 0, 0);
        newptr(surf1, "SDL_CreateRGBSurface");
    } else {
        ERR("could not handle image with %d components", comp);
    }

    if (comp == 4) {
        surf2 = SDL_CreateRGBSurface(0, x, y, 32, rmask, gmask, bmask, amask);
        newptr(surf2, "SDL_CreateRGBSurface");
    } else if (comp == 3) {
        surf2 = SDL_CreateRGBSurface(0, x, y, 24, rmask, gmask, bmask, 0);
        newptr(surf2, "SDL_CreateRGBSurface");
    } else if (comp == 2) {
        surf2 = SDL_CreateRGBSurface(0, x, y, 32, 0, 0, 0, 0);
        newptr(surf2, "SDL_CreateRGBSurface");
    } else {
        ERR("could not handle image with %d components", comp);
    }

    memcpy(surf1->pixels, image_data, comp * x * y);
    memcpy(surf2->pixels, image_data, comp * x * y);

    if (comp == 2) {
        SDL_Surface *old_surf = surf1;
        LOG("- SDL_ConvertSurfaceFormat");
        surf1 = SDL_ConvertSurfaceFormat(old_surf, SDL_PIXELFORMAT_RGBA8888, 0);
        newptr(surf1, "SDL_CreateRGBSurface");
        oldptr(old_surf);
        SDL_FreeSurface(old_surf);
        SDL_SaveBMP(surf1, filename.c_str());
    }

    if (comp == 2) {
        SDL_Surface *old_surf = surf2;
        LOG("- SDL_ConvertSurfaceFormat");
        surf2 = SDL_ConvertSurfaceFormat(old_surf, SDL_PIXELFORMAT_RGBA8888, 0);
        newptr(surf2, "SDL_CreateRGBSurface");
        oldptr(old_surf);
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
Texp tex_load (std::string file, std::string name, int mode)
{_
    Texp t = tex_find(name);

    if (t) {
        return (t);
    }

    LOG("loading texture '%s', '%s'", file.c_str(), name.c_str());
    if (file == "") {
        if (name == "") {
            ERR("no file for tex");
            return (0);
        } else {
            ERR("no file for tex loading '%s'", name.c_str());
            return (0);
        }
    }

    SDL_Surface *surface = 0;
    surface = load_image(file);

    if (!surface) {
        ERR("could not make surface from file '%s'", file.c_str());
    }

    LOG("- create texture '%s', '%s'", file.c_str(), name.c_str());
    t = tex_from_surface(surface, file, name, mode);

    LOG("- loaded texture '%s', '%s'", file.c_str(), name.c_str());

    return (t);
}

static Texp tex_from_surface_black_and_white (SDL_Surface *in,
                                              std::string file,
                                              std::string name,
                                              int mode)
{
    Texp t = new Tex(name);
    black_and_white_textures.insert(std::make_pair(name, t));
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

    int32_t ix;
    int32_t iy;
    uint32_t ox;
    uint32_t oy;

    SDL_Surface *out = SDL_CreateRGBSurface(0, owidth, oheight, 32,
                                            rmask, gmask, bmask, amask);
    newptr(out, "SDL_CreateRGBSurface");

    //
    // Omit every grid pixel between tiles.
    //
    ox = 0;

    for (ix = 0; ix < (int32_t) iwidth; ix++) {

        oy = 0;

        for (iy = 0; iy < (int32_t) iheight; iy++) {

            color c;

            c = getPixel(in, ix, iy);

            uint8_t avg = ((int)c.r + (int)c.g + (int)c.b) / 3;
            c.r = avg;
            c.g = avg;
            c.b = avg;

            putPixel(out, ox, oy, c);

            oy++;
        }

        ox++;
    }

    SDL_FreeSurface(in);
    oldptr(in);

    t = tex_from_surface(out, file, name, mode);

    return (t);
}

void tex_load_color_and_black_and_white (Texp *tex,
                                         Texp *tex_black_and_white,
                                         std::string file,
                                         std::string name,
                                         int mode)
{_
    Texp t = tex_find(name);
    if (t) {
        ERR("tex already eciste '%s'", name.c_str());
    }

    LOG("loading texture '%s', '%s'", file.c_str(), name.c_str());
    if (file == "") {
        if (name == "") {
            ERR("no file for tex");
        } else {
            ERR("no file for tex loading '%s'", name.c_str());
        }
    }

    LOG("- create textures '%s', '%s'", file.c_str(), name.c_str());
    SDL_Surface *surface = 0;
    SDL_Surface *surface_black_and_white = 0;
    load_image_pair(&surface, &surface_black_and_white, file);

    if (!surface) {
        ERR("could not make surface from file '%s'", file.c_str());
    }

    if (!surface_black_and_white) {
        ERR("could not make black and white surface from file '%s'",
            file.c_str());
    }

    *tex = tex_from_surface(surface, file, name, mode);
    *tex_black_and_white =
        tex_from_surface_black_and_white(surface_black_and_white, file,
                                         name + "_black_and_white", mode);

    LOG("- loaded texture '%s', '%s'", file.c_str(), name.c_str());
}

//
// Find an existing tex.
//
Texp tex_find (std::string file)
{_
    if (file == "") {
        ERR("no filename given for tex find");
    }

    auto result = textures.find(file);
    if (result == textures.end()) {
        return (0);
    }

    return (result->second);
}

//
// Creae a texture from a surface
//
Texp tex_from_surface (SDL_Surface *surface,
                       std::string file,
                       std::string name,
                       int mode)
{_
    if (!surface) {
        ERR("could not make surface from file, '%s'", file.c_str());
    }

    DBG("Texture: '%s', %dx%d", file.c_str(), surface->w, surface->h);

    //
    // Get the number of channels in the SDL surface
    //
    int32_t channels = surface->format->BytesPerPixel;
    int32_t textureFormat = 0;

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
        ERR("'%s' is not truecolor, need %d bytes per pixel", file.c_str(),
            channels);
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
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGBA8,
        surface->w,
        surface->h,
        0,
        textureFormat,
        GL_UNSIGNED_BYTE,
        surface->pixels
    );

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

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    Texp t = new Tex(name);
    auto result = textures.insert(std::make_pair(name, t));

    if (result.second == false) {
        ERR("tex insert name '%s' failed", name.c_str());
    }

    t->width = surface->w;
    t->height = surface->h;
    t->gl_surface_binding = gl_surface_binding;
    t->surface = surface;

    return (t);
}

int32_t tex_get_gl_binding (Texp tex)
{_
    return (tex->gl_surface_binding);
}

uint32_t tex_get_width (Texp tex)
{_
    if (!tex) {
        ERR("no texture");
    }

    return (tex->width);
}

uint32_t tex_get_height (Texp tex)
{_
    if (!tex) {
        ERR("no texture");
    }

    return (tex->height);
}

SDL_Surface *tex_get_surface (Texp tex)
{_
    return (tex->surface);
}

Texp string2tex (const char **s)
{_
    static char tmp[MAXSHORTSTR];
    static std::string eo_tmp = tmp + MAXSHORTSTR;
    const char *c = *s;
    char *t = tmp;

    while (t < eo_tmp) {
        if ((*c == '\0') || (*c == '$')) {
            break;
        }

        *t++ = *c++;
    }

    if (c == eo_tmp) {
        return (0);
    }

    *t++ = '\0';
    *s += (t - tmp);

    auto result = textures.find(tmp);
    if (result == textures.end()) {
        ERR("unknown tex '%s'", tmp);
    }

    return (result->second);
}

Texp string2tex (std::string &s, int *len)
{_
    auto iter = s.begin();
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
        ERR("unknown tex '%s'", out.c_str());
    }

    auto result = textures.find(out);
    if (result == textures.end()) {
        ERR("unknown tex '%s'", out.c_str());
    }

    return (result->second);
}

Texp string2tex (std::wstring &s, int *len)
{_
    auto v = wstring_to_string(s);
    return (string2tex(v, len));
}
