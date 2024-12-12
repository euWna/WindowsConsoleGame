#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__

struct PlayerSetting
{
	char _sprite;
	char _shotSprite;
	int _maxLife;
};

struct Player
{
	int _xPos;
	int _yPos;
};

struct PlayerShot
{
	bool isGenerated = false;
	int _xPos;
	int _yPos;
	int iPower;
	char _sprite;
};

extern Player player;
extern PlayerSetting playerSetting;
extern PlayerShot playerShot[SCREEN_SIZE];

void player_Control(SHORT inputKey);
void player_Move(SHORT inputKey);
void player_Shoot();
bool player_GetShot();

bool playerShot_hitEnemy();

#endif
