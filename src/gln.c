/*
 gln lib draws primitives in both forward and backward compatible way
 Copyright (C) 2010 Florent Monnier
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <strings.h>
#include <string.h>

#define GL_GLEXT_PROTOTYPES

#if defined(__APPLE__) && !defined (VMDMESA)
  #include <OpenGL/gl.h>
  #include <OpenGL/glext.h>
#else
  #if defined(USE_GL3_CORE_PROFILE)
    #define GL3_PROTOTYPES 1
    #include <GL3/gl3.h>
  #else
    #include <GL/gl.h>
    #include <GL/glext.h>
  #endif
#endif


/* Switch forward or backward compatibility */
/*
#define DO_FORWARD_COMPATIBLE
*/

#include "gln.h"
#include "gln_intern.h"
#include "gln_shaders.h"

#ifdef _WIN32
#include <windows.h>

/* if the PFNGL*PROC types are not defined in gl.h or glext.h uncomment these lines:
 */

#if 0
typedef GLuint (APIENTRYP PFNGLCREATESHADERPROC) (GLenum type);
typedef void (APIENTRYP PFNGLDELETESHADERPROC) (GLuint shader);
typedef void (APIENTRYP PFNGLSHADERSOURCEPROC) (GLuint shader, GLsizei count, const GLchar* *string, const GLint *length);
typedef void (APIENTRYP PFNGLCOMPILESHADERPROC) (GLuint shader);
typedef void (APIENTRYP PFNGLGETSHADERIVPROC) (GLuint shader, GLenum pname, GLint *params);

typedef GLuint (APIENTRYP PFNGLCREATEPROGRAMPROC) (void);
typedef void (APIENTRYP PFNGLDELETEPROGRAMPROC) (GLuint program);
typedef void (APIENTRYP PFNGLUSEPROGRAMPROC) (GLuint program);
typedef void (APIENTRYP PFNGLATTACHSHADERPROC) (GLuint program, GLuint shader);
typedef void (APIENTRYP PFNGLDETACHSHADERPROC) (GLuint program, GLuint shader);
typedef void (APIENTRYP PFNGLLINKPROGRAMPROC) (GLuint program);
typedef void (APIENTRYP PFNGLGETPROGRAMIVPROC) (GLuint program, GLenum pname, GLint *params);

