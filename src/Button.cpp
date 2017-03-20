//#include "Button.h"
//#include <glm/gtx/transform.hpp>
//
//Button::Button()
//{
//	clear();
//}
//
//Button::Button(glm::ivec2 pos, glm::ivec2 widthLength, /*ButtonCallback cb,*/ std::string passiveTexturePath, std::string activeTexturePath, std::string text)
//{
//	/*callbackFunction = cb;*/
//	name = text;
//	ButtonText = text;
//	position = pos;
//	widthHeight = widthLength;
//	glm::ivec2 temp = position;
//	PassiveTexture = std::make_shared<image>(passiveTexturePath, passiveSize.x, passiveSize.y);
//	ActiveTexture = std::make_shared<image>(activeTexturePath, activeSize.x, activeSize.y);
//	position.x -= passiveSize.x;
//	position.y -= passiveSize.y;
//	PassiveModelMatrix = glm::translate(glm::vec3(position, 0.5));
//	ActiveModelMatrix = glm::translate(glm::vec3(position, 0.5));
//	PassiveModelMatrix *= glm::scale(glm::vec3(widthHeight.x , widthHeight.y , 1));
//	ActiveModelMatrix *= glm::scale(glm::vec3(widthHeight.x , widthHeight.y , 1));
//
//
//	textRenderer::getInstance()->getTextSize(ButtonText, textWidthHeight.x, textWidthHeight.y);
//	temp.x -= textWidthHeight.x / 2;
//	temp.y -= textWidthHeight.y / 2;
//	highlighted = false;
//
//
//}
//void Button::createButton(glm::ivec2 pos, glm::ivec2 widthLength, /*ButtonCallback cb,*/ std::string passiveTexturePath, std::string activeTexturePath, std::string text)
//{
//	/*callbackFunction = cb;*/
//	name = text;
//	ButtonText = text;
//	position = pos;
//	widthHeight = widthLength;
//
//	PassiveTexture = std::make_shared<image>(passiveTexturePath, passiveSize.x, passiveSize.y);
//	ActiveTexture = std::make_shared<image>(activeTexturePath, activeSize.x, activeSize.y);
//	//todo resize texture
//	PassiveModelMatrix = glm::translate(glm::vec3(position, 0));
//	ActiveModelMatrix = glm::translate(glm::vec3(position, 0));
//	PassiveModelMatrix *= glm::scale(glm::vec3(widthHeight.x / passiveSize.x, widthHeight.y / passiveSize.y, 1));
//	ActiveModelMatrix *= glm::scale(glm::vec3(widthHeight.x / activeSize.x, widthHeight.y / activeSize.y, 1));
//	
//	textRenderer::getInstance()->getTextSize(ButtonText, textWidthHeight.x, textWidthHeight.y);
//	position.x -= textWidthHeight.x / 2;
//	position.y -= textWidthHeight.y / 2;
//	highlighted = false;
//}
//Button::~Button()
//{
//	PassiveTexture.reset();
//	ActiveTexture.reset();
//}
//void Button::clear()
//{
//	callbackFunction = NULL;
//	name = "";
//	ButtonText = "";
//	position = glm::ivec2(0);
//	widthHeight = glm::ivec2(0);
//
//	PassiveTexture.reset();
//	ActiveTexture.reset();
//	highlighted = false;
//}
//void Button::render()
//{
//	if (highlighted)
//	{
//		ActiveTexture->render(ActiveModelMatrix);
//	}
//	else
//	{
//		PassiveTexture->render(PassiveModelMatrix);
//	}
//	textRenderer::getInstance()->RenderText(ButtonText, position, 1.f);
//}
//void Button::pressed()
//{
//	callbackFunction();
//}
//
//bool Button::withInButtonBounds(int x, int y)
//{
//	if (highlighted)
//	{
//		if (x > activeSize.x && x < activeSize.x + widthHeight.x
//			&& y > activeSize.y && y < activeSize.y + widthHeight.y)
//		{
//			return true;
//		}
//	}
//	else
//	{
//		if (x > passiveSize.x && x < passiveSize.x + widthHeight.x
//			&& y > passiveSize.y && y < passiveSize.y + widthHeight.y)
//		{
//			return true;
//		}
//	}
//	return false;
//}