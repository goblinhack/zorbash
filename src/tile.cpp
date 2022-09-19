//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_color_defs.hpp"
#include "my_dmap.hpp"
#include "my_game.hpp"
#include "my_gl.hpp"
#include "my_globals.hpp"
#include "my_pixel.hpp"
#include "my_ptrcheck.hpp"
#include "my_random.hpp"
#include "my_size.hpp"
#include "my_string.hpp"
#include "my_sys.hpp"
#include "my_template.hpp"
#include "my_tex.hpp"
#include "my_thing_template.hpp"
#include "my_tile.hpp"

std::map< std::string, class Tile * > all_tiles;
std::vector< class Tile * >           all_tiles_array;

static uint8_t tile_init_done;

#define ENABLE_TILE_BOUNDS

Tile::Tile(void) { newptr(MTYPE_TILE, this, "Tile"); }

Tile::~Tile(void) { oldptr(MTYPE_TILE, this); }

Tilep tile_index_to_tile(uint16_t i)
{
  if (unlikely(! i)) {
    return nullptr;
  } else {
    return all_tiles_array[ i - 1 ];
  }
}

uint8_t tile_init(void);
uint8_t tile_init(void)
{
  TRACE_AND_INDENT();
  tile_init_done = true;

  return true;
}

void tile_fini(void)
{
  TRACE_AND_INDENT();
  if (tile_init_done) {
    tile_init_done = false;
  }

  for (auto &t : all_tiles) {
    verify(MTYPE_TILE, t.second);
    delete t.second;
  }

  all_tiles_array.clear();
}

Tile::Tile(const class Tile *tile)
{
  newptr(MTYPE_TILE, this, "Tile copy");

  pix_width  = tile->pix_width;
  pix_height = tile->pix_height;
  pct_width  = tile->pct_width;
  pct_height = tile->pct_height;
  x1         = tile->x1;
  y1         = tile->y1;
  x2         = tile->x2;
  y2         = tile->y2;

#ifdef ENABLE_TILE_BOUNDS
  ox1 = tile->ox1;
  oy1 = tile->oy1;
  ox2 = tile->ox2;
  oy2 = tile->oy2;
  px1 = tile->px1;
  py1 = tile->py1;
  px2 = tile->px2;
  py2 = tile->py2;
#endif

  set_gl_binding(tile->gl_binding());
  set_gl_binding_black_and_white(tile->gl_binding_black_and_white());
  set_gl_binding_mask(tile->gl_binding_mask());

  tex                 = tile->tex;
  tex_black_and_white = tile->tex_black_and_white;
  tex_mask            = tile->tex_mask;

  std::copy(mbegin(tile->pix), mend(tile->pix), mbegin(pix));

  delay_ms                      = tile->delay_ms;
  dir                           = tile->dir;
  is_join_node                  = tile->is_join_node;
  is_join_left                  = tile->is_join_left;
  is_join_bot                   = tile->is_join_bot;
  is_join_right                 = tile->is_join_right;
  is_join_top                   = tile->is_join_top;
  is_join_horiz                 = tile->is_join_horiz;
  is_join_vert                  = tile->is_join_vert;
  is_join_l90                   = tile->is_join_l90;
  is_join_l                     = tile->is_join_l;
  is_join_l270                  = tile->is_join_l270;
  is_join_l180                  = tile->is_join_l180;
  is_join_t270                  = tile->is_join_t270;
  is_join_t180                  = tile->is_join_t180;
  is_join_t90                   = tile->is_join_t90;
  is_join_t                     = tile->is_join_t;
  is_join_x                     = tile->is_join_x;
  is_moving                     = tile->is_moving;
  is_yyy5                       = tile->is_yyy5;
  is_yyy6                       = tile->is_yyy6;
  is_yyy7                       = tile->is_yyy7;
  is_yyy8                       = tile->is_yyy8;
  is_yyy9                       = tile->is_yyy9;
  is_invisible                  = tile->is_invisible;
  is_hp_25_percent              = tile->is_hp_25_percent;
  is_hp_50_percent              = tile->is_hp_50_percent;
  is_hp_75_percent              = tile->is_hp_75_percent;
  is_hp_100_percent             = tile->is_hp_100_percent;
  is_sleeping                   = tile->is_sleeping;
  is_open                       = tile->is_open;
  is_dead                       = tile->is_dead;
  is_end_of_anim                = tile->is_end_of_anim;
  is_end_of_ascii_anim          = tile->is_end_of_ascii_anim;
  is_dead_on_end_of_anim        = tile->is_dead_on_end_of_anim;
  is_dead_on_end_of_ascii_anim  = tile->is_dead_on_end_of_ascii_anim;
  is_alive_on_end_of_anim       = tile->is_alive_on_end_of_anim;
  is_alive_on_end_of_ascii_anim = tile->is_alive_on_end_of_ascii_anim;
  internal_has_dir_anim         = tile->internal_has_dir_anim;
  ascii_fg_char                 = tile->ascii_fg_char;
  ascii_bg_char                 = tile->ascii_bg_char;
  ascii_bg_col_name             = tile->ascii_bg_col_name;
  ascii_fg_col_name             = tile->ascii_fg_col_name;
  ascii_bg_alpha                = tile->ascii_bg_alpha;
  ascii_fg_alpha                = tile->ascii_fg_alpha;

  index        = 0;
  global_index = all_tiles_array.size() + 1;
  name         = tile->name + " " + std::to_string(global_index);

  auto result = all_tiles.insert(std::make_pair(name, this));
  if (result.second == false) {
    ERR("Tile copy insert name [%s] failed", name.c_str());
  }
  all_tiles_array.push_back(this);
}

