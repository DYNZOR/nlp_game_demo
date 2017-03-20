#include "splashScreen.h"
#include "TextureLoader.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>

#include <glm/gtc/type_ptr.hpp>

splashScreen::splashScreen() { }

void splashScreen::initScene()
{

	gl::Enable(gl::DEPTH_TEST);
	AssetManager::AssetManagerInstance()->getShaderProgram("texture");
	TextureLoader loading;
	int width;
	int height;
	loading.loadTexture("resources/textures/splash.png", texture, width, height);

	//set the parameters for the cube map

	gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MAG_FILTER, gl::LINEAR);
	gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MIN_FILTER, gl::LINEAR);


	//sets the texture to the current texture object
	gl::BindTexture(gl::TEXTURE_2D, 0);

    /////////////////// Create the VBO ////////////////////
	float positionData[] = {
		0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f };

    float uvData[] = {
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.f, 0.0f,
		0.0, 1.0f};


	int indices[] = { //cube indices
		0,1,2, 1,2,3
	};


    // Create and populate the buffer objects using separate buffers
    GLuint vboHandles[3];
	gl::GenBuffers(3, vboHandles);
   
	positionBufferHandle = vboHandles[0];
	IndexBufferId = vboHandles[1];
	uvBufferHandle = vboHandles[2];
	

    gl::BindBuffer(gl::ARRAY_BUFFER, positionBufferHandle);
    gl::BufferData(gl::ARRAY_BUFFER, sizeof(positionData), positionData, gl::STATIC_DRAW);

	gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, IndexBufferId);
    gl::BufferData(gl::ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, gl::STATIC_DRAW);

  // GLuint uvBufferHandle = vboHandles[1];
	gl::BindBuffer(gl::ARRAY_BUFFER, uvBufferHandle);
	gl::BufferData(gl::ARRAY_BUFFER, sizeof(uvData), uvData, gl::STATIC_DRAW);
	

    // Create and set-up the vertex array object
    gl::GenVertexArrays( 1, &vaoHandle );
    gl::BindVertexArray(vaoHandle);

    gl::EnableVertexAttribArray(0);  // Vertex position
    gl::EnableVertexAttribArray(1);  // Vertex color
	gl::EnableVertexAttribArray(2);

    gl::BindBuffer(gl::ARRAY_BUFFER, positionBufferHandle);
    gl::VertexAttribPointer( 0, 3, gl::FLOAT, FALSE, 0, (GLubyte *)NULL );

	gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, IndexBufferId);
	gl::VertexAttribPointer(1,3,gl::FLOAT,FALSE,0,(GLubyte *)NULL);

    gl::BindBuffer(gl::ARRAY_BUFFER, uvBufferHandle);
    gl::VertexAttribPointer( 2, 2, gl::FLOAT, FALSE, 0, (GLubyte *)NULL );
}

void splashScreen::update( float t )
{

}

void splashScreen::render()
{
	gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);
	AssetManager::AssetManagerInstance()->getShaderManager()->setActiveShader("texture"); //#ERROR possible error
	
	glm::mat4 projection = glm::ortho(0.0f, 200.f, 0.0f, 400.f);

	AssetManager::AssetManagerInstance()->getShaderProgram("texture")->setUniform("p", projection);

	glm::mat4 matty = glm::scale(glm::vec3(200,400,0));

	AssetManager::AssetManagerInstance()->getShaderProgram("texture")->setUniform("m", matty);

    gl::Clear(gl::COLOR_BUFFER_BIT);
	gl::ActiveTexture(gl::TEXTURE0);
	gl::BindVertexArray(vaoHandle);
	gl::BindTexture(gl::TEXTURE_2D, texture);
	gl::DrawElements( gl::TRIANGLES, 12, gl::UNSIGNED_INT, NULL );
	gl::BindVertexArray(0);
}

void splashScreen::resize(int w, int h)
{
    gl::Viewport(0,0,w,h);
}