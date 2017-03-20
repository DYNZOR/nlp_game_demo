#ifndef CHANNEL_H
#define CHANNEL_H

#include <glm/gtx/transform2.hpp>

class Channel
{
public:
	void Clear();
	int objectID;
	glm::vec3 objectsCurrentPosition; //needs to be changed to gameobject
	glm::vec3 prevPosition;
};

#endif CHANNEL_H