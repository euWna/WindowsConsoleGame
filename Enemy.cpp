#include <windows.h>

#include "Buffer.h"
#include "MovePattern.h"
#include "Enemy.h"
#include "GameStage.h"
#include "Player.h"


EnemyType EnemyType_Table[MAX_ENEMY_TYPE];
EnemySetting enemySetting;
Enemy enemy[MAX_ENEMY];
EnemyShot enemyShot[MAX_ENEMY_SHOT];

void enemy_Shoot(int eIdx)
{
	if (eShotCnt == MAX_ENEMY_SHOT) return;
	int eIdx = 0;
	while (enemyShot[eIdx].isVisible) eIdx++;
	enemyShot[eIdx].isVisible = true;
	enemyShot[eIdx]._xPos = enemy[eIdx]._xPos;
	enemyShot[eIdx]._yPos = enemy[eIdx]._yPos;
	eShotCnt++;
}

void enemy_GetShot(int enemyIdx)
{
	Enemy* e = &(enemy[enemyIdx]);
	
	e->_life--;

	if (e->_life == 0)
	{
		e->_isDead = true;
		stageMgr._enemyAlive--;
		stageMgr._enemyLocationData[e->_yPos][e->_xPos] = MAX_ENEMY;
	}
	else
	{
		e->_sprite = (enemy[enemyIdx]._sprite - 1);
	}
}

void enemy_Move(int enemyIdx)
{
	Enemy* e = &(enemy[enemyIdx]);
	Enemy_MovePatternQueue* q = &(e->_movePattern);
	int moveIdx = q->_moveIdx;
	MoveOffset* pattern = q->_type->_pattern;

	stageMgr._enemyLocationData[e->_yPos][e->_xPos] = MAX_ENEMY;
	e->_xPos += pattern[moveIdx]._x;
	e->_yPos += pattern[moveIdx]._y;
	stageMgr._enemyLocationData[e->_yPos][e->_xPos] = enemyIdx;

	q->_moveIdx = (moveIdx + 1)%(q->_type->_length);
}

void enemyShot_Move(int enemyShotIdx)
{
	EnemyShot* e = &enemyShot[enemyShotIdx];
	enemyShot[enemyShotIdx]._yPos++;

	if (enemyShot[enemyShotIdx]._yPos >= dfSCREEN_HEIGHT)
	{
		enemyShot[enemyShotIdx].isVisible = false;
		eShotCnt--;
	}
}