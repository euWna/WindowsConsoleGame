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
	/*�Է�*/
	int inputKey = cs_GetKeyInput();

	/*����*/
	//Player ���� 
	player_Control(inputKey);
	//Player & Enemy �浹 ���� ����




	//Player & EnemyShot �浹 ���� ����

	/*���*/
	
}