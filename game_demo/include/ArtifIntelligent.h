#ifndef	ARTIFINTELLIGENT_h
#define ARTIFINTELLIGENT_h

#include <string>
#include <glm\glm.hpp>

class ArtifIntelligent
{
private:
	std::string sBehaviour;
	glm::vec3 pos2;
	glm::vec3 pos1;
	float ai2;
	bool bAiDir;
public:
	ArtifIntelligent();
	~ArtifIntelligent();
	void setBehaviour(std::string behaviour);
	std::string getBehaviour();
	void setPos2(glm::vec3 pos2);
	glm::vec3 getPos2();
	void setPos1(glm::vec3 pos1);
	glm::vec3 getPos1();
	void setAi2(float ai2);
	float getAi2();
	bool getAiDir();
	void setAiDir(bool dir);
};

#endif