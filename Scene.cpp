#include <stdio.h>
#include <windows.h>

#include "ScreenSetting.h"
#include "Scene.h"
#include "Buffer.h"

extern SCENE_NUM currentScene;

SCENE Scene[4] = { {TITLE}, {LOADING}, {RES_FAIL}, {RES_CLEAR} };

void scene_Title()
{
	//로직 - 화면버퍼 업데이트
	buffer_UpdateScene(Scene[TITLE].memory);
		
	//입력 - 엔터키 누르면 게임 진입
	if ((GetAsyncKeyState(VK_RETURN) & 0x8001))
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
	
	//입력 - 엔터키 : 게임 재시작
	if ((GetAsyncKeyState(VK_RETURN) & 0x8001))
	{
		currentScene = TITLE;
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
		Sleep(2000);
		return;
	case RES_CLEAR:
		currentScene = RES_CLEAR;
		return;
	default:
		return;
	}
}