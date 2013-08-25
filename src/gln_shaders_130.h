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


/* ==== Shaders Sources ================================ */

static const char plain_color_vertex_shader_130[] =
    /* vertex shader */
    "#version 130\n"
    "in vec3 VertexPosition;\n"
    "uniform mat4 ProjectionMatrix;\n"
    "uniform mat4 ModelViewMatrix;\n"
    "invariant gl_Position;\n"
    "void main () {\n"
    "    mat4 ModelViewProjectionMatrix = ProjectionMatrix * ModelViewMatrix;\n"
    "    gl_Position = ModelViewProjectionMatrix * vec4 (VertexPosition, 1.0);\n"
    "}\n";

static const char static_color3_130[] =
    /* fragment shader */
    "#version 130\n"
    "precision highp float;\n"
    "out vec4 Color;\n"
    "void main() {\n"
    "    Color = vec4 (%f,%f,%f,1.0);\n"
    "}\n";

static const char static_color4_130[] =
    /* fragment shader */
    "#version 130\n"
    "precision highp float;\n"
    "out vec4 Color;\n"
    "void main() {\n"
    "    Color = vec4 (%f,%f,%f,%f);\n"
    "}\n";

static const char plain_uniform_color_130[] =
    /* fragment shader */
    "#version 130\n"
    "precision highp float;\n"
    "uniform vec3 PlainColor;\n"
    "out vec4 Color;\n"
    "void main() {\n"
    "    Color = vec4 (PlainColor, 1.0);\n"
    "}\n";

/* interpolate RGB colors of the vertices, no lighting */
static const char interpolate_rgb_vert_130[] =
    /* vertex shader */
    "#version 130\n"
    "in vec3 VertexColor;\n"
    "in vec3 VertexPosition;\n"
    "uniform mat4 ProjectionMatrix;\n"
    "uniform mat4 ModelViewMatrix;\n"
    "invariant gl_Position;\n"
    "smooth out vec3 InterpolatedColor;\n"
    "void main () {\n"
    "    mat4 ModelViewProjectionMatrix = ProjectionMatrix * ModelViewMatrix;\n"
    "    InterpolatedColor = VertexColor;\n"
    "    gl_Position = ModelViewProjectionMatrix * vec4 (VertexPosition, 1.0);\n"
    "}\n";

static const char interpolate_rgb_frag_130[] =
    /* fragment shader */
    "#version 130\n"
    "precision highp float;\n"
    "smooth in vec3 InterpolatedColor;\n"
    "out vec4 Color;\n"
    "void main() {\n"
    "    Color = vec4 (InterpolatedColor, 1.0);\n"
    "}\n";

/* interpolate UV texture coordinates, no color, do replace */
static const char interpolate_uv_vert_130[] =
    /* vertex shader */
    "#version 130\n"
    "in vec2 VertexUV;\n"
    "in vec3 VertexPosition;\n"
    "uniform mat4 ProjectionMatrix;\n"
    "uniform mat4 ModelViewMatrix;\n"
    "invariant gl_Position;\n"
    "smooth out vec2 InterpolatedUV;\n"
    "void main () {\n"
    "    mat4 ModelViewProjectionMatrix = ProjectionMatrix * ModelViewMatrix;\n"
    "    InterpolatedUV = VertexUV;\n"
    "    gl_Position = ModelViewProjectionMatrix * vec4 (VertexPosition, 1.0);\n"
    "}\n";

static const char interpolate_uv_frag_130[] =
    /* fragment shader */
    "#version 130\n"
    "precision highp float;\n"
    "uniform sampler2D texture0;\n"
    "smooth in vec2 InterpolatedUV;\n"
    "out vec4 Color;\n"
    "void main() {\n"
    "    Color = texture(texture0, InterpolatedUV);\n"
    "}\n";

/* interpolate RGB and UV */
static const char interpolate_uv_rgb_vert_130[] =
    /* vertex shader */
    "#version 130\n"
    "in vec2 VertexUV;\n"
    "in vec3 VertexColor;\n"
    "in vec3 VertexPosition;\n"
    "uniform mat4 ProjectionMatrix;\n"
    "uniform mat4 ModelViewMatrix;\n"
    "invariant gl_Position;\n"
    "smooth out vec3 InterpolatedColor;\n"
    "smooth out vec2 InterpolatedUV;\n"
    "void main () {\n"
    "    mat4 ModelViewProjectionMatrix = ProjectionMatrix * ModelViewMatrix;\n"
    "    InterpolatedUV = VertexUV;\n"
    "    InterpolatedColor = VertexColor;\n"
    "    gl_Position = ModelViewProjectionMatrix * vec4 (VertexPosition, 1.0);\n"
    "}\n";

