#include <windows.h>

#include "ScreenSetting.h"
#include "MovePattern.h"
#include "Enemy.h"
#include "GameStage.h"
#include "Player.h"


EnemyType EnemyType_Table[MAX_ENEMY_TYPE];
EnemySetting enemySetting;
Enemy enemy[SCREEN_SIZE];
EnemyShot enemyShot[SCREEN_SIZE];

void enemy_Shoot(int enemyIdx)
{
	Enemy target = enemy[enemyIdx];
	
}

void enemy_GetShot(int enemyIdx)
{

}

void enemy_Move(int enemyIdx)
{
	Enemy_MovePatternQueue* q = &(enemy[enemyIdx]._movePattern);
	int moveIdx = q->_moveIdx;
	MoveOffset* _pattern = q->_type->_pattern;

	enemy[enemyIdx]._xPos += _pattern[moveIdx]._x;
	enemy[enemyIdx]._yPos += _pattern[moveIdx]._y;
	q->_moveIdx = (moveIdx + 1)%(q->_type->_length);
}