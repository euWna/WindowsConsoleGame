#pragma once
#ifndef __ENEMY_H__
#define __ENEMY_H__

enum ENEMY_SHOT_TYPE;

enum ENEMY_MOVE_PATTERN_TYPE;

struct Enemy
{
	bool isAlive = true;
	int _xPos;
	int _yPos;
	int _life;
	char _Sprite;
	ENEMY_SHOT_TYPE nShotType;
	ENEMY_MOVE_PATTERN_TYPE nMovePattern;
};

struct EnemyShot
{
	bool isGenerated = false;
	//생성시 pos player 및 enemy 위치에 ypos + 1 로 초기화, 직후 한칸 앞으로
	int _xPos;
	int _yPos;
	int iPower;
	char _Sprite;
};

void enemy_Shoot(int enemyIdx);
void enemy_GetShot(int enemyIdx);
#endif