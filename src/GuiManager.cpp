//#include "GuiManager.h"
//
//GuiManager::GuiManager()
//{
//	mouseImage = NULL;
//	position = glm::ivec2(100,400);
//	widthHeight = glm::ivec2(0);
//	mouseMatrix = glm::mat4(1);
//	HasMOuse = false;
//	index = 0;
//}
//
//void GuiManager::addMouseTexture(std::string mouseTexPath)
//{
//	mouseImage = std::make_shared<image>(mouseTexPath, widthHeight.x, widthHeight.y);
//	UpdateModelMatrix();
//	HasMOuse = true;
//}
//
//GuiManager* GuiManager::GuiManagerInstance()
//{
//	static GuiManager *theInstance = new GuiManager();
//	return theInstance;
//}
//
//void GuiManager::addButton(Button buttonToAdd)
//{
//	buttons.push_back(buttonToAdd);
//}
//
//void GuiManager::DeleteButton(int vectorPlacement)
//{
//	buttons.erase(buttons.begin() + vectorPlacement);
//}
//
//void GuiManager::DeleteButton(std::string textOfthButton)
//{
//	for (std::vector<Button>::iterator it = buttons.begin(); it != buttons.end(); ++it)
//	{
//		if (it->name == textOfthButton)
//		{
//			it = buttons.erase(it);
//			break;
//		}
//		
//	}
//}
//
//void GuiManager::ClickTest()
//{
//	for (std::vector<Button>::iterator it = buttons.begin(); it != buttons.end(); ++it)
//	{
//		if (it->highlighted)
//		{
//			
//			it->pressed();
//			
//		}
//	}
//}
//
//bool GuiManager::checkBounds(int x, int y)
//{
//	for (std::vector<Button>::iterator it = buttons.begin(); it != buttons.end(); ++it)
//	{
//		if (it->withInButtonBounds(x, y))
//		{
//			it->highlighted = true;
//			return true;
//		}
//		it->highlighted = false;
//	}
//	return false;
//}
//
//void GuiManager::UpdateModelMatrix()
//{
//	//mouseMatrix = glm::scale(glm::vec3(widthHeight.x / widthHeight.x, widthHeight.y / widthHeight.y, 1));
//	mouseMatrix = glm::translate(glm::vec3(position,1)) * glm::scale(glm::vec3(50, 50, 1));
//}
//
//void GuiManager::UpdateMouse(int x, int y)
//{
//	position.x += x;
//	position.y += y;
//
//	if (checkBounds(x,y))
//	{
//		ClickTest();
//	}
//
//	//UpdateModelMatrix();
//}
//
//void GuiManager::renderGUI()
//{
//	for (std::vector<Button>::iterator it = buttons.begin(); it != buttons.end(); ++it)
//	{
//		it->render();
//	}
//	if (HasMOuse)
//	{
//		mouseImage->render(mouseMatrix);
//	}
//}
//
//void GuiManager::buttonUp()
//{
//	if (index < buttons.size()-1)
//	{
//		index++;
//	}
//	else
//	{
//		index = 0;
//	}
//	buttons.at(index).highlighted = true;
//}
//
//void GuiManager::buttonDown()
//{
//	if (index > 0)
//	{
//		index--;
//	}
//	else
//	{
//		index = buttons.size() - 1;
//	}
//
//	buttons.at(index).highlighted = true;
//}