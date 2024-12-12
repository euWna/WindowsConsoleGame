#include <stdio.h>
#include <windows.h>

#include "ScreenSetting.h"
#include "Scene.h"
#include "Buffer.h"

SCENE Scene[4] = { {TITLE}, {LOADING}, {RES_FAIL}, {RES_CLEAR} };

extern SceneType currentScene;
extern int currentStage;

void scene_ConvertTo(SceneType scene)
{
	currentScene = scene;
}

void scene_Title()
{
	//���� - ȭ����� ������Ʈ
	buffer_UpdateScene(Scene[TITLE].memory);
		
	//�Է� - ����Ű ������ ���� ����
	if ((GetAsyncKeyState(VK_RETURN) & 0x8001))
	{
		scene_ConvertTo(LOADING);
		currentStage = 1;
		return;
	}
}

extern void InitGame();
extern void game_InitStage();
//�������� �ε� �Լ� 
void scene_Loading()
{
	buffer_UpdateScene(Scene[LOADING].memory);

	//���� ���۽� �ʱ�ȭ
	if (currentStage == 0)
	{
		InitGame();
	}

	//�������� ���۽� �ʱ�ȭ
	else
	{
		game_InitStage();
	}

	return;
}

void scene_ResFail()
{
	//���� - ȭ����� ������Ʈ
	buffer_UpdateScene(Scene[RES_FAIL].memory);
	
	//�Է� - ����Ű : ���� �����
	if ((GetAsyncKeyState(VK_RETURN) & 0x8001))
	{
		scene_ConvertTo(TITLE);
		return;
	}
	else if ((GetAsyncKeyState(VK_ESCAPE) & 0x8001))
	{
		scene_ConvertTo(EXIT);
		return;
	}
}

void scene_ResClear()
{
	//���� - ȭ����� ������Ʈ
	buffer_UpdateScene(Scene[RES_CLEAR].memory);

	//�Է� - ����Ű : ���� ��������
	if ((GetAsyncKeyState(VK_RETURN) & 0x8001))
	{
		currentStage++;
		scene_ConvertTo(LOADING);
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
	case RES_FAIL:
		frameResult = PLAY;
		scene_ConvertTo(RES_FAIL);
		//Sleep(2000);
		return;
	case RES_CLEAR:
		frameResult = PLAY;
		scene_ConvertTo(RES_CLEAR);
		return;
	default:
		return;
	}
}