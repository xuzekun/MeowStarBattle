#ifndef GameEnemyBullet_H
#define GameEnemyBullet_H

#include "cocos2d.h"
using namespace cocos2d;

class GameEnemyBullet:public CCNode
{
private:
	bool isVisible;

	CCSprite* mainbody;
	CCSprite* bang;
	CCAnimation* bangAnimation ;

public:
	GameEnemyBullet();
	~GameEnemyBullet();

	void setIsVisable();
	void setIsNotVisable();
	bool getIsvisble();

	virtual void onEnter();

	void setBang();
};

#endif