/** \file camera.h
* Header file for the component class.
*/
#ifndef SOUND3DCOMPONENT_H
#define SOUND3DCOMPONENT_H
#include <string>
#include "SoundManager.h"
#include "Model.h"
#include <memory>
#include "soundManager.h"

//! The component Class
/*!
This class is a simple place holder component
*/

class Sound3DComponent
{
protected:
	int channelIndex;
	int soundType;

	float minVol;
	float maxVol;
	float minPitch;
	float maxPitch;

	std::string filePath;//also the name
	std::shared_ptr<Model> toModel;
	glm::vec3 pastPosition;
public:
	Sound3DComponent();
	void CreateComponent(std::string filePath);
	//void CreateComponent(std::string filePath, std::shared_ptr<Model> toModel);
	void CreateLoopedComponent(std::string filePath);
	//void CreateLoopedComponent(std::string filePath, std::shared_ptr<Model> toModel);

	void playSound(const glm::vec3 &position);
	void playSound(const glm::vec3 &position, const int &loopCount);
	void playSound(const glm::vec3 &position, const glm::vec3 &velocity, const glm::vec3 &forward);
	void playSound(const glm::vec3 &position, const glm::vec3 &velocity, const glm::vec3 &forward, const int &loopCount);

	void updateSound(const glm::vec3 &position);
	void updateSound(const glm::vec3 &position, const glm::vec3 &forward);

	void PlayInfinite3DSound(const glm::vec3 &position);
	void PlayInfinite3DSound(const glm::vec3 &position, const glm::vec3 &velocity, const glm::vec3 &forward);

	void stop();
	void pause(const bool &isPaused);
	void pauseToggle();
	void mute(const bool &isPaused);
	void muteToggle();
	void volume(const float volume);

	void setMinVolMaxVol(const float minvolume, const float maxvolume);
	void setMinPitchMaxPitch(const float minPitch, const float maxPitch);

	void MinMaxDistance(float minDistance, float maxDistance);
	void ConeSettings(const float insideAngle, const float outsideAngle, const float outsideVolume);
	void DopplerLevel(const float level);

};

#endif SOUND3DCOMPONENT_H