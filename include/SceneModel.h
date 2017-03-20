/** \file gameObject.h
* Header file for the gameObject class.
*/

#ifndef SCENEMODEL_H
#define SCENEMODEL_H

#define GLM_FORCE_RADIANS

#include "SceneObject.h"
#include "AssetManager.h"

class SceneModel : public SceneObject
{
protected: 

	std::shared_ptr<Model> pModel;

public:

	/** sets all the pointers to null. */
	SceneModel(const std::string sNameIn, const glm::vec3 vPos, glm::quat qRotation, glm::vec3 vScale, const char* kcProgName, std::string kcAiBehaviour, glm::vec3 vPos2, float fAi2);
	/**Resets the the pointer objects. */
	~SceneModel();

	/** A pointer to the graphics component */

	/** updates the object before drawing
	\param dt the delta time to update
	*/
	virtual void update(float dt) override;
	/**Draw the scene.*/
	virtual void render() override;
	virtual void updateAI(glm::vec3 playerPos, float t);

	std::shared_ptr<Model> getModelHandle() { return pModel;  }

private:
	void turnTowards(glm::vec3 target);
	
};
#endif  //GAMEOBJECT_H