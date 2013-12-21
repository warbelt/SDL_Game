#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>

#include "TextureManager.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"

class Game
{
public:
	
	~Game() {}

	//set running variable true	
	bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void render();
	void update();
	void handleEvents();
	void clean();

	bool running() { return m_bRunning; } //access to private running variable
	std::vector<GameObject*> m_gameObjects;

	static Game* Instance()   //Texture Manager is singleton: Constructor is private so it can only be created by Instance, that assures there is only one TextureManager
	{
		if(s_pInstance == 0)
		{
			s_pInstance = new Game();
			return s_pInstance;
		}
		return s_pInstance;
	}

	SDL_Renderer* getRenderer() const {return m_pRenderer;}

private:

	Game();
	static Game* s_pInstance;

	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

	int m_currentFrame;
	bool m_bRunning;

	GameObject* m_go;
	GameObject* m_player;
	GameObject* m_enemy;
};

typedef Game TheGame;

#endif
