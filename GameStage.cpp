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

	/*�Է�*/
	//Player ����Ű �Է�
	int inputKey = cs_GetKeyInput();


	/*����*/
	//1. ������Ʈ �̵�
	///Player �̵� �Ǵ� �߻�
	player_Control(inputKey);

	//PlayerShot �߻� �� �̵�
	for (psIdx = 0; psIdx < MAX_PLAYER_SHOT; psIdx++)
	{
		if (!playerShot[psIdx].isVisible) continue;
		else playerShot[psIdx]._yPos--;
	}

	///Enemy �̵�
	for (eIdx = 0; eIdx < stageMgr._numOfEnemies; eIdx++)
	{
		if (enemy[eIdx]._isDead) continue;
		else enemy_Move(eIdx);
	}

	///EnemyShot �߻� �� �̵�
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


	//2. �浹 ó�� �� ���� Ŭ����/���� �Ǵ�
	///Player & Enemy �浹 ���� (= ���� ���� ����) ����
	for (eIdx = 0; eIdx < stageMgr._numOfEnemies; eIdx++)
	{
		if (enemy[eIdx]._isDead) continue;

		if (enemy[eIdx]._xPos == player._xPos
			&& enemy[eIdx]._yPos == player._yPos)
		{
			return RES_FAIL;
		}
	}

	///Player & EnemyShot �浹 & ���� ���� ����
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

	///Enemy & PlayerShot �浹 ���� & ���� Ŭ���� ����
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


	/*���*/
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

//�÷��̾�

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
		///������Ʈ �迭 0���� �ʱ�ȭ
		memset(enemy, 0, sizeof(enemy));
		memset(playerShot, 0, sizeof(playerShot));
		memset(enemyShot, 0, sizeof(enemyShot));

		///stage ���� �ʱ�ȭ
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


