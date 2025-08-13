//
// Copyright goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_ptrcheck.hpp"

float      glapi_last_tex_right;
float      glapi_last_tex_bottom;
GLushort   glapi_last_right;
GLushort   glapi_last_bottom;
static int in_2d_mode;

std::array< GLuint, MAX_FBO > render_buf_id = {};
std::array< GLuint, MAX_FBO > fbo_id        = {};
std::array< GLuint, MAX_FBO > fbo_tex_id    = {};
std::array< isize, MAX_FBO >  fbo_size      = {};

void MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message,
                     const void *userParam)
{
  CON("GL CALLBACK: type = 0x%x, severity = 0x%x, message = %s\n", type, severity, message);
}

void gl_init_2d_mode(void)
{
  TRACE_AND_INDENT();
  GL_ERROR_CHECK();

  if (in_2d_mode) {
    gl_leave_2d_mode();
  }

  //
  // Enable Texture Worldping
  //
  LOG("GFX: OpenGL enable textures");
  glEnable(GL_TEXTURE_2D);
  GL_ERROR_CHECK();

  //
  // Enable alpha blending for sprites
  //
  LOG("GFX: OpenGL enable blending");
  glEnable(GL_BLEND);
  GL_ERROR_CHECK();
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  GL_ERROR_CHECK();

  //
  // Setup our viewport
  //
  LOG("GFX: OpenGL enable viewport");
  glViewport(0, 0, game->config.window_pix_width, game->config.window_pix_height);
  GL_ERROR_CHECK();

  //
  // Reset the view
  //
  glLoadIdentity();
  GL_ERROR_CHECK();

  gl_init_fbo();

  glLineWidth(1.0);
  GL_ERROR_CHECK();
  glEnable(GL_LINE_SMOOTH);
  GL_ERROR_CHECK();

  LOG("GFX: OpenGL initialized");
}

void gl_enter_2d_mode(void)
{
  TRACE_AND_INDENT();
  if (in_2d_mode) {
    gl_leave_2d_mode();
  }

  //
  // Change to the projection matrix and set our viewing volume.
  //
  glMatrixMode(GL_PROJECTION);
  GL_ERROR_CHECK();
  glPushMatrix();
  GL_ERROR_CHECK();

  //
  // Reset the view
  //
  glLoadIdentity();
  GL_ERROR_CHECK();

  //
  // 2D projection
  //
  if (! game->config.game_pix_width || ! game->config.game_pix_height) {
    LOG("Cannot call glOrtho(%d,%d)", game->config.game_pix_width, game->config.game_pix_height);
    return;
  }

  glOrtho(0,                            // left
          game->config.game_pix_width,  // right
          game->config.game_pix_height, // bottom
          0,                            // top
          -1200.0, 1200.0);
  GL_ERROR_CHECK();

  //
  // Make sure we're changing the model view and not the projection
  //
  glMatrixMode(GL_MODELVIEW);
  GL_ERROR_CHECK();
  glPushMatrix();
  GL_ERROR_CHECK();

  //
  // Reset the view
  //
  glLoadIdentity();
  GL_ERROR_CHECK();
  in_2d_mode = true;
}

void gl_enter_2d_mode(int w, int h)
{
  TRACE_AND_INDENT();
  if (in_2d_mode) {
    gl_leave_2d_mode();
  }

  //
  // Change to the projection matrix and set our viewing volume.
  //
  glMatrixMode(GL_PROJECTION);
  GL_ERROR_CHECK();
  glPushMatrix();
  GL_ERROR_CHECK();

  //
  // Reset the view
  //
  glLoadIdentity();
  GL_ERROR_CHECK();

  //
  // 2D projection
  //
  glOrtho(0, // left
          w, // right
          h, // bottom
          0, // top
          -1200.0, 1200.0);
  GL_ERROR_CHECK();

  glViewport(0, 0, w, h);
  GL_ERROR_CHECK();

  //
  // Make sure we're changing the model view and not the projection
  //
  glMatrixMode(GL_MODELVIEW);
  GL_ERROR_CHECK();
  glPushMatrix();
  GL_ERROR_CHECK();

  //
  // Reset the view
  //
  glLoadIdentity();
  GL_ERROR_CHECK();
  in_2d_mode = true;
}

void gl_leave_2d_mode(void)
{
  TRACE_AND_INDENT();
  if (! in_2d_mode) {
    return;
  }
  glMatrixMode(GL_MODELVIEW);
  GL_ERROR_CHECK();
  glPopMatrix();
  GL_ERROR_CHECK();

  glMatrixMode(GL_PROJECTION);
  GL_ERROR_CHECK();
  glPopMatrix();
  GL_ERROR_CHECK();
  in_2d_mode = false;
}

void gl_enter_2_5d_mode(void)
{
  TRACE_AND_INDENT();
  glEnable(GL_DEPTH_TEST);
  glClear(GL_COLOR_BUFFER_BIT);

  glMatrixMode(GL_PROJECTION);
  glPushMatrix();

  glLoadIdentity();

  double scale = 15;
  glOrtho(-scale, scale, -scale * 0.7, scale * 0.7, -scale, scale);

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();

  glLoadIdentity();

  glRotatef(35.264f, 1.0f, 0.0f, 0.0f);
  glRotatef(-45.0f, 0.0f, 1.0f, 0.0f);

#ifdef WIREFRAME
  glPolygonMode(GL_FRONT, GL_LINE); // draw wireframe polygons
  glPolygonMode(GL_BACK, GL_LINE);  // draw wireframe polygons
#endif

  glCullFace(GL_BACK); // don't draw back faces
}

void gl_leave_2_5d_mode(void)
{
  TRACE_AND_INDENT();
  glDisable(GL_DEPTH_TEST);

  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();

  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
}

