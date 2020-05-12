//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

// REMOVED #include "my_main.h"
#include "my_game.h"
#include "my_gl.h"
// REMOVED #include "my_time.h"
#include "my_thing_template.h"

float glapi_last_tex_right;
float glapi_last_tex_bottom;
float glapi_last_right;
float glapi_last_bottom;
static int in_2d_mode;

#define GL_ERROR_CHECK() { \
    auto errCode = glGetError();                                   \
    if (errCode == GL_NO_ERROR) {                                  \
    } else {                                                       \
        ERR("OpenGL: error at %s:%s line %u",                      \
            __FILE__, __PRETTY_FUNCTION__, __LINE__);              \
        if (errCode == GL_INVALID_ENUM) {                          \
            ERR("OpenGL: error, GL_INVALID_ENUM");                 \
        } else if (errCode == GL_INVALID_VALUE) {                  \
            ERR("OpenGL: error, GL_INVALID_VALUE");                \
        } else if (errCode == GL_INVALID_OPERATION) {              \
            ERR("OpenGL: error, GL_INVALID_OPERATION");            \
        } else if (errCode == GL_STACK_OVERFLOW) {                 \
            ERR("OpenGL: error, GL_STACK_OVERFLOW");               \
        } else if (errCode == GL_STACK_UNDERFLOW) {                \
            ERR("OpenGL: error, GL_STACK_UNDERFLOW");              \
        } else if (errCode == GL_OUT_OF_MEMORY) {                  \
            ERR("OpenGL: error, GL_OUT_OF_MEMORY");                \
        } else {                                                   \
            ERR("OpenGL: unknown error, %d", errCode);             \
        }                                                          \
    }                                                              \
}

void gl_init_2d_mode (void)
{_
    //
    // Enable Texture Worldping
    //
    CON("INIT: OpenGL enable textures");
    glEnable(GL_TEXTURE_2D);
    GL_ERROR_CHECK();

    //
    // Enable alpha blending for sprites
    //
    CON("INIT: OpenGL enable blending");
    glEnable(GL_BLEND);
    GL_ERROR_CHECK();
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    GL_ERROR_CHECK();

    //
    // Setup our viewport
    //
    CON("INIT: OpenGL enable viewport");
    glViewport(0, 0,
               game->config.outer_pix_width,
               game->config.outer_pix_height);
    GL_ERROR_CHECK();

    //
    // Reset the view
    //
    CON("INIT: OpenGL identity");
    glLoadIdentity();
    GL_ERROR_CHECK();

    gl_init_fbo();

    CON("INIT: OpenGL misc");
    glLineWidth(1.0);
    GL_ERROR_CHECK();
    glEnable(GL_LINE_SMOOTH);
    GL_ERROR_CHECK();
}

void gl_enter_2d_mode (void)
{_
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
            game->config.inner_pix_width, // right
            game->config.inner_pix_height, // bottom
            0, //top
            -1200.0,
            1200.0);
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

void gl_enter_2d_mode (int w, int h)
{_
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
            0, //top
            -1200.0,
            1200.0);
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