void tile_load_arr(std::string file, std::string name, uint32_t width, uint32_t height, uint32_t nargs,
                   const char *arr[])
{
  TRACE_AND_INDENT();
  Texp tex = tex_load(file, name, GL_NEAREST);

  float fw = 1.0 / ((((float) tex_get_width(tex))) / (((float) width)));
  float fh = 1.0 / ((((float) tex_get_height(tex))) / (((float) height)));

  int x   = 0;
  int y   = 0;
  int idx = 0;

  isize pixel_size;

  pixel_size.w = width;
  pixel_size.h = height;

  while (nargs--) {
    std::string name = arr[ idx++ ];

    if (name != "") {
      if (tile_find(name)) {
        ERR("Tile name [%s] already used", name.c_str());
      }

      auto t      = new Tile(); // std::make_shared< class Tile >();
      auto result = all_tiles.insert(std::make_pair(name, t));
      if (result.second == false) {
        ERR("Tile insert name [%s] failed", name.c_str());
      }

      //
      // Global array of all tiles
      //
      all_tiles_array.push_back(t);
      t->global_index = all_tiles_array.size();

      t->name       = name;
      t->index      = idx - 1;
      t->pix_width  = width;
      t->pix_height = height;
      t->tex        = tex;
      t->set_gl_binding(tex_get_gl_binding(tex));

      t->x1 = fw * ((float) (x));
      t->y1 = fh * ((float) (y));
      t->x2 = t->x1 + fw;
      t->y2 = t->y1 + fh;

#ifdef ENABLE_TILE_BOUNDS
      t->ox1 = t->x1;
      t->oy1 = t->y1;
      t->ox2 = t->x2;
      t->oy2 = t->y2;
#endif

      t->pct_width  = fw;
      t->pct_height = fh;

#ifdef ENABLE_DEBUG_TILE
      printf("Tile: %-10s %ux%u (%u, %u)", name.c_str(), width, height, x, y);
#endif

#ifdef ENABLE_TILE_BOUNDS
      if ((pixel_size.w <= TILE_WIDTH_MAX) && (pixel_size.h <= TILE_HEIGHT_MAX)) {
        SDL_Surface *s = tex_get_surface(tex);

        point off = make_point(pixel_size.w * x, pixel_size.h * y);

        point MAX = make_point(pixel_size.w * x, pixel_size.h * y);

        point MIN = make_point((pixel_size.w * x) + pixel_size.w - 1, (pixel_size.h * y) + pixel_size.h - 1);

        int x1, y1;

        for (y1 = pixel_size.h - 1; y1 >= 0; y1--) {
          for (x1 = 0; x1 < pixel_size.w; x1++) {

            point at = make_point((pixel_size.w * x) + x1, (pixel_size.h * y) + y1);

            color p;
            getPixel(s, at.x, at.y, p);

            //
            // If solid...
            //
            if (p.a >= 0xef) {
              MIN.x = std::min(at.x, MIN.x);
              MIN.y = std::min(at.y, MIN.y);
              MAX.x = std::max(at.x, MAX.x);
              MAX.y = std::max(at.y, MAX.y);
#ifdef ENABLE_DEBUG_TILE
              printf("X");
#endif
              if ((x1 < TILE_WIDTH_MAX) && (y1 < TILE_HEIGHT_MAX)) {
                set(t->pix, x1, y1, (uint8_t) 1);
              }
            } else if (p.a > 0) {
#ifdef ENABLE_DEBUG_TILE
              printf(".");
#endif
            } else {
#ifdef ENABLE_DEBUG_TILE
              printf(" ");
#endif
            }
          }
#ifdef ENABLE_DEBUG_TILE
          printf("\n");
#endif
        }

        t->px1 = (((float) (MIN.x) - off.x)) / ((float) pixel_size.w);
        t->px2 = (((float) (MAX.x) - off.x + 1)) / ((float) pixel_size.w);
        t->py1 = (((float) (MIN.y) - off.y)) / ((float) pixel_size.h);
        t->py2 = (((float) (MAX.y) - off.y + 1)) / ((float) pixel_size.h);
      }
#endif

#ifdef ENABLE_DEBUG_TILE
      printf("^^^  %s %f %f %f %f\n", name.c_str(), t->px1, t->py1, t->px2, t->py2);
#endif
    }

    x++;

    //
    // Check the whole tile can be read
    //
    if ((x * width) + (width - 1) >= tex_get_width(tex)) {
      x = 0;
      y++;
    }

    if (y * height > tex_get_height(tex)) {
      if (name != "") {
        ERR("Overflow reading tile arr[%s]", name.c_str());
      } else {
        ERR("Overflow reading tile arr at x %d y %d", x, y);
      }
    }
  }
}

