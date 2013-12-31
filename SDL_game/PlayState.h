#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "GameState.h"
#include <vector>
class SDLGameObject;
class GameObject;

class PlayState : public GameState
{
public:
	virtual void update();
	virtual void render();
	bool checkCollision(SDLGameObject* p1, SDLGameObject* p2);

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return s_playID; }

private:
	static const std::string s_playID;

	std::vector<GameObject*> m_gameObjects;
};

#endif