#pragma once
#include <string>
#include <vector>

struct SentenceData
{
	std::string sentence; // Sentence to be sent to NLP Module
};

//typedef std::vector<std::string> VectorStrings;
struct CommandResponse
{
	int bHasLocation;
	int bCancelAction;

	std::string sAction; // Action in the sentence 
	std::string sPresentAction;

	std::string sPersonEntity1; // Gameobject entity referred. 
	std::string sPersonEntity2;
	std::string sLocation; // Gameobject location 

	//std::vector<std::string> sEntities;
	//std::vector<std::string> sLocations;

	//VectorStrings sEntities;
	//VectorStrings sLocations;
	//VectorStrings sActions;
	//VectorStrings sPresentActions;

};