void tile_load_arr(std::string file, std::string name, uint32_t width, uint32_t height,
                   const std::vector< std::string > &arr)
{
  TRACE_AND_INDENT();
  Texp tex = tex_load(file, name, GL_NEAREST);

  float fw = 1.0 / ((((float) tex_get_width(tex))) / (((float) width)));
  float fh = 1.0 / ((((float) tex_get_height(tex))) / (((float) height)));

  int x   = 0;
  int y   = 0;
  int idx = 0;

  isize pixel_size;

  pixel_size.w = width;
  pixel_size.h = height;

  for (auto &name : arr) {
    idx++;

    if (name != "") {
      if (tile_find(name)) {
        ERR("Tile name [%s] already used", name.c_str());
      }

      auto t      = new Tile(); // std::make_shared< class Tile >();
      auto result = all_tiles.insert(std::make_pair(name, t));
      if (result.second == false) {
        ERR("Tile insert name [%s] failed", name.c_str());
      }

      //
      // Global array of all tiles
      //
      all_tiles_array.push_back(t);
      t->global_index = all_tiles_array.size();

      t->name       = name;
      t->index      = idx - 1;
      t->pix_width  = width;
      t->pix_height = height;
      t->tex        = tex;
      t->set_gl_binding(tex_get_gl_binding(tex));

      t->x1 = fw * ((float) (x));
      t->y1 = fh * ((float) (y));
      t->x2 = t->x1 + fw;
      t->y2 = t->y1 + fh;

#ifdef ENABLE_TILE_BOUNDS
      t->ox1 = t->x1;
      t->oy1 = t->y1;
      t->ox2 = t->x2;
      t->oy2 = t->y2;
#endif

      t->pct_width  = fw;
      t->pct_height = fh;

#ifdef ENABLE_DEBUG_TILE
      printf("Tile: %-10s %ux%u (%u, %u)", name.c_str(), width, height, x, y);
#endif

#ifdef ENABLE_TILE_BOUNDS
      if ((pixel_size.w <= TILE_WIDTH_MAX) && (pixel_size.h <= TILE_HEIGHT_MAX)) {
        SDL_Surface *s = tex_get_surface(tex);

        point off = make_point(pixel_size.w * x, pixel_size.h * y);

        point MAX = make_point(pixel_size.w * x, pixel_size.h * y);

        point MIN = make_point((pixel_size.w * x) + pixel_size.w - 1, (pixel_size.h * y) + pixel_size.h - 1);

        int x1, y1;

        for (y1 = pixel_size.h - 1; y1 >= 0; y1--) {
          for (x1 = 0; x1 < pixel_size.w; x1++) {

            point at = make_point((pixel_size.w * x) + x1, (pixel_size.h * y) + y1);

            color p;
            getPixel(s, at.x, at.y, p);

            //
            // If solid...
            //
            if (p.a >= 0xef) {
              MIN.x = std::min(at.x, MIN.x);
              MIN.y = std::min(at.y, MIN.y);
              MAX.x = std::max(at.x, MAX.x);
              MAX.y = std::max(at.y, MAX.y);
#ifdef ENABLE_DEBUG_TILE
              printf("X");
#endif
              if ((x1 < TILE_WIDTH_MAX) && (y1 < TILE_HEIGHT_MAX)) {
                set(t->pix, x1, y1, (uint8_t) 1);
              }
            } else if (p.a > 0) {
#ifdef ENABLE_DEBUG_TILE
              printf(".");
#endif
            } else {
#ifdef ENABLE_DEBUG_TILE
              printf(" ");
#endif
            }
          }
#ifdef ENABLE_DEBUG_TILE
          printf("\n");
#endif
        }

        t->px1 = (((float) (MIN.x) - off.x)) / ((float) pixel_size.w);
        t->px2 = (((float) (MAX.x) - off.x + 1)) / ((float) pixel_size.w);
        t->py1 = (((float) (MIN.y) - off.y)) / ((float) pixel_size.h);
        t->py2 = (((float) (MAX.y) - off.y + 1)) / ((float) pixel_size.h);
      }
#endif

#ifdef ENABLE_DEBUG_TILE
      printf("^^^  %s %f %f %f %f\n", name.c_str(), t->px1, t->py1, t->px2, t->py2);
#endif
    }

    x++;

    //
    // Check the whole tile can be read
    //
    if ((x * width) + (width - 1) >= tex_get_width(tex)) {
      x = 0;
      y++;
    }

    if (y * height > tex_get_height(tex)) {
      if (name != "") {
        ERR("Overflow reading tile arr[%s]", name.c_str());
      } else {
        ERR("Overflow reading tile arr at x %d y %d", x, y);
      }
    }
  }
}

void tile_load_arr_sprites(std::string file, std::string name, uint32_t width, uint32_t height, uint32_t nargs,
                           const char *arr[], int gl_mode)
{
  TRACE_AND_INDENT();
  Texp tex;
  Texp tex_black_and_white;
  Texp tex_mask;

  tex_load(&tex, &tex_black_and_white, &tex_mask, file, name, gl_mode);

  float fw = 1.0 / ((((float) tex_get_width(tex))) / (((float) width)));
  float fh = 1.0 / ((((float) tex_get_height(tex))) / (((float) height)));

  int x   = 0;
  int y   = 0;
  int idx = 0;

  isize pixel_size;

  pixel_size.w = width;
  pixel_size.h = height;

  while (nargs--) {
    std::string name = arr[ idx++ ];

    if (name != "") {
      if (tile_find(name)) {
        ERR("Tile name [%s] already used", name.c_str());
      }

      IF_DEBUG3 { LOG("Add tile name [%s]", name.c_str()); }

      auto t      = new Tile(); // std::make_shared< class Tile >();
      auto result = all_tiles.insert(std::make_pair(name, t));
      if (result.second == false) {
        ERR("Tile insert name [%s] failed", name.c_str());
      }

      //
      // Global array of all tiles
      //
      all_tiles_array.push_back(t);
      t->global_index = all_tiles_array.size();

      t->name                = name;
      t->index               = idx - 1;
      t->pix_width           = width;
      t->pix_height          = height;
      t->tex                 = tex;
      t->tex_black_and_white = tex_black_and_white;
      t->tex_mask            = tex_mask;

      t->set_gl_binding(tex_get_gl_binding(tex));
      t->set_gl_binding_black_and_white(tex_get_gl_binding(tex_black_and_white));
      t->set_gl_binding_mask(tex_get_gl_binding(tex_mask));

      t->x1 = fw * ((float) (x));
      t->y1 = fh * ((float) (y));
      t->x2 = t->x1 + fw;
      t->y2 = t->y1 + fh;

#ifdef ENABLE_TILE_BOUNDS
      t->ox1 = t->x1;
      t->oy1 = t->y1;
      t->ox2 = t->x2;
      t->oy2 = t->y2;
#endif

      t->pct_width  = fw;
      t->pct_height = fh;

#ifdef ENABLE_DEBUG_TILE
      printf("Tile: %-10s %ux%u (%u, %u)", name.c_str(), width, height, x, y);
#endif

#ifdef ENABLE_TILE_BOUNDS
      if ((pixel_size.w <= TILE_WIDTH_MAX) && (pixel_size.h <= TILE_HEIGHT_MAX)) {
        SDL_Surface *s = tex_get_surface(tex);

        point off = make_point(pixel_size.w * x, pixel_size.h * y);

        point MAX = make_point(pixel_size.w * x, pixel_size.h * y);

        point MIN = make_point((pixel_size.w * x) + pixel_size.w - 1, (pixel_size.h * y) + pixel_size.h - 1);

        int x1, y1;

        for (y1 = pixel_size.h - 1; y1 >= 0; y1--) {
          for (x1 = 0; x1 < pixel_size.w; x1++) {

            point at = make_point((pixel_size.w * x) + x1, (pixel_size.h * y) + y1);

            color p;
            getPixel(s, at.x, at.y, p);

            //
            // If solid...
            //
            if (p.a >= 0xef) {
              MIN.x = std::min(at.x, MIN.x);
              MIN.y = std::min(at.y, MIN.y);
              MAX.x = std::max(at.x, MAX.x);
              MAX.y = std::max(at.y, MAX.y);
#ifdef ENABLE_DEBUG_TILE
              printf("X");
#endif
              if ((x1 < TILE_WIDTH_MAX) && (y1 < TILE_HEIGHT_MAX)) {
                set(t->pix, x1, y1, (uint8_t) 1);
              }
            } else if (p.a > 0) {
#ifdef ENABLE_DEBUG_TILE
              printf(".");
#endif
            } else {
#ifdef ENABLE_DEBUG_TILE
              printf(" ");
#endif
            }
          }
#ifdef ENABLE_DEBUG_TILE
          printf("\n");
#endif
        }

        t->px1 = (((float) (MIN.x) - off.x)) / ((float) pixel_size.w);
        t->px2 = (((float) (MAX.x) - off.x + 1)) / ((float) pixel_size.w);
        t->py1 = (((float) (MIN.y) - off.y)) / ((float) pixel_size.h);
        t->py2 = (((float) (MAX.y) - off.y + 1)) / ((float) pixel_size.h);
      }
#endif

#ifdef ENABLE_DEBUG_TILE
      printf("^^^  %s %f %f %f %f\n", name.c_str(), t->px1, t->py1, t->px2, t->py2);
#endif
    }

    x++;

    //
    // Check the whole tile can be read
    //
    if ((x * width) + (width - 1) >= tex_get_width(tex)) {
      x = 0;
      y++;
    }

    if (y * height > tex_get_height(tex)) {
      if (name != "") {
        ERR("Overflow reading tile arr[%s]", name.c_str());
      } else {
        ERR("Overflow reading tile arr at x %d y %d", x, y);
      }
    }
  }
}

