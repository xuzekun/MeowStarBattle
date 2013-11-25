#ifndef GameObjHero_H
#define GameObjHero_H

#include "cocos2d.h"
using namespace cocos2d;

class GameObjHero :public CCNode,public CCTargetedTouchDelegate
{
public:
	CCSprite* lefthand;
	CCSprite* righthand;
	bool isControl;
	CCPoint offset;

	GameObjHero(void);
	virtual ~GameObjHero(void);

	CCRect rect();
	bool containsTouchLocation(CCTouch* touch);

	virtual void onEnter();
	virtual void onExit();

	virtual bool ccTouchBegan(CCTouch* touch,CCEvent* event);
	virtual void ccTouchMoved(CCTouch* touch,CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch,CCEvent* event);

	virtual void touchDelegateRetain();
	virtual void touchDelegateRelease();

};

#endif GameObjHero_H