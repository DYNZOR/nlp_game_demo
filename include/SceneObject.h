/** \file gameObject.h
* Header file for the gameObject class.
*/

#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include <vector>
#include <memory>
#include "Model.h"

//#include "cameraInputComponent.h"
//#include "moveableComponent.h"
//#include "lightComponent.h"
//#include "cameraComponent.h"
//#include "robotAnimation.h"
//#include "menuComponent.h"
//#include "imageComponent.h"
//#include "textReportComponent.h"
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
	/** A pointer to the graphics component */
	//std::shared_ptr<Drawable> graphics;

	/** updates the object before drawing
	\param dt the delta time to update
	*/
	virtual void update(float dt) = 0;
	/**Draw the scene.*/
	virtual void render() = 0;

	/** sets all the pointers to null. */
	SceneObject();
	/**Resets the the pointer objects. */
	~SceneObject();
};
#endif  GAMEOBJECT_H