void
gl_leave_2d_mode (void)
{_
    if (!in_2d_mode) {
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

void gl_enter_2_5d_mode (void)
{_
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();

    glLoadIdentity();

    double scale = 15;
    glOrtho(-scale,
            scale,
            -scale * 0.7,
            scale * 0.7,
            -scale,
            scale);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glLoadIdentity();

    glRotatef(35.264f, 1.0f, 0.0f, 0.0f);
    glRotatef(-45.0f, 0.0f, 1.0f, 0.0f);

#ifdef WIREFRAME
    glPolygonMode(GL_FRONT, GL_LINE); // draw wireframe polygons
    glPolygonMode(GL_BACK, GL_LINE); // draw wireframe polygons
#endif

    glCullFace(GL_BACK); // don't draw back faces
}

void
gl_leave_2_5d_mode (void)
{_
    glDisable(GL_DEPTH_TEST);

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
}

static void gl_init_fbo_ (int fbo,
                          GLuint *render_buf_id,
                          GLuint *fbo_id,
                          GLuint *fbo_tex_id,
                          GLuint tex_width,
                          GLuint tex_height)
{_
    CON("INIT: OpenGL create FBO, size %dx%d", tex_width, tex_height);
    GL_ERROR_CHECK();

    LOG("INIT: - glGenTextures");
    if (*fbo_tex_id) {
        glDeleteTextures(1, fbo_tex_id);
        *fbo_tex_id = 0;
    }
    glGenTextures(1, fbo_tex_id);
    GL_ERROR_CHECK();

    LOG("INIT: - glBindTexture");
    glBindTexture(GL_TEXTURE_2D, *fbo_tex_id);
    GL_ERROR_CHECK();

    LOG("INIT: - glTexParameterf");
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    GL_ERROR_CHECK();
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    GL_ERROR_CHECK();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    GL_ERROR_CHECK();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    GL_ERROR_CHECK();

    LOG("INIT: - glTexImage2D");
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8,
                 tex_width, tex_height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    GL_ERROR_CHECK();

    //
    // Create a render buffer object.
    //
    if (!glFramebufferTexture2D_EXT) {
        SDL_MSG_BOX("glGenRenderbuffers_EXT is not present; fatal");
        ERR("glGenRenderbuffers_EXT is not present; fatal");
        return;
    }

    LOG("INIT: - glGenRenderbuffers_EXT");
    glGenRenderbuffers_EXT(1, render_buf_id);
    GL_ERROR_CHECK();

    LOG("INIT: - glBindRenderbuffer_EXT");
    glBindRenderbuffer_EXT(GL_RENDERBUFFER, *render_buf_id);
    GL_ERROR_CHECK();

    LOG("INIT: - glRenderbufferStorage_EXT");
    glRenderbufferStorage_EXT(GL_RENDERBUFFER, GL_DEPTH_COMPONENT,
                              tex_width, tex_height);
    GL_ERROR_CHECK();

    LOG("INIT: - glBindRenderbuffer_EXT");
    glBindRenderbuffer_EXT(GL_RENDERBUFFER, 0);
    GL_ERROR_CHECK();

    //
    // Create a frame buffer object.
    //
    LOG("INIT: - glGenFramebuffers_EXT");
    glGenFramebuffers_EXT(1, fbo_id);
    GL_ERROR_CHECK();

    LOG("INIT: - glBindFramebuffer_EXT");
    glBindFramebuffer_EXT(GL_FRAMEBUFFER, *fbo_id);
    GL_ERROR_CHECK();

    //
    // Attach the texture to FBO color attachment point
    //
    LOG("INIT: - glFramebufferTexture2D_EXT");
    glFramebufferTexture2D_EXT(GL_FRAMEBUFFER,        // 1. fbo target: GL_FRAMEBUFFER
                               GL_COLOR_ATTACHMENT0,  // 2. attachment point
                               GL_TEXTURE_2D,         // 3. tex target: GL_TEXTURE_2D
                               *fbo_tex_id,           // 4. tex ID
                               0);                    // 5. mipmap level: 0(base)
    GL_ERROR_CHECK();

    //
    // Attach the renderbuffer to depth attachment point
    //
    LOG("INIT: - glFramebufferRenderbuffer_EXT");
    glFramebufferRenderbuffer_EXT(GL_FRAMEBUFFER,      // 1. fbo target: GL_FRAMEBUFFER
                                  GL_DEPTH_ATTACHMENT, // 2. attachment point
                                  GL_RENDERBUFFER,     // 3. rbo target: GL_RENDERBUFFER
                                  *render_buf_id);     // 4. rbo ID
    GL_ERROR_CHECK();

    //
    // Check FBO status
    //
    LOG("INIT: - glCheckFramebufferStatus_EXT");
    GLenum status = glCheckFramebufferStatus_EXT(GL_FRAMEBUFFER);
    if (status && (status != GL_FRAMEBUFFER_COMPLETE)) {
        ERR("Failed to create framebuffer, error: %d", status);

#ifdef GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT
        if (status == GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT) {
            ERR("INIT: - OpenGL: GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT Not all framebuffer attachment points are framebuffer attachment complete. This means that at least one attachment point with a renderbuffer or texture attached has its attached object no longer in existence or has an attached image with a width or height of zero, or the color attachment point has a non-color-renderable image attached, or the depth attachment point has a non-depth-renderable image attached, or the stencil attachment point has a non-stencil-renderable image attached.  Color-renderable formats include GL_RGBA4, GL_RGB5_A1, and GL_RGB565. GL_DEPTH_COMPONENT16 is the only depth-renderable format. GL_STENCIL_INDEX8 is the only stencil-renderable format.");
        }
#endif
#ifdef GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS
        if (status == GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS) {
            ERR("INIT: - OpenGL: GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS Not all attached images have the same width and height.");
        }
#endif
#ifdef GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT
        if (status == GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT) {
            ERR("INIT: - OpenGL: GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT No images are attached to the framebuffer.");
        }
#endif
#ifdef GL_FRAMEBUFFER_UNSUPPORTED
        if (status == GL_FRAMEBUFFER_UNSUPPORTED) {
            ERR("INIT: - OpenGL: GL_FRAMEBUFFER_UNSUPPORTED The combination of internal formats of the attached images violates an implementation-dependent set of restrictions.");
        }
#endif
#ifdef GL_FRAMEBUFFER_UNSUPPORTED
        if (status == GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER) {
            ERR("INIT: - OpenGL: GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER");
        }
#endif
#ifdef GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER
        if (status == GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER) {
            ERR("INIT: - OpenGL: GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER");
        }
#endif
    }
    if (!status) {
        glGetError();
    }
    GL_ERROR_CHECK();

    // switch back to window-system-provided framebuffer
    LOG("INIT: - glBindFramebuffer_EXT");
    glBindFramebuffer_EXT(GL_FRAMEBUFFER, 0);
    GL_ERROR_CHECK();
}

std::array<GLuint, MAX_FBO> render_buf_id = {};
std::array<GLuint, MAX_FBO> fbo_id = {};
std::array<GLuint, MAX_FBO> fbo_tex_id = {};

void gl_init_fbo (void)
{
    int i;

    CON("INIT: OpenGL create FBOs");
    GL_ERROR_CHECK();

    for (i = 0; i < MAX_FBO; i++) {
        GLuint tex_width = game->config.inner_pix_width;
        GLuint tex_height = game->config.inner_pix_height;

        switch (i) {
            case FBO_MAP:
            case FBO_MAP_HIDDEN:
            case FBO_MAP_VISIBLE:
            case FBO_MASK1:
            case FBO_MASK2:
            case FBO_MASK3:
            case FBO_MASK4:
            case FBO_REFLECTION:
            case FBO_LIGHT:
                tex_width = game->config.inner_pix_width;
                tex_height = game->config.inner_pix_height;
                break;
            case FBO_MINIMAP:
                tex_width = MAP_WIDTH;
                tex_height = MAP_HEIGHT;
                break;
            case FBO_WID:
                //
                // Outer for the UI allows use to have more detail in
                // the logo and other things
                //
            case FBO_FINAL:
                tex_width = game->config.outer_pix_width;
                tex_height = game->config.outer_pix_height;
                break;
        }

        gl_init_fbo_(i, &render_buf_id[i], &fbo_id[i], &fbo_tex_id[i],
                     tex_width, tex_height);
        gl_enter_2d_mode(tex_width, tex_height);
        blit_fbo_bind(i);
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);
        blit_fbo_unbind();
    }

    CON("INIT: OpenGL created FBOs");
    GL_ERROR_CHECK();
}

void blit_fbo (int fbo)
{
    blit_init();
    blit(fbo_tex_id[fbo],
         0.0, 1.0, 1.0, 0.0,
         0, 0,
         game->config.inner_pix_width,
         game->config.inner_pix_height);
    blit_flush();
}

void blit_fbo_outer (int fbo)
{
    blit_init();
    blit(fbo_tex_id[fbo],
         0.0, 1.0, 1.0, 0.0,
         0, 0,
         game->config.outer_pix_width,
         game->config.outer_pix_height);
    blit_flush();
}

void blit_fbo_bind (int fbo)
{
    glBindFramebuffer_EXT(GL_FRAMEBUFFER, fbo_id[fbo]);
}

void blit_fbo_unbind (void)
{
    glBindFramebuffer_EXT(GL_FRAMEBUFFER, 0);
}

//
// x and y per element.
//
#define NUMBER_DIMENSIONS_PER_COORD_2D 2
#define NUMBER_DIMENSIONS_PER_COORD_3D 3

//
// r,g,b,a per element
//
#define NUMBER_COMPONENTS_PER_COLOR 4

uint32_t NUMBER_BYTES_PER_VERTICE_2D = sizeof(GLfloat) *
                                       NUMBER_DIMENSIONS_PER_COORD_2D +
                                       sizeof(GLfloat) *
                                       NUMBER_DIMENSIONS_PER_COORD_2D +
                                       sizeof(GLfloat) *
                                       NUMBER_COMPONENTS_PER_COLOR;

uint32_t NUMBER_BYTES_PER_VERTICE_3D = sizeof(GLfloat) *
                                       NUMBER_DIMENSIONS_PER_COORD_2D +
                                       sizeof(GLfloat) *
                                       NUMBER_DIMENSIONS_PER_COORD_3D +
                                       sizeof(GLfloat) *
                                       NUMBER_COMPONENTS_PER_COLOR;

uint32_t NUMBER_FLOATS_PER_VERTICE_2D = NUMBER_BYTES_PER_VERTICE_2D / sizeof(float);
uint32_t NUMBER_FLOATS_PER_VERTICE_3D = NUMBER_BYTES_PER_VERTICE_3D / sizeof(float);

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
int buf_tex;

void blit_init (void)
{_
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

    gl_array_buf = (__typeof__(gl_array_buf))
                    myzalloc(gl_array_size_required, "GL xy buffer");

    //
    // Make the end a bit smaller so we have plenty of headroom.
    //
    gl_array_buf_end =
            (__typeof__(gl_array_buf_end))
                ((char *)gl_array_buf) +
                ((gl_array_size_required * 2) / 3);

    bufp = gl_array_buf;
    bufp_end = gl_array_buf_end;
}

void blit_fini (void)
{_
    if (gl_array_buf) {
        myfree(gl_array_buf);
        gl_array_buf = 0;
    }
}

void blit_flush (void)
{_
    if (gl_array_buf == bufp) {
        return;
    }

    //
    // Display all the tiles selected above in one blast.
    //
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    static long nvertices;

    nvertices = ((char*)bufp - (char*)gl_array_buf) /
                    NUMBER_BYTES_PER_VERTICE_2D;

    glBindTexture(GL_TEXTURE_2D, buf_tex);

    glTexCoordPointer(
        NUMBER_DIMENSIONS_PER_COORD_2D, // (u,v)
        GL_FLOAT,
        NUMBER_BYTES_PER_VERTICE_2D,
        gl_array_buf);

    glVertexPointer(
        NUMBER_DIMENSIONS_PER_COORD_2D, // (x,y)
        GL_FLOAT,
        NUMBER_BYTES_PER_VERTICE_2D,
        ((char*)gl_array_buf) +
            sizeof(GLfloat) *        // skip (u,v)
            NUMBER_DIMENSIONS_PER_COORD_2D);

    glColorPointer(
        NUMBER_COMPONENTS_PER_COLOR, // (r,g,b,a)
        GL_FLOAT,
        NUMBER_BYTES_PER_VERTICE_2D,
        ((char*)gl_array_buf) +
            sizeof(GLfloat) *        // skip (x,y)
            NUMBER_DIMENSIONS_PER_COORD_2D +
            sizeof(GLfloat) *        // skip (u,v)
            NUMBER_DIMENSIONS_PER_COORD_2D);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, (GLsizei) nvertices);

    glBindTexture(GL_TEXTURE_2D, 0);

    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

    blit_init();
}

