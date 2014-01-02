#include "MenuButton.h"
#include "InputHandler.h"
#include "LoaderParams.h"

MenuButton::MenuButton() : SDLGameObject()
{
	m_currentFrame = MOUSE_OUT;
	m_bReleased = 0;
}

void MenuButton::load(const LoaderParams* pParams)
{
	SDLGameObject::load(pParams);
	m_callbackID = pParams->getCallbackID();
	m_currentFrame = MOUSE_OUT;
}

void MenuButton::draw()
{
	SDLGameObject::draw();
}

void MenuButton::update()
{
	Vector2D* pMousePos = TheInputHandler::Instance()->getMousePosition();
	if ( pMousePos->getX() > m_position.getX() 
		&& pMousePos->getX() < (m_position.getX() + m_width)
		&& pMousePos->getY() > m_position.getY()
		&& pMousePos->getY() < (m_position.getY() + m_height))
	{
		if (TheInputHandler::Instance()->getMouseButtonState(LEFT) && m_bReleased)
		{
			m_currentFrame = CLICKED;
			m_bReleased = false;
			m_callback();
		}
		else if (!TheInputHandler::Instance()->getMouseButtonState(LEFT))
		{
			m_currentFrame = MOUSE_OVER;
			m_bReleased = true;
		}
	}
	else
	{
		m_currentFrame = MOUSE_OUT;
	}
}

void MenuButton::clean()
{
	SDLGameObject::clean();
}