void tile_load_arr_sprites(std::string file, std::string name, uint32_t width, uint32_t height,
                           const std::vector< std::string > &arr, int gl_mode)
{
  TRACE_AND_INDENT();
  Texp tex;
  Texp tex_black_and_white;
  Texp tex_mask;

  tex_load(&tex, &tex_black_and_white, &tex_mask, file, name, gl_mode);

  float fw = 1.0 / ((((float) tex_get_width(tex))) / (((float) width)));
  float fh = 1.0 / ((((float) tex_get_height(tex))) / (((float) height)));

  int x   = 0;
  int y   = 0;
  int idx = 0;

  isize pixel_size;

  pixel_size.w = width;
  pixel_size.h = height;

  for (auto &name : arr) {
    if (name != "") {
      if (tile_find(name)) {
        ERR("Tile name [%s] already used", name.c_str());
      }

      auto t      = new Tile(); // std::make_shared< class Tile >();
      auto result = all_tiles.insert(std::make_pair(name, t));
      if (result.second == false) {
        ERR("Tile insert name [%s] failed", name.c_str());
      }

      //
      // Global array of all tiles
      //
      all_tiles_array.push_back(t);
      t->global_index = all_tiles_array.size();

      t->name                = name;
      t->index               = idx - 1;
      t->pix_width           = width;
      t->pix_height          = height;
      t->tex                 = tex;
      t->tex_black_and_white = tex_black_and_white;
      t->tex_mask            = tex_mask;
      t->set_gl_binding(tex_get_gl_binding(tex));
      t->set_gl_binding_black_and_white(tex_get_gl_binding(tex_black_and_white));
      t->set_gl_binding_mask(tex_get_gl_binding(tex_mask));

      t->x1 = fw * ((float) (x));
      t->y1 = fh * ((float) (y));
      t->x2 = t->x1 + fw;
      t->y2 = t->y1 + fh;

#ifdef ENABLE_TILE_BOUNDS
      t->ox1 = t->x1;
      t->oy1 = t->y1;
      t->ox2 = t->x2;
      t->oy2 = t->y2;
#endif
      t->pct_width  = fw;
      t->pct_height = fh;

#ifdef ENABLE_DEBUG_TILE
      printf("Tile: %-10s %ux%u (%u, %u)", name.c_str(), width, height, x, y);
#endif

#ifdef ENABLE_TILE_BOUNDS
      if ((pixel_size.w <= TILE_WIDTH_MAX) && (pixel_size.h <= TILE_HEIGHT_MAX)) {
        SDL_Surface *s = tex_get_surface(tex);

        point off = make_point(pixel_size.w * x, pixel_size.h * y);

        point MAX = make_point(pixel_size.w * x, pixel_size.h * y);

        point MIN = make_point((pixel_size.w * x) + pixel_size.w - 1, (pixel_size.h * y) + pixel_size.h - 1);

        int x1, y1;

        for (y1 = pixel_size.h - 1; y1 >= 0; y1--) {
          for (x1 = 0; x1 < pixel_size.w; x1++) {

            point at = make_point((pixel_size.w * x) + x1, (pixel_size.h * y) + y1);

            color p;
            getPixel(s, at.x, at.y, p);

            //
            // If solid...
            //
            if (p.a >= 0xef) {
              MIN.x = std::min(at.x, MIN.x);
              MIN.y = std::min(at.y, MIN.y);
              MAX.x = std::max(at.x, MAX.x);
              MAX.y = std::max(at.y, MAX.y);
#ifdef ENABLE_DEBUG_TILE
              printf("X");
#endif
              if ((x1 < TILE_WIDTH_MAX) && (y1 < TILE_HEIGHT_MAX)) {
                set(t->pix, x1, y1, (uint8_t) 1);
              }
            } else if (p.a > 0) {
#ifdef ENABLE_DEBUG_TILE
              printf(".");
#endif
            } else {
#ifdef ENABLE_DEBUG_TILE
              printf(" ");
#endif
            }
          }
#ifdef ENABLE_DEBUG_TILE
          printf("\n");
#endif
        }

        t->px1 = (((float) (MIN.x) - off.x)) / ((float) pixel_size.w);
        t->px2 = (((float) (MAX.x) - off.x + 1)) / ((float) pixel_size.w);
        t->py1 = (((float) (MIN.y) - off.y)) / ((float) pixel_size.h);
        t->py2 = (((float) (MAX.y) - off.y + 1)) / ((float) pixel_size.h);
      }
#endif

#ifdef ENABLE_DEBUG_TILE
      printf("^^^  %s %f %f %f %f\n", name.c_str(), t->px1, t->py1, t->px2, t->py2);
#endif
    }

    x++;

    //
    // Check the whole tile can be read
    //
    if ((x * width) + (width - 1) >= tex_get_width(tex)) {
      x = 0;
      y++;
    }

    if (y * height > tex_get_height(tex)) {
      if (name != "") {
        ERR("Overflow reading tile arr[%s]", name.c_str());
      } else {
        ERR("Overflow reading tile arr at x %d y %d", x, y);
      }
    }
  }
}