void blit_flush_3d (void)
{_
    if (gl_array_buf == bufp) {
        return;
    }

    //
    // Display all the tiles selected above in one blast.
    //
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    static long nvertices;

    nvertices = ((char*)bufp - (char*)gl_array_buf) /
                    NUMBER_BYTES_PER_VERTICE_3D;

    glBindTexture(GL_TEXTURE_2D, buf_tex);

    glTexCoordPointer(
        NUMBER_DIMENSIONS_PER_COORD_2D, // (u,v)
        GL_FLOAT,
        NUMBER_BYTES_PER_VERTICE_3D,
        gl_array_buf);

    glVertexPointer(
        NUMBER_DIMENSIONS_PER_COORD_3D, // (x,y)
        GL_FLOAT,
        NUMBER_BYTES_PER_VERTICE_3D,
        ((char*)gl_array_buf) +
            sizeof(GLfloat) *        // skip (u,v)
            NUMBER_DIMENSIONS_PER_COORD_2D);

    glColorPointer(
        NUMBER_COMPONENTS_PER_COLOR, // (r,g,b,a)
        GL_FLOAT,
        NUMBER_BYTES_PER_VERTICE_3D,
        ((char*)gl_array_buf) +
            sizeof(GLfloat) *        // skip (x,y)
            NUMBER_DIMENSIONS_PER_COORD_3D +
            sizeof(GLfloat) *        // skip (u,v)
            NUMBER_DIMENSIONS_PER_COORD_2D);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, (GLsizei) nvertices);

    glBindTexture(GL_TEXTURE_2D, 0);

    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

    blit_init();
}

void blit_flush_colored_triangles (void)
{_
    if (gl_array_buf == bufp) {
        return;
    }

    //
    // Display all the tiles selected above in one blast.
    //
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    static long nvertices;

    static const GLsizei stride =
                        sizeof(GLfloat) *
                        NUMBER_DIMENSIONS_PER_COORD_2D +
                        sizeof(GLfloat) *
                        NUMBER_COMPONENTS_PER_COLOR;

    nvertices = ((char*)bufp - (char*)gl_array_buf) / stride;

    glVertexPointer(
        NUMBER_DIMENSIONS_PER_COORD_2D, // (x,y)
        GL_FLOAT,
        stride,
        gl_array_buf);

    glColorPointer(
        NUMBER_COMPONENTS_PER_COLOR, // (r,g,b,a)
        GL_FLOAT,
        stride,
        ((char*)gl_array_buf) +
            sizeof(GLfloat) *        // skip (x,y)
            NUMBER_DIMENSIONS_PER_COORD_2D);

    glDrawArrays(GL_TRIANGLES, 0, (GLsizei) nvertices);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

    blit_init();
}

void blit_flush_triangle_fan (void)
{_
    blit_flush_triangle_fan(gl_array_buf, bufp);
}

void blit_flush_triangle_fan (float *b, float *e)
{_
    //
    // Display all the tiles selected above in one blast.
    //
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    static long nvertices;

    static const GLsizei stride =
                        sizeof(GLfloat) *
                        NUMBER_DIMENSIONS_PER_COORD_2D +
                        sizeof(GLfloat) *
                        NUMBER_COMPONENTS_PER_COLOR;

    nvertices = ((char*)e - (char*)b) / stride;

    glVertexPointer(
        NUMBER_DIMENSIONS_PER_COORD_2D, // (x,y)
        GL_FLOAT,
        stride,
        b);

    glColorPointer(
        NUMBER_COMPONENTS_PER_COLOR, // (r,g,b,a)
        GL_FLOAT,
        stride,
        ((char*)b) +
            sizeof(GLfloat) *        // skip (x,y)
            NUMBER_DIMENSIONS_PER_COORD_2D);

    glDrawArrays(GL_TRIANGLE_FAN, 0, (GLsizei) nvertices);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

    blit_init();
}

