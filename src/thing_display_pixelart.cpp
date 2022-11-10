//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_color_defs.hpp"
#include "my_font.hpp"
#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_random.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"
#include "my_ui.hpp"

void Thing::blit_non_player_owned_shadow(const Tpp &tpp, const Tilep &tile, const point blit_tl, const point blit_br)
{
  TRACE_NO_INDENT();
  IF_DEBUG2 { return; }

  if (g_render_black_and_white) {
    return;
  }

  if (! level->player) {
    return;
  }

  if (is_foilage()) {
    fpoint p  = level->player->interpolated_at_get();
    fpoint o  = interpolated_at_get();
    fpoint d  = o - p;
    float  dx = d.x;
    float  dy = d.y;

    //
    // Don't have shadows all the way across the level
    //
    float max_shadow = 10;
    if (dx < -max_shadow) {
      dx = -max_shadow;
    } else if (dx > max_shadow) {
      dx = max_shadow;
    }
    if (dy < -max_shadow) {
      dy = -max_shadow;
    } else if (dy > max_shadow) {
      dy = max_shadow;
    }

    color c = BLACK;
    glcolor(c);

    {
      point shadow_bl(blit_tl.x, blit_br.y);
      point shadow_br(blit_br.x, blit_br.y);
      point shadow_tl = shadow_bl;
      point shadow_tr = shadow_br;

      shadow_tl.x += ((float) TILE_WIDTH) * dx;
      shadow_tl.y += ((float) TILE_WIDTH) * dy;
      shadow_tr.x += ((float) TILE_WIDTH) * dx;
      shadow_tr.y += ((float) TILE_WIDTH) * dy;

      tile_blit(tile, shadow_bl, shadow_br, shadow_tl, shadow_tr);
    }

    if (dx < 0) {
      point shadow_tr(blit_br.x, blit_tl.y);
      point shadow_br(blit_br.x, blit_br.y);
      point shadow_tl = shadow_tr;
      point shadow_bl = shadow_br;

      shadow_tl.x += ((float) TILE_WIDTH) * (dx - 1.5);
      shadow_tl.y += ((float) TILE_WIDTH) * dy;
      shadow_bl.x += ((float) TILE_WIDTH) * (dx - 1.5);
      shadow_bl.y += ((float) TILE_WIDTH) * dy;

      tile_blit(tile, shadow_bl, shadow_br, shadow_tl, shadow_tr);
    }

    if (dx > 0) {
      point shadow_tl(blit_tl.x, blit_tl.y);
      point shadow_bl(blit_tl.x, blit_br.y);
      point shadow_tr = shadow_tl;
      point shadow_br = shadow_bl;

      shadow_tr.x += ((float) TILE_WIDTH) * (dx + 1.5);
      shadow_tr.y += ((float) TILE_WIDTH) * dy;
      shadow_br.x += ((float) TILE_WIDTH) * (dx + 1.5);
      shadow_br.y += ((float) TILE_WIDTH) * dy;

      tile_blit(tile, shadow_bl, shadow_br, shadow_tl, shadow_tr);
    }

    glcolor(WHITE);
  } else {
    point shadow_bl(blit_tl.x, blit_br.y);
    point shadow_br(blit_br.x, blit_br.y);
    point shadow_tl = shadow_bl;
    point shadow_tr = shadow_br;

    float dx = 1.0;
    float dy = 1.0;
    if (level->player) {
      if (immediate_owner_id() == level->player->id) {
        // use default shadow for carried items
      } else if (this != level->player) {
        fpoint      p = level->player->interpolated_at_get();
        fpoint      o = interpolated_at_get();
        fpoint      d = o - p;
        const float D = 16.0;
        dx            = d.x / D;
        dy            = d.y / D;

        if (distance(o, p) > TILES_VISIBLE_ACROSS / 2) {
          return;
        }
      }
    } else {
      // use default shadow
    }

    float n = 0.0;
    if (dy < 0) {
      dy = std::min(-n, dy);
    } else {
      dy = std::max(n, dy);
    }

    //
    // Max length of shadow
    //
    float m = 3;
    if (dx < 0) {
      dx = std::max(-m, dx);
    } else {
      dx = std::min(m, dx);
    }
    if (dy < 0) {
      dy = std::max(-m, dy);
    } else {
      dy = std::min(m, dy);
    }

    if (unlikely(tpp->gfx_pixelart_shadow_very_short())) {
      shadow_tl.x += ((float) TILE_WIDTH) * dx * 4;
      shadow_tr.x += ((float) TILE_WIDTH) * dx * 4;
      shadow_tl.y += ((float) TILE_WIDTH) * dy * 4;
      shadow_tr.y += ((float) TILE_WIDTH) * dy * 4;
    } else if (unlikely(tpp->gfx_pixelart_shadow_short())) {
      shadow_tl.x += ((float) TILE_WIDTH) * dx * 10;
      shadow_tr.x += ((float) TILE_WIDTH) * dx * 10;
      shadow_tl.y += ((float) TILE_WIDTH) * dy * 10;
      shadow_tr.y += ((float) TILE_WIDTH) * dy * 10;
    } else { /* long shadow */
      shadow_tl.x += ((float) TILE_WIDTH) * dx * 20;
      shadow_tr.x += ((float) TILE_WIDTH) * dx * 20;
      shadow_tl.y += ((float) TILE_WIDTH) * dy * 20;
      shadow_tr.y += ((float) TILE_WIDTH) * dy * 20;
    }

    if (shadow_tl.x > shadow_tr.x) {
      std::swap(shadow_tl, shadow_tr);
    }

    float bounce = bounce_curr();
    float tileh  = game->config.tile_pix_height;
    float bh     = (tileh / TILE_HEIGHT) * (int) (bounce * TILE_HEIGHT);

    float fadeup = fadeup_curr();
    if (fadeup < 0) {
      return;
    }

    bh += fadeup;

    shadow_tl.y += bh;
    shadow_tr.y += bh;
    shadow_bl.y += bh;
    shadow_br.y += bh;

    shadow_tl.x -= bh;
    shadow_tr.x -= bh;
    shadow_bl.x -= bh;
    shadow_br.x -= bh;

    color c = BLACK;
    if (likely(! tpp->gfx_pixelart_shadow_solid())) {
      c.a = 150;
    }

    glcolor(c);
    tile_blit(tile, shadow_bl, shadow_br, shadow_tl, shadow_tr);
    glcolor(WHITE);
  }
}

