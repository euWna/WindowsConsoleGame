#include <windows.h>

#include "Buffer.h"
#include "Console.h"
#include "Player.h"
#include "MovePattern.h"
#include "Enemy.h"
#include "Scene.h"
#include "GameStage.h"

StageMgr stageMgr;
int currentStage;

Player player;

PlayerShot playerShot[MAX_PLAYER_SHOT];
Enemy enemy[MAX_ENEMY];
EnemyShot enemyShot[MAX_ENEMY_SHOT];

int pShotCnt;
int eShotCnt;

extern DWORD t_Standard; //enemyShot 발사 쿨타임 계산용

//로직
//1. Player 제어
//2. 오브젝트 이동
//3. 오브젝트간 충돌 처리 및 게임 클리어/오버 판단
SceneType processFrame(SHORT inputKey)
{
	//게임 오브젝트 배열 인덱스
	int psIdx;
	int eIdx;
	int esIdx;

	//1. Player 제어
	switch (inputKey)
	{
	///PlayerShot 발사
	case VK_SPACE:
		if (pShotCnt < MAX_PLAYER_SHOT)
		{
			psIdx = 0;
			while (playerShot[psIdx]._isShot) psIdx++;
			player_Shoot(&playerShot[psIdx]);
			pShotCnt++;
		}
		break;

	///Player 이동
	case VK_LEFT:
		//[[fallthrough]]
	case VK_UP:
		//[[fallthrough]]
	case VK_RIGHT:
		//[[fallthrough]]
	case VK_DOWN:
		player_Move(inputKey);
		break;

	default:
		break;
	}

	//2. 오브젝트 이동
	///PlayerShot 이동
	for (psIdx = 0; psIdx < MAX_PLAYER_SHOT; psIdx++)
	{
		if (playerShot[psIdx]._isShot == false) continue;
		else
		{
			if (playerShot_Move(&playerShot[psIdx]) == false)
			{
 				pShotCnt--;
			}
		}
	}

	///Enemy 이동
	for (eIdx = 0; eIdx < stageMgr._enemyTotal; eIdx++)
	{
		if (enemy[eIdx]._isDead) continue;
		else
		{
			stageMgr._enemyLocationData[enemy[eIdx]._yPos][enemy[eIdx]._xPos] = EMPTY;
			enemy_Move(&enemy[eIdx]);
			stageMgr._enemyLocationData[enemy[eIdx]._yPos][enemy[eIdx]._xPos] = eIdx;
		}
	}

	///Enemy 발사
	if (eShotCnt < MAX_ENEMY_SHOT)
	{
		for (eIdx = 0; eIdx < stageMgr._enemyTotal; eIdx++)
		{
			if (enemy[eIdx]._isDead) continue;
			if (t_Standard % (enemy[eIdx]._shotCoolTime * 1000) == 0)
			{
				esIdx = 0;
				while (enemyShot[esIdx]._isShot) esIdx++;
				enemy_Shoot(&enemy[eIdx], &enemyShot[esIdx]);
				eShotCnt++;
			}
		}
	}

	///EnemyShot 이동
	for (esIdx = 0; esIdx < MAX_ENEMY_SHOT; esIdx++)
	{
		if (enemyShot[esIdx]._isShot == false) continue;
		else
		{
			if (enemyShot_Move(&enemyShot[esIdx]) == false)
			{
				eShotCnt--;
			}
		}
			
	}


	//3. 충돌 처리 및 게임 클리어/오버 판단
	///Player & Enemy 충돌 여부 (= 게임 오버 여부) 판정
	for (eIdx = 0; eIdx < stageMgr._enemyTotal; eIdx++)
	{
		if (enemy[eIdx]._isDead) continue;

		if (enemy[eIdx]._xPos == player._xPos
			&& enemy[eIdx]._yPos == player._yPos)
		{
			return GAME_OVER;
		}
	}

	///Player & EnemyShot 충돌 & 게임 오버 판정
	for (esIdx = 0; esIdx < MAX_ENEMY_SHOT; esIdx++)
	{
		if (enemyShot[esIdx]._isShot == false) continue;

		if (enemyShot[esIdx]._xPos == player._xPos
			&& enemyShot[esIdx]._yPos == player._yPos)
		{
			stageMgr._playerLife--;
			enemyShot[esIdx]._isShot = false;
			eShotCnt--;

			if (stageMgr._playerLife == 0)
				return GAME_OVER;
		}
	}

	///Enemy & PlayerShot 충돌 여부 & 게임 클리어 판정
	for (psIdx = 0; psIdx < MAX_PLAYER_SHOT; psIdx++)
	{
		if (playerShot[psIdx]._isShot == false) continue;
		PlayerShot* ps = &playerShot[psIdx];
		int shotEnemyIdx;

		if (stageMgr._enemyLocationData[ps->_yPos][ps->_xPos] != EMPTY)
		{
			ps->_isShot = false;
			pShotCnt--;

			shotEnemyIdx = stageMgr._enemyLocationData[ps->_yPos][ps->_xPos];
			bool eIsDead = enemy_GetShot(&enemy[shotEnemyIdx]);
			if (eIsDead)
			{
				stageMgr._enemyAlive--;
				stageMgr._enemyLocationData[enemy[shotEnemyIdx]._yPos][enemy[shotEnemyIdx]._xPos] = EMPTY;
			}

			if (stageMgr._enemyAlive == 0) 
 				return STAGE_CLEAR;
		}
	}


	/*출력*/
	//enemy shot
	for (esIdx = 0; esIdx < MAX_ENEMY_SHOT; esIdx++)
	{
		if (enemyShot[esIdx]._isShot == false) continue;

		buffer_DrawSprite(enemyShot[esIdx]._xPos, enemyShot[esIdx]._yPos, enemySetting._shotSprite);
	}

	//enemy
	for (eIdx = 0; eIdx < stageMgr._enemyTotal; eIdx++)
	{
		if (enemy[eIdx]._isDead) continue;

		buffer_DrawSprite(enemy[eIdx]._xPos, enemy[eIdx]._yPos, enemy[eIdx]._sprite);
	}

	//player shot
	for (psIdx = 0; psIdx < MAX_PLAYER_SHOT; psIdx++)
	{
		if (playerShot[psIdx]._isShot == false) continue;
		
		buffer_DrawSprite(playerShot[psIdx]._xPos, playerShot[psIdx]._yPos, playerSetting._shotSprite);
	}

	//player
	buffer_DrawSprite(player._xPos, player._yPos, playerSetting._sprite);

	return PLAY;
}


