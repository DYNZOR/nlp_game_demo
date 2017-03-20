#include "channel.h"

void Channel::Clear()
{
	objectID = 0;
	objectsCurrentPosition = glm::vec3(0, 0, 0);
	prevPosition = glm::vec3(0, 0, 0);
}