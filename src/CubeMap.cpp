#include "CubeMap.h"
CubeMap::CubeMap()
{

}

CubeMap::CubeMap(const std::string& ksCubeMap) // Create program object 
{

	// Array of open gl texture targets 
	// for targeting each face of the cube map
	targets = {

		//gl::TEXTURE_CUBE_MAP_POSITIVE_X,
		//gl::TEXTURE_CUBE_MAP_NEGATIVE_X,
		//gl::TEXTURE_CUBE_MAP_POSITIVE_Y,
		//gl::TEXTURE_CUBE_MAP_NEGATIVE_Y,
		//gl::TEXTURE_CUBE_MAP_POSITIVE_Z,
		//gl::TEXTURE_CUBE_MAP_NEGATIVE_Z

		gl::TEXTURE_CUBE_MAP_NEGATIVE_X,
		gl::TEXTURE_CUBE_MAP_POSITIVE_X,

		gl::TEXTURE_CUBE_MAP_POSITIVE_Y,
		gl::TEXTURE_CUBE_MAP_NEGATIVE_Y,

		gl::TEXTURE_CUBE_MAP_POSITIVE_Z,

		gl::TEXTURE_CUBE_MAP_NEGATIVE_Z,
	};

	// Array of texture suffixes to represent position of textures on cube map
	suffixes = { "rt", "lf", "up", "dn", "ft", "bk" };


	// Specifying directory to find cube map textures
	sName = ksCubeMap;
	sDirectory = CUBEMAPRESOURCEPATH + sName + "/";
}

void CubeMap::loadCubeMap()	// Loads a cube map
{

	GLfloat cubePositionData[] = {
		// front

		-1000.0, -1000.0, 1000.0,
		1000.0, -1000.0, 1000.0,
		1000.0, 1000.0, 1000.0,
		-1000.0, 1000.0, 1000.0,

		// back
		-1000.0, -1000.0, -1000.0,
		1000.0, -1000.0, -1000.0,
		1000.0, 1000.0, -1000.0,
		-1000.0, 1000.0, -1000.0
	};

	GLuint cubeIndexData[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// top
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// bottom
		4, 0, 3,
		3, 7, 4,
		// left
		4, 5, 1,
		1, 0, 4,
		// right
		3, 2, 6,
		6, 7, 3,
	};

	// Create and populate the buffer objects using separate buffers
	gl::GenBuffers(2, vboHandles);

	GLuint positionBufferHandle = vboHandles[0];
	GLuint indexBufferHandle = vboHandles[1];

	gl::BindBuffer(gl::ARRAY_BUFFER, positionBufferHandle);
	gl::BufferData(gl::ARRAY_BUFFER, sizeof(cubePositionData), &cubePositionData[0], gl::STATIC_DRAW);

	elementsSize = sizeof(cubeIndexData);
	gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, indexBufferHandle);
	gl::BufferData(gl::ELEMENT_ARRAY_BUFFER, elementsSize, &cubeIndexData[0], gl::STATIC_DRAW);

	// Create and set-up the vertex array object
	gl::GenVertexArrays(1, &vaoHandle);
	gl::BindVertexArray(vaoHandle);

	gl::EnableVertexAttribArray(0);  // Vertex position

	gl::BindBuffer(gl::ARRAY_BUFFER, positionBufferHandle);
	gl::VertexAttribPointer(0, 3, gl::FLOAT, FALSE, 0, (GLubyte *)NULL);


	// Setting up texture target to active and bind with new texture handle
	gl::ActiveTexture(gl::TEXTURE0);
	gl::GenTextures(1, &textureID);
	gl::BindTexture(gl::TEXTURE_CUBE_MAP, textureID);

	// Iterate 6 times for each face of the cube map
	for (int i = 0; i < 6; i++)
	{
		// Set up filepath for texture using specific suffix
		std::string textureFile = sDirectory + sName + "_" + suffixes[i] + ".tga";

		// Create bitmap from filepath 
		Bitmap bmp = Bitmap::bitmapFromFile(textureFile);

		// Specify 2D texture image
		gl::TexImage2D(targets[i], 0, gl::RGB,
			bmp.width(), bmp.height(), 0,
			gl::RGB, gl::UNSIGNED_BYTE,
			bmp.pixelBuffer());

	}

	// Set cube map texture filtering properties 
	gl::TexParameterf(gl::TEXTURE_CUBE_MAP, gl::TEXTURE_MAG_FILTER, gl::LINEAR);
	gl::TexParameterf(gl::TEXTURE_CUBE_MAP, gl::TEXTURE_MIN_FILTER, gl::LINEAR);
	gl::TexParameterf(gl::TEXTURE_CUBE_MAP, gl::TEXTURE_WRAP_S, gl::CLAMP_TO_EDGE);
	gl::TexParameterf(gl::TEXTURE_CUBE_MAP, gl::TEXTURE_WRAP_T, gl::CLAMP_TO_EDGE);
	gl::TexParameterf(gl::TEXTURE_CUBE_MAP, gl::TEXTURE_WRAP_R, gl::CLAMP_TO_EDGE);


}


void CubeMap::render()
{
	//program.setUniform("DrawSkyBox", true);

	setUpMatrices(glm::mat4(1.0f));

	// Draw skybox 
	GLuint indexBufferHandle = vboHandles[1];

	gl::BindVertexArray(vaoHandle);
	gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, indexBufferHandle);
	gl::DrawElements(gl::TRIANGLES, elementsSize, gl::UNSIGNED_INT, (void*)0);

	//program.setUniform("DrawSkyBox", false);

	//program.setUniform("refractionRatioIndex", 0.80f);
	//program.setUniform("reflectionFactor", 0.3f);
}

GLuint CubeMap::getHandle() // Get texture handle 
{
	return textureID;
}

void CubeMap::setActiveShader(std::shared_ptr<ShaderProgram> programIn)
{
	setShader(programIn);
}

void CubeMap::setUpMatrices(glm::mat4 modelMatrix)
{
	getActiveShader()->setUniform("mModelMatrix", modelMatrix);
	//getActiveShader()->setUniform("mViewMatrix", camera.getViewMatrix());
	//getActiveShader()->setUniform("mProjectionMatrix", camera.getProjectionMatrix());
}