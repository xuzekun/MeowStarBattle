#include "HelloWorldScene.h"


using namespace cocos2d;
//CCArray* heroBullets;


CCScene* HelloWorld::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        HelloWorld *layer = HelloWorld::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    bool bRet = false;
    do 
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////

        CC_BREAK_IF(! CCLayer::init());

        //////////////////////////////////////////////////////////////////////////
        // add your codes below...
        //////////////////////////////////////////////////////////////////////////

        // 1. Add a menu item with "X" image, which is clicked to quit the program.

        // Create a "close" menu item with close icon, it's an auto release object.
        CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
            "CloseNormal.png",
            "CloseSelected.png",
            this,
            menu_selector(HelloWorld::menuCloseCallback));
        CC_BREAK_IF(! pCloseItem);

        // Place the menu item bottom-right conner.
        pCloseItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20));

        // Create a menu with the "close" menu item, it's an auto release object.
        CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
        pMenu->setPosition(CCPointZero);
        CC_BREAK_IF(! pMenu);

        // Add the menu to HelloWorld layer as a child layer.
        this->addChild(pMenu, 1);

        // 2. Add a label shows "Hello World".

        // Create a label and initialize with string "Hello World".
        CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);
        CC_BREAK_IF(! pLabel);

        // Get window size and place the label upper. 
        CCSize size = CCDirector::sharedDirector()->getWinSize();
        pLabel->setPosition(ccp(size.width / 2, size.height - 50));

        // Add the label to HelloWorld layer as a child layer.
        this->addChild(pLabel, 1);

        // 3. Add add a splash screen, show the cocos2d splash image.
        CCSprite* pSprite = CCSprite::create("Default.png");
        CC_BREAK_IF(! pSprite);

        // Place the sprite on the center of the screen
        pSprite->setPosition(ccp(size.width/2, size.height/2));

        // Add the sprite to HelloWorld layer as a child layer.
        this->addChild(pSprite, 0);

		/*
		CCSprite* cat = CCSprite::create("cat.png");
		cat->setPosition(ccp(100,200));
		this->addChild(cat,0);
		*/

		GameObjHero* hero = new GameObjHero();
		hero->setPosition(ccp(size.width/2,-50));
		this->addChild(hero);
		hero->runAction(CCMoveBy::create(0.5,ccp(0,150)));
/*
		GameObjEnemy* enemy = new GameObjEnemy();
		enemy->setPosition(ccp(300,200));
		this->addChild(enemy);

*/
		CCArray* enemys = CCArray::create();
		for (int i=0;i<3;i++)
		{
			GameObjEnemy* enemy = new GameObjEnemy();
			enemy->setPosition(ccp(size.width/4 * (i+1),size.height + 50));
			enemy->setScale(0.5);
			enemy->setType(i+1);
			
			enemys->addObject(enemy);
			this->addChild(enemy,1);
			enemy->movestart();
		}
		
		//heroBullets = CCArray::create();
		//heroBullets->ret
		heroBullets = new GameHeroBullet*[5];
		
		for(int i=0;i<5;i++)
		{
			heroBullets[i] = new GameHeroBullet();
			this->addChild(heroBullets[i],3);
			heroBullets[i]->setScale(0.5);
			heroBullets[i]->setIsNotVisable();
			//heroBullets[i]->setPosition(30*i,200);
		}

        bRet = true;
    } while (0);

    return bRet;
}

void HelloWorld::releaseHeroBullet(int x,int y)
{
	for (int i=0;i< 5;i++)
	{
		if (!heroBullets[i]->getIsVisable())
		{
			heroBullets[i]->setPosition(x,y);
			heroBullets[i]->setIsVisable();
			//heroBullets[i]->getVisible();
			break;
		}
		
	}
	
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    // "close" menu item clicked
    CCDirector::sharedDirector()->end();
}

