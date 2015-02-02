#include "PlayLayer.h"
#include "Result.h"
#include "Menu.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace gui;

CCScene* PlayLayer::scene(int colorIndex,int levelNum)
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	PlayLayer *layer = PlayLayer::create();
	layer->mBaseLevel = levelNum;
	layer->mColorTypeIndex = colorIndex;
	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

PlayLayer::PlayLayer()
{

}

PlayLayer::~PlayLayer()
{

}

void PlayLayer::onEnter()
{
	CCLayer::onEnter();
	//mColorTypeIndex = 0;    //这个是暂时的
	showNextBlock(randOneBlock());
	showScaleAnimation();
}

void PlayLayer::initData()
{
	for (int i = 0;i < GAME_AREA_WIDTH;i++)
	{
		for(int j = 0;j < GAME_AREA_HEIGHT;j++)
		{
			mBlockArea[i][j] = 0;
		}
	}
}

bool PlayLayer::init()
{
	mScore = 0;
	mCleanTag = 0;
	mTimes = 0;
	mLevel = 1;
	mSpeed = GAME_SPEED_SIMPLE;
	mGameStatus = GAME_STATUS_WAIT;
	mScreenSize = CCDirector::sharedDirector()->getWinSize();
	setTouchEnabled( true );
	this->setKeypadEnabled(true);
	std::srand((unsigned int)time(0));
	scheduleUpdate();
	mLevelLabel = UILabel::create();
	mLevelLabel->setFontSize(25);
	mLevelLabel->setAnchorPoint(ccp(0,0));
	mLevelLabel->setText("level:1");
	mLevelLabel->setPosition(ccp(0,mScreenSize.height - mLevelLabel->getContentSize().height));
	addChild(mLevelLabel,100);

	mScoreLabel = UILabel::create();
	mScoreLabel->setFontSize(25);
	mScoreLabel->setAnchorPoint(ccp(0.5,0));
	mScoreLabel->setText("0");
	mScoreLabel->setPosition(ccp(mScreenSize.width/2,mScreenSize.height - mScoreLabel->getContentSize().height));
	addChild(mScoreLabel,100);

	initData();
	//showNextBlock(randOneBlock());
	//showScaleAnimation();
	return true;
}

void PlayLayer::showNextBlock(CCSprite* sprite)
{
	//sprite->setContentSize(CCSize(mScreenSize.width,BLOCK_HEIGHT));
	float anchor = mPositionIndex/4.0;
	sprite->setAnchorPoint(ccp(0,0));
	sprite->setPosition(ccp(0,mScreenSize.height - BLOCK_HEIGHT/2));
	this->addChild(sprite);
}

void PlayLayer::showScaleAnimation()
{
	CCSprite* sprite = (CCSprite*)this->getChildByTag(BLOCK_NEXT);
	CCActionInterval *scaleAction = CCScaleTo::create(0.5,0.25,1);
	CCActionInterval *moveAction = CCMoveBy::create(0.5,CCPoint(mPositionIndex * BLOCK_WIDTH,0));
	CCSpawn *spawn = CCSpawn::create(scaleAction,moveAction,NULL);
	CCActionInterval *seque = CCSequence::create(spawn,CCDelayTime::create(0.5),CCCallFunc::create(this,callfunc_selector(PlayLayer::moveNextBlock)),NULL);
	sprite->runAction(seque);
}

void PlayLayer::moveNextBlock()
{
	if(mGameStatus == GAME_STATUS_BLOCK_MOVING)
	{

	}
	else
	{
		mGameStatus = GAME_STATUS_BLOCK_MOVING;
		CCSprite *sprite = (CCSprite*)this->getChildByTag(BLOCK_NEXT);
		sprite->setTag(BLOCK_MOVING);
	}
}

CCSprite* PlayLayer::randOneBlock()
{
	mNextColorIndex = rand() % BLOCK_COLOR_DY;
	mPositionIndex = rand() % GAME_AREA_WIDTH;
	
	int r = COLOR_ARRAY[mColorTypeIndex][mNextColorIndex][0];
	int g = COLOR_ARRAY[mColorTypeIndex][mNextColorIndex][1];
	int b = COLOR_ARRAY[mColorTypeIndex][mNextColorIndex][2];
	CCSprite* sprite = CCSprite::create("block.png");
	sprite->setUserData((void*)mNextColorIndex);
	sprite->setTag(BLOCK_NEXT);
	ccColor3B color;
	color.r = r;
	color.g = g;
	color.b = b;
	sprite->setColor(color);
	return sprite;
}

bool PlayLayer::hasBlockClean()
{
	for(int j = 0;j < GAME_AREA_HEIGHT;j++ )
	{
		int temp = mBlockArea[0][j];
		bool bClean = true;
		for(int i = 0;i < GAME_AREA_WIDTH;i++)
		{
			if(mBlockArea[i][j] != temp || temp == 0)
			{
				bClean = false;
			}
		}
		if(bClean)
		{
			playCleanAnimation(j);
			return true;
		}
	}
	return false;
}

