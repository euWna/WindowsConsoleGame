#include <windows.h>

#include "ScreenSetting.h"
#include "Buffer.h"
#include "Console.h"
#include "Player.h"
#include "MovePattern.h"
#include "Enemy.h"
#include "Scene.h"
//#include "DataParsing.h"
#include "GameStage.h"


StageMgr stageMgr;


int processFrame()
{
	/*�Է�*/
	//Player ����Ű �Է�
	int inputKey = cs_GetKeyInput();


	/*����*/
	//1. ������Ʈ �̵�
	///Player �̵� �Ǵ� ����
	player_Control(inputKey);

	///Enemy �̵�
	for (int eIdx = 0; eIdx < stageMgr._numOfEnemies; eIdx++)
	{
		if (enemy[eIdx]._isDead) continue;

		enemy_Move(eIdx);
	}

	///EnemyShot �̵�

	///PlayerShot �̵�


	//2. �浹 ó�� �� ���� Ŭ����/���� �Ǵ�
	///Player & Enemy �浹 ���� (= ���� ���� ����) ����
	for (int eIdx = 0; eIdx < stageMgr._numOfEnemies; eIdx++)
	{
		if (enemy[eIdx]._isDead) continue;

		if (enemy[eIdx]._xPos == player._xPos
			&& enemy[eIdx]._yPos == player._yPos)
		{
			return RES_FAIL;
		}
	}

	///Player & EnemyShot �浹 ���� (+ ���� ���� ����) ����

	///PlayerShot & Enemy �浹 ���� ����

	//���� Ŭ���� ���� ����


	////EnemyShot �̵� �� Player���� �浹 ����(+���� ���� ����) ����
	//for (EnemyShot shot : enemyShot)
	//{
	//	if (!shot.isGenerated) continue;

	//	enemyShot_Move();

	//	if (shot._xPos == player._xPos
	//		&& shot._xPos == player._yPos)
	//	{
	//		stageMgr._playerLife--;
	//		if (stageMgr._playerLife == 0) return RES_FAIL;
	//	}
	//}

	////PlayerShot �̵� �� Enemy���� �浹 ����(+���� Ŭ���� ����) ����
	//for (PlayerShot shot : playerShot)
	//{
	//	if (!shot.isGenerated) continue;
	//	
	//	//�̵�
	//	shot._yPos--;

	//	//�浹 ���� ����
	//	for (Enemy e : enemy)
	//	{
	//		if (e._xPos == shot._xPos
	//			&& e._yPos == shot._yPos)
	//		{
	//			
	//		}
	//	}
	//}

	/*���*/
	//player
	buffer_DrawSprite(player._xPos, player._yPos, playerSetting._sprite);
	//enemy
	for (int eIdx = 0; eIdx < stageMgr._numOfEnemies; eIdx++)
	{
		if (enemy[eIdx]._isDead) continue;

		buffer_DrawSprite(enemy[eIdx]._xPos, enemy[eIdx]._yPos, enemy[eIdx]._sprite);
	}

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
		///Enemy �迭 0���� �ʱ�ȭ
		memset(enemy, 0, sizeof(enemy));
		///stageMgr �ʱ�ȭ
		stageMgr._enemyAlive = stageMgr._numOfEnemies;
		stageMgr._playerLife = playerSetting._maxLife;
		break;

	case SetGameObjectsOnStage:
		game_SetGameObjectsOnStage();
		break;

	case Finish:
		scene_ConvertTo(PLAY);
		buffer_UpdateScene(stageMgr._stageData);
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
				eTypeNum = *c - '0';
				e->_xPos = x;
				e->_yPos = y;
				e->_life = EnemyType_Table[eTypeNum]._maxLife;
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


