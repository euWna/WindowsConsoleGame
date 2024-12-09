#pragma once
#ifndef __ENEMY_H__
#define __ENEMY_H__

#define MAX_ENEMY 20
#define MAX_ENEMY_TYPE 3


struct Enemy_MovePatternQueue
{
	//Circular Queue
	int _moveIdx;
	MovePatternType* _type;
};

struct Enemy
{
	bool _isAlive = true;
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
	int _shotCoolTime;
	int _movePatternTypeNum;
};


struct EnemyShot
{
	bool isGenerated = false;
	//생성시 pos player 및 enemy 위치에 ypos + 1 로 초기화, 직후 한칸 앞으로
	int _xPos;
	int _yPos;
	char _Sprite;
};

extern Enemy_Setting enemySetting;
extern Enemy enemy[SCREEN_SIZE];
extern EnemyShot enemyShot[SCREEN_SIZE];
extern Enemy_Type EnemyType_Table[MAX_ENEMY_TYPE];

void enemy_Shoot(int enemyIdx);
void enemy_GetShot(int enemyIdx);
void enemy_Move(int enemyIdx);

bool enemyShot_IsVisible(int enemyShotIdx);
void enemyShot_Move(int enemyShotIdx);


#endif