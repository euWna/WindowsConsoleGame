#pragma once
#ifndef __GAME_OBJECTS_H__
#define __GAME_OBJECTS_H__

struct Player
{
	int iXpos;
	int iYpos;
	int iLife;
	char cIcon;
};


struct PlayerShot
{
	int iPower;
	char cIcon;
};

typedef unsigned short ENEMY_BULLET_TYPE ;
typedef unsigned short ENEMY_MOVE_PATTERN_TYPE ;
struct Enemy
{
	int iXpos;
	int iYpos;
	int iLife;
	char cIcon;
};

struct EnemyShot
{
	char cIcon;
	int iPower;
};


#endif