//
// Find an existing tile.
//
Tilep tile_find(std::string name)
{
  TRACE_AND_INDENT();
  if (name == "") {
    return 0;
  }

  auto result = all_tiles.find(name);
  if (result == all_tiles.end()) {
    return 0;
  }

  return (result->second);
}

Tilep tile_find_mand(std::string name)
{
  TRACE_AND_INDENT();
  if (name == "") {
    ERR("No tile name give");
    return 0;
  }

  auto result = all_tiles.find(name);
  if (result == all_tiles.end()) {
    ERR("Tile name %s not found", name.c_str());
    return 0;
  }

  return (result->second);
}

std::string tile_get_name(Tilep tile) { return (tile->name); }

int tile_get_width(Tilep tile) { return (tile->pix_width); }

int tile_get_height(Tilep tile) { return (tile->pix_height); }

Texp tile_get_tex(Tilep tile) { return (tile->tex); }

uint32_t tile_get_index(Tilep tile) { return (tile->index); }

void tile_get_coords(Tilep tile, float *x1, float *y1, float *x2, float *y2)
{
  *x1 = tile->x1;
  *y1 = tile->x1;
  *x2 = tile->x2;
  *x2 = tile->x2;
}

Tilep string2tile(const char **s)
{
  TRACE_AND_INDENT();
  static char        name[ MAXSHORTSTR ];
  static const char *eo_name = name + MAXSHORTSTR;
  const char        *c       = *s;
  char              *t       = name;

  while (t < eo_name) {
    if ((*c == '\0') || (*c == '$')) {
      break;
    }

    *t++ = *c++;
  }

  if (c == eo_name) {
    return 0;
  }

  *t++ = '\0';
  *s += (t - name);

  auto result = all_tiles.find(name);
  if (result == all_tiles.end()) {
    ERR("Unknown tile [%s]", name);
    return 0;
  }

  return (result->second);
}

Tilep string2tile(std::string &s, int *len)
{
  TRACE_AND_INDENT();
  auto        iter = s.begin();
  std::string name;

  while (iter != s.end()) {
    auto c = *iter;

    if ((c == '\0') || (c == '$')) {
      break;
    }

    name += c;
    iter++;
  }

  if (iter == s.end()) {
    ERR("Unknown tile [%s]", name.c_str());
  }

  if (len) {
    *len = iter - s.begin();
  }

  auto result = all_tiles.find(name);
  if (result == all_tiles.end()) {
    ERR("Unknown tile [%s]", name.c_str());
  }

  return (result->second);
}

Tilep string2tile(std::wstring &s, int *len)
{
  TRACE_AND_INDENT();
  auto v = wstring_to_string(s);
  return (string2tile(v, len));
}

//
// Blits a whole tile.
//
void tile_blit_at(const Tilep &tile, point tl, point br)
{
  blit(tile->gl_binding(), tile->x1, tile->y2, tile->x2, tile->y1, tl.x, tl.y, br.x, br.y);
}

//
// Blits a whole tile. Y co-ords are inverted.
//
void tile_blit_colored_fat(Tpp tp, Tilep tile, point tl, point br, color color_tl, color color_tr, color color_bl,
                           color color_br)
{
  float x1 = tile->x1;
  float x2 = tile->x2;
  float y1 = tile->y1;
  float y2 = tile->y2;

  if (unlikely(tp != 0)) {
    float left_off  = (float) tp->blit_left_off();
    float right_off = (float) tp->blit_right_off();
    float top_off   = (float) tp->blit_top_off();
    float bot_off   = (float) tp->blit_bot_off();

    float pct_w = tile->pct_width;
    float pct_h = tile->pct_height;
    float pix_w = br.x - tl.x;
    float pix_h = br.y - tl.y;

    tl.x -= left_off * pix_w;
    br.x += right_off * pix_w;
    tl.y -= top_off * pix_h;
    br.y += bot_off * pix_h;

    x1 -= left_off * pct_w;
    x2 += right_off * pct_w;
    y1 -= top_off * pct_h;
    y2 += bot_off * pct_h;
  }

  blit_colored(tile->gl_binding(), x1, y2, x2, y1, tl.x, br.y, br.x, tl.y, color_tl, color_tr, color_bl, color_br);
}

void tile_blit_colored(Tilep tile, point tl, point br, color color_tl, color color_tr, color color_bl, color color_br)
{
  float x1 = tile->x1;
  float x2 = tile->x2;
  float y1 = tile->y1;
  float y2 = tile->y2;

  blit_colored(tile->gl_binding(), x1, y2, x2, y1, tl.x, br.y, br.x, tl.y, color_tl, color_tr, color_bl, color_br);
}

std::string tile_name(Tilep t)
{
  TRACE_AND_INDENT();
  return (t->name);
}

