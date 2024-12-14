#include <windows.h>

#include "Buffer.h"
#include "MovePattern.h"
#include "Enemy.h"

EnemyType EnemyType_Table[MAX_ENEMY_TYPE];
EnemySetting enemySetting;


void enemy_Move(Enemy* e)
{
	Enemy_MovePatternQueue* q = &(e->_movePattern);
	int moveIdx = q->_moveIdx;
	MoveOffset* pattern = q->_type->_pattern;

	e->_xPos += pattern[moveIdx]._x;
	e->_yPos += pattern[moveIdx]._y;

	q->_moveIdx = (moveIdx + 1) % (q->_type->_length);
}

void enemy_Shoot(Enemy* e, EnemyShot* eShot)
{
	eShot->_isShot = true;
	eShot->_xPos = e->_xPos;
	eShot->_yPos = e->_yPos;
}

bool enemy_GetShot(Enemy* e) //죽었는지 여부 리턴
{	
	e->_life--;

	if (e->_life > 0)
	{
		e->_sprite = (e->_sprite - 1);
	}
	else 
	{
		e->_isDead = true;
	}

	return e->_isDead;
}

bool enemyShot_Move(EnemyShot* eShot) //화면에 남아있는지 여부 리턴
{
	eShot->_yPos++;

	if (eShot->_yPos > dfSCREEN_HEIGHT)
	{
		eShot->_isShot = false;
	}
	
	return eShot->_isShot;
}