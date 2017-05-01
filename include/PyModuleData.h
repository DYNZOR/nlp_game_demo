#pragma once
#include <string>

struct SentenceData
{
	std::string sentence; // Sentence to be sent to NLP Module

	std::string sAction; // Action in the sentence 
	std::string sPersonEntity1; // Gameobject entity referred. 
	std::string sPersonEntity2;
	std::string sLocation; // Gameobject location 


};