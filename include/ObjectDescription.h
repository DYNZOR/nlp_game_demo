#ifndef OBJECTDESCRIPTION_H
#define OBJECTDESCRIPTION_H

#include <string>

enum EntityType
{
	NE,
	LOCATION,
};

struct ObjectDescription
{
	std::string m_sName;
	std::string m_sColour;
	EntityType m_Type;
};

#endif