typedef void (APIENTRYP PFNGLGETPROGRAMINFOLOGPROC) (GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
typedef void (APIENTRYP PFNGLGETSHADERINFOLOGPROC) (GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
typedef GLint (APIENTRYP PFNGLGETUNIFORMLOCATIONPROC) (GLuint program, const GLchar *name);
typedef GLint (APIENTRYP PFNGLGETATTRIBLOCATIONPROC) (GLuint program, const GLchar *name);

typedef void (APIENTRYP PFNGLUNIFORM1IPROC) (GLint location, GLint v0);
typedef void (APIENTRYP PFNGLUNIFORM2IPROC) (GLint location, GLint v0, GLint v1);
typedef void (APIENTRYP PFNGLUNIFORM3IPROC) (GLint location, GLint v0, GLint v1, GLint v2);
typedef void (APIENTRYP PFNGLUNIFORM4IPROC) (GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
typedef void (APIENTRYP PFNGLUNIFORM1IVPROC) (GLint location, GLsizei count, const GLint *value);
typedef void (APIENTRYP PFNGLUNIFORM2IVPROC) (GLint location, GLsizei count, const GLint *value);
typedef void (APIENTRYP PFNGLUNIFORM3IVPROC) (GLint location, GLsizei count, const GLint *value);
typedef void (APIENTRYP PFNGLUNIFORM4IVPROC) (GLint location, GLsizei count, const GLint *value);
typedef void (APIENTRYP PFNGLUNIFORM1FPROC) (GLint location, GLfloat v0);
typedef void (APIENTRYP PFNGLUNIFORM2FPROC) (GLint location, GLfloat v0, GLfloat v1);
typedef void (APIENTRYP PFNGLUNIFORM3FPROC) (GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
typedef void (APIENTRYP PFNGLUNIFORM4FPROC) (GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
typedef void (APIENTRYP PFNGLUNIFORM1FVPROC) (GLint location, GLsizei count, const GLfloat *value);
typedef void (APIENTRYP PFNGLUNIFORM2FVPROC) (GLint location, GLsizei count, const GLfloat *value);
typedef void (APIENTRYP PFNGLUNIFORM3FVPROC) (GLint location, GLsizei count, const GLfloat *value);
typedef void (APIENTRYP PFNGLUNIFORM4FVPROC) (GLint location, GLsizei count, const GLfloat *value);

typedef void (APIENTRYP PFNGLUNIFORMMATRIX2FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX3FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX4FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);

typedef void (APIENTRYP PFNGLUNIFORMMATRIX2X3FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX3X2FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX2X4FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX4X2FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX3X4FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX4X3FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);


typedef void (APIENTRYP PFNGLVERTEXATTRIB1SPROC) (GLuint index, GLshort x);
typedef void (APIENTRYP PFNGLVERTEXATTRIB1DPROC) (GLuint index, GLdouble x);
typedef void (APIENTRYP PFNGLVERTEXATTRIB2SPROC) (GLuint index, GLshort x, GLshort y);
typedef void (APIENTRYP PFNGLVERTEXATTRIB2DPROC) (GLuint index, GLdouble x, GLdouble y);
typedef void (APIENTRYP PFNGLVERTEXATTRIB3SPROC) (GLuint index, GLshort x, GLshort y, GLshort z);
typedef void (APIENTRYP PFNGLVERTEXATTRIB3DPROC) (GLuint index, GLdouble x, GLdouble y, GLdouble z);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4SPROC) (GLuint index, GLshort x, GLshort y, GLshort z, GLshort w);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4DPROC) (GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);

typedef void (APIENTRYP PFNGLENABLEVERTEXATTRIBARRAYPROC) (GLuint index);
typedef void (APIENTRYP PFNGLBINDATTRIBLOCATIONPROC) (GLuint program, GLuint index, const GLchar *name);
#endif


#define CHECK_FUNC(func, f_type) \
  { static f_type func = NULL; \
    static unsigned int func##_is_loaded = 0; \
    if (!func##_is_loaded) { \
        func = (f_type) wglGetProcAddress(#func); \
        if (func == NULL) \
        { fprintf(stderr, "gln error: unable to load " #func "\n"); \
          exit(1); } \
        else { func##_is_loaded = 1; } \
    } \
  }

#else
#define CHECK_FUNC(func, f_type)
#endif


#if defined(DO_FORWARD_COMPATIBLE)

/* ==== Compile Shaders ================================ */

static void glnPrintShaderInfoLog(GLuint shaderID)
{
    GLchar *infoLog;
    GLint infologLength;
    GLsizei writtenLength;
    glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infologLength);
    infoLog = malloc(infologLength * sizeof(GLchar));
    glGetShaderInfoLog(shaderID, infologLength,  &writtenLength, infoLog);
    fprintf(stderr, "gln error: shader info-log:\n%s\n", infoLog);
    free(infoLog);
}

static void glnPrintProgramInfoLog(GLuint shaderProgram)
{
    GLchar *infoLog;
    GLint infologLength;
    GLsizei writtenLength;
    glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &infologLength);
    infoLog = malloc(infologLength * sizeof(GLchar));
    glGetProgramInfoLog(shaderProgram, infologLength,  &writtenLength, infoLog);
    fprintf(stderr, "gln error: program info-log:\n%s\n", infoLog);
    free(infoLog);
}

static void glnCompileShaders(
        gln_shading *shading,
        const char *vertexShader,
        const char *fragmentShader)
{
    GLuint vertexShaderID;
    GLuint fragmentShaderID;
    GLuint shaderProgram;
    GLint error;

    CHECK_FUNC(glCreateShader, PFNGLCREATESHADERPROC)
    CHECK_FUNC(glShaderSource, PFNGLSHADERSOURCEPROC)
    CHECK_FUNC(glCompileShader, PFNGLCOMPILESHADERPROC)
    CHECK_FUNC(glGetShaderiv, PFNGLGETSHADERIVPROC)
    CHECK_FUNC(glCreateProgram, PFNGLCREATEPROGRAMPROC)
    CHECK_FUNC(glAttachShader, PFNGLATTACHSHADERPROC)
    CHECK_FUNC(glLinkProgram, PFNGLLINKPROGRAMPROC)
    CHECK_FUNC(glGetProgramiv, PFNGLGETPROGRAMIVPROC)
    CHECK_FUNC(glGetShaderInfoLog, PFNGLGETSHADERINFOLOGPROC)
    CHECK_FUNC(glGetProgramInfoLog, PFNGLGETPROGRAMINFOLOGPROC)

    /*
    printf("SHADING_LANGUAGE_VERSION: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    */

    vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    if (vertexShaderID == 0) {
        fprintf(stderr, "gln error: create vertex shader\n");
        exit(1);
    }

    fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    if (fragmentShaderID == 0) {
        fprintf(stderr, "gln error: create fragment shader\n");
        exit(1);
    }

    glShaderSource(vertexShaderID, 1, &vertexShader, NULL);
    glShaderSource(fragmentShaderID, 1, &fragmentShader, NULL);

    glCompileShader(vertexShaderID);
    glCompileShader(fragmentShaderID);

    glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &error);
    if (error == GL_FALSE) {
        fprintf(stderr, "gln error: vertex shader compile operation failed\n");
        glnPrintShaderInfoLog(vertexShaderID);
        exit(1);
    }

    glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &error);
    if (error == GL_FALSE) {
        fprintf(stderr, "gln error: fragment shader compile operation failed\n");
        glnPrintShaderInfoLog(fragmentShaderID);
        exit(1);
    }

    shaderProgram = glCreateProgram();
    if (shaderProgram == 0) {
        fprintf(stderr, "gln error: create program failed\n");
        exit(1);
    }

    glAttachShader(shaderProgram, vertexShaderID);
    glAttachShader(shaderProgram, fragmentShaderID);

    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &error);
    if (error == GL_FALSE) {
        fprintf(stderr, "gln error: link program failed\n");
        glnPrintProgramInfoLog(shaderProgram);
        exit(1);
    }

    shading->shaderProgram  = shaderProgram;
    shading->vertexShader   = vertexShaderID;
    shading->fragmentShader = fragmentShaderID;
}


/* ==== Load Shaders ================================ */

static GLint glnGetUniformLocation(GLuint shaderProgram, const char *name)
{
    CHECK_FUNC(glGetUniformLocation, PFNGLGETUNIFORMLOCATIONPROC)
    GLint loc = glGetUniformLocation(shaderProgram, name);
    if (loc == -1) {
        fprintf(stderr, "gln error: get uniform location failed\n");
        exit(1);
    }
    return loc;
}

static GLint glnGetAttribLocation(GLuint shaderProgram, const char *name)
{
    CHECK_FUNC(glGetAttribLocation, PFNGLGETATTRIBLOCATIONPROC)
    GLint loc = glGetAttribLocation(shaderProgram, name);
    if (loc == -1) {
        fprintf(stderr, "gln error: get attrib location failed\n");
        exit(1);
    }
    return loc;
}

#define get_uniform_loc(i, name) \
    shading->locations[i] = glnGetUniformLocation(shading->shaderProgram, name);
#define get_attrib_loc(i, name) \
    shading->locations[i] = glnGetAttribLocation(shading->shaderProgram, name);

static void glnLoadShaders_rgb(
        gln_shading *shading, gln_glslVersion v)
{
    glnCompileShaders(shading,
        interpolate_rgb_vert(v),
        interpolate_rgb_frag(v));

    shading->type = GLN_SHAD_COLOR_ATTRIB;

    get_uniform_loc(0, "ProjectionMatrix")
    get_uniform_loc(1, "ModelViewMatrix" )
    get_attrib_loc (2, "VertexPosition"  )
    get_attrib_loc (3, "VertexColor"     )
}

static void glnLoadShaders_uniformcolor(
        gln_shading *shading, gln_glslVersion v)
{
    glnCompileShaders(shading,
        plain_color_vertex_shader(v),
        plain_uniform_color(v));

    shading->type = GLN_SHAD_COLOR;

    get_uniform_loc(0, "ProjectionMatrix")
    get_uniform_loc(1, "ModelViewMatrix" )
    get_uniform_loc(2, "PlainColor"      )
    get_attrib_loc (3, "VertexPosition"  )
}

#define BUF_LEN 4096
static char buf[BUF_LEN];

static void glnLoadShaders_staticcolor3(
        gln_shading *shading, float color[4], gln_glslVersion v)
{
    static_color3(v, color, buf, BUF_LEN);

    glnCompileShaders(shading,
        plain_color_vertex_shader(v),
        buf);

    shading->type = GLN_SHAD_BASE;

    get_uniform_loc(0, "ProjectionMatrix")
    get_uniform_loc(1, "ModelViewMatrix" )
    get_attrib_loc (2, "VertexPosition"  )
}

static void glnLoadShaders_staticcolor4(
        gln_shading *shading, float color[4], gln_glslVersion v)
{
    static_color4(v, color, buf, BUF_LEN);

    glnCompileShaders(shading,
        plain_color_vertex_shader(v),
        buf);

    shading->type = GLN_SHAD_BASE;

    get_uniform_loc(0, "ProjectionMatrix")
    get_uniform_loc(1, "ModelViewMatrix" )
    get_attrib_loc (2, "VertexPosition"  )
}

static void glnLoadShaders_uv(gln_shading *shading, gln_glslVersion v)
{
    glnCompileShaders(shading,
        interpolate_uv_vert(v),
        interpolate_uv_frag(v));

    shading->type = GLN_SHAD_UV_ATTRIB;

    get_uniform_loc(0, "ProjectionMatrix")
    get_uniform_loc(1, "ModelViewMatrix" )
    get_attrib_loc (2, "VertexPosition")
    get_attrib_loc (3, "VertexUV"      )
}

static void glnLoadShaders_uv_color(gln_shading *shading, gln_glslVersion v)
{
    glnCompileShaders(shading,
        interpolate_uv_rgb_vert(v),
        interpolate_uv_rgb_frag(v));

    shading->type = GLN_SHAD_UV_COLOR_ATTRIB;

    get_uniform_loc(0, "ProjectionMatrix")
    get_uniform_loc(1, "ModelViewMatrix" )
    get_uniform_loc(2, "TexEnv" )
    get_attrib_loc (3, "VertexPosition")
    get_attrib_loc (4, "VertexUV"      )
    get_attrib_loc (5, "VertexColor"   )
}

static void glnLoadShaders_normal(gln_shading *shading, gln_glslVersion v)
{
    glnCompileShaders(shading,
        interpolate_normal_vert(v),
        interpolate_normal_frag(v));

    shading->type = GLN_SHAD_NORMAL_ATTRIB;

    get_uniform_loc(0, "ProjectionMatrix")
    get_uniform_loc(1, "ModelViewMatrix" )
    get_uniform_loc(2, "PlainColor"      )
    get_uniform_loc(3, "lightDir"        )
    get_attrib_loc (4, "VertexPosition"  )
    get_attrib_loc (5, "VertexNormal"    )
}

static void glnLoadShaders_normal_rgb(gln_shading *shading, gln_glslVersion v)
{
    glnCompileShaders(shading,
        interpolate_normal_rgb_vert(v),
        interpolate_normal_rgb_frag(v));

    shading->type = GLN_SHAD_NORMAL_COLOR_ATTRIB;

    get_uniform_loc(0, "ProjectionMatrix")
    get_uniform_loc(1, "ModelViewMatrix" )
    get_uniform_loc(2, "lightDir"        )
    get_attrib_loc (3, "VertexPosition"  )
    get_attrib_loc (4, "VertexNormal"    )
    get_attrib_loc (5, "VertexColor"     )
}

static void glnLoadShaders_normal_uv(gln_shading *shading, gln_glslVersion v)
{
    glnCompileShaders(shading,
        interpolate_normal_uv_vert(v),
        interpolate_normal_uv_frag(v));

    shading->type = GLN_SHAD_NORMAL_UV_ATTRIB;

    get_uniform_loc(0, "ProjectionMatrix")
    get_uniform_loc(1, "ModelViewMatrix" )
    get_uniform_loc(2, "lightDir"        )
    get_attrib_loc (3, "VertexPosition"  )
    get_attrib_loc (4, "VertexNormal"    )
    get_attrib_loc (5, "VertexUV"        )
}

#undef get_uniform_loc
#undef get_attrib_loc


/* ==== Make Mesh ================================ */

gln_mesh* glnMakeMesh(gln_meshSrc *src)
{
    gln_glslVersion v = GLN_GLSL_VERSION_120;

    gln_mesh *mesh = malloc(sizeof(gln_mesh));
    if (!mesh) {
        fprintf(stderr, "gln error: out of memory\n");
        exit(1);
    }

    switch (src->vertices_kind)
    {
        case GLN_VERTICES3:
            glnLoadShaders_uniformcolor(&(mesh->shading), v);
            break;

        case GLN_RGB_VERTICES3:
            glnLoadShaders_rgb(&(mesh->shading), v);
            break;

        case GLN_PLAINCOLOR3_VERTICES3:
            glnLoadShaders_staticcolor3(&(mesh->shading), src->color, v);
            break;

        case GLN_PLAINCOLOR4_VERTICES3:
            glnLoadShaders_staticcolor4(&(mesh->shading), src->color, v);
            break;

        case GLN_UV_VERTICES3:
            glnLoadShaders_uv(&(mesh->shading), v);
            break;

        case GLN_UV_RGB_VERTICES3:
            glnLoadShaders_uv_color(&(mesh->shading), v);
            break;

        case GLN_NORMAL_VERTICES3:
            glnLoadShaders_normal(&(mesh->shading), v);
            break;

        case GLN_NORMAL_RGB_VERTICES3:
            glnLoadShaders_normal_rgb(&(mesh->shading), v);
            break;

        case GLN_NORMAL_UV_VERTICES3:
            glnLoadShaders_normal_uv(&(mesh->shading), v);
            break;
    }

    glGenBuffersARB(2, &(mesh->vboIds[0]));
    if (mesh->vboIds[0] == 0 ||
        mesh->vboIds[1] == 0)
    {
        fprintf(stderr, "gln error: generate buffer object names failed\n");
        exit(1);
    }

    glBindBufferARB(GL_ARRAY_BUFFER_ARB, mesh->vboIds[0]);
    glBufferDataARB(GL_ARRAY_BUFFER_ARB,
                    src->vertices_size * sizeof(float),
                    src->vertices, GL_STATIC_DRAW_ARB);

    glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, mesh->vboIds[1]);
    glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB,
                    src->indices_size * sizeof(int),
                    src->indices, GL_STATIC_DRAW_ARB);

    mesh->elem_buf_len = src->indices_size;
    mesh->elem_type = GL_UNSIGNED_INT;

    return mesh;
}

/* ==== Delete Mesh ================================ */

void glnDeleteMesh(gln_mesh* mesh)
{
    CHECK_FUNC(glDeleteShader, PFNGLDELETESHADERPROC)
    CHECK_FUNC(glDeleteProgram, PFNGLDELETEPROGRAMPROC)

    glDeleteShader(mesh->shading.vertexShader);
    glDeleteShader(mesh->shading.fragmentShader);
    glDeleteProgram(mesh->shading.shaderProgram);

    glDeleteBuffersARB(2, &(mesh->vboIds[0]));

    free(mesh);
}


