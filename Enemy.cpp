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

void enemy_Die(int enemyIdx)
{

}
void enemy_Shoot(int enemyIdx)
{
	Enemy target = enemy[enemyIdx];
	
}

void enemy_GetShot(int enemyIdx)
{
	Enemy* e = &(enemy[enemyIdx]);
	
	e->_life--;

	if (e->_life == 0)
	{
		e->_isDead = true;
	}
	else
	{
		e->_sprite = (enemy[enemyIdx]._sprite - 1);
	}
}

void enemy_Move(int enemyIdx)
{
	Enemy_MovePatternQueue* q = &(enemy[enemyIdx]._movePattern);
	int moveIdx = q->_moveIdx;
	MoveOffset* pattern = q->_type->_pattern;

	enemy[enemyIdx]._xPos += pattern[moveIdx]._x;
	enemy[enemyIdx]._yPos += pattern[moveIdx]._y;
	q->_moveIdx = (moveIdx + 1)%(q->_type->_length);
}