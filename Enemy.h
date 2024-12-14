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
	//생성시 pos player 및 enemy 위치에 ypos + 1 로 초기화, 직후 한칸 앞으로
	int _xPos;
	int _yPos;
	bool _isShot = false;
};

extern EnemySetting enemySetting;
extern Enemy enemy[MAX_ENEMY];
extern EnemyShot enemyShot[MAX_ENEMY_SHOT];
extern EnemyType EnemyType_Table[MAX_ENEMY_TYPE];

extern int eShotCnt;

void enemy_Shoot(int enemyIdx);
void enemy_GetShot(int enemyIdx);
void enemy_Move(int enemyIdx);
void enemyShot_Move(int enemyShotIdx);

#endif