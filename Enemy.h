#pragma once
#ifndef __ENEMY_H__
#define __ENEMY_H__

#define MAX_ENEMY 20
#define MAX_ENEMY_TYPE 4 //Type Idx : 1 ~ 3 


struct Enemy_MovePatternQueue
{
	//Circular Queue
	int _moveIdx = 0;
	MovePattern* _type;
};

struct Enemy
{
	bool _isAlive = true;
	int _xPos;
	int _yPos;
	int _life;
	char _sprite;
	Enemy_MovePatternQueue _movePattern;
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
	bool isGenerated = false;
	//������ pos player �� enemy ��ġ�� ypos + 1 �� �ʱ�ȭ, ���� ��ĭ ������
	int _xPos;
	int _yPos;
	char _sprite;
};

extern EnemySetting enemySetting;
extern Enemy enemy[SCREEN_SIZE];
extern EnemyShot enemyShot[SCREEN_SIZE];
extern EnemyType EnemyType_Table[MAX_ENEMY_TYPE];

void enemy_Shoot(int enemyIdx);
void enemy_GetShot(int enemyIdx);
void enemy_Move(int enemyIdx);

bool enemyShot_IsVisible(int enemyShotIdx);
void enemyShot_Move(int enemyShotIdx);


#endif