static void gl_init_fbo_(int fbo, GLuint *render_buf_id, GLuint *fbo_id, GLuint *fbo_tex_id, GLuint tex_width,
                         GLuint tex_height)
{
  TRACE_AND_INDENT();
  DBG2("GFX: create FBO, size %dx%d", tex_width, tex_height);
  GL_ERROR_CHECK();

  DBG2("OpenGl: - glGenTextures");
  if (*fbo_tex_id) {
    DBG2("OpenGl: - glDeleteTextures");
    glDeleteTextures(1, fbo_tex_id);
    GL_ERROR_CHECK();
    *fbo_tex_id = 0;
  }

  if (*fbo_id) {
    DBG2("OpenGl: - glDeleteRenderbuffers");
    glDeleteRenderbuffers_EXT(1, fbo_id);
    GL_ERROR_CHECK();
    *fbo_id = 0;
  }

  glGenTextures(1, fbo_tex_id);
  GL_ERROR_CHECK();

  DBG2("OpenGl: - glBindTexture");
  glBindTexture(GL_TEXTURE_2D, *fbo_tex_id);
  GL_ERROR_CHECK();

  DBG2("OpenGl: - glTexParameterf (clamping)");
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  GL_ERROR_CHECK();
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  GL_ERROR_CHECK();

  DBG2("OpenGl: - glTexParameterf (GL_NEAREST)");
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  GL_ERROR_CHECK();
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  GL_ERROR_CHECK();

  DBG2("OpenGl: - glTexImage2D");
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, tex_width, tex_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
  GL_ERROR_CHECK();
  glBindTexture(GL_TEXTURE_2D, 0);
  GL_ERROR_CHECK();

  //
  // Create a render buffer object.
  //
#ifdef _WIN32
  if (! glFramebufferTexture2D_EXT) {
    DIE("GlGenRenderbuffers_EXT is not present; fatal");
    return;
  }
#endif

  DBG2("OpenGl: - glGenRenderbuffers_EXT");
  glGenRenderbuffers_EXT(1, render_buf_id);
  GL_ERROR_CHECK();

  DBG2("OpenGl: - glBindRenderbuffer_EXT");
  glBindRenderbuffer_EXT(GL_RENDERBUFFER, *render_buf_id);
  GL_ERROR_CHECK();

  DBG2("OpenGl: - glRenderbufferStorage_EXT");
  glRenderbufferStorage_EXT(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, tex_width, tex_height);
  GL_ERROR_CHECK();

  DBG2("OpenGl: - glBindRenderbuffer_EXT");
  glBindRenderbuffer_EXT(GL_RENDERBUFFER, 0);
  GL_ERROR_CHECK();

  //
  // Create a frame buffer object.
  //
  DBG2("OpenGl: - glGenFramebuffers_EXT");
  glGenFramebuffers_EXT(1, fbo_id);
  GL_ERROR_CHECK();

  DBG2("OpenGl: - glBindFramebuffer_EXT");
  glBindFramebuffer_EXT(GL_FRAMEBUFFER, *fbo_id);
  GL_ERROR_CHECK();

  //
  // Attach the texture to FBO color attachment point
  //
  DBG2("OpenGl: - glFramebufferTexture2D_EXT");
  glFramebufferTexture2D_EXT(GL_FRAMEBUFFER,       // 1. fbo target: GL_FRAMEBUFFER
                             GL_COLOR_ATTACHMENT0, // 2. attachment point
                             GL_TEXTURE_2D,        // 3. tex target: GL_TEXTURE_2D
                             *fbo_tex_id,          // 4. tex ID
                             0);                   // 5. mipmap level: 0(base)
  GL_ERROR_CHECK();

  //
  // Attach the renderbuffer to depth attachment point
  //
  DBG2("OpenGl: - glFramebufferRenderbuffer_EXT");
  glFramebufferRenderbuffer_EXT(GL_FRAMEBUFFER,      // 1. fbo target: GL_FRAMEBUFFER
                                GL_DEPTH_ATTACHMENT, // 2. attachment point
                                GL_RENDERBUFFER,     // 3. rbo target: GL_RENDERBUFFER
                                *render_buf_id);     // 4. rbo ID
  GL_ERROR_CHECK();

  //
  // Check FBO status
  //
  DBG2("OpenGl: - glCheckFramebufferStatus_EXT");
  auto status = glCheckFramebufferStatus_EXT(GL_FRAMEBUFFER);
  if (status && (status != GL_FRAMEBUFFER_COMPLETE)) {
    LOG("Failed to create framebuffer, error: %d/0x%x", status, status);

#ifdef GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT
    if (status == GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT) {
      LOG("OpenGl: - GFX: GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT Not all framebuffer attachment points "
          "are framebuffer attachment complete. This means that at least one attachment point with a "
          "renderbuffer or texture attached has its attached object no longer in existence or has an "
          "attached image with a width or height of zero, or the color attachment point has a "
          "non-color-renderable image attached, or the depth attachment point has a non-depth-renderable "
          "image attached, or the stencil attachment point has a non-stencil-renderable image attached. "
          "Color-renderable formats include GL_RGBA4, GL_RGB5_A1, and GL_RGB565. GL_DEPTH_COMPONENT16 is "
          "the only depth-renderable format. GL_STENCIL_INDEX8 is the only stencil-renderable format.");
    }
#endif
#ifdef GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS
    if (status == GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS) {
      LOG("OpenGl: - GFX: GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS Not all attached images have the same "
          "width and height.");
    }
#endif
#ifdef GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT
    if (status == GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT) {
      LOG("OpenGl: - GFX: GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT No images are attached to the framebuffer.");
    }
#endif
#ifdef GL_FRAMEBUFFER_UNSUPPORTED
    if (status == GL_FRAMEBUFFER_UNSUPPORTED) {
      LOG("OpenGl: - GFX: GL_FRAMEBUFFER_UNSUPPORTED The combination of internal formats of the attached images "
          "violates an implementation-dependent set of restrictions.");
    }
#endif
#ifdef GL_FRAMEBUFFER_UNSUPPORTED
    if (status == GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER) {
      LOG("OpenGl: - GFX: GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER");
    }
#endif
#ifdef GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER
    if (status == GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER) {
      LOG("OpenGl: - GFX: GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER");
    }
#endif
  }
  if (! status) {
    glGetError();
  }
  GL_ERROR_CHECK();

  // switch back to window-system-provided framebuffer
  DBG2("OpenGl: - glBindFramebuffer_EXT");
  glBindFramebuffer_EXT(GL_FRAMEBUFFER, 0);
  GL_ERROR_CHECK();
}

void gl_init_fbo(void)
{
  int i;

  LOG("GFX: OpenGL creat FBOs");
  GL_ERROR_CHECK();

  for (i = 0; i < MAX_FBO; i++) {
    int tex_width;
    int tex_height;

    // old size check
    fbo_get_size(i, tex_width, tex_height);

    //
    // If no change in size (map_mini, bg map) then do not reset the FBO
    //
    if (fbo_size[ i ] == isize(tex_width, tex_height)) {
      continue;
    }

    gl_init_fbo_(i, &render_buf_id[ i ], &fbo_id[ i ], &fbo_tex_id[ i ], tex_width, tex_height);
    fbo_size[ i ] = isize(tex_width, tex_height);

    gl_enter_2d_mode(tex_width, tex_height);
    blit_fbo_bind(i);
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    blit_fbo_unbind();
  }

  LOG("GFX: OpenGL created FBOs");
  GL_ERROR_CHECK();
}

