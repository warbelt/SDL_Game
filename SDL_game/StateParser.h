#ifndef STATEPARSER_H
#define STATEPARSER_H

#include <iostream>
#include <vector>
#include "tinyxml.h"
class GameObject;

class StateParser
{
public:
	bool parseState(const char* stateFile, std::string stateID, std::vector<GameObject*> *pObjects, std::vector<std::string> *pTextureIDs);

private:
	void parseObjects(TiXmlElement* pStateRoot, std::vector<GameObject*> *pObjects);
	void parseTextures(TiXmlElement* pTextureRoot, std::vector<std::string> *pTextureIDs);
};

#endif