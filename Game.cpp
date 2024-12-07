#include "Console.h"
#include "Player.h"
#include "Enemy.h"
#include "ScreenSetting.h"
#include "GameObjects.h"
#include "Scene.h"




int processFrame()
{
	/*�Է�*/
	int inputKey = cs_GetKeyInput();


	/*����*/
	//Player ���� 
	player_Control(inputKey);

	//Enemy �̵� �� Player���� �浹 ���� ����
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

	//PlayerShot �̵� �� Enemy���� �浹 ���� ����
	for (PlayerShot shot : pShot)
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

	//EnemyShot �̵� �� Player���� �浹 ���� ����

	//Enemy �̵�

	//Shot �̵�
	
	//Player & Enemy �浹 ���� ����


	//Player & EnemyShot �浹 ���� ����
	for (EnemyShot shot : eShot)
	{
		if (!shot.isGenerated) continue;

		if (shot._xPos == player._xPos
			&& shot._xPos == player._yPos)
		{
			player._life -= shot.iPower;
		}
	}

	//PlayerShot & Enemy �浹 ���� ����

	/*���*/
	
}

