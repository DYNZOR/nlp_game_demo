#include "SoundManager.h"
#include <exception>
#include "math.h"
#include "time.h"
SoundManager::SoundManager()
{
	system = NULL;
	lastpos = { 0.0f, 0.0f, 0.0f };
	for (int channelIndex = 0; channelIndex < numberOfChannels; channelIndex++)
	{
		channelArray[channelIndex].Clear();
	}
	fade = fade_done;
	currentSongVolume = 1.0;
	srand(time(0));
	currentDeltaTime = 0;
	newSong = false;
}

SoundManager* SoundManager::SoundManagerInstance(){
	static SoundManager *theInstance = new SoundManager();
	return theInstance;}SoundManager::~SoundManager()
{
	if (system)
	{
		system->release();
	}
}

void SoundManager::FMODisOK(FMOD_RESULT result)
{
	if (result != FMOD_OK)
	{
		throw ("FMOD error " + std::to_string(result) + ": " + FMOD_ErrorString(result) + placeOfError);
	}
}

void SoundManager::Initialize()
{
	placeOfError = "SoundManager::Initialize";
	// Create the main system object.
	unsigned int version;
	FMOD_RESULT result;
	result = FMOD::System_Create(&system);
	FMODisOK(result);
		
	result = system->getVersion(&version);
	FMODisOK(result);

	if (version < FMOD_VERSION)
	{
		throw ("Error! You are using an old version of FMOD " + std::to_string(version) + ". This program requires " + std::to_string(FMOD_VERSION));
	}


	result = system->init(numberOfChannels/* the amount of channels possibly change*/, FMOD_INIT_NORMAL, 0);    // Initialize FMOD.
	if (result != FMOD_OK)
	FMODisOK(result);

	system->set3DSettings(1.0, 1.0, 1.0);//set the deafualt settings 
	FMODisOK(result);

	system->getMasterChannelGroup(&master);
	system->createChannelGroup(0, &sfx);
	master->addGroup(sfx);

	system->createChannelGroup(0, &sfx2D);
	sfx->addGroup(sfx2D);

	system->createChannelGroup(0, &sfx3D);
	sfx->addGroup(sfx3D);

	system->createChannelGroup(0, &background);
	master->addGroup(background);

}

void SoundManager::update(glm::vec3 pos, glm::quat Orentaion/*can be changed to the cameras up and forward vector*/, float dt)
{
	placeOfError = "SoundManager::update";
	FMOD_RESULT result;
	FMOD_VECTOR position = { 0.0f, 0.0f, 0.0f };
	FMOD_VECTOR forward = { 0.0f, 0.0f, 0.0f };
	FMOD_VECTOR up = { 0.0f, 0.0f, 0.0f };
	FMOD_VECTOR vel = { 0.0f, 0.0f, 0.0f };
	currentDeltaTime = dt;
	glm::mat4 _view = glm::mat4_cast(Orentaion);

	glm::vec3 forwardTemp = glm::vec3(_view[2][0], _view[2][1], _view[2][2]);
	glm::normalize(forwardTemp);

	forward = glmVectorToFmodVector(-forwardTemp);

	glm::vec3 upTemp = glm::vec3(_view[1][0], _view[1][1], _view[1][2]);
	glm::normalize(upTemp);

	up = glmVectorToFmodVector(upTemp);
	position = glmVectorToFmodVector(-pos);//negative sighn to fix the position bug
	vel.x = (position.x - lastpos.x) * dt;
	vel.y = (position.y - lastpos.y) * dt;
	vel.z = (position.z - lastpos.z) * dt;

	lastpos = position;

	result = system->set3DListenerAttributes(0, &position, &vel, &forward, &up);
	FMODisOK(result);
	bool isPlaying;
	result = currentSong->isPlaying(&isPlaying);
	switch (fade)
	{
		case(fade_done) :
		{
			break;
		}
		case(fade_to) :
		{
			float vol;
			currentSong->getVolume(&vol);
			vol -= dt * (currentSongVolume * 0.3);
			if (vol <= currentSongVolume)
			{
				currentSong->setVolume(currentSongVolume);
				fade = fade_done;
			}
			else
			{
				currentSong->setVolume(vol);
			}
			break;
		}
		case(fade_out) :
		{
			float vol;
			currentSong->getVolume(&vol);
			vol -= dt * (currentSongVolume * 0.3);
			if (vol <= 0.0)
			{
				currentSong->setVolume(0.0);
				fade = fade_done;
				if (newSong)
				{
					currentSong->stop();
					if (nextSong.empty())
					{
						newSong = false;
						fade = fade_done;
						break;
					}
					if ((system->playSound(stream2DLooped.at(nextSong).fmodSound, 0, false, &currentSong)) != FMOD_OK)
					{
						system->update();
						newSong = false;
						fade = fade_done;
						return;
					}
					currentSong->setVolume(0.0);
					currentSong->setChannelGroup(background);
					fade = fade_in;
					newSong = false;
				}
			}
			else
			{
				currentSong->setVolume(vol);
			}
			break;
		}
		case(fade_in) :
		{
			if (isPlaying)
			{
				float vol;
				currentSong->getVolume(&vol);
				vol += dt * (currentSongVolume * 0.1);
				if (vol >= currentSongVolume)
				{
					currentSong->setVolume(currentSongVolume);
					fade = fade_done;
				}
				else
				{
					currentSong->setVolume(vol);
				}
			}
			break;
		}
	}

	system->update();
}

