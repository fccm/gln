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

/* ==== Get Shaders Sources ================================ */

typedef enum {
    GLN_GLSL_VERSION_120,
    GLN_GLSL_VERSION_130
} gln_glslVersion;


const char *plain_color_vertex_shader (gln_glslVersion);
const char *plain_uniform_color (gln_glslVersion);

void static_color3 (gln_glslVersion glsl_version, float *color, char *buf, int buf_len);
void static_color4 (gln_glslVersion glsl_version, float *color, char *buf, int buf_len);

const char *interpolate_rgb_vert (gln_glslVersion);
const char *interpolate_rgb_frag (gln_glslVersion);

const char *interpolate_uv_vert (gln_glslVersion);
const char *interpolate_uv_frag (gln_glslVersion);

const char *interpolate_uv_rgb_vert (gln_glslVersion);
const char *interpolate_uv_rgb_frag (gln_glslVersion);

const char *interpolate_normal_vert (gln_glslVersion);
const char *interpolate_normal_frag (gln_glslVersion);

const char *interpolate_normal_rgb_vert (gln_glslVersion);
const char *interpolate_normal_rgb_frag (gln_glslVersion);

const char *interpolate_normal_uv_vert (gln_glslVersion);
const char *interpolate_normal_uv_frag (gln_glslVersion);

/* vim: sw=4 sts=4 ts=4 et
 */