void Thing::blit_player_owned_shadow(const Tpp &tpp, const Tilep &tile, const point blit_tl, const point blit_br)
{
  TRACE_NO_INDENT();
  IF_DEBUG2 { return; }

  if (g_render_black_and_white) {
    return;
  }

  point shadow_tl = blit_tl;
  point shadow_br = blit_br;

  float dx = game->config.one_pixel_width;
  float dy = game->config.one_pixel_width;

  color c = BLACK;
  if (likely(! tpp->gfx_pixelart_shadow_solid())) {
    c.a = 150;
  }

  dx *= -4;
  dy *= -4;

  glcolor(c);

  shadow_tl.x += dx;
  shadow_tl.y += dy;
  shadow_br.x += dx;
  shadow_br.y += dy;

  tile_blit(tile, shadow_tl, shadow_br);

  glcolor(WHITE);
}

void Thing::blit_shadow(const Tpp &tpp, const Tilep &tile, const point blit_tl, const point blit_br)
{
  TRACE_NO_INDENT();
  IF_DEBUG2 { return; }

  if (g_render_black_and_white) {
    return;
  }

  if (! gfx_pixelart_shadow()) {
    return;
  }

  if (! level->player) {
    blit_non_player_owned_shadow(tpp, tile, blit_tl, blit_br);
    return;
  }

  if (is_player() || (immediate_owner_id() == level->player->id)) {
    blit_player_owned_shadow(tpp, tile, blit_tl, blit_br);
  } else {
    blit_non_player_owned_shadow(tpp, tile, blit_tl, blit_br);
  }
}