void fbo_get_size(int fbo, int &w, int &h)
{
  w = game->config.game_pix_width;
  h = game->config.game_pix_height;

  switch (fbo) {
    case FBO_MAP :
    case FBO_MAP_HIDDEN :
    case FBO_MAP_VISIBLE :
    case FBO_PLAYER_VISIBLE_LIGHTING :
    case FBO_SCREEN_FADE_IN_AND_OUT :
    case FBO_SMALL_POINT_LIGHTS :
      w = game->config.game_pix_width;
      h = game->config.game_pix_height;
      break;
    case FBO_MASK1 :
    case FBO_MASK2 :
    case FBO_MASK3 :
    case FBO_MASK4 :
      w = game->config.game_pix_width;
      h = game->config.game_pix_height;
      break;
    case FBO_MAP_MINI :
      w = MAP_WIDTH;
      h = MAP_HEIGHT;
      break;
    case FBO_PIXELART_FULLMAP :
    case FBO_PIXELART_FULLMAP_LIGHT :
    case FBO_PIXELART_FULLMAP_VISITED :
      w = TILE_WIDTH * MAP_WIDTH;
      h = TILE_HEIGHT * MAP_HEIGHT;
      break;
    case FBO_PIXELART_FULLMAP_MASK1 :
    case FBO_PIXELART_FULLMAP_MASK2 :
    case FBO_PIXELART_FULLMAP_MASK3 :
    case FBO_PIXELART_FULLMAP_MASK4 :
      w = TILE_WIDTH * MAP_WIDTH;
      h = TILE_HEIGHT * MAP_HEIGHT;
      break;
    case FBO_WID :
      w = game->config.ui_pix_width;
      h = game->config.ui_pix_height;
      break;
    case FBO_FINAL :
      w = game->config.window_pix_width;
      h = game->config.window_pix_height;
      break;
    case FBO_SPRITE1 :
    case FBO_SPRITE2 :
    case FBO_SPRITE3 :
      w = game->config.game_pix_width;
      h = game->config.game_pix_height;
      break;
  }

  if ((fbo >= FBO_MAP_DEBUG) && (fbo < FBO_MAP_DEBUG_END)) {
    w = MAP_WIDTH;
    h = MAP_HEIGHT;
  }
}

void blit_fbo(int fbo)
{
  int tex_width;
  int tex_height;
  fbo_get_size(fbo, tex_width, tex_height);
  blit_init();
  blit(fbo_tex_id[ fbo ], 0.0, 1.0, 1.0, 0.0, 0, 0, tex_width, tex_height);
  blit_flush();
}

void blit_fbo_game_pix(int fbo)
{
  blit_init();
  blit(fbo_tex_id[ fbo ], 0.0, 1.0, 1.0, 0.0, 0, 0, game->config.game_pix_width, game->config.game_pix_height);
  blit_flush();
}

void blit_fbo_ui_pix(int fbo)
{
  blit_init();
  blit(fbo_tex_id[ fbo ], 0.0, 1.0, 1.0, 0.0, 0, 0, game->config.ui_pix_width, game->config.ui_pix_height);
  blit_flush();
}

void blit_fbo_window_pix(int fbo)
{
  blit_init();
  blit(fbo_tex_id[ fbo ], 0.0, 1.0, 1.0, 0.0, 0, 0, game->config.window_pix_width, game->config.window_pix_height);
  blit_flush();
}

static int fbo_locked = -1;
static int fbo_last   = -1;

void blit_fbo_push(int fbo) { glBindFramebuffer_EXT(GL_FRAMEBUFFER, fbo_id[ fbo ]); }

void blit_fbo_pop(void) { glBindFramebuffer_EXT(GL_FRAMEBUFFER, fbo_id[ fbo_last ]); }

void blit_fbo_bind(int fbo)
{
  fbo_last = fbo;
  if (fbo_locked != -1) {
    DIE("Attempt to bind to another FBO %d when locked", fbo);
  }
  glBindFramebuffer_EXT(GL_FRAMEBUFFER, fbo_id[ fbo ]);
}

void blit_fbo_unbind(void)
{
  if (fbo_locked != -1) {
    DIE("Attempt to unbind when locked");
  }
  glBindFramebuffer_EXT(GL_FRAMEBUFFER, 0);
}

void blit_fbo_bind_locked(int fbo)
{
  fbo_last   = fbo;
  fbo_locked = fbo;
  glBindFramebuffer_EXT(GL_FRAMEBUFFER, fbo_id[ fbo ]);
}

void blit_fbo_unbind_locked(void)
{
  fbo_locked = -1;
  glBindFramebuffer_EXT(GL_FRAMEBUFFER, 0);
}

//
// x and y per element.
//
#define NUMBER_DIMENSIONS_PER_COORD_2D 2

//
// r,g,b,a per element
//
#define NUMBER_COMPONENTS_PER_COLOR 4

uint32_t NUMBER_BYTES_PER_VERTICE_2D = SIZEOF(GLfloat) * NUMBER_DIMENSIONS_PER_COORD_2D
                                     + SIZEOF(GLushort) * NUMBER_DIMENSIONS_PER_COORD_2D
                                     + SIZEOF(GLubyte) * NUMBER_COMPONENTS_PER_COLOR;
//
// Two arrays, xy and uv.
//
float *gl_array_buf;
float *gl_array_buf_end;

//
// Where we are currently up to in writing to these buffers.
//
GLfloat *bufp;
GLfloat *bufp_end;
int      buf_tex;

void blit_init(void)
{
  TRACE_NO_INDENT();
  buf_tex = 0;

  if (gl_array_buf) {
    bufp = gl_array_buf;
    return;
  }

  //
  // Our array size requirements.
  //
  uint32_t gl_array_size_required;

  //
  // If the screen size has changed or this is the first run, allocate our
  // buffer if our size requirements have changed.
  //
  gl_array_size_required = 8 * 1024 * 1024;

  gl_array_buf = (__typeof__(gl_array_buf)) myzalloc(gl_array_size_required, "GL xy buffer");

  //
  // Make the end a bit smaller so we have plenty of headroom.
  //
  gl_array_buf_end = (__typeof__(gl_array_buf_end)) ((char *) gl_array_buf) + ((gl_array_size_required * 2) / 3);

  bufp     = gl_array_buf;
  bufp_end = gl_array_buf_end;
}

void blit_fini(void)
{
  TRACE_NO_INDENT();
  if (gl_array_buf) {
    myfree(gl_array_buf);
    gl_array_buf = nullptr;
  }
}

