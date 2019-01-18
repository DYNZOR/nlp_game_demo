#include "Sound2DComponent.h"

Sound2DComponent::Sound2DComponent()
{
	filePath = "";
	channelIndex = 0;
	soundType = 0;
}

void Sound2DComponent::CreateComponent(std::string file)
{// create an if sound playing then delete the sound incase of a newly created sound
	filePath = file;
	soundType = SoundManager::SoundManagerInstance()->Create2DSound(file);
	channelIndex = 0;
}

void Sound2DComponent::CreateLoopedComponent(std::string file)
{
	filePath = file;
	soundType = SoundManager::SoundManagerInstance()->Create2DLoopedStream(file);
	channelIndex = 0;
}

void Sound2DComponent::playSound()
{
	if (SoundManager::SoundManagerInstance()->IsInfiniteLooped(soundType))
	{
		SoundManager::SoundManagerInstance()->PlayInfinite2DSound(filePath, &channelIndex);
		return;
	}
	SoundManager::SoundManagerInstance()->Play2DSound(filePath, &channelIndex);
}

void Sound2DComponent::playSound(int loopCount)
{
	SoundManager::SoundManagerInstance()->Play2DSound(filePath, &channelIndex, loopCount);
}

void Sound2DComponent::stop()
{
	SoundManager::SoundManagerInstance()->StopSound(&channelIndex);
}

void Sound2DComponent::pause(const bool &pause)
{
	SoundManager::SoundManagerInstance()->ChannelPause(channelIndex, pause);
}

void Sound2DComponent::mute(const bool &mute)
{
	SoundManager::SoundManagerInstance()->ChannelMute(channelIndex, mute);
}

void Sound2DComponent::volume(const float volume)
{
	SoundManager::SoundManagerInstance()->ChannelVolume(channelIndex, volume);
}