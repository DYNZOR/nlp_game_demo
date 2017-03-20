///** \file textRenderer.h
//* Header file for the textRenderer class.
//*/
//
//#ifndef TEXTRENDERER_H
//#define TEXTRENDERER_H
//
//#include <map>
//#include "gl_core_4_3.hpp"
//#include <glm/glm.hpp>
//#include "charaterLetter.h"
//#include "AssetManager.h"
////! The textRenderer Class
///*!
//This class is a textRenderer
//*/
//class textRenderer
//{
//public:
//	/** maps charaters to the precompiled letters*/
//	std::map<GLchar, letter> chars;
//	/** static function which allows*/
//	static textRenderer* getInstance();
//	/** Pre-compiles a list of characters from the given font*/
//	void Load(std::string fontPath, GLuint fontSize);
//	/** size of the font*/
//	glm::vec2 sizeOfFont;
//	/** loads the text as a texture
//	\param text the text to be renderd.
//	\param position the position the text to be placed.
//	\param scale the size of the text to be scaled by.
//	\param color the colour id twh text.
//	*/
//	void loadText(std::string text, glm::vec2 position, GLfloat scale, glm::vec3 color);
//	// Renders a string of text using the precompiled list of characters
//	void RenderText(std::string text, glm::vec2 position, GLfloat scale, glm::vec3 color = glm::vec3(1.0f));
//
//	void getTextSize(std::string text, int &width, int &height);
//private:
//	/** the constructer of the text render*/
//	textRenderer();
//	/** the vertex array of the text object*/
//	GLuint textVAO;
//	/** the vbo handlers*/
//	GLuint handle[2];
//	/** loads the matrix of the text
//	\param colour the colour of the text.
//	*/
//	void loadMatrix(glm::vec3 colour);
//};
//
//#endif TEXTRENDERER_H