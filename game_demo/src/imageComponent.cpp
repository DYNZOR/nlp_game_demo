#include "imageComponent.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include "textureLoader.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


image::image(std::string imagepath, int &imageWidth, int &imageHeight)
{ 
	TextureLoader loader;
	if (!loader.loadTexture(imagepath, texture, imageWidth, imageHeight))
	{
		return;
	}
	
	//sets the texture to the current texture object
	gl::BindTexture(gl::TEXTURE_2D, 0);

	/////////////////// Create the VBO ////////////////////
	float positionData[] = {
		0.0f, 1.0f,
		0.0f, 0.0f, 
		1.0f, 0.0f,
		
		0.0f, 1.0f,
		1.0f, 0.0f,
		1.0f, 1.0f
		};


	float uvData[] = {
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,

		0.0f, 0.0f,
		1.0f, 1.0f,
		1.0f, 0.0f
	};

	// Create and set-up the vertex array object
	gl::GenVertexArrays(1, &vaoHandle);
	gl::BindVertexArray(vaoHandle);
	// Create and populate the buffer objects using separate buffers
	gl::GenBuffers(2, vboHandles);


	gl::BindBuffer(gl::ARRAY_BUFFER, vboHandles[0]);
	gl::BufferData(gl::ARRAY_BUFFER, sizeof(positionData), positionData, gl::STATIC_DRAW);
	gl::VertexAttribPointer(0, 2, gl::FLOAT, FALSE, 0, (GLubyte *)NULL);
	gl::EnableVertexAttribArray(0);  // Vertex position

	// GLuint uvBufferHandle = vboHandles[1];
	gl::BindBuffer(gl::ARRAY_BUFFER, vboHandles[1]);
	gl::BufferData(gl::ARRAY_BUFFER, sizeof(uvData), uvData, gl::STATIC_DRAW);
	gl::VertexAttribPointer(1, 2, gl::FLOAT, FALSE, 0, (GLubyte *)NULL);
	gl::EnableVertexAttribArray(1);

	gl::BindVertexArray(0);
}

void image::createImage(std::string imagepath, int &imageWidth, int &imageHeight)
{
	TextureLoader loader;
	if (!loader.loadTexture(imagepath, texture, imageWidth, imageHeight))
	{
		return;
	}

	//sets the texture to the current texture object
	gl::BindTexture(gl::TEXTURE_2D, 0);

	/////////////////// Create the VBO ////////////////////
	float positionData[] = {
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,

		0.0f, 1.0f,
		1.0f, 0.0f,
		1.0f, 1.0f
	};


	float uvData[] = {
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,

		0.0f, 0.0f,
		1.0f, 1.0f,
		1.0f, 0.0f
	};

	// Create and set-up the vertex array object
	gl::GenVertexArrays(1, &vaoHandle);
	gl::BindVertexArray(vaoHandle);
	// Create and populate the buffer objects using separate buffers
	gl::GenBuffers(2, vboHandles);


	gl::BindBuffer(gl::ARRAY_BUFFER, vboHandles[0]);
	gl::BufferData(gl::ARRAY_BUFFER, sizeof(positionData), positionData, gl::STATIC_DRAW);
	gl::VertexAttribPointer(0, 2, gl::FLOAT, FALSE, 0, (GLubyte *)NULL);
	gl::EnableVertexAttribArray(0);  // Vertex position

	// GLuint uvBufferHandle = vboHandles[1];
	gl::BindBuffer(gl::ARRAY_BUFFER, vboHandles[1]);
	gl::BufferData(gl::ARRAY_BUFFER, sizeof(uvData), uvData, gl::STATIC_DRAW);
	gl::VertexAttribPointer(1, 2, gl::FLOAT, FALSE, 0, (GLubyte *)NULL);
	gl::EnableVertexAttribArray(1);

	gl::BindVertexArray(0);
}

void image::loadMatrix(glm::mat4 mat)
{
	glm::mat4 projection = glm::ortho(0.0f, 800.f, 0.0f, 800.f);
	AssetManager::AssetManagerInstance()->getShaderProgram("texture")->setUniform("p", projection);
	glm::mat4 modelMatrix = mat;
	AssetManager::AssetManagerInstance()->getShaderProgram("texture")->setUniform("m", modelMatrix);
	
}

void image::render(glm::mat4 mat)
{ 
	AssetManager::AssetManagerInstance()->getShaderProgram("texture");
	AssetManager::AssetManagerInstance()->getShaderManager()->setActiveShader("texture"); //#ERROR possible error
	loadMatrix(mat);
	gl::ActiveTexture(gl::TEXTURE0);
	gl::BindVertexArray(vaoHandle);
	gl::BindTexture(gl::TEXTURE_2D, texture);
	gl::DrawArrays(gl::TRIANGLES, 0, 6);
	gl::BindVertexArray(0);
}