void blit_flush(void)
{
  TRACE_NO_INDENT();
  if (gl_array_buf == bufp) {
    return;
  }

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);

  static long nvertices;

  nvertices = ((char *) bufp - (char *) gl_array_buf) / NUMBER_BYTES_PER_VERTICE_2D;

  glBindTexture(GL_TEXTURE_2D, buf_tex);

  glTexCoordPointer(NUMBER_DIMENSIONS_PER_COORD_2D, // (u,v)
                    GL_FLOAT, NUMBER_BYTES_PER_VERTICE_2D, gl_array_buf);

  glVertexPointer(NUMBER_DIMENSIONS_PER_COORD_2D, // (x,y)
                  GL_SHORT, NUMBER_BYTES_PER_VERTICE_2D,
                  ((char *) gl_array_buf)
                      + SIZEOF(GLfloat) * // skip (u,v)
                            NUMBER_DIMENSIONS_PER_COORD_2D);

  glColorPointer(NUMBER_COMPONENTS_PER_COLOR, // (r,g,b,a)
                 GL_UNSIGNED_BYTE, NUMBER_BYTES_PER_VERTICE_2D,
                 ((char *) gl_array_buf)
                     + SIZEOF(GLushort) * // skip (x,y)
                           NUMBER_DIMENSIONS_PER_COORD_2D
                     + SIZEOF(GLfloat) * // skip (u,v)
                           NUMBER_DIMENSIONS_PER_COORD_2D);

  GL_ERROR_CHECK();
  glDrawArrays(GL_TRIANGLE_STRIP, 0, (GLsizei) nvertices);

  glBindTexture(GL_TEXTURE_2D, 0);

  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_COLOR_ARRAY);

  blit_init();
}

void blit_flush_triangle_fan(void)
{
  TRACE_NO_INDENT();
  blit_flush_triangle_fan(gl_array_buf, bufp);
}

void blit_flush_colored_triangle_fan(void)
{
  TRACE_NO_INDENT();
  blit_flush_colored_triangle_fan(gl_array_buf, bufp);
}

void blit_flush_colored_triangle_fan(float *b, float *e)
{
  TRACE_NO_INDENT();
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);

  static long nvertices;

  static const GLsizei stride
      = SIZEOF(GLushort) * NUMBER_DIMENSIONS_PER_COORD_2D + SIZEOF(GLubyte) * NUMBER_COMPONENTS_PER_COLOR;

  nvertices = ((char *) e - (char *) b) / stride;

  glVertexPointer(NUMBER_DIMENSIONS_PER_COORD_2D, // (x,y)
                  GL_SHORT, stride, b);

  glColorPointer(NUMBER_COMPONENTS_PER_COLOR, // (r,g,b,a)
                 GL_UNSIGNED_BYTE, stride,
                 ((char *) b)
                     + SIZEOF(GLushort) * // skip (x,y)
                           NUMBER_DIMENSIONS_PER_COORD_2D);

  GL_ERROR_CHECK();
  glDrawArrays(GL_TRIANGLE_FAN, 0, (GLsizei) nvertices);

  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_COLOR_ARRAY);

  blit_init();
}

void blit_flush_triangle_fan(float *b, float *e)
{
  TRACE_NO_INDENT();
  glEnableClientState(GL_VERTEX_ARRAY);

  static long nvertices;

  static const GLsizei stride = SIZEOF(GLushort) * NUMBER_DIMENSIONS_PER_COORD_2D;

  nvertices = ((char *) e - (char *) b) / stride;

  glVertexPointer(NUMBER_DIMENSIONS_PER_COORD_2D, // (x,y)
                  GL_SHORT, stride, b);

  GL_ERROR_CHECK();
  glDrawArrays(GL_TRIANGLE_FAN, 0, (GLsizei) nvertices);

  glDisableClientState(GL_VERTEX_ARRAY);

  blit_init();
}

void gl_blitquad(GLushort left, GLushort top, GLushort right, GLushort bottom)
{
  GLushort  xy[ 4 * 2 ];
  GLushort *xyp = xy;

  Vertex2(left, top);
  Vertex2(right, top);
  Vertex2(left, bottom);
  Vertex2(right, bottom);

  glEnableClientState(GL_VERTEX_ARRAY);

  glVertexPointer(2, GL_SHORT, 0, xy);
  GL_ERROR_CHECK();
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  glDisableClientState(GL_VERTEX_ARRAY);
}

void gl_blitquad(const point tl, const point tr, const point bl, const point br)
{
  GLushort  xy[ 4 * 2 ];
  GLushort *xyp = xy;

  Vertex2(tl.x, tl.y);
  Vertex2(tr.x, tr.y);
  Vertex2(bl.x, bl.y);
  Vertex2(br.x, br.y);

  glEnableClientState(GL_VERTEX_ARRAY);

  glVertexPointer(2, GL_SHORT, 0, xy);
  GL_ERROR_CHECK();
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  glDisableClientState(GL_VERTEX_ARRAY);
}

void gl_blitsquare(GLushort left, GLushort top, GLushort right, GLushort bottom)
{
  GLushort  xy[ 4 * 2 ];
  GLushort *xyp = xy;

  Vertex2(left, top);
  Vertex2(right, top);
  Vertex2(right, bottom);
  Vertex2(left, bottom);

  glEnableClientState(GL_VERTEX_ARRAY);

  glVertexPointer(2, GL_SHORT, 0, xy);
  GL_ERROR_CHECK();
  glDrawArrays(GL_LINE_LOOP, 0, 4);

  glDisableClientState(GL_VERTEX_ARRAY);
}

void gl_blitline(GLushort left, GLushort top, GLushort right, GLushort bottom)
{
  GLushort  xy[ 2 * 2 ];
  GLushort *xyp = xy;

  Vertex2(left, top);
  Vertex2(right, bottom);

  glEnableClientState(GL_VERTEX_ARRAY);

  glVertexPointer(2, GL_SHORT, 0, xy);
  GL_ERROR_CHECK();
  glDrawArrays(GL_LINES, 0, 2);

  glDisableClientState(GL_VERTEX_ARRAY);
}

#ifdef _WIN32

HDC      hDC;
HGLRC    hGLRC;
HPALETTE hPalette;

const char g_szClassName[] = "myWindowClass";

