#ifndef ANIMATED_GRAPHIC_H
#define ANIMATED_GRAPHIC_H

#include "SDLGameObject.h"

class AnimatedGraphic : public SDLGameObject 
{
public:

	AnimatedGraphic(const LoaderParams* pParams, int animSpeed);

	virtual void draw();
	virtual void update();
	virtual void clean();

private:
	int m_animSpeed;
};

#endif
