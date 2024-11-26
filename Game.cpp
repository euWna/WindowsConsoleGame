#include "Console.h"
#include "GameStructs.h"
#include "Player.h"

extern Player player;
extern Enemy enemies;

#define PLAY 0
#define CLEAR 1
#define FAIL 2 

int playGame()
{
	/*입력*/
	int inputKey = cs_GetKeyInput();

	/*로직*/
	//Player 조작 
	player_Control(inputKey);
	//Player & Enemy 충돌 여부 판정




	//Player & EnemyShot 충돌 여부 판정

	/*출력*/
	
}