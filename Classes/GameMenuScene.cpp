#include "GameMenuScene.h"

CCScene* GameMenu::scene()
{
	CCScene* scene = NULL;
	do 
	{
		scene = CCScene::create();
		CC_BREAK_IF(!scene);

		GameMenu* layer = GameMenu::create();
		CC_BREAK_IF(!layer);

		scene->addChild(layer);
	} while (0);

	return scene;
}

bool GameMenu::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	CCSprite* bg = CCSprite::create("bg.png");
	bg->setPosition(ccp(size.width/2,size.height/2));
	bg->setScale(0.5);
	this->addChild(bg,0,0);

	CCSprite* moon = CCSprite::create("moon.png");
	moon->setAnchorPoint(ccp(0.5,0));
	moon->setPosition(ccp(size.width/3*2,0));
	moon->setScale(0.5);
	this->addChild(moon,1,1);

	CCNode* title = CCNode::create();
	title->setContentSize(CCSizeMake(size.width - 40 ,50));

	CCSprite* ptmLabel = CCSprite::create("meowstar.png");
	ptmLabel->setScale(0.5);
	ptmLabel->setPosition(ccp(0,30));
	title->addChild(ptmLabel);

	CCSprite* ptbLabel = CCSprite::create("battle.png");
	ptbLabel->setScale(0.5);
	ptbLabel->setPosition(ccp(0,-30));
	title->addChild(ptbLabel);

	title->setPosition(ccp(size.width/2,size.height - 80));
	this->addChild(title,2,2);

	CCMenuItemImage* newGameItem = CCMenuItemImage::create("newgameA.png","newgameB.png",this,menu_selector(GameMenu::menuNewGameCallback));
	newGameItem->setScale(0.5);
	newGameItem->setPosition(ccp(size.width/2,size.height/2 - 20));
	//newGameItem->setEnabled(false);

	CCMenuItemImage* continueItem = CCMenuItemImage::create("continueA.png","continueB.png",this,menu_selector(GameMenu::menuContinueCallback));
	continueItem->setScale(0.5);
	continueItem->setPosition(ccp(size.width/2,size.height/2 - 80));

	CCMenuItemImage* aboutItem = CCMenuItemImage::create("aboutA.png","aboutB.png",this,menu_selector(GameMenu::menuAboutCallback));
	aboutItem->setScale(0.5);
	aboutItem->setPosition(ccp(size.width/2,size.height/2 -140));

	soundItem = CCMenuItemImage::create("sound-on-A.png","sound-on-B.png",this,menu_selector(GameMenu::menuSoundCallback));
	soundItem->setScale(0.5);
	soundItem->setPosition(ccp(size.width-40,40));

	CCMenu* mainMenu = CCMenu::create(newGameItem,continueItem,aboutItem,soundItem,NULL);
	mainMenu->setPosition(CCPointZero);
	this->addChild(mainMenu,3,3);

	isSound = true;
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("background.mp3",true);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.5);
	return true;
}

void GameMenu::menuNewGameCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->replaceScene(GameMain::scene());
}

void GameMenu::menuContinueCallback(CCObject* pSender)
{

}

void GameMenu::menuAboutCallback(CCObject* pSender)
{

}

void GameMenu::menuSoundCallback(CCObject* pSender)
{
	if(!isSound)
	{
		soundItem->setNormalImage(CCSprite::create("sound-on-A.png"));
		soundItem->setDisabledImage(CCSprite::create("sound-on-B.png"));
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("background.mp3",true);
		isSound = true;
	}
	else
	{
		soundItem->setNormalImage(CCSprite::create("sound-off-A.png"));
		soundItem->setDisabledImage(CCSprite::create("sound-off-B.png"));
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
		isSound = false;
	}
}

void GameMenu::onEnter()
{
	CCLayer::onEnter();
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	CCNode* mainMenu = this->getChildByTag(3);
	mainMenu->setPositionX(-200);
	mainMenu->runAction(CCEaseSineIn::create(CCMoveTo::create(0.5,ccp(0,0))));

	CCNode* title = this->getChildByTag(2);
	title->setPositionY(size.height+20);
	title->runAction(CCEaseSineIn::create(CCMoveBy::create(0.5,ccp(0,-100))));

	CCNode* moon = this->getChildByTag(1);
	moon->setPositionY(-100);
	moon->runAction(CCEaseSineIn::create(CCMoveBy::create(0.5,ccp(0,100))));
}