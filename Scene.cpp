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
	//ȭ����� ������Ʈ
	buffer_UpdateScene(Scene[TITLE].memory);
		
	//�����̽��� ������ ���� ����
	if ((GetAsyncKeyState(VK_SPACE) & 0x8001))
	{
		currentScene = LOADING;
		return;
	}
}


//�������� �ε� �Լ� 
void scene_Loading()
{
	//ȭ����� ������Ʈ
	buffer_UpdateScene(Scene[LOADING].memory);
	
	//�������� ������ �ҷ�����

	return;
}

void scene_ResFail()
{

	buffer_UpdateScene(Scene[RES_FAIL].memory);
	//sleep �ʿ�
}

void scene_ResClear()
{
	buffer_UpdateScene(Scene[RES_CLEAR].memory);
	//sleep �ʿ�
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