void blit_flush_tex_triangle_fan (void)
{
    if (gl_array_buf == bufp) {
        return;
    }

    //
    // Display all the tiles selected above in one blast.
    //
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    static long nvertices;

    nvertices = ((char*)bufp - (char*)gl_array_buf) /
                    NUMBER_BYTES_PER_VERTICE_2D;

    glBindTexture(GL_TEXTURE_2D, buf_tex);

    glTexCoordPointer(
        NUMBER_DIMENSIONS_PER_COORD_2D, // (u,v)
        GL_FLOAT,
        NUMBER_BYTES_PER_VERTICE_2D,
        gl_array_buf);

    glVertexPointer(
        NUMBER_DIMENSIONS_PER_COORD_2D, // (x,y)
        GL_FLOAT,
        NUMBER_BYTES_PER_VERTICE_2D,
        ((char*)gl_array_buf) +
            sizeof(GLfloat) *        // skip (x,y)
            NUMBER_DIMENSIONS_PER_COORD_2D);

    glColorPointer(
        NUMBER_COMPONENTS_PER_COLOR, // (r,g,b,a)
        GL_FLOAT,
        NUMBER_BYTES_PER_VERTICE_2D,
        ((char*)gl_array_buf) +
            sizeof(GLfloat) *        // skip (x,y)
            NUMBER_DIMENSIONS_PER_COORD_2D +
            sizeof(GLfloat) *        // skip (u,v)
            NUMBER_DIMENSIONS_PER_COORD_2D);

    glDrawArrays(GL_TRIANGLE_FAN, 0, (GLsizei) nvertices);

    glBindTexture(GL_TEXTURE_2D, 0);

    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

    blit_init();
}

void blit_flush_triangle_strip (void)
{
    if (gl_array_buf == bufp) {
        return;
    }

    //
    // Display all the tiles selected above in one blast.
    //
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    static long nvertices;

    static const GLsizei stride =
                        sizeof(GLfloat) *
                        NUMBER_DIMENSIONS_PER_COORD_2D +
                        sizeof(GLfloat) *
                        NUMBER_COMPONENTS_PER_COLOR;

    nvertices = ((char*)bufp - (char*)gl_array_buf) / stride;

    glVertexPointer(
        NUMBER_DIMENSIONS_PER_COORD_2D, // (x,y)
        GL_FLOAT,
        stride,
        gl_array_buf);

    glColorPointer(
        NUMBER_COMPONENTS_PER_COLOR, // (r,g,b,a)
        GL_FLOAT,
        stride,
        ((char*)gl_array_buf) +
            sizeof(GLfloat) *        // skip (x,y)
            NUMBER_DIMENSIONS_PER_COORD_2D);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, (GLsizei) nvertices);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

    blit_init();
}

void blit_flush_triangles (void)
{
    if (gl_array_buf == bufp) {
        return;
    }

    //
    // Display all the tiles selected above in one blast.
    //
    glEnableClientState(GL_VERTEX_ARRAY);

    static long number_bytes_per_vertice_2d =
                    sizeof(GLfloat) * NUMBER_DIMENSIONS_PER_COORD_2D;

    long nvertices = ((char*)bufp - (char*)gl_array_buf) /
                    number_bytes_per_vertice_2d;

    glBindTexture(GL_TEXTURE_2D, 0);

    glVertexPointer(
        NUMBER_DIMENSIONS_PER_COORD_2D, // (x,y)
        GL_FLOAT,
        0, // stride
        ((char*)gl_array_buf));

    glDrawArrays(GL_TRIANGLES, 0, (GLsizei) nvertices);

    glDisableClientState(GL_VERTEX_ARRAY);

    blit_init();
}

void gl_blitquad (float left, float top, float right, float bottom)
{
    GLfloat xy[4*2];
    GLfloat *xyp = xy;

    Vertex2f(left, top);
    Vertex2f(right, top);
    Vertex2f(left, bottom);
    Vertex2f(right, bottom);

    glEnableClientState(GL_VERTEX_ARRAY);

    glVertexPointer(2, GL_FLOAT, 0, xy);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glDisableClientState(GL_VERTEX_ARRAY);
}

void gl_blitsquare (float left, float top, float right, float bottom)
{
    GLfloat xy[4*2];
    GLfloat *xyp = xy;

    Vertex2f(left, top);
    Vertex2f(right, top);
    Vertex2f(right, bottom);
    Vertex2f(left, bottom);

    glEnableClientState(GL_VERTEX_ARRAY);

    glVertexPointer(2, GL_FLOAT, 0, xy);
    glDrawArrays(GL_LINE_LOOP, 0, 4);

    glDisableClientState(GL_VERTEX_ARRAY);
}

void gl_blitline (float left, float top, float right, float bottom)
{
    GLfloat xy[2*2];
    GLfloat *xyp = xy;

    Vertex2f(left, top);
    Vertex2f(right, bottom);

    glEnableClientState(GL_VERTEX_ARRAY);

    glVertexPointer(2, GL_FLOAT, 0, xy);
    glDrawArrays(GL_LINES, 0, 2);

    glDisableClientState(GL_VERTEX_ARRAY);
}

#ifdef _WIN32

HDC hDC;
HGLRC hGLRC;
HPALETTE hPalette;

const char g_szClassName[] = "myWindowClass";

PFNGLCREATEPROGRAMPROC glCreateProgram_EXT;
PFNGLDELETEPROGRAMPROC glDeleteProgram_EXT;
PFNGLISPROGRAMPROC glIsProgram_EXT;
PFNGLCREATESHADERPROC glCreateShader_EXT;
PFNGLDELETESHADERPROC glDeleteShader_EXT;
PFNGLSHADERSOURCEPROC glShaderSource_EXT;
PFNGLCOMPILESHADERPROC glCompileShader_EXT;
PFNGLATTACHSHADERPROC glAttachShader_EXT;
PFNGLDETACHSHADERPROC glDetachShader_EXT;
PFNGLGETATTACHEDSHADERSPROC glGetAttachedShaders_EXT;
PFNGLLINKPROGRAMPROC glLinkProgram_EXT;
PFNGLUSEPROGRAMPROC glUseProgram_EXT;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog_EXT;
PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog_EXT;
PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation_EXT;
PFNGLUNIFORM1FPROC glUniform1f_EXT;
PFNGLUNIFORM1IPROC glUniform1i_EXT;
PFNGLUNIFORM2FVPROC glUniform2fv_EXT;
PFNGLUNIFORM3FVPROC glUniform3fv_EXT;
PFNGLGENERATEMIPMAPPROC glGenerateMipmap_EXT;
PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers_EXT;
PFNGLDELETEFRAMEBUFFERSPROC glDeleteFramebuffers_EXT;
PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer_EXT;
PFNGLGENRENDERBUFFERSPROC glGenRenderbuffers_EXT;
PFNGLDELETERENDERBUFFERSPROC glDeleteRenderbuffers_EXT;
PFNGLBINDRENDERBUFFERPROC glBindRenderbuffer_EXT;
PFNGLRENDERBUFFERSTORAGEPROC glRenderbufferStorage_EXT;
PFNGLFRAMEBUFFERRENDERBUFFERPROC glFramebufferRenderbuffer_EXT;
PFNGLFRAMEBUFFERTEXTURE2DPROC glFramebufferTexture2D_EXT;
PFNGLCHECKFRAMEBUFFERSTATUSPROC glCheckFramebufferStatus_EXT;
PFNGLGENBUFFERSARBPROC glGenBuffersARB_EXT;
PFNGLBINDBUFFERARBPROC glBindBufferARB_EXT;
PFNGLBUFFERDATAARBPROC glBufferDataARB_EXT;
PFNGLDELETEBUFFERSARBPROC glDeleteBuffersARB_EXT;

