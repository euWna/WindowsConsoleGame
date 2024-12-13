#include <windows.h>

#include "ScreenSetting.h"
#include "Buffer.h"
#include "Console.h"
#include "Player.h"
#include "MovePattern.h"
#include "Enemy.h"
#include "Scene.h"
#include "GameStage.h"


StageMgr stageMgr;

extern DWORD t_Standard;

int processFrame()
{
	int eIdx;
	int esIdx;
	int psIdx;

	/*입력*/
	//Player 조작키 입력
	int inputKey = cs_GetKeyInput();


	/*로직*/
	//1. 오브젝트 이동
	///Player 이동 또는 발사
	player_Control(inputKey);

	//PlayerShot 발사 및 이동
	for (psIdx = 0; psIdx < MAX_PLAYER_SHOT; psIdx++)
	{
		if (!playerShot[psIdx].isVisible) continue;
		else playerShot[psIdx]._yPos--;
	}

	///Enemy 이동
	for (eIdx = 0; eIdx < stageMgr._numOfEnemies; eIdx++)
	{
		if (enemy[eIdx]._isDead) continue;
		else enemy_Move(eIdx);
	}

	///EnemyShot 발사 및 이동
	for (eIdx = 0; eIdx < stageMgr._numOfEnemies; eIdx++)
	{
		if (t_Standard % (enemy[eIdx]._shotCoolTime * 1000) == 0)
			enemy_Shoot(eIdx);
	}
	for (esIdx = 0; esIdx < MAX_ENEMY_SHOT; esIdx++)
	{
		if (!enemyShot[esIdx].isVisible) continue;
		else enemyShot_Move(esIdx);
	}


	//2. 충돌 처리 및 게임 클리어/오버 판단
	///Player & Enemy 충돌 여부 (= 게임 오버 여부) 판정
	for (eIdx = 0; eIdx < stageMgr._numOfEnemies; eIdx++)
	{
		if (enemy[eIdx]._isDead) continue;

		if (enemy[eIdx]._xPos == player._xPos
			&& enemy[eIdx]._yPos == player._yPos)
		{
			return RES_FAIL;
		}
	}

	///Player & EnemyShot 충돌 & 게임 오버 판정
	for (esIdx = 0; esIdx < MAX_ENEMY_SHOT; esIdx++)
	{
		if (!enemyShot[esIdx].isVisible) continue;

		if (enemyShot[esIdx]._xPos == player._xPos
			&& enemy[eIdx]._yPos == player._yPos)
		{
			stageMgr._playerLife--;
			if (stageMgr._playerLife <= 0)
				return RES_FAIL;
		}
	}

	///Enemy & PlayerShot 충돌 여부 & 게임 클리어 판정
	for (psIdx = 0; psIdx < MAX_PLAYER_SHOT; psIdx++)
	{
		PlayerShot* ps = &playerShot[psIdx];
		int shotEnemyIdx;

		if (stageMgr._enemyLocationData[ps->_yPos][ps->_xPos] < MAX_ENEMY)
		{
			shotEnemyIdx = stageMgr._enemyLocationData[ps->_yPos][ps->_xPos];
			enemy_GetShot(shotEnemyIdx);
			if (stageMgr._enemyAlive <= 0)
				return RES_CLEAR;
		}
	}


	/*출력*/
	//enemy shot
	for (esIdx = 0; esIdx < MAX_ENEMY_SHOT; esIdx++)
	{
		if (!enemyShot[esIdx].isVisible) continue;

		buffer_DrawSprite(enemyShot[esIdx]._xPos, enemyShot[esIdx]._yPos, enemySetting._shotSprite);
	}

	//player shot
	for (psIdx = 0; psIdx < MAX_PLAYER_SHOT; psIdx++)
	{
		if (!playerShot[psIdx].isVisible) continue;
		
		buffer_DrawSprite(playerShot[psIdx]._xPos, playerShot[psIdx]._yPos, playerSetting._shotSprite);
	}

	//enemy
	for (eIdx = 0; eIdx < stageMgr._numOfEnemies; eIdx++)
	{
		if (enemy[eIdx]._isDead) continue;

		buffer_DrawSprite(enemy[eIdx]._xPos, enemy[eIdx]._yPos, enemy[eIdx]._sprite);
	}

	//player
	buffer_DrawSprite(player._xPos, player._yPos, playerSetting._sprite);

	return PLAY;

}

//플레이어

extern SceneType currentScene;
extern int currentStage;
extern void parseData_Stage(int stageNum);
void game_SetGameObjectsOnStage();

enum StageSetting
{
	Init,
	ParseStageData,
	InitGameObjects,
	SetGameObjectsOnStage,
	Finish
};

void game_InitStage()
{
	static int nowSetting = Init;

	switch (nowSetting)
	{
	case Init:
		break;

	case ParseStageData:
		parseData_Stage(currentStage);
		break;

	case InitGameObjects:
		///오브젝트 배열 0으로 초기화
		memset(enemy, 0, sizeof(enemy));
		memset(playerShot, 0, sizeof(playerShot));
		memset(enemyShot, 0, sizeof(enemyShot));

		///stage 변수 초기화
		stageMgr._enemyAlive = stageMgr._numOfEnemies;
		stageMgr._playerLife = playerSetting._maxLife;
		eShotCnt = 0;
		pShotCnt = 0;
		break;

	case SetGameObjectsOnStage:
		game_SetGameObjectsOnStage();
		break;

	case Finish:
		buffer_UpdateScene(stageMgr._stageData);
		scene_ConvertTo(PLAY);
		nowSetting = Init;
		break;

	default:
		return;
	}
	nowSetting++;
}



void game_SetGameObjectsOnStage()
{
	char* c;

	int eTypeNum;
	int eCnt = 0;
	Enemy* e = &(enemy[eCnt]);

	for (int y = 0; y < 24; y++)
	{
		for (int x = 0; x < dfSCREEN_WIDTH; x++)
		{
			c = &(stageMgr._stageData[y][x]);

			//Void
			if (*c == '.' || *c == '|' || *c == '*')
			{
				stageMgr._stageData[y][x] = ' ';
			}
			//Player
			else if (*c == '0')
			{
				stageMgr._stageData[y][x] = playerSetting._sprite;
				player._xPos = x;
				player._yPos = y;
			}
			else if (*c == '\0')
			{
				continue;
			}
			//Enemy
			else
			{
				stageMgr._enemyLocationData[y][x] = eCnt;
				eTypeNum = *c - '0';
				e->_xPos = x;
				e->_yPos = y;
				e->_life = EnemyType_Table[eTypeNum]._maxLife;
				e->_shotCoolTime = EnemyType_Table[eTypeNum]._shotCoolTime;
				e->_movePattern._type = &MovePattern_Table[EnemyType_Table[eTypeNum]._movePatternTypeNum];
				e->_sprite = *c;

				e = &(enemy[++eCnt]);
			}
		}
	}
}

bool game_CheckVisible()
{

}


void game_CheckEnemyAlive()
{

}

void game_CheckPlayerLife()
{

}

void game_ShiftStage()
{

}


