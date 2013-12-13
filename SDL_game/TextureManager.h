#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <string>
#include <iostream>
#include "SDL.h"
#include <map>

class TextureManager 
{
public:
	bool load (std::string fileName, std::string id, SDL_Renderer* pRenderer);
	void draw (std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawFrame (std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	std::map<std::string, SDL_Texture*> m_textureMap;
	
	static TextureManager* Instance()   //Texture Manager is singleton: Constructor is private so it can only be created by Instance, that assures there is only one TextureManager
	{
		if(s_pInstance == 0)
		{
			s_pInstance = new TextureManager();
			return s_pInstance;
		}
		return s_pInstance;
	};

private:
	TextureManager() {}
	static TextureManager* s_pInstance;

};

typedef TextureManager TheTextureManager;

#endif