static void gl_ext_load (void)
{_
    glCreateProgram_EXT = (__typeof__(glCreateProgram_EXT))
        wglGetProcAddress("glCreateProgram");
    if (!glCreateProgram_EXT) {
        CON("INIT: - glCreateProgram_EXT - NOT present");
    } else {
        CON("INIT: - glCreateProgram_EXT - present");
    }

    glDeleteProgram_EXT =
        (__typeof__(glDeleteProgram_EXT)) wglGetProcAddress("glDeleteProgram");
    if (!glDeleteProgram_EXT) {
        CON("INIT: - glDeleteProgram_EXT - NOT present");
    } else {
        CON("INIT: - glDeleteProgram_EXT - present");
    }

    glIsProgram_EXT =
        (__typeof__(glIsProgram_EXT)) wglGetProcAddress("glIsProgram");
    if (!glIsProgram_EXT) {
        CON("INIT: - glIsProgram_EXT - NOT present");
    } else {
        CON("INIT: - glIsProgram_EXT - present");
    }

    glCreateShader_EXT =
        (__typeof__(glCreateShader_EXT)) wglGetProcAddress("glCreateShader");
    if (!glCreateShader_EXT) {
        CON("INIT: - glCreateShader_EXT - NOT present");
    } else {
        CON("INIT: - glCreateShader_EXT - present");
    }

    glDeleteShader_EXT =
        (__typeof__(glDeleteShader_EXT)) wglGetProcAddress("glDeleteShader");
    if (!glDeleteShader_EXT) {
        CON("INIT: - glDeleteShader_EXT - NOT present");
    } else {
        CON("INIT: - glDeleteShader_EXT - present");
    }

    glShaderSource_EXT =
        (__typeof__(glShaderSource_EXT)) wglGetProcAddress("glShaderSource");
    if (!glShaderSource_EXT) {
        CON("INIT: - glShaderSource_EXT - NOT present");
    } else {
        CON("INIT: - glShaderSource_EXT - present");
    }

    glCompileShader_EXT =
        (__typeof__(glCompileShader_EXT)) wglGetProcAddress("glCompileShader");
    if (!glCompileShader_EXT) {
        CON("INIT: - glCompileShader_EXT - NOT present");
    } else {
        CON("INIT: - glCompileShader_EXT - present");
    }

    glAttachShader_EXT =
        (__typeof__(glAttachShader_EXT)) wglGetProcAddress("glAttachShader");
    if (!glAttachShader_EXT) {
        CON("INIT: - glAttachShader_EXT - NOT present");
    } else {
        CON("INIT: - glAttachShader_EXT - present");
    }

    glDetachShader_EXT =
        (__typeof__(glDetachShader_EXT)) wglGetProcAddress("glDetachShader");
    if (!glDetachShader_EXT) {
        CON("INIT: - glDetachShader_EXT - NOT present");
    } else {
        CON("INIT: - glDetachShader_EXT - present");
    }

    glGetAttachedShaders_EXT =
        (__typeof__(glGetAttachedShaders_EXT)) wglGetProcAddress("glGetAttachedShaders");
    if (!glGetAttachedShaders_EXT) {
        CON("INIT: - glGetAttachedShaders_EXT - NOT present");
    } else {
        CON("INIT: - glGetAttachedShaders_EXT - present");
    }

    glLinkProgram_EXT =
        (__typeof__(glLinkProgram_EXT)) wglGetProcAddress("glLinkProgram");
    if (!glLinkProgram_EXT) {
        CON("INIT: - glLinkProgram_EXT - NOT present");
    } else {
        CON("INIT: - glLinkProgram_EXT - present");
    }

    glUseProgram_EXT =
        (__typeof__(glUseProgram_EXT)) wglGetProcAddress("glUseProgram");
    if (!glUseProgram_EXT) {
        CON("INIT: - glUseProgram_EXT - NOT present");
    } else {
        CON("INIT: - glUseProgram_EXT - present");
    }

    glGetShaderInfoLog_EXT =
        (__typeof__(glGetShaderInfoLog_EXT)) wglGetProcAddress("glGetShaderInfoLog");
    if (!glGetShaderInfoLog_EXT) {
        CON("INIT: - glGetShaderInfoLog_EXT - NOT present");
    } else {
        CON("INIT: - glGetShaderInfoLog_EXT - present");
    }

    glGetProgramInfoLog_EXT =
        (__typeof__(glGetProgramInfoLog_EXT)) wglGetProcAddress("glGetProgramInfoLog");
    if (!glGetProgramInfoLog_EXT) {
        CON("INIT: - glGetProgramInfoLog_EXT - NOT present");
    } else {
        CON("INIT: - glGetProgramInfoLog_EXT - present");
    }

    glGetUniformLocation_EXT =
        (__typeof__(glGetUniformLocation_EXT)) wglGetProcAddress("glGetUniformLocation");
    if (!glGetUniformLocation_EXT) {
        CON("INIT: - glGetUniformLocation_EXT - NOT present");
    } else {
        CON("INIT: - glGetUniformLocation_EXT - present");
    }

    glUniform1f_EXT =
        (__typeof__(glUniform1f_EXT)) wglGetProcAddress("glUniform1f");
    if (!glUniform1f_EXT) {
        CON("INIT: - glUniform1f_EXT - NOT present");
    } else {
        CON("INIT: - glUniform1f_EXT - present");
    }

    glUniform1i_EXT =
        (__typeof__(glUniform1i_EXT)) wglGetProcAddress("glUniform1i");
    if (!glUniform1i_EXT) {
        CON("INIT: - glUniform1i_EXT - NOT present");
    } else {
        CON("INIT: - glUniform1i_EXT - present");
    }

    glUniform2fv_EXT =
        (__typeof__(glUniform2fv_EXT)) wglGetProcAddress("glUniform2fv");
    if (!glUniform2fv_EXT) {
        CON("INIT: - glUniform2fv_EXT - NOT present");
    } else {
        CON("INIT: - glUniform2fv_EXT - present");
    }

    glUniform3fv_EXT =
        (__typeof__(glUniform3fv_EXT)) wglGetProcAddress("glUniform3fv");
    if (!glUniform3fv_EXT) {
        CON("INIT: - glUniform3fv_EXT - NOT present");
    } else {
        CON("INIT: - glUniform3fv_EXT - present");
    }

    glGenerateMipmap_EXT =
        (__typeof__(glGenerateMipmap_EXT)) wglGetProcAddress("glGenerateMipmap");
    if (!glGenerateMipmap_EXT) {
        CON("INIT: - glGenerateMipmap_EXT - NOT present");
    } else {
        CON("INIT: - glGenerateMipmap_EXT - present");
    }

    glGenFramebuffers_EXT =
        (__typeof__(glGenFramebuffers_EXT)) wglGetProcAddress("glGenFramebuffers");
    if (!glGenFramebuffers_EXT) {
        CON("INIT: - glGenFramebuffers_EXT - NOT present");
    } else {
        CON("INIT: - glGenFramebuffers_EXT - present");
    }

    glDeleteFramebuffers_EXT =
        (__typeof__(glDeleteFramebuffers_EXT)) wglGetProcAddress("glDeleteFramebuffers");
    if (!glDeleteFramebuffers_EXT) {
        CON("INIT: - glDeleteFramebuffers_EXT - NOT present");
    } else {
        CON("INIT: - glDeleteFramebuffers_EXT - present");
    }

    glBindFramebuffer_EXT =
        (__typeof__(glBindFramebuffer_EXT)) wglGetProcAddress("glBindFramebuffer");
    if (!glBindFramebuffer_EXT) {
        CON("INIT: - glBindFramebuffer_EXT - NOT present");
    } else {
        CON("INIT: - glBindFramebuffer_EXT - present");
    }

    glGenRenderbuffers_EXT =
        (__typeof__(glGenRenderbuffers_EXT)) wglGetProcAddress("glGenRenderbuffers");
    if (!glGenRenderbuffers_EXT) {
        CON("INIT: - glGenRenderbuffers_EXT - NOT present");
    } else {
        CON("INIT: - glGenRenderbuffers_EXT - present");
    }

    glDeleteRenderbuffers_EXT =
        (__typeof__(glDeleteRenderbuffers_EXT)) wglGetProcAddress("glDeleteRenderbuffers");
    if (!glDeleteRenderbuffers_EXT) {
        CON("INIT: - glDeleteRenderbuffers_EXT - NOT present");
    } else {
        CON("INIT: - glDeleteRenderbuffers_EXT - present");
    }

    glBindRenderbuffer_EXT =
        (__typeof__(glBindRenderbuffer_EXT)) wglGetProcAddress("glBindRenderbuffer");
    if (!glBindRenderbuffer_EXT) {
        CON("INIT: - glBindRenderbuffer_EXT - NOT present");
    } else {
        CON("INIT: - glBindRenderbuffer_EXT - present");
    }

    glRenderbufferStorage_EXT =
        (__typeof__(glRenderbufferStorage_EXT)) wglGetProcAddress("glRenderbufferStorage");
    if (!glRenderbufferStorage_EXT) {
        CON("INIT: - glRenderbufferStorage_EXT - NOT present");
    } else {
        CON("INIT: - glRenderbufferStorage_EXT - present");
    }

    glFramebufferRenderbuffer_EXT =
        (__typeof__(glFramebufferRenderbuffer_EXT)) wglGetProcAddress("glFramebufferRenderbuffer");
    if (!glFramebufferRenderbuffer_EXT) {
        CON("INIT: - glFramebufferRenderbuffer_EXT - NOT present");
    } else {
        CON("INIT: - glFramebufferRenderbuffer_EXT - present");
    }

    glCheckFramebufferStatus_EXT =
        (__typeof__(glCheckFramebufferStatus_EXT)) wglGetProcAddress("glFramebufferRenderbuffer");
    if (!glCheckFramebufferStatus_EXT) {
        CON("INIT: - glCheckFramebufferStatus_EXT - NOT present");
    } else {
        CON("INIT: - glCheckFramebufferStatus_EXT - present");
    }

    glFramebufferTexture2D_EXT =
        (__typeof__(glFramebufferTexture2D_EXT)) wglGetProcAddress("glFramebufferTexture2D");
    if (!glFramebufferTexture2D_EXT) {
        CON("INIT: - glFramebufferTexture2D_EXT - NOT present");
    } else {
        CON("INIT: - glFramebufferTexture2D_EXT - present");
    }

    glGenBuffersARB_EXT =
        (__typeof__(glGenBuffersARB_EXT)) wglGetProcAddress("glGenBuffersARB");
    if (!glGenBuffersARB_EXT) {
        CON("INIT: - glGenBuffersARB_EXT - NOT present");
    } else {
        CON("INIT: - glGenBuffersARB_EXT - present");
    }

    glBindBufferARB_EXT =
        (__typeof__(glBindBufferARB_EXT)) wglGetProcAddress("glBindBufferARB");
    if (!glBindBufferARB_EXT) {
        CON("INIT: - glBindBufferARB_EXT - NOT present");
    } else {
        CON("INIT: - glBindBufferARB_EXT - present");
    }

    glDeleteBuffersARB_EXT =
        (__typeof__(glDeleteBuffersARB_EXT)) wglGetProcAddress("glDeleteBuffersARB");
    if (!glDeleteBuffersARB_EXT) {
        CON("INIT: - glDeleteBuffersARB_EXT - NOT present");
    } else {
        CON("INIT: - glDeleteBuffersARB_EXT - present");
    }

    glDeleteBuffersARB_EXT =
        (__typeof__(glDeleteBuffersARB_EXT)) wglGetProcAddress("glDeleteBuffersARB");
    if (!glDeleteBuffersARB_EXT) {
        CON("INIT: - glDeleteBuffersARB_EXT - NOT present");
    } else {
        CON("INIT: - glDeleteBuffersARB_EXT - present");
    }
}

