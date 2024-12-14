#include <stdio.h>
#include <windows.h>

#include "Console.h"
#include "Buffer.h"
#include "Scene.h"
#include "GameStage.h"

StaticScene staticScene[NUM_OF_STATIC_SCENES] 
= { {TITLE}, {LOADING}, {STAGE_CLEAR} ,{GAME_OVER}, {GAME_ALLCLEAR} };

SceneType currentScene;

void scene_SwitchTo(SceneType scene)
{
	currentScene = scene;
}

void scene_Title()
{
	//입력
	int inputKey = cs_GetKeyInput();

	//로직	
	switch (inputKey)
	{
	///엔터키 입력 -> 게임 시작
	case VK_RETURN:
		currentStage = 1;
		scene_SwitchTo(LOADING);
		break;

	///ESC 입력 -> 게임 종료
	case VK_ESCAPE:
		scene_SwitchTo(EXIT);
		break;

	default:
		break;
	}

	//출력 -> Title 화면 업데이트
	buffer_UpdateScene(staticScene[TITLE].memory);
}



//스테이지 로딩 함수 
extern void LoadGameData(void);
extern void stage_InitStage(void);
void scene_Loading()
{
	//입력 x

	//로직
	//게임 시작시 초기화
	if (currentStage == 0)
	{
		LoadGameData();
	}

	//스테이지 시작시 초기화
	else
	{
		stage_InitStage();
	}
	 
	//출력 -> Loading 화면 업데이트
	buffer_UpdateScene(staticScene[LOADING].memory);

	return;
}

void scene_StageClear()
{
	//입력
	int inputKey = cs_GetKeyInput();

	//로직	
	switch (inputKey)
	{
	///엔터키 입력 -> 다음 스테이지
	case VK_RETURN:
		currentStage++;
		scene_SwitchTo(LOADING);
		break;

	///ESC 입력 -> 게임 종료
	case VK_ESCAPE:
		scene_SwitchTo(EXIT);
		break;

	default:
		break;
	}

	//출력 -> Stage Clear 화면 업데이트
	buffer_UpdateScene(staticScene[STAGE_CLEAR].memory);
}

void scene_GameOver()
{
	//입력
	int inputKey = cs_GetKeyInput();

	//로직	
	switch (inputKey)
	{
	///엔터키 입력 -> 게임 재시작
	case VK_RETURN:
		currentStage = 0;
		scene_SwitchTo(TITLE);
		break;

	///ESC 입력 -> 게임 종료
	case VK_ESCAPE:
		scene_SwitchTo(EXIT);
		break;

	default:
		break;
	}

	//출력 -> Game Over 화면 업데이트
	buffer_UpdateScene(staticScene[GAME_OVER].memory);
}

void scene_GameAllClear()
{
	//입력
	int inputKey = cs_GetKeyInput();

	//로직	
	switch (inputKey)
	{
	///엔터키 입력 -> 게임 재시작
	case VK_RETURN:
		currentStage = 0;
		scene_SwitchTo(TITLE);
		return;

	///ESC 입력 -> 게임 종료
	case VK_ESCAPE:
		scene_SwitchTo(EXIT);
		break;

	default:
		break;
	}

	//출력 -> Game AllClear 화면 업데이트
	buffer_UpdateScene(staticScene[GAME_ALLCLEAR].memory);
}

extern SceneType processFrame(SHORT inputKey);
void scene_PlayGame()
{
	//입력
	SHORT inputKey = cs_GetKeyInput();

	//로직
	SceneType frameResult = processFrame(inputKey);
	switch (frameResult)
	{
	case PLAY:
		return;

	case GAME_OVER:
		scene_SwitchTo(GAME_OVER);
		return;

	case STAGE_CLEAR:
		if (currentStage == MAX_STAGE)
		{
			scene_SwitchTo(GAME_ALLCLEAR);
		}
		else
		{
			scene_SwitchTo(STAGE_CLEAR);
		}
		return;

	default:
		return;
	}
}