static int blit_msg_strlen(std::string const &text)
{
  TRACE_NO_INDENT();

  auto text_iter = text.begin();
  int  x         = 0;

  while (text_iter != text.end()) {
    auto c = *text_iter;
    text_iter++;

    if (c == '%') {
      if (text_iter != text.end()) {
        if (*text_iter == '%') {
          text_iter++;
        }
      }

      if (std::string(text_iter, text_iter + 3) == "fg=") {
        text_iter += 3;
        auto tmp = std::string(text_iter, text.end());

        int len = 0;
        (void) string2color(tmp, &len);
        text_iter += len + 1;
        continue;
      }
      if (std::string(text_iter, text_iter + 3) == "bg=") {
        text_iter += 3;
        auto tmp = std::string(text_iter, text.end());

        int len = 0;
        (void) string2color(tmp, &len);
        text_iter += len + 1;

        continue;
      }
      if (std::string(text_iter, text_iter + 3) == "tp=") {
        text_iter += 3;
        auto tmp = std::string(text_iter, text.end());

        int len = 0;
        (void) string2tp(tmp, &len);
        text_iter += len + 1;

        continue;
      }
      if (std::string(text_iter, text_iter + 4) == "tex=") {
        text_iter += 4;
        continue;
      }
      if (std::string(text_iter, text_iter + 5) == "tile=") {
        text_iter += 5;
        auto tmp = std::string(text_iter, text.end());

        int len = 0;
        (void) string2tile(tmp, &len);
        text_iter += len + 1;
        continue;
      }
    }

    x++;
  }

  return x;
}

void Thing::blit_text(std::string const &text, color fg, point oblit_tl, point oblit_br)
{
  TRACE_NO_INDENT();

  Tilep tile;
  auto  text_iter = text.begin();
  fg.a            = blit_fg_color.a;

  tile = nullptr;

  int l = blit_msg_strlen(text);

  point blit_tl, blit_br;
  blit_tl.x = ((oblit_br.x + oblit_tl.x) / 2) - (UI_FONT_SMALL_WIDTH * (l / 2));
  blit_br.x = blit_tl.x + UI_FONT_SMALL_WIDTH;

  blit_tl.y = oblit_tl.y;
  blit_br.y = oblit_tl.y + UI_FONT_SMALL_HEIGHT;

  while (text_iter != text.end()) {
    auto c = *text_iter;
    text_iter++;

    if (unlikely(c == L'%')) {
      if (std::string(text_iter, text_iter + 3) == "fg=") {
        text_iter += 3;
        auto tmp = std::string(text_iter, text.end());
        int  len = 0;
        fg       = string2color(tmp, &len);
        fg.a     = blit_fg_color.a;
        text_iter += len + 1;
        continue;
      }
      if (std::string(text_iter, text_iter + 3) == "tp=") {
        text_iter += 3;
        auto tmp = std::string(text_iter, text.end());

        int  len = 0;
        auto tp  = string2tp(tmp, &len);
        text_iter += len;

        tile = tp_first_tile(tp);
        continue;
      }
      if (std::string(text_iter, text_iter + 4) == "tex=") {
        text_iter += 4;
        continue;
      }
      if (std::string(text_iter, text_iter + 5) == "tile=") {
        text_iter += 5;
        auto tmp = std::string(text_iter, text.end());
        int  len = 0;
        tile     = string2tile(tmp, &len);
        text_iter += len;
        continue;
      }
      continue;
    }

    if (unlikely(! tile)) {
      tile = font_pixelart_small->unicode_to_tile(c);
    }

    if (tile) {
      tile_blit(tile, blit_tl, blit_br, fg);
    }

    tile = nullptr;
    blit_tl.x += UI_FONT_SMALL_WIDTH;
    blit_br.x += UI_FONT_SMALL_WIDTH;
  }
  glcolor(WHITE);
}