/* ==== Draw Mesh ================================ */

#define FPTR(i) ((float *) NULL + (i))
#define LOC(i) (mesh->shading.locations[i])

void glnDrawMesh(
        gln_mesh *mesh,
        gln_matrices *matrices,
        gln_drawMeshParams *params )
{
    const float identity_matrix[] =
       { 1.0, 0.0, 0.0, 0.0,
         0.0, 1.0, 0.0, 0.0,
         0.0, 0.0, 1.0, 0.0,
         0.0, 0.0, 0.0, 1.0 };
    const float default_color[] =
        { 1.0, 1.0, 1.0 };
    const float default_light_dir[] =
        { 0.0, -1.0, 0.0, 1.0 };
    const int default_texenv = GLN_MODULATE;

    GLsizei stride;

    if (mesh == NULL) {
        fprintf(stderr, "gln error: draw request with null pointer\n");
        return;
    }

    CHECK_FUNC(glUseProgram, PFNGLUSEPROGRAMPROC)
    CHECK_FUNC(glEnableVertexAttribArray, PFNGLENABLEVERTEXATTRIBARRAYPROC)
    CHECK_FUNC(glDisableVertexAttribArray, PFNGLDISABLEVERTEXATTRIBARRAYPROC)
    CHECK_FUNC(glVertexAttribPointer, PFNGLVERTEXATTRIBPOINTERPROC)
    CHECK_FUNC(glUniformMatrix4fv, PFNGLUNIFORMMATRIX4FVPROC)
    CHECK_FUNC(glUniform3fv, PFNGLUNIFORM3FVPROC)
    CHECK_FUNC(glUniform1i, PFNGLUNIFORM1IPROC)

    glUseProgram(mesh->shading.shaderProgram);

    if (matrices == NULL) {
        glUniformMatrix4fv(LOC(0), 1, GL_FALSE, identity_matrix);
        glUniformMatrix4fv(LOC(1), 1, GL_FALSE, identity_matrix);
    } else {
        glUniformMatrix4fv(LOC(0), 1, GL_FALSE, matrices->projection);
        glUniformMatrix4fv(LOC(1), 1, GL_FALSE, matrices->modelview);
    }

    switch (mesh->shading.type)
    {
    case GLN_SHAD_COLOR_ATTRIB:

        /* activate the 2 generic arrays */
        glEnableVertexAttribArray(LOC(2));
        glEnableVertexAttribArray(LOC(3));

        /* bind the vertices buffer */
        glBindBufferARB(GL_ARRAY_BUFFER_ARB, mesh->vboIds[0]);

        /* and link the buffer data with the shader program */
        stride = sizeof(float) * 6;
        /* index [2] is the vertex position attrib location */
        /* index [3] is the vertex color attrib location */
        glVertexAttribPointer(LOC(3), 3, GL_FLOAT, GL_FALSE, stride, FPTR(0));
        glVertexAttribPointer(LOC(2), 3, GL_FLOAT, GL_FALSE, stride, FPTR(3));

        /* active the indices buffer */
        glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, mesh->vboIds[1]);
        /* and render the mesh */
        glDrawElements(GL_TRIANGLES, mesh->elem_buf_len, mesh->elem_type, 0);

        /* desactivate the generique arrays */
        glDisableVertexAttribArray(LOC(2));
        glDisableVertexAttribArray(LOC(3));

    break;
    case GLN_SHAD_BASE:  /* TODO: test me! */
        glEnableVertexAttribArray(LOC(2));

        stride = sizeof(float) * 3;
        glBindBufferARB(GL_ARRAY_BUFFER_ARB, mesh->vboIds[0]);
        glVertexAttribPointer(LOC(2), 3, GL_FLOAT, GL_FALSE, stride, FPTR(0));

        glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, mesh->vboIds[1]);
        glDrawElements(GL_TRIANGLES, mesh->elem_buf_len, mesh->elem_type, 0);

        glDisableVertexAttribArray(LOC(2));

    break;
    case GLN_SHAD_COLOR:  /* TODO: test me! */

        if (params == NULL) {
            glUniform3fv(LOC(2), 1, default_color);
        } else {
            glUniform3fv(LOC(2), 1, params->color);
        }

        glEnableVertexAttribArray(LOC(3));

        stride = sizeof(float) * 3;
        glBindBufferARB(GL_ARRAY_BUFFER_ARB, mesh->vboIds[0]);
        glVertexAttribPointer(LOC(3), 3, GL_FLOAT, GL_FALSE, stride, FPTR(0));

        glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, mesh->vboIds[1]);
        glDrawElements(GL_TRIANGLES, mesh->elem_buf_len, mesh->elem_type, 0);

        glDisableVertexAttribArray(LOC(3));

    break;
    case GLN_SHAD_NORMAL_ATTRIB:  /* TODO: test me! */

        if (params == NULL) {
            glUniform3fv(LOC(2), 1, default_color);
            glUniform3fv(LOC(3), 1, default_light_dir);
        } else {
            glUniform3fv(LOC(2), 1, params->color);
            glUniform3fv(LOC(3), 1, params->light_dir);
        }

        glEnableVertexAttribArray(LOC(4));
        glEnableVertexAttribArray(LOC(5));

        stride = sizeof(float) * 6;
        glBindBufferARB(GL_ARRAY_BUFFER_ARB, mesh->vboIds[0]);
        glVertexAttribPointer(LOC(5), 3, GL_FLOAT, GL_FALSE, stride, FPTR(0));
        glVertexAttribPointer(LOC(4), 3, GL_FLOAT, GL_FALSE, stride, FPTR(3));

        glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, mesh->vboIds[1]);
        glDrawElements(GL_TRIANGLES, mesh->elem_buf_len, mesh->elem_type, 0);

        glDisableVertexAttribArray(LOC(4));
        glDisableVertexAttribArray(LOC(5));

    break;
    case GLN_SHAD_UV_ATTRIB:

        glEnableVertexAttribArray(LOC(2));
        glEnableVertexAttribArray(LOC(3));

        stride = sizeof(float) * 5;
        glBindBufferARB(GL_ARRAY_BUFFER_ARB, mesh->vboIds[0]);
        glVertexAttribPointer(LOC(3), 2, GL_FLOAT, GL_FALSE, stride, FPTR(0));
        glVertexAttribPointer(LOC(2), 3, GL_FLOAT, GL_FALSE, stride, FPTR(2));

        glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, mesh->vboIds[1]);
        glDrawElements(GL_TRIANGLES, mesh->elem_buf_len, mesh->elem_type, 0);

        glDisableVertexAttribArray(LOC(2));
        glDisableVertexAttribArray(LOC(3));

    break;
    case GLN_SHAD_UV_COLOR_ATTRIB:  /* TODO: test me! */

        if (params == NULL) {
            glUniform1i(LOC(2), default_texenv);
        } else {
            glUniform1i(LOC(2), params->texenv);
        }

        glEnableVertexAttribArray(LOC(3));
        glEnableVertexAttribArray(LOC(4));
        glEnableVertexAttribArray(LOC(5));

        stride = sizeof(float) * 8;
        glBindBufferARB(GL_ARRAY_BUFFER_ARB, mesh->vboIds[0]);
        glVertexAttribPointer(LOC(4), 2, GL_FLOAT, GL_FALSE, stride, FPTR(0));
        glVertexAttribPointer(LOC(5), 3, GL_FLOAT, GL_FALSE, stride, FPTR(2));
        glVertexAttribPointer(LOC(3), 3, GL_FLOAT, GL_FALSE, stride, FPTR(5));

        glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, mesh->vboIds[1]);
        glDrawElements(GL_TRIANGLES, mesh->elem_buf_len, mesh->elem_type, 0);

        glDisableVertexAttribArray(LOC(3));
        glDisableVertexAttribArray(LOC(4));
        glDisableVertexAttribArray(LOC(5));

    break;
    case GLN_SHAD_NORMAL_COLOR_ATTRIB:  /* TODO: test me! */

        if (params == NULL) {
            glUniform3fv(LOC(2), 1, default_light_dir);
        } else {
            glUniform3fv(LOC(2), 1, params->light_dir);
        }

        glEnableVertexAttribArray(LOC(3));
        glEnableVertexAttribArray(LOC(4));
        glEnableVertexAttribArray(LOC(5));

        stride = sizeof(float) * 9;
        glBindBufferARB(GL_ARRAY_BUFFER_ARB, mesh->vboIds[0]);
        glVertexAttribPointer(LOC(4), 3, GL_FLOAT, GL_FALSE, stride, FPTR(0));
        glVertexAttribPointer(LOC(5), 3, GL_FLOAT, GL_FALSE, stride, FPTR(3));
        glVertexAttribPointer(LOC(3), 3, GL_FLOAT, GL_FALSE, stride, FPTR(6));

        glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, mesh->vboIds[1]);
        glDrawElements(GL_TRIANGLES, mesh->elem_buf_len, mesh->elem_type, 0);

        glDisableVertexAttribArray(LOC(3));
        glDisableVertexAttribArray(LOC(4));
        glDisableVertexAttribArray(LOC(5));

    break;
    case GLN_SHAD_NORMAL_UV_ATTRIB:

        if (params == NULL) {
            glUniform3fv(LOC(2), 1, default_light_dir);
        } else {
            glUniform3fv(LOC(2), 1, params->light_dir);
        }

        glEnableVertexAttribArray(LOC(3));
        glEnableVertexAttribArray(LOC(4));
        glEnableVertexAttribArray(LOC(5));

        stride = sizeof(float) * 8;
        glBindBufferARB(GL_ARRAY_BUFFER_ARB, mesh->vboIds[0]);
        glVertexAttribPointer(LOC(4), 3, GL_FLOAT, GL_FALSE, stride, FPTR(0));
        glVertexAttribPointer(LOC(5), 2, GL_FLOAT, GL_FALSE, stride, FPTR(3));
        glVertexAttribPointer(LOC(3), 3, GL_FLOAT, GL_FALSE, stride, FPTR(5));

        glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, mesh->vboIds[1]);
        glDrawElements(GL_TRIANGLES, mesh->elem_buf_len, mesh->elem_type, 0);

        glDisableVertexAttribArray(LOC(3));
        glDisableVertexAttribArray(LOC(4));
        glDisableVertexAttribArray(LOC(5));

    break;
    }

    glUseProgram(0);
}

