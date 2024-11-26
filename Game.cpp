#include "Console.h"
#include "GlobalObjects.h"
#include "Scene.h"




int processFrame()
{
	/*입력*/
	int inputKey = cs_GetKeyInput();


	/*로직*/
	//Player 조작 
	player_Control(inputKey);

	//Enemy 이동 및 Player와의 충돌 여부 판정
	for (Enemy e : enemy)
	{
		if (!e.isAlive) continue;

		//이동
		//move pattern

		//충돌 여부 판정
		if (e.iXpos == player.iXpos
			&& e.iYpos == player.iYpos)
		{
			return RES_FAIL;
		}
	}

	//PlayerShot 이동 및 Enemy와의 충돌 여부 판정
	for (PlayerShot shot : pShot)
	{
		if (!shot.isGenerated) continue;
		
		//이동
		shot.iYpos--;

		//충돌 여부 판정
		for (Enemy e : enemy)
		{
			if (e.iXpos == shot.iXpos
				&& e.iYpos == shot.iYpos)
			{
				
			}
		}
	}

	//EnemyShot 이동 및 Player와의 충돌 여부 판정

	//Enemy 이동

	//Shot 이동
	
	//Player & Enemy 충돌 여부 판정


	//Player & EnemyShot 충돌 여부 판정
	for (EnemyShot shot : eShot)
	{
		if (!shot.isGenerated) continue;

		if (shot.iXpos == player.iXpos
			&& shot.iXpos == player.iYpos)
		{
			player.iLife -= shot.iPower;
		}
	}

	//PlayerShot & Enemy 충돌 여부 판정

	/*출력*/
	
}