static void
setupPixelFormat(HDC hDC)
{_
    PIXELFORMATDESCRIPTOR pfd = {
        sizeof(PIXELFORMATDESCRIPTOR),  // size
        1,                              // version
        PFD_SUPPORT_OPENGL |
        PFD_DRAW_TO_WINDOW |
        PFD_DOUBLEBUFFER,               // support double-buffering
        PFD_TYPE_RGBA,                  // color type
        16,                             // prefered color depth
        0, 0, 0, 0, 0, 0,               // color bits (ignored)
        0,                              // no alpha buffer
        0,                              // alpha bits (ignored)
        0,                              // no accumulation buffer
        0, 0, 0, 0,                     // accum bits (ignored)
        16,                             // depth buffer
        0,                              // no stencil buffer
        0,                              // no auxiliary buffers
        PFD_MAIN_PLANE,                 // main layer
        0,                              // reserved
        0, 0, 0,                        // no layer, visible, damage masks
    };
    int pixelFormat;

    pixelFormat = ChoosePixelFormat(hDC, &pfd);
    if (pixelFormat == 0) {
        MessageBox(WindowFromDC(hDC), "ChoosePixelFormat failed.", "Error",
                MB_ICONERROR | MB_OK);
        exit(1);
    }

    if (SetPixelFormat(hDC, pixelFormat, &pfd) != TRUE) {
        MessageBox(WindowFromDC(hDC), "SetPixelFormat failed.", "Error",
                MB_ICONERROR | MB_OK);
        exit(1);
    }
}