FMOD_VECTOR SoundManager::glmVectorToFmodVector(const glm::vec3 vector)
{
	FMOD_VECTOR vec;

	vec.x = vector.x;
	vec.y = vector.y;
	vec.z = vector.z;

	return vec;
}

int SoundManager::Create3DSound(std::string &filePath)
{
	placeOfError = "SoundManager::Create3DSound";
	FMOD_RESULT    result;
	FMOD::Sound *  sound;
	soundInstance soundToBeCreated;
	int soundIndex;
	if (sound3D.find(filePath) == sound3D.end())
		{
		//no sound found
		soundToBeCreated.fileName = filePath;
		soundToBeCreated.soundType = sound_3D;
		result = system->createSound(filePath.c_str(), FMOD_3D, 0, &sound);
		FMODisOK(result);
		soundToBeCreated.fmodSound = sound;
		sound3D[filePath] = soundToBeCreated;
	}
		//found sound
		return sound_3D;


}

int SoundManager::Create3DLoopedSound(std::string &filePath)
{
	placeOfError = "SoundManager::Create3DLoopedSound";
	FMOD_RESULT    result;
	FMOD::Sound *  sound;
	soundInstance soundToBeCreated;
	int soundIndex;
	if (sound3DLooped.find(filePath) == sound3DLooped.end())
	{
		//no sound found
		soundToBeCreated.fileName = filePath;
		soundToBeCreated.soundType = sound_3D;
		result = system->createSound(filePath.c_str(), FMOD_3D, 0, &sound);
		FMODisOK(result);
		result = sound->setMode(FMOD_LOOP_NORMAL);
		FMODisOK(result);
		soundToBeCreated.fmodSound = sound;
		sound3DLooped[filePath] = soundToBeCreated;
	}

	//found sound
	return sound_3D_looped;

}

int SoundManager::Create2DSound(std::string &filePath)
{
	placeOfError = "SoundManager::Create2DSound";
	FMOD_RESULT    result;
	FMOD::Sound *  sound;
	soundInstance soundToBeCreated;
	int soundIndex;
	if (sound2D.find(filePath) == sound2D.end())
	{
		//no sound found
		soundToBeCreated.fileName = filePath;
		soundToBeCreated.soundType = sound_3D;
		result = system->createSound(filePath.c_str(), FMOD_2D, 0, &sound);
		FMODisOK(result);
		soundToBeCreated.fmodSound = sound;
		sound2D[filePath] = soundToBeCreated;
	}

	//found sound
	return sound_2D;

}

