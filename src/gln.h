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

#ifndef _GLN_H
#define _GLN_H

/* ==== Meshes ==== */

typedef enum {
    GLN_PLAINCOLOR3_VERTICES3,  /* float [3] */
    /* all the vertices are colored with the same color provided
       with the color member of the structure gln_meshSrc,
       where only the 3 first components are used */

    GLN_PLAINCOLOR4_VERTICES3,  /* float [3] */
    /* same than GLN_PLAINCOLOR3_VERTICES3 but all the 4 components of
       the color member of gln_meshSrc are used */

    GLN_VERTICES3,              /* float [3] */
    /* all the vertices are colored with the same color provided
       as the color member of the structure gln_drawMeshParams */

    GLN_RGB_VERTICES3,          /* float [6] */
    /* all the vertices have an associated RGB color, with this kind of data
       no fields from the structure gln_drawMeshParams are used */

    GLN_UV_VERTICES3,           /* float [5] */
    /* simple texture application with UV (2D coordinates),
       this lib does not handle loading/binding the image so you should
       do it yourself before calling glnDrawMesh() */

    GLN_UV_RGB_VERTICES3,       /* float [8] */
    /* Same than GLN_UV_VERTICES3, but vertices are colored,
       so you should provide the texenv parameter from the structure
       gln_drawMeshParams to select how to mix the vertex color with
       the texture texel. */

    GLN_NORMAL_VERTICES3,       /* float [6] */
    /* Providing normals enables the use of a directional light.
       The direction of this directional light is provided with the
       light_dir member of the structure gln_drawMeshParameters.
       The normals should be normalised, this lib does not do it for you.
       The vector light_dir should be normalised too. */

    GLN_NORMAL_RGB_VERTICES3,   /* float [9] */
    /* Same than with GLN_NORMAL_VERTICES3, but vertices are colored */

    GLN_NORMAL_UV_VERTICES3     /* float [8] */

} gln_verticesKind;
/* the data should be store in the same order that it appears in this enum,
   for example for GLN_UV_RGB_VERTICES3 give the UV texture coordinates first,
   then the RGB color, and finally the XYZ 3D coordinates */


typedef struct _glnMeshSrc
{
    gln_verticesKind vertices_kind;
    float *vertices;
    /* not the number of vertices but the number of floats in the array */
    unsigned int vertices_size;
    unsigned int *indices;
    unsigned int indices_size;
    float color[4]; /* only used with the type GLN_PLAINCOLOR(3|4)_VERTICES3 */
} gln_meshSrc;


typedef enum {
    GLN_MODULATE,    /* multiply texture color and vertex color,
                        the result is a nice mix */
    GLN_DECAL,       /* in the transparent parts of the texture,
                        use the vertex color */
    GLN_ADD,
    GLN_ADD_SIGNED,
    GLN_SUBTRACT
} gln_texEnv;


typedef enum {
    GLN_PER_PIXEL,   /* calculate the lighting in the fragment shader */
    GLN_PER_VERTEX   /* calculate the lighting in the vertex shader */
} gln_lighting;


typedef struct _gln_drawMeshParameters
{
    float color[3];
    /* provide this parameter only with GLN_VERTICES3 or GLN_NORMAL_VERTICES3
       data. */

    float light_dir[4];
    /* direction for a directional light (the vector should be normalised),
       provide this parameter only for meshes created with vertices that have
       associated normals. Without normals lighting can not be done. */

    gln_texEnv texenv;
    /* provide this parameter only with GLN_UV_RGB_VERTICES3 data where it is
       used to select how to mix the vertex color with the texture texel. */
} gln_drawMeshParams;


typedef struct _gln_mesh gln_mesh; 


gln_mesh* glnMakeMesh( gln_meshSrc* mesh_src );
void glnDeleteMesh( gln_mesh* mesh );

typedef struct _gln_matrices
{
    float modelview[16];
    float projection[16];
} gln_matrices;

void glnDrawMesh(
        gln_mesh *mesh,
        gln_matrices *matrices,
        gln_drawMeshParams *params );

int glnGetStride(gln_verticesKind k);


/* ==== Matrices Handling ==== */

/* set up a perspective projection matrix */
void glnPerspective(
        gln_matrices *matrices,
        double fovy, double aspect, double zNear, double zFar);

/* replace the current modelview matrix with the identity matrix */
void glnLoadIdentity(gln_matrices *matrices);

void glnTranslate(gln_matrices *m, float x, float y, float z);
void glnScale(gln_matrices *m, float x, float y, float z);
void glnRotated(gln_matrices *m, double angle, double x, double y, double z);
void glnRotatef(gln_matrices *m, float angle, float x, float y, float z);

void glnCopyMatrices(gln_matrices *src, gln_matrices *dst);


/* ==== Geometric Objects ==== */

#define GLN_GEN_NORMALS (1<<0)
#define GLN_GEN_UV      (1<<1)
/*define GLN_WIREFRAME  (1<<2)  TODO */

/* Sphere */

gln_mesh* glnMakeSphere(
    double radius, unsigned int slices, unsigned int stacks,
    unsigned int params );

gln_meshSrc* glnGetSphereSrc(
    double radius, unsigned int slices, unsigned int stacks,
    unsigned int params );

/*
  slices specifies the number of subdivisions around the Z axis
  (similar to lines of longitude, so a full circle)

  stacks specifies the number of subdivisions along the Z axis
  (similar to lines of latitude, so half a circle)

  in a classic use, slices will be twice than stacks.
  (for example slices = 32 and stacks = 16)
*/

/* Torus */

gln_mesh* glnMakeTorus(
    double inner_radius, double outer_radius,
    unsigned int sides, unsigned int rings,
    unsigned int params );

gln_meshSrc* glnGetTorusSrc(
    double inner_radius, double outer_radius,
    unsigned int sides, unsigned int rings,
    unsigned int params );

/* Cylinder */

gln_mesh* glnMakeCylinder(
    double radius, double bottom, double top,
    unsigned int slices, unsigned int stacks,
    unsigned int params );

gln_meshSrc* glnGetCylinderSrc(
    double radius, double bottom, double top,
    unsigned int slices, unsigned int stacks,
    unsigned int params );

#endif /* _GLN_H */
/* vim: sw=4 sts=4 ts=4 et
 */