PFNGLCREATEPROGRAMPROC           glCreateProgram_EXT;
PFNGLDEBUGMESSAGECALLBACKPROC    glDebugMessageCallback_EXT;
PFNGLDELETEPROGRAMPROC           glDeleteProgram_EXT;
PFNGLISPROGRAMPROC               glIsProgram_EXT;
PFNGLCREATESHADERPROC            glCreateShader_EXT;
PFNGLDELETESHADERPROC            glDeleteShader_EXT;
PFNGLSHADERSOURCEPROC            glShaderSource_EXT;
PFNGLCOMPILESHADERPROC           glCompileShader_EXT;
PFNGLATTACHSHADERPROC            glAttachShader_EXT;
PFNGLDETACHSHADERPROC            glDetachShader_EXT;
PFNGLGETATTACHEDSHADERSPROC      glGetAttachedShaders_EXT;
PFNGLLINKPROGRAMPROC             glLinkProgram_EXT;
PFNGLUSEPROGRAMPROC              glUseProgram_EXT;
PFNGLGETSHADERINFOLOGPROC        glGetShaderInfoLog_EXT;
PFNGLGETPROGRAMINFOLOGPROC       glGetProgramInfoLog_EXT;
PFNGLGETUNIFORMLOCATIONPROC      glGetUniformLocation_EXT;
PFNGLUNIFORM1FPROC               glUniform1f_EXT;
PFNGLUNIFORM1IPROC               glUniform1i_EXT;
PFNGLUNIFORM2FVPROC              glUniform2fv_EXT;
PFNGLUNIFORM3FVPROC              glUniform3fv_EXT;
PFNGLGENERATEMIPMAPPROC          glGenerateMipmap_EXT;
PFNGLGENFRAMEBUFFERSPROC         glGenFramebuffers_EXT;
PFNGLDELETEFRAMEBUFFERSPROC      glDeleteFramebuffers_EXT;
PFNGLBINDFRAMEBUFFERPROC         glBindFramebuffer_EXT;
PFNGLGENRENDERBUFFERSPROC        glGenRenderbuffers_EXT;
PFNGLDELETERENDERBUFFERSPROC     glDeleteRenderbuffers_EXT;
PFNGLBINDRENDERBUFFERPROC        glBindRenderbuffer_EXT;
PFNGLRENDERBUFFERSTORAGEPROC     glRenderbufferStorage_EXT;
PFNGLFRAMEBUFFERRENDERBUFFERPROC glFramebufferRenderbuffer_EXT;
PFNGLFRAMEBUFFERTEXTURE2DPROC    glFramebufferTexture2D_EXT;
PFNGLCHECKFRAMEBUFFERSTATUSPROC  glCheckFramebufferStatus_EXT;
PFNGLGENBUFFERSARBPROC           glGenBuffersARB_EXT;
PFNGLBINDBUFFERARBPROC           glBindBufferARB_EXT;
PFNGLBUFFERDATAARBPROC           glBufferDataARB_EXT;
PFNGLDELETEBUFFERSARBPROC        glDeleteBuffersARB_EXT;

