#include <windows.h>

#include "ScreenSetting.h"
#include "Console.h"
#include "Player.h"
#include "MovePattern.h"
#include "Enemy.h"
#include "Scene.h"
//#include "DataParsing.h"
#include "GameStage.h"


StageMgr stageMgr;
extern SceneType currentScene;
extern int currentStage;
extern void parseData_Stage(int stageNum);


int processFrame()
{
	/*�Է�*/
	//Player ����Ű �Է�
	int inputKey = cs_GetKeyInput();


	/*����*/
	//Player ����
	player_Control(inputKey);

	//Enemy �̵�
	//for (int i=0;)

	//EnemyShot �̵�

	//PlayerShot �̵�

	//Player & Enemy �浹 ���� (= ���� ���� ����) ����

	//Player & EnemyShot �浹 ���� (+ ���� ���� ����) ����

	//PlayerShot & Enemy �浹 ���� ����

	//���� Ŭ���� ���� ����


	//Player �̵� 
	player_Control(inputKey);

	//Enemy �̵� �� Player���� �浹 ����(+���� ���� ����) ����
	for (Enemy e : enemy)
	{
		if (!e._isAlive) continue;

		//�̵�
		//move pattern

		//�浹 ���� ����
		if (e._xPos == player._xPos
			&& e._yPos == player._yPos)
		{
			return RES_FAIL;
		}
	}
	//EnemyShot �̵� �� Player���� �浹 ����(+���� ���� ����) ����
	for (EnemyShot shot : enemyShot)
	{
		if (!shot.isGenerated) continue;

		enemyShot_Move();

		if (shot._xPos == player._xPos
			&& shot._xPos == player._yPos)
		{
			stageMgr._iPlayerLife--;
			if (stageMgr._iPlayerLife == 0) return RES_FAIL;
		}
	}

	//PlayerShot �̵� �� Enemy���� �浹 ����(+���� Ŭ���� ����) ����
	for (PlayerShot shot : playerShot)
	{
		if (!shot.isGenerated) continue;
		
		//�̵�
		shot._yPos--;

		//�浹 ���� ����
		for (Enemy e : enemy)
		{
			if (e._xPos == shot._xPos
				&& e._yPos == shot._yPos)
			{
				
			}
		}
	}

	/*���*/
}



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
	static int nowSetting = 0;

	switch (nowSetting)
	{
	case Init:
		break;
	case ParseStageData:
		parseData_Stage(currentStage);
		break;
	case InitGameObjects:
		///Enemy �迭 �ʱ�ȭ
		memset(enemy, 0, sizeof(enemy));
		///Player life �ʱ�ȭ
		stageMgr._iPlayerLife = playerSetting._maxLife;
	case SetGameObjectsOnStage:
		game_SetGameObjectsOnStage();
		break;
	case Finish:
		currentScene = PLAY;
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

	for (int y = 0; y < dfSCREEN_HEIGHT; y++)
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
			}
			//Enemy
			else
			{
				eTypeNum = *c - '0';
				e->_xPos = x;
				e->_yPos = y;
				e->_life = EnemyType_Table[eTypeNum]._maxLife;
				e->_sprite = e->_life;
				e->_movePattern._type = &MovePattern_Table[EnemyType_Table[eTypeNum]._movePatternTypeNum];

				stageMgr._stageData[y][x] = e->_sprite;
				eCnt++;
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


