#include "SDLGameObject.h"
#include "LoaderParams.h"
#include "TextureManager.h"
#include "Game.h"
#include "Vector2D.h"

SDLGameObject::SDLGameObject() : GameObject() {}

void SDLGameObject::load(const LoaderParams* pParams)
{
	m_position = Vector2D(pParams->getX(), pParams->getY());
	m_velocity = Vector2D(0,0);
	m_acceleration = Vector2D(0,0);
	m_width = pParams->getWidth();
	m_height = pParams->getHeight();
	m_textureID = pParams->getTextureID();
	m_currentRow = 0;
	m_currentFrame = 0;
	m_numFrames = pParams->getNumFrames();
}

void SDLGameObject::draw()
{
	if(m_velocity.getX() > 0)
	{
		TextureManager::Instance()->drawFrame(m_textureID, m_position.getX(), m_position.getY(), m_width, m_height, m_currentRow, m_currentFrame, TheGame::Instance()->getRenderer(), SDL_FLIP_HORIZONTAL);
	}
	else
	{
		TextureManager::Instance()->drawFrame(m_textureID, m_position.getX(), m_position.getY(), m_width, m_height, m_currentRow, m_currentFrame, TheGame::Instance()->getRenderer());
	}
}

void SDLGameObject::clean()
{}

void SDLGameObject::update()
{
	m_velocity+=m_acceleration;
	m_position+=m_velocity;
}