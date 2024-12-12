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
		if (!e._isAlive) continue;

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
		///Enemy 배열 초기화
		memset(enemy, 0, sizeof(enemy));
		///Player life 초기화
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


