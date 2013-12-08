#include "GameHeroBullet.h"

GameHeroBullet::GameHeroBullet()
{
}

GameHeroBullet::~GameHeroBullet()
{

}

void GameHeroBullet::onEnter()
{
	CCNode::onEnter();
	this->setContentSize(CCSizeMake(21,52));
	CCSprite* mainbody = CCSprite::create("catBullet.png");
	addChild(mainbody);
}

void GameHeroBullet::onExit()
{
	CCNode::onExit();
}


void GameHeroBullet::setIsVisable()
{
	this->setVisible(true);
	isVisible = true;
	this->runAction(CCSequence::create(CCMoveTo::create((550 - this->getPositionY())/300,ccp(this->getPositionX(),550)),CCCallFunc::create(this,callfunc_selector(GameHeroBullet::setIsNotVisable)),NULL));
}

void GameHeroBullet::setIsNotVisable()
{
	this->setVisible(false);
	isVisible = false;
	this->stopAllActions();
}

bool GameHeroBullet::getIsVisible()
{
	return isVisible;
}