int SoundManager::Create2DLoopedStream(std::string &filePath)
{
	placeOfError = "SoundManager::Create2DSound";
	FMOD_RESULT    result;
	FMOD::Sound *  sound;
	soundInstance soundToBeCreated;
	int soundIndex;
	if (stream2DLooped.find(filePath) == stream2DLooped.end())
	{
		//no sound found
		soundToBeCreated.fileName = filePath;
		soundToBeCreated.soundType = sound_3D;
		result = system->createStream(filePath.c_str(), FMOD_2D, 0, &sound);
		FMODisOK(result);
		result = sound->setMode(FMOD_LOOP_NORMAL);
		FMODisOK(result);
		soundToBeCreated.fmodSound = sound;
		stream2DLooped[filePath] = soundToBeCreated;
	}

	//found sound
	return sound_2D_looped;
}
/*
void SoundManager::playSound(std::string &filePath, int objectID, int soundType, int *channelIndex)
{
	placeOfError = "SoundManager::playSound";
	sounds type = (sounds)soundType;
	FMOD::Channel *channel;
	FMOD_RESULT result;
	soundInstance soundint;
	int channelIndexTemp;
	switch(type)
	{
		case(sound_3D):
		{
			if (!sound3D.count(filePath))
			{
				return;
			}
			soundint = sound3D.at(filePath);
			break;
		}

		case(sound_3D_looped) :
		{
			if (!sound3DLooped.count(filePath))
			{
				return;
			}
			soundint = sound3DLooped.at(filePath);
			break;
		}

		case(sound_2D) :
		{
			if (!sound2D.count(filePath))
			{
				return;
			}
			soundint = sound2D.at(filePath);
			break;
		}

		case(sound_2D_looped) :
		{
			if (!stream2DLooped.count(filePath))
			{
				return;
			}
			soundint = stream2DLooped.at(filePath);
			break;
		}
	}

	if (channelIndex)
		channelIndexTemp = *channelIndex;
	else
		channelIndexTemp = NULL;

	if (channelIndexTemp != NULL) //potential error
	{
		channelIndexTemp = *channelIndex;
		result = system->getChannel(channelIndexTemp, &channel);
		FMODisOK(result);
		bool isPlaying;
		result = channel->isPlaying(&isPlaying);
		if ((result == FMOD_OK) && (isPlaying == true) && (channelArray[channelIndexTemp].objectID == objectID))
		{
			return;//already playing
		}
	}

	result = system->playSound(soundint.fmodSound,0, false, &channel);
	if (result == !FMOD_OK)
	{
		std::cout << "SoundManager::PlaySound could not play sound  FMOD Error:" << FMOD_ErrorString(result);
		*channelIndex = NULL;
		return;
	}

	channel->getIndex(&channelIndexTemp);

	// This is where the sound really starts.
	result = channel->setPaused(false);

	*channelIndex = channelIndexTemp;
}
*/
void SoundManager::Play2DSound(const std::string &filePath, int *channelIndex)
{
	placeOfError = "SoundManager::playSound";
	FMOD::Channel *channel;
	FMOD_RESULT result;
	soundInstance soundint;
	int channelIndexTemp;

	if (!sound2D.count(filePath))
	{
		channelIndex = NULL;
		return;
	}

	soundint = sound2D.at(filePath);


	if ((system->playSound(sound2D.at(filePath).fmodSound, 0, false, &channel)) != FMOD_OK)
	{
		channelIndex = NULL;
		return;
	}
	channel->getIndex(channelIndex);
	channel->setChannelGroup(sfx2D);
}

void SoundManager::Play2DSound(const std::string &filePath, int *channelIndex, const int &loopCount)
{
	placeOfError = "SoundManager::playSound";
	FMOD::Channel *channel;
	FMOD_RESULT result;

	if (!sound2D.count(filePath))
	{
		channelIndex = NULL;
		return;
	}


	if ((system->playSound(sound2D.at(filePath).fmodSound, 0, false, &channel)) != FMOD_OK)
	{
		channelIndex = NULL;
		return;
	}
	channel->getIndex(channelIndex);
	channel->setLoopCount(loopCount);
	channel->setChannelGroup(sfx2D);
}

void SoundManager::Play3DSound(const std::string &filePath, const glm::vec3 &position, int *channelIndex, float minVol , float maxVol , float minPitch , float maxPitch )
{
	placeOfError = "SoundManager::playSound";
	FMOD::Channel *channel;
	FMOD_RESULT result;
	soundInstance soundint;

	if (!sound3D.count(filePath))
	{
		channelIndex = NULL;
		return;
	}

	if (system->playSound(sound3D.at(filePath).fmodSound, 0, false, &channel) != FMOD_OK)
	{
		channelIndex = NULL;
		return;
	}

	if (minVol !=0 && maxVol != 0)
	{
		float volume = randomBetween(minVol, maxVol);
		float pitch = randomBetween(minPitch, maxPitch);
		channel->setVolume(volume);
		FMOD::DSP* dsp = getPitchChangeDSP(pitch);
		channel->addDSP(0,dsp);
	}

	channel->getIndex(channelIndex);
	this->Channel3DAttributes(*channelIndex, position, glm::vec3(0));
	channel->setChannelGroup(sfx3D);
}