uint32_t tile_delay_ms(Tilep t) { return (t->delay_ms); }

uint8_t tile_is_moving(Tilep t) { return (t->is_moving); }

uint8_t tile_is_yyy5(Tilep t) { return (t->is_yyy5); }

uint8_t tile_is_yyy6(Tilep t) { return (t->is_yyy6); }

uint8_t tile_is_yyy7(Tilep t) { return (t->is_yyy7); }

uint8_t tile_is_yyy8(Tilep t) { return (t->is_yyy8); }

uint8_t tile_is_yyy9(Tilep t) { return (t->is_yyy9); }

uint8_t tile_is_invisible(Tilep t) { return (t->is_invisible); }

uint8_t tile_is_hp_25_percent(Tilep t) { return (t->is_hp_25_percent); }

uint8_t tile_is_hp_50_percent(Tilep t) { return (t->is_hp_50_percent); }

uint8_t tile_is_hp_75_percent(Tilep t) { return (t->is_hp_75_percent); }

uint8_t tile_is_hp_100_percent(Tilep t) { return (t->is_hp_100_percent); }

uint8_t tile_is_sleeping(Tilep t) { return (t->is_sleeping); }

uint8_t tile_is_open(Tilep t) { return (t->is_open); }

uint8_t tile_is_dead(Tilep t) { return (t->is_dead); }

uint8_t tile_is_end_of_anim(Tilep t) { return (t->is_end_of_anim); }

uint8_t tile_is_end_of_ascii_anim(Tilep t) { return (t->is_end_of_ascii_anim); }

uint8_t tile_is_dead_on_end_of_anim(Tilep t) { return (t->is_dead_on_end_of_anim); }

uint8_t tile_is_dead_on_end_of_ascii_anim(Tilep t) { return (t->is_dead_on_end_of_ascii_anim); }

uint8_t tile_is_alive_on_end_of_anim(Tilep t) { return (t->is_alive_on_end_of_anim); }

uint8_t tile_is_alive_on_end_of_ascii_anim(Tilep t) { return (t->is_alive_on_end_of_ascii_anim); }

uint8_t tile_is_resurrecting(Tilep t) { return (t->is_resurrecting); }

Tilep tile_first(Tilemap *tmap)
{
  if (unlikely(! tmap)) {
    return nullptr;
  }
  std::vector< Tilep > *tiles = &((*tmap));
  if (unlikely(! tiles)) {
    return nullptr;
  }
  if (unlikely(tiles->empty())) {
    return nullptr;
  }
  Tilep tile = (*tiles)[ 0 ];
  return tile_index_to_tile(tile->global_index);
}

Tilep tile_random(Tilemap *tmap)
{
  if (unlikely(! tmap)) {
    return nullptr;
  }
  std::vector< Tilep > *tiles = &((*tmap));
  if (unlikely(! tiles)) {
    return nullptr;
  }
  if (unlikely(tiles->empty())) {
    return nullptr;
  }

  int tries = 999999;
  while (tries--) {
    auto index = non_pcg_rand() % tiles->size();
    auto tile  = (*tiles)[ index ];

    //
    // Don't really want dead tiles when choosing a random start tile.
    //
    if (tile->is_dead) {
      continue;
    }
    if (unlikely(! tile)) {
      ERR("no tile at index #%d, max %d", (int) index, (int) tiles->size());
      return nullptr;
    }
    return tile_index_to_tile(tile->global_index);
  }

  DIE("failed to choose a random tile");
}

Tilep tile_n(Tilemap *tmap, int n)
{
  if (unlikely(! tmap)) {
    return nullptr;
  }
  std::vector< Tilep > *tiles = &((*tmap));
  if (unlikely(! tiles)) {
    return nullptr;
  }
  if (unlikely(tiles->empty())) {
    return nullptr;
  }
  auto index = n % tiles->size();
  auto tile  = (*tiles)[ index ];
  if (unlikely(! tile)) {
    ERR("no tile at index #%d, max %d", (int) index, (int) tiles->size());
    return nullptr;
  }
  return tile_index_to_tile(tile->global_index);
}

int tile_get_n(Tilemap *tmap, Tile *p)
{
  int n = 0;
  for (const auto t : *tmap) {
    if (t == p) {
      return n;
    }
    n++;
  }
  return -1;
}

Tilep tile_get_frame(Tilemap *tmap, uint32_t frame)
{
  for (const auto t : *tmap) {
    if (t->frame == frame) {
      return t;
    }
  }
  return nullptr;
}

Tilep tile_next(Tilemap *tmap, Tilep in)
{
  if (unlikely(! tmap)) {
    return 0;
  }
  std::vector< Tilep > *tiles = &((*tmap));
  if (unlikely(tiles->empty())) {
    return 0;
  }
  auto cursor = in->index;
  cursor++;
  if (cursor >= tiles->size()) {
    cursor = 0;
  }
  auto tile = ((*tiles)[ cursor ]);
  return tile_index_to_tile(tile->global_index);
}

int Tile::gl_binding(void) const
{
  if (g_render_black_and_white) {
    if (_gl_binding_black_and_white) {
    } else {
      return (_gl_binding);
    }
    return (_gl_binding_black_and_white);
  } else {
    return (_gl_binding);
  }
}

void Tile::set_gl_binding(int v) { _gl_binding = v; }

int Tile::gl_binding_black_and_white(void) const { return (_gl_binding_black_and_white); }

void Tile::set_gl_binding_black_and_white(int v) { _gl_binding_black_and_white = v; }

int Tile::gl_binding_mask(void) const { return (_gl_binding_mask); }

void Tile::set_gl_binding_mask(int v) { _gl_binding_mask = v; }