bool Thing::coords_get(point &blit_tl, point &blit_br, point &pre_effect_blit_tl, point &pre_effect_blit_br,
                       Tilep &tile, bool reflection)
{
  TRACE_NO_INDENT();

  fpoint at = interpolated_at_get();

  //
  // We render these offset form their owner, so if dead, then it is
  // likely they also have no owner as the swing has ended.
  //
  auto tpp   = tp();
  auto blit  = true;
  auto o_top = top_owner();
  auto o_imm = immediate_owner();

  if (unlikely(is_changing_level)) {
    blit = false;
  } else if (unlikely(is_hidden)) {
    blit = false;
  } else if (unlikely(tpp->gfx_pixelart_attack_anim() || tpp->gfx_pixelart_equip_carry_anim())) {
    //
    // Hide weapons that have swung
    //
    if (is_dead) {
      blit = false;
    }
  } else if (is_cursor() || is_cursor_path() || is_the_grid) {
    blit = true;
  }

  float tilew = game->config.tile_pix_width;
  float tileh = game->config.tile_pix_height;
  float X     = at.x;
  float Y     = at.y;

  blit_tl.x = ((float) X) * tilew;
  blit_tl.y = ((float) Y) * tileh;
  blit_br.x = blit_tl.x + tilew;
  blit_br.y = blit_tl.y + tileh;

  //
  // Some things (like messages) have no tiles and so use the default.
  //
  // float is needed here for 24x24 tiles
  //
  float tile_pix_width  = TILE_WIDTH;
  float tile_pix_height = TILE_HEIGHT;

  if (likely(! is_no_tile())) {
    tile = tile_index_to_tile(tile_curr);
    if (unlikely(! tile)) {
      err("Has no tile, index %d", tile_curr);
      blit = false;
    } else {
      tile_pix_width  = tile->pix_width;
      tile_pix_height = tile->pix_height;
    }
  } else {
    tile = {};
  }

  //
  // Scale up tiles that are larger to the same pix scale.
  //
  if (unlikely((tile_pix_width != TILE_WIDTH) || (tile_pix_height != TILE_HEIGHT))) {
    auto xtiles = tile_pix_width / TILE_WIDTH;
    blit_tl.x -= ((xtiles - 1) * tilew) / 2;
    blit_br.x += ((xtiles - 1) * tilew) / 2;

    auto ytiles = tile_pix_height / TILE_HEIGHT;
    blit_tl.y -= ((ytiles - 1) * tileh) / 2;
    blit_br.y += ((ytiles - 1) * tileh) / 2;
  }

  //
  // Put larger tiles on the same y base as small ones.
  //
  if (unlikely(tpp->gfx_pixelart_oversized_and_on_floor())) {
    float y_offset = (((tile_pix_height - TILE_HEIGHT) / TILE_HEIGHT) * tileh) / 2.0;
    blit_tl.y -= y_offset;
    blit_br.y -= y_offset;
  }

  //
  // Flipping
  //
  auto falling = is_falling || (o_top && o_top->is_falling);

  if (likely(! falling)) {
    if (unlikely(tpp->gfx_pixelart_animated_can_hflip())) {
      if (ts_flip_start_get()) {
        //
        // Slow flip
        //
        auto diff       = time_ms_cached() - ts_flip_start_get();
        ts_t flip_time  = game->current_move_speed;
        ts_t flip_steps = flip_time;

        if (diff > flip_time) {
          ts_flip_start_set(0);
          is_facing_left = ! is_facing_left;
          if (is_dir_left() || is_dir_tl() || is_dir_bl()) {
            std::swap(blit_tl.x, blit_br.x);
          }
        } else {
          if (is_dir_right() || is_dir_tr() || is_dir_br()) {
            std::swap(blit_tl.x, blit_br.x);
          }
          float w   = blit_br.x - blit_tl.x;
          float dw  = w / flip_steps;
          float tlx = blit_tl.x;
          float brx = blit_br.x;

          blit_tl.x = tlx + dw * diff;
          blit_br.x = brx - dw * diff;
          std::swap(blit_tl.x, blit_br.x);
        }
      } else {
        //
        // Fast flip
        //
        if (is_dir_right() || is_dir_tr() || is_dir_br()) {
          std::swap(blit_tl.x, blit_br.x);
        }
      }
    }

    if (unlikely(tpp->gfx_pixelart_animated_can_vflip())) {
      if (is_dir_down() || is_dir_br() || is_dir_bl()) {
        std::swap(blit_tl.y, blit_br.y);
      }
    }
  }

  //
  // For second rings provide a small offset of a few pixels so we can see both.
  //
  if (unlikely(is_ring2)) {
    if (is_dir_left() || is_dir_tl() || is_dir_bl()) {
      blit_tl.x += 4;
      blit_br.x += 4;
    } else {
      blit_tl.x -= 4;
      blit_br.x -= 4;
    }
  }

  //
  // Set this pre-bounce as the cursor uses it.
  //
  last_blit_at = ((blit_tl + blit_br) / (short) 2);

  //
  // Bouncing. But not in water, that just looks odd.
  //
  if (unlikely((! (is_in_water || is_in_lava)) && (is_bouncing || (o_top && o_top->is_bouncing)))) {
    float bounce;
    if (o_top) {
      bounce = o_top->bounce_curr();
    } else {
      bounce = bounce_curr();
    }

    float bounce_height = (tileh / TILE_HEIGHT) * (int) (bounce * TILE_HEIGHT);
    if (reflection) {
      blit_tl.y += bounce_height;
      blit_br.y += bounce_height;
    } else {
      blit_tl.y -= bounce_height;
      blit_br.y -= bounce_height;
    }
  }

  //
  // Waaaaaaah
  //
  if (unlikely(falling)) {
    float fall = 0;

    fall = fall_curr();
    update_interpolated_position();
    if (o_top) {
      fall = o_top->fall_curr();
    }

    auto s = ((blit_br.y - blit_tl.y - 1) / 2) * fall;
    blit_tl.x += s;
    blit_br.x -= s;
    blit_tl.y += s;
    blit_br.y -= s;

    blit_tl.y += fall * 40;
    blit_br.y += fall * 40;
  }

  //
  // Prevent items inside bags/chests being seen.
  //
  if (unlikely(o_imm && o_imm->is_bag_item_container())) {
    blit = false;
  }

  //
  // Lunge to attack.
  //
  float lunge;
  if (o_imm) {
    lunge = o_imm->lunge_curr();
  } else {
    lunge = lunge_curr();
  }
  if (unlikely(lunge > 0.0)) {
    point delta;
    if (o_imm) {
      delta = o_imm->lunge_to_get() - o_imm->curr_at;
    } else {
      delta = lunge_to_get() - curr_at;
    }
    float dx = -delta.x * lunge;
    float dy = -delta.y * lunge;
    dx       = -delta.x * lunge * TILE_WIDTH;
    dy       = delta.y * lunge * TILE_HEIGHT;
    blit_tl.x -= dx;
    blit_br.x -= dx;
    blit_tl.y += dy;
    blit_br.y += dy;
  }

  //
  // Fading. Used for text.
  //
  float fadeup = fadeup_curr();
  if (likely(fadeup == 0)) {
    //
    // Not fading.
    //
  } else if (fadeup < 0) {
    blit = false;
  } else {
    if (reflection) {
      blit_tl.y += fadeup;
      blit_br.y += fadeup;
    } else {
      blit_tl.y -= fadeup;
      blit_br.y -= fadeup;
    }
  }

  return blit;
}