enum StageSetting
{
	Init,
	InitGameObjects,
	ParseStageData,
	ParseScreen,
	InitStageMgr,
	Finish
};

void stage_InitGameObjects();
extern void parseData_Stage(int stageNum);
void stage_ParseScreen();
void stage_InitStageMgr();

void stage_InitStage()
{
	static int nowSetting = Init;

	switch (nowSetting)
	{
	case Init:
		nowSetting++;
		//[[fallthrough]]
	case InitGameObjects:
		stage_InitGameObjects();
		break;

	case ParseStageData:
		parseData_Stage(currentStage);
		break;

	case ParseScreen:
		stage_ParseScreen();
		break;

	case InitStageMgr:
		stage_InitStageMgr();
		break;

	case Finish:
		buffer_UpdateScene(stageMgr._stageData);
		scene_SwitchTo(PLAY);
		nowSetting = Init;
		break;

	default:
		return;
	}
	nowSetting++;
}

void stage_ParseScreen()
{
	char* c;

	Enemy* e;
	int eTypeNum;
	int eCnt = 0;

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
			else if (*c == '\0')
			{
				continue;
			}
			//Player
			else if (*c == '0')
			{
				stageMgr._stageData[y][x] = playerSetting._sprite;
				player._xPos = x;
				player._yPos = y;
			}
			//Enemy
			else
			{
				e = &(enemy[eCnt]);

				eTypeNum = *c - '0';
				e->_xPos = x;
				e->_yPos = y;
				e->_life = EnemyType_Table[eTypeNum]._maxLife;
				e->_shotCoolTime = EnemyType_Table[eTypeNum]._shotCoolTime;
				e->_movePattern._type = &MovePattern_Table[EnemyType_Table[eTypeNum]._movePatternTypeNum];
				e->_sprite = *c;

				eCnt++;
			}
		}
	}
}

void stage_InitGameObjects()
{
	///오브젝트 관련 변수 및 배열 0으로 초기화
	memset(enemy, 0, sizeof(enemy));
	memset(playerShot, 0, sizeof(playerShot));
	memset(enemyShot, 0, sizeof(enemyShot));
	eShotCnt = 0;
	pShotCnt = 0;

}

void stage_InitStageMgr()
{
	///stage 변수 초기화
	stageMgr._enemyAlive = stageMgr._enemyTotal;
	stageMgr._playerLife = playerSetting._maxLife;
	memset(stageMgr._enemyLocationData, EMPTY, sizeof(stageMgr._enemyLocationData));
}