#undef FPTR
#undef LOC

#else /* DO_FORWARD_COMPATIBLE */

/* ==== Backward Compatibility ==== */

gln_mesh* glnMakeMesh(gln_meshSrc *src)
{
    /* check max of elements vertices and elements indices that your video card supports
       Use these values to determine the range of glDrawRangeElements()
       The constants are defined in glext.h */
    /*
    int maxVertices;
    int maxIndices;
    glGetIntegerv(GL_MAX_ELEMENTS_VERTICES, &maxVertices);
    glGetIntegerv(GL_MAX_ELEMENTS_INDICES, &maxIndices);
    */

    gln_mesh *mesh = malloc(sizeof(gln_mesh));
    if (!mesh) {
        fprintf(stderr, "gln error: out of memory\n");
        return NULL;
    }

    mesh->vertices_kind = src->vertices_kind;
    mesh->vertices_size = src->vertices_size;
    mesh->indices_size  = src->indices_size;

    mesh->color[0] = src->color[0];
    mesh->color[1] = src->color[1];
    mesh->color[2] = src->color[2];
    mesh->color[3] = src->color[3];

    mesh->vertices = malloc(src->vertices_size * sizeof(float));
    if (!mesh->vertices) {
        fprintf(stderr, "gln error: out of memory\n");
        free(mesh);
        return NULL;
    }

    mesh->indices = malloc(src->indices_size * sizeof(int));
    if (!mesh->indices) {
        fprintf(stderr, "gln error: out of memory\n");
        free(mesh->vertices);
        free(mesh);
        return NULL;
    }

    memcpy(mesh->vertices, src->vertices, src->vertices_size * sizeof(float));
    memcpy(mesh->indices,  src->indices,  src->indices_size * sizeof(int));

    return mesh;
}

void glnDeleteMesh(gln_mesh* mesh)
{
    free(mesh->vertices);
    free(mesh->indices);
    free(mesh);
}

#define FSTR(ofs) ((ofs) * sizeof(float))

void glnDrawMesh(
        gln_mesh *mesh,
        gln_matrices *matrices,
        gln_drawMeshParams *params )
{
    const float identity_matrix[] =
        { 1.0, 0.0, 0.0, 0.0,
          0.0, 1.0, 0.0, 0.0,
          0.0, 0.0, 1.0, 0.0,
          0.0, 0.0, 0.0, 1.0 };
    const float default_color[] =
        { 1.0, 1.0, 1.0 };
    const float default_light_dir[] =
        { 0.0, -1.0, 0.0, 1.0 };
    const int default_texenv = GLN_MODULATE;

    /* previous states */
    gln_matrices prev_mat_state;
    GLenum prev_matrix_mode;
    GLdouble prev_color[4];

    if (mesh == NULL) {
        fprintf(stderr, "gln error: draw request with null pointer\n");
        return;
    }

    if (matrices != NULL)
    {
        /* save previous state */
        glGetIntegerv(GL_MATRIX_MODE, (GLint*) &prev_matrix_mode);
        glGetFloatv(GL_MODELVIEW_MATRIX, prev_mat_state.modelview);
        glGetFloatv(GL_PROJECTION_MATRIX, prev_mat_state.projection);

        glMatrixMode(GL_MODELVIEW);
        glLoadMatrixf(matrices->modelview);
        glMatrixMode(GL_PROJECTION);
        glLoadMatrixf(matrices->projection);
    }


    switch (mesh->vertices_kind)
    {
    case GLN_RGB_VERTICES3:

        glEnableClientState(GL_COLOR_ARRAY);
        glEnableClientState(GL_VERTEX_ARRAY);

        glColorPointer(3, GL_FLOAT, FSTR(6), mesh->vertices);
        glVertexPointer(3, GL_FLOAT, FSTR(6), mesh->vertices + 3);

        glDrawElements(GL_TRIANGLES, mesh->indices_size,
                       GL_UNSIGNED_INT, mesh->indices);

        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);

    break;
    case GLN_PLAINCOLOR3_VERTICES3:

        glGetDoublev(GL_CURRENT_COLOR, prev_color);
        glColor3fv(mesh->color);
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, mesh->vertices);
        glDrawElements(GL_TRIANGLES, mesh->indices_size,
                       GL_UNSIGNED_INT, mesh->indices);
        glDisableClientState(GL_VERTEX_ARRAY);
        glColor4dv(prev_color);

    break;
    case GLN_PLAINCOLOR4_VERTICES3:

        glGetDoublev(GL_CURRENT_COLOR, prev_color);
        glColor4fv(mesh->color);
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, mesh->vertices);
        glDrawElements(GL_TRIANGLES, mesh->indices_size,
                       GL_UNSIGNED_INT, mesh->indices);
        glDisableClientState(GL_VERTEX_ARRAY);
        glColor4dv(prev_color);

    break;
    case GLN_VERTICES3:

        glGetDoublev(GL_CURRENT_COLOR, prev_color);
        if (params == NULL) {
            glColor3fv(default_color);
        } else {
            glColor3fv(params->color);
            printf(" %f %f %f\n",
                   params->color[0], params->color[1], params->color[2]);
        }
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, mesh->vertices);
        glDrawElements(GL_TRIANGLES, mesh->indices_size,
                       GL_UNSIGNED_INT, mesh->indices);
        glDisableClientState(GL_VERTEX_ARRAY);
        glColor4dv(prev_color);

    break;
    case GLN_NORMAL_VERTICES3:

#if 0
            GLfloat lightKa[] = {.2f, .2f, .2f, 1.0f};  /* ambient light  */
            GLfloat lightKd[] = {.6f, .6f, .6f, 1.0f};  /* diffuse light  */
            GLfloat lightKs[] = {1, 1, 1, 1};           /* specular light */
            /*glLightfv(GL_LIGHT0, GL_AMBIENT, lightKa);*/
            /*glLightfv(GL_LIGHT0, GL_DIFFUSE, lightKd);*/
            /*glLightfv(GL_LIGHT0, GL_SPECULAR, lightKs);*/
#endif
        if (params == NULL) {
            glEnable(GL_LIGHTING);
            glEnable(GL_LIGHT0);
            glLightfv(GL_LIGHT0, GL_POSITION, default_light_dir);
        } else {
            GLfloat light_diff[4];
            GLfloat light_dir[4];
            /* TODO should restore */
            glEnable(GL_LIGHTING);
            glEnable(GL_LIGHT0);
            light_dir[0] = params->light_dir[0];
            light_dir[1] = params->light_dir[1];
            light_dir[2] = params->light_dir[2];
            light_dir[3] = 0.0f;
            glLightfv(GL_LIGHT0, GL_POSITION, light_dir);
            light_diff[0] = params->color[0];
            light_diff[1] = params->color[1];
            light_diff[2] = params->color[2];
            light_diff[3] = 1.0f;
            glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diff);
        }

        glEnableClientState(GL_NORMAL_ARRAY);
        glEnableClientState(GL_VERTEX_ARRAY);

        glNormalPointer(GL_FLOAT, FSTR(6), mesh->vertices);
        glVertexPointer(3, GL_FLOAT, FSTR(6), mesh->vertices + 3);

        glDrawElements(GL_TRIANGLES, mesh->indices_size,
                       GL_UNSIGNED_INT, mesh->indices);

        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_NORMAL_ARRAY);

    break;
    case GLN_UV_VERTICES3:

        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glEnableClientState(GL_VERTEX_ARRAY);

        glTexCoordPointer(2, GL_FLOAT, FSTR(5), mesh->vertices);
        glVertexPointer(3, GL_FLOAT, FSTR(5), mesh->vertices + 2);

        glDrawElements(GL_TRIANGLES, mesh->indices_size,
                       GL_UNSIGNED_INT, mesh->indices);

        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);

    break;
    case GLN_UV_RGB_VERTICES3:

        if (params == NULL) {
            /* use: default_texenv */
        } else {
            /* use: params->texenv */
        }

        fprintf(stderr, "gln todo\n");
        exit(1);

    break;
    case GLN_NORMAL_RGB_VERTICES3:

        if (params == NULL) {
            /* use: default_light_dir */
        } else {
            /* use: params->light_dir */
        }

        fprintf(stderr, "gln todo\n");
        exit(1);
        /*
        glEnableClientState(GL_NORMAL_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);
        glEnableClientState(GL_VERTEX_ARRAY);

        glNormalPointer(GL_FLOAT, FSTR(9), mesh->vertices);
        glColorPointer(3, GL_FLOAT, FSTR(9), mesh->vertices + 3);
        glVertexPointer(3, GL_FLOAT, FSTR(9), mesh->vertices + 6);

        glDrawElements(GL_TRIANGLES, mesh->indices_size,
                       GL_UNSIGNED_INT, mesh->indices);

        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_NORMAL_ARRAY);
        */

    break;
    case GLN_NORMAL_UV_VERTICES3:

        /* TODO should restore */
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        /*
        glShadeModel(GL_SMOOTH);
        */
        glEnable(GL_TEXTURE_2D);

        if (params == NULL) {
            /* use: default_light_dir */
        } else {
            GLfloat light_dir[4];
            light_dir[0] = params->light_dir[0];
            light_dir[1] = params->light_dir[1];
            light_dir[2] = params->light_dir[2];
            light_dir[3] = 0.0f;
            glLightfv(GL_LIGHT0, GL_POSITION, light_dir);
        }

        glEnableClientState(GL_NORMAL_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glEnableClientState(GL_VERTEX_ARRAY);

        glNormalPointer(GL_FLOAT, FSTR(8), mesh->vertices);
        glTexCoordPointer(2, GL_FLOAT, FSTR(8), mesh->vertices + 3);
        glVertexPointer(3, GL_FLOAT, FSTR(8), mesh->vertices + 5);

        glDrawElements(GL_TRIANGLES, mesh->indices_size,
                       GL_UNSIGNED_INT, mesh->indices);

        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        glDisableClientState(GL_NORMAL_ARRAY);

    break;
    }

    if (matrices != NULL)
    {
        /* restore previous state */
        glMatrixMode(GL_MODELVIEW);
        glLoadMatrixf(prev_mat_state.modelview);
        glMatrixMode(GL_PROJECTION);
        glLoadMatrixf(prev_mat_state.projection);
        glMatrixMode(prev_matrix_mode);
    }
}

