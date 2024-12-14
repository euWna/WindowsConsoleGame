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

SceneType processFrame()
{
	/*입력*/
	//Player 조작키 입력
	int inputKey = cs_GetKeyInput();


	/*로직*/
	int eIdx;
	int esIdx;
	int psIdx;

	//1. 오브젝트 이동
	///Player 이동 또는 발사
	player_Control(inputKey);

	//PlayerShot 발사 및 이동
	for (psIdx = 0; psIdx < MAX_PLAYER_SHOT; psIdx++)
	{
		if (!playerShot[psIdx]._isShot) continue;
		else playerShot[psIdx]._yPos--;
	}

	///Enemy 이동
	for (eIdx = 0; eIdx < stageMgr._enemyTotal; eIdx++)
	{
		if (enemy[eIdx]._isDead) continue;
		else enemy_Move(eIdx);
	}

	///EnemyShot 발사 및 이동
	for (eIdx = 0; eIdx < stageMgr._enemyTotal; eIdx++)
	{
		if (t_Standard % (enemy[eIdx]._shotCoolTime * 1000) == 0)
			enemy_Shoot(eIdx);
	}
	for (esIdx = 0; esIdx < MAX_ENEMY_SHOT; esIdx++)
	{
		if (!enemyShot[esIdx]._isShot) continue;
		else enemyShot_Move(esIdx);
	}


	//2. 충돌 처리 및 게임 클리어/오버 판단
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
		if (!enemyShot[esIdx]._isShot) continue;

		if (enemyShot[esIdx]._xPos == player._xPos
			&& enemy[eIdx]._yPos == player._yPos)
		{
			stageMgr._playerLife--;
			if (stageMgr._playerLife <= 0)
				return GAME_OVER;
		}
	}

	///Enemy & PlayerShot 충돌 여부 & 게임 클리어 판정
	for (psIdx = 0; psIdx < MAX_PLAYER_SHOT; psIdx++)
	{
		PlayerShot* ps = &playerShot[psIdx];
		int shotEnemyIdx;

		if (stageMgr._enemyLocationData[ps->_yPos][ps->_xPos] != EMPTY)
		{
			shotEnemyIdx = stageMgr._enemyLocationData[ps->_yPos][ps->_xPos];
			enemy_GetShot(shotEnemyIdx);
			if (stageMgr._enemyAlive <= 0)
				return STAGE_CLEAR;
		}
	}


	/*출력*/
	//enemy shot
	for (esIdx = 0; esIdx < MAX_ENEMY_SHOT; esIdx++)
	{
		if (!enemyShot[esIdx]._isShot) continue;

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
		if (!playerShot[psIdx]._isShot) continue;
		
		buffer_DrawSprite(playerShot[psIdx]._xPos, playerShot[psIdx]._yPos, playerSetting._shotSprite);
	}

	//player
	buffer_DrawSprite(player._xPos, player._yPos, playerSetting._sprite);

	return PLAY;
}

//플레이어

extern SceneType currentScene;
extern void parseData_Stage(int stageNum);
void stage_ParseScreen();

enum StageSetting
{
	Init,
	ParseStageData,
	ParseScreen,
	InitGameObjects,
	Finish
};

void stage_InitStage()
{
	static int nowSetting = Init;

	switch (nowSetting)
	{
	case Init:
		//동작 없음. 바로 다음 케이스로
		nowSetting++;
	case ParseStageData:
		parseData_Stage(currentStage);
		break;

	case ParseScreen:
		stage_ParseScreen();
		break;

	case InitGameObjects:
		stage_InitGameObjects();
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

void stage_InitGameObjects()
{
	///오브젝트 관련 변수 및 배열 0으로 초기화
	memset(enemy, 0, sizeof(enemy));
	memset(playerShot, 0, sizeof(playerShot));
	memset(enemyShot, 0, sizeof(enemyShot));
	eShotCnt = 0;
	pShotCnt = 0;

	///stage 변수 초기화
	stageMgr._enemyAlive = stageMgr._enemyTotal;
	stageMgr._playerLife = playerSetting._maxLife;
}