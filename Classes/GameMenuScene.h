#ifndef GameMenuScene_H
#define GameMenuScene_H

#include "cocos2d.h"
#include "GameMainScene.h"
#include "SimpleAudioEngine.h"
#include "GameAboutScene.h"
using namespace cocos2d;

class GameMenu : public CCLayer
{
public:
	bool isSound;
	CCMenuItemImage* soundItem;
	virtual bool init();
	static CCScene* scene();

	void menuNewGameCallback(CCObject* pSender);
	void menuContinueCallback(CCObject* pSender);
	void menuAboutCallback(CCObject* pSender);
	void menuSoundCallback(CCObject* pSender);
	void menuCloseCallback(CCObject* pSender);
	CREATE_FUNC(GameMenu);

	virtual void onEnter();
};

#endif