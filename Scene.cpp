#include <stdio.h>
#include <Windows.h>

#include "Scene.h"
#include "Buffer.h"

extern char ScreenBuffer[dfSCREEN_HEIGHT][dfSCREEN_WIDTH];
extern SCENE_NUM currentScene;
extern int currentStage;

SCENE Scene[4] = { {TITLE}, {LOADING}, {RES_FAIL}, {RES_CLEAR} };

void scene_LoadSceneData(const char* fileName, char memory[][dfSCREEN_WIDTH])
{
	FILE* fp = nullptr;
	fopen_s(&fp, fileName, "r");
	if (fp == nullptr) return;

	fread(memory, sizeof(ScreenBuffer), 1, fp);
	for (int iBufCnt = 0; iBufCnt < dfSCREEN_HEIGHT; iBufCnt++)
	{
		memory[iBufCnt][dfSCREEN_WIDTH - 1] = '\0';
	}

	fclose(fp);
	return;
}

void scene_Title()
{
	//화면버퍼 업데이트
	buffer_UpdateScene(Scene[TITLE].memory);
		
	//스페이스바 누르면 게임 진입
	if ((GetAsyncKeyState(VK_SPACE) & 0x8001))
	{
		currentScene = LOADING;
		return;
	}
}


//스테이지 로딩 함수 
void scene_Loading()
{
	//화면버퍼 업데이트
	buffer_UpdateScene(Scene[LOADING].memory);
	
	//스테이지 데이터 불러오기

	return;
}

void scene_ResFail()
{

	buffer_UpdateScene(Scene[RES_FAIL].memory);
	//sleep 필요
}

void scene_ResClear()
{
	buffer_UpdateScene(Scene[RES_CLEAR].memory);
	//sleep 필요
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