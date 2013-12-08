#ifndef GameObjEnemy_H
#define GameObjEnemy_H

#include "cocos2d.h"
using namespace cocos2d;

class GameObjEnemy : public CCNode
{
private:
	CCSprite* boom;
	CCSprite* mainbody;
	int type;
	bool islife;

public:
	GameObjEnemy();
	virtual ~GameObjEnemy();

	virtual void onEnter();
	virtual void onExit();

	void setDie();

	void restart();
	void movestart();
	void setType(int type);
};

#endif 