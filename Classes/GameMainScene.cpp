#include "GameMainScene.h"

CCScene* GameMain::scene()
{
	CCScene* scene = NULL; 
	do 
	{
		scene = CCScene::create();
		CC_BREAK_IF(!scene);

		GameMain* layer = GameMain::create();
		CC_BREAK_IF(!layer);

		scene->addChild(layer);

	} while (0);
	
	return scene;
}

bool GameMain::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());

		CCSize size = CCDirector::sharedDirector()->getWinSize();

		bg1 = CCSprite::create("bg.png");
		bg1->setScale(0.5);
		bg1->setAnchorPoint(ccp(0,0));
		bg1->setPosition(ccp(0,0));
		this->addChild(bg1,0);

		bg2 = CCSprite::create("bg.png");
		bg2->setScale(0.5);
		bg2->setAnchorPoint(ccp(0,0));
		bg2->setPosition(ccp(0,size.height));
		this->addChild(bg2,0);

		hero = new GameObjHero();
		hero->setPosition(ccp(size.width/2,-50));
		this->addChild(hero,2);
		hero->setScale(0.5);
		hero->runAction(CCMoveBy::create(1,ccp(0,150)));

		enemys = new GameObjEnemy*[3];
		for (int i=0;i<3;i++)
		{
			enemys[i] = new GameObjEnemy();
			enemys[i]->setPosition(ccp(size.width/4 * (i+1),size.height + 50));
			enemys[i]->setScale(0.5);
			enemys[i]->setType(i+1);

			this->addChild(enemys[i],1);
			enemys[i]->movestart();
		}

		heroBulletsNum = 5;
		enemyBulletsNum = 9;

		heroBullets = new GameHeroBullet* [heroBulletsNum];
		for(int i =0;i<heroBulletsNum;i++)
		{
			heroBullets[i] = new GameHeroBullet();
			heroBullets[i]->setScale(0.5);
			heroBullets[i]->setIsNotVisable();
			this->addChild(heroBullets[i],3);
		}
		/*
		GameEnemyBullet* eB = new GameEnemyBullet();
		eB->setPosition(ccp(100,500));
		eB->setIsVisible();
		addChild(eB);
		*/

		enemyBullets = new GameEnemyBullet* [enemyBulletsNum];
		for (int i=0;i<enemyBulletsNum;i++)
		{
			enemyBullets[i] = new GameEnemyBullet();
			enemyBullets[i]->setScale(0.5);
			enemyBullets[i]->setIsNotVisable();
			this->addChild(enemyBullets[i],3);
		}

		// set score
		CCSprite* scoreLabel = CCSprite::create("score.png");
		scoreLabel->setPosition(ccp(size.width/2+40,size.height-15));
		scoreLabel->setScale(0.5);
		this->addChild(scoreLabel,4);
		
		markLabel = CCLabelAtlas::create("./0123456789","fps_images.png",12,32,'.');
		markLabel->setString("00000");
		markLabel->setScale(1.3f);
		markLabel->setPosition(ccp(size.width/2+70,size.height-25));
		this->addChild(markLabel,4);
		
		mark = 0;

		//set blood
		heroLife = 3;
		CCSpriteBatchNode* ui = CCSpriteBatchNode::create("cat.png");
		blood1 = CCSprite::createWithTexture(ui->getTexture());
		blood1->setScale(0.2f);
		blood1->setPosition(ccp(20,size.height-20));
		ui->addChild(blood1);

		blood2 = CCSprite::createWithTexture(ui->getTexture());
		blood2->setScale(0.2f);
		blood2->setPosition(ccp(50,size.height-20));
		ui->addChild(blood2);

		blood3 = CCSprite::createWithTexture(ui->getTexture());
		blood3->setScale(0.2f);
		blood3->setPosition(ccp(80,size.height-20));
		ui->addChild(blood3);
		this->addChild(ui,4);

		//set GameOver Menu
		gameover = CCSprite::create("gameover.png");
		gameover->setPosition(ccp(size.width/2,size.height/2+50));
		gameover->setScale(0.5);
		gameover->setVisible(false);
		this->addChild(gameover,5);

		CCMenuItemImage* pRetryItem = CCMenuItemImage::create("retry.png","retry.png",this,menu_selector(GameMain::menuRetryCallBack));
		pRetryItem->setPosition(ccp(size.width/2,size.height/2-20));
		pRetryItem->setScale(0.8);

		CCMenuItemImage* pCloseItem = CCMenuItemImage::create("back.png","back.png",this,menu_selector(GameMain::menuCloseCallBack));
		pCloseItem->setPosition(ccp(size.width/2,size.height/2-70));
		pCloseItem->setScale(0.8);

		overMenu = CCMenu::create(pRetryItem,pCloseItem,NULL);
		overMenu->setPosition(ccp(0,0));
		overMenu->setVisible(false);
		this->addChild(overMenu,5);

		isReduce = false;
		isOver = false;
		scheduleUpdate();

		///////////

		//CCLabelTTF* l = CCLabelTTF::create("0","Î¢ÈíÑÅºÚ",24);
		//l->setPosition(ccp(300,460));
		//this->addChild(l,5,10);

	//	CCLabelAtlas* mark = CCLabelAtlas::create("./0123456789","fps_images.png",12,32,'.');
	//	mark->setPosition(ccp(100,400));
	//	mark->setString("./903478:5");
	//this->addChild(mark);
	
		//	CCSprite*a = CCSprite::create("bang.jpg");
	//	a->setPosition(ccp(0,0));
	//	this->addChild(a);
		///////////////
	
		bRet = true;
	} while (0);
	return bRet;
}

