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

/* ==== Simple Example ================================ */

#include <gln.h>
#include <math.h>

/* using the sfml for windowing */

#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <string.h>

void sfProcessEvents(
        sfRenderWindow* App, gln_matrices *matrices, int *width, int *height)
{
    sfEvent Event;
    while (sfRenderWindow_GetEvent(App, &Event))
    {
      if (Event.Type == sfEvtClosed ||
         ((Event.Type == sfEvtKeyPressed) && (Event.Key.Code == sfKeyEscape))) {
          sfRenderWindow_Close(App);
      }

      if (Event.Type == sfEvtResized) {
          glnPerspective(matrices, 60.0, (double) (Event.Size.Width/2) /
                                         (double) Event.Size.Height, 0.2, 40.0);
          *width = Event.Size.Width;
          *height = Event.Size.Height;
      }
    }
}

int main()
{
    int width = 1024;
    int height = 768;

    gln_matrices matrices;
    gln_drawMeshParams dm_params;

    sfRenderWindow* App;
    sfClock *Clock;
    sfWindowSettings Settings = {24, 8, 0};
    sfVideoMode Mode = {width, height, 32};

    float gl_matrix[16];

    App = sfRenderWindow_Create(
                Mode, "gln's torus",
                sfResize | sfClose, Settings);
    if (!App) return EXIT_FAILURE;

    sfRenderWindow_PreserveOpenGLStates(App, sfTrue);

    /* the opengl context has to be set before calling glnMakeTorus() */
    double inner_radius = 0.4;
    double outer_radius = 1.2;
    unsigned int sides = 32;
    unsigned int rings = 64;

    int gen_base           = 0;
    int gen_uv_only        = GLN_GEN_UV;
    int gen_normals_only   = GLN_GEN_NORMALS;
    int gen_normals_and_uv = GLN_GEN_NORMALS | GLN_GEN_UV;

    gln_mesh *my_mesh =
        glnMakeTorus(inner_radius, outer_radius, sides, rings, gen_uv_only);


    /* load an OpenGL texture */
    GLuint Texture = 0;
    {
        sfImage* Image;
        Image = sfImage_CreateFromFile("./texture.png");
        if (!Image) return EXIT_FAILURE;

        glGenTextures(1, &Texture);
        glBindTexture(GL_TEXTURE_2D, Texture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
                     sfImage_GetWidth(Image),
                     sfImage_GetHeight(Image), 0,
                     GL_RGBA, GL_UNSIGNED_BYTE,
                     sfImage_GetPixelsPtr(Image));

        sfImage_Destroy(Image);
    }

    /* bind our texture */
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, Texture);

    /* enable Z-buffer read and write */
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);

    /* enable back face culling */
    glFrontFace(GL_CCW);     /* assume a clean model */
    glEnable(GL_CULL_FACE);  /* activate elimination of polygons */
    glCullFace(GL_BACK);     /* remove back side of polygons */

    /* background color */
    glClearColor(0.3, 0.3, 0.35, 1.0);

    /* set up a perspective projection matrix */
    glnPerspective(&matrices, 60.0, (double) (width/2) / (double) height, 0.2, 40.0);

    /* create a clock for measuring the time elapsed */
    Clock = sfClock_Create();

    /* start the main loop */
    while (sfRenderWindow_IsOpened(App))
    {
        sfProcessEvents(App, &matrices, &width, &height);

        float time = sfClock_GetTime(Clock);

        float v = (cosf(time) + 1.0) / 2.0;
        dm_params.color[0] = v;        /* r */
        dm_params.color[1] = 1.0 - v;  /* g */
        dm_params.color[2] = 0.0;      /* b */

        float a = time * 1.1f;
        float b = time * 0.9f;
        /* set the light direction */
        dm_params.light_dir[0] = cosf(a) * cosf(b);  /* x */
        dm_params.light_dir[1] = cosf(a) * sinf(b);  /* y */
        dm_params.light_dir[2] = sinf(a);            /* z */

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glViewport(0, 0, width/2, height);

        /* apply some transformations */
        glMatrixMode(GL_MODELVIEW);
        /* let's cheat (this part is not legacy free) */
        glLoadIdentity();
        glTranslated(0.0, 0.0, -5.0);
        glRotatef(time * 12.0f, 1.0f, 0.0f, 0.0f);
        glRotatef(time * 20.0f, 0.0f, 1.0f, 0.0f);
        glRotatef(time * 36.0f, 0.0f, 0.0f, 1.0f);
        glGetFloatv(GL_MODELVIEW_MATRIX, matrices.modelview);

        glnDrawMesh(my_mesh, &matrices, &dm_params);

        glViewport(width/2, 0, width/2, height);

        /* apply some transformations */
        glnLoadIdentity(&matrices);
        glnTranslate(&matrices, 0.0, 0.0, -5.0);
        glnRotated(&matrices, time * 12.0, -1.0, 0.0, 0.0);
        glnRotated(&matrices, time * 20.0, 0.0, -1.0, 0.0);
        glnRotated(&matrices, time * 36.0, 0.0, 0.0, -1.0);

        glnDrawMesh(my_mesh, &matrices, &dm_params);

        sfRenderWindow_Display(App);
    }

    /* cleanup gln-lib resources */
    glnDeleteMesh(my_mesh);

    /* don't forget to destroy our texture */
    glDeleteTextures(1, &Texture);

    /* cleanup windowing resources */
    sfClock_Destroy(Clock);
    sfRenderWindow_Destroy(App);

    return EXIT_SUCCESS;
}

