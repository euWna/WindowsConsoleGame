#include <windows.h>

#include "ScreenSetting.h"
#include "GameStage.h"
#include "MovePattern.h"
#include "Enemy.h"
#include "Player.h"
#include "GameObjects.h"

Enemy_Type EnemyType_Table[MAX_ENEMY_TYPE];



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
	q->_moveIdx = (moveIdx + 1)%(q->_type->_patternLen);
}