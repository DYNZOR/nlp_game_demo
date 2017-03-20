#version 430

layout (location = 0) in vec3 VertexPosition;

out vec3 texCoords;

uniform mat4 mProjectionMatrix;
uniform mat4 mViewMatrix;
uniform mat4 mModelMatrix;


void main()
{
	texCoords = VertexPosition;
	gl_Position = mProjectionMatrix * mViewMatrix * mModelMatrix * vec4( VertexPosition, 1.0);
}