#include "GameEnemyBullet.h"

GameEnemyBullet::GameEnemyBullet(){}

GameEnemyBullet::~GameEnemyBullet(){}

bool GameEnemyBullet::getIsvisble()
{
	return isVisible;
}

void GameEnemyBullet::setIsVisable()
{
	this->setVisible(true);
	mainbody->setVisible(true);
	bang->setVisible(false);
	isVisible = true;
	this->runAction(CCRepeatForever::create(CCRotateBy::create(1,360)));
	this->runAction(CCSequence::create(CCMoveTo::create((this->getPositionY() +50)/150,ccp(this->getPositionX(),-50)),CCCallFunc::create(this,callfunc_selector(GameEnemyBullet::setIsNotVisable)),NULL));
}

void GameEnemyBullet::setIsNotVisable()
{
	this->setVisible(false);
	isVisible = false;
	this->stopAllActions();
}

void GameEnemyBullet::onEnter()
{
	CCNode::onEnter();
	this->setContentSize(CCSizeMake(21,52));
	mainbody = CCSprite::create("DrDogBullet.png");
	mainbody->runAction(CCRepeatForever::create(CCRotateBy::create(1,360)));
	addChild(mainbody);

	CCTexture2D* bangTexture = CCTextureCache::sharedTextureCache()->addImage("bang.png");
	bang = CCSprite::createWithTexture(bangTexture,CCRectMake(0,0,500,486));
	addChild(bang);
	bang->setVisible(false);
}

void GameEnemyBullet::setBang()
{
	isVisible = false;
	this->stopAllActions();

	mainbody->setVisible(false);
	bang->setVisible(true);

	CCTexture2D* bangTexture = CCTextureCache::sharedTextureCache()->addImage("bang.png");
	CCArray* aniFrames = CCArray::createWithCapacity(4);

	CCSpriteFrame** frames = new CCSpriteFrame*[4];
	frames[0] = CCSpriteFrame::createWithTexture(bangTexture,CCRectMake(0,0,500,486));
	frames[2] = CCSpriteFrame::createWithTexture(bangTexture,CCRectMake(500,0,500,486));
	frames[1] = CCSpriteFrame::createWithTexture(bangTexture,CCRectMake(486,0,500,486));
	frames[3] = CCSpriteFrame::createWithTexture(bangTexture,CCRectMake(486,500,500,486));
	aniFrames->addObject(frames[0]);
	aniFrames->addObject(frames[1]);
	aniFrames->addObject(frames[2]);
	aniFrames->addObject(frames[3]);
	bangAnimation = CCAnimation::createWithSpriteFrames(aniFrames,0.1f);

	bang->setScale(0.1f);
	aniFrames->release();
	//bang->setVisible(true);
	//	bang->runAction(CCAnimate::create(bangAnimation));
	bang->runAction(CCSequence::create(CCAnimate::create(bangAnimation),CCCallFunc::create(this,callfunc_selector(GameEnemyBullet::setIsNotVisable)),NULL));
}