#pragma once
#ifndef __GAME_STAGE_H__
#define __GAME_STAGE_H__

#define MAX_STAGE 3

struct StageMgr
{
	char stageData[dfSCREEN_HEIGHT][dfSCREEN_WIDTH];
	//Enemy _e[MAX_ENEMY];
	int _iEnemyAlive;
	int _iPlayerLife;
};


extern StageMgr stageMgr;

typedef char* Stage;

#endif