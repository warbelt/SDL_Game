#ifndef MENUSTATE_H
#define MENUSTATE_H

#include <vector>
#include "GameState.h"
class GameObject;

class MenuState : public GameState
{
public:
	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return s_menuID; }
	std::vector<GameObject*> m_gameObjects;

private:
	//call back functions for menu items
	static void s_menuToPlay();
	static void s_exitFromMenu();

	static const std::string s_menuID;
};

#endif