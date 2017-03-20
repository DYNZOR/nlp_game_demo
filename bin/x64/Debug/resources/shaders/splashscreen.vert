#version 430

layout (location=0) in vec3 position;
layout (location=1) in vec3 normal;
layout (location=2) in vec2 texCoords;

out vec2 TexCoords;
out vec3 FragPosition;
out vec3 Normal;

uniform mat3 NormalMatrix;
uniform mat4 mModelView;
uniform mat4 mMVP;

uniform mat4 mProjectionMatrix;
uniform mat4 mViewMatrix;
uniform mat4 mModelMatrix;

//out vec4 colour;


void main() {

	//colour = vec4(vec3(0.0,0.0,0.0),1.0);

	//Transform from local to world to camera to NDCs

	gl_Position = mProjectionMatrix * mViewMatrix * mModelMatrix * vec4(position,1.0);
	FragPosition = vec3(mModelMatrix * vec4(position, 1.0f));


	//Normal = normalize(NormalMatrix * normal);

	Normal = mat3(transpose(inverse(mModelMatrix))) * normal;

	TexCoords = texCoords;

}



