#include "Enemy.h"

Enemy::Enemy(const LoaderParams* pParams) : SDLGameObject(pParams)
{}

void Enemy::draw()
{
	SDLGameObject::draw();
}

void Enemy::update()
{
	m_acceleration.setX(0.0625);
	m_velocity.setY(1);
	SDLGameObject::update();

	m_currentFrame = int((SDL_GetTicks() / 100) % 6);
}

void Enemy::clean()
{}
