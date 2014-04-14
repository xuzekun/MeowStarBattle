#include "GameObjEnemy.h"
#include "GameMainScene.h"

GameObjEnemy::GameObjEnemy(){}

GameObjEnemy::~GameObjEnemy(){}

void GameObjEnemy::onEnter()
{
	CCNode::onEnter();
	this->setContentSize(CCSizeMake(99,111));

	mainbody = CCSprite::create("DrDog1.png");
	addChild(mainbody);

	CCAnimation* animation = CCAnimation::create();
	animation->addSpriteFrameWithFileName("DrDog1.png");
	animation->addSpriteFrameWithFileName("DrDog2.png");
	animation->setDelayPerUnit(0.1f);
	animation->setRestoreOriginalFrame(true);
	mainbody->runAction(CCRepeatForever::create(CCAnimate::create(animation)));

	boom = CCSprite::create("Boom1.png");
	addChild(boom);
	boom->setVisible(false);

	islife = true;

	//
	//setDie();
//	releaseBullet();
}

void GameObjEnemy::onExit()
{

}

void GameObjEnemy::setDie()
{
	islife = false;
	//boom->setPosition(ccp(-100,0));
	mainbody->setVisible(false);
	boom->setVisible(true);
	this->stopAllActions();
	CCAnimation* boomAnimation = CCAnimation::create();
	boomAnimation->addSpriteFrameWithFileName("Boom1.png");
	boomAnimation->addSpriteFrameWithFileName("Boom2.png");
	boomAnimation->addSpriteFrameWithFileName("Boom3.png");
	boomAnimation->addSpriteFrameWithFileName("Boom4.png");
	boomAnimation->addSpriteFrameWithFileName("Boom5.png");
	boomAnimation->setDelayPerUnit(0.1f);
	boomAnimation->setRestoreOriginalFrame(true);
	boom->runAction(CCSequence::create(CCAnimate::create(boomAnimation),CCCallFunc::create(this,callfunc_selector(GameObjEnemy::restart)),NULL));

}

void GameObjEnemy::setType(int type)
{
	this->type = type;
}

void GameObjEnemy::restart()
{
	
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	this->setPosition(ccp(size.width/4 * type,size.height + 50));
	islife = true;
	mainbody->setVisible(true);
	boom->setVisible(false);
	this->movestart();
	
}

void GameObjEnemy::movestart()
{
	islife = true;
	ccBezierConfig bezier1;
	bezier1.controlPoint_1 = CCPointMake(this->getPositionX()-400,330);
	bezier1.controlPoint_2 = CCPointMake(this->getPositionX()+400,280);
	bezier1.endPosition = CCPointMake(this->getPositionX(),-70);
	CCBezierTo* bezierBy1 = CCBezierTo::create(6,bezier1);

	ccBezierConfig bezier2;
	bezier2.controlPoint_1 = CCPointMake(this->getPositionX()+400,330);
	bezier2.controlPoint_2 = CCPointMake(this->getPositionX()-400,280);
	bezier2.endPosition = CCPointMake(this->getPositionX(),-70);
	CCBezierTo* bezierBy2 = CCBezierTo::create(6,bezier2);
	
	int type = CCRANDOM_0_1() * 4;
	
	switch (type)
	{
	case 0:
	case 1:
		this->runAction(CCSequence::create(CCMoveBy::create(6,ccp(0,-600)),CCCallFunc::create(this,callfunc_selector(GameObjEnemy::restart)),NULL));
		break;
	case 2:
		this->runAction(CCSequence::create(bezierBy1,CCCallFunc::create(this,callfunc_selector(GameObjEnemy::restart)),NULL));
		break;
	case 3:
		this->runAction(CCSequence::create(bezierBy2,CCCallFunc::create(this,callfunc_selector(GameObjEnemy::restart)),NULL));
		break;
	}
	schedule(schedule_selector(GameObjEnemy::releaseBullet),1.5f);
}

void GameObjEnemy::releaseBullet(float f)
{
	//CCSize size = CCDirector::sharedDirector()->getWinSize();
	GameMain* p = (GameMain*)this->getParent();
	p->releaseEnemyBullets(this->getPositionX(),this->getPositionY()-20);
}

bool GameObjEnemy::getIslife()
{
	return islife;
}