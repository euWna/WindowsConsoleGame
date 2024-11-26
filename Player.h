#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <Windows.h>

struct Player
{
	int iXpos;
	int iYpos;
	int iLife;
	char cIcon;
};

void player_Control(SHORT inputKey);
void player_Shoot();
void player_GetShot();

#endif
