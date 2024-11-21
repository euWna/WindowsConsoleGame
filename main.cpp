#include <stdio.h>
#include <memory.h>
#include <Windows.h>
#include "sample/Console_sample.h"
#include "Screen.h"

char szScreenBuffer[dfSCREEN_HEIGHT][dfSCREEN_WIDTH];

int iPlayerPosX = dfSCREEN_WIDTH/2;
int iPlayerPosY = dfSCREEN_HEIGHT/2;


int main()
{
	cs_Initial();
	sc_Title();
}