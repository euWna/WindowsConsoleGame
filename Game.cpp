#include "Console.h"
#include "Player.h"
#include "Enemy.h"
#include "ScreenSetting.h"
#include "GameObjects.h"
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
		if (e._xPos == player._xPos
			&& e._yPos == player._yPos)
		{
			return RES_FAIL;
		}
	}

	//PlayerShot 이동 및 Enemy와의 충돌 여부 판정
	for (PlayerShot shot : pShot)
	{
		if (!shot.isGenerated) continue;
		
		//이동
		shot._yPos--;

		//충돌 여부 판정
		for (Enemy e : enemy)
		{
			if (e._xPos == shot._xPos
				&& e._yPos == shot._yPos)
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

		if (shot._xPos == player._xPos
			&& shot._xPos == player._yPos)
		{
			player._life -= shot.iPower;
		}
	}

	//PlayerShot & Enemy 충돌 여부 판정

	/*출력*/
	
}