void PlayLayer::playCleanAnimation(int row)
{
	//消除row这一行
	for(int i = 0;i < GAME_AREA_WIDTH;i++)
	{
		this->removeChildByTag(row*10 + i + 1000);
	}
	bool temp = true;
	mCleanTag = 0;
	for(int p = row+1;p < GAME_AREA_HEIGHT;p++)    //每个都下移动一格
	{
		for(int m = 0;m < GAME_AREA_WIDTH;m++)
		{
			if(mBlockArea[m][p] != 0)
			{
				mCleanTag++;
			}
		}
	}
	for(int p = row+1;p < GAME_AREA_HEIGHT;p++)    //每个都下移动一格
	{
		for(int m = 0;m < GAME_AREA_WIDTH;m++)
		{
			if(mBlockArea[m][p] != 0)
			{
				temp = false;
				CCSprite *sprite = (CCSprite*)this->getChildByTag(p*10 + m + 1000);
				sprite->setTag((p-1)*10 + m + 1000);
				CCActionInterval *moveAction = CCMoveBy::create(0.5,CCPoint(0,-1 * BLOCK_HEIGHT));
				//CCSpawn *spawn = CCSpawn::create(scaleAction,moveAction,NULL);
				CCActionInterval *seque = CCSequence::create(moveAction,CCCallFuncND::create(this,callfuncND_selector(PlayLayer::cleanCallBack),(void*)p),NULL);
				sprite->runAction(seque);
				
			}
		}
	}
	if(temp)
	{
		for(int p = row;p < GAME_AREA_HEIGHT;p++)
		{
			for(int m = 0;m < GAME_AREA_WIDTH;m++)
			{
				if(p < GAME_AREA_HEIGHT - 1)
				{
					mBlockArea[m][p] = mBlockArea[m][p+1];
				}
				else
					mBlockArea[m][p] = 0;
			}
		}
		updateScore(200);
		mGameStatus = GAME_STATUS_WAIT;
		showNextBlock(randOneBlock());
		showScaleAnimation();
	}
}

void PlayLayer::cleanCallBack(CCNode* pSender, void* data)
{
	mCleanTag--;
	if(mCleanTag == 0)
	{
		int row = (int)data - 1;
		for(int p = row;p < GAME_AREA_HEIGHT;p++)
		{
			for(int m = 0;m < GAME_AREA_WIDTH;m++)
			{
				if(p < GAME_AREA_HEIGHT - 1)
				{
					mBlockArea[m][p] = mBlockArea[m][p+1];
				}
				else
					mBlockArea[m][p] = 0;
			}
		}
		updateScore(200);
		mGameStatus = GAME_STATUS_WAIT;
		showNextBlock(randOneBlock());
		showScaleAnimation();
	}
	
}

void PlayLayer::update(float delta)
{
	if(mGameStatus == GAME_STATUS_BLOCK_MOVING)
	{
		moveBlock();
	}
	
}

bool PlayLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	return true;
}

void PlayLayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{

}

void PlayLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	if(mGameStatus == GAME_STATUS_BLOCK_MOVING)
	{
		CCLOG("ccTouchEnded");
		CCPoint point = pTouch->getLocation();
		int x = point.x / BLOCK_WIDTH;
		int y = point.y / BLOCK_HEIGHT;
		canMoveHor(x,y);
	}
}

bool PlayLayer::canMoveHor(int x,int y)
{
	{
		CCSprite *sprite = (CCSprite*)this->getChildByTag(BLOCK_MOVING);
		CCPoint position = sprite->getPosition();
		int moveX = position.x / BLOCK_WIDTH;
		int moveY = position.y / BLOCK_HEIGHT;
		if(x > moveX)
		{
			bool temp = true;
			for(int i = moveX+1;i <= x;i++)
			{
				if(mBlockArea[i][moveY] != 0)
				{
					temp = false;
				}
			}
			if(temp)
			{
				position.x = x*BLOCK_WIDTH;
				sprite->setPosition(position);
				return true;
			}
		}
		else if(x < moveX)
		{
			bool temp = true;
			for(int i = x;i < moveX;i++)
			{
				if(mBlockArea[i][moveY] != 0)
				{
					temp = false;
				}
			}
			if(temp)
			{
				position.x = x*BLOCK_WIDTH;
				sprite->setPosition(position);
				return true;
			}
		}
	}
	return false;
}

void PlayLayer::registerWithTouchDispatcher(void)
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,false);
}

