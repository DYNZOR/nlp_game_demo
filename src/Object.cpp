#include "Object.h"


Object::Object()
{
	glm::vec3 pos; 

	//vPosition = glm::vec3(0.0, 0.0, 0.0);
	//setPosition(0.0, 0.0, 0.0);
}

Object::~Object()
{

}

//void Object::SetParent(std::shared_ptr<Object> parent) { m_Parent = parent; }
//void Object::AddChild(std::shared_ptr<Object> newChild) { m_aChildren.emplace_back(newChild); }

//void Object::setPosition(const float kX, const float kY, const float kZ)
//{
//	vPosition = glm::vec3(kX, kY, kZ);
//}
//
//void Object::setPosition(const glm::vec3 vPos)
//{
//	vPosition = vPos;
//}
//
//void Object::translate(const float kX, const float kY, const float kZ)
//{
//	vPosition += glm::vec3(kX, kY, kZ);
//}
//
//void Object::translate(const glm::vec3 kTranslate)
//{
//	vPosition += kTranslate;
//}
