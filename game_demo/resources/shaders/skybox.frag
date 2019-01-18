#version 430

uniform samplerCube cubeMap;

in vec3 texCoords;

layout ( location = 0 ) out vec4 FragColour;

void main()
{
	FragColour = texture( cubeMap, texCoords );
}