void PlayLayer::moveBlock()
{
	mTimes++;
	CCSprite *sprite = (CCSprite*)this->getChildByTag(BLOCK_MOVING);
	CCPoint position = sprite->getPosition();
	//获取当前的数组位置
	if(position.y < 0)
	{
		position.y = 0;
	}
	int x = position.x / BLOCK_WIDTH;
	int y = position.y / BLOCK_HEIGHT;
	if(y > 0)
	{
		if(mBlockArea[x][y-1] != 0)    //下面有方块了
		{
			//CCLOG("pY = %f,y = %d",position.y,y);
			position.y -= mSpeed;//BLOCK_HEIGHT/20;
			if(position.y < y*BLOCK_HEIGHT)
			{
				position.y = y*BLOCK_HEIGHT;
				sprite->setPosition(position);
				mBlockArea[x][y] = COLOR_DY[mNextColorIndex];
				stopBlcok(sprite,x,y);
				updateScore(2);
				return;
			}
			sprite->setPosition(position);
		}
		else
		{
			position.y -= mSpeed;//BLOCK_HEIGHT/20;
			sprite->setPosition(position);
		}
	}
	else
	{
		position.y -= mSpeed;//BLOCK_HEIGHT/20;
		if(position.y <= 0)
		{
			position.y = 0;
			sprite->setPosition(position);
			mBlockArea[x][y] = COLOR_DY[mNextColorIndex];
			stopBlcok(sprite,x,y);
			updateScore(2);
			return;
		}
		sprite->setPosition(position);
	}
}

void PlayLayer::updateScore(int addScore)
{
	mScore += addScore;
	mLevel = (mScore/500)+1;
	mSpeed = mSpeed + (mScore/500)*0.5;
	char str[10] = {0};
	sprintf(str,"level:%d",mLevel);
	mLevelLabel->setText(str);
	memset(str,0,10);
	sprintf(str,"%d",mScore);
	mScoreLabel->setText(str);
}

bool PlayLayer::mergeBlock()
{
	for(int i = 0;i < GAME_AREA_WIDTH;i++)
	{
		for(int j = GAME_AREA_HEIGHT - 1;j >=0;j--)
		{
			if(mBlockArea[i][j] != 0 && j > 0)
			{
				if(mBlockArea[i][j] == mBlockArea[i][j-1] && mBlockArea[i][j-1] != COLOR_DY[4])    //可以merge
				{
					mBlockArea[i][j-1] *= 2;
					mBlockArea[i][j] = 0;
					int tagMerge = (j-1)*10 + i + 1000;
					int tagRemove = j*10 + i + 1000;
					
					CCSprite* spriete = (CCSprite*)this->getChildByTag(tagMerge);
					CCSprite* spriteRemove = (CCSprite*)this->getChildByTag(tagRemove);
					playMergAnimation(spriteRemove);
					updateScore(4);
					return true;
				}
			}
		}
	}
	return false;
}

void PlayLayer::playMergAnimation(CCSprite *sprite)
{
	CCActionInterval *moveAction = CCMoveBy::create(0.3,CCPoint(0,-1 * BLOCK_HEIGHT));
	//CCSpawn *spawn = CCSpawn::create(scaleAction,moveAction,NULL);
	CCActionInterval *seque = CCSequence::create(/*CCDelayTime::create(0.2),*/moveAction,CCCallFuncND::create(this,callfuncND_selector(PlayLayer::mergeCallBack),(void*)sprite),NULL);
	sprite->runAction(seque);
}

void PlayLayer::mergeCallBack(CCNode* pSender, void* data)
{
	CCSprite *sprite = (CCSprite*)data;
	int tagRemove = sprite->getTag();
	int tagMerge = tagRemove - 10;
	CCSprite* spriete = (CCSprite*)this->getChildByTag(tagMerge);
	int colorIndex = (int)sprite->getUserData();
	colorIndex++;
	ccColor3B color;
	color.r = COLOR_ARRAY[mColorTypeIndex][colorIndex][0];
	color.g = COLOR_ARRAY[mColorTypeIndex][colorIndex][1];
	color.b = COLOR_ARRAY[mColorTypeIndex][colorIndex][2];
	spriete->setColor(color);
	spriete->setUserData((void*)colorIndex);
	this->removeChildByTag(tagRemove);
	if(!mergeBlock())
	{
		if(!hasBlockClean())
		{
			mGameStatus = GAME_STATUS_WAIT;
			showNextBlock(randOneBlock());
			showScaleAnimation();
		}

	}
}

bool PlayLayer::isGameOver()
{
	for(int i = 0;i < GAME_AREA_WIDTH;i++)
	{
		if(mBlockArea[i][GAME_AREA_HEIGHT-1] != 0)
		{
			return true;
		}
	}
	return false;
}

void PlayLayer::showResult()
{
	CCLOG("game is over");
	CCScene *resultScene = Result::scene(mBaseLevel,mScore);
	CCDirector::sharedDirector()->replaceScene(resultScene);
}

void PlayLayer::stopBlcok(CCSprite *sprite,int x,int y)
{
	mGameStatus = GAME_STATUS_BLOCK_CLEAN;
	sprite->setTag(y*10 + x + 1000);
	if(mergeBlock() )    //颜色消除
	{
		
	}
	else if(hasBlockClean())    //block合成
	{
	
	}
	else if(isGameOver())
	{
		showResult();
	}
	else
	{
		mGameStatus = GAME_STATUS_WAIT;
		showNextBlock(randOneBlock());
		showScaleAnimation();
	}
}

void PlayLayer::keyBackClicked()
{
	CCScene *scene = Menu::scene();
	CCDirector::sharedDirector()->replaceScene(scene);
}

