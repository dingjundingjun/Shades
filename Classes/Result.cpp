#include "Result.h"
#include "Menu.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace gui;

CCScene* Result::scene(int levelIndex,int currentScore)
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	Result *layer = Result::create();
	layer->mCurrentScore = currentScore;
	layer->mLevelIndex = levelIndex;
	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

Result::Result()
{

}

Result::~Result()
{

}

void Result::onEnter()
{
	mLevelLabel = UILabel::create();
	mLevelLabel->setFontSize(25);
	mLevelLabel->setPosition(ccp(mScreenSize.width/2,mScreenSize.height - mLevelLabel->getContentSize().height));
	addChild(mLevelLabel,100);

	if(mLevelIndex == GAME_SPEED_SIMPLE)
	{
		mLevelLabel->setText("simple");
		mBestScore  = CCUserDefault::sharedUserDefault()->getIntegerForKey("simple_bestScore",0);
		if(mBestScore < mCurrentScore)
		{
			mBestScore = mCurrentScore;
			CCUserDefault::sharedUserDefault()->setIntegerForKey("simple_bestScore", mBestScore);
			CCUserDefault::sharedUserDefault()->flush();
		}
	}
	else if(mLevelIndex == GAME_SPEED_NORMAL)
	{
		mLevelLabel->setText("normal");
		mBestScore  = CCUserDefault::sharedUserDefault()->getIntegerForKey("normal_bestScore",0);
		if(mBestScore < mCurrentScore)
		{
			mBestScore = mCurrentScore;
			CCUserDefault::sharedUserDefault()->setIntegerForKey("normal_bestScore", mBestScore);
			CCUserDefault::sharedUserDefault()->flush();
		}
	}
	else if(mLevelIndex == GAME_SPEED_HARD)
	{
		mLevelLabel->setText("hard");
		mBestScore  = CCUserDefault::sharedUserDefault()->getIntegerForKey("hard_bestScore",0);
		if(mBestScore < mCurrentScore)
		{
			mBestScore = mCurrentScore;
			CCUserDefault::sharedUserDefault()->setIntegerForKey("hard_bestScore", mBestScore);
			CCUserDefault::sharedUserDefault()->flush();
		}
	}
	mScoreLabel = UILabel::create();
	mScoreLabel->setFontSize(25);
	char str[50] = {0};
	sprintf(str,"the socre is:%d",mCurrentScore);
	mScoreLabel->setText(str);
	mScoreLabel->setPosition(ccp(mScreenSize.width/2,mScreenSize.height/2 + mScoreLabel->getContentSize().height));
	addChild(mScoreLabel,100);

	mBestScoreLabel = UILabel::create();
	mBestScoreLabel->setFontSize(25);
	memset(str,0,50);
	sprintf(str,"the best socre is:%d",mBestScore);
	mBestScoreLabel->setText(str);
	mBestScoreLabel->setPosition(ccp(mScreenSize.width/2,mScreenSize.height/2 - mBestScoreLabel->getContentSize().height));
	addChild(mBestScoreLabel,100);
}

bool Result::init()
{
	mScreenSize = CCDirector::sharedDirector()->getWinSize();
	setTouchEnabled( true );
	this->setKeypadEnabled(true);
	/*
	mLevelLabel = UILabel::create();
	mLevelLabel->setFontSize(25);
	mLevelLabel->setAnchorPoint(ccp(0,0));
	mLevelLabel->setText("level:1");
	mLevelLabel->setPosition(ccp(0,mScreenSize.height - mLevelLabel->getContentSize().height));
	addChild(mLevelLabel,100);
	*/
	return true;
}

void Result::keyBackClicked()
{
	CCScene *scene = Menu::scene();
	CCDirector::sharedDirector()->replaceScene(scene);
}
