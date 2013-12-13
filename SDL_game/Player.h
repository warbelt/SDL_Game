#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"

class Player : protected GameObject 
{
public:

	void load(int x, int y, int width, int height, std::string textureID);
	void draw(SDL_Renderer* pRenderer);
	void update();
	void clean();
};

#endif