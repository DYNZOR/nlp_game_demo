///** \file letter.h
//* Header file for the letter class.
//*/
//
//
//#ifndef BUTTON_H
//#define BUTTON_H
//
//#include <glm/glm.hpp>
//#include "imageComponent.h"
//#include "textRender.h"
//#include <memory>
////! The letter Class
///*!
//This class is a letter
//*/
//class Button
//{
//private:
//	
//	typedef void(*ButtonCallback)();
//	ButtonCallback callbackFunction;
//	glm::ivec2 position;
//	glm::ivec2 widthHeight;
//
//	glm::ivec2 passiveSize;
//	glm::ivec2 activeSize;
//	std::shared_ptr<image> PassiveTexture;
//	std::shared_ptr<image> ActiveTexture;
//	std::string ButtonText;
//
//	glm::ivec2 textWidthHeight;
//
//	glm::mat4 PassiveModelMatrix;
//	glm::mat4 ActiveModelMatrix;
//	//typedef void(*ButtonCallback)();
//	//ButtonCallback callbackFunction;
//public:
//	bool highlighted;
//	std::string name;
//
//	/** the texture for the letter */
//	Button();
//	Button(glm::ivec2 position, glm::ivec2 widthHeight, /*ButtonCallback cb,*/ std::string passiveTexturePath, std::string activeTexturePath, std::string text);
//	void createButton(glm::ivec2 position, glm::ivec2 widthHeight, /*ButtonCallback cb,*/ std::string passiveTexturePath, std::string activeTexturePath, std::string text);
//	~Button();
//	void clear();
//	void render();
//	void pressed();
//	bool withInButtonBounds(int x, int y);
//	
//};
//
//#endif BUTTON_H