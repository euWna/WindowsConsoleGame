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

extern DWORD t_Standard; //enemyShot �߻� ��Ÿ�� ����

//����
//1. Player ����
//2. ������Ʈ �̵�
//3. ������Ʈ�� �浹 ó�� �� ���� Ŭ����/���� �Ǵ�
SceneType processFrame(SHORT inputKey)
{
	//���� ������Ʈ �迭 �ε���
	int psIdx;
	int eIdx;
	int esIdx;

	//1. Player ����
	switch (inputKey)
	{
	///PlayerShot �߻�
	case VK_SPACE:
		if (pShotCnt < MAX_PLAYER_SHOT)
		{
			psIdx = 0;
			while (playerShot[psIdx]._isShot) psIdx++;
			player_Shoot(&playerShot[psIdx]);
			pShotCnt++;
		}
		break;

	///Player �̵�
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

	//2. ������Ʈ �̵�
	///PlayerShot �̵�
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

	///Enemy �̵�
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

	///Enemy �߻�
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

	///EnemyShot �̵�
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


	//3. �浹 ó�� �� ���� Ŭ����/���� �Ǵ�
	///Player & Enemy �浹 ���� (= ���� ���� ����) ����
	for (eIdx = 0; eIdx < stageMgr._enemyTotal; eIdx++)
	{
		if (enemy[eIdx]._isDead) continue;

		if (enemy[eIdx]._xPos == player._xPos
			&& enemy[eIdx]._yPos == player._yPos)
		{
			return GAME_OVER;
		}
	}

	///Player & EnemyShot �浹 & ���� ���� ����
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

	///Enemy & PlayerShot �浹 ���� & ���� Ŭ���� ����
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


	/*���*/
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
	///������Ʈ ���� ���� �� �迭 0���� �ʱ�ȭ
	memset(enemy, 0, sizeof(enemy));
	memset(playerShot, 0, sizeof(playerShot));
	memset(enemyShot, 0, sizeof(enemyShot));
	eShotCnt = 0;
	pShotCnt = 0;

}

void stage_InitStageMgr()
{
	///stage ���� �ʱ�ȭ
	stageMgr._enemyAlive = stageMgr._enemyTotal;
	stageMgr._playerLife = playerSetting._maxLife;
	memset(stageMgr._enemyLocationData, EMPTY, sizeof(stageMgr._enemyLocationData));
}