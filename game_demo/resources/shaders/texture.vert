
#version 430

layout (location=0) in vec2 VertexPosition;
layout (location=1) in vec2 fragTexCoord;

out vec2 texCoord;
uniform mat4 p;
uniform mat4 m;

void main()
{
	texCoord = vec2(fragTexCoord.x, 1.0 - fragTexCoord.y);
    gl_Position = p * m * vec4(VertexPosition,0,1.0);
}
