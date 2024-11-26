#include <memory.h>

#include "ScreenSetting.h"
#include "Buffer.h"

extern char ScreenBuffer_Render[dfSCREEN_HEIGHT][dfSCREEN_WIDTH];
extern char ScreenBuffer_Next[dfSCREEN_HEIGHT][dfSCREEN_WIDTH];

void buffer_Clear(void)
{
	int iCnt;
	memset(ScreenBuffer_Next, ' ', dfSCREEN_WIDTH * dfSCREEN_HEIGHT);

	for (iCnt = 0; iCnt < dfSCREEN_HEIGHT; iCnt++)
	{
		ScreenBuffer_Next[iCnt][dfSCREEN_WIDTH - 1] = '\0';
	}
}

void buffer_DrawSprite(int iX, int iY, char chSprite)
{
	if (iX < 0 || iY < 0 || iX >= dfSCREEN_WIDTH - 1 || iY >= dfSCREEN_HEIGHT)
		return;

	ScreenBuffer_Next[iY][iX] = chSprite;
}

void buffer_GetSceneData(FILE* fp)
{
	fread(ScreenBuffer_Next, dfSCREEN_HEIGHT * dfSCREEN_WIDTH, 1, fp);
	for (int iBufCnt = 0; iBufCnt < dfSCREEN_HEIGHT; iBufCnt++)
	{
		ScreenBuffer_Next[iBufCnt][dfSCREEN_WIDTH - 1] = '\0';
	}
}

void buffer_Flip()
{
	char (*ptrRender)[dfSCREEN_WIDTH] = ScreenBuffer_Render;
	char(*ptrNext)[dfSCREEN_WIDTH] = ScreenBuffer_Next;
	
	char (*ptrTemp)[dfSCREEN_WIDTH] = ptrRender;
	ptrRender = ptrNext;
	ptrNext = ptrTemp;

}