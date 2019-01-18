#version 430

layout (location = 0) in vec2 vertex; // <vec2 pos, vec2 tex>
layout (location = 1) in vec2 uv;
out vec2 TexCoords;

uniform mat4 p;
uniform mat4 m;

void main()
{
    gl_Position = p * m * vec4(vertex, 0.0, 1.0);
    TexCoords = uv;
} 