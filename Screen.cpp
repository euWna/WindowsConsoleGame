#include <stdio.h>
#include "sample/Console_sample.h"

extern char szScreenBuffer[dfSCREEN_HEIGHT][dfSCREEN_WIDTH];

void sc_Title()
{
	int iBufCnt;
	for (iBufCnt = 0; iBufCnt < dfSCREEN_WIDTH-1; iBufCnt++)
	{
		szScreenBuffer[0][iBufCnt] = '=';
	}
	szScreenBuffer[0][iBufCnt++] = '\0';
	//buffer[iBufCnt] = '\0';
	printf(buffer);

	sz
}