#ifndef ENUMPARSER_H
#define ENUMPARSER_H

#include <map>
#include "EntityNames.h"

template <typename T>
class EnumParser
{
	std::map<std::string, T> enumMap;
public:
	EnumParser() {};

	T ParseSomeEnum(const std::string &value)
	{
		std::map<std::string, T>::const_iterator iValue = enumMap.find(value);
		if (iValue == enumMap.end())
			throw std::runtime_error("");
		return iValue->second;
	}
};


EnumParser<EntityNames>::EnumParser()
{
	enumMap["Bob"] = BOB;
	enumMap["Bill"] = BILL;
	enumMap["Dinis"] = DINIS;
}


EnumParser<LocationNames>::EnumParser()
{
	enumMap["England"] = England;
	enumMap["Germany"] = Germany;
	enumMap["France"] = France;

}

#endif