void GameMain::releaseHeroBullets(int x,int y)
{
	for (int i=0;i<5;i++)
	{
		if (!heroBullets[i]->getIsVisable())
		{
			heroBullets[i]->setPosition(x,y);
			heroBullets[i]->setIsVisable();
			break;
		}
	}
}

void GameMain::releaseEnemyBullets(int x,int y)
{
	for(int i=0;i<enemyBulletsNum;i++)
	{
		if(!enemyBullets[i]->getIsvisble())
		{
			enemyBullets[i]->setPosition(x,y);
			enemyBullets[i]->setIsVisable();
			break;
		}
	}
}

void GameMain::update(float time)
{
	if(!isOver)
	{
		bg1->setPosition(ccp(bg1->getPositionX(),bg1->getPositionY() - 1));
		bg2->setPosition(ccp(bg2->getPositionX(),bg2->getPositionY() - 1));

		CCSize size = CCDirector::sharedDirector()->getWinSize();

		if(bg1->getPositionY() <= -480)
		{
			bg1->setPosition(ccp(0,size.height));
		}

		if(bg2->getPositionY() <= -480)
		{
			bg2->setPosition(ccp(0,size.height));
		}
	static int kill=0;
	//enemy vs herobullets
		CCPoint heroPos = hero->getPosition();

		for (int i=0;i<3;i++)
		{
			if(enemys[i]->getIslife())
			{
				CCPoint enemyPos = enemys[i]->getPosition();
				for(int j=0;j<heroBulletsNum;j++)
				{
					if (heroBullets[j]->getIsVisable())
					{
						CCPoint bulletPos = heroBullets[j]->getPosition();
						if(isCollion(enemyPos,bulletPos,5,13,21,28))
						{
							//enemys[i]->setVisible(false);
					//		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("boom.wav");
							enemys[i]->setDie();
							heroBullets[j]->setIsNotVisable();
							kill++;
							mark +=20;
							break;
							//heroBullets[]
						}
					}
				}
			}
		}
		//herobullets vs enemybullets
		static int collion = 0;
		for (int i=0;i<heroBulletsNum;i++)
		{
			if(heroBullets[i]->getIsVisable())
			{
				CCPoint herobulletsPos = heroBullets[i]->getPosition();
				for (int j=0;j<enemyBulletsNum;j++)
				{
					if(enemyBullets[j]->getIsvisble())
					{
						CCPoint enemybulletsPos = enemyBullets[j]->getPosition();
						if(isCollion(herobulletsPos,enemybulletsPos,5,13,5,13))
						{
						//	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("bulletsCollion.mp3");
							heroBullets[i]->setIsNotVisable();
						//	enemyBullets[j]->setIsNotVisable();
							enemyBullets[j]->setBang();
							collion++;
							mark +=5;
							break;
						}
					}
				}

			}
		}
	
		//hero vs enemy
	//	static int heroLife = 10;
		if(!isReduce)
		{
			for (int i=0;i<3;i++)
			{
				if(enemys[i]->getIslife())
				{
					CCPoint enemyPos = enemys[i]->getPosition();
			
					if(isCollion(heroPos,enemyPos,21,22.5,21,28))
					{
					//	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("boom.wav");
						enemys[i]->setDie();
						setHeroHurt();
						mark += 20;
					}
				}
			}

			//hero vs enemybullets
			for (int i=0;i<enemyBulletsNum;i++)
			{
				if(enemyBullets[i]->getIsvisble())
				{
					CCPoint enemyBulletPos = enemyBullets[i]->getPosition();
					if(isCollion(heroPos,enemyBulletPos,21,22.5,5,13))
					{
						setHeroHurt();
						//enemyBullets[i]->setIsNotVisable();
						enemyBullets[i]->setBang();
					}
				}
			}
		}
	}
	/*
	this->removeChildByTag(10);
	char s[20];
	sprintf(s,"%d %d %d",kill,collion,heroLife);
	CCLabelTTF* l = CCLabelTTF::create(s,"Î¢ÈíÑÅºÚ",24);
	l->setPosition(ccp(250,440));
	this->addChild(l,5,10);
	*/
	char str[10];
	sprintf(str,"%d",mark);
	markLabel->setString(str);

}

