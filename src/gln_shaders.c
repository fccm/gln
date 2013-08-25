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

#include "gln_shaders.h"

#include "gln_shaders_120.h"
#include "gln_shaders_130.h"

/* ==== Provide Shaders Sources ================================ */

void static_color3 (
        gln_glslVersion glsl_version, float color[4], char *buf, int buf_len)
{
    const char *_static_color3;
    switch (glsl_version)
    {
        case GLN_GLSL_VERSION_120: _static_color3 = static_color3_120; break;
        case GLN_GLSL_VERSION_130: _static_color3 = static_color3_130; break;
    }
    snprintf(buf, buf_len, _static_color3, color[0], color[1], color[2]);
}

void static_color4 (
        gln_glslVersion glsl_version, float color[4], char *buf, int buf_len)
{
    const char *_static_color4;
    switch (glsl_version)
    {
        case GLN_GLSL_VERSION_120: _static_color4 = static_color4_120; break;
        case GLN_GLSL_VERSION_130: _static_color4 = static_color4_130; break;
    }
    snprintf(buf, buf_len, _static_color4, color[0], color[1], color[2]);
}

static const char shade_err[] = "Error";

#define RETURN_SHADER(gln_shader) \
const char *gln_shader (gln_glslVersion glsl_version) { \
    switch (glsl_version) { \
        case GLN_GLSL_VERSION_120: return gln_shader##_120; \
        case GLN_GLSL_VERSION_130: return gln_shader##_130; \
    } \
    return shade_err; }

RETURN_SHADER(plain_color_vertex_shader)
RETURN_SHADER(plain_uniform_color)
RETURN_SHADER(interpolate_rgb_vert)
RETURN_SHADER(interpolate_rgb_frag)
RETURN_SHADER(interpolate_uv_vert)
RETURN_SHADER(interpolate_uv_frag)
RETURN_SHADER(interpolate_uv_rgb_vert)
RETURN_SHADER(interpolate_uv_rgb_frag)
RETURN_SHADER(interpolate_normal_vert)
RETURN_SHADER(interpolate_normal_frag)
RETURN_SHADER(interpolate_normal_rgb_vert)
RETURN_SHADER(interpolate_normal_rgb_frag)
RETURN_SHADER(interpolate_normal_uv_vert)
RETURN_SHADER(interpolate_normal_uv_frag)

/* vim: sw=4 sts=4 ts=4 et
 */
