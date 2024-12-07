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
	//������ pos player �� enemy ��ġ�� ypos + 1 �� �ʱ�ȭ, ���� ��ĭ ������
	int _xPos;
	int _yPos;
	int iPower;
	char _Sprite;
};

void enemy_Shoot(int enemyIdx);
void enemy_GetShot(int enemyIdx);
#endif