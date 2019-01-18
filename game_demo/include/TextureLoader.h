/** \file TextureLoader.h
* Header file for the TextureLoader class.
*/

#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include "gl_core_4_3.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>
#include <string>
#include "Bitmap.h"
//! The TextureLoader Class
/*!
This class is a TextureLoader to load textures
*/
class TextureLoader
{
public:
	/**TextureLoader deafualt construtor*/
	TextureLoader();
	/**
	loadTexture to load a texture
	\param location the path to the texture
	\param texture the texture id to load the texture
	*/
	bool loadTexture(std::string location, GLuint &texture, int &width, int &height);
};
#endif  TEXTURELOADER_H
