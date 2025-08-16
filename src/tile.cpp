//
// Copyright goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_pixel.hpp"
#include "my_ptrcheck.hpp"
#include "my_string.hpp"
#include "my_template.hpp"
#include "my_tex.hpp"

std::unordered_map< std::string, class Tile * > all_tiles;
std::vector< class Tile * >                     all_tiles_array;

static uint8_t tile_init_done;

#define ENABLE_TILE_BOUNDS

Tile::Tile(void) { newptr(MTYPE_TILE, this, "Tile"); }

Tile::~Tile(void) { oldptr(MTYPE_TILE, this); }

Tilep tile_index_to_tile(uint16_t i)
{
  if (unlikely(! i)) {
    return nullptr;
  }
  return all_tiles_array[ i - 1 ];
}

uint8_t tile_init(void);
uint8_t tile_init(void)
{
  TRACE_NO_INDENT();
  tile_init_done = true;

  return true;
}

void tile_fini(void)
{
  TRACE_NO_INDENT();
  if (tile_init_done) {
    tile_init_done = false;
  }

  for (auto &t : all_tiles) {
    IF_DEBUG3 { verify(MTYPE_TILE, t.second); }
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
  if (g_opt_gfx_monochrome) {
    set_gl_binding(tile->gl_binding_monochrome());
  }
  set_gl_binding_monochrome(tile->gl_binding_monochrome());
  set_gl_binding_mask(tile->gl_binding_mask());

  tex            = tile->tex;
  tex_monochrome = tile->tex_monochrome;
  tex_mask       = tile->tex_mask;

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
  if (! result.second) {
    ERR("Tile copy insert name [%s] failed", name.c_str());
  }
  all_tiles_array.push_back(this);
}

void tile_load_arr(std::string file, std::string name, uint32_t width, uint32_t height, uint32_t nargs,
                   const char *arr[])
{
  TRACE_NO_INDENT();
  Texp tex;
  Texp tex_monochrome;
  Texp tex_mask;
  tex_load(&tex, &tex_monochrome, &tex_mask, file, name, GL_NEAREST);

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
      if (! result.second) {
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
      if (g_opt_gfx_monochrome) {
        t->set_gl_binding(tex_get_gl_binding(tex_monochrome));
      }

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
  TRACE_NO_INDENT();
  Texp tex;
  Texp tex_monochrome;
  Texp tex_mask;
  tex_load(&tex, &tex_monochrome, &tex_mask, file, name, GL_NEAREST);

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
      if (! result.second) {
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
      if (g_opt_gfx_monochrome) {
        t->set_gl_binding(tex_get_gl_binding(tex_monochrome));
      }

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
  TRACE_NO_INDENT();
  Texp tex;
  Texp tex_monochrome;
  Texp tex_mask;

  tex_load(&tex, &tex_monochrome, &tex_mask, file, name, gl_mode);

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
      if (! result.second) {
        ERR("Tile insert name [%s] failed", name.c_str());
      }

      //
      // Global array of all tiles
      //
      all_tiles_array.push_back(t);
      t->global_index = all_tiles_array.size();

      t->name           = name;
      t->index          = idx - 1;
      t->pix_width      = width;
      t->pix_height     = height;
      t->tex            = tex;
      t->tex_monochrome = tex_monochrome;

      t->tex_mask = tex_mask;

      t->set_gl_binding(tex_get_gl_binding(t->tex));
      if (g_opt_gfx_monochrome) {
        t->set_gl_binding(tex_get_gl_binding(tex_monochrome));
      }
      t->set_gl_binding_monochrome(tex_get_gl_binding(t->tex_monochrome));
      t->set_gl_binding_mask(tex_get_gl_binding(t->tex_mask));

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
  TRACE_NO_INDENT();
  Texp tex;
  Texp tex_monochrome;
  Texp tex_mask;

  tex_load(&tex, &tex_monochrome, &tex_mask, file, name, gl_mode);

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
      if (! result.second) {
        ERR("Tile insert name [%s] failed", name.c_str());
      }

      //
      // Global array of all tiles
      //
      all_tiles_array.push_back(t);
      t->global_index = all_tiles_array.size();

      t->name           = name;
      t->index          = idx - 1;
      t->pix_width      = width;
      t->pix_height     = height;
      t->tex            = tex;
      t->tex_monochrome = tex_monochrome;
      t->tex_mask       = tex_mask;
      t->set_gl_binding(tex_get_gl_binding(t->tex));
      if (g_opt_gfx_monochrome) {
        t->set_gl_binding(tex_get_gl_binding(tex_monochrome));
      }
      t->set_gl_binding_monochrome(tex_get_gl_binding(t->tex_monochrome));
      t->set_gl_binding_mask(tex_get_gl_binding(t->tex_mask));

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
  TRACE_NO_INDENT();
  if (name == "") {
    return nullptr;
  }

  auto result = all_tiles.find(name);
  if (result == all_tiles.end()) {
    return nullptr;
  }

  return (result->second);
}

Tilep tile_find_mand(std::string name)
{
  TRACE_NO_INDENT();
  if (name == "") {
    ERR("No tile name given");
    return nullptr;
  }

  auto result = all_tiles.find(name);
  if (result == all_tiles.end()) {
    DIE("Tile name %s not found", name.c_str());
    return nullptr;
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
  TRACE_NO_INDENT();
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
    return nullptr;
  }

  *t++ = '\0';
  *s += (t - name);

  auto result = all_tiles.find(name);
  if (result == all_tiles.end()) {
    ERR("Unknown tile [%s]", name);
    return nullptr;
  }

  return (result->second);
}

Tilep string2tile(std::string &s, int *len)
{
  TRACE_NO_INDENT();
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
  TRACE_NO_INDENT();
  auto v = wstring_to_string(s);
  return (string2tile(v, len));
}
