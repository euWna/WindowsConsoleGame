#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__

struct Player
{
	int _life;
	int _xPos;
	int _yPos;
};

struct PlayerShot
{
	bool isGenerated = false;
	int _xPos;
	int _yPos;
	int iPower;
	char _Sprite;
};

struct PlayerSettingMemory
{
	char SPRITE;
	char SHOT_SPRITE;
	int MAX_LIFE;
};


void player_Control(SHORT inputKey);
void player_Move(SHORT inputKey);
void player_Shoot();
bool player_GetShot();

#endif
