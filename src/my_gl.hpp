//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_GLAPI_HPP_
#define _MY_GLAPI_HPP_
#define GL_GLEXT_PROTOTYPES

#include "my_game_defs.hpp"
#include <array>

/* Defined before OpenGL and GLUT includes to avoid deprecation messages */
#define GL_SILENCE_DEPRECATION

#ifdef __IPHONE_OS_VERSION_MIN_REQUIRED
#define __IPHONEOS__
#include "SDL_opengles.h"

#define CreateVertexBuffers(nobuf, bufptr) glGenBuffers(nobuf, bufptr)
#define DeleteVertexBuffers(nobuf, bufptr) glDeleteBuffers(nobuf, bufptr)
#else

#ifdef _WIN32
#include "SDL_opengl.h"
#endif

#define glOrthof glOrtho
#endif

#ifdef _WIN32
//    #include "GL/glew.h"
#elif __APPLE__
#include "OpenGL/gl.h"
#include "OpenGL/glext.h"
#include "TargetConditionals.h"

#if TARGET_IPHONE_SIMULATOR
// iOS Simulator
#elif TARGET_OS_IPHONE
// iOS device
#elif TARGET_OS_MAC
// Other kinds of Mac OS
#else
// Unsupported platform
#endif
#else
// linux
#include "GL/gl.h"
#include "GL/glext.h"
#endif

#include "my_color.hpp"
#include "my_point.hpp"
#include "my_size.hpp"

//
// Push elements onto the array buffer.
//
#define gl_push_texcoord(p, x, y)                                                                                    \
  {                                                                                                                  \
    *p++ = x;                                                                                                        \
    *p++ = y;                                                                                                        \
  }

//
// Push elements onto the array buffer.
//
#define gl_push_vertex(p, x, y)                                                                                      \
  {                                                                                                                  \
    auto c = (GLushort *) p;                                                                                         \
    *c++   = x;                                                                                                      \
    *c++   = y;                                                                                                      \
    p      = (GLfloat *) c;                                                                                          \
  }

//
// Push elements onto the array buffer.
//
#define gl_push_rgba(p, r, g, b, a)                                                                                  \
  {                                                                                                                  \
    auto c = (GLubyte *) p;                                                                                          \
    *c++   = r;                                                                                                      \
    *c++   = g;                                                                                                      \
    *c++   = b;                                                                                                      \
    *c++   = a;                                                                                                      \
    p      = (GLfloat *) c;                                                                                          \
  }

#define Vertex2(x, y)                                                                                                \
  *xyp++ = x;                                                                                                        \
  *xyp++ = y;

//
// gl_push_triangle
//
#define gl_push_triangle_colored(p, p_end, x1, y1, x2, y2, x3, y3, r1, g1, b1, a1, r2, g2, b2, a2, r3, g3, b3, a3)   \
  {                                                                                                                  \
    gl_push_vertex(p, x1, y1);                                                                                       \
    gl_push_rgba(p, r1, g1, b1, a1);                                                                                 \
    gl_push_vertex(p, x2, y2);                                                                                       \
    gl_push_rgba(p, r2, g2, b2, a2);                                                                                 \
    gl_push_vertex(p, x3, y3);                                                                                       \
    gl_push_rgba(p, r2, g3, b3, a3);                                                                                 \
  }

#define gl_push_colored_point(p, p_end, x1, y1, r1, g1, b1, a1)                                                      \
  {                                                                                                                  \
    gl_push_vertex(p, x1, y1);                                                                                       \
    gl_push_rgba(p, r1, g1, b1, a1);                                                                                 \
  }

#define gl_push_point(p, p_end, x1, y1)                                                                              \
  {                                                                                                                  \
    gl_push_vertex(p, x1, y1);                                                                                       \
  }

//
// gl_push_tex_point
//
#define gl_push_tex_point(p, p_end, tx, ty, x1, y1, r1, g1, b1, a1)                                                  \
  {                                                                                                                  \
    gl_push_texcoord(p, tx, ty);                                                                                     \
    gl_push_vertex(p, x1, y1);                                                                                       \
    gl_push_rgba(p, r1, g1, b1, a1);                                                                                 \
  }

#define triangle_colored(x1, y1, x2, y2, x3, y3, r1, g1, b1, a1, r2, g2, b2, a2, r3, g3, b3, a3)                     \
  {                                                                                                                  \
    gl_push_triangle_colored(bufp, bufp_end, x1, y1, x2, y2, x3, y3, r1, g1, b1, a1, r2, g2, b2, a2, r3, g3, b3,     \
                             a3);                                                                                    \
  }

