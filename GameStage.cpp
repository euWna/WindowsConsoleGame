#include <windows.h>

#include "ScreenSetting.h"
#include "Console.h"
#include "Player.h"
#include "MovePattern.h"
#include "Enemy.h"
#include "Scene.h"
#include "GameStage.h"


StageMgr stageMgr;


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
		if (!e.isAlive) continue;

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



bool game_CheckVisible()
{

}


void game_InitStage(int stageNum)
{
	//�������� ���� �ҷ�����
	int* numOfEnemies = &(stageMgr._iEnemyAlive);
	//char(*stageData)[dfSCREEN_WIDTH] = ScreenBuffer;

	//StageMgr �ʱ�ȭ
	///Enemy �迭 �ʱ�ȭ
	memset(enemy, 0, sizeof(enemy));
	int enemyCnt = 0;
	

	///Player life �ʱ�ȭ
	stageMgr._iPlayerLife = playerSetting.MAX_LIFE;
	
}

void game_ParseStage(const char* filePath)
{
	//�Ľ��� ������

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