//
// Blits a whole tile. Y co-ords are inverted.
//
void tile_blit_outline(const Tilep &tile, const point tl, const point br, const color &c)
{
  float x1, x2, y1, y2;

  if (unlikely(! tile)) {
    return;
  }

  x1 = tile->x1;
  x2 = tile->x2;
  y1 = tile->y1;
  y2 = tile->y2;

  color outline = {10, 10, 10, 255};
  glcolor(outline);

  const float dx = game->config.one_pixel_width;
  const float dy = game->config.one_pixel_height;

  auto binding = tile->gl_binding_mask();
  blit(binding, x1, y2, x2, y1, tl.x - dx, br.y - dy, br.x - dx, tl.y - dy);
  blit(binding, x1, y2, x2, y1, tl.x + dx, br.y + dy, br.x + dx, tl.y + dy);
  blit(binding, x1, y2, x2, y1, tl.x - dx, br.y + dy, br.x - dx, tl.y + dy);
  blit(binding, x1, y2, x2, y1, tl.x + dx, br.y - dy, br.x + dx, tl.y - dy);
  blit(binding, x1, y2, x2, y1, tl.x + dx, br.y, br.x + dx, tl.y);
  blit(binding, x1, y2, x2, y1, tl.x - dx, br.y, br.x - dx, tl.y);
  blit(binding, x1, y2, x2, y1, tl.x, br.y + dy, br.x, tl.y + dy);
  blit(binding, x1, y2, x2, y1, tl.x, br.y - dy, br.x, tl.y - dy);

  glcolor(c);
  binding = tile->gl_binding();
  blit(binding, x1, y2, x2, y1, tl.x, br.y, br.x, tl.y);
}

void tile_blit_outline(const Tilep &tile, const point tl, const point br, const color &c, const color &outline)
{
  float x1, x2, y1, y2;

  if (unlikely(! tile)) {
    return;
  }

  x1 = tile->x1;
  x2 = tile->x2;
  y1 = tile->y1;
  y2 = tile->y2;

  glcolor(outline);

  const float dx = game->config.one_pixel_width;
  const float dy = game->config.one_pixel_height;

  auto binding = tile->gl_binding_mask();
  blit(binding, x1, y2, x2, y1, tl.x - dx, br.y - dy, br.x - dx, tl.y - dy);
  blit(binding, x1, y2, x2, y1, tl.x + dx, br.y + dy, br.x + dx, tl.y + dy);
  blit(binding, x1, y2, x2, y1, tl.x - dx, br.y + dy, br.x - dx, tl.y + dy);
  blit(binding, x1, y2, x2, y1, tl.x + dx, br.y - dy, br.x + dx, tl.y - dy);
  blit(binding, x1, y2, x2, y1, tl.x + dx, br.y, br.x + dx, tl.y);
  blit(binding, x1, y2, x2, y1, tl.x - dx, br.y, br.x - dx, tl.y);
  blit(binding, x1, y2, x2, y1, tl.x, br.y + dy, br.x, tl.y + dy);
  blit(binding, x1, y2, x2, y1, tl.x, br.y - dy, br.x, tl.y - dy);

  glcolor(c);
  binding = tile->gl_binding();
  blit(binding, x1, y2, x2, y1, tl.x, br.y, br.x, tl.y);
}

void tile_blit_outline(uint16_t index, const point tl, const point br, const color &c)
{
  tile_blit_outline(tile_index_to_tile(index), tl, br, c);
}

void tile_blit(const Tilep &tile, const point tl, const point br, const color &c)
{
  float x1, x2, y1, y2;

  if (unlikely(! tile)) {
    return;
  }

  x1 = tile->x1;
  x2 = tile->x2;
  y1 = tile->y1;
  y2 = tile->y2;

  auto binding = tile->gl_binding();
  glcolor(c);
  blit(binding, x1, y2, x2, y1, tl.x, br.y, br.x, tl.y);
}

//
// Blits a whole tile. Y co-ords are inverted.
//
static void tile_blit_outline_section(const Tilep &tile, const fpoint &tile_tl, const fpoint &tile_br, const point tl,
                                      const point br, float scale)
{
  float x1, x2, y1, y2;

  if (unlikely(! tile)) {
    return;
  }

  float tw = tile->x2 - tile->x1;
  float th = tile->y2 - tile->y1;

  x1 = tile->x1 + tile_tl.x * tw;
  x2 = tile->x1 + tile_br.x * tw;
  y1 = tile->y1 + tile_tl.y * th;
  y2 = tile->y1 + tile_br.y * th;

  glcolor(BLACK);

  if (scale < 0.2) {
    scale = 0.2;
  }
  const float dx = game->config.one_pixel_width * scale;
  const float dy = game->config.one_pixel_height * scale;

  blit(tile->gl_binding(), x1, y2, x2, y1, tl.x - dx, br.y - dy, br.x - dx, tl.y - dy);
  blit(tile->gl_binding(), x1, y2, x2, y1, tl.x + dx, br.y + dy, br.x + dx, tl.y + dy);
  blit(tile->gl_binding(), x1, y2, x2, y1, tl.x - dx, br.y + dy, br.x - dx, tl.y + dy);
  blit(tile->gl_binding(), x1, y2, x2, y1, tl.x + dx, br.y - dy, br.x + dx, tl.y - dy);
  blit(tile->gl_binding(), x1, y2, x2, y1, tl.x + dx, br.y, br.x + dx, tl.y);
  blit(tile->gl_binding(), x1, y2, x2, y1, tl.x - dx, br.y, br.x - dx, tl.y);
  blit(tile->gl_binding(), x1, y2, x2, y1, tl.x, br.y + dy, br.x, tl.y + dy);
  blit(tile->gl_binding(), x1, y2, x2, y1, tl.x, br.y - dy, br.x, tl.y - dy);

  glcolor(WHITE);
  blit(tile->gl_binding(), x1, y2, x2, y1, tl.x, br.y, br.x, tl.y);
}

void tile_blit(const Tilep &tile, const point tl, const point br)
{
  float x1, x2, y1, y2;

  //
  // Only some walls have deco tiles, so the pointer is left null for
  // those that do not.
  //
  if (unlikely(! tile)) {
    return;
  }

  x1 = tile->x1;
  x2 = tile->x2;
  y1 = tile->y1;
  y2 = tile->y2;

  blit(tile->gl_binding(), x1, y2, x2, y1, tl.x, br.y, br.x, tl.y);
}