void SoundManager::Play3DSound(const std::string &filePath, const glm::vec3 &position, int *channelIndex, const int &loopCount, float minVol , float maxVol , float minPitch , float maxPitch )
{
	placeOfError = "SoundManager::playSound";
	FMOD::Channel *channel;
	FMOD_RESULT result;
	soundInstance soundint;

	if (!sound3D.count(filePath))
	{
		channelIndex = NULL;
		return;
	}

	if (system->playSound(sound3D.at(filePath).fmodSound, 0, false, &channel) != FMOD_OK)
	{
		channelIndex = NULL;
		return;
	}

	if (minVol != 0 && maxVol != 0)
	{
		float volume = randomBetween(minVol, maxVol);
		float pitch = randomBetween(minPitch, maxPitch);
		channel->setVolume(volume);
		FMOD::DSP* dsp = getPitchChangeDSP(pitch);
		channel->addDSP(0, dsp);
	}

	channel->setLoopCount(loopCount);
	channel->getIndex(channelIndex);

	this->Channel3DAttributes(*channelIndex, position, glm::vec3(0));
	channel->setChannelGroup(sfx3D);
}

void SoundManager::Play3DSound(const std::string &filePath, int *channelIndex, const glm::vec3 &position, const glm::vec3 &velocity, const glm::vec3 &forward, float minVol, float maxVol, float minPitch, float maxPitch)
{
	placeOfError = "SoundManager::playSound";
	FMOD::Channel *channel;
	FMOD_RESULT result;
	soundInstance soundint;

	if (!sound3D.count(filePath))
	{
		channelIndex = NULL;
		return;
	}

	if (system->playSound(sound3D.at(filePath).fmodSound, 0, false, &channel) != FMOD_OK)
	{
		channelIndex = NULL;
		return;
	}

	if (minVol != 0 && maxVol != 0)
	{
		float volume = randomBetween(minVol, maxVol);
		float pitch = randomBetween(minPitch, maxPitch);
		channel->setVolume(volume);
		FMOD::DSP* dsp = getPitchChangeDSP(pitch);
		channel->addDSP(0, dsp);
	}

	channel->getIndex(channelIndex);

	this->Channel3DAttributes(*channelIndex, position, velocity);
	this->Channel3DConeOrientation(*channelIndex, forward);
	channel->setChannelGroup(sfx3D);
}

void SoundManager::Play3DSound(const std::string &filePath, int *channelIndex, const glm::vec3 &position, const glm::vec3 &velocity, const glm::vec3 &forward, const int &loopCount, float minVol , float maxVol, float minPitch , float maxPitch)
{
	placeOfError = "SoundManager::playSound";
	FMOD::Channel *channel;
	FMOD_RESULT result;
	soundInstance soundint;

	if (!sound3D.count(filePath))
	{
		channelIndex = NULL;
		return;
	}

	if (system->playSound(sound3D.at(filePath).fmodSound, 0, false, &channel) != FMOD_OK)
	{
		channelIndex = NULL;
		return;
	}
	if (minVol != 0 && maxVol != 0)
	{
		float volume = randomBetween(minVol, maxVol);
		float pitch = randomBetween(minPitch, maxPitch);
		channel->setVolume(volume);
		FMOD::DSP* dsp = getPitchChangeDSP(pitch);
		channel->addDSP(0, dsp);
	}
	channel->setLoopCount(loopCount);
	channel->getIndex(channelIndex);

	this->Channel3DAttributes(*channelIndex, position, velocity);
	this->Channel3DConeOrientation(*channelIndex, forward);
	channel->setChannelGroup(sfx3D);
}

void SoundManager::PlayInfinite2DSound(const std::string &filePath, int *channelIndex)
{
	placeOfError = "SoundManager::playSound";
	FMOD_RESULT result;
	soundInstance soundint;
	int channelIndexTemp;

	if (!stream2DLooped.count(filePath))
	{
		channelIndex = NULL;
		return;
	}

	soundint = stream2DLooped.at(filePath);
	bool isPlaying;
	currentSong->isPlaying(&isPlaying);
	
	if (!isPlaying)
	{
		if ((system->playSound(stream2DLooped.at(filePath).fmodSound, 0, false, &currentSong)) != FMOD_OK)
		{
			channelIndex = NULL;
			return;
		}
		currentSong->setVolume(0.0);
		currentSong->getIndex(channelIndex);
		currentSong->setChannelGroup(background);
		fade = fade_in;
	}
	else
	{
		nextSong = filePath;
		fade = fade_out;
		newSong = true;
	}
}

