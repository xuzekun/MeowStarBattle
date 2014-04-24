#ifndef _GAMEABOUTSCENE_H
#define _GAMEABOUTSCENE_H

#include "cocos2d.h"
#include "GameMenuScene.h"
using namespace cocos2d;

class GameAbout: public CCLayer
{
public:
	virtual bool init();
	virtual void onEnter();
	static CCScene* scene();
	CREATE_FUNC(GameAbout);

	void menuReturnCallBack(CCObject* pSender);
};

#endif