static const char interpolate_uv_rgb_frag_130[] =
    /* fragment shader */
    "#version 130\n"
    "precision highp float;\n"
    "uniform sampler2D texture0;\n"
    "uniform int TexEnv;\n"
    "smooth in vec3 InterpolatedColor;\n"
    "smooth in vec2 InterpolatedUV;\n"
    "out vec4 Color;\n"
    "void main() {\n"
    "    vec4 vert_color = vec4(InterpolatedColor, 1.0);\n"
    "    vec4 tex_color = texture(texture0, InterpolatedUV);\n"
    "    if (TexEnv == 0) {  // MODULATE\n"
    "        Color = vert_color * tex_color;\n"
    "    } else\n"
    "    if (TexEnv == 1) {  // DECAL\n"
    "        vec3 col = mix(vert_color.rgb, tex_color.rgb, tex_color.a);\n"
    "        Color = vec4(col, vert_color.a);\n"
    "    } else\n"
    "    if (TexEnv == 2) {  // ADD\n"
    "        vert_color.rgb += tex_color.rgb;\n"
    "        vert_color.a *= tex_color.a;\n"
    "        Color = clamp(vert_color, 0.0, 1.0);\n"
    "    } else\n"
    "    if (TexEnv == 3) {  // ADD_SIGNED\n"
    "        vert_color.rgb += tex_color.rgb;\n"
    "        vert_color.rgb -= vec3(0.5, 0.5, 0.5);\n"
    "        vert_color.a *= tex_color.a;\n"
    "        Color = clamp(vert_color, 0.0, 1.0);\n"
    "    } else\n"
    "    if (TexEnv == 4) {  // SUBTRACT\n"
    "        vert_color.rgb -= tex_color.rgb;\n"
    "        vert_color.a *= tex_color.a;\n"
    "        Color = clamp(vert_color, 0.0, 1.0);\n"
    "    } else\n"
    "    Color = tex_color;  // REPLACE\n"
    "    //Color = vec4(1.0, 0.0, 0.0, 1.0); // DEBUG\n"
    "}\n";

/* combine lighting and RGB colors of the vertices */
static const char interpolate_normal_vert_130[] =
    /* vertex shader */
    "#version 130\n"
    "in vec3 VertexNormal;\n"
    "in vec3 VertexPosition;\n"
    "uniform mat4 ProjectionMatrix;\n"
    "uniform mat4 ModelViewMatrix;\n"
    "uniform vec3 PlainColor;\n"
    "uniform vec3 lightDir;\n"
    "invariant gl_Position;\n"
    "smooth out vec3 InterpolatedColor;\n"
    "const float pi = 3.141592653589793;\n"
    "void main () {\n"
    "    mat4 ModelViewProjectionMatrix = ProjectionMatrix * ModelViewMatrix;\n"
    "    float NdotL = dot(VertexNormal, lightDir);\n"
    "    InterpolatedColor = ((NdotL + 1.0) / 2.0) * PlainColor;\n"
    "    gl_Position = ModelViewProjectionMatrix * vec4 (VertexPosition, 1.0);\n"
    "}\n";

static const char interpolate_normal_frag_130[] =
    /* fragment shader */
    "#version 130\n"
    "precision highp float;\n"
    "smooth in vec3 InterpolatedColor;\n"
    "out vec4 Color;\n"
    "void main() {\n"
    "    Color = vec4 (InterpolatedColor, 1.0);\n"
    "}\n";

/* combine lighting and RGB colors of the vertices */
static const char interpolate_normal_rgb_vert_130[] =
    /* vertex shader */
    "#version 130\n"
    "in vec3 VertexNormal;\n"
    "in vec3 VertexColor;\n"
    "in vec3 VertexPosition;\n"
    "uniform mat4 ProjectionMatrix;\n"
    "uniform mat4 ModelViewMatrix;\n"
    "uniform vec3 lightDir;\n"
    "invariant gl_Position;\n"
    "smooth out vec3 InterpolatedColor;\n"
    "const float pi = 3.141592653589793;\n"
    "void main () {\n"
    "    mat4 ModelViewProjectionMatrix = ProjectionMatrix * ModelViewMatrix;\n"
    "    float NdotL = dot(VertexNormal, lightDir);\n"
    "    InterpolatedColor = ((NdotL + 1.0) / 2.0) * VertexColor;\n"
    "    gl_Position = ModelViewProjectionMatrix * vec4 (VertexPosition, 1.0);\n"
    "}\n";

static const char interpolate_normal_rgb_frag_130[] =
    /* fragment shader */
    "#version 130\n"
    "precision highp float;\n"
    "smooth in vec3 InterpolatedColor;\n"
    "out vec4 Color;\n"
    "void main() {\n"
    "    Color = vec4 (InterpolatedColor, 1.0);\n"
    "}\n";

/* lighting and texture */
static const char interpolate_normal_uv_vert_130[] =
    /* vertex shader */
    "#version 130\n"
    "in vec3 VertexNormal;\n"
    "in vec2 VertexUV;\n"
    "in vec3 VertexPosition;\n"
    "uniform mat4 ProjectionMatrix;\n"
    "uniform mat4 ModelViewMatrix;\n"
    "uniform vec3 lightDir;\n"
    "invariant gl_Position;\n"
    "smooth out vec2 InterpolatedUV;\n"
    "smooth out float InterpolatedLighted;\n"
    "const float pi = 3.141592653589793;\n"
    "void main () {\n"
    "    mat4 ModelViewProjectionMatrix = ProjectionMatrix * ModelViewMatrix;\n"
    "    float NdotL = dot(VertexNormal, lightDir);\n"
    "    InterpolatedLighted = ((NdotL + 1.0) / 2.0);\n"
    "    InterpolatedUV = VertexUV;\n"
    "    gl_Position = ModelViewProjectionMatrix * vec4 (VertexPosition, 1.0);\n"
    "}\n";

static const char interpolate_normal_uv_frag_130[] =
    /* fragment shader */
    "#version 130\n"
    "precision highp float;\n"
    "uniform sampler2D texture0;\n"
    "smooth in vec2 InterpolatedUV;\n"
    "smooth in float InterpolatedLighted;\n"
    "out vec4 Color;\n"
    "void main() {\n"
    "    vec4 ColorT = texture(texture0, InterpolatedUV);\n"
    "    Color = InterpolatedLighted * ColorT;\n"
    "}\n";

