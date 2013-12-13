#ifndef GAME_H
#define GAME_H

#include "SDL.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Player.h"

class Game
{
public:
	
	Game() {}
	~Game() {}

	//set running variable true	
	bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void render();
	void update();
	void handleEvents();
	void clean();

	bool running() { return m_bRunning; } //access to private running variable

private:

	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

	int m_currentFrame;
	bool m_bRunning;

	GameObject m_go;
	Player m_player;
};

#endif