static void
setupPalette(HDC hDC)
{_
    int pixelFormat = GetPixelFormat(hDC);
    PIXELFORMATDESCRIPTOR pfd;
    LOGPALETTE* pPal;
    int paletteSize;

    DescribePixelFormat(hDC, pixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

    if (pfd.dwFlags & PFD_NEED_PALETTE) {
        paletteSize = 1 << pfd.cColorBits;
    } else {
        return;
    }

    pPal = (LOGPALETTE*)
        malloc(sizeof(LOGPALETTE) + paletteSize * sizeof(PALETTEENTRY));
    pPal->palVersion = 0x300;
    pPal->palNumEntries = paletteSize;

    // build a simple RGB color palette */
    {
        int redMask = (1 << pfd.cRedBits) - 1;
        int greenMask = (1 << pfd.cGreenBits) - 1;
        int blueMask = (1 << pfd.cBlueBits) - 1;
        int i;

        for (i=0; i<paletteSize; ++i) {
            pPal->palPalEntry[i].peRed =
                    (((i >> pfd.cRedShift) & redMask) * 255) / redMask;
            pPal->palPalEntry[i].peGreen =
                    (((i >> pfd.cGreenShift) & greenMask) * 255) / greenMask;
            pPal->palPalEntry[i].peBlue =
                    (((i >> pfd.cBlueShift) & blueMask) * 255) / blueMask;
            pPal->palPalEntry[i].peFlags = 0;
        }
    }

    hPalette = CreatePalette(pPal);
    free(pPal);

    if (hPalette) {
        SelectPalette(hDC, hPalette, FALSE);
        RealizePalette(hDC);
    }
}

static LRESULT APIENTRY
WndProc(
    HWND hWnd,
    UINT message,
    WPARAM wParam,
    LPARAM lParam)
{_
    return DefWindowProc(hWnd, message, wParam, lParam);
}

void gl_ext_init (void)
{_
    WNDCLASSEX wc;
    HWND hwnd;

    CON("INIT: OpenGL extensions");

    CON("INIT: - GetModuleHandle");
    HINSTANCE hInstance = GetModuleHandle(0);

    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = g_szClassName;
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    CON("INIT: - RegisterClassEx");
    if (!RegisterClassEx(&wc)) {
        MessageBox(NULL, "Window Registration Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return;
    }

    CON("INIT: - CreateWindowEx");
    hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,
                          g_szClassName,
                          "zorbash startup",
                          WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT, CW_USEDEFAULT, 240, 120,
                          NULL, NULL, hInstance, NULL);

    if (hwnd == NULL) {
        MessageBox(NULL, "Window Creation Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
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
        wglMakeCurrent(NULL, NULL);
        wglDeleteContext(hGLRC);
    }

    if (hPalette) {
        DeleteObject(hPalette);
    }

    ReleaseDC(hwnd, hDC);
}
#else
void gl_ext_init (void)
{_
}
#endif

//
// Blits a whole tile. Y co-ords are inverted.
//
void tile_blit_outline (const Tilep &tile, const spoint &tl, const spoint &br,
                        const color &c)
{
    float x1, x2, y1, y2;

    if (!tile) {
        return;
    }

    x1 = tile->x1;
    x2 = tile->x2;
    y1 = tile->y1;
    y2 = tile->y2;

    color outline = {0,0,0,0};
    outline.a = c.a / 2;
    glcolor(outline);

    const float dx = game->config.one_pixel_width;
    const float dy = game->config.one_pixel_height;

    blit(tile->gl_binding(), x1, y2, x2, y1,
         tl.x - dx, br.y - dy, br.x - dx, tl.y - dy);
    blit(tile->gl_binding(), x1, y2, x2, y1,
         tl.x + dx, br.y + dy, br.x + dx, tl.y + dy);
    blit(tile->gl_binding(), x1, y2, x2, y1,
         tl.x - dx, br.y + dy, br.x - dx, tl.y + dy);
    blit(tile->gl_binding(), x1, y2, x2, y1,
         tl.x + dx, br.y - dy, br.x + dx, tl.y - dy);
    blit(tile->gl_binding(), x1, y2, x2, y1,
         tl.x + dx, br.y, br.x + dx, tl.y);
    blit(tile->gl_binding(), x1, y2, x2, y1,
         tl.x - dx, br.y, br.x - dx, tl.y);
    blit(tile->gl_binding(), x1, y2, x2, y1,
         tl.x, br.y + dy, br.x, tl.y + dy);
    blit(tile->gl_binding(), x1, y2, x2, y1,
         tl.x, br.y - dy, br.x, tl.y - dy);

    glcolor(c);
    blit(tile->gl_binding(), x1, y2, x2, y1, tl.x, br.y, br.x, tl.y);
}

void tile_blit_outline (uint16_t index, const spoint &tl, const spoint &br,
                        const color &c)
{
    tile_blit_outline(tile_index_to_tile(index), tl, br, c);
}

//
// Blits a whole tile. Y co-ords are inverted.
//
void tile_blit_outline_section (const Tilep &tile,
                                const fpoint &tile_tl,
                                const fpoint &tile_br,
                                const spoint &tl,
                                const spoint &br,
                                float scale)
{
    float x1, x2, y1, y2;

    if (!tile) {
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

    blit(tile->gl_binding(), x1, y2, x2, y1,
         tl.x - dx, br.y - dy, br.x - dx, tl.y - dy);
    blit(tile->gl_binding(), x1, y2, x2, y1,
         tl.x + dx, br.y + dy, br.x + dx, tl.y + dy);
    blit(tile->gl_binding(), x1, y2, x2, y1,
         tl.x - dx, br.y + dy, br.x - dx, tl.y + dy);
    blit(tile->gl_binding(), x1, y2, x2, y1,
         tl.x + dx, br.y - dy, br.x + dx, tl.y - dy);
    blit(tile->gl_binding(), x1, y2, x2, y1,
         tl.x + dx, br.y, br.x + dx, tl.y);
    blit(tile->gl_binding(), x1, y2, x2, y1,
         tl.x - dx, br.y, br.x - dx, tl.y);
    blit(tile->gl_binding(), x1, y2, x2, y1,
         tl.x, br.y + dy, br.x, tl.y + dy);
    blit(tile->gl_binding(), x1, y2, x2, y1,
         tl.x, br.y - dy, br.x, tl.y - dy);

    glcolor(WHITE);
    blit(tile->gl_binding(), x1, y2, x2, y1, tl.x, br.y, br.x, tl.y);
}

void tile_blit_outline_section (const Tilep &tile,
                                const fpoint &tile_tl,
                                const fpoint &tile_br,
                                const spoint &tl, 
                                const spoint &br)
{
    tile_blit_outline_section (tile, tile_tl, tile_br, tl, br, 0.75);
}

void tile_blit_outline_section (uint16_t index,
                                const fpoint &tile_tl,
                                const fpoint &tile_br,
                                const spoint &tl, 
                                const spoint &br)
{
    tile_blit_outline_section(tile_index_to_tile(index),
                              tile_tl, tile_br, tl, br, 0.75);
}

void tile_blit (const Tilep &tile, const spoint &tl, const spoint &br)
{
    float x1, x2, y1, y2;

    //
    // Only some walls have deco tiles, so the pointer is left null for
    // those that do not.
    //
    if (!tile) {
        return;
    }

    x1 = tile->x1;
    x2 = tile->x2;
    y1 = tile->y1;
    y2 = tile->y2;

    blit(tile->gl_binding(), x1, y2, x2, y1, tl.x, br.y, br.x, tl.y);
}

void tile_blit (const Tilep &tile,
                const spoint &tl,
                const spoint &tr,
                const spoint &bl,
                const spoint &br)
{
    float x1, x2, y1, y2;

    //
    // Only some walls have deco tiles, so the pointer is left null for
    // those that do not.
    //
    if (!tile) {
        return;
    }

    x1 = tile->x1;
    x2 = tile->x2;
    y1 = tile->y1;
    y2 = tile->y2;

    blit(tile->gl_binding(), x1, y2, x2, y1, tl, tr, bl, br);
}

void tile_blit (uint16_t index, const spoint &tl, const spoint &br)
{
    tile_blit(tile_index_to_tile(index), tl, br);
}

void tile_blit_section (const Tilep &tile,
                        const spoint &tile_tl, const spoint &tile_br,
                        const spoint &tl, const spoint &br)
{
    float x1, x2, y1, y2;

    //
    // Only some walls have deco tiles, so the pointer is left null for
    // those that do not.
    //
    if (!tile) {
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

void tile_blit_section (uint16_t index,
                        const spoint &tile_tl, const spoint &tile_br,
                        const spoint &tl, const spoint &br)
{
    tile_blit_section(tile_index_to_tile(index), tile_tl, tile_br, tl, br);
}

void tile_blit_section_colored (const Tilep &tile,
                                const fpoint &tile_tl, const fpoint &tile_br,
                                const spoint &tl, const spoint &br,
                                color color_bl,
                                color color_br,
                                color color_tl,
                                color color_tr)
{
    float x1, x2, y1, y2;

    //
    // Only some walls have deco tiles, so the pointer is left null for
    // those that do not.
    //
    if (!tile) {
        return;
    }

    float tw = tile->x2 - tile->x1;
    float th = tile->y2 - tile->y1;

    x1 = tile->x1 + tile_tl.x * tw;
    x2 = tile->x1 + tile_br.x * tw;
    y1 = tile->y1 + tile_tl.y * th;
    y2 = tile->y1 + tile_br.y * th;

    blit_colored(tile->gl_binding(), x1, y2, x2, y1,
                 tl.x, br.y, br.x, tl.y,
                 color_bl, color_br, color_tl, color_tr);
}

void tile_blit_section_colored (uint16_t index,
                                const fpoint &tile_tl, const fpoint &tile_br,
                                const spoint &tl, const spoint &br,
                                color color_bl,
                                color color_br,
                                color color_tl,
                                color color_tr)
{
    tile_blit_section_colored(tile_index_to_tile(index),
                              tile_tl, tile_br, tl, br,
                              color_bl, color_br, color_tl, color_tr);
}

void tile_blit_outline_section_colored (const Tilep &tile,
                                        const fpoint &tile_tl,
                                        const fpoint &tile_br,
                                        const spoint &tl,
                                        const spoint &br,
                                        color color_bl,
                                        color color_br,
                                        color color_tl,
                                        color color_tr)
{
    tile_blit_outline_section(tile, tile_tl, tile_br, tl, br, 0.75);
}

void tile_blit_outline_section_colored (uint16_t index,
                                        const fpoint &tile_tl,
                                        const fpoint &tile_br,
                                        const spoint &tl,
                                        const spoint &br,
                                        color color_bl,
                                        color color_br,
                                        color color_tl,
                                        color color_tr)
{
    tile_blit_outline_section_colored(tile_index_to_tile(index),
                                      tile_tl, tile_br, tl, br,
                                      color_bl, color_br, color_tl, color_tr);
}

void tile_blit_outline_section_colored (const Tilep &tile,
                                        const fpoint &tile_tl,
                                        const fpoint &tile_br,
                                        const spoint &tl,
                                        const spoint &br,
                                        color color_bl,
                                        color color_br,
                                        color color_tl,
                                        color color_tr,
                                        float scale)
{
    tile_blit_outline_section(tile, tile_tl, tile_br, tl, br, scale);
}

void tile_blit_outline_section_colored (uint16_t index,
                                        const fpoint &tile_tl,
                                        const fpoint &tile_br,
                                        const spoint &tl,
                                        const spoint &br,
                                        color color_bl,
                                        color color_br,
                                        color color_tl,
                                        color color_tr,
                                        float scale)
{
    tile_blit_outline_section_colored(tile_index_to_tile(index),
                                      tile_tl, tile_br, tl, br,
                                      color_bl, color_br,
                                      color_tl, color_tr, scale);
}
