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
	/*입력*/
	//Player 조작키 입력
	int inputKey = cs_GetKeyInput();


	/*로직*/
	//Player 조작
	player_Control(inputKey);

	//Enemy 이동
	//for (int i=0;)

	//EnemyShot 이동

	//PlayerShot 이동

	//Player & Enemy 충돌 여부 (= 게임 오버 여부) 판정

	//Player & EnemyShot 충돌 여부 (+ 게임 오버 여부) 판정

	//PlayerShot & Enemy 충돌 여부 판정

	//게임 클리어 여부 판정


	//Player 이동 
	player_Control(inputKey);

	//Enemy 이동 및 Player와의 충돌 여부(+게임 오버 여부) 판정
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
	//EnemyShot 이동 및 Player와의 충돌 여부(+게임 오버 여부) 판정
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

	//PlayerShot 이동 및 Enemy와의 충돌 여부(+게임 클리어 여부) 판정
	for (PlayerShot shot : playerShot)
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

	/*출력*/
	
}



bool game_CheckVisible()
{

}


void game_InitStage(int stageNum)
{
	//스테이지 정보 불러오기
	int* numOfEnemies = &(stageMgr._iEnemyAlive);
	//char(*stageData)[dfSCREEN_WIDTH] = ScreenBuffer;

	//StageMgr 초기화
	///Enemy 배열 초기화
	memset(enemy, 0, sizeof(enemy));
	int enemyCnt = 0;
	

	///Player life 초기화
	stageMgr._iPlayerLife = playerSetting.MAX_LIFE;
	
}

void game_ParseStage(const char* filePath)
{
	//파싱할 데이터

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