void tile_blit(const Tilep &tile, const point tl, const point tr, const point bl, const point br)
{
  float x1, x2, y1, y2;

  //
  // Only some walls have deco tiles, so the pointer is left null for
  // those that do not.
  //
  if (unlikely(! tile)) {
    return;
  }

  x1 = tile->x1;
  x2 = tile->x2;
  y1 = tile->y1;
  y2 = tile->y2;

  blit(tile->gl_binding(), x1, y2, x2, y1, tl, tr, bl, br);
}

void tile_blit(uint16_t index, const point tl, const point br) { tile_blit(tile_index_to_tile(index), tl, br); }

void tile_blit_section(const Tilep &tile, const point tile_tl, const point tile_br, const point tl, const point br)
{
  float x1, x2, y1, y2;

  //
  // Only some walls have deco tiles, so the pointer is left null for
  // those that do not.
  //
  if (unlikely(! tile)) {
    return;
  }

  float tw = tile->x2 - tile->x1;
  float th = tile->y2 - tile->y1;

  x1 = tile->x1 + tile_tl.x * tw;
  x2 = tile->x1 + tile_br.x * tw;
  y1 = tile->y1 + tile_tl.y * th;
  y2 = tile->y1 + tile_br.y * th;

  blit(tile->gl_binding(), x1, y2, x2, y1, tl.x, br.y, br.x, tl.y);
}

void tile_blit_section(uint16_t index, const point tile_tl, const point tile_br, const point tl, const point br)
{
  tile_blit_section(tile_index_to_tile(index), tile_tl, tile_br, tl, br);
}

void tile_blit_section_colored(const Tilep &tile, const fpoint &tile_tl, const fpoint &tile_br, const point tl,
                               const point br, color color_bl, color color_br, color color_tl, color color_tr)
{
  float x1, x2, y1, y2;

  //
  // Only some walls have deco tiles, so the pointer is left null for
  // those that do not.
  //
  if (unlikely(! tile)) {
    return;
  }

  float tw = tile->x2 - tile->x1;
  float th = tile->y2 - tile->y1;

  x1 = tile->x1 + tile_tl.x * tw;
  x2 = tile->x1 + tile_br.x * tw;
  y1 = tile->y1 + tile_tl.y * th;
  y2 = tile->y1 + tile_br.y * th;

  blit_colored(tile->gl_binding(), x1, y2, x2, y1, tl.x, br.y, br.x, tl.y, color_bl, color_br, color_tl, color_tr);
}

void tile_blit_section_colored(uint16_t index, const fpoint &tile_tl, const fpoint &tile_br, const point tl,
                               const point br, color color_bl, color color_br, color color_tl, color color_tr)
{
  tile_blit_section_colored(tile_index_to_tile(index), tile_tl, tile_br, tl, br, color_bl, color_br, color_tl,
                            color_tr);
}

void tile_blit_outline_section_colored(const Tilep &tile, const fpoint &tile_tl, const fpoint &tile_br,
                                       const point tl, const point br, color color_bl, color color_br, color color_tl,
                                       color color_tr)
{
  tile_blit_outline_section(tile, tile_tl, tile_br, tl, br, 0.75);
}

void tile_blit_outline_section_colored(uint16_t index, const fpoint &tile_tl, const fpoint &tile_br, const point tl,
                                       const point br, color color_bl, color color_br, color color_tl, color color_tr)
{
  tile_blit_outline_section_colored(tile_index_to_tile(index), tile_tl, tile_br, tl, br, color_bl, color_br, color_tl,
                                    color_tr);
}

void tile_blit_outline_section_colored(const Tilep &tile, const fpoint &tile_tl, const fpoint &tile_br,
                                       const point tl, const point br, color color_bl, color color_br, color color_tl,
                                       color color_tr, float scale)
{
  tile_blit_outline_section(tile, tile_tl, tile_br, tl, br, scale);
}

void tile_blit_outline_section_colored(uint16_t index, const fpoint &tile_tl, const fpoint &tile_br, const point tl,
                                       const point br, color color_bl, color color_br, color color_tl, color color_tr,
                                       float scale)
{
  tile_blit_outline_section_colored(tile_index_to_tile(index), tile_tl, tile_br, tl, br, color_bl, color_br, color_tl,
                                    color_tr, scale);
}

void tile_blit_frozen(const Tilep &tile, const point tl, const point br)
{
  static Tilep tile_ice;
  if (! tile_ice) {
    tile_ice = tile_find_mand("ice");
  }

  auto  width  = tl.x > br.x ? (tl.x - br.y) : (br.x - tl.x);
  auto  height = br.y - tl.y;
  float tw     = ((float) width) / ((float) game->config.game_pix_width);
  float th     = ((float) height) / ((float) game->config.game_pix_height);

  blit_fbo_push(FBO_SPRITE);
  {
    glcolor(WHITE);
    blit_init();
    {
      //
      // Blit a solid ice texture
      //
      glBlendFunc(GL_ZERO, GL_ONE);
      tile_blit(tile_ice, point(0, 0), point(width, height));

      //
      // Now invert the mask for the thing and merge with the ice
      //
      glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ZERO);
      {
        glLogicOp(GL_COPY_INVERTED);
        glEnable(GL_COLOR_LOGIC_OP);
        {
          blit(tile->gl_binding_mask(), tile->x1, tile->y1, tile->x2, tile->y2, 0, 0, width, height);
        }
        glLogicOp(GL_COPY);
        glDisable(GL_COLOR_LOGIC_OP);
      }
    }
    blit_flush();
  }
  blit_fbo_pop();

  //
  // Blit the final combined texture
  //
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  blit_init();
  {
    blit(fbo_tex_id[ FBO_SPRITE ], 0, 1, tw, 1.0 - th, tl.x, tl.y, br.x, br.y);
  }
  blit_flush();

  //
  // Restore normal blending
  //
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
