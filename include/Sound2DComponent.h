/** \file camera.h
* Header file for the component class.
*/
#ifndef SOUND2DCOMPONENT_H
#define SOUND2DCOMPONENT_H
#include <string>
#include "Model.h"
#include <memory>
#include "soundManager.h"
//! The component Class
/*!
This class is a simple place holder component
*/

class Sound2DComponent
{
protected:
	int channelIndex;
	int soundType;
	std::string filePath;//also the name
public:
	Sound2DComponent();
	void CreateComponent(std::string filePath);
	void CreateLoopedComponent(std::string filePath);

	void playSound();
	void playSound(int loopCount);

	void stop();
	void pause(const bool &isPaused);
	void mute(const bool &isPaused);
	void volume(const float volume);

};

#endif SOUND2DCOMPONENT_H