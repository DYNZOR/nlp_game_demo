/** \file gameObject.h
* Header file for the gameObject class.
*/

#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include <vector>
#include <memory>
#include "Model.h"
#include "ObjectDescription.h"
#include "EntityNames.h"

//! The gameObject Class
/*!
This class is a gameObject the base of all gameobjects holds pointers to all components
*/
/** A predefined class for the component */

enum Type {
	MODEL,
	POINT_LIGHT,
	DIRECTIONAL_LIGHT,
};

class SceneObject
{
public:
	/** sets all the pointers to null. */
	SceneObject(const std::string sEntityName);
	/**Resets the the pointer objects. */
	~SceneObject();

	/** updates the object before drawing
	\param dt the delta time to update
	*/
	virtual void update(float dt) = 0;

	/**Draw the object.*/
	virtual void render() = 0;

	unsigned int GetID() { return m_uiID; }
	ObjectDescription& GetDescription() { return m_pDescription;  }


protected: 

private:
	unsigned int m_uiID;
	static unsigned int m_uiNextValidID;
	ObjectDescription m_pDescription; 

	void SetID(unsigned int uiNewID);



};
#endif  GAMEOBJECT_H