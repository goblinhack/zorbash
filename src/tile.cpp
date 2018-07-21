/*
 * Copyright (C) 2018 goblinhack@gmail.com
 *
 * See the README file for license info for license.
 */

#include "my_glapi.h"
#include "my_tile.h"
#include "my_tex.h"
#include "my_pixel.h"
#include "my_size.h"
#include "my_string.h"

std::map<std::string, std::shared_ptr< class tile > > tiles;

static uint8_t tile_init_done;

uint8_t tile_init (void)
{_
    tile_init_done = true;

    return (true);
}

static void tile_destroy (tilep t)
{_
}

void tile_fini (void)
{_
    if (tile_init_done) {
        tile_init_done = false;

        auto iter = tiles.begin();

        while (iter != tiles.end()) {
            tile_destroy(iter->second);
            iter = tiles.erase(iter);
        }
    }
}

void tile_load_arr (std::string tex_name,
                    uint32_t width, uint32_t height,
                    uint32_t nargs, const char * arr[])
{_
    texp tex = tex_load("", tex_name, GL_LINEAR);

    float fw = 1.0 / (((float)tex_get_width(tex)) / ((float)width));
    float fh = 1.0 / (((float)tex_get_height(tex)) / ((float)height));
    float pw = 1.0 / ((float)tex_get_width(tex));
    float ph = 1.0 / ((float)tex_get_height(tex));
    pw /= 2.0;
    ph /= 2.0;

    int x = 0;
    int y = 0;
    int idx = 0;

    size pixel_size;

    pixel_size.w = width;
    pixel_size.h = height;

    while (nargs--) {

        std::string name = arr[idx++];

        if (name != "") {

            if (tile_find(name)) {
                ERR("tile name [%s] already used", name.c_str());
            }

	    auto t = std::make_shared< class tile >();

	    auto result = tiles.insert(std::make_pair(name, t));

	    if (result.second == false) {
		DIE("tile insert name [%s] failed", name.c_str());
	    }

            t->name = name;
            t->index = idx - 1;
            t->pix_width = width;
            t->pix_height = height;
            t->tex = tex;
            t->gl_surface_binding = tex_get_gl_binding(tex);

            t->x1 = fw * (float)(x);
            t->y1 = fh * (float)(y);
            t->x2 = t->x1 + fw;
            t->y2 = t->y1 + fh;

            t->ox1 = t->x1;
            t->oy1 = t->y1;
            t->ox2 = t->x2;
            t->oy2 = t->y2;

            /*
             * Why? Texture atlas and GL_LINEAR will cause problems blending
             * with tiles adjacent in the atlas, so we trim 0.5 of a pixel
             * all around.
             */
            t->x1 += pw;
            t->x2 -= pw;
            t->y1 += ph;
            t->y2 -= ph;

            t->pct_width = fw;
            t->pct_height = fh;

#ifdef DEBUG_TILE
            printf("Tile: %-10s %ux%u (%u, %u)", name.c_str(), width, height, x, y);
#endif

#ifdef NEED_TILE_BOUNDS
            SDL_Surface *s = tex_get_surface(tex);

	    point AT = {
                pixel_size.w * x,
                pixel_size.h * y
            };

	    point MAX = {
                pixel_size.w * x,
		pixel_size.h * y
            };

	    point MIN = {
               (pixel_size.w * x) + pixel_size.w - 1,
	       (pixel_size.h * y) + pixel_size.h - 1
            };

            int x1, y1;

	    for (y1=pixel_size.h - 1; y1>=0; y1--) {
		for (x1=0; x1<pixel_size.w; x1++) {

		    point at = {
                        (pixel_size.w * x) + x1,
			(pixel_size.h * y) + y1
                    };

		    color p = getPixel(s, at.x, at.y);

                    /*
                     * If solid...
                     */
		    if (p.a >= 0xef) {
			MIN.x = std::min(at.x, MIN.x);
			MIN.y = std::min(at.y, MIN.y);
			MAX.x = std::max(at.x, MAX.x);
			MAX.y = std::max(at.y, MAX.y);
#ifdef DEBUG_TILE
                        printf("X");
#endif
                        if ((x1 < MAX_TILE_WIDTH) && (y1 < MAX_TILE_HEIGHT)) {
                            t->pix[x1][y1] = 1;
                        }
                    } else if (p.a > 0) {
#ifdef DEBUG_TILE
                        printf(".");
#endif
		    } else {
#ifdef DEBUG_TILE
                        printf(" ");
#endif
                    }
		}
#ifdef DEBUG_TILE
                printf("\n");
#endif
	    }

            t->px1 = ((double) (MIN.x - AT.x)) / (double) pixel_size.w;
            t->px2 = ((double) (MAX.x - AT.x + 1)) / (double) pixel_size.w;
            t->py1 = ((double) (MIN.y - AT.y)) / (double) pixel_size.h;
            t->py2 = ((double) (MAX.y - AT.y + 1)) / (double) pixel_size.h;
#endif

#ifdef DEBUG_TILE
            printf("^^^  %s %f %f %f %f min x %d %d min y %d %d\n",name.c_str(),t->px1,t->py1,t->px2,t->py2, MIN.x,MAX.x,MIN.y,MAX.y);
#endif
        }

        x++;

        /*
         * Check the whole tile can be read
         */
        if ((x * width) + (width - 1) >= tex_get_width(tex)) {
            x = 0;
            y++;
        }

        if (y * height > tex_get_height(tex)) {
            if (name != "") {
                ERR("overflow reading tile arr[%s]", name.c_str());
            } else {
                ERR("overflow reading tile arr at x %d y %d", x, y);
            }
        }
    }
}

