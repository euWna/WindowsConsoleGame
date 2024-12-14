#include <stdio.h>
#include <windows.h>

#include "Buffer.h"
#include "Scene.h"

StaticScene staticScene[NUM_OF_STATIC_SCENES] 
= { {TITLE}, {LOADING}, {STAGE_CLEAR} ,{GAME_OVER}, {GAME_ALLCLEAR} };


extern SceneType currentScene;
extern int currentStage;
void scene_ConvertTo(SceneType scene)
{
	currentScene = scene;
}

void scene_Title()
{
	//로직 - 화면버퍼 업데이트
	buffer_UpdateScene(staticScene[TITLE].memory);
		
	//입력 - 엔터키 누르면 게임 시작
	if ((GetAsyncKeyState(VK_RETURN) & 0x8001))
	{
		scene_ConvertTo(LOADING);
		currentStage = 1;
		return;
	}
}

extern void LoadGameData(void);
extern void game_LoadStage(void);
//스테이지 로딩 함수 
void scene_Loading()
{
	buffer_UpdateScene(staticScene[LOADING].memory);

	//게임 시작시 초기화
	if (currentStage == 0)
	{
		LoadGameData();
	}

	//스테이지 시작시 초기화
	else
	{
		game_LoadStage();
	}

	return;
}

void scene_StageClear()
{
	//로직 - 화면버퍼 업데이트
	buffer_UpdateScene(staticScene[STAGE_CLEAR].memory);

	//입력 - 엔터키 : 다음 스테이지
	if ((GetAsyncKeyState(VK_RETURN) & 0x8001))
	{
		currentStage++;
		scene_ConvertTo(LOADING);
		return;
	}
}

void scene_GameOver()
{
	//로직 - 화면버퍼 업데이트
	buffer_UpdateScene(staticScene[GAME_OVER].memory);
	
	//입력
	///엔터키 : 게임 재시작
	if ((GetAsyncKeyState(VK_RETURN) & 0x8001))
	{
		scene_ConvertTo(TITLE);
		return;
	}
	///ESC키 : 게임 종료
	else if ((GetAsyncKeyState(VK_ESCAPE) & 0x8001))
	{
		scene_ConvertTo(EXIT);
		return;
	}
}

void scene_GameAllClear()
{
	//로직 - 화면버퍼 업데이트
	buffer_UpdateScene(staticScene[GAME_OVER].memory);

	//입력
	///엔터키 : 게임 재시작
	if ((GetAsyncKeyState(VK_RETURN) & 0x8001))
	{
		scene_ConvertTo(TITLE);
		return;
	}
	///ESC키 : 게임 종료
	else if ((GetAsyncKeyState(VK_ESCAPE) & 0x8001))
	{
		scene_ConvertTo(EXIT);
		return;
	}
}


extern int processFrame();
void scene_PlayGame()
{
	static int frameResult = PLAY; //processFrame();

	switch (frameResult)
	{
	case PLAY:
		frameResult = processFrame();
		return;
	case GAME_OVER:
		frameResult = PLAY;
		scene_ConvertTo(GAME_OVER);
		//Sleep(2000);
		return;
	case STAGE_CLEAR:
		frameResult = PLAY;
		scene_ConvertTo(STAGE_CLEAR);
		return;
	default:
		return;
	}
}