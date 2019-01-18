#include "Sound3DComponent.h"

Sound3DComponent::Sound3DComponent()
{
	filePath = "";
	toModel = NULL;
	channelIndex = 0;
	soundType = 0;
	pastPosition = glm::vec3(0.0);

	minVol = 0;
	maxVol = 0;
	minPitch = 0;
	maxPitch = 0;
}

void Sound3DComponent::CreateComponent(std::string file)
{// create an if sound playing then delete the sound incase of a newly created sound
	filePath = file;
	toModel = NULL;
	soundType = SoundManager::SoundManagerInstance()->Create3DSound(file);
	channelIndex = 0;
}
/*
void Sound3DComponent::CreateComponent(std::string file, std::shared_ptr<Model> model)
{// create an if sound playing then delete the sound incase of a newly created sound
	filePath = file;
	toModel = model;
	soundType = SoundManager::SoundManagerInstance()->Create3DSound(file);
	channelIndex = 0;
}*/

void Sound3DComponent::CreateLoopedComponent(std::string file)
{
	filePath = file;
	toModel = NULL;
	soundType = SoundManager::SoundManagerInstance()->Create3DLoopedSound(file);
	channelIndex = 0;
}
/*
void Sound3DComponent::CreateLoopedComponent(std::string file, std::shared_ptr<Model> model)
{
	filePath = file;
	toModel = model;
	soundType = SoundManager::SoundManagerInstance()->Create3DLoopedSound(file);
	channelIndex = 0;
}*/

void Sound3DComponent::playSound(const glm::vec3 &position)
{
	if (SoundManager::SoundManagerInstance()->IsInfiniteLooped(soundType))
	{
		SoundManager::SoundManagerInstance()->PlayInfinite3DSound(filePath, position, &channelIndex);
	}
	SoundManager::SoundManagerInstance()->Play3DSound(filePath, position, &channelIndex, minVol, maxVol, minPitch, maxPitch);
	pastPosition = position;
}

void Sound3DComponent::playSound(const glm::vec3 &position, const int &loopCount)
{
	SoundManager::SoundManagerInstance()->Play3DSound(filePath, position, &channelIndex, loopCount, minVol, maxVol, minPitch, maxPitch);
	pastPosition = position;
}

void Sound3DComponent::playSound(const glm::vec3 &position, const glm::vec3 &velocity, const glm::vec3 &forward)
{
	if (SoundManager::SoundManagerInstance()->IsInfiniteLooped(soundType))
	{
		SoundManager::SoundManagerInstance()->PlayInfinite3DSound(filePath, &channelIndex, position, velocity, forward);
	}
	SoundManager::SoundManagerInstance()->Play3DSound(filePath, &channelIndex, position, velocity, forward, minVol, maxVol, minPitch, maxPitch);
	pastPosition = position;
}

void Sound3DComponent::playSound(const glm::vec3 &position, const glm::vec3 &velocity, const glm::vec3 &forward, const int &loopCount)
{
	SoundManager::SoundManagerInstance()->Play3DSound(filePath, &channelIndex, position, velocity, forward, loopCount, minVol, maxVol, minPitch, maxPitch);
	pastPosition = position;
}

void Sound3DComponent::updateSound(const glm::vec3 &position)
{
	glm::vec3 velocity = position - pastPosition;
	SoundManager::SoundManagerInstance()->Channel3DAttributes(channelIndex, position, velocity);
	pastPosition = position;
}

void Sound3DComponent::updateSound(const glm::vec3 &position, const glm::vec3 &forward)
{
	glm::vec3 velocity = position - pastPosition;
	SoundManager::SoundManagerInstance()->Channel3DAttributes(channelIndex, position, velocity);
	SoundManager::SoundManagerInstance()->Channel3DConeOrientation(channelIndex, forward);
	pastPosition = position;
}

void Sound3DComponent::stop()
{
	SoundManager::SoundManagerInstance()->StopSound(&channelIndex);
}

void Sound3DComponent::pause(const bool &pause)
{
	SoundManager::SoundManagerInstance()->ChannelPause(channelIndex, pause);
}

void Sound3DComponent::pauseToggle()
{
	SoundManager::SoundManagerInstance()->ChannelPauseToggle(channelIndex);
}

void Sound3DComponent::mute(const bool &mute)
{
	SoundManager::SoundManagerInstance()->ChannelMute(channelIndex, mute);
}

void Sound3DComponent::muteToggle()
{
	SoundManager::SoundManagerInstance()->ChannelMuteToggle(channelIndex);
}

void Sound3DComponent::volume(const float volume)
{
	SoundManager::SoundManagerInstance()->ChannelVolume(channelIndex, volume);
}

void Sound3DComponent::MinMaxDistance(float minDistance, float maxDistance)
{
	SoundManager::SoundManagerInstance()->Set3DMinMaxDistance(channelIndex, minDistance, maxDistance);
}
void Sound3DComponent::ConeSettings(const float insideAngle, const float outsideAngle, const float outsideVolume)
{
	SoundManager::SoundManagerInstance()->Channel3DConeSettings(channelIndex, insideAngle, outsideAngle, outsideVolume);
}
void Sound3DComponent::DopplerLevel(const float level)
{
	float temp = level;
	if (temp < 0)
	{
		temp = 0;
	}
	else if (temp > 5)
	{
		temp = 5;
	}
	SoundManager::SoundManagerInstance()->Channel3DDopplerLevel(channelIndex, temp);
}

void Sound3DComponent::setMinVolMaxVol(const float minvolume, const float maxvolume)
{
	minVol = minvolume;
	maxVol = maxvolume;
}

void Sound3DComponent::setMinPitchMaxPitch(const float minPit, const float maxPit)
{
	minPitch = minPit;
	maxPitch = maxPit;
}