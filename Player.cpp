#include <Windows.h>

#include "Player.h"
#include "ScreenSetting.h"
#include "GameStructs.h"
#include "Buffer.h"

#define X 0
#define Y 1


extern Player player;

void player_Control(SHORT inputKey)
{
	switch (inputKey)
	{
	case VK_LEFT: 
		[[fallthrough]]
	case VK_UP: 
		[[fallthrough]]
	case VK_RIGHT: 
		[[fallthrough]]
	case VK_DOWN: 
		player_Move(inputKey);
		break;
	case VK_SPACE:
		player_Shoot();
		break;
	default:
		break;
	}
}

const int posOffset[4][2] = { {0,-1}, {-1,0}, {0,1}, {1,0} }; //←↑→↓ (시계 방향)
void player_Move(SHORT inputKey)
{
	//LEFT:0 | UP:1 | RIGHT:2 | DOWN:3
	int directionNum = inputKey - VK_LEFT;
	
	int newXpos = player.iXpos + posOffset[directionNum][X];
	int newYpos = player.iYpos + posOffset[directionNum][Y];
	
	if (newXpos >= 0 && newXpos < dfSCREEN_WIDTH
		&& newYpos >= 0 && newYpos < dfSCREEN_HEIGHT)
	{
		player.iXpos = newXpos;
		player.iYpos = newYpos;
		return;
	}
}

void player_Shoot()
{

}

void player_GetShot()
{

}