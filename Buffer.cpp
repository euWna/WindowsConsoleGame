#include <memory.h>
#include <string.h>

#include "ScreenSetting.h"
#include "Buffer.h"


void buffer_Clear(void)
{
	int iBufCnt;
	memset(ScreenBuffer, ' ', dfSCREEN_WIDTH * dfSCREEN_HEIGHT);

	for (iBufCnt = 0; iBufCnt < dfSCREEN_HEIGHT; iBufCnt++)
	{
		ScreenBuffer[iBufCnt][dfSCREEN_WIDTH - 1] = '\0';
	}
}

void buffer_DrawSprite(int iX, int iY, char chSprite)
{
	if (iX < 0 || iY < 0 || iX >= dfSCREEN_WIDTH - 1 || iY >= dfSCREEN_HEIGHT)
		return;

	ScreenBuffer[iY][iX] = chSprite;
}

void buffer_UpdateScene(char scene_memory[][dfSCREEN_WIDTH])
{
	int iBufCnt;
	for (iBufCnt = 0; iBufCnt < dfSCREEN_HEIGHT; iBufCnt++)
	{
		strcpy_s(ScreenBuffer[iBufCnt], scene_memory[iBufCnt]);
	}
}