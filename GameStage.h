#pragma once
#ifndef __GAME_STAGE_H__
#define __GAME_STAGE_H__

#define MAX_STAGE 3

struct StageMgr
{
	int _numOfEnemies;
	int _enemyAlive;
	int _playerLife;
	char _stageData[dfSCREEN_HEIGHT][dfSCREEN_WIDTH];
	//Enemy _e[MAX_ENEMY];

};


extern StageMgr stageMgr;

typedef char* Stage;

#endif