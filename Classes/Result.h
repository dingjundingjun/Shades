#ifndef _Result_H_
#define _Result_H_

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Util.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace gui;

class Result : public cocos2d::CCLayer
{
public:
	Result();
	~Result();
	static CCScene* scene(int levelIndex,int score);
	CREATE_FUNC(Result);
	virtual bool init();  
	void keyBackClicked();
	virtual void onEnter();
private:
	int mBestScore;
	int mCurrentScore;
	int mLevelIndex;
	CCSize mScreenSize;
	UILabel *mBestScoreLabel;
	UILabel *mScoreLabel;
	UILabel *mLevelLabel;
};

#endif