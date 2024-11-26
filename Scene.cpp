#include <stdio.h>
#include <Windows.h>

#include "ScreenSetting.h"
#include "Scene.h"
#include "Buffer.h"

extern char szScreenBuffer[dfSCREEN_HEIGHT][dfSCREEN_WIDTH];
extern int currentScene;

const char* FILE_TITLE = "Title.txt";
const char* FILE_LOADING = "Loading.txt";
const char* FILE_RES_FAIL = "ResFail.txt";
const char* FILE_RES_CLEAR = "ResClear.txt";


void scene_Title()
{
	FILE* fp = nullptr;
	fopen_s(&fp, FILE_TITLE, "r");
	if (fp == nullptr) return;
	
	buffer_GetSceneData(fp);
	fclose(fp);

	if ((GetAsyncKeyState(VK_SPACE) & 0x8001))
	{
		currentScene = LOADING;
		return;
	}
}

void scene_Game()
{
	player_Control
}

void scene_Loading()
{
	FILE* fp = nullptr;
	fopen_s(&fp, FILE_LOADING, "r");
	if (fp == nullptr) return;

	buffer_GetSceneData(fp);
	fclose(fp);
	return;
}

void scene_ResFail()
{

}

void scene_ResClear()
{

}