/*
 * Find an existing tile.
 */
tilep tile_find (std::string name)
{_
    if (name == "") {
        ERR("no name for tile find");
	return (0);
    }

    auto result = tiles.find(name);

    if (result == tiles.end()) {
        return (0);
    }

    return (result->second);
}

int32_t tile_get_gl_binding (tilep tile)
{_
    return (tile->gl_surface_binding);
}

int32_t tile_get_width (tilep tile)
{_
    return (tile->pix_width);
}

std::string tile_get_name (tilep tile)
{_
    return (tile->name);
}

int32_t tile_get_height (tilep tile)
{_
    return (tile->pix_height);
}

texp tile_get_tex (tilep tile)
{_
    return (tile->tex);
}

uint32_t tile_get_index (tilep tile)
{_
    return (tile->index);
}

void tile_get_coords (tilep tile, float *x1, float *y1, float *x2, float *y2)
{_
    *x1 = tile->x1;
    *y1 = tile->x1;
    *x2 = tile->x2;
    *x2 = tile->x2;
}

tilep string2tile (const char **s)
{_
    static char tmp[MAXSTR];
    static const char * eo_tmp = tmp + MAXSTR;
    const char * c = *s;
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

    auto result = tiles.find(tmp);

    if (result == tiles.end()) {
        DIE("unknown tile [%s]", tmp);
        return (0);
    }

    return (result->second);
}

tilep string2tile (std::string &s, int *len)
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

    if (iter == s.end()) {
        DIE("unknown tile [%s]", out.c_str());
    }

    if (len) {
        *len = iter - s.begin();
    }

    auto result = tiles.find(out);
    if (result == tiles.end()) {
        DIE("unknown tile [%s]", out.c_str());
    }

    return (result->second);
}

tilep string2tile (std::wstring &s, int *len)
{_
    auto v = wstring_to_string(s);
    return (string2tile(v, len));
}

/*
 * Blits a whole tile. Y co-ords are inverted.
 */
void tile_blit_fat (tpp tp, tilep tile, char *name, fpoint *tl, fpoint *br)
{
    double x1;
    double x2;
    double y1;
    double y2;

    x1 = tile->x1;
    x2 = tile->x2;
    y1 = tile->y1;
    y2 = tile->y2;

    if (unlikely(tp != 0)) {
        double left_off  = (double)tp_get_blit_left_off(tp);
        double right_off = (double)tp_get_blit_right_off(tp);
        double top_off   = (double)tp_get_blit_top_off(tp);
        double bot_off   = (double)tp_get_blit_bot_off(tp);

        double pct_w     = tile->pct_width;
        double pct_h     = tile->pct_height;
        double pix_w     = br->x - tl->x;
        double pix_h     = br->y - tl->y;

        tl->x -= left_off  * pix_w;
        br->x += right_off * pix_w;
        tl->y -= top_off   * pix_h;
        br->y += bot_off   * pix_h;

        x1 -= left_off  * pct_w;
        x2 += right_off * pct_w;
        y1 -= top_off   * pct_h;
        y2 += bot_off   * pct_h;
    }

    blit(tile->gl_surface_binding,
         x1, y2, x2, y1, tl->x, br->y, br->x, tl->y);
}