bool Thing::map_offset_coords_get(point &blit_tl, point &blit_br, Tilep &tile, bool reflection)
{
  TRACE_NO_INDENT();

  point pre_effect_blit_tl;
  point pre_effect_blit_br;

  auto blit = coords_get(blit_tl, blit_br, pre_effect_blit_tl, pre_effect_blit_br, tile, reflection);

  float dx = level->pixel_map_at.x;
  float dy = level->pixel_map_at.y;
  blit_tl.x -= dx;
  blit_tl.y -= dy;
  blit_br.x -= dx;
  blit_br.y -= dy;

  if (likely(! reflection)) {
    last_blit_tl = blit_tl;
    last_blit_br = blit_br;
    pre_effect_blit_tl.x -= dx;
    pre_effect_blit_tl.y -= dy;
    pre_effect_blit_br.x -= dx;
    pre_effect_blit_br.y -= dy;
  }

  return blit;
}

uint8_t Thing::blit_begin_submerged(void)
{
  TRACE_NO_INDENT();

  auto submerged = submerged_offset_get();
  if (submerged) {
    blit_flush();
    auto waterline = last_blit_br.y;
    auto owner     = immediate_owner();
    if (owner) {
      waterline = owner->last_blit_br.y;
    }
    if (waterline < game->config.game_pix_height) {
      glScissor(0, game->config.game_pix_height - waterline, game->config.game_pix_width,
                game->config.game_pix_height);
      GL_ERROR_CHECK();
    }
    glEnable(GL_SCISSOR_TEST);
    glTranslatef(0, submerged, 0);
    blit_init();
  }
  return submerged;
}

void Thing::blit_end_submerged(uint8_t submerged)
{
  TRACE_NO_INDENT();

  blit_flush();
  glTranslatef(0, -submerged, 0);
  glDisable(GL_SCISSOR_TEST);

  blit_init();
}