static void gl_ext_load(void)
{
  TRACE_AND_INDENT();
  glDebugMessageCallback_EXT = (__typeof__(glDebugMessageCallback_EXT)) wglGetProcAddress("glDebugMessageCallback");
  if (! glDebugMessageCallback_EXT) {
    LOG("OpenGl: - glDebugMessageCallback_EXT - NOT present");
  } else {
    LOG("OpenGl: - glDebugMessageCallback_EXT - present");
  }

  if (glDebugMessageCallback_EXT) {
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback_EXT(MessageCallback, 0);
  }

  TRACE_AND_INDENT();
  glCreateProgram_EXT = (__typeof__(glCreateProgram_EXT)) wglGetProcAddress("glCreateProgram");
  if (! glCreateProgram_EXT) {
    LOG("OpenGl: - glCreateProgram_EXT - NOT present");
  } else {
    LOG("OpenGl: - glCreateProgram_EXT - present");
  }

  glDeleteProgram_EXT = (__typeof__(glDeleteProgram_EXT)) wglGetProcAddress("glDeleteProgram");
  if (! glDeleteProgram_EXT) {
    LOG("OpenGl: - glDeleteProgram_EXT - NOT present");
  } else {
    LOG("OpenGl: - glDeleteProgram_EXT - present");
  }

  glIsProgram_EXT = (__typeof__(glIsProgram_EXT)) wglGetProcAddress("glIsProgram");
  if (! glIsProgram_EXT) {
    LOG("OpenGl: - glIsProgram_EXT - NOT present");
  } else {
    LOG("OpenGl: - glIsProgram_EXT - present");
  }

  glCreateShader_EXT = (__typeof__(glCreateShader_EXT)) wglGetProcAddress("glCreateShader");
  if (! glCreateShader_EXT) {
    LOG("OpenGl: - glCreateShader_EXT - NOT present");
  } else {
    LOG("OpenGl: - glCreateShader_EXT - present");
  }

  glDeleteShader_EXT = (__typeof__(glDeleteShader_EXT)) wglGetProcAddress("glDeleteShader");
  if (! glDeleteShader_EXT) {
    LOG("OpenGl: - glDeleteShader_EXT - NOT present");
  } else {
    LOG("OpenGl: - glDeleteShader_EXT - present");
  }

  glShaderSource_EXT = (__typeof__(glShaderSource_EXT)) wglGetProcAddress("glShaderSource");
  if (! glShaderSource_EXT) {
    LOG("OpenGl: - glShaderSource_EXT - NOT present");
  } else {
    LOG("OpenGl: - glShaderSource_EXT - present");
  }

  glCompileShader_EXT = (__typeof__(glCompileShader_EXT)) wglGetProcAddress("glCompileShader");
  if (! glCompileShader_EXT) {
    LOG("OpenGl: - glCompileShader_EXT - NOT present");
  } else {
    LOG("OpenGl: - glCompileShader_EXT - present");
  }

  glAttachShader_EXT = (__typeof__(glAttachShader_EXT)) wglGetProcAddress("glAttachShader");
  if (! glAttachShader_EXT) {
    LOG("OpenGl: - glAttachShader_EXT - NOT present");
  } else {
    LOG("OpenGl: - glAttachShader_EXT - present");
  }

  glDetachShader_EXT = (__typeof__(glDetachShader_EXT)) wglGetProcAddress("glDetachShader");
  if (! glDetachShader_EXT) {
    LOG("OpenGl: - glDetachShader_EXT - NOT present");
  } else {
    LOG("OpenGl: - glDetachShader_EXT - present");
  }

  glGetAttachedShaders_EXT = (__typeof__(glGetAttachedShaders_EXT)) wglGetProcAddress("glGetAttachedShaders");
  if (! glGetAttachedShaders_EXT) {
    LOG("OpenGl: - glGetAttachedShaders_EXT - NOT present");
  } else {
    LOG("OpenGl: - glGetAttachedShaders_EXT - present");
  }

  glLinkProgram_EXT = (__typeof__(glLinkProgram_EXT)) wglGetProcAddress("glLinkProgram");
  if (! glLinkProgram_EXT) {
    LOG("OpenGl: - glLinkProgram_EXT - NOT present");
  } else {
    LOG("OpenGl: - glLinkProgram_EXT - present");
  }

  glUseProgram_EXT = (__typeof__(glUseProgram_EXT)) wglGetProcAddress("glUseProgram");
  if (! glUseProgram_EXT) {
    LOG("OpenGl: - glUseProgram_EXT - NOT present");
  } else {
    LOG("OpenGl: - glUseProgram_EXT - present");
  }

  glGetShaderInfoLog_EXT = (__typeof__(glGetShaderInfoLog_EXT)) wglGetProcAddress("glGetShaderInfoLog");
  if (! glGetShaderInfoLog_EXT) {
    LOG("OpenGl: - glGetShaderInfoLog_EXT - NOT present");
  } else {
    LOG("OpenGl: - glGetShaderInfoLog_EXT - present");
  }

  glGetProgramInfoLog_EXT = (__typeof__(glGetProgramInfoLog_EXT)) wglGetProcAddress("glGetProgramInfoLog");
  if (! glGetProgramInfoLog_EXT) {
    LOG("OpenGl: - glGetProgramInfoLog_EXT - NOT present");
  } else {
    LOG("OpenGl: - glGetProgramInfoLog_EXT - present");
  }

  glGetUniformLocation_EXT = (__typeof__(glGetUniformLocation_EXT)) wglGetProcAddress("glGetUniformLocation");
  if (! glGetUniformLocation_EXT) {
    LOG("OpenGl: - glGetUniformLocation_EXT - NOT present");
  } else {
    LOG("OpenGl: - glGetUniformLocation_EXT - present");
  }

  glUniform1f_EXT = (__typeof__(glUniform1f_EXT)) wglGetProcAddress("glUniform1f");
  if (! glUniform1f_EXT) {
    LOG("OpenGl: - glUniform1f_EXT - NOT present");
  } else {
    LOG("OpenGl: - glUniform1f_EXT - present");
  }

  glUniform1i_EXT = (__typeof__(glUniform1i_EXT)) wglGetProcAddress("glUniform1i");
  if (! glUniform1i_EXT) {
    LOG("OpenGl: - glUniform1i_EXT - NOT present");
  } else {
    LOG("OpenGl: - glUniform1i_EXT - present");
  }

  glUniform2fv_EXT = (__typeof__(glUniform2fv_EXT)) wglGetProcAddress("glUniform2fv");
  if (! glUniform2fv_EXT) {
    LOG("OpenGl: - glUniform2fv_EXT - NOT present");
  } else {
    LOG("OpenGl: - glUniform2fv_EXT - present");
  }

  glUniform3fv_EXT = (__typeof__(glUniform3fv_EXT)) wglGetProcAddress("glUniform3fv");
  if (! glUniform3fv_EXT) {
    LOG("OpenGl: - glUniform3fv_EXT - NOT present");
  } else {
    LOG("OpenGl: - glUniform3fv_EXT - present");
  }

  glGenerateMipmap_EXT = (__typeof__(glGenerateMipmap_EXT)) wglGetProcAddress("glGenerateMipmap");
  if (! glGenerateMipmap_EXT) {
    LOG("OpenGl: - glGenerateMipmap_EXT - NOT present");
  } else {
    LOG("OpenGl: - glGenerateMipmap_EXT - present");
  }

  glGenFramebuffers_EXT = (__typeof__(glGenFramebuffers_EXT)) wglGetProcAddress("glGenFramebuffers");
  if (! glGenFramebuffers_EXT) {
    LOG("OpenGl: - glGenFramebuffers_EXT - NOT present");
  } else {
    LOG("OpenGl: - glGenFramebuffers_EXT - present");
  }

  glDeleteFramebuffers_EXT = (__typeof__(glDeleteFramebuffers_EXT)) wglGetProcAddress("glDeleteFramebuffers");
  if (! glDeleteFramebuffers_EXT) {
    LOG("OpenGl: - glDeleteFramebuffers_EXT - NOT present");
  } else {
    LOG("OpenGl: - glDeleteFramebuffers_EXT - present");
  }

  glBindFramebuffer_EXT = (__typeof__(glBindFramebuffer_EXT)) wglGetProcAddress("glBindFramebuffer");
  if (! glBindFramebuffer_EXT) {
    LOG("OpenGl: - glBindFramebuffer_EXT - NOT present");
  } else {
    LOG("OpenGl: - glBindFramebuffer_EXT - present");
  }

  glGenRenderbuffers_EXT = (__typeof__(glGenRenderbuffers_EXT)) wglGetProcAddress("glGenRenderbuffers");
  if (! glGenRenderbuffers_EXT) {
    LOG("OpenGl: - glGenRenderbuffers_EXT - NOT present");
  } else {
    LOG("OpenGl: - glGenRenderbuffers_EXT - present");
  }

  glDeleteRenderbuffers_EXT = (__typeof__(glDeleteRenderbuffers_EXT)) wglGetProcAddress("glDeleteRenderbuffers");
  if (! glDeleteRenderbuffers_EXT) {
    LOG("OpenGl: - glDeleteRenderbuffers_EXT - NOT present");
  } else {
    LOG("OpenGl: - glDeleteRenderbuffers_EXT - present");
  }

  glBindRenderbuffer_EXT = (__typeof__(glBindRenderbuffer_EXT)) wglGetProcAddress("glBindRenderbuffer");
  if (! glBindRenderbuffer_EXT) {
    LOG("OpenGl: - glBindRenderbuffer_EXT - NOT present");
  } else {
    LOG("OpenGl: - glBindRenderbuffer_EXT - present");
  }

  glRenderbufferStorage_EXT = (__typeof__(glRenderbufferStorage_EXT)) wglGetProcAddress("glRenderbufferStorage");
  if (! glRenderbufferStorage_EXT) {
    LOG("OpenGl: - glRenderbufferStorage_EXT - NOT present");
  } else {
    LOG("OpenGl: - glRenderbufferStorage_EXT - present");
  }

  glFramebufferRenderbuffer_EXT
      = (__typeof__(glFramebufferRenderbuffer_EXT)) wglGetProcAddress("glFramebufferRenderbuffer");
  if (! glFramebufferRenderbuffer_EXT) {
    LOG("OpenGl: - glFramebufferRenderbuffer_EXT - NOT present");
  } else {
    LOG("OpenGl: - glFramebufferRenderbuffer_EXT - present");
  }

  glCheckFramebufferStatus_EXT
      = (__typeof__(glCheckFramebufferStatus_EXT)) wglGetProcAddress("glCheckFramebufferStatus");
  if (! glCheckFramebufferStatus_EXT) {
    LOG("OpenGl: - glCheckFramebufferStatus_EXT - NOT present");
  } else {
    LOG("OpenGl: - glCheckFramebufferStatus_EXT - present");
  }

  glFramebufferTexture2D_EXT = (__typeof__(glFramebufferTexture2D_EXT)) wglGetProcAddress("glFramebufferTexture2D");
  if (! glFramebufferTexture2D_EXT) {
    LOG("OpenGl: - glFramebufferTexture2D_EXT - NOT present");
  } else {
    LOG("OpenGl: - glFramebufferTexture2D_EXT - present");
  }

  glGenBuffersARB_EXT = (__typeof__(glGenBuffersARB_EXT)) wglGetProcAddress("glGenBuffersARB");
  if (! glGenBuffersARB_EXT) {
    LOG("OpenGl: - glGenBuffersARB_EXT - NOT present");
  } else {
    LOG("OpenGl: - glGenBuffersARB_EXT - present");
  }

  glBindBufferARB_EXT = (__typeof__(glBindBufferARB_EXT)) wglGetProcAddress("glBindBufferARB");
  if (! glBindBufferARB_EXT) {
    LOG("OpenGl: - glBindBufferARB_EXT - NOT present");
  } else {
    LOG("OpenGl: - glBindBufferARB_EXT - present");
  }

  glDeleteBuffersARB_EXT = (__typeof__(glDeleteBuffersARB_EXT)) wglGetProcAddress("glDeleteBuffersARB");
  if (! glDeleteBuffersARB_EXT) {
    LOG("OpenGl: - glDeleteBuffersARB_EXT - NOT present");
  } else {
    LOG("OpenGl: - glDeleteBuffersARB_EXT - present");
  }

  glDeleteBuffersARB_EXT = (__typeof__(glDeleteBuffersARB_EXT)) wglGetProcAddress("glDeleteBuffersARB");
  if (! glDeleteBuffersARB_EXT) {
    LOG("OpenGl: - glDeleteBuffersARB_EXT - NOT present");
  } else {
    LOG("OpenGl: - glDeleteBuffersARB_EXT - present");
  }
}

