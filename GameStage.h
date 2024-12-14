#pragma once
#ifndef __GAME_STAGE_H__
#define __GAME_STAGE_H__

#define MAX_STAGE 3

enum GameObject
{
	X,
	PLAYERSHOT,
	ENEMY,
	ENEMYSHOT
};

struct StageMgr
{
	int _numOfEnemies;
	int _enemyAlive;
	int _playerLife;
	char _stageData[dfSCREEN_HEIGHT][dfSCREEN_WIDTH];
	int _enemyLocationData[dfSCREEN_HEIGHT][dfSCREEN_WIDTH];
};

extern StageMgr stageMgr;

typedef char* Stage;

#endif