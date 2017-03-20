#include "ArtifIntelligent.h"

ArtifIntelligent::ArtifIntelligent()
{
	sBehaviour = "none";
	bAiDir = true;
}

ArtifIntelligent::~ArtifIntelligent()
{

}

void ArtifIntelligent::setBehaviour(std::string behaviour)
{
	sBehaviour = behaviour;
}

std::string ArtifIntelligent::getBehaviour()
{
	return sBehaviour;
}

void ArtifIntelligent::setPos2(glm::vec3 newPos2)
{
	pos2 = newPos2;
}

glm::vec3 ArtifIntelligent::getPos2()
{
	return pos2;
}

void ArtifIntelligent::setPos1(glm::vec3 newPos1)
{
	pos1 = newPos1;
}

glm::vec3 ArtifIntelligent::getPos1()
{
	return pos1;
}

void ArtifIntelligent::setAi2(float newAi2)
{
	ai2 = newAi2;
}

float ArtifIntelligent::getAi2()
{
	return ai2;
}

void ArtifIntelligent::setAiDir(bool dir)
{
	bAiDir = dir;
}

bool ArtifIntelligent::getAiDir()
{
	return bAiDir;
}