#undef FSTR

#endif /* DO_FORWARD_COMPATIBLE */


int glnGetStride(gln_verticesKind k)
{
    switch (k) {
    case GLN_PLAINCOLOR3_VERTICES3: return 3;
    case GLN_PLAINCOLOR4_VERTICES3: return 3;
    case GLN_VERTICES3:             return 3;
    case GLN_RGB_VERTICES3:         return 6;
    case GLN_UV_VERTICES3:          return 5;
    case GLN_UV_RGB_VERTICES3:      return 8;
    case GLN_NORMAL_VERTICES3:      return 6;
    case GLN_NORMAL_RGB_VERTICES3:  return 9;
    case GLN_NORMAL_UV_VERTICES3:   return 8;
    }
    return -1;
}


/* ==== Geometric Objects ================================ */

#define GLN_PI 3.141592653589793238462643
static const double pi = GLN_PI;
static const double pi_twice = GLN_PI * 2.0;
static const double pi_half = GLN_PI / 2.0;
#define GLN_DEG_TO_RAD  (GLN_PI / 360.0)

/* ==== Sphere ================================ */

static void glnCreateSphereSrc_no_uv(
        gln_meshSrc *src, double radius,
        unsigned int slices, unsigned int stacks,
        int gen_normals)
{
    unsigned int n = ((stacks - 1) * slices) + 2;
    unsigned int stride = (gen_normals ? (3+3) : 3);
    unsigned int vert_size = n * stride;
    float *verts = malloc(vert_size * sizeof(float));
    unsigned int m = 2 * ((stacks - 2) * slices) + (2 * slices);
    unsigned int face_size = m * 3;
    unsigned int *faces = malloc(face_size * sizeof(int));
    double fslices = (double) slices;
    double fstacks = (double) stacks;
    unsigned int v = 0;
    unsigned int f = 0;
    unsigned int i;
    unsigned int j;
    unsigned int ofs;
    for (j = 1; j < stacks; j++)
    {
        double percent_j = (double) j / fstacks;
        double a = percent_j * pi - pi_half;
        double cos_a = cos(a);
        double sin_a = sin(a);
        double r_cos_a = radius * cos_a;
        double r_sin_a = radius * sin_a;
        for (i = 0; i < slices; i++)
        {
            double percent_i = (double) i / fslices;
            double b = percent_i * pi_twice;
            /*
               x = r * (cos a) * (cos b)    -pi/2 < a < pi/2
               y = r * (cos a) * (sin b)        0 < b < 2 pi
               z = r * (sin a)
            */
            double cos_b = cos(b);
            double sin_b = sin(b);
            if (gen_normals) {
              verts[v] = (float) (cos_a * cos_b);  ++v;  /* normal x */
              verts[v] = (float) (cos_a * sin_b);  ++v;  /* normal y */
              verts[v] = (float) (sin_a);          ++v;  /* normal z */
            }
            verts[v] = (float) (r_cos_a * cos_b);  ++v;  /* x */
            verts[v] = (float) (r_cos_a * sin_b);  ++v;  /* y */
            verts[v] = (float) (r_sin_a);          ++v;  /* z */
        }
    }
    /* the top */
    if (gen_normals) {
      verts[v] =  0.0f;  ++v;  /* normal x */
      verts[v] =  0.0f;  ++v;  /* normal y */
      verts[v] =  1.0f;  ++v;  /* normal z */
    }
    verts[v] =  0.0f;    ++v;  /* x */
    verts[v] =  0.0f;    ++v;  /* y */
    verts[v] = radius;   ++v;  /* z */

    /* the bottom */
    if (gen_normals) {
      verts[v] =  0.0f;  ++v;  /* normal x */
      verts[v] =  0.0f;  ++v;  /* normal y */
      verts[v] = -1.0f;  ++v;  /* normal z */
    }
    verts[v] =  0.0f;    ++v;  /* x */
    verts[v] =  0.0f;    ++v;  /* y */
    verts[v] = - radius; ++v;  /* z */

    /* faces */
    for (j = 0; j < (stacks - 2); j++)
    {
        for (i = 0; i < slices; i++)
        {
            unsigned int ni = (i + 1) % slices;
            unsigned int s = (j * slices);
            unsigned int ns = ((j + 1) * slices);
            unsigned int a = i + s;
            unsigned int b = ni + s;
            unsigned int c = i + ns;
            unsigned int d = ni + ns;
            /* face 1 */
            faces[f] = a; ++f;
            faces[f] = b; ++f;
            faces[f] = c; ++f;
            /* face 2 */
            faces[f] = c; ++f;
            faces[f] = b; ++f;
            faces[f] = d; ++f;
        }
    }
    ofs = (stacks - 2) * slices;
    for (i = 0; i < slices; i++)
    {
        unsigned int a = i;
        unsigned int b = (i + 1) % slices;
        unsigned int c = a + ofs;
        unsigned int d = b + ofs;
        /* face 1 */
        faces[f] = b;     ++f;
        faces[f] = a;     ++f;
        faces[f] = n - 1; ++f;
        /* face 2 */
        faces[f] = c;     ++f;
        faces[f] = d;     ++f;
        faces[f] = n - 2; ++f;
    }

    if (gen_normals)
        src->vertices_kind = GLN_NORMAL_VERTICES3;
    else
        src->vertices_kind = GLN_VERTICES3;

    src->vertices_size = vert_size;
    src->indices_size = face_size;
    src->vertices = verts;
    src->indices = faces;
}

static void glnCreateSphereSrc_with_uv(
        gln_meshSrc *src, double radius,
        unsigned int slices, unsigned int stacks,
        int gen_normals)
{
    unsigned int n = ((stacks + 1) * (slices + 1));
    unsigned int stride = (gen_normals ? (5+3) : 5);
    unsigned int vert_size = n * stride;
    float *verts = malloc(vert_size * sizeof(float));
    unsigned int m = 2 * ((stacks - 2) * slices) + (2 * slices);
    unsigned int face_size = m * 3;
    unsigned int *faces = malloc(face_size * sizeof(int));
    double fslices = (double) slices;
    double fstacks = (double) stacks;
    unsigned int v = 0;
    unsigned int f = 0;
    unsigned int i;
    unsigned int j;
    unsigned int ofs;
    unsigned int ofs2;
    unsigned int ofs3;
    for (j = 1; j < stacks; j++)
    {
        double percent_j = (double) j / fstacks;
        double a = percent_j * pi - pi_half;
        double cos_a = cos(a);
        double sin_a = sin(a);
        double r_cos_a = radius * cos_a;
        double r_sin_a = radius * sin_a;
        for (i = 0; i <= slices; i++)
        {
            double percent_i = (double) i / fslices;
            double b = percent_i * pi_twice;
            /*
               x = r * (cos a) * (cos b)    -pi/2 < a < pi/2
               y = r * (cos a) * (sin b)        0 < b < 2 pi
               z = r * (sin a)
            */
            double cos_b = cos(b);
            double sin_b = sin(b);
            if (gen_normals) {
              verts[v] = (float) (cos_a * cos_b);  ++v;  /* normal x */
              verts[v] = (float) (cos_a * sin_b);  ++v;  /* normal y */
              verts[v] = (float) (sin_a);          ++v;  /* normal z */
            }
            verts[v] = (float) percent_i;          ++v;  /* u */
            verts[v] = (float) percent_j;          ++v;  /* v */
            verts[v] = (float) (r_cos_a * cos_b);  ++v;  /* x */
            verts[v] = (float) (r_cos_a * sin_b);  ++v;  /* y */
            verts[v] = (float) (r_sin_a);          ++v;  /* z */
        }
    }
    for (i = 0; i <= slices; i++) {
        float percent_i = (float) i / (float) fslices;
        /* the top */
        if (gen_normals) {
          verts[v] =  0.0f;   ++v;  /* normal x */
          verts[v] =  0.0f;   ++v;  /* normal y */
          verts[v] =  1.0f;   ++v;  /* normal z */
        }
        verts[v] = percent_i; ++v;  /* u */
        verts[v] =  1.0f;     ++v;  /* v */
        verts[v] =  0.0f;     ++v;  /* x */
        verts[v] =  0.0f;     ++v;  /* y */
        verts[v] = radius;    ++v;  /* z */

        /* the bottom */
        if (gen_normals) {
          verts[v] =  0.0f;   ++v;  /* normal x */
          verts[v] =  0.0f;   ++v;  /* normal y */
          verts[v] = -1.0f;   ++v;  /* normal z */
        }
        verts[v] = percent_i; ++v;  /* u */
        verts[v] =  0.0f;     ++v;  /* v */
        verts[v] =  0.0f;     ++v;  /* x */
        verts[v] =  0.0f;     ++v;  /* y */
        verts[v] = - radius;  ++v;  /* z */
    }
    if (vert_size != v) {  /* DEBUG */
        fprintf(stderr, "gln warning: creating sphere: wrong buffer size\n");
    }

    /* now faces */
    for (j = 0; j < (stacks - 2); j++) {
        for (i = 0; i < slices; i++) {
            unsigned int ni = (i + 1);
            unsigned int s = (j * (slices+1));
            unsigned int ns = ((j + 1) * (slices+1));
            unsigned int a = i + s;
            unsigned int b = ni + s;
            unsigned int c = i + ns;
            unsigned int d = ni + ns;
            /* face 1 */
            faces[f] = a; ++f;
            faces[f] = b; ++f;
            faces[f] = c; ++f;
            /* face 2 */
            faces[f] = c; ++f;
            faces[f] = b; ++f;
            faces[f] = d; ++f;
        }
    }
    ofs = (stacks - 2) * (slices + 1);
    ofs2 = n - ((slices-1) * 2) - 1;
    ofs3 = ofs2 - 1;
    for (i = 0; i < slices; i++)
    {
        unsigned int a = i;
        unsigned int b = (i + 1);
        unsigned int c = a + ofs;
        unsigned int d = b + ofs;
        /* face 1 */
        faces[f] = b;  ++f;
        faces[f] = a;  ++f;
        faces[f] = ofs2 + (i*2);  ++f;
        /* face 2 */
        faces[f] = c;  ++f;
        faces[f] = d;  ++f;
        faces[f] = ofs3 + (i*2);  ++f;
    }

    if (gen_normals)
        src->vertices_kind = GLN_NORMAL_UV_VERTICES3;
    else
        src->vertices_kind = GLN_UV_VERTICES3;

    src->vertices_size = vert_size;
    src->indices_size = face_size;
    src->vertices = verts;
    src->indices = faces;
}


