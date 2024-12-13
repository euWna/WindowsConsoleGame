#include <windows.h>

#include "ScreenSetting.h"
#include "Player.h"
#include "Buffer.h"

#define X 0
#define Y 1

Player player;
PlayerSetting playerSetting;
PlayerShot playerShot[MAX_PLAYER_SHOT];

int pShotCnt;

void player_Control(SHORT inputKey)
{
	switch (inputKey)
	{
	case VK_SPACE:
		player_Shoot();
		return;

	case VK_LEFT: 
		//[[fallthrough]]
	case VK_UP: 
		//[[fallthrough]]
	case VK_RIGHT: 
		//[[fallthrough]]
	case VK_DOWN: 
		player_Move(inputKey);
		return;

	default:
		return;
	}
}

const int posOffset[4][2] = { {-1,0}, {0,-1}, {1,0}, {0,1} }; //←↑→↓ (시계 방향)
void player_Move(SHORT inputKey)
{
	//LEFT:0 | UP:1 | RIGHT:2 | DOWN:3
	int directionNum = inputKey - VK_LEFT;
	
	int newXpos = player._xPos + posOffset[directionNum][X];
	int newYpos = player._yPos + posOffset[directionNum][Y];
	
	//Check if new pos's are in the screen range
	if (newXpos >= 0 && newXpos < dfSCREEN_WIDTH-1
		&& newYpos >= 0 && newYpos < dfSCREEN_HEIGHT-1)
	{
		player._xPos = newXpos;
		player._yPos = newYpos;
		return;
	}
}

void player_Shoot()
{
	if (pShotCnt == MAX_PLAYER_SHOT) return;

	int psIdx = 0;
	while (playerShot[psIdx].isVisible) psIdx++;
	playerShot[psIdx].isVisible = true;
	playerShot[psIdx]._xPos = player._xPos;
	playerShot[psIdx]._yPos = player._yPos;

	pShotCnt++;
}