#define push_colored_point(x1, y1, r1, g1, b1, a1)                                                                   \
  {                                                                                                                  \
    gl_push_colored_point(bufp, bufp_end, x1, y1, r1, g1, b1, a1);                                                   \
  }

#define push_point(x1, y1)                                                                                           \
  {                                                                                                                  \
    gl_push_point(bufp, bufp_end, x1, y1);                                                                           \
  }

#define push_tex_point(tx, ty, x1, y1, r1, g1, b1, a1)                                                               \
  {                                                                                                                  \
    gl_push_tex_point(bufp, bufp_end, tx, ty, x1, y1, r1, g1, b1, a1);                                               \
  }

//
// gl_push_triangle
//
#define gl_push_triangle(p, p_end, x1, y1, x2, y2, x3, y3)                                                           \
  {                                                                                                                  \
    gl_push_vertex(p, x1, y1);                                                                                       \
    gl_push_vertex(p, x2, y2);                                                                                       \
    gl_push_vertex(p, x3, y3);                                                                                       \
  }

#define triangle(x1, y1, x2, y2, x3, y3)                                                                             \
  {                                                                                                                  \
    gl_push_triangle(bufp, bufp_end, x1, y1, x2, y2, x3, y3);                                                        \
  }

#ifdef _WIN32
extern PFNGLCREATEPROGRAMPROC           glCreateProgram_EXT;
extern PFNGLDELETEPROGRAMPROC           glDeleteProgram_EXT;
extern PFNGLISPROGRAMPROC               glIsProgram_EXT;
extern PFNGLCREATESHADERPROC            glCreateShader_EXT;
extern PFNGLDELETESHADERPROC            glDeleteShader_EXT;
extern PFNGLSHADERSOURCEPROC            glShaderSource_EXT;
extern PFNGLCOMPILESHADERPROC           glCompileShader_EXT;
extern PFNGLATTACHSHADERPROC            glAttachShader_EXT;
extern PFNGLDETACHSHADERPROC            glDetachShader_EXT;
extern PFNGLGETATTACHEDSHADERSPROC      glGetAttachedShaders_EXT;
extern PFNGLLINKPROGRAMPROC             glLinkProgram_EXT;
extern PFNGLUSEPROGRAMPROC              glUseProgram_EXT;
extern PFNGLGETSHADERINFOLOGPROC        glGetShaderInfoLog_EXT;
extern PFNGLGETPROGRAMINFOLOGPROC       glGetProgramInfoLog_EXT;
extern PFNGLGETUNIFORMLOCATIONPROC      glGetUniformLocation_EXT;
extern PFNGLUNIFORM1FPROC               glUniform1f_EXT;
extern PFNGLUNIFORM1IPROC               glUniform1i_EXT;
extern PFNGLUNIFORM2FVPROC              glUniform2fv_EXT;
extern PFNGLUNIFORM3FVPROC              glUniform3fv_EXT;
extern PFNGLGENERATEMIPMAPPROC          glGenerateMipmap_EXT;
extern PFNGLGENFRAMEBUFFERSPROC         glGenFramebuffers_EXT;
extern PFNGLDELETEFRAMEBUFFERSPROC      glDeleteFramebuffers_EXT;
extern PFNGLBINDFRAMEBUFFERPROC         glBindFramebuffer_EXT;
extern PFNGLGENRENDERBUFFERSPROC        glGenRenderbuffers_EXT;
extern PFNGLDELETERENDERBUFFERSPROC     glDeleteRenderbuffers_EXT;
extern PFNGLBINDRENDERBUFFERPROC        glBindRenderbuffer_EXT;
extern PFNGLRENDERBUFFERSTORAGEPROC     glRenderbufferStorage_EXT;
extern PFNGLFRAMEBUFFERRENDERBUFFERPROC glFramebufferRenderbuffer_EXT;
extern PFNGLFRAMEBUFFERTEXTURE2DPROC    glFramebufferTexture2D_EXT;
extern PFNGLCHECKFRAMEBUFFERSTATUSPROC  glCheckFramebufferStatus_EXT;
extern PFNGLGENBUFFERSARBPROC           glGenBuffersARB_EXT;
extern PFNGLBINDBUFFERARBPROC           glBindBufferARB_EXT;
extern PFNGLBUFFERDATAARBPROC           glBufferDataARB_EXT;
extern PFNGLDELETEBUFFERSARBPROC        glDeleteBuffersARB_EXT;
#else
#define glCreateProgram_EXT           glCreateProgramEXT
#define glDeleteProgram_EXT           glDeleteProgramEXT
#define glIsProgram_EXT               glIsProgramEXT
#define glCreateShader_EXT            glCreateShaderEXT
#define glDeleteShader_EXT            glDeleteShaderEXT
#define glShaderSource_EXT            glShaderSourceEXT
#define glCompileShader_EXT           glCompileShaderEXT
#define glAttachShader_EXT            glAttachShaderEXT
#define glDetachShader_EXT            glDetachShaderEXT
#define glGetAttachedShaders_EXT      glGetAttachedShadersEXT
#define glLinkProgram_EXT             glLinkProgramEXT
#define glUseProgram_EXT              glUseProgramEXT
#define glGetShaderInfoLog_EXT        glGetShaderInfoLogEXT
#define glGetProgramInfoLog_EXT       glGetProgramInfoLogEXT
#define glGetUniformLocation_EXT      glGetUniformLocationEXT
#define glUniform1f_EXT               glUniform1fEXT
#define glUniform1i_EXT               glUniform1iEXT
#define glUniform2fv_EXT              glUniform2fvEXT
#define glUniform3fv_EXT              glUniform3fvEXT
#define glGenerateMipmap_EXT          glGenerateMipmapEXT
#define glGenFramebuffers_EXT         glGenFramebuffersEXT
#define glDeleteFramebuffers_EXT      glDeleteFramebuffersEXT
#define glBindFramebuffer_EXT         glBindFramebufferEXT
#define glGenRenderbuffers_EXT        glGenRenderbuffersEXT
#define glDeleteRenderbuffers_EXT     glDeleteRenderbuffersEXT
#define glBindRenderbuffer_EXT        glBindRenderbufferEXT
#define glRenderbufferStorage_EXT     glRenderbufferStorageEXT
#define glFramebufferRenderbuffer_EXT glFramebufferRenderbufferEXT
#define glFramebufferTexture2D_EXT    glFramebufferTexture2DEXT
#define glCheckFramebufferStatus_EXT  glCheckFramebufferStatusEXT
#define glGenBuffersARB_EXT           glGenBuffersARBEXT
#define glBindBufferARB_EXT           glBindBufferARBEXT
#define glBufferDataARB_EXT           glBufferDataARBEXT
#define glDeleteBuffersARB_EXT        glDeleteBuffersARBEXT
#endif

