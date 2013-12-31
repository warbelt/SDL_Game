#include <string>
#include "GameOverState.h"
#include "GameObject.h"
#include "TextureManager.h"
#include "Game.h"
#include "MenuButton.h"
#include "LoaderParams.h"
#include "AnimatedGraphic.h"
#include "GameStateMachine.h"
#include "MenuState.h"
#include "PlayState.h"

const std::string GameOverState::s_gameOverID = "GAMEOVER";

void GameOverState::update()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}
}

void GameOverState::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
}

bool GameOverState::onEnter()
{
	if (!TheTextureManager::Instance()->load("assets/main.png", "mainbutton", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/restart.png", "restartbutton", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/gameover.png", "gameover", TheGame::Instance()->getRenderer()))
	{
		return false;
	}

	GameObject* button1 = new MenuButton(new LoaderParams(200, 200, 200, 80, "mainbutton"), s_gameOverToMain);
	GameObject* button2 = new MenuButton(new LoaderParams(200, 300, 200, 80, "restartbutton"), s_restartPlay);
	GameObject* gameOverText = new AnimatedGraphic(new LoaderParams(200, 100, 190, 30, "gameover"), 2);

	m_gameObjects.push_back(button1);
	m_gameObjects.push_back(button2);
	m_gameObjects.push_back(gameOverText);

	std::cout << "entering GameOverState\n";
	return true;
}

bool GameOverState::onExit()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
	}

	m_gameObjects.clear();
	TheTextureManager::Instance()->clearFromTextureMap("restartbutton");
	TheTextureManager::Instance()->clearFromTextureMap("mainbutton");
	TheTextureManager::Instance()->clearFromTextureMap("gameover");

	std::cout << "exiting GameOverState\n";
	return true;
}

void GameOverState::s_gameOverToMain()
{
	TheGame::Instance()->getGameStateMachine()->changeState(new MenuState);
}

void GameOverState::s_restartPlay()
{
	TheGame::Instance()->getGameStateMachine()->changeState(new PlayState);
}