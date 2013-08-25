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

void sfProcessEvents(sfRenderWindow* App, gln_matrices *matrices)
{
    sfEvent Event;
    while (sfRenderWindow_GetEvent(App, &Event))
    {
      if (Event.Type == sfEvtClosed ||
         ((Event.Type == sfEvtKeyPressed) && (Event.Key.Code == sfKeyEscape)))
          sfRenderWindow_Close(App);

      if (Event.Type == sfEvtResized) {
          glViewport(0, 0, Event.Size.Width, Event.Size.Height);
          glnPerspective(matrices, 60.0,
                      (double) Event.Size.Width /
                      (double) Event.Size.Height, 0.2, 40.0);
      }
    }
}

int main()
{
    int width = 800;
    int height = 600;

    gln_matrices matrices;
    gln_drawMeshParams dm_params;

    /* set the light direction */
    dm_params.light_dir[0] =  0.0;  /* x */
    dm_params.light_dir[1] = -1.0;  /* y */
    dm_params.light_dir[2] =  0.0;  /* z */

    dm_params.color[0] = 1.0;  /* r */
    dm_params.color[1] = 0.0;  /* g */
    dm_params.color[2] = 0.0;  /* b */

    sfRenderWindow* App;
    sfClock *Clock;
    sfWindowSettings Settings = {24, 8, 0};
    sfVideoMode Mode = {width, height, 32};

    App = sfRenderWindow_Create(
                Mode, "gln sphere example",
                sfResize | sfClose, Settings);
    if (!App) return EXIT_FAILURE;

    sfRenderWindow_PreserveOpenGLStates(App, sfTrue);

    /* the opengl context has to be set before calling glnMakeSphere() */
    double radius = 1.0;
    int slices = 32;
    int stacks = 16;
    gln_mesh *my_mesh =
        glnMakeSphere(
                radius, slices, stacks, GLN_GEN_NORMALS);

    /* enable Z-buffer read and write */
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);

    /* enable back face culling */
    glFrontFace(GL_CCW);     /* assume a clean model */
    glEnable(GL_CULL_FACE);  /* activate elimination of polygons */
    glCullFace(GL_BACK);     /* remove back side of polygons */

    /* background color */
    glClearColor(0.3, 0.3, 0.3, 1.0);

    /* set up a perspective projection matrix */
    glnPerspective(&matrices,
                60.0, (double) width / (double) height, 0.2, 40.0);

    /* create a clock for measuring the time elapsed */
    Clock = sfClock_Create();

    /* start the main loop */
    while (sfRenderWindow_IsOpened(App))
    {
        float time = sfClock_GetTime(Clock);
        sfProcessEvents(App, &matrices);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        /* Apply some transformations */
        glnLoadIdentity(&matrices);
        glnTranslate(&matrices, 0.0, 0.0, -5.0);
        glnRotated(&matrices, time * 50.0, 1.0, 0.0, 0.0);
        glnRotated(&matrices, time * 30.0, 0.0, 1.0, 0.0);
        glnRotated(&matrices, time * 90.0, 0.0, 0.0, 1.0);

        float v = (cosf(time) + 1.0) / 2.0;
        dm_params.color[0] = v;        /* r */
        dm_params.color[1] = 1.0 - v;  /* g */
        dm_params.color[2] = 0.0;      /* b */

        glnDrawMesh(my_mesh, &matrices, &dm_params);

        sfRenderWindow_Display(App);
    }

    /* cleanup gln-lib resources */
    glnDeleteMesh(my_mesh);

    /* cleanup windowing resources */
    sfClock_Destroy(Clock);
    sfRenderWindow_Destroy(App);

    return EXIT_SUCCESS;
}