static void setupPixelFormat(HDC hDC)
{
  TRACE_AND_INDENT();
  PIXELFORMATDESCRIPTOR pfd = {
      SIZEOF(PIXELFORMATDESCRIPTOR),                              // size
      1,                                                          // version
      PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER, // support double-buffering
      PFD_TYPE_RGBA,                                              // color type
      16,                                                         // prefered color depth
      0,
      0,
      0,
      0,
      0,
      0, // color bits (ignored)
      0, // no alpha buffer
      0, // alpha bits (ignored)
      0, // no accumulation buffer
      0,
      0,
      0,
      0,              // accum bits (ignored)
      16,             // depth buffer
      0,              // no stencil buffer
      0,              // no auxiliary buffers
      PFD_MAIN_PLANE, // main layer
      0,              // reserved
      0,
      0,
      0, // no layer, visible, damage masks
  };
  int pixelFormat;

  pixelFormat = ChoosePixelFormat(hDC, &pfd);
  if (pixelFormat == 0) {
    MessageBox(WindowFromDC(hDC), "ChoosePixelFormat failed.", "Error", MB_ICONERROR | MB_OK);
    exit(1);
  }

  if (SetPixelFormat(hDC, pixelFormat, &pfd) != TRUE) {
    MessageBox(WindowFromDC(hDC), "SetPixelFormat failed.", "Error", MB_ICONERROR | MB_OK);
    exit(1);
  }
}

static void setupPalette(HDC hDC)
{
  TRACE_AND_INDENT();
  int                   pixelFormat = GetPixelFormat(hDC);
  PIXELFORMATDESCRIPTOR pfd;
  LOGPALETTE           *pPal;
  int                   paletteSize;

  DescribePixelFormat(hDC, pixelFormat, SIZEOF(PIXELFORMATDESCRIPTOR), &pfd);

  if (pfd.dwFlags & PFD_NEED_PALETTE) {
    paletteSize = 1 << pfd.cColorBits;
  } else {
    return;
  }

  pPal                = (LOGPALETTE *) malloc(SIZEOF(LOGPALETTE) + paletteSize * SIZEOF(PALETTEENTRY));
  pPal->palVersion    = 0x300;
  pPal->palNumEntries = paletteSize;

  // build a simple RGB color palette */
  {
    int redMask   = (1 << pfd.cRedBits) - 1;
    int greenMask = (1 << pfd.cGreenBits) - 1;
    int blueMask  = (1 << pfd.cBlueBits) - 1;
    int i;

    for (i = 0; i < paletteSize; ++i) {
      pPal->palPalEntry[ i ].peRed   = (((i >> pfd.cRedShift) & redMask) * 255) / redMask;
      pPal->palPalEntry[ i ].peGreen = (((i >> pfd.cGreenShift) & greenMask) * 255) / greenMask;
      pPal->palPalEntry[ i ].peBlue  = (((i >> pfd.cBlueShift) & blueMask) * 255) / blueMask;
      pPal->palPalEntry[ i ].peFlags = 0;
    }
  }

  hPalette = CreatePalette(pPal);
  free(pPal);

  if (hPalette) {
    SelectPalette(hDC, hPalette, FALSE);
    RealizePalette(hDC);
  }
}

static LRESULT APIENTRY WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  TRACE_AND_INDENT();
  return DefWindowProc(hWnd, message, wParam, lParam);
}