static void glnCreateSphereSrc_options(
        gln_meshSrc *src, double radius,
        unsigned int slices, unsigned int stacks,
        int gen_normals, int gen_uv)
{
    if (gen_uv)
        glnCreateSphereSrc_with_uv(src, radius, slices, stacks, gen_normals);
    else
        glnCreateSphereSrc_no_uv(src, radius, slices, stacks, gen_normals);
}


gln_mesh* glnMakeSphere(
        double radius, unsigned int slices, unsigned int stacks,
        unsigned int params)
{
    gln_meshSrc src;
    gln_mesh *mesh;
    int gen_normals = (params & GLN_GEN_NORMALS) != 0;
    int gen_uv      = (params & GLN_GEN_UV) != 0;

    glnCreateSphereSrc_options(
            &src, radius, slices, stacks, gen_normals, gen_uv);

    mesh = glnMakeMesh(&src);
    free(src.vertices);
    free(src.indices);
    return mesh;
}

gln_meshSrc* glnGetSphereSrc(
        double radius, unsigned int slices, unsigned int stacks,
        unsigned int params)
{
    gln_meshSrc *src;

    int gen_normals = (params & GLN_GEN_NORMALS) != 0;
    int gen_uv      = (params & GLN_GEN_UV) != 0;

    src = malloc(sizeof(gln_meshSrc));
    glnCreateSphereSrc_options(
            src, radius, slices, stacks, gen_normals, gen_uv);

    return src;
}


/* ==== Torus ================================ */

static void glnCreateTorusSrc_no_uv(
        gln_meshSrc *src,
        double ri /* inner_radius */, double ro /* outer_radius */,
        unsigned int sides, unsigned int rings,
        int gen_normals)
{
    /* x(u,v) = (R + r cos v) cos u
       y(u,v) = (R + r cos v) sin u
       z(u,v) = r sin v
       with (u,v) in the interval [0, 2pi)
    */
    unsigned int n = sides * rings;
    unsigned int stride = (gen_normals ? 6 : 3);
    unsigned int vert_size = n * stride;
    float *verts = malloc(vert_size * sizeof(float));

    unsigned int m = 2 * sides * rings;
    unsigned int face_size = m * 3;
    unsigned int *faces = malloc(face_size * sizeof(int));

    double fsides = (double) sides;
    double frings = (double) rings;
    unsigned int p = 0;
    unsigned int f = 0;
    unsigned int i;
    unsigned int j;

    for (i = 0; i < rings; i++)
    {
        double u = ((double) i / frings) * pi_twice;
        double cos_u = cos(u);
        double sin_u = sin(u);
        for (j = 0; j < sides; j++)
        {
            double v = ((double) j / fsides) * pi_twice;
            double cos_v = cos(v);
            double sin_v = sin(v);

            if (gen_normals) {
              verts[p] = (float) cos_v * cos_u;            ++p;  /* normal x */
              verts[p] = (float) cos_v * sin_u;            ++p;  /* normal y */
              verts[p] = (float) sin_v;                    ++p;  /* normal z */
            }
            verts[p] = (float) (ro + ri * cos_v) * cos_u;  ++p;  /* x */
            verts[p] = (float) (ro + ri * cos_v) * sin_u;  ++p;  /* y */
            verts[p] = (float) ri * sin_v;                 ++p;  /* z */
        }
    }

    for (i = 0; i < rings; i++)
    {
        for (j = 0; j < sides; j++)
        {
            unsigned int a = j + (i * sides);
            unsigned int b = a + 1;
            unsigned int c;
            unsigned int d;
            if (j == (sides - 1)) b -= sides;
            if (i == (rings - 1)) {
                c = j;
                d = (j == (sides - 1) ? (j+1) - sides : (j+1));
            } else {
                c = a + sides;
                d = b + sides;
            }
            /* face 1 */
            faces[f] = a; ++f;
            faces[f] = c; ++f;
            faces[f] = b; ++f;
            /* face 2 */
            faces[f] = c; ++f;
            faces[f] = d; ++f;
            faces[f] = b; ++f;
        }
    }

    if (gen_normals)
        src->vertices_kind = GLN_NORMAL_VERTICES3;
    else
        src->vertices_kind = GLN_VERTICES3;

    src->vertices_size = vert_size;
    src->indices_size = face_size;
    src->vertices = verts;
    src->indices = faces;
}


static void glnCreateTorusSrc_with_uv(
        gln_meshSrc *src,
        double ri /* inner_radius */,
        double ro /* outer_radius */,
        unsigned int sides, unsigned int rings,
        int gen_normals)
{
    /* x(u,v) = (R + r cos v) cos u
       y(u,v) = (R + r cos v) sin u
       z(u,v) = r sin v
       with (u,v) in the interval [0, 2pi)
    */
    unsigned int n = (sides + 1) * (rings + 1);
    unsigned int stride = (gen_normals ? 8 : 5);
    unsigned int vert_size = n * stride;
    float *verts = malloc(vert_size * sizeof(float));

    unsigned int m = 2 * sides * rings;
    unsigned int face_size = m * 3;
    unsigned int *faces = malloc(face_size * sizeof(int));

    double fsides = (double) sides;
    double frings = (double) rings;
    unsigned int p = 0;
    unsigned int f = 0;
    unsigned int i;
    unsigned int j;
    unsigned int nsides;

    for (i = 0; i <= rings; i++)
    {
        double percent_i = (double) i / frings;
        double u = percent_i * pi_twice;
        double cos_u = cos(u);
        double sin_u = sin(u);
        for (j = 0; j <= sides; j++)
        {
            double percent_j = (double) j / fsides;
            double v = percent_j * pi_twice;
            double cos_v = cos(v);
            double sin_v = sin(v);
            if (gen_normals) {
              verts[p] = (float) cos_v * cos_u;            ++p;  /* normal x */
              verts[p] = (float) cos_v * sin_u;            ++p;  /* normal y */
              verts[p] = (float) sin_v;                    ++p;  /* normal z */
            }
            verts[p] = (float) percent_i;                  ++p;  /* u */
            verts[p] = (float) percent_j;                  ++p;  /* v */
            verts[p] = (float) (ro + ri * cos_v) * cos_u;  ++p;  /* x */
            verts[p] = (float) (ro + ri * cos_v) * sin_u;  ++p;  /* y */
            verts[p] = (float) ri * sin_v;                 ++p;  /* z */
        }
    }
    if (vert_size != p) {  /* DEBUG */
        fprintf(stderr, "gln warning: creating torus: wrong buffer size\n");
    }

    nsides = sides + 1;
    for (i = 0; i < rings; i++)
    {
        for (j = 0; j < sides; j++)
        {
            unsigned int a = j + (i * nsides);
            unsigned int b = a + 1;
            unsigned int c = a + nsides;
            unsigned int d = b + nsides;
            /* face 1 */
            faces[f] = a; ++f;
            faces[f] = c; ++f;
            faces[f] = b; ++f;
            /* face 2 */
            faces[f] = c; ++f;
            faces[f] = d; ++f;
            faces[f] = b; ++f;
        }
    }

    if (gen_normals)
        src->vertices_kind = GLN_NORMAL_UV_VERTICES3;
    else
        src->vertices_kind = GLN_UV_VERTICES3;

    src->vertices_size = vert_size;
    src->indices_size = face_size;
    src->vertices = verts;
    src->indices = faces;
}


static void glnCreateTorusSrc_options(
        gln_meshSrc *src,
        double ri /* inner_radius */,
        double ro /* outer_radius */,
        unsigned int sides, unsigned int rings,
        int gen_normals, int gen_uv)
{
    if (gen_uv)
        glnCreateTorusSrc_with_uv(src, ri, ro, sides, rings, gen_normals);
    else
        glnCreateTorusSrc_no_uv(src, ri, ro, sides, rings, gen_normals);
}


