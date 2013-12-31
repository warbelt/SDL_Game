#ifndef GAME_H
#define GAME_H

#include <vector>
#include <SDL.h>
#include <SDL_image.h>
class GameObject;
class GameStateMachine;

class Game
{
public:
	bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void handleEvents();
	void update();
	void render();
	void clean();

	bool running() { return m_bRunning; } //access to private running variable
	void quit() { m_bRunning = false; }

	SDL_Renderer* getRenderer() const { return m_pRenderer; }
	GameStateMachine* getGameStateMachine() { return m_pGameStateMachine; }

	static Game* Instance()
	{
		if(s_pInstance == 0)
		{
			s_pInstance = new Game();
			return s_pInstance;
		}
		return s_pInstance;
	}

	std::vector<GameObject*> m_gameObjects;

private:
	Game() {}
	~Game() {}

	static Game* s_pInstance;
	GameStateMachine* m_pGameStateMachine;

	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

	int m_currentFrame;
	bool m_bRunning;
};
typedef Game TheGame;

#endif
