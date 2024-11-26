#include "Console.h"
#include "GlobalObjects.h"
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
		if (e.iXpos == player.iXpos
			&& e.iYpos == player.iYpos)
		{
			return RES_FAIL;
		}
	}

	//PlayerShot �̵� �� Enemy���� �浹 ���� ����
	for (PlayerShot shot : pShot)
	{
		if (!shot.isGenerated) continue;
		
		//�̵�
		shot.iYpos--;

		//�浹 ���� ����
		for (Enemy e : enemy)
		{
			if (e.iXpos == shot.iXpos
				&& e.iYpos == shot.iYpos)
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

		if (shot.iXpos == player.iXpos
			&& shot.iXpos == player.iYpos)
		{
			player.iLife -= shot.iPower;
		}
	}

	//PlayerShot & Enemy �浹 ���� ����

	/*���*/
	
}