uint8_t Thing::blit_begin_reflection_submerged(void)
{
  TRACE_NO_INDENT();

  if (! gfx_pixelart_reflection()) {
    return false;
  }

  auto submerged = submerged_offset_get();
  if (submerged) {
    blit_flush();
    auto waterline = last_blit_br.y;
    auto owner     = immediate_owner();
    if (owner) {
      waterline = owner->last_blit_br.y;
    }
    if (waterline < game->config.game_pix_height) {
      glScissor(0, 0, game->config.game_pix_width, game->config.game_pix_height - waterline);
      GL_ERROR_CHECK();
    }
    glEnable(GL_SCISSOR_TEST);
    glTranslatef(0, -submerged, 0);
    blit_init();
  }
  return submerged;
}

void Thing::blit_end_reflection_submerged(uint8_t submerged)
{
  TRACE_NO_INDENT();

  if (! gfx_pixelart_reflection()) {
    return;
  }

  blit_flush();
  glTranslatef(0, submerged, 0);
  glDisable(GL_SCISSOR_TEST);
  blit_init();
}

void Thing::blit_internal(int fbo, point &blit_tl, point &blit_br, const Tilep tile, color c, bool reflection)
{
  TRACE_NO_INDENT();

  auto tpp = tp();

  //
  // Displayed as a particles
  //
  if (is_jumping) {
    return;
  }

  if (! g_render_black_and_white) {
    if (unlikely(tpp->gfx_pixelart_shadow_very_short() || tpp->gfx_pixelart_shadow_short() ||
                 tpp->gfx_pixelart_shadow_long())) {
      if (auto submerged = blit_begin_submerged()) {

        blit_shadow(tpp, tile, blit_tl, blit_br);
        blit_end_submerged(submerged);
      } else {
        blit_shadow(tpp, tile, blit_tl, blit_br);
      }
    }
  }

  if (unlikely(is_msg())) {
    blit_text(msg_get(), WHITE, blit_tl, blit_br);
  }

  //
  // Show a health bar over the thing?
  //
  auto h = health();
  auto m = health_max();

  auto lit = (fbo == FBO_PIXELART_FULLMAP) || level->is_currently_pixelart_raycast_lit_no_check(curr_at.x, curr_at.y);

  if (tile && ! tile->is_invisible && ! is_dead && ! reflection && lit &&
      (gfx_pixelart_health_bar_shown() || (gfx_pixelart_health_bar_autohide() && (h < m)))) {

    if (is_sleeping && gfx_pixelart_health_bar_only_when_awake()) {
      //
      // Only show health when awake
      //
    } else {
      int h_step = (1.0 - (((float) h) / ((float) m))) * GAME_MONST_HEALTH_BAR_STEPS;
      h_step     = std::min(h_step, GAME_MONST_HEALTH_BAR_STEPS);
      h_step     = std::max(h_step, 1);
      int y      = blit_br.y - ((1.0 - tile->py1 /* pct */) * tile->pix_height) - 4;
      int x      = (blit_tl.x + blit_br.x) / 2;

      //
      // Add health bar
      //
      {
        auto index = 0;
        if (maybe_infop()->monst_state) {
          if (is_sleeping) {
            //
            // If asleep and we are allowed to show the Zzz animation. Not for gargoyles when asleep.
            //
            if (gfx_pixelart_show_asleep_anim()) {
              index = 1;
            }
          }
        }

        //
        // Index 0 is the normal healthbar
        // Index 1 is the healthbar + Zzz animation
        //
        auto tile = get(game->tile_cache_health, index, h_step);
        if (unlikely(! tile)) {
          //
          // Sleeping?
          //
          std::string s = "health" + std::to_string(h_step);
          if (index) {
            s = "health_sleeping" + std::to_string(h_step);
          }
          tile = tile_find_mand(s);
          set(game->tile_cache_health, index, h_step, tile);
        }

        auto health_bar_width = TILE_WIDTH;

        switch (thing_size()) {
          case THING_SIZE_GARGANTUAN: health_bar_width = TILE_WIDTH * 2; break;
          case THING_SIZE_GIANT: health_bar_width = TILE_WIDTH * 1.5; break;
          case THING_SIZE_LARGE: health_bar_width = TILE_WIDTH; break;
          case THING_SIZE_NORMAL: health_bar_width = TILE_WIDTH; break;
          case THING_SIZE_SMALL: health_bar_width = TILE_WIDTH; break;
          case THING_SIZE_TINY: health_bar_width = TILE_WIDTH / 2; break;
        }

        tile_blit(tile, point(x - health_bar_width / 2, y - TILE_HEIGHT), point(x + health_bar_width / 2, y));
      }
    }
  }

  //
  // Try to look like we are trapped in ice
  //
  if (! is_block_of_ice()) {
    if (level->is_block_of_ice(curr_at)) {
      c = CYAN;
    }
  }

  //
  // If on fire, flicker the thing color
  //
  if (unlikely(is_on_fire())) {
    static uint32_t ts;
    static color    fire_color;
    if (time_have_x_tenths_passed_since(2, ts)) {
      ts = time_ms_cached();
      if (non_pcg_random_range(0, 100) < 20) {
        fire_color = YELLOW;
      } else if (non_pcg_random_range(0, 100) < 50) {
        fire_color = ORANGE;
      } else {
        fire_color = RED;
      }
    }
    c = fire_color;
  }

  //
  // Means it has been lit, but light does fade
  //
  uint8_t fade = level->is_currently_pixelart_raycast_lit(curr_at.x, curr_at.y);
  if (fbo == FBO_PIXELART_FULLMAP) {
    c.a = 255;
  } else if (light_dist_get()) {
    c.a = fade;
  }

  IF_DEBUG2 { c.a = 255; }

  //
  // Dim non currently lit areas
  //
  if (has_light) {
    auto lit = get(level->can_see_ever.can_see, curr_at.x, curr_at.y);
    if (! lit) {
      c.r /= 2;
      c.g /= 2;
      c.b /= 2;
    }
  } else {
    auto lit = get(level->can_see_currently.can_see, curr_at.x, curr_at.y);
    if (! lit) {
      c.r /= 2;
      c.g /= 2;
      c.b /= 2;
    }
  }

  glcolor(c);

  auto wobble = update_wobble();
  if (wobble != 0.0) {
    auto mid = (blit_tl + blit_br) / (short) 2;
    blit_flush();
    blit_init();
    glPushMatrix();
    glTranslatef(mid.x, mid.y, 0);
    glRotatef(wobble, 0.0f, 0.0f, 1.0f);
    glTranslatef(-mid.x, -mid.y, 0);
  }

  bool outline = tpp->gfx_pixelart_show_outlined();

  if (! g_render_black_and_white) {
    if (reflection) {
      if (auto submerged = blit_begin_reflection_submerged()) {
        tile_blit(tile, blit_tl, blit_br);
        blit_end_reflection_submerged(submerged);
      } else {
        if (tile && tile_get_height(tile) != TILE_HEIGHT) {
          if (tpp->gfx_pixelart_oversized_and_on_floor()) {
            //
            // e.g. kraken
            //
          } else if (tpp->gfx_pixelart_oversized_and_centered()) {
            //
            // e.g. dungeon cleaner
            //
          } else if (immediate_owner()) {
            //
            // e.g. sword
            //
          } else {
            blit_br.y += TILE_HEIGHT;
            blit_tl.y += TILE_HEIGHT;
          }
        }
        tile_blit(tile, blit_tl, blit_br);
        if (is_frozen) {
          if (outline) {
            tile_blit_frozen(tile, point(blit_tl.x, blit_tl.y - 1), point(blit_br.x, blit_br.y - 1));
          } else {
            tile_blit_frozen(tile, blit_tl, blit_br);
          }
        }
        if (is_burnt) {
          if (outline) {
            tile_blit_burnt(tile, point(blit_tl.x, blit_tl.y - submerged - 1),
                            point(blit_br.x, blit_br.y - submerged - 1));
          } else {
            tile_blit_burnt(tile, point(blit_tl.x, blit_tl.y - submerged), point(blit_br.x, blit_br.y - submerged));
          }
        }
      }
    } else if (auto submerged = blit_begin_submerged()) {
      if (outline) {
        //
        // Compensate for the one pixel of outline
        //
        tile_blit_outline(tile, point(blit_tl.x, blit_tl.y - 1), point(blit_br.x, blit_br.y - 1), c);
      } else {
        tile_blit(tile, blit_tl, blit_br);
      }
      if (is_frozen) {
        if (outline) {
          tile_blit_frozen(tile, point(blit_tl.x, blit_tl.y - submerged - 1),
                           point(blit_br.x, blit_br.y - submerged - 1));
        } else {
          tile_blit_frozen(tile, point(blit_tl.x, blit_tl.y - submerged), point(blit_br.x, blit_br.y - submerged));
        }
      }
      if (is_burnt) {
        if (outline) {
          tile_blit_burnt(tile, point(blit_tl.x, blit_tl.y - submerged - 1),
                          point(blit_br.x, blit_br.y - submerged - 1));
        } else {
          tile_blit_burnt(tile, point(blit_tl.x, blit_tl.y - submerged), point(blit_br.x, blit_br.y - submerged));
        }
      }
      blit_end_submerged(submerged);
    } else {
      if (outline) {
        //
        // Compensate for the one pixel of outline
        //
        tile_blit_outline(tile, point(blit_tl.x, blit_tl.y - 1), point(blit_br.x, blit_br.y - 1), c);
      } else {
        tile_blit(tile, blit_tl, blit_br);
      }
      if (is_frozen) {
        if (outline) {
          tile_blit_frozen(tile, point(blit_tl.x, blit_tl.y - 1), point(blit_br.x, blit_br.y - 1));
        } else {
          tile_blit_frozen(tile, blit_tl, blit_br);
        }
      }
      if (is_burnt) {
        if (outline) {
          tile_blit_burnt(tile, point(blit_tl.x, blit_tl.y - submerged - 1),
                          point(blit_br.x, blit_br.y - submerged - 1));
        } else {
          tile_blit_burnt(tile, point(blit_tl.x, blit_tl.y - submerged), point(blit_br.x, blit_br.y - submerged));
        }
      }
    }
  } else {
    tile_blit(tile, blit_tl, blit_br);
  }

  tiles_get();
  if (is_wall()) {
    if (! reflection) {
      blit_wall_shadow(blit_tl, blit_br, &tiles);
    }
    blit_wall_cladding(blit_tl, blit_br, &tiles);
  }

  //
  // NOTE: chasm tiles are not blitted explicitly. Instead a floor tile
  // will check for the presence of a chasm beneath it and blit the chasm
  //
  if (tiles.bot3_tile) {
    blit_floor_chasm(blit_tl, blit_br, &tiles);
  }

  if (wobble != 0.0) {
    blit_flush();
    glPopMatrix();
    blit_init();
  }

  is_blitted = true;
}

