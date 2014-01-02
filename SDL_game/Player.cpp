#include "Player.h"
#include "InputHandler.h"

Player::Player() : SDLGameObject()
{}

void Player::load(const LoaderParams* pParams)
{
	SDLGameObject::load(pParams);
}

void Player::draw()
{
	SDLGameObject::draw();
}

void Player::update()
{
	m_velocity.setX(0);
	m_velocity.setY(0);

	handleInput();

	m_currentFrame = int((SDL_GetTicks() / 100) % 5);

	SDLGameObject::update();
}

void Player::clean()
{}

void Player::handleInput()
{
	if(TheInputHandler::Instance()->joysticksInitialised())
	{
		//Stick movement
		/*
		if(TheInputHandler::Instance()->xvalue(0,1) > 0 || TheInputHandler::Instance()->xvalue(0,1) < 0)
		{
			m_velocity.setX(1 * TheInputHandler::Instance()->xvalue(0,1));
		}
		else if(TheInputHandler::Instance()->yvalue(0,1) > 0 || TheInputHandler::Instance()->yvalue(0,1) < 0)
		{
			m_velocity.setY(1 * TheInputHandler::Instance()->yvalue(0,1));
		}
		else if(TheInputHandler::Instance()->xvalue(0,2) > 0 || TheInputHandler::Instance()->xvalue(0,2) < 0)
		{
			m_velocity.setX(1 * TheInputHandler::Instance()->xvalue(0,2));
		}
		else if(TheInputHandler::Instance()->yvalue(0,2) > 0 || TheInputHandler::Instance()->yvalue(0,2) < 0)
		{
			m_velocity.setY(1 * TheInputHandler::Instance()->yvalue(0,2));
		}
		*/

		//Buttons
		/*
		if(TheInputHandler::Instance()->getButtonState(0, 3))
		{
			m_velocity.setX(1);
		}
		*/

		//Mouse buttons
		/*
		if(TheInputHandler::Instance()->getMouseButtonState(LEFT))
		{
			m_velocity.setY(1);
		}
		*/

		//Mouse position
		
		Vector2D* mPos = TheInputHandler::Instance()->getMousePosition();

		m_velocity = (*mPos - m_position) /50;
		

		//Keyboard arrow keys
		/*if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT))
		{
			m_velocity.setX(-2);
		}
		if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT))
		{
			m_velocity.setX(2);
		}
		if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP))
		{
			m_velocity.setY(-2);
		}
		if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN))
		{
			m_velocity.setY(2);
		}*/
	}
	
}