/*
 * Blits a whole tile. Y co-ords are inverted.
 */
void tile_blit_fat_with_offset (tpp tp, tilep tile, 
                                char *name, fpoint *tl,
                                fpoint *br,
                                double left_off,
                                double right_off,
                                double top_off,
                                double bot_off)
{
    double x1;
    double x2;
    double y1;
    double y2;

    x1 = tile->x1;
    x2 = tile->x2;
    y1 = tile->y1;
    y2 = tile->y2;

    double pct_w     = tile->pct_width;
    double pct_h     = tile->pct_height;
    double pix_w     = br->x - tl->x;
    double pix_h     = br->y - tl->y;

    tl->x -= left_off  * pix_w;
    br->x += right_off * pix_w;
    tl->y -= top_off   * pix_h;
    br->y += bot_off   * pix_h;

    x1 -= left_off  * pct_w;
    x2 += right_off * pct_w;
    y1 -= top_off   * pct_h;
    y2 += bot_off   * pct_h;

    blit(tile->gl_surface_binding,
         x1, y2, x2, y1, tl->x, br->y, br->x, tl->y);
}

/*
 * Given tile bounds, stretch them to get the full size.
 */
void tile_get_blit_size (tpp tp, tilep tile, char *name, fpoint *tl, fpoint *br)
{
    if (tp) {
        double left_off  = (double)tp_get_blit_left_off(tp);
        double right_off = (double)tp_get_blit_right_off(tp);
        double top_off   = (double)tp_get_blit_top_off(tp);
        double bot_off   = (double)tp_get_blit_bot_off(tp);

        double pix_w     = br->x - tl->x;
        double pix_h     = br->y - tl->y;

        tl->x -= left_off  * pix_w;
        br->x += right_off * pix_w;
        tl->y -= top_off   * pix_h;
        br->y += bot_off   * pix_h;
    }
}

/*
 * Blits a whole tile.
 */
void tile_blit_at (tilep tile, char *name, fpoint tl, fpoint br)
{
    blit(tile->gl_surface_binding,
         tile->x1, tile->y2, tile->x2, tile->y1, tl.x, tl.y, br.x, br.y);
}

/*
 * Blits a whole tile.
 */
void tile_blit (tilep tile, char *name, point at)
{
    fpoint tl, br;

    tl.x = at.x - tile->pix_width/2;
    br.y = at.y - tile->pix_height/2;
    br.x = at.x + tile->pix_width/2;
    tl.y = at.y + tile->pix_height/2;

    tile_blit_at(tile, name, tl, br);
}

/*
 * Blits a whole tile. Y co-ords are inverted.
 */
void tile_blit_colored_fat (tpp tp,
                            tilep tile,
                            fpoint tl,
                            fpoint br,
                            color color_tl,
                            color color_tr,
                            color color_bl,
                            color color_br)
{
    double x1 = tile->x1;
    double x2 = tile->x2;
    double y1 = tile->y1;
    double y2 = tile->y2;

    if (unlikely(tp != 0)) {
        double left_off  = (double)tp_get_blit_left_off(tp);
        double right_off = (double)tp_get_blit_right_off(tp);
        double top_off   = (double)tp_get_blit_top_off(tp);
        double bot_off   = (double)tp_get_blit_bot_off(tp);

        double pct_w     = tile->pct_width;
        double pct_h     = tile->pct_height;
        double pix_w     = br.x - tl.x;
        double pix_h     = br.y - tl.y;

        tl.x -= left_off  * pix_w;
        br.x += right_off * pix_w;
        tl.y -= top_off   * pix_h;
        br.y += bot_off   * pix_h;

        x1 -= left_off  * pct_w;
        x2 += right_off * pct_w;
        y1 -= top_off   * pct_h;
        y2 += bot_off   * pct_h;
    }

    blit_colored(tile->gl_surface_binding,
                 x1, y2, x2, y1,
                 tl.x, br.y, br.x, tl.y,
                 color_tl,
                 color_tr,
                 color_bl,
                 color_br);
}
