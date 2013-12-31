#include "PlayState.h"
#include <iostream>
#include "TextureManager.h"
#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "LoaderParams.h"
#include "GameObject.h"
#include "InputHandler.h"
#include "GameStateMachine.h"
#include "PauseState.h"
#include "GameOverState.h"

const std::string PlayState::s_playID = "PLAY";

void PlayState::update()
{	//WATCH FOR PAUSE
	if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->getGameStateMachine()->pushState(new PauseState());
	}

	//UPDATE OBJECTS
	for(int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}

	//CHECK COLLISIONS
	if (checkCollision(dynamic_cast<SDLGameObject*> (m_gameObjects[0]), dynamic_cast<SDLGameObject*> (m_gameObjects[1])))
	{
		TheGame::Instance()->getGameStateMachine()->changeState(new GameOverState);
	}
}

void PlayState::render()
{
	for(int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
}

bool PlayState::onEnter()
{
	if(!TheTextureManager::Instance()->load("assets/helicopter.png", "helicopter", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if(!TheTextureManager::Instance()->load("assets/helicopter2.png", "helicopter2", TheGame::Instance()->getRenderer()))
	{
		return false;
	}

	GameObject* player = new Player(new LoaderParams(500, 100, 128, 55, "helicopter"));
	GameObject* enemy = new Enemy(new LoaderParams(100, 100, 128, 55, "helicopter2"));
	m_gameObjects.push_back(player);
	m_gameObjects.push_back(enemy);

	std::cout << "entering PlayState\n";
	return true;
}

bool PlayState::onExit()
{
	for(int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
	}

	m_gameObjects.clear();

	TheTextureManager::Instance()->clearFromTextureMap("helicopter");

	std::cout << "exiting PlayState\n";
	return true;
}

bool PlayState::checkCollision(SDLGameObject* p1, SDLGameObject* p2)
{
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	leftA = p1->getPosition()->getX();
	rightA = p1->getPosition()->getX() + p1->getWidth();
	topA = p1->getPosition()->getY();
	bottomA = p1->getPosition()->getY() + p1->getHeight();

	leftB = p2->getPosition()->getX();
	rightB = p2->getPosition()->getX() + p2->getWidth();
	topB = p2->getPosition()->getY();
	bottomB = p2->getPosition()->getY() + p2->getHeight();

	if (topA > bottomB || bottomA < topB || rightA < leftB || leftA > rightB) { return false; }
	return true;
}