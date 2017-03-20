#version 430

in vec2 TexCoords;
out vec4 tcolor;

uniform sampler2D text;
uniform vec3 color;

void main()
{    
    vec4 font = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
    tcolor = vec4(color, 1.0) * font;
} 