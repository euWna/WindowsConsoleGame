#include <stdio.h>
#include <Windows.h>

#include "Scene.h"
#include "Buffer.h"

extern char ScreenBuffer[dfSCREEN_HEIGHT][dfSCREEN_WIDTH];
extern SCENE_NUM currentScene;
extern int currentStage;

SCENE Scene[4] = { {TITLE}, {LOADING}, {RES_FAIL}, {RES_CLEAR} };

void scene_Title()
{
	//로직 - 화면버퍼 업데이트
	buffer_UpdateScene(Scene[TITLE].memory);
		
	//입력 - 스페이스바 누르면 게임 진입
	if ((GetAsyncKeyState(VK_SPACE) & 0x8001))
	{
		currentScene = LOADING;
		return;
	}
}


//스테이지 로딩 함수 
void scene_Loading()
{
	//로직 - 화면버퍼 업데이트
	buffer_UpdateScene(Scene[LOADING].memory);
	
	//스테이지 데이터 불러오기

	return;
}

void scene_ResFail()
{
	//로직 - 화면버퍼 업데이트
	buffer_UpdateScene(Scene[RES_FAIL].memory);
	
	//입력 - 스페이스바 : 게임 재시작 | ESC : 게임 종료
	if ((GetAsyncKeyState(VK_SPACE) & 0x8001))
	{
		//currentScene = LOADING;
		return;
	}
}

void scene_ResClear()
{
	//로직 - 화면버퍼 업데이트
	buffer_UpdateScene(Scene[RES_CLEAR].memory);

	//입력 - 스페이스바 : 다음 스테이지
	if ((GetAsyncKeyState(VK_SPACE) & 0x8001))
	{
		//currentScene =
		return;
	}
}

void scene_Game()
{
	int frameResult = 0; //processFrame();

	switch (frameResult)
	{
	case PLAY:
		return;
	case RES_FAIL:
		currentScene = RES_FAIL;
		return;
	case RES_CLEAR:
		currentScene = RES_CLEAR;
		return;
	default:
		return;
	}
}