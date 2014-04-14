#ifndef GameMenuScene_H
#define GameMenuScene_H

#include "cocos2d.h"
#include "GameMainScene.h"
using namespace cocos2d;

class GameMenu : public CCLayer
{
public:
	virtual bool init();
	static CCScene* scene();

	void menuNewGameCallback(CCObject* pSender);
	void menuContinueCallback(CCObject* pSender);
	void menuAboutCallback(CCObject* pSender);
	CREATE_FUNC(GameMenu);

	virtual void onEnter();
};

#endif