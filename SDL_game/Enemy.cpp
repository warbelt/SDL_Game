#include "Enemy.h"

Enemy::Enemy(const LoaderParams* pParams) : SDLGameObject(pParams)
{}

void Enemy::draw()
{
	GameObject::draw();
}

void Enemy::update()
{
	m_x += 1;
	m_y += 1;
	m_currentFrame = int((SDL_GetTicks() / 100) & 6);
}

void Enemy::clean()
{}
