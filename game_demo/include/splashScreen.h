/** \file splashScreen.h
* Header file for the splashScreen class.
*/

#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include "Bitmap.h"
#include "Texture.h"
#include "gl_core_4_3.hpp"
#include "AssetManager.h"
//! The splashScreen Class
/*!
This class is a splashScreen for the start of the game engine
*/

class splashScreen 
{
private:
	/** The width and height of the splash screen */
	int width, height;
	
	/** The vertex array object */
	GLuint vaoHandle;
	/** The program handler of the shader */
	GLuint programHandle;
	/** the vbo handle for the position */
	GLuint positionBufferHandle;
	/** the vbo handle for the IndexBufferId */
	GLuint IndexBufferId;
	/** the vbo handle for the uvBufferHandle */
	GLuint uvBufferHandle;
	/** the vbo handle for the uvBufferHandle */
	GLuint texture;
	/** links the vertex and fragment shader */
	void linkMe(GLint vertShader, GLint fragShader);
public:
	/** the constructer of the splashScreen*/
	splashScreen();
	/** The initialisation of the screen*/
	void initScene();
	/** updates the frame before drawing
	\param t the delta time to update
	*/
	void update( float t);
	/** Draw the scene.*/
	void render();
	/**
	can resize the window
	\param width the width of the resize
	\param height the height of the resize
	*/
	void resize(int width, int height);

};
#endif  SPLASHSCREEN_H