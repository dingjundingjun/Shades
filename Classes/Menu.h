#ifndef _MENU_H_
#define _MENU_H_

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Util.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace gui;

class Menu : public cocos2d::CCLayer
{
public:
	Menu();
	~Menu();
	static CCScene* scene();
	CREATE_FUNC(Menu);
	virtual bool init();  
	void keyBackClicked();
	virtual void registerWithTouchDispatcher(void);
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

	void updateLevelInfo();
private:
	//CCSprite *mStartGame;
	int mLevel;
	CCSize mScreenSize;
	CCSprite *mColorSprite;
	UILabel *mStartGame;
	UILabel *mGameSimple;
	UILabel *mGameNormal;
	UILabel *mGameHard;
	UILabel *mLevelInfo;
	int colorType;
};

#endif