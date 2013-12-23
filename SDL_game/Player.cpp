#include "Player.h"

Player::Player(const LoaderParams* pParams) : SDLGameObject(pParams)
{}

void Player::draw()
{
	SDLGameObject::draw();
}

void Player::update()
{
	m_position-=Vector2D(1,0);
	m_currentFrame = int((SDL_GetTicks() / 100) % 6);
}

void Player::clean()
{}
