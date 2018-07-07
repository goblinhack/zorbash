/*
 * Copyright (C) 2011-2020 goblinhack@gmail.com
 *
 * See the README file for license info.
 */

#pragma once

#ifndef _MY_GLAPI_H_
#define _MY_GLAPI_H_
#define GL_GLEXT_PROTOTYPES

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

#include <stdlib.h>
#include "my_main.h"
#include "my_color.h"
#include "my_string.h"

/*
 * gl.c
 */
void gl_init_2d_mode(void);
void gl_enter_2d_mode(void);
void gl_leave_2d_mode(void);
void gl_enter_2_5d_mode(void);
void gl_leave_2_5d_mode(void);

void blit_flush(void);
void blit_flush_3d(void);
void blit_flush_triangles(void);
void blit_flush_colored_triangles(void);
void blit_flush_triangle_fan(void);
void blit_flush_triangle_strip(void);
void blit_flush_tex_triangle_fan(void);
void blit_fini(void);
void gl_blitquad(float tlx, float tly, float brx, float bry);
void gl_blitsquare(float tlx, float tly, float brx, float bry);
void gl_blitline(float tlx, float tly, float brx, float bry);

/*
 * gl_push_texcoord
 *
 * Push elements onto the array buffer.
 */
#define gl_push_texcoord(p, x, y) \
{ \
    *p++ = x; \
    *p++ = y; \
}

/*
 * gl_push_vertex
 *
 * Push elements onto the array buffer.
 */
#define gl_push_vertex(p, x, y) \
{ \
    *p++ = x; \
    *p++ = y; \
}

/*
 * gl_push_vertex
 *
 * Push elements onto the array buffer.
 *
 * Ok, why, z then y ? for isometric views, it's easier to think of z as up
 */
#define gl_push_vertex_3d(p, x, z, y) \
{ \
    *p++ = x; \
    *p++ = y; \
    *p++ = z; \
}

/*
 * gl_push_rgba
 *
 * Push elements onto the array buffer.
 */
#define gl_push_rgba(p, r, g, b, a) \
{ \
    *p++ = r; \
    *p++ = g; \
    *p++ = b; \
    *p++ = a; \
} \

#define Vertex2f(x, y)                          \
    *xyp++ = x;                                 \
    *xyp++ = y;

#define Vertex3f(x, y, z)                       \
    *xyp++ = x;                                 \
    *xyp++ = y;                                 \
    *xyp++ = z;

extern GLfloat *bufp;
extern GLfloat *bufp_end;
extern int buf_tex;

extern void blit_init(void);

extern float glapi_last_tex_right;
extern float glapi_last_tex_bottom;
extern float glapi_last_right;
extern float glapi_last_bottom;

/*
 * gl_push
 */
static inline void
gl_push (float **P,
         float *p_end,
         uint8_t first,
         float tex_left,
         float tex_top,
         float tex_right,
         float tex_bottom,
         float left,
         float top,
         float right,
         float bottom,
         float r1, float g1, float b1, float a1,
         float r2, float g2, float b2, float a2,
         float r3, float g3, float b3, float a3,
         float r4, float g4, float b4, float a4)
{
    float *p = *P;

    if (unlikely(p >= p_end)) {
        DIE("overflow on gl bug %s", __FUNCTION__);
    }

    if (likely(!first)) {
        /*
         * If there is a break in the triangle strip then make a degenerate
         * triangle.
         */
        if ((glapi_last_right != left) || (glapi_last_bottom != bottom)) {
            gl_push_texcoord(p, glapi_last_tex_right, glapi_last_tex_bottom);
            gl_push_vertex(p, glapi_last_right, glapi_last_bottom);
            gl_push_rgba(p, r4, g4, b4, a4);

            gl_push_texcoord(p, tex_left,  tex_top);
            gl_push_vertex(p, left,  top);
            gl_push_rgba(p, r1, g1, b1, a1);
        }
    }

    gl_push_texcoord(p, tex_left,  tex_top);
    gl_push_vertex(p, left,  top);
    gl_push_rgba(p, r1, g1, b1, a1);

    gl_push_texcoord(p, tex_left,  tex_bottom);
    gl_push_vertex(p, left,  bottom);
    gl_push_rgba(p, r2, g2, b2, a2);

    gl_push_texcoord(p, tex_right, tex_top);
    gl_push_vertex(p, right, top);
    gl_push_rgba(p, r3, g3, b3, a3);

    gl_push_texcoord(p, tex_right, tex_bottom);
    gl_push_vertex(p, right, bottom);
    gl_push_rgba(p, r4, g4, b4, a4);

    glapi_last_tex_right = tex_right;
    glapi_last_tex_bottom = tex_bottom;
    glapi_last_right = right;
    glapi_last_bottom = bottom;
    *P = p;
}

