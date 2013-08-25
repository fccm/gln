GLN is an OpenGL utility library providing to the C programmers
a set of functions for geometric object rendering.
The primitives that it currently provides for use in OpenGL applications
are spheres and torus. Cylinders, cones, and disks are planed.

GLN source code is available under the MIT license.
All the files available in this archive are provided with the same
conditions.
Alternatively if you find more convenient to use all this under BSD license,
or zlib/png license, or GPL/LGPL license, or ISC, then just help yourself.

The GLN main characteristic is that GLN implementation is "legacy-free"
or in other words "forward-compatible".  Indeed it uses VBOs and GLSL
(Vertex Buffer Object and OpenGL Shading Language), and does not use any
deprecated OpenGL functions.

GLN functions all have gln as prefix.  An example function is glnMakeSphere()
which creates a sphere mesh which can be drawn in an efficient way.

GLN tries to be easy to use, here is an example to draw a sphere. First in the
initialisation stage we generate a mesh of the sphere with glnMakeSphere()
then in the main loop we draw it with glnDrawMesh(), and when we're off
we clean (free) with glnDeleteMesh():

  my_sphere = glnMakeSphere( /* parameters */ );

  glnDrawMesh( my_sphere, /* parameters */ );

  glnDeleteMesh( my_sphere );

