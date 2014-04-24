#include "GameAboutScene.h"

CCScene* GameAbout::scene()
{
	CCScene* scene = CCScene::create();
	GameAbout* layer = GameAbout::create();
	scene->addChild(layer);
	return scene;
}

bool GameAbout::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	CCSize size = CCDirector::sharedDirector()->getWinSize();

	CCSprite* bg = CCSprite::create("bg.png");
	bg->setScale(0.5);
	bg->setPosition(ccp(size.width/2,size.height/2));
	this->addChild(bg,0);

	CCSprite* moon = CCSprite::create("moon.png");
	moon->setScale(0.5);
	moon->setAnchorPoint(ccp(0.5,0));
	moon->setPosition(ccp(size.width/3,0));
	this->addChild(moon,1,1);

	CCSprite* tb = CCSprite::create("tb.png");
	tb->setPosition(ccp(size.width/2,size.height/2));
	tb->setScale(0.5);
	this->addChild(tb,2,2);

	CCSprite* aboutTitle = CCSprite::create("about.png");
	aboutTitle->setPosition(ccp(size.width/2,size.height-20));
	aboutTitle->setScale(0.5);
	this->addChild(aboutTitle,3,3);

	CCMenuItemImage* pReturnItem = CCMenuItemImage::create("backA.png","backB.png",this,menu_selector(GameAbout::menuReturnCallBack));
	pReturnItem->setPosition(ccp(size.width-20,size.height-20));
	pReturnItem->setScale(0.5);

	CCMenu* menu = CCMenu::create(pReturnItem,NULL);
	menu->setPosition(ccp(0,0));
	this->addChild(menu,4,4);

	char inf[30];
	sprintf(inf,"Present By: \n\nXuZekun");
	CCLabelTTF* info = CCLabelTTF::create(inf,"Marker Felt",24);
	info->setPosition(ccp(size.width/2,size.height/2+20));
	this->addChild(info,5,5);

	return true;
}

void GameAbout::menuReturnCallBack(CCObject* pSender)
{
	CCDirector::sharedDirector()->replaceScene(GameMenu::scene());
}

void GameAbout::onEnter()
{
	CCLayer::onEnter();
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	CCNode* menu  = this->getChildByTag(4);
	menu->setPositionX(-100);
	menu->runAction(CCEaseSineIn::create(CCMoveBy::create(0.5,ccp(100,0))));

	CCNode* moon = this->getChildByTag(1);
	moon->setPosition(ccp(size.width/3*2,0));
	moon->runAction(CCEaseSineIn::create(CCMoveBy::create(0.5,ccp(-size.width/3,0))));

	CCNode* aboutTitle = this->getChildByTag(3);
	aboutTitle->setPositionY(size.height+20);
	aboutTitle->runAction(CCEaseSineIn::create(CCMoveBy::create(0.5,ccp(0,-40))));

	CCNode* tb = this->getChildByTag(2);
	tb->setPositionX(-200);
	tb->runAction(CCEaseSineIn::create(CCMoveTo::create(0.5,ccp(size.width/2,size.height/2))));

	CCNode* info = this->getChildByTag(5);
	info->setPositionX(-200);
	info->runAction(CCEaseSineIn::create(CCMoveTo::create(0.5,ccp(size.width/2,size.height/2+20))));

}