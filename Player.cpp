#include <windows.h>

#include "Player.h"
#include "Buffer.h"

#define X 0
#define Y 1

PlayerSetting playerSetting;
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

void player_Shoot(PlayerShot* pShot)
{
	pShot->_isShot = true;
	pShot->_xPos = player._xPos;
	pShot->_yPos = player._yPos;
}


bool playerShot_Move(PlayerShot* pShot)
{
	pShot->_yPos--;

	if (pShot->_yPos >= 0)
	{
		return true;
	}
	else
	{
		pShot->_isShot = false;
		return false;
	}

}