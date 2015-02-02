#include "Menu.h"
#include "PlayLayer.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace gui;

CCScene* Menu::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	Menu *layer = Menu::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

Menu::Menu()
{

}

Menu::~Menu()
{

}

bool Menu::init()
{
	colorType = 0;
	mLevel = GAME_SPEED_SIMPLE;
	mScreenSize = CCDirector::sharedDirector()->getWinSize();
	setTouchEnabled( true );
	this->setKeypadEnabled(true);

	mStartGame = UILabel::create();
	mStartGame->setFontSize(20);
	//char str[50] = {0};
	//sprintf(str,"the socre is:%d",mCurrentScore);
	//mStartGame->setContentSize(ccp(100,50));
	mStartGame->setText("start game");
	mStartGame->setPosition(ccp(mScreenSize.width/2,mScreenSize.height/2 + mStartGame->getContentSize().height));
	
	mGameSimple = UILabel::create();
	mGameSimple->setFontSize(20);
	//char str[50] = {0};
	//sprintf(str,"the socre is:%d",mCurrentScore);
	mGameSimple->setText("simple");
	mGameSimple->setPosition(ccp(50,100));

	mGameNormal = UILabel::create();
	mGameNormal->setFontSize(20);
	//char str[50] = {0};
	//sprintf(str,"the socre is:%d",mCurrentScore);
	mGameNormal->setText("normal");
	mGameNormal->setPosition(ccp(180,100));

	mGameHard = UILabel::create();
	mGameHard->setFontSize(20);
	//char str[50] = {0};
	//sprintf(str,"the socre is:%d",mCurrentScore);
	mGameHard->setText("hard");
	mGameHard->setPosition(ccp(260,100));

	mLevelInfo = UILabel::create();
	mLevelInfo->setFontSize(20);
	//char str[50] = {0};
	//sprintf(str,"the socre is:%d",mCurrentScore);
	mLevelInfo->setPosition(ccp(mScreenSize.width/2,150));

	mColorSprite = CCSprite::create("start_game.png");
	mColorSprite->setPosition(ccp(mScreenSize.width/2,mScreenSize.height/2 + mStartGame->getContentSize().height));
	int r = COLOR_ARRAY[colorType][1][0];
	int g = COLOR_ARRAY[colorType][1][1];
	int b = COLOR_ARRAY[colorType][1][2];
	ccColor3B color;
	color.r = r;
	color.g = g;
	color.b = b;
	mColorSprite->setColor(color);
	addChild(mColorSprite,50);
	addChild(mGameSimple,100);
	addChild(mStartGame,100);
	addChild(mGameNormal,100);
	addChild(mGameHard,100);
	addChild(mLevelInfo,100);
	updateLevelInfo();
	return true;
}

void Menu::keyBackClicked()
{
	CCDirector::sharedDirector()->end();
}

bool Menu::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	return true;
}

void Menu::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{

}

void Menu::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	CCPoint point = pTouch->getLocation();
	if(mColorSprite->boundingBox().containsPoint(point))
	{
		CCScene *playScene = PlayLayer::scene(0,mLevel);
		CCDirector::sharedDirector()->replaceScene(playScene);
	}
	else if(mGameSimple->boundingBox().containsPoint(point))
	{
		mLevel = GAME_SPEED_SIMPLE;
	}
	else if(mGameNormal->boundingBox().containsPoint(point))
	{
		mLevel = GAME_SPEED_NORMAL;
	}
	else if(mGameHard->boundingBox().containsPoint(point))
	{
		mLevel = GAME_SPEED_HARD;
	}
}

void Menu::updateLevelInfo()
{
	int score = 0;
	char str[50] = {0};
	if(mLevel == GAME_SPEED_SIMPLE)
	{
		score  = CCUserDefault::sharedUserDefault()->getIntegerForKey("simple_bestScore",0);
	}
	else if(mLevel == GAME_SPEED_NORMAL)
	{
		score  = CCUserDefault::sharedUserDefault()->getIntegerForKey("normal_bestScore",0);
	}
	else if(mLevel == GAME_SPEED_HARD)
	{
		score  = CCUserDefault::sharedUserDefault()->getIntegerForKey("normal_bestScore",0);
	}
	sprintf(str,"the best score is:%d",score);
	mLevelInfo->setText(str);
}

void Menu::registerWithTouchDispatcher(void)
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,false);
}
