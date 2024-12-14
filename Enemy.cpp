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

	int esIdx = 0;
	while (enemyShot[esIdx]._isShot) esIdx++;

	enemyShot[esIdx]._isShot = true;
	enemyShot[esIdx]._xPos = enemy[eIdx]._xPos;
	enemyShot[esIdx]._yPos = enemy[eIdx]._yPos;
	eShotCnt++;
}

void enemy_GetShot(int eIdx)
{
	Enemy* e = &(enemy[eIdx]);
	
	e->_life--;

	if (e->_life == 0)
	{
		e->_isDead = true;
		stageMgr._enemyAlive--;
		stageMgr._enemyLocationData[e->_yPos][e->_xPos] = EMPTY;
	}
	else
	{
		e->_sprite = (enemy[eIdx]._sprite - 1);
	}
}

void enemy_Move(int eIdx)
{
	Enemy* e = &(enemy[eIdx]);
	Enemy_MovePatternQueue* q = &(e->_movePattern);
	int moveIdx = q->_moveIdx;
	MoveOffset* pattern = q->_type->_pattern;

	stageMgr._enemyLocationData[e->_yPos][e->_xPos] = EMPTY;
	e->_xPos += pattern[moveIdx]._x;
	e->_yPos += pattern[moveIdx]._y;
	stageMgr._enemyLocationData[e->_yPos][e->_xPos] = eIdx;

	q->_moveIdx = (moveIdx + 1)%(q->_type->_length);
}

void enemyShot_Move(int esIdx)
{
	EnemyShot* e = &enemyShot[esIdx];
	enemyShot[esIdx]._yPos++;

	if (enemyShot[esIdx]._yPos >= dfSCREEN_HEIGHT)
	{
		enemyShot[esIdx]._isShot = false;
		eShotCnt--;
	}
}