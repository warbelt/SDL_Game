#include <string>
#include <iostream>
#include "MenuState.h"
#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "MenuButton.h"
#include "PlayState.h"
#include "LoaderParams.h"
#include "GameStateMachine.h"
#include "InputHandler.h"

const std::string MenuState::s_menuID = "MENU";

void MenuState::update()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}
} //Bug--> se actualiza el boton play, esta clicado, se elimina el MenuState y se añade el Play estate ---- se vuelve a esta funcion que ya no existe!! ---
//Inicializar m_gameObjects para que al crear el nuevo estado, tenga tamaño 0?

void MenuState::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
}

bool MenuState::onEnter()
{
	if (!TheTextureManager::Instance()->load("assets/play.png", "playbutton", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/exit.png", "exitbutton", TheGame::Instance()->getRenderer()))
	{
		return false;
	}

	GameObject* button1 = new MenuButton(new LoaderParams(100, 100, 400, 100, "playbutton"), s_menuToPlay);
	GameObject* button2 = new MenuButton(new LoaderParams(100, 300, 400, 100, "exitbutton"), s_exitFromMenu);

	m_gameObjects.push_back(button1);
	m_gameObjects.push_back(button2);

	std::cout << "entering MenuState\n";
	return true;
}

bool MenuState::onExit()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
	}

	m_gameObjects.clear();
	TheTextureManager::Instance()->clearFromTextureMap("playbutton");
	TheTextureManager::Instance()->clearFromTextureMap("exitbutton");

	TheInputHandler::Instance()->reset();

	std::cout << "exiting MenuState\n";
	return true;
}

void MenuState::s_exitFromMenu()
{
	TheGame::Instance()->quit();
}

void MenuState::s_menuToPlay()
{
	TheGame::Instance()->getGameStateMachine()->changeState(new PlayState());
}