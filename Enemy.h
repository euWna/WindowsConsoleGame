#pragma once
#ifndef __ENEMY_H__
#define __ENEMY_H__

#define MAX_ENEMY 20
#define MAX_ENEMY_TYPE 4 //Type Idx : 1 ~ 3 
#define MAX_ENEMY_SHOT 100

struct Enemy_MovePatternQueue
{
	//Circular Queue
	int _moveIdx;
	MovePattern* _type;
};

struct Enemy
{
	int _xPos;
	int _yPos;
	int _life;
	int _shotCoolTime;
	Enemy_MovePatternQueue _movePattern;
	char _sprite;
	bool _isDead = false;;
};

struct EnemySetting
{
	char _shotSprite;
};

struct EnemyType
{
	int _maxLife;
	int _shotCoolTime;
	int _movePatternTypeNum;
};


struct EnemyShot
{
	//������ pos player �� enemy ��ġ�� ypos + 1 �� �ʱ�ȭ, ���� ��ĭ ������
	int _xPos;
	int _yPos;
	bool _isShot = false;
};

extern EnemySetting enemySetting;
extern EnemyType EnemyType_Table[MAX_ENEMY_TYPE];

extern int eShotCnt;

void enemy_Move(Enemy* e);
void enemy_Shoot(Enemy* e, EnemyShot* eShot);
bool enemy_GetShot(Enemy* e);
bool enemyShot_Move(EnemyShot* eShot);

#endif