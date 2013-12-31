#include <string>
#include <iostream>
#include "PauseState.h"
#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "MenuButton.h"
#include "PlayState.h"
#include "LoaderParams.h"
#include "GameStateMachine.h"
#include "MenuState.h"

const std::string PauseState::s_pauseID = "PAUSE";

void PauseState::update()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}
} //Bug--> se actualiza el boton play, esta clicado, se elimina el MenuState y se añade el Play estate ---- se vuelve a esta funcion que ya no existe!! ---
//Inicializar m_gameObjects para que al crear el nuevo estado, tenga tamaño 0?

void PauseState::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
}

bool PauseState::onEnter()
{
	if (!TheTextureManager::Instance()->load("assets/main.png", "mainbutton", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/resume.png", "resumebutton", TheGame::Instance()->getRenderer()))
	{
		return false;
	}

	GameObject* button1 = new MenuButton(new LoaderParams(200, 100, 200, 80, "mainbutton"), s_pauseToMain);
	GameObject* button2 = new MenuButton(new LoaderParams(200, 300, 200, 80, "resumebutton"), s_resumePlay);

	m_gameObjects.push_back(button1);
	m_gameObjects.push_back(button2);

	std::cout << "entering PauseState\n";
	return true;
}

bool PauseState::onExit()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
	}

	m_gameObjects.clear();
	TheTextureManager::Instance()->clearFromTextureMap("resumebutton");
	TheTextureManager::Instance()->clearFromTextureMap("mainbutton");

	std::cout << "exiting PauseState\n";
	return true;
}

void PauseState::s_pauseToMain()
{
	TheGame::Instance()->getGameStateMachine()->changeState(new MenuState());
}

void PauseState::s_resumePlay()
{
	TheGame::Instance()->getGameStateMachine()->popState();
}