#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Util.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace gui;
static int COLOR_ARRAY[BLOCK_ARRAY_SIZE][BLOCK_COLOR_DY][3] = {{{200,232,247},{138,205,238},{47,167,225},{24,119,165},{15,73,102}}};
static int COLOR_DY[5] = {1,2,4,8,16};
class PlayLayer : public cocos2d::CCLayer
{
public:
	PlayLayer();
	~PlayLayer();
	static CCScene* scene(int colorIndex,int levelNum);
	CREATE_FUNC(PlayLayer);
	virtual bool init();  
	virtual void update(float delta);
	void keyBackClicked();
	void initData();
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void registerWithTouchDispatcher(void);
	virtual void onEnter();

	/**随机出一个方块*/
	CCSprite* randOneBlock();
	/**显示下一个方块*/
	void showNextBlock(CCSprite* sprite);
	/**变形动画*/
	void showScaleAnimation();
	/**方块开始下落*/
	void moveNextBlock();
	/**判断是否有可以消除的方块*/
	bool hasBlockClean();
	/**方块运动*/
	void moveBlock();
	/**停止方块运动*/
	void stopBlcok(CCSprite *sprite,int x,int y);
	/**颜色合成*/
	bool mergeBlock();
	/**是否可以横向移动*/
	bool canMoveHor(int x,int y);
	/**播放合并动画*/
	void playMergAnimation(CCSprite *sprite);
	/**合成动画回调*/
	void mergeCallBack(CCNode* pSender, void* data);
	/**播放消除动画*/
	void playCleanAnimation(int row);
	/**消除动画huid*/
	void cleanCallBack(CCNode* pSender, void* data);
	/**更新分数*/
	void updateScore(int addScore);
	/**是否游戏结束*/
	bool isGameOver();
	/**显示结果*/
	void showResult();
private:
	CCSize mScreenSize;
	/**哪种颜色*/
	int mColorTypeIndex;
	/**当前出现的颜色*/
	int mColorIndex;
	/**下一个颜色*/
	int mNextColorIndex;
	/**当前颜色的位置*/
	int mPositionIndex;
	/**下一下方块的值 这里从浅到深依次用1,2,4,8,16来表示*/
	int mBlockColor;
	/**游戏区域数组*/
	int mBlockArea[GAME_AREA_WIDTH][GAME_AREA_HEIGHT];
	/**控制游戏状态*/
	int mGameStatus;
	/**方块下落速度*/
	int mSpeed;
	int mTimes;
	int mLevel;
	int mCleanTag;
	int mScore;
	UILabel *mLevelLabel;
	UILabel *mScoreLabel;
	int mBaseLevel;

};

#endif