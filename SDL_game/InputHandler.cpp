#include <iostream>
#include "InputHandler.h"
#include "Game.h"

InputHandler* InputHandler::s_pInstance = 0;

InputHandler::InputHandler()
{
	m_mousePosition = new Vector2D(0,0);

	for (int i = 0; i<3; i++)
	{
		m_mouseButtonStates.push_back(false);
	}
}

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

				std::vector<bool> tempButtons;

				for (int j = 0; j < SDL_JoystickNumButtons(joy); j++)
				{
					tempButtons.push_back(false);
				}

				m_buttonStates.push_back(tempButtons);
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
	m_keystates = SDL_GetKeyboardState(0);
	while(SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			TheGame::Instance()->quit();
			break;

		case SDL_JOYAXISMOTION:
			onJoystickAxisMove(event);
			break;

		case SDL_JOYBUTTONDOWN:
			onJoystickButtonDown(event);
			break;

		case SDL_JOYBUTTONUP:
			onJoystickButtonUp(event);
			break;

		case SDL_MOUSEBUTTONDOWN:
			onMouseButtonDown(event);
			break;

		case SDL_MOUSEBUTTONUP:
			onMouseButtonUp(event);
			break;

		case SDL_MOUSEMOTION:
			onMouseMove(event);
			break;

		case SDL_KEYDOWN:
			onKeyDown();
			break;

		case SDL_KEYUP:
			onKeyUp();
			break;

		default:
			break;
		}
	}
}
//Member accesors
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
bool InputHandler::isKeyDown(SDL_Scancode key)
{
/////////////////////////////////////////
///LIST OF SLD_SCANCODES AT LIBDSL.ORG///
/////////////////////////////////////////
	if(m_keystates != 0)
	{
		if(m_keystates[key] == 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}
	
//Wrappers
//Joystick
void InputHandler::onJoystickAxisMove(SDL_Event& event)
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
void InputHandler::onJoystickButtonDown(SDL_Event& event)
{
	int whichOne = event.jbutton.which;
	m_buttonStates[whichOne][event.jbutton.button] = true;
}
void InputHandler::onJoystickButtonUp(SDL_Event& event)
{
	int whichOne = event.jbutton.which;
	m_buttonStates[whichOne][event.jbutton.button] = false;
}
//Mouse
void InputHandler::onMouseButtonDown(SDL_Event& event)
{
	if (event.button.button = SDL_BUTTON_LEFT)
	{
		m_mouseButtonStates[LEFT] = true;
	}
	if (event.button.button = SDL_BUTTON_MIDDLE)
	{
		m_mouseButtonStates[MIDDLE] = true;
	}
	if (event.button.button = SDL_BUTTON_RIGHT)
	{
		m_mouseButtonStates[RIGHT] = true;
	}
}
void InputHandler::onMouseButtonUp(SDL_Event& event)
{
	if (event.button.button = SDL_BUTTON_LEFT)
	{
		m_mouseButtonStates[LEFT] = false;
	}
	if (event.button.button = SDL_BUTTON_MIDDLE)
	{
		m_mouseButtonStates[MIDDLE] = false;
	}
	if (event.button.button = SDL_BUTTON_RIGHT)
	{
		m_mouseButtonStates[RIGHT] = false;
	}
}
void InputHandler::onMouseMove(SDL_Event& event)
{
	m_mousePosition->setX(event.motion.x);			
	m_mousePosition->setY(event.motion.y);
}
//Keyboard
void InputHandler::onKeyDown(){}
void InputHandler::onKeyUp(){}