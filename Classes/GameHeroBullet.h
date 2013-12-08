#ifndef GameHeroBullet_H
#define GameHeroBullet_H

#include "cocos2d.h"
using namespace cocos2d;

class GameHeroBullet:public CCNode
{
private:
	bool isVisible;
public:
	GameHeroBullet();
	virtual ~GameHeroBullet();
	void setIsNotVisable();
	void setIsVisable();
	bool getIsVisible();

	virtual void onEnter();
	virtual void onExit();
};

#endif