//
// Frame buffer objects
//
#define FBO_MAP                      0
#define FBO_MAP_VISIBLE              1
#define FBO_MAP_HIDDEN               2
#define FBO_WID                      3
#define FBO_PLAYER_VISIBLE_LIGHTING  4
#define FBO_MAP_MINI                 5
#define FBO_MASK1                    6
#define FBO_MASK2                    7
#define FBO_MASK3                    8
#define FBO_MASK4                    9
#define FBO_PIXELART_FULLMAP         10
#define FBO_PIXELART_FULLMAP_MASK1   11
#define FBO_PIXELART_FULLMAP_MASK2   12
#define FBO_PIXELART_FULLMAP_MASK3   13
#define FBO_PIXELART_FULLMAP_MASK4   14
#define FBO_PIXELART_FULLMAP_LIGHT   15
#define FBO_PIXELART_FULLMAP_VISITED 16
#define FBO_FINAL                    17
#define FBO_SCREEN_FADE_IN_AND_OUT   18
#define FBO_SMALL_POINT_LIGHTS       19
#define FBO_SPRITE                   20
#define FBO_MAP_DEBUG                21 // MUST BE LAST, as we generate more from this point
#define FBO_MAP_DEBUG_END            (FBO_MAP_DEBUG + (DUNGEONS_GRID_CHUNK_WIDTH * DUNGEONS_GRID_CHUNK_HEIGHT))
#define MAX_FBO                      (FBO_MAP_DEBUG_END + 1)

