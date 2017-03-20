/**
@file Texture.h
*/
#pragma once

#include <gl_core_4_3.hpp>
#include "Bitmap.h"

#include <assimp/scene.h>      


/*! \class Texture
\brief The texture class 
*/
class Texture {
public:

	Texture(const Bitmap& bitmap,GLint minFiler = gl::LINEAR, GLint magFiler = gl::LINEAR, GLint wrapMode = gl::CLAMP_TO_EDGE); //!< Create an opengl texture from the content of the bitmap file 

	~Texture(); //!< Texture destructor 

	GLuint object() const; //!< Returns the handle to the texture object 

	GLfloat originalWidth() const; //!< The width of the bitmap image loaded in

	GLfloat originalHeight() const; //!< The width of the bitmap image loaded in

	std::string type; //!< Type of texture 
	aiString path; //!< Path to the texture 

private:
	GLuint _object;
	GLfloat _originalWidth;
	GLfloat _originalHeight;

	//copying disabled
	Texture(const Texture&);
	const Texture& operator=(const Texture&);
};