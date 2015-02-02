#ifndef _UTIL_H_
#define _UTIL_H_

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace gui;
using namespace cocos2d::extension;

/**方块宽度*/
#define BLOCK_WIDTH  80    
/**方块高度*/
#define BLOCK_HEIGHT 40
/**游戏区域的宽度，即宽度有多少个方块*/
#define GAME_AREA_WIDTH 4    //计算方式是width*10 + height
/**游戏区域的高度，即高度有多少个方块*/
#define GAME_AREA_HEIGHT 12
/**方块类型的数量*/
#define GAME_TYPE_NUMBER 5
/**几个相连能消除*/
#define GAME_CLEAN_UP_NUMBER 4
/**方块的数组大小*/
#define BLOCK_ARRAY_SIZE 1
/**每种颜色分为几个色差*/
#define BLOCK_COLOR_DY 5
/***方块为空的标记*/
#define HAS_NO_BLOCK 100
/**游戏区域的左边偏移*/
#define GAME_AREA_P_LEFT 130
/**游戏区域的上边偏移*/
#define GAME_AREA_P_DOWN 650
/**每个钱币的间隔*/
#define MONEY_P 10
/**标记为下一个方块*/
#define BLOCK_NEXT 100
/**标记移动中的方块*/
#define BLOCK_MOVING 101
/**方块移动停止了*/
#define BLOCK_STOP 102
/**游戏等待*/
#define GAME_STATUS_WAIT 1
/**游戏方块下落状态*/
#define GAME_STATUS_BLOCK_MOVING 2
/**方块消除状态*/
#define GAME_STATUS_BLOCK_CLEAN 3
/**游戏的速度*/
#define GAME_SPEED_SIMPLE 5
#define GAME_SPEED_NORMAL 2
#define GAME_SPEED_HARD 3
/**过关步数*/
static int gGameStepsNumber = 0;
/**过关得分*/
static int gGameSuccessScore = 0;
#endif