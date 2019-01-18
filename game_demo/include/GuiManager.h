//#ifndef GUIMANAGER_H
//#define GUIMANAGER_H
//
//#include <gl_core_4_3.hpp>
//#include <vector>
//#include <memory>
//#include "Model.h"
//#include "Button.h"
//
//class GuiManager {
//	
//private:
//	std::vector<Button> buttons;
//	std::shared_ptr<image> mouseImage;
//	glm::ivec2 position;
//	glm::ivec2 widthHeight;
//	glm::mat4 mouseMatrix;
//	void UpdateModelMatrix();
//	bool HasMOuse;
//	int index;
//	GuiManager();
//public:
//	static GuiManager* GuiManagerInstance();
//	void addMouseTexture(std::string mouseTexPath);
//	void addButton(Button buttonToAdd);
//	void buttonUp();
//	void buttonDown();
//	void DeleteButton(int vectorPlacement);
//	void DeleteButton(std::string textOfthButton);
//	void ClickTest();
//	bool checkBounds(int x, int y);
//
//	void UpdateMouse(int x, int y);
//	void renderGUI();
//};
//
//#endif GUIMANAGER_H