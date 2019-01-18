#ifndef SoundManager_H
#define SoundManager_H

#include <iostream>
#include <fstream>
#include <string>
#include "fmod.hpp"
#include "fmod_errors.h"
#include <map>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>
#include <glm/gtx/quaternion.hpp>
#include "Channel.h"

enum sounds { sound_3D, sound_3D_looped, sound_2D_looped, sound_2D };

struct soundInstance
{
	std::string fileName;
	FMOD::Sound * fmodSound;
	sounds soundType;
};

const int numberOfChannels = 200;
const int invalid = -1;
class SoundManager
{
private:
	enum fadeing { fade_in, fade_out, fade_done , fade_to};
	fadeing fade;
	FMOD::System *system;
	std::string placeOfError;
	FMOD::Channel* currentSong;
	float currentSongVolume;

	std::string nextSong;
	bool newSong;

	FMOD_VECTOR lastpos;
	void FMODisOK(FMOD_RESULT result);
	double currentDeltaTime;
	FMOD_VECTOR glmVectorToFmodVector(const glm::vec3 vector);

	FMOD::ChannelGroup * master;
	FMOD::ChannelGroup * sfx;
	FMOD::ChannelGroup * sfx2D;
	FMOD::ChannelGroup * sfx3D;
	FMOD::ChannelGroup * background;

	std::map<std::string, soundInstance> sound3D;
	std::map<std::string, soundInstance> sound3DLooped;
	std::map<std::string, soundInstance> sound2D;
	std::map<std::string, soundInstance> stream2DLooped;
	Channel channelArray[numberOfChannels];
public:
	static SoundManager* SoundManagerInstance();
	SoundManager();
	~SoundManager();
	void Initialize(void);

	int Create3DSound(std::string &filePath);         // single-shot 3D sound.  returns soundType
	int Create3DLoopedSound(std::string &filePath);   // looping 3D sound.  returns soundType
	
	int Create2DSound(std::string &filePath);
	int Create2DLoopedStream(std::string &filePath);  // looping 2D stream.  returns soundType
	
	//void playSound(std::string &filePath, int objectID, int soundType, int *channelIndex);

	void Play2DSound(const std::string &soundName, int *channelIndex);
	void Play2DSound(const std::string &filePath, int *channelIndex, const int &loopCount);
	void PlayInfinite2DSound(const std::string &filePath, int *channelIndex);

	void Play3DSound(const std::string &filePath, const glm::vec3 &position, int *channelIndex, float minVol = 0, float maxVol = 0, float minPitch = 0, float maxPitch = 0);
	void Play3DSound(const std::string &filePath, const glm::vec3 &position, int *channelIndex, const int &loopCount, float minVol = 0, float maxVol = 0, float minPitch = 0, float maxPitch = 0);
	void Play3DSound(const std::string &filePath, int *channelIndex, const glm::vec3 &position, const glm::vec3 &velocity, const glm::vec3 &forward, float minVol = 0, float maxVol = 0, float minPitch = 0, float maxPitch = 0);
	void Play3DSound(const std::string &filePath, int *channelIndex, const glm::vec3 &position, const glm::vec3 &velocity, const glm::vec3 &forward, const int &loopCount, float minVol = 0, float maxVol = 0, float minPitch = 0, float maxPitch = 0);
	
	void PlayInfinite3DSound(const std::string &filePath, const glm::vec3 &position, int *channelIndex);
	void PlayInfinite3DSound(const std::string &filePath, int *channelIndex, const glm::vec3 &position, const glm::vec3 &velocity, const glm::vec3 &forward);

	bool IsInfiniteLooped(const int soundType);


	void StopAllSounds();
	void StopSound(int *channelIndex);
	void ChannelPause(const int &index, const bool &isPaused);
	void ChannelPauseToggle(const int &channelIndex);
	void ChannelMute(const int &index, const bool &isMuted);
	void ChannelMuteToggle(const int &channelIndex);
	void ChannelVolume(const int &index, const float &volume);
	void MasterVolume(const float &volume);
	void SFXVolume(const float &volume);
	void BackgroundVolume(const float &volume);

	void Set3DMinMaxDistance(int channelIndex, float minDistance, float maxDistance);
	float GetSoundLength(std::string &filePath, int soundType = invalid);

	void Channel3DAttributes(const int channelIndex, const glm::vec3 position, const glm::vec3 velocity = glm::vec3(0));
	void Channel3DConeOrientation(const int channelIndex, const glm::vec3 orientation);
	void Channel3DConeSettings(const int channelIndex, const float insideAngle, const float outsideAngle, const float outsideVolume);
	void Channel3DDopplerLevel(const int channelIndex, const float level);

	void setReverbGlobalProperties(FMOD_REVERB_PROPERTIES prop);
	FMOD::Reverb3D* setReverbRegion(FMOD_REVERB_PROPERTIES prop, glm::vec3 pos, float minDistance, float maxDistance);

	float ChangeOctave(float frequency, float variation);
	float ChangeSemiTone(float frequency, float variation);

	FMOD::DSP* getPitchChangeDSP(float variation);

	FMOD::Channel *GetSoundChannel(int channelIndex);
	//updats the listener needs to be done every frame
	void update(const glm::vec3 position,const glm::quat Orentaion,const float dt);
	
	float randomBetween(float min, float max);
};

#endif SoundManager_H