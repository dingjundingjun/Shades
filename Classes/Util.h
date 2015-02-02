#ifndef _UTIL_H_
#define _UTIL_H_

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace gui;
using namespace cocos2d::extension;

/**������*/
#define BLOCK_WIDTH  80    
/**����߶�*/
#define BLOCK_HEIGHT 40
/**��Ϸ����Ŀ�ȣ�������ж��ٸ�����*/
#define GAME_AREA_WIDTH 4    //���㷽ʽ��width*10 + height
/**��Ϸ����ĸ߶ȣ����߶��ж��ٸ�����*/
#define GAME_AREA_HEIGHT 12
/**�������͵�����*/
#define GAME_TYPE_NUMBER 5
/**��������������*/
#define GAME_CLEAN_UP_NUMBER 4
/**����������С*/
#define BLOCK_ARRAY_SIZE 1
/**ÿ����ɫ��Ϊ����ɫ��*/
#define BLOCK_COLOR_DY 5
/***����Ϊ�յı��*/
#define HAS_NO_BLOCK 100
/**��Ϸ��������ƫ��*/
#define GAME_AREA_P_LEFT 130
/**��Ϸ������ϱ�ƫ��*/
#define GAME_AREA_P_DOWN 650
/**ÿ��Ǯ�ҵļ��*/
#define MONEY_P 10
/**���Ϊ��һ������*/
#define BLOCK_NEXT 100
/**����ƶ��еķ���*/
#define BLOCK_MOVING 101
/**�����ƶ�ֹͣ��*/
#define BLOCK_STOP 102
/**��Ϸ�ȴ�*/
#define GAME_STATUS_WAIT 1
/**��Ϸ��������״̬*/
#define GAME_STATUS_BLOCK_MOVING 2
/**��������״̬*/
#define GAME_STATUS_BLOCK_CLEAN 3
/**��Ϸ���ٶ�*/
#define GAME_SPEED_SIMPLE 5
#define GAME_SPEED_NORMAL 2
#define GAME_SPEED_HARD 3
/**���ز���*/
static int gGameStepsNumber = 0;
/**���ص÷�*/
static int gGameSuccessScore = 0;
#endif