void Thing::blit_pixelart(int fbo)
{
  TRACE_NO_INDENT();

  point blit_tl, blit_br;
  Tilep tile = {};

  //
  // If currently being displayed and is visible, update the frame count so we can tell
  // what is currently visible and on screen.
  //
  if (get_no_check(level->can_see_currently.can_see, curr_at.x, curr_at.y)) {
    frame_count = game->frame_count;
  }

  //
  // If blitting to the background, ignore scroll
  //
  if (fbo == FBO_PIXELART_FULLMAP) {
    point pre_effect_blit_tl;
    point pre_effect_blit_br;

    if (! coords_get(blit_tl, blit_br, pre_effect_blit_tl, pre_effect_blit_br, tile, false)) {
      return;
    }
  } else {
    if (! map_offset_coords_get(blit_tl, blit_br, tile, false)) {
      return;
    }
  }

  blit_internal(fbo, blit_tl, blit_br, tile, WHITE, false);
}

void Thing::blit_upside_down(int fbo)
{
  TRACE_NO_INDENT();

  if (! gfx_pixelart_reflection()) {
    return;
  }

  point blit_tl, blit_br;
  Tilep tile = {};
  auto  tpp  = tp();

  if (fbo == FBO_PIXELART_FULLMAP) {
    point pre_effect_blit_tl;
    point pre_effect_blit_br;

    if (! coords_get(blit_tl, blit_br, pre_effect_blit_tl, pre_effect_blit_br, tile, false)) {
      return;
    }
  } else {
    if (! map_offset_coords_get(blit_tl, blit_br, tile, true)) {
      return;
    }
  }

  auto diff = blit_br.y - blit_tl.y;
  std::swap(blit_tl.y, blit_br.y);

  if (tile && tile_get_height(tile) != TILE_HEIGHT) {
    if (tpp->gfx_pixelart_oversized_and_on_floor()) {
      blit_br.y += diff;
      blit_tl.y += diff;
    } else {
      blit_br.y += TILE_HEIGHT;
      blit_tl.y += TILE_HEIGHT;
    }
  } else {
    blit_br.y += diff;
    blit_tl.y += diff;
  }

  color reflection = {100, 100, 100, 200};
  blit_internal(fbo, blit_tl, blit_br, tile, reflection, true);
}
