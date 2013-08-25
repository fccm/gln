/*
 Copyright (c) 2010 Florent Monnier
 
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

#ifndef _GLN_INTERN_H
#define _GLN_INTERN_H

#include "gln.h"

/* types which internal contents are hidden in the public interface */

#if defined(DO_FORWARD_COMPATIBLE)

typedef enum {
    GLN_SHAD_BASE,
    GLN_SHAD_COLOR,
    GLN_SHAD_COLOR_ATTRIB,
    GLN_SHAD_UV_ATTRIB,
    GLN_SHAD_UV_COLOR_ATTRIB,
    GLN_SHAD_NORMAL_ATTRIB,
    GLN_SHAD_NORMAL_COLOR_ATTRIB,
    GLN_SHAD_NORMAL_UV_ATTRIB
} gln_shadingType;

typedef struct _gln_shading
{
    gln_shadingType type;

    GLuint shaderProgram;
    GLuint vertexShader;
    GLuint fragmentShader;

    GLint locations[8];
    /* contains uniform and attrib locations */

} gln_shading;

struct _gln_mesh
{
    GLuint vboIds[2];
    unsigned int elem_buf_len;
    GLenum elem_type;
    /* one of GL_UNSIGNED_BYTE, GL_UNSIGNED_SHORT or GL_UNSIGNED_INT */
    gln_shading shading;
};

#else /* DO_FORWARD_COMPATIBLE */

struct _gln_mesh
{
    gln_verticesKind vertices_kind;
    float *vertices;
    /* not the number of vertices but the number of floats in the array */
    unsigned int vertices_size;
    unsigned int *indices;
    unsigned int indices_size;
    float color[4]; /* only used with the type GLN_PLAINCOLOR(3|4)_VERTICES3 */
};

#endif /* DO_FORWARD_COMPATIBLE */


#define GLN_GEN_NORMALS_ONLY   (GLN_GEN_NORMALS)
#define GLN_GEN_UV_ONLY        (GLN_GEN_UV)
#define GLN_GEN_NORMALS_AND_UV (GLN_GEN_NORMALS | GLN_GEN_UV)


#endif /* _GLN_INTERN_H */
/* vim: sw=4 sts=4 ts=4 et
 */