gln_mesh* glnMakeTorus(
        double ri /* inner_radius */,
        double ro /* outer_radius */,
        unsigned int sides, unsigned int rings,
        unsigned int params)
{
    gln_meshSrc src;
    gln_mesh *mesh;
    int gen_normals = (params & GLN_GEN_NORMALS) != 0;
    int gen_uv      = (params & GLN_GEN_UV) != 0;

    glnCreateTorusSrc_options(
            &src, ri, ro, sides, rings, gen_normals, gen_uv);

    mesh = glnMakeMesh(&src);
    free(src.vertices);
    free(src.indices);
    return mesh;
}

gln_meshSrc* glnGetTorusSrc(
        double ri /* inner_radius */,
        double ro /* outer_radius */,
        unsigned int sides, unsigned int rings,
        unsigned int params)
{
    gln_meshSrc *src;

    int gen_normals = (params & GLN_GEN_NORMALS) != 0;
    int gen_uv      = (params & GLN_GEN_UV) != 0;

    src = malloc(sizeof(gln_meshSrc));
    glnCreateTorusSrc_options(
            src, ri, ro, sides, rings, gen_normals, gen_uv);

    return src;
}


/* ==== Cylinder ================================ */

#define INTERMEDIATES_NUM 64

static void glnCreateCylinderSrc_no_uv(
        gln_meshSrc *src,
        double radius, double bottom, double top,
        unsigned int slices, unsigned int stacks,
        int gen_normals)
{
    unsigned int stride = (gen_normals ? 6 : 3);
    unsigned int n = (slices * stacks);  /* no bottom/top */
    unsigned int vert_size = n * stride;
    float *verts = malloc(vert_size * sizeof(float));

    unsigned int m = 2 * (slices) * (stacks - 1);
    unsigned int face_size = m * 3;
    unsigned int *faces = malloc(face_size * sizeof(int));

    double fslices = (double) slices;
    unsigned int stacks_inter = stacks - 1;
    unsigned int slices_inter = slices - 1;

    unsigned int v = 0;
    unsigned int f = 0;
    unsigned int i, j;

    unsigned int inter_steps = stacks - 2;
    float *intermediates;
    float intermediates_buf[INTERMEDIATES_NUM];
    {
        double intermediate_part = (top - bottom) / (double)(stacks - 1);

        if (inter_steps <= INTERMEDIATES_NUM) {
            intermediates = &(intermediates_buf[0]);
        } else {
            intermediates = malloc(inter_steps * sizeof(float));
        }
        for (j = 0; j < inter_steps; j++)
        {
            double d = (double) (j+1);
            intermediates[j] = (float) (bottom + (intermediate_part * d));
        }
    }

    for (i = 0; i < slices; i++)
    {
        double percent_i = (double) i / fslices;
        double a = percent_i * pi_twice;
        double cos_a = cos(a);
        double sin_a = sin(a);
        double x = radius * cos_a;
        double y = radius * sin_a;
        if (!gen_normals) {
            verts[v] = (float) x;      ++v;
            verts[v] = (float) y;      ++v;
            verts[v] = (float) bottom; ++v;
            for (j = 0; j < inter_steps; j++)
            {
              verts[v] = (float) x;    ++v;
              verts[v] = (float) y;    ++v;
              verts[v] = intermediates[j]; ++v;
            }
            verts[v] = (float) x;      ++v;
            verts[v] = (float) y;      ++v;
            verts[v] = (float) top;    ++v;
        } else {
            /* with normals */
            verts[v] = (float) cos_a;  ++v;
            verts[v] = (float) sin_a;  ++v;
            verts[v] = 0.0f;           ++v;
            verts[v] = (float) x;      ++v;
            verts[v] = (float) y;      ++v;
            verts[v] = (float) bottom; ++v;
            for (j = 0; j < inter_steps; j++)
            {
              verts[v] = (float) cos_a; ++v;
              verts[v] = (float) sin_a; ++v;
              verts[v] = 0.0f;          ++v;
              verts[v] = (float) x;     ++v;
              verts[v] = (float) y;     ++v;
              verts[v] = intermediates[j]; ++v;
            }
            verts[v] = (float) cos_a;  ++v;
            verts[v] = (float) sin_a;  ++v;
            verts[v] = 0.0f;           ++v;
            verts[v] = (float) x;      ++v;
            verts[v] = (float) y;      ++v;
            verts[v] = (float) top;    ++v;
        }
    }

    if (vert_size != v) {  /* DEBUG */
        fprintf(stderr, "gln error: creating cylinder: wrong buffer size\n");
    }

    for (i = 0; i < slices_inter; i++)
    {
        for (j = 0; j < stacks_inter; j++)
        {
            unsigned int a = (i * stacks) + j;
            unsigned int b = a + 1;
            unsigned int c = a + stacks;
            unsigned int d = c + 1;
            /* face 1 */
            faces[f] = a; ++f;
            faces[f] = c; ++f;
            faces[f] = b; ++f;
            /* face 2 */
            faces[f] = b; ++f;
            faces[f] = c; ++f;
            faces[f] = d; ++f;
        }
    }
    for (j = 0; j < stacks_inter; j++)
    {
        unsigned int a = (slices_inter * stacks) + j;
        unsigned int b = a + 1;
        unsigned int c = j;
        unsigned int d = j + 1;
        /* face 1 */
        faces[f] = a; ++f;
        faces[f] = c; ++f;
        faces[f] = b; ++f;
        /* face 2 */
        faces[f] = b; ++f;
        faces[f] = c; ++f;
        faces[f] = d; ++f;
    }

    if (face_size != f) {  /* DEBUG */
        fprintf(stderr, "gln error: creating cylinder: wrong buffer size\n");
    }

    if (inter_steps > INTERMEDIATES_NUM) {
        free(intermediates);
    }

    if (gen_normals)
        src->vertices_kind = GLN_NORMAL_VERTICES3;
    else
        src->vertices_kind = GLN_VERTICES3;

    src->vertices_size = vert_size;
    src->indices_size = face_size;
    src->vertices = verts;
    src->indices = faces;
}

static void glnCreateCylinderSrc_with_uv(
        gln_meshSrc *src,
        double radius, double bottom, double top,
        unsigned int slices, unsigned int stacks,
        int gen_normals)
{
}

static void glnCreateCylinderSrc_options(
        gln_meshSrc *src,
        double radius, double bottom, double top,
        unsigned int slices, unsigned int stacks,
        int gen_normals, int gen_uv)
{
    if (gen_uv)
        glnCreateCylinderSrc_with_uv(
                src, radius, bottom, top, slices, stacks, gen_normals);
    else
        glnCreateCylinderSrc_no_uv(
                src, radius, bottom, top, slices, stacks, gen_normals);
}

gln_mesh* glnMakeCylinder(
        double radius, double bottom, double top,
        unsigned int slices, unsigned int stacks,
        unsigned int params )
{
    gln_meshSrc src;
    gln_mesh *mesh;

    int gen_normals = (params & GLN_GEN_NORMALS) != 0;
    int gen_uv      = (params & GLN_GEN_UV) != 0;

    if (stacks < 2 || slices < 3) {
        fprintf(stderr, "gln error: make cylinder: wrong parameter\n");
        return NULL;
    }

    glnCreateCylinderSrc_options(
            &src, radius, bottom, top, slices, stacks, gen_normals, gen_uv);

    mesh = glnMakeMesh(&src);
    free(src.vertices);
    free(src.indices);
    return mesh;
}

gln_meshSrc* glnGetCylinderSrc(
        double radius, double bottom, double top,
        unsigned int slices, unsigned int stacks,
        unsigned int params )
{
    gln_meshSrc *src;

    int gen_normals = (params & GLN_GEN_NORMALS) != 0;
    int gen_uv      = (params & GLN_GEN_UV) != 0;

    if (stacks < 2) {
        fprintf(stderr, "gln error: get cylinder src: wrong parameter\n");
        return NULL;
    }

    src = malloc(sizeof(gln_meshSrc));
    glnCreateCylinderSrc_options(
            src, radius, bottom, top, slices, stacks, gen_normals, gen_uv);

    return src;
}


/* ==== Matrices Handling ================================ */

/* set up a perspective projection matrix */
void glnPerspective(
        gln_matrices *matrices,
        double fovy, double aspect, double zNear, double zFar)
{
    float *m = matrices->projection;

    double maxY = zNear * tan(fovy * GLN_DEG_TO_RAD);
    double minY = -maxY;
    double minX = minY * aspect;
    double maxX = maxY * aspect;

    double xdiff = maxX - minX;
    double ydiff = maxY - minY;
    double zdiff = zFar - zNear;
    double znear_twice = 2.0 * zNear;

    bzero(m, 16 * sizeof(float));

    m[0]  = (float) (znear_twice / xdiff);
    m[5]  = (float) (znear_twice / ydiff);
    m[8]  = (float) ((maxX + minX) / xdiff);
    m[9]  = (float) ((maxY + minY) / ydiff);
    m[10] = (float) (-(zFar + zNear) / zdiff);
    m[11] = -1.0;
    m[14] = (float) (-(znear_twice * zFar) / zdiff);
}

void glnLoadIdentity(gln_matrices *matrices)
{
    float *m = matrices->modelview;

    m[0]  = m[5]  = m[10] = m[15] = 1.0f;
    m[1]  = m[2]  = m[3]  = m[4]  = 0.0f;
    m[6]  = m[7]  = m[8]  = m[9]  = 0.0f;
    m[11] = m[12] = m[13] = m[14] = 0.0f;
}

void glnCopyMatrices(gln_matrices *src, gln_matrices *dst)
{
    memcpy(&(dst->modelview[0]), &(src->modelview[0]), 16 * sizeof(float));
    memcpy(&(dst->projection[0]), &(src->projection[0]), 16 * sizeof(float));
}

