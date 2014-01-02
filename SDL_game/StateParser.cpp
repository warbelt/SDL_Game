#include <string>
#include <vector>
#include "StateParser.h"
#include "TextureManager.h"
#include "Game.h"
#include "GameObjectFactory.h"
#include "GameObject.h"
#include "LoaderParams.h"

bool StateParser::parseState(const char* stateFile, std::string stateID, std::vector<GameObject*> *pObjects, std::vector<std::string> *pTextureIDs)
{
	TiXmlDocument xmlDoc;
	int j = xmlDoc.LoadFile(stateFile);
	if (!j)
	{
		std::cerr << xmlDoc.ErrorDesc() << "\n";
	}

	TiXmlElement* pRoot = xmlDoc.RootElement();
	TiXmlElement* pStateRoot = 0;

	for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string(stateID))
		{
			pStateRoot = e;
		}
	}

	TiXmlElement* pTextureRoot = 0;

	for (TiXmlElement * e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("TEXTURES"))
		{
			pTextureRoot = e;
		}
	}

	parseTextures(pTextureRoot, pTextureIDs);

	TiXmlElement* pObjectRoot = 0;

	for (TiXmlElement* e = pStateRoot->FirstChildElement(); e!=NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("OBJECTS"))
		{
			pObjectRoot = e;
		}
	}

	parseObjects(pObjectRoot, pObjects);

	return true;
}

void StateParser::parseTextures(TiXmlElement* pTextureRoot, std::vector<std::string> *pTextureIDs)
{
	for (TiXmlElement* e = pTextureRoot->FirstChildElement(); e!=NULL; e = e->NextSiblingElement())
	{
		std::string filenameAttribute = e->Attribute("filename");
		std::string idAttribute = e->Attribute("ID");
		pTextureIDs->push_back(idAttribute);

		TheTextureManager::Instance()->load(filenameAttribute, idAttribute, TheGame::Instance()->getRenderer());
	}
}

void StateParser::parseObjects(TiXmlElement* pObjectRoot, std::vector<GameObject*> *pObjects)
{
	for (TiXmlElement* e = pObjectRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		int x, y, width, height, numFrames, callbackID, animSpeed;
		std::string textureID;

		e->Attribute("x", &x);
		e->Attribute("y", &y);
		e->Attribute("width", &width);
		e->Attribute("height", &height);
		e->Attribute("numFrames", &numFrames);
		e->Attribute("callbackID", &callbackID);
		e->Attribute("animSpeed", &animSpeed);

		textureID = e->Attribute("textureID");

		GameObject* pGameObject = TheGameObjectFactory::Instance()->create(e->Attribute("type"));
		pGameObject->load(new LoaderParams(x, y, width, height, textureID, numFrames, callbackID, animSpeed));
		pObjects->push_back(pGameObject);
	}
}