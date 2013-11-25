#include "GameObjHero.h"

GameObjHero::GameObjHero(){}

GameObjHero::~GameObjHero(){}

CCRect GameObjHero::rect()
{
	CCSize s = CCSizeMake(85,90);
	return CCRectMake(-s.width/2,-s.height/2,s.width,s.height);
}

bool GameObjHero::containsTouchLocation(CCTouch* touch)
{
	return rect().containsPoint(convertTouchToNodeSpaceAR(touch));
}

void GameObjHero::onEnter()
{
	CCNode::onEnter();
	this->setContentSize(CCSizeMake(85,90));

	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,true);

	CCSprite* mainsprite = CCSprite::create("catBody1.png");
	CCAnimation* animation = CCAnimation::create();
	animation->addSpriteFrameWithFileName("catBody1.png");
	animation->addSpriteFrameWithFileName("catBody2-4.png");
	animation->addSpriteFrameWithFileName("catBody3.png");
	animation->addSpriteFrameWithFileName("catBody2-4.png");
	animation->setDelayPerUnit(0.1f);
	animation->setRestoreOriginalFrame(true);
	mainsprite->runAction(CCRepeatForever::create(CCAnimate::create(animation)));
	addChild(mainsprite);

	CCSprite* tail = CCSprite::create("catTail.png");
	tail->setAnchorPoint(ccp(0.5,1));
	tail->setPosition(ccp(-5,-29));
	tail->setScale(0.5);
	tail->setRotation(20);
	tail->runAction(CCRepeatForever::create((CCActionInterval*)CCSequence::create(CCRotateBy::create(0.5,-40),CCRotateBy::create(0.5,40),NULL)));
	addChild(tail);

	lefthand = CCSprite::create("catHand1.png");
	lefthand->setAnchorPoint(ccp(1,0.5));
	lefthand->setPosition(ccp(-18,-20));
	addChild(lefthand);

	righthand = CCSprite::create("catHand2.png");
	righthand->setAnchorPoint(ccp(0,0.5));
	righthand->setPosition(ccp(18,-20));
	addChild(righthand);

	offset = ccp(0,0);

	isControl = false;
}

bool GameObjHero::ccTouchBegan(CCTouch* touch,CCEvent* event)
{
	if(! containsTouchLocation(touch))
		return false;

	isControl = true;
	CCPoint touchPoint = touch->getLocationInView();
	touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);

	offset.x = touchPoint.x - this->getPosition().x;
	offset.y = touchPoint.y - this->getPosition().y;

	return true;
}

void GameObjHero::ccTouchMoved(CCTouch* touch,CCEvent* event)
{
	if (isControl)
	{
		CCPoint touchPoint = touch->getLocationInView();
		touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);

		float x = touchPoint.x - offset.x;
		float y = touchPoint.y - offset.y;

		if (x < this->getPosition().x)
		{
			lefthand->setFlipY(true);
			righthand->setFlipY(false);
		} 
		else
		{
			lefthand->setFlipY(false);
			righthand->setFlipY(true);
		}

		this->setPosition(x,y);
	}
}

void GameObjHero::ccTouchEnded(CCTouch* touch,CCEvent* event)
{
	if (isControl)
	{
		isControl = false;
		lefthand->setFlipY(false);
		righthand->setFlipY(false);
	}
}

void GameObjHero::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCNode::onExit();
}

void GameObjHero::touchDelegateRelease()
{
	this->release();
}

void GameObjHero::touchDelegateRetain()
{
	this->retain();
}