void SoundManager::PlayInfinite3DSound(const std::string &filePath, const glm::vec3 &position, int *channelIndex)
{
	placeOfError = "SoundManager::playSound";
	FMOD::Channel *channel;
	FMOD_RESULT result;
	soundInstance soundint;
	int channelIndexTemp;

	if (!sound3DLooped.count(filePath))
	{
		channelIndex = NULL;
		return;
	}

	soundint = sound3DLooped.at(filePath);


	if ((system->playSound(sound3DLooped.at(filePath).fmodSound, 0, false, &channel)) != FMOD_OK)
	{
		channelIndex = NULL;
		return;
	}
	channel->getIndex(channelIndex);
	this->Channel3DAttributes(*channelIndex, position, glm::vec3(0));
	channel->setChannelGroup(background);
}

void SoundManager::PlayInfinite3DSound(const std::string &filePath, int *channelIndex, const glm::vec3 &position, const glm::vec3 &velocity, const glm::vec3 &forward)
{
	placeOfError = "SoundManager::playSound";
	FMOD::Channel *channel;
	FMOD_RESULT result;
	soundInstance soundint;
	int channelIndexTemp;

	if (!sound3DLooped.count(filePath))
	{
		channelIndex = NULL;
		return;
	}

	soundint = sound3DLooped.at(filePath);


	if ((system->playSound(sound3DLooped.at(filePath).fmodSound, 0, false, &channel)) != FMOD_OK)
	{
		channelIndex = NULL;
		return;
	}
	channel->getIndex(channelIndex);
	this->Channel3DAttributes(*channelIndex, position, velocity);
	this->Channel3DConeOrientation(*channelIndex, forward);
	channel->setChannelGroup(background);
}

bool SoundManager::IsInfiniteLooped(const int soundType)
{
	sounds type = (sounds)soundType;
	switch (type)
	{
		case(sound_3D):
		{
			return false;
			break;
		}
		case(sound_2D) :
		{
			return false;
			break;
		}

		case(sound_3D_looped):
		{
			return true;
			break;
		}
		case(sound_2D_looped) :
		{
			return true;
			break;
		}
	}
	return false;
}

FMOD::Channel *SoundManager::GetSoundChannel(int channelIndex)
{
	if (channelIndex > 0 && channelIndex < numberOfChannels)
	{
		FMOD::Channel *soundChannel;
		system->getChannel(channelIndex, &soundChannel);
		return soundChannel;
	}
		return NULL;
}

void SoundManager::Set3DMinMaxDistance(int channelIndex, float minDistance, float maxDistance)
{
	FMOD_RESULT    result;
	FMOD::Channel *channel;

	if (channelIndex == invalid)
		return;

	result = system->getChannel(channelIndex, &channel);
	if (result == FMOD_OK)
		channel->set3DMinMaxDistance(minDistance, maxDistance);
}

void SoundManager::Channel3DAttributes(const int channelIndex, const glm::vec3 position, const glm::vec3 velocity)
{
	FMOD::Channel* channel;
	if (system->getChannel(channelIndex, &channel) != FMOD_OK)
	{
		return;
	}

	const FMOD_VECTOR posVec = glmVectorToFmodVector(position);

	glm::vec3 temp = velocity * (float)currentDeltaTime;

	const FMOD_VECTOR velVec = glmVectorToFmodVector(temp);

	channel->set3DAttributes(&posVec, &velVec);
}

void SoundManager::Channel3DConeOrientation(const int channelIndex, const glm::vec3 orientation)
{
	FMOD::Channel* channel;
	if (system->getChannel(channelIndex, &channel) != FMOD_OK)
	{
		return;
	}

	glm::vec3 temp = glm::normalize(orientation);

	FMOD_VECTOR orient = glmVectorToFmodVector(temp);

	channel->set3DConeOrientation(&orient);
}

void SoundManager::Channel3DConeSettings(const int channelIndex, const float insideAngle, const float outsideAngle, const float outsideVolume)
{
	FMOD::Channel* channel;
	if (system->getChannel(channelIndex, &channel) != FMOD_OK)
	{
		return;
	}

	channel->set3DConeSettings(insideAngle, outsideAngle, outsideVolume);
}