static inline
void blit (int tex,
           float texMinX,
           float texMinY,
           float texMaxX,
           float texMaxY,
           float left,
           float top,
           float right,
           float bottom)
{
    uint8_t first;

    if (unlikely(!buf_tex)) {
        blit_init();
        first = true;
    } else if (unlikely(buf_tex != tex)) {
        blit_flush();
        first = true;
    } else {
        first = false;
    }

    buf_tex = tex;

    color c = gl_color_current();

    float r = ((float)c.r) / 255.0;
    float g = ((float)c.g) / 255.0;
    float b = ((float)c.b) / 255.0;
    float a = ((float)c.a) / 255.0;

    gl_push(&bufp,
            bufp_end,
            first,
            texMinX,
            texMinY,
            texMaxX,
            texMaxY,
            left,
            top,
            right,
            bottom,
            r, g, b, a,
            r, g, b, a,
            r, g, b, a,
            r, g, b, a);
}

static inline
void blit_colored (int tex,
                   float texMinX,
                   float texMinY,
                   float texMaxX,
                   float texMaxY,
                   float left,
                   float top,
                   float right,
                   float bottom,
                   color color_bl,
                   color color_br,
                   color color_tl,
                   color color_tr
                   )
{
    uint8_t first;

    if (unlikely(!buf_tex)) {
        blit_init();
        first = true;
    } else if (unlikely(buf_tex != tex)) {
        blit_flush();
        first = true;
    } else {
        first = false;
    }

    buf_tex = tex;

    gl_push(&bufp,
            bufp_end,
            first,
            texMinX,
            texMinY,
            texMaxX,
            texMaxY,
            left,
            top,
            right,
            bottom,
            ((double)color_tl.r) / 255.0,
            ((double)color_tl.g) / 255.0,
            ((double)color_tl.b) / 255.0,
            ((double)color_tl.a) / 255.0,
            ((double)color_bl.r) / 255.0,
            ((double)color_bl.g) / 255.0,
            ((double)color_bl.b) / 255.0,
            ((double)color_bl.a) / 255.0,
            ((double)color_tr.r) / 255.0,
            ((double)color_tr.g) / 255.0,
            ((double)color_tr.b) / 255.0,
            ((double)color_tr.a) / 255.0,
            ((double)color_br.r) / 255.0,
            ((double)color_br.g) / 255.0,
            ((double)color_br.b) / 255.0,
            ((double)color_br.a) / 255.0);
}

/*
 * gl_push_triangle
 */
#define gl_push_triangle_colored(p, \
                                 p_end, \
                                 x1, y1, \
                                 x2, y2, \
                                 x3, y3, \
                                 r1, g1, b1, a1, \
                                 r2, g2, b2, a2, \
                                 r3, g3, b3, a3) \
{ \
    gl_push_vertex(p, x1, y1); \
    gl_push_rgba(p, r1, g1, b1, a1); \
    gl_push_vertex(p, x2, y2); \
    gl_push_rgba(p, r2, g2, b2, a2); \
    gl_push_vertex(p, x3, y3); \
    gl_push_rgba(p, r2, g3, b3, a3); \
} \

/*
 * gl_push_point
 */
