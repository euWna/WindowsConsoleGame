#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__

#define MAX_PLAYER_SHOT 50

struct PlayerSetting
{
	int _maxLife;
	char _sprite;
	char _shotSprite;
};

struct Player
{
	int _xPos;
	int _yPos;
};

struct PlayerShot
{
	int _xPos;
	int _yPos;
	bool isVisible = false;
};

extern Player player;
extern PlayerSetting playerSetting;
extern PlayerShot playerShot[MAX_PLAYER_SHOT];
extern int pShotCnt;

void player_Control(SHORT inputKey);
void player_Move(SHORT inputKey);
void player_Shoot();

#endif
