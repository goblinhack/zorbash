/*
 * Copyright (C) 2011-2020 goblinhack@gmail.com
 *
 * See the README file for license info for license.
 */

#include "my_stb_image.h"

#include <SDL.h>
#include "my_glapi.h"
#include "my_tex.h"
#include "my_ramdisk.h"
#include "my_pixel.h"
#include "my_math_util.h"
#include "my_string.h"

class tex {

public:
    tex (void)
    {
    }

    ~tex (void)
    {
        SDL_FreeSurface(this->surface);

        GLuint gl_surface_binding;
        gl_surface_binding = this->gl_surface_binding;

        glDeleteTextures(1, &gl_surface_binding);

        oldptr(this->surface);
    }

    uint32_t width = {};
    uint32_t height = {};

    int32_t gl_surface_binding = {};

    SDL_Surface *surface = {};
};

std::map<std::string, std::shared_ptr< class tex > > textures;

static uint8_t tex_init_done;

uint8_t tex_init (void)
{_
    tex_init_done = true;

    return (true);
}

static void tex_destroy (texp t)
{_
}

void tex_fini (void)
{_
    if (tex_init_done) {
        tex_init_done = false;

        auto iter = textures.begin();

        while (iter != textures.end()) {
            tex_destroy(iter->second);
            iter = textures.erase(iter);
        }
    }
}

static unsigned char *load_raw_image (std::string filename,
                                      int32_t *x,
                                      int32_t *y,
                                      int32_t *comp)
{_
    unsigned char *ramdisk_data;
    unsigned char *image_data = 0;
    int32_t len;

    ramdisk_data = ramdisk_load(filename.c_str(), &len);
    if (!ramdisk_data) {
        DIE("could not read file, %s", filename.c_str());
    }

    if (filename.find(".tga")) {
        image_data = stbi_tga_load_from_memory(ramdisk_data,
                                               len, x, y, comp, 0);
    } else if (filename.find(".jpg")) {
        image_data = stbi_jpeg_load_from_memory(ramdisk_data,
                                                len, x, y, comp, 0);
    } else if (filename.find(".bmp")) {
        image_data = stbi_bmp_load_from_memory(ramdisk_data,
                                               len, x, y, comp, 0);
    } else if (filename.find(".png")) {
        image_data = stbi_png_load_from_memory(ramdisk_data,
                                               len, x, y, comp, 0);
    } else {
        DIE("unknown suffix for image, %s", filename.c_str());
    }

    if (!image_data) {
        DIE("could not read memory for file, %s", filename.c_str());
    }

    DBG("Load %s, %ux%u", filename.c_str(), *x, *y);

    myfree(ramdisk_data);

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
        DIE("could not read memory for file, %s", filename.c_str());
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
        surf = SDL_ConvertSurfaceFormat(old_surf, SDL_PIXELFORMAT_RGBA8888, 0);
        newptr(surf, "SDL_CreateRGBSurface");
        oldptr(old_surf);
        SDL_FreeSurface(old_surf);
        SDL_SaveBMP(surf, filename.c_str());
        DIE("x");
    }

    free_raw_image(image_data);

    return (surf);
}

/*
 * Load a texture
 */
texp tex_load (std::string file, std::string name, int mode)
{_
    texp t = tex_find(name);

    if (t) {
        return (t);
    }

    if (file == "") {
        if (name == "") {
            DIE("no file for tex");
            return (0);
        } else {
            DIE("no file for tex loading %s", name.c_str());
            return (0);
        }
    }

    SDL_Surface *surface = 0;
    surface = load_image(file);

    if (!surface) {
        DIE("could not make surface from file, %s", file.c_str());
    }

    t = tex_from_surface(surface, file, name, mode);

    return (t);
}

/*
 * Find an existing tex.
 */
texp tex_find (std::string file)
{_
    if (file == "") {
        DIE("no filename given for tex find");
    }

    auto result = textures.find(file);
    if (result == textures.end()) {
        return (0);
    }

    return (result->second);
}

/*
 * Creae a texture from a surface
 */