#define gl_push_point(p, p_end, \
                      x1, y1, \
                      r1, g1, b1, a1) \
{ \
    gl_push_vertex(p, x1, y1); \
    gl_push_rgba(p, r1, g1, b1, a1); \
} \

/*
 * gl_push_tex_point
 */
#define gl_push_tex_point(p, p_end, \
                          tx, ty, \
                          x1, y1, \
                          r1, g1, b1, a1) \
{ \
    gl_push_texcoord(p, tx, ty); \
    gl_push_vertex(p, x1, y1); \
    gl_push_rgba(p, r1, g1, b1, a1); \
} \

#define triangle_colored(x1, y1, \
                         x2, y2, \
                         x3, y3, \
                         r1, g1, b1, a1, \
                         r2, g2, b2, a2, \
                         r3, g3, b3, a3) \
{ \
    gl_push_triangle_colored(bufp, \
                             bufp_end, \
                             x1, y1, \
                             x2, y2, \
                             x3, y3, \
                             r1, g1, b1, a1, \
                             r2, g2, b2, a2, \
                             r3, g3, b3, a3); \
} \

#define push_point(x1, y1, r1, g1, b1, a1) \
{ \
    gl_push_point(bufp, \
                  bufp_end, \
                  x1, y1, \
                  r1, g1, b1, a1); \
} \

#define push_tex_point(tx, ty, x1, y1, r1, g1, b1, a1) \
{ \
    gl_push_tex_point(bufp, \
                      bufp_end, \
                      tx, ty, \
                      x1, y1, \
                      r1, g1, b1, a1); \
} \

/*
 * gl_push_triangle
 */
#define gl_push_triangle(p, p_end, x1, y1, x2, y2, x3, y3) \
{ \
    gl_push_vertex(p, x1, y1); \
    gl_push_vertex(p, x2, y2); \
    gl_push_vertex(p, x3, y3); \
} \

#define triangle(x1, y1, x2, y2, x3, y3) \
{ \
    gl_push_triangle(bufp, \
                     bufp_end, \
                     x1, y1, \
                     x2, y2, \
                     x3, y3); \
}

/*
 * Set the current GL color
 */
static inline void glcolor (color s)
{
    gl_last_color = s;

    glColor4ub(s.r, s.g, s.b, s.a);
}

extern void gl_ext_init(void);

extern GLuint render_buf_id1;
extern GLuint fbo_id1;
extern GLuint fbo_tex_id1;

extern GLuint render_buf_id_wid;
extern GLuint fbo_id_wid;
extern GLuint fbo_tex_id_wid;

