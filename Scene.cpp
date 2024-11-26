#include <stdio.h>
#include <Windows.h>

#include "ScreenSetting.h"
#include "Scene.h"
#include "Buffer.h"

extern char ScreenBuffer[dfSCREEN_HEIGHT][dfSCREEN_WIDTH];
extern int currentScene;
extern bool LoadData;

const char* FILE_TITLE = "Title.txt";
const char* FILE_LOADING = "Loading.txt";
const char* FILE_RES_FAIL = "ResFail.txt";
const char* FILE_RES_CLEAR = "ResClear.txt";


void scene_Title()
{
	if (LoadData)
	{
		FILE* fp = nullptr;
		fopen_s(&fp, FILE_TITLE, "r");
		if (fp == nullptr) return;

		buffer_GetSceneData(fp);
		fclose(fp);
		LoadData = false;
	}


	if ((GetAsyncKeyState(VK_SPACE) & 0x8001))
	{
		currentScene = LOADING;
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
	case RES_CLEAR :
		currentScene = RES_CLEAR;
		return;
	default:
		return;
	}
}

//스테이지 로딩 함수 (로딩화면 그리기 + 데이터 불러오기)
void scene_Loading(const char* StageFileName)
{
	//로딩화면 그리기
	FILE* fp = nullptr;
	fopen_s(&fp, FILE_LOADING, "r");
	if (fp == nullptr) return;

	buffer_GetSceneData(fp);
	fclose(fp);

	//스테이지 데이터 불러오기
	fopen_s(&fp, StageFileName, "r");
	if (fp == nullptr) return;

	return;
}

void scene_ResFail()
{

}

void scene_ResClear()
{

}

