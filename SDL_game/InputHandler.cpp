#include <iostream>
#include "InputHandler.h"
#include "Game.h"

InputHandler* InputHandler::s_pInstance = 0;

void InputHandler::initialiseJoysticks()
{
	//Initialize Joysticks subsystem
	if (SDL_WasInit(SDL_INIT_JOYSTICK) == 0)
	{
		SDL_InitSubSystem(SDL_INIT_JOYSTICK);
	}
	//Open each joystick and activate joystick events
	if (SDL_NumJoysticks > 0)
	{
		for (int i = 0; i < SDL_NumJoysticks(); i++)
		{
			SDL_Joystick* joy = SDL_JoystickOpen(i);
			if(joy)
			{
				m_joysticks.push_back(joy);
				m_joystickValues.push_back(std::make_pair(new Vector2D(0,0), new Vector2D(0,0)));
			}
			else
			{
				std::cout << SDL_GetError();
			}
		}

		SDL_JoystickEventState(SDL_ENABLE);
		m_bJoysticksInitialised = true;

		std::cout << "Initialised " << m_joysticks.size() << " joysticks\n";
	}
	else
	{
		m_bJoysticksInitialised = false;
	}
}

void InputHandler::clean()
{
	if (m_bJoysticksInitialised == true)
	{
		for (int i = 0; i < m_joysticks.size(); i++)
		{
			SDL_JoystickClose(m_joysticks[i]);
		}
	}
}

void InputHandler::update()
{
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		if(event.type == SDL_QUIT)
		{
			TheGame::Instance()->quit();
		}
		if(event.type == SDL_JOYAXISMOTION)
		{
			int whichOne = event.jaxis.which;
			//left stick left-right
			if (event.jaxis.axis == 0) 
			{
				if (event.jaxis.value > m_joystickDeadZone)
				{
					m_joystickValues[whichOne].first->setX(1);
				}
				else if (event.jaxis.value < -m_joystickDeadZone)
				{
					m_joystickValues[whichOne].first->setX(-1);
				}
				else
				{
					m_joystickValues[whichOne].first->setX(0);
				}
			}
			//left stick up-down
			else if (event.jaxis.axis == 1) 
			{
				if (event.jaxis.value > m_joystickDeadZone)
				{
					m_joystickValues[whichOne].first->setY(1);
				}
				else if (event.jaxis.value < -m_joystickDeadZone)
				{
					m_joystickValues[whichOne].first->setY(-1);
				}
				else
				{
					m_joystickValues[whichOne].first->setY(0);
				}
			}
			//right stick left-right
			else if (event.jaxis.axis == 2)
			{
				if (event.jaxis.value > m_joystickDeadZone)
				{
					m_joystickValues[whichOne].second->setX(1);
				}
				else if (event.jaxis.value < -m_joystickDeadZone)
				{
					m_joystickValues[whichOne].second->setX(-1);
				}
				else
				{
					m_joystickValues[whichOne].second->setX(0);
				}
			}
			//right stick up-down
			else if (event.jaxis.axis == 3) 
			{
				if (event.jaxis.value > m_joystickDeadZone)
				{
					m_joystickValues[whichOne].second->setY(1);
				}
				else if (event.jaxis.value < -m_joystickDeadZone)
				{
					m_joystickValues[whichOne].second->setY(-1);
				}
				else
				{
					m_joystickValues[whichOne].second->setY(0);
				}
			}
		}
	}
}

int InputHandler::xvalue(int joy, int stick)
{
	if(m_joysticks.size() > 0)
	{
		if(stick==1) //left stick
			return m_joystickValues[joy].first->getX();
		else if (stick==2) //right stick
			return m_joystickValues[joy].second->getX();
	}
	return 0;
}

int InputHandler::yvalue(int joy, int stick)
{
	if(m_joysticks.size() > 0)
	{
		if(stick==1) //left stick
			return m_joystickValues[joy].first->getY();
		else if (stick==2) //right stick
			return m_joystickValues[joy].second->getY();
	}
	return 0;
}