bool GameMain::isCollion(CCPoint p1,CCPoint p2,int w1,int h1,int w2,int h2)
{
	if(abs(p1.x-p2.x)<w1+w2 && abs(p1.y -p2.y)<h1+h2)
		return true;
	else return false;
}

void GameMain::setHeroHurt()
{	
	hero->runAction(CCSequence::create(CCBlink::create(2,6),CCCallFunc::create(this,callfunc_selector(GameMain::resetReduce)),NULL));
	isReduce = true;
	switch(heroLife)
	{
	case 3:
		heroLife--;
		blood3->setVisible(false);
		break;

	case 2:
		heroLife --;
		blood2->setVisible(false);
		break;

	case 1:
		heroLife --;
		blood1->setVisible(false);
		break;

	case 0:
		if(!isOver)
		{
			setGameOver();
			isOver = true;	
		}
		break;
		
	}

}

void GameMain::menuRetryCallBack(CCObject* pSender)
{
	CCDirector::sharedDirector()->replaceScene(GameMain::scene());
}

void GameMain::menuCloseCallBack(CCObject* pSender)
{
	CCDirector::sharedDirector()->replaceScene(GameMenu::scene());
}

void GameMain::setGameOver()
{
	hero->stopAllActions();
	hero->setVisible(false);
	for (int i=0;i<3;i++)
	{
		enemys[i]->stopBullets();
		enemys[i]->setVisible(false);
	}


	gameover->setVisible(true);
	overMenu->setVisible(true);
	gameover->setScale(0);
	overMenu->setScale(0);
	gameover->runAction(CCScaleTo::create(0.5,0.5));
	overMenu->runAction(CCScaleTo::create(0.5,0.8));

}

void GameMain::resetReduce()
{
	isReduce = false;
}