void gl_ext_init(void)
{
  TRACE_AND_INDENT();
  WNDCLASSEX wc;
  HWND       hwnd;

  LOG("GFX: extensions");

  LOG("OpenGl: - GetModuleHandle");
  HINSTANCE hInstance = GetModuleHandle(0);

  wc.cbSize        = SIZEOF(WNDCLASSEX);
  wc.style         = 0;
  wc.lpfnWndProc   = WndProc;
  wc.cbClsExtra    = 0;
  wc.cbWndExtra    = 0;
  wc.hInstance     = hInstance;
  wc.hIcon         = LoadIcon(nullptr, IDI_APPLICATION);
  wc.hCursor       = LoadCursor(nullptr, IDC_ARROW);
  wc.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
  wc.lpszMenuName  = nullptr;
  wc.lpszClassName = g_szClassName;
  wc.hIconSm       = LoadIcon(nullptr, IDI_APPLICATION);

  LOG("OpenGl: - RegisterClassEx");
  if (! RegisterClassEx(&wc)) {
    MessageBox(nullptr, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
    return;
  }

  LOG("OpenGl: - CreateWindowEx");
  hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, g_szClassName, "zorbash startup", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
                        CW_USEDEFAULT, 240, 120, nullptr, nullptr, hInstance, nullptr);

  if (hwnd == nullptr) {
    MessageBox(nullptr, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
    return;
  }

  ShowWindow(hwnd, 0);
  UpdateWindow(hwnd);

  // initialize OpenGL rendering

  hDC = GetDC(hwnd);
  setupPixelFormat(hDC);
  setupPalette(hDC);
  hGLRC = wglCreateContext(hDC);
  wglMakeCurrent(hDC, hGLRC);

  gl_ext_load();

  // finish OpenGL rendering
  if (hGLRC) {
    wglMakeCurrent(nullptr, nullptr);
    wglDeleteContext(hGLRC);
  }

  if (hPalette) {
    DeleteObject(hPalette);
  }

  ReleaseDC(hwnd, hDC);
}
#else
void gl_ext_init(void) { TRACE_AND_INDENT(); }
#endif

void gl_error(GLenum errCode)
{
  if (errCode == GL_INVALID_ENUM) {
    LOG("GFX: error, GL_INVALID_ENUM");
  } else if (errCode == GL_INVALID_VALUE) {
    LOG("GFX: error, GL_INVALID_VALUE");
  } else if (errCode == GL_INVALID_OPERATION) {
    LOG("GFX: error, GL_INVALID_OPERATION");
  } else if (errCode == GL_STACK_OVERFLOW) {
    LOG("GFX: error, GL_STACK_OVERFLOW");
  } else if (errCode == GL_STACK_UNDERFLOW) {
    LOG("GFX: error, GL_STACK_UNDERFLOW");
  } else if (errCode == GL_OUT_OF_MEMORY) {
    LOG("GFX: error, GL_OUT_OF_MEMORY");
  } else {
    LOG("GFX: unknown error, %d", errCode);
  }
}

/*
 * Set the current GL color
 */
void glcolor(color s)
{
  gl_last_color = s;

  glColor4ub(s.r, s.g, s.b, s.a);
}

/*
 * Set the internal GL color
 */
void glcolorfast(color s) { gl_last_color = s; }

//
// gl_push
//
void gl_push(float **P, float *p_end, uint8_t first, float tex_left, float tex_top, float tex_right, float tex_bottom,
             point tl, point tr, point bl, point br, uint8_t r1, uint8_t g1, uint8_t b1, uint8_t a1, uint8_t r2,
             uint8_t g2, uint8_t b2, uint8_t a2, uint8_t r3, uint8_t g3, uint8_t b3, uint8_t a3, uint8_t r4,
             uint8_t g4, uint8_t b4, uint8_t a4)
{
  float *p = *P;

  if (unlikely(p >= p_end)) {
    LOG("overflow on gl bug %s", __FUNCTION__);
    return;
  }

  if (likely(! first)) {
    //
    // If there is a break in the triangle strip then make a degenerate
    // triangle.
    //
    if ((glapi_last_right != bl.x) || (glapi_last_bottom != bl.y)) {
      gl_push_texcoord(p, glapi_last_tex_right, glapi_last_tex_bottom);
      gl_push_vertex(p, glapi_last_right, glapi_last_bottom);
      gl_push_rgba(p, r4, g4, b4, a4);

      gl_push_texcoord(p, tex_left, tex_top);
      gl_push_vertex(p, tl.x, tl.y);
      gl_push_rgba(p, r1, g1, b1, a1);
    }
  }

  gl_push_texcoord(p, tex_left, tex_top);
  gl_push_vertex(p, tl.x, tl.y);
  gl_push_rgba(p, r1, g1, b1, a1);

  gl_push_texcoord(p, tex_left, tex_bottom);
  gl_push_vertex(p, bl.x, bl.y);
  gl_push_rgba(p, r2, g2, b2, a2);

  gl_push_texcoord(p, tex_right, tex_top);
  gl_push_vertex(p, tr.x, tr.y);
  gl_push_rgba(p, r3, g3, b3, a3);

  gl_push_texcoord(p, tex_right, tex_bottom);
  gl_push_vertex(p, br.x, br.y);
  gl_push_rgba(p, r4, g4, b4, a4);

  glapi_last_tex_right  = tex_right;
  glapi_last_tex_bottom = tex_bottom;
  glapi_last_right      = br.x;
  glapi_last_bottom     = br.y;
  *P                    = p;
}

//
// gl_push
//
void gl_push(float **P, float *p_end, uint8_t first, float tex_left, float tex_top, float tex_right, float tex_bottom,
             GLushort left, GLushort top, GLushort right, GLushort bottom, uint8_t r1, uint8_t g1, uint8_t b1,
             uint8_t a1, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t a2, uint8_t r3, uint8_t g3, uint8_t b3,
             uint8_t a3, uint8_t r4, uint8_t g4, uint8_t b4, uint8_t a4)
{
  point tl(left, top);
  point tr(right, top);
  point bl(left, bottom);
  point br(right, bottom);

  gl_push(P, p_end, first, tex_left, tex_top, tex_right, tex_bottom, tl, tr, bl, br, r1, g1, b1, a1, r2, g2, b2, a2,
          r3, g3, b3, a3, r4, g4, b4, a4);
}

void blit(int tex, float texMinX, float texMinY, float texMaxX, float texMaxY, GLushort left, GLushort top,
          GLushort right, GLushort bottom)
{
  uint8_t first;

  if (unlikely(! buf_tex)) {
    blit_init();
    first = true;
  } else if (unlikely(buf_tex != tex)) {
    blit_flush();
    first = true;
  } else {
    first = false;
  }

  buf_tex = tex;

  color   c = gl_color_current();
  uint8_t r = c.r;
  uint8_t g = c.g;
  uint8_t b = c.b;
  uint8_t a = c.a;

  gl_push(&bufp, bufp_end, first, texMinX, texMinY, texMaxX, texMaxY, left, top, right, bottom, r, g, b, a, r, g, b,
          a, r, g, b, a, r, g, b, a);
}

void blit(int tex, float texMinX, float texMinY, float texMaxX, float texMaxY, point tl, point tr, point bl, point br)
{
  uint8_t first;

  if (unlikely(! buf_tex)) {
    blit_init();
    first = true;
  } else if (unlikely(buf_tex != tex)) {
    blit_flush();
    first = true;
  } else {
    first = false;
  }

  buf_tex = tex;

  color   c = gl_color_current();
  uint8_t r = c.r;
  uint8_t g = c.g;
  uint8_t b = c.b;
  uint8_t a = c.a;

  gl_push(&bufp, bufp_end, first, texMinX, texMinY, texMaxX, texMaxY, tl, tr, bl, br, r, g, b, a, r, g, b, a, r, g, b,
          a, r, g, b, a);
}

void blit_colored(int tex, float texMinX, float texMinY, float texMaxX, float texMaxY, GLushort left, GLushort top,
                  GLushort right, GLushort bottom, color color_bl, color color_br, color color_tl, color color_tr)
{
  uint8_t first;

  if (unlikely(! buf_tex)) {
    blit_init();
    first = true;
  } else if (unlikely(buf_tex != tex)) {
    blit_flush();
    first = true;
  } else {
    first = false;
  }

  buf_tex = tex;

  gl_push(&bufp, bufp_end, first, texMinX, texMinY, texMaxX, texMaxY, left, top, right, bottom, color_tl.r,
          color_tl.g, color_tl.b, color_tl.a, color_bl.r, color_bl.g, color_bl.b, color_bl.a, color_tr.r, color_tr.g,
          color_tr.b, color_tr.a, color_br.r, color_br.g, color_br.b, color_br.a);
}

void blit(int tex, GLushort left, GLushort top, GLushort right, GLushort bottom)
{
  blit(tex, 0, 0, 1, 1, left, top, right, bottom);
}

void blit(int tex, point tl, point tr, point bl, point br) { blit(tex, 0, 0, 1, 1, tl, tr, bl, br); }

void blit_colored(int tex, GLushort left, GLushort top, GLushort right, float bottom, color color_bl, color color_br,
                  color color_tl, color color_tr)
{
  blit_colored(tex, 0, 0, 1, 1, left, top, right, bottom, color_bl, color_br, color_tl, color_tr);
}
