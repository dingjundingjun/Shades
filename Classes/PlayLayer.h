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

	/**�����һ������*/
	CCSprite* randOneBlock();
	/**��ʾ��һ������*/
	void showNextBlock(CCSprite* sprite);
	/**���ζ���*/
	void showScaleAnimation();
	/**���鿪ʼ����*/
	void moveNextBlock();
	/**�ж��Ƿ��п��������ķ���*/
	bool hasBlockClean();
	/**�����˶�*/
	void moveBlock();
	/**ֹͣ�����˶�*/
	void stopBlcok(CCSprite *sprite,int x,int y);
	/**��ɫ�ϳ�*/
	bool mergeBlock();
	/**�Ƿ���Ժ����ƶ�*/
	bool canMoveHor(int x,int y);
	/**���źϲ�����*/
	void playMergAnimation(CCSprite *sprite);
	/**�ϳɶ����ص�*/
	void mergeCallBack(CCNode* pSender, void* data);
	/**������������*/
	void playCleanAnimation(int row);
	/**��������huid*/
	void cleanCallBack(CCNode* pSender, void* data);
	/**���·���*/
	void updateScore(int addScore);
	/**�Ƿ���Ϸ����*/
	bool isGameOver();
	/**��ʾ���*/
	void showResult();
private:
	CCSize mScreenSize;
	/**������ɫ*/
	int mColorTypeIndex;
	/**��ǰ���ֵ���ɫ*/
	int mColorIndex;
	/**��һ����ɫ*/
	int mNextColorIndex;
	/**��ǰ��ɫ��λ��*/
	int mPositionIndex;
	/**��һ�·����ֵ �����ǳ����������1,2,4,8,16����ʾ*/
	int mBlockColor;
	/**��Ϸ��������*/
	int mBlockArea[GAME_AREA_WIDTH][GAME_AREA_HEIGHT];
	/**������Ϸ״̬*/
	int mGameStatus;
	/**���������ٶ�*/
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