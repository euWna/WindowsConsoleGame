#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <windows.h>

struct Player
{
	int iXpos;
	int iYpos;
	int iLife;
	char cIcon;
};

struct PlayerShot
{
	bool isGenerated = false;
	int iXpos;
	int iYpos;
	int iPower;
	char cIcon;
};

void player_Control(SHORT inputKey);
void player_Move(SHORT inputKey);
void player_Shoot();
bool player_GetShot();

#endif