void SoundManager::Channel3DDopplerLevel(const int channelIndex, const float level)
{
	FMOD::Channel* channel;
	if (system->getChannel(channelIndex, &channel) != FMOD_OK)
	{
		return;
	}

	channel->set3DDopplerLevel(level);
}

void SoundManager::setReverbGlobalProperties(FMOD_REVERB_PROPERTIES prop)
{
	system->setReverbProperties(0, &prop);
}

FMOD::Reverb3D* SoundManager::setReverbRegion(FMOD_REVERB_PROPERTIES prop, glm::vec3 pos, float minDistance, float maxDistance)
{
	FMOD::Reverb3D* reverb;
	system->createReverb3D(&reverb);
	reverb->setProperties(&prop);
	//FMOD_VECTOR position = glmVectorToFmodVector(pos);
	reverb->set3DAttributes(&glmVectorToFmodVector(pos), minDistance, maxDistance);
	return reverb;
}


void SoundManager::StopAllSounds()
{
	int            channelIndex;
	FMOD_RESULT    result;
	FMOD::Channel *nextChannel;

	for (channelIndex = 0; channelIndex < numberOfChannels; channelIndex++)
	{
		result = system->getChannel(channelIndex, &nextChannel);
		if ((result == FMOD_OK) && (nextChannel != NULL))
			nextChannel->stop();
		channelArray[channelIndex].Clear();
	}
}

void SoundManager::StopSound(int *channelIndex)
{
	if (*channelIndex > 0 && *channelIndex < numberOfChannels)
	{
		FMOD::Channel *soundChannel;

		system->getChannel(*channelIndex, &soundChannel);
		soundChannel->stop();

		channelArray[*channelIndex].Clear();
		*channelIndex = invalid;
	}
}

void SoundManager::ChannelPause(const int &channelIndex, const bool &isPaused)
{
FMOD::Channel* channel;
if (system->getChannel(channelIndex, &channel) != FMOD_OK)
{
	return;
}
channel->setPaused(isPaused);
}

void SoundManager::ChannelPauseToggle(const int &channelIndex)
{
	FMOD::Channel* channel;
	bool isPaused;
	if (system->getChannel(channelIndex, &channel) != FMOD_OK)
	{
		return;
	}
	channel->getPaused(&isPaused);
	channel->setPaused(!isPaused);
}

void SoundManager::ChannelMute(const int &channelIndex, const bool &isMuted)
{
	FMOD::Channel* channel;
	if (system->getChannel(channelIndex, &channel) != FMOD_OK)
	{
		return;
	}
		
	channel->setMute(isMuted);
}

void SoundManager::ChannelMuteToggle(const int &channelIndex)
{
	FMOD::Channel* channel;
	bool isMuted;
	if (system->getChannel(channelIndex, &channel) != FMOD_OK)
	{
		return;
	}
	channel->getMute(&isMuted);
	channel->setMute(!isMuted);
}

void SoundManager::ChannelVolume(const int &channelIndex, const float &volume)
{
	FMOD::Channel* channel;
	if (system->getChannel(channelIndex, &channel) != FMOD_OK)
	{
		return;
	}
	int temp;
	currentSong->getIndex(&temp);
	if (channelIndex == temp)
	{
		if (volume < currentSongVolume)
		{
			fade = fade_to;
		}
		else
		{
			fade = fade_in;
		}
		currentSongVolume = volume;
		return;
	}
	channel->setVolume(volume);
}

float SoundManager::ChangeOctave(float frequency, float variation)
{
	return frequency * pow(2.0f, variation);
}

float SoundManager::ChangeSemiTone(float frequency, float variation)
{
	return frequency * pow(pow(2.0f, 1.0f / 12.0f), variation);
}

void SoundManager::MasterVolume(const float &volume)
{
	master->setVolume(volume);
}

void SoundManager::SFXVolume(const float &volume)
{
	sfx->setVolume(volume);
}

void SoundManager::BackgroundVolume(const float &volume)
{
	background->setVolume(volume);
}

FMOD::DSP* SoundManager::getPitchChangeDSP(float variation)
{
	FMOD::DSP *dsp;
	system->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT, &dsp);
	dsp->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH, variation);
	dsp->setParameterInt(FMOD_DSP_PITCHSHIFT_FFTSIZE, 4096);
	return dsp;
}

float SoundManager::randomBetween(float min, float max)
{
	if (min == max)
	{
		return min;
	}
	float n = (float)rand() / (float)RAND_MAX;
	return min + n * (max - min);
}