#ifdef _WIN32
extern PFNGLCREATEPROGRAMPROC glCreateProgram_EXT;
extern PFNGLDELETEPROGRAMPROC glDeleteProgram_EXT;
extern PFNGLISPROGRAMPROC glIsProgram_EXT;
extern PFNGLCREATESHADERPROC glCreateShader_EXT;
extern PFNGLDELETESHADERPROC glDeleteShader_EXT;
extern PFNGLSHADERSOURCEPROC glShaderSource_EXT;
extern PFNGLCOMPILESHADERPROC glCompileShader_EXT;
extern PFNGLATTACHSHADERPROC glAttachShader_EXT;
extern PFNGLDETACHSHADERPROC glDetachShader_EXT;
extern PFNGLGETATTACHEDSHADERSPROC glGetAttachedShaders_EXT;
extern PFNGLLINKPROGRAMPROC glLinkProgram_EXT;
extern PFNGLUSEPROGRAMPROC glUseProgram_EXT;
extern PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog_EXT;
extern PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog_EXT;
extern PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation_EXT;
extern PFNGLUNIFORM1FPROC glUniform1f_EXT;
extern PFNGLUNIFORM1IPROC glUniform1i_EXT;
extern PFNGLUNIFORM2FVPROC glUniform2fv_EXT;
extern PFNGLUNIFORM3FVPROC glUniform3fv_EXT;
extern PFNGLGENERATEMIPMAPPROC glGenerateMipmap_EXT;
extern PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers_EXT;
extern PFNGLDELETEFRAMEBUFFERSPROC glDeleteFramebuffers_EXT;
extern PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer_EXT;
extern PFNGLGENRENDERBUFFERSPROC glGenRenderbuffers_EXT;
extern PFNGLDELETERENDERBUFFERSPROC glDeleteRenderbuffers_EXT;
extern PFNGLBINDRENDERBUFFERPROC glBindRenderbuffer_EXT;
extern PFNGLRENDERBUFFERSTORAGEPROC glRenderbufferStorage_EXT;
extern PFNGLFRAMEBUFFERRENDERBUFFERPROC glFramebufferRenderbuffer_EXT;
extern PFNGLFRAMEBUFFERTEXTURE2DPROC glFramebufferTexture2D_EXT;
extern PFNGLCHECKFRAMEBUFFERSTATUSPROC glCheckFramebufferStatus_EXT;
extern PFNGLGENBUFFERSARBPROC glGenBuffersARB_EXT;
extern PFNGLBINDBUFFERARBPROC glBindBufferARB_EXT;
extern PFNGLBUFFERDATAARBPROC glBufferDataARB_EXT;
extern PFNGLDELETEBUFFERSARBPROC glDeleteBuffersARB_EXT;
#else
#define glCreateProgram_EXT glCreateProgramEXT
#define glDeleteProgram_EXT glDeleteProgramEXT
#define glIsProgram_EXT glIsProgramEXT
#define glCreateShader_EXT glCreateShaderEXT
#define glDeleteShader_EXT glDeleteShaderEXT
#define glShaderSource_EXT glShaderSourceEXT
#define glCompileShader_EXT glCompileShaderEXT
#define glAttachShader_EXT glAttachShaderEXT
#define glDetachShader_EXT glDetachShaderEXT
#define glGetAttachedShaders_EXT glGetAttachedShadersEXT
#define glLinkProgram_EXT glLinkProgramEXT
#define glUseProgram_EXT glUseProgramEXT
#define glGetShaderInfoLog_EXT glGetShaderInfoLogEXT
#define glGetProgramInfoLog_EXT glGetProgramInfoLogEXT
#define glGetUniformLocation_EXT glGetUniformLocationEXT
#define glUniform1f_EXT glUniform1fEXT
#define glUniform1i_EXT glUniform1iEXT
#define glUniform2fv_EXT glUniform2fvEXT
#define glUniform3fv_EXT glUniform3fvEXT
#define glGenerateMipmap_EXT glGenerateMipmapEXT
#define glGenFramebuffers_EXT glGenFramebuffersEXT
#define glDeleteFramebuffers_EXT glDeleteFramebuffersEXT
#define glBindFramebuffer_EXT glBindFramebufferEXT
#define glGenRenderbuffers_EXT glGenRenderbuffersEXT
#define glDeleteRenderbuffers_EXT glDeleteRenderbuffersEXT
#define glBindRenderbuffer_EXT glBindRenderbufferEXT
#define glRenderbufferStorage_EXT glRenderbufferStorageEXT
#define glFramebufferRenderbuffer_EXT glFramebufferRenderbufferEXT
#define glFramebufferTexture2D_EXT glFramebufferTexture2DEXT
#define glCheckFramebufferStatus_EXT glCheckFramebufferStatusEXT
#define glGenBuffersARB_EXT glGenBuffersARBEXT
#define glBindBufferARB_EXT glBindBufferARBEXT
#define glBufferDataARB_EXT glBufferDataARBEXT
#define glDeleteBuffersARB_EXT glDeleteBuffersARBEXT
#endif

extern const uint32_t NUMBER_BYTES_PER_VERTICE_2D;
extern const uint32_t NUMBER_BYTES_PER_VERTICE_3D;
extern const uint32_t NUMBER_FLOATS_PER_VERTICE_2D;
extern const uint32_t NUMBER_FLOATS_PER_VERTICE_3D;
#endif

void gl_ortho_set(int32_t width, int32_t height);
