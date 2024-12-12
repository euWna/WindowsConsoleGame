#include <stdio.h>
#include <windows.h>

#include "ScreenSetting.h"
#include "Scene.h"
#include "Buffer.h"

extern SceneType currentScene;
extern int currentStage;
extern void InitGame();
extern void game_InitStage();


SCENE Scene[4] = { {TITLE}, {LOADING}, {RES_FAIL}, {RES_CLEAR} };

void scene_Title()
{
	//로직 - 화면버퍼 업데이트
	buffer_UpdateScene(Scene[TITLE].memory);
		
	//입력 - 엔터키 누르면 게임 진입
	if ((GetAsyncKeyState(VK_RETURN) & 0x8001))
	{
		currentScene = LOADING;
		currentStage = 1;
		return;
	}
}


//스테이지 로딩 함수 
void scene_Loading()
{
	//로직 - 화면버퍼 업데이트
	buffer_UpdateScene(Scene[LOADING].memory);

	//게임 시작시 초기화
	if (currentStage == 0)
	{
		InitGame();
	}

	//스테이지 시작시 초기화
	else
	{
		game_InitStage();
	}

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

	//입력 - 엔터키 : 다음 스테이지
	if ((GetAsyncKeyState(VK_RETURN) & 0x8001))
	{
		currentStage++;
		currentScene = LOADING;
		return;
	}
}

void scene_PlayGame()
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