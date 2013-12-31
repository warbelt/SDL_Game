#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <iostream>
#include <SDL.h>
class LoaderParams;

class GameObject 
{
public:

	virtual void draw() =0;
	virtual void update() =0;
	virtual void clean() =0;

protected:
	
	GameObject (const LoaderParams* pParams) {}
	virtual ~GameObject() {}
};

#endif
