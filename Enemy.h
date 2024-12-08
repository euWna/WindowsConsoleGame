#pragma once
#ifndef __ENEMY_H__
#define __ENEMY_H__

#define MAX_ENEMY 20
#define MAX_ENEMY_TYPE 3

struct Enemy;
struct Enemy_Setting;
struct Enemy_Type;
struct Enemy_MovePatternQueue;

struct EnemyShot;

extern Enemy_Type EnemyType_Table[MAX_ENEMY_TYPE];


struct Enemy
{
	bool isAlive = true;
	int _xPos;
	int _yPos;
	int _life;
	char _Sprite;
	Enemy_MovePatternQueue _movePattern;
};

struct Enemy_Setting
{
	char SHOT_SPRITE;
};

struct Enemy_Type
{
	int _maxLife;
	int _movePatternTypeNum;
};

struct Enemy_MovePatternQueue
{
	//Circular Queue
	int _moveIdx;
	MovePatternType* _type;
};

struct EnemyShot
{
	bool isGenerated = false;
	//생성시 pos player 및 enemy 위치에 ypos + 1 로 초기화, 직후 한칸 앞으로
	int _xPos;
	int _yPos;
	char _Sprite;
};


void enemy_Shoot(int enemyIdx);
void enemy_GetShot(int enemyIdx);
void enemy_Move(int enemyIdx);

bool enemyShot_IsVisible(int enemyShotIdx);
void enemyShot_Move(int enemyShotIdx);




#endif