/* multiply two matrices */
/*
void mult_matrix(float *m, const float *m1, const float *m2)
{
    m[0] =  m1[0] * m2[0] + m1[4] * m2[1] + m1[8]  * m2[2] + m1[12] * m2[3];
    m[1] =  m1[1] * m2[0] + m1[5] * m2[1] + m1[9]  * m2[2] + m1[13] * m2[3];
    m[2] =  m1[2] * m2[0] + m1[6] * m2[1] + m1[10] * m2[2] + m1[14] * m2[3];
    m[3] =  m1[3] * m2[0] + m1[7] * m2[1] + m1[11] * m2[2] + m1[15] * m2[3];

    m[4] =  m1[0] * m2[4] + m1[4] * m2[5] + m1[8]  * m2[6] + m1[12] * m2[7];
    m[5] =  m1[1] * m2[4] + m1[5] * m2[5] + m1[9]  * m2[6] + m1[13] * m2[7];
    m[6] =  m1[2] * m2[4] + m1[6] * m2[5] + m1[10] * m2[6] + m1[14] * m2[7];
    m[7] =  m1[3] * m2[4] + m1[7] * m2[5] + m1[11] * m2[6] + m1[15] * m2[7];

    m[8]  = m1[0] * m2[8] + m1[4] * m2[9] + m1[8]  * m2[10] + m1[12] * m2[11];
    m[9]  = m1[1] * m2[8] + m1[5] * m2[9] + m1[9]  * m2[10] + m1[13] * m2[11];
    m[10] = m1[2] * m2[8] + m1[6] * m2[9] + m1[10] * m2[10] + m1[14] * m2[11];
    m[11] = m1[3] * m2[8] + m1[7] * m2[9] + m1[11] * m2[10] + m1[15] * m2[11];

    m[12] = m1[0] * m2[12] + m1[4] * m2[13] + m1[8]  * m2[14] + m1[12] * m2[15];
    m[13] = m1[1] * m2[12] + m1[5] * m2[13] + m1[9]  * m2[14] + m1[13] * m2[15];
    m[14] = m1[2] * m2[12] + m1[6] * m2[13] + m1[10] * m2[14] + m1[14] * m2[15];
    m[15] = m1[3] * m2[12] + m1[7] * m2[13] + m1[11] * m2[14] + m1[15] * m2[15];
}

void matrix_mult(float *m1, const float *m2)
{
    float m[16];
    m[0] =  m1[0] * m2[0] + m1[4] * m2[1] + m1[8]  * m2[2] + m1[12] * m2[3];
    m[1] =  m1[1] * m2[0] + m1[5] * m2[1] + m1[9]  * m2[2] + m1[13] * m2[3];
    m[2] =  m1[2] * m2[0] + m1[6] * m2[1] + m1[10] * m2[2] + m1[14] * m2[3];
    m[3] =  m1[3] * m2[0] + m1[7] * m2[1] + m1[11] * m2[2] + m1[15] * m2[3];

    m[4] =  m1[0] * m2[4] + m1[4] * m2[5] + m1[8]  * m2[6] + m1[12] * m2[7];
    m[5] =  m1[1] * m2[4] + m1[5] * m2[5] + m1[9]  * m2[6] + m1[13] * m2[7];
    m[6] =  m1[2] * m2[4] + m1[6] * m2[5] + m1[10] * m2[6] + m1[14] * m2[7];
    m[7] =  m1[3] * m2[4] + m1[7] * m2[5] + m1[11] * m2[6] + m1[15] * m2[7];

    m[8]  = m1[0] * m2[8] + m1[4] * m2[9] + m1[8]  * m2[10] + m1[12] * m2[11];
    m[9]  = m1[1] * m2[8] + m1[5] * m2[9] + m1[9]  * m2[10] + m1[13] * m2[11];
    m[10] = m1[2] * m2[8] + m1[6] * m2[9] + m1[10] * m2[10] + m1[14] * m2[11];
    m[11] = m1[3] * m2[8] + m1[7] * m2[9] + m1[11] * m2[10] + m1[15] * m2[11];

    m[12] = m1[0] * m2[12] + m1[4] * m2[13] + m1[8]  * m2[14] + m1[12] * m2[15];
    m[13] = m1[1] * m2[12] + m1[5] * m2[13] + m1[9]  * m2[14] + m1[13] * m2[15];
    m[14] = m1[2] * m2[12] + m1[6] * m2[13] + m1[10] * m2[14] + m1[14] * m2[15];
    m[15] = m1[3] * m2[12] + m1[7] * m2[13] + m1[11] * m2[14] + m1[15] * m2[15];

    memcpy(m1, m, 16 * sizeof(float));
}
*/

void glnTranslate(gln_matrices *m, float x, float y, float z)
{
    float m0  = m->modelview[0];
    float m1  = m->modelview[1];
    float m2  = m->modelview[2];
    float m3  = m->modelview[3];
    float m4  = m->modelview[4];
    float m5  = m->modelview[5];
    float m6  = m->modelview[6];
    float m7  = m->modelview[7];
    float m8  = m->modelview[8];
    float m9  = m->modelview[9];
    float m10 = m->modelview[10];
    float m11 = m->modelview[11];
    float m12 = m->modelview[12];
    float m13 = m->modelview[13];
    float m14 = m->modelview[14];
    float m15 = m->modelview[15];

    m->modelview[12] = (m0 * x) + (m4 * y) + (m8  * z) + (m12);
    m->modelview[13] = (m1 * x) + (m5 * y) + (m9  * z) + (m13);
    m->modelview[14] = (m2 * x) + (m6 * y) + (m10 * z) + (m14);
    m->modelview[15] = (m3 * x) + (m7 * y) + (m11 * z) + (m15);
}

void glnScale(gln_matrices *m, float x, float y, float z)
{
    float m0  = m->modelview[0];
    float m1  = m->modelview[1];
    float m2  = m->modelview[2];
    float m3  = m->modelview[3];
    float m4  = m->modelview[4];
    float m5  = m->modelview[5];
    float m6  = m->modelview[6];
    float m7  = m->modelview[7];
    float m8  = m->modelview[8];
    float m9  = m->modelview[9];
    float m10 = m->modelview[10];
    float m11 = m->modelview[11];

    m->modelview[0]  = (m0 * x);
    m->modelview[1]  = (m1 * x);
    m->modelview[2]  = (m2 * x);
    m->modelview[3]  = (m3 * x);
    m->modelview[4]  = (m4 * y);
    m->modelview[5]  = (m5 * y);
    m->modelview[6]  = (m6 * y);
    m->modelview[7]  = (m7 * y);
    m->modelview[8]  = (m8 * z);
    m->modelview[9]  = (m9 * z);
    m->modelview[10] = (m10 * z);
    m->modelview[11] = (m11 * z);
}

void glnRotated(gln_matrices *m, double angle, double x, double y, double z)
{
    double a = angle * GLN_DEG_TO_RAD;

    /* normalise vector */
    double len = sqrt(x * x + y * y + z * z);
    double nx = x / len;
    double ny = y / len;
    double nz = z / len;

    double sin_a = sin(a);

    double qx = nx * sin_a;
    double qy = ny * sin_a;
    double qz = nz * sin_a;
    double qw = cos(a);

    double x2 = qx * qx;
    double y2 = qy * qy;
    double z2 = qz * qz;
    double xy = qx * qy;
    double xz = qx * qz;
    double yz = qy * qz;
    double wx = qw * qx;
    double wy = qw * qy;
    double wz = qw * qz;

    double r_0  = 1.0 - 2.0 * (y2 + z2);
    double r_1  = 2.0 * (xy - wz);
    double r_2  = 2.0 * (xz + wy);
    double r_4  = 2.0 * (xy + wz);
    double r_5  = 1.0 - 2.0 * (x2 + z2);
    double r_6  = 2.0 * (yz - wx);
    double r_8  = 2.0 * (xz - wy);
    double r_9  = 2.0 * (yz + wx);
    double r_10 = 1.0 - 2.0 * (x2 + y2);

    double m_0  = m->modelview[0];
    double m_1  = m->modelview[1];
    double m_2  = m->modelview[2];
    double m_3  = m->modelview[3];
    double m_4  = m->modelview[4];
    double m_5  = m->modelview[5];
    double m_6  = m->modelview[6];
    double m_7  = m->modelview[7];
    double m_8  = m->modelview[8];
    double m_9  = m->modelview[9];
    double m_10 = m->modelview[10];
    double m_11 = m->modelview[11];

    m->modelview[0]  =  (m_0 * r_0) + (m_4 * r_1) + (m_8  * r_2 );
    m->modelview[1]  =  (m_1 * r_0) + (m_5 * r_1) + (m_9  * r_2 );
    m->modelview[2]  =  (m_2 * r_0) + (m_6 * r_1) + (m_10 * r_2 );
    m->modelview[3]  =  (m_3 * r_0) + (m_7 * r_1) + (m_11 * r_2 );
    m->modelview[4]  =  (m_0 * r_4) + (m_4 * r_5) + (m_8  * r_6 );
    m->modelview[5]  =  (m_1 * r_4) + (m_5 * r_5) + (m_9  * r_6 );
    m->modelview[6]  =  (m_2 * r_4) + (m_6 * r_5) + (m_10 * r_6 );
    m->modelview[7]  =  (m_3 * r_4) + (m_7 * r_5) + (m_11 * r_6 );
    m->modelview[8]  =  (m_0 * r_8) + (m_4 * r_9) + (m_8  * r_10);
    m->modelview[9]  =  (m_1 * r_8) + (m_5 * r_9) + (m_9  * r_10);
    m->modelview[10] =  (m_2 * r_8) + (m_6 * r_9) + (m_10 * r_10);
    m->modelview[11] =  (m_3 * r_8) + (m_7 * r_9) + (m_11 * r_10);
}

void glnRotatef(gln_matrices *m, float angle, float x, float y, float z)
{
    glnRotated(m, (double)angle, (double)x, (double)y, (double)z);
}

/* vim: sw=4 sts=4 ts=4 et nowrap
 */
