#include <stdio.h>

#include "Console.h"

HANDLE  hConsole;

//-------------------------------------------------------------
// 이렇게 씁니다.
//
// #incude <stdio.h>
// #include <windows.h>
// #incude "Console.h"
//
// void main(void)
// {
//		cs_Initial();
//
//		cs_MoveCursor(0, 0);	// 커서를 0, 0 위치로
//		printf("abcde");		// 0, 0 위치에 글씨를 찍음
//		cs_MoveCursor(20, 10);	// 커서를 20, 10 위치로
//		printf("abcde");		// 20, 10 위치에 글씨를 찍음
//
// }
//-------------------------------------------------------------

//-------------------------------------------------------------
// 콘솔 제어를 위한 준비 작업.
//
//-------------------------------------------------------------
void cs_Initial(void)
{
	CONSOLE_CURSOR_INFO stConsoleCursor;

	//-------------------------------------------------------------
	// 화면의 커서를 안보이게끔 설정한다.
	//-------------------------------------------------------------
	stConsoleCursor.bVisible = FALSE;
	stConsoleCursor.dwSize = 1;


	//-------------------------------------------------------------
	// 콘솔화면 (스텐다드 아웃풋) 핸들을 구한다.
	//-------------------------------------------------------------
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(hConsole, &stConsoleCursor);
}

//-------------------------------------------------------------
// 콘솔 화면의 커서를 X, Y 좌표로 이동시킨다.
//
//-------------------------------------------------------------
void cs_MoveCursor(int iPosX, int iPosY)
{
	COORD stCoord;
	stCoord.X = iPosX;
	stCoord.Y = iPosY;
	//-------------------------------------------------------------
	// 원하는 위치로 커서를 이동시킨다.
	//-------------------------------------------------------------
	SetConsoleCursorPosition(hConsole, stCoord);
}

//-------------------------------------------------------------
// 콘솔 화면을 초기화 한다.
//
//-------------------------------------------------------------
void cs_ClearScreen(void)
{
	DWORD dw;

	FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), ' ', 100 * 100, { 0, 0 }, &dw);

}

//-------------------------------------------------------------
// 콘솔에서 키보드 입력을 받는다.
// 게임의 조작키인 방향키(←↑→↓)와 Space바 입력만 처리한다.
//
//-------------------------------------------------------------
SHORT cs_GetKeyInput(void)
{
	SHORT inputKey = 0;
	if (GetAsyncKeyState(VK_LEFT) && 0x8001)
	{
		inputKey = VK_LEFT;
	}
	else if (GetAsyncKeyState(VK_UP) && 0x8001)
	{
		inputKey = VK_UP;
	}
	else if (GetAsyncKeyState(VK_RIGHT) && 0x8001)
	{
		inputKey = VK_RIGHT;
	}
	else if (GetAsyncKeyState(VK_DOWN) && 0x8001)
	{
		inputKey = VK_DOWN;
	}
	else if (GetAsyncKeyState(VK_SPACE) && 0x8001)
	{
		inputKey = VK_SPACE;
	}

	return inputKey;
}