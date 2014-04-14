#ifndef GameMainScene_H
#define GameMainScene_H

#include "cocos2d.h"
#include "GameObjHero.h"
#include "GameObjEnemy.h"
#include "GameHeroBullet.h"
#include "GameEnemyBullet.h"

using namespace cocos2d;

class GameMain:public CCLayer
{
private:
	GameObjHero* hero;
	GameObjEnemy** enemys;
	GameHeroBullet** heroBullets;
	GameEnemyBullet** enemyBullets;
	CCSprite* bg1;
	CCSprite* bg2;
	CCLabelAtlas* markLabel;
	int mark;

	int heroBulletsNum;
	int enemyBulletsNum;

	int heroLife;
	CCSprite* blood1;
	CCSprite* blood2;
	CCSprite* blood3;

public:
	static CCScene* scene();
	virtual bool init();

	CREATE_FUNC(GameMain);

	void releaseHeroBullets(int x,int y);
	void releaseEnemyBullets(int x,int y);
	virtual void update(float time);

	bool isCollion(CCPoint p1,CCPoint p2,int w1,int h1,int w2,int h2);
	void setHeroHurt();

	CCLabelTTF* l;
};

#endif