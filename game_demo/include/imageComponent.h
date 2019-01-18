/** \file image.h
* Header file for the image class.
*/

#ifndef IMAGECOMPONENT_H
#define IMAGECOMPONENT_H

#include "Bitmap.h"
#include "Texture.h"
#include "gl_core_4_3.hpp"
#include "glm/glm.hpp"
#include "AssetManager.h"
//! The image Class
/*!
This class is a image inherited from component
*/
class image 
{
private:
	/** creates an array of two vbo*/
	GLuint vboHandles[2];
	/** creates a vertex array */
	GLuint vaoHandle;
	/** creates a texture element*/
	GLuint texture;


public:
	/** creates an image from the path provided
	\param imagePath the image path.
	*/
	image(std::string imagePath, int &imageWidth, int &imageHeigh);

	void createImage(std::string imagePath, int &imageWidth, int &imageHeigh);

	/** sets the matrix of the model
	\param matrix matrix which wants to be set.
	*/
	void loadMatrix(glm::mat4 mat);
	/** renders the object
	\param obj the object which need to be renderd.
	*/
	void render(glm::mat4 mat);

};
#endif  IMAGECOMPONENT_H