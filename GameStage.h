#pragma once
#ifndef __GAME_STAGE_H__
#define __GAME_STAGE_H__

#define MAX_STAGE 3
#define EMPTY -1


struct StageMgr
{
	int _playerLife;
	int _enemyTotal;
	int _enemyAlive;

	int _enemyLocationData[dfSCREEN_HEIGHT][dfSCREEN_WIDTH] = { -1 }; //�� ��ǥ�� ��ġ�� enemy�� index�� �����ϴ� �迭
	char _stageData[dfSCREEN_HEIGHT][dfSCREEN_WIDTH];
};

extern StageMgr stageMgr;

#endif