texp tex_from_surface (SDL_Surface *surface,
                       std::string file,
                       std::string name,
                       int mode)
{_
    texp t;

    if (!surface) {
        DIE("could not make surface from file, %s", file.c_str());
    }

    /*
     * Check that the sdl_surface's width is a power of 2
     */
    if ((surface->w & (surface->w - 1)) != 0) {
        /*
        LOG("%s has a width %u that is not a power of 2", file, surface->w);
         */
    }

    /*
     * Also check if the height is a power of 2
     */
    if ((surface->h & (surface->h - 1)) != 0) {
        /*
        LOG("%s has a height %u that is not a power of 2", file, surface->h);
        */
    }

    DBG("Texture: %s, %dx%d", file.c_str(), surface->w, surface->h);

    /*
     * Get the number of channels in the SDL surface
     */
    int32_t channels = surface->format->BytesPerPixel;
    int32_t textureFormat = 0;

    if (channels == 4) {
        /*
         * Contains alpha channel
         */
        if (surface->format->Rmask == 0x000000ff) {
            textureFormat = GL_RGBA;
        } else {
            textureFormat = GL_BGRA;
        }
    } else if (channels == 3) {
        /*
         * Contains no alpha channel
         */
        if (surface->format->Rmask == 0x000000ff) {
            textureFormat = GL_RGB;
        } else {
#ifdef GL_BGR
            textureFormat = GL_BGR;
#else
            DIE("%s Need support for GL_BGR", file);
#endif
        }
    } else {
        DIE("%s is not truecolor, need %d bytes per pixel", file.c_str(),
            channels);
    }

    /*
     * Create the tex
     */
    GLuint gl_surface_binding = 0;

    glEnable(GL_TEXTURE_2D); /* Apparently needed for ATI drivers */

    glGenTextures(1, &gl_surface_binding);

    /*
     * Typical tex generation using data from the bitmap
     */
    glBindTexture(GL_TEXTURE_2D, gl_surface_binding);

    /*
     * Generate the tex
     */
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

    /*
     * linear filtering. Nearest is meant to be quicker but I didn't see
     * that in reality.
     */
    if (mode == GL_NEAREST) {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    } else {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    }

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    /*
     * For clouds
     */
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    t = std::make_shared< class tex >();

    auto result = textures.insert(std::make_pair(name, t));

    if (result.second == false) {
        DIE("tex insert name [%s] failed", name.c_str());
    }

    t->width = surface->w;
    t->height = surface->h;
    t->gl_surface_binding = gl_surface_binding;
    t->surface = surface;

    return (t);
}

int32_t tex_get_gl_binding (texp tex)
{_
    return (tex->gl_surface_binding);
}

uint32_t tex_get_width (texp tex)
{_
    if (!tex) {
        DIE("no texture");
    }

    return (tex->width);
}

uint32_t tex_get_height (texp tex)
{_
    if (!tex) {
        DIE("no texture");
    }

    return (tex->height);
}

SDL_Surface *tex_get_surface (texp tex)
{_
    return (tex->surface);
}

/*
 * Blits a whole tex.
 */
void tex_blit (texp tex, point at)
{_
    static point tl, br;

    tl.x = at.x - tex->width/2;
    br.y = at.y - tex->height/2;
    br.x = at.x + tex->width/2;
    tl.y = at.y + tex->height/2;

    blit(tex->gl_surface_binding,
         0.0f, 1.0f, 1.0f, 0.0f, tl.x, tl.y, br.x, br.y);
}

texp string2tex (const char **s)
{_
    static char tmp[MAXSTR];
    static std::string eo_tmp = tmp + MAXSTR;
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
        DIE("unknown tex [%s]", tmp);
    }

    return (result->second);
}

texp string2tex (std::string &s, int *len)
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
        DIE("unknown tex [%s]", out.c_str());
    }

    auto result = textures.find(out);
    if (result == textures.end()) {
        DIE("unknown tex [%s]", out.c_str());
    }

    return (result->second);
}

texp string2tex (std::wstring &s, int *len)
{_
    auto v = wstring_to_string(s);
    return (string2tex(v, len));
}
