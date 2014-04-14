#ifndef GameHeroBullet_H
#define GameHeroBullet_H

#include "cocos2d.h"
using namespace cocos2d;

class GameHeroBullet:public CCNode
{
private:
	bool isVisible;
	CCSprite* mainbody;


public:
	GameHeroBullet();
	virtual ~GameHeroBullet();
	void setIsNotVisable();
	void setIsVisable();
	bool getIsVisable();

	virtual void onEnter();
	virtual void onExit();

	
};

#endif