extern uint32_t                      NUMBER_BYTES_PER_VERTICE_2D;
extern GLfloat                      *bufp;
extern GLfloat                      *bufp_end;
extern GLushort                      glapi_last_bottom;
extern GLushort                      glapi_last_right;
extern float                        *gl_array_buf;
extern float                        *gl_array_buf_end;
extern float                         glapi_last_tex_bottom;
extern float                         glapi_last_tex_right;
extern int                           buf_tex;
extern std::array< GLuint, MAX_FBO > fbo_id;
extern std::array< GLuint, MAX_FBO > fbo_tex_id;
extern std::array< GLuint, MAX_FBO > render_buf_id;
extern std::array< isize, MAX_FBO >  fbo_size;
void                                 blit(int tex, GLushort left, GLushort top, GLushort right, GLushort bottom);
void blit(int tex, float texMinX, float texMinY, float texMaxX, float texMaxY, GLushort left, GLushort top,
          GLushort right, GLushort bottom);
void blit(int tex, float texMinX, float texMinY, float texMaxX, float texMaxY, point tl, point tr, point bl,
          point br);
void blit(int tex, point tl, point tr, point bl, point br);
void blit_colored(int tex, GLushort left, GLushort top, GLushort right, float bottom, color color_bl, color color_br,
                  color color_tl, color color_tr);
void blit_colored(int tex, float texMinX, float texMinY, float texMaxX, float texMaxY, GLushort left, GLushort top,
                  GLushort right, GLushort bottom, color color_bl, color color_br, color color_tl, color color_tr);
void blit_fbo(int fbo);
void blit_fbo_push(int fbo);
void blit_fbo_pop(void);
void blit_fbo_bind(int fbo);
void blit_fbo_bind_locked(int fbo);
void blit_fbo_game_pix(int fbo);
void blit_fbo_ui_pix(int fbo);
void blit_fbo_window_pix(int fbo);
void blit_fbo_unbind(void);
void blit_fbo_unbind_locked(void);
void blit_fini(void);
void blit_flush(void);
void blit_flush_colored_triangle_fan(float *begin, float *end);
void blit_flush_colored_triangle_fan(void);
void blit_flush_triangle_fan(float *begin, float *end);
void blit_flush_triangle_fan(void);
void blit_init(void);
void fbo_get_size(int fbo, int &w, int &h);
void gl_blitline(GLushort tlx, GLushort tly, GLushort brx, GLushort bry);
void gl_blitquad(GLushort tlx, GLushort tly, GLushort brx, GLushort bry);
void gl_blitquad(const point tl, const point tr, const point bl, const point br);
void gl_blitsquare(GLushort tlx, GLushort tly, GLushort brx, GLushort bry);
void gl_enter_2_5d_mode(void);
void gl_enter_2d_mode(int, int);
void gl_enter_2d_mode(void);
void gl_error(GLenum err);
void gl_ext_init(void);
void gl_init_2d_mode(void);
void gl_init_fbo(void);
void gl_leave_2_5d_mode(void);
void gl_leave_2d_mode(void);
void gl_ortho_set(int width, int height);
void gl_push(float **P, float *p_end, uint8_t first, float tex_left, float tex_top, float tex_right, float tex_bottom,
             GLushort left, GLushort top, GLushort right, GLushort bottom, uint8_t r1, uint8_t g1, uint8_t b1,
             uint8_t a1, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t a2, uint8_t r3, uint8_t g3, uint8_t b3,
             uint8_t a3, uint8_t r4, uint8_t g4, uint8_t b4, uint8_t a4);
void gl_push(float **P, float *p_end, uint8_t first, float tex_left, float tex_top, float tex_right, float tex_bottom,
             point tl, point tr, point bl, point br, uint8_t r1, uint8_t g1, uint8_t b1, uint8_t a1, uint8_t r2,
             uint8_t g2, uint8_t b2, uint8_t a2, uint8_t r3, uint8_t g3, uint8_t b3, uint8_t a3, uint8_t r4,
             uint8_t g4, uint8_t b4, uint8_t a4);
void glcolor(color s);
void glcolorfast(color s);

#define GL_ERROR_CHECK()                                                                                             \
  {                                                                                                                  \
    auto errCode = glGetError();                                                                                     \
    if (likely(errCode == GL_NO_ERROR)) {                                                                            \
      /* CON("GFX: ok at %s:%s line %u", SRC_FILE_NAME, SRC_FUNC_NAME, SRC_LINE_NUM); */                             \
    } else {                                                                                                         \
      LOG("GFX: error at %s:%s line %u", SRC_FILE_NAME, SRC_FUNC_NAME, SRC_LINE_NUM);                                \
      gl_error(errCode);                                                                                             \
    }                                                                                                                \
  }

#endif
