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
	//���� - ȭ����� ������Ʈ
	buffer_UpdateScene(staticScene[TITLE].memory);
		
	//�Է� - ����Ű ������ ���� ����
	if ((GetAsyncKeyState(VK_RETURN) & 0x8001))
	{
		scene_ConvertTo(LOADING);
		currentStage = 1;
		return;
	}
}

extern void LoadGameData(void);
extern void game_LoadStage(void);
//�������� �ε� �Լ� 
void scene_Loading()
{
	buffer_UpdateScene(staticScene[LOADING].memory);

	//���� ���۽� �ʱ�ȭ
	if (currentStage == 0)
	{
		LoadGameData();
	}

	//�������� ���۽� �ʱ�ȭ
	else
	{
		game_LoadStage();
	}

	return;
}

void scene_StageClear()
{
	//���� - ȭ����� ������Ʈ
	buffer_UpdateScene(staticScene[STAGE_CLEAR].memory);

	//�Է� - ����Ű : ���� ��������
	if ((GetAsyncKeyState(VK_RETURN) & 0x8001))
	{
		currentStage++;
		scene_ConvertTo(LOADING);
		return;
	}
}

void scene_GameOver()
{
	//���� - ȭ����� ������Ʈ
	buffer_UpdateScene(staticScene[GAME_OVER].memory);
	
	//�Է�
	///����Ű : ���� �����
	if ((GetAsyncKeyState(VK_RETURN) & 0x8001))
	{
		scene_ConvertTo(TITLE);
		return;
	}
	///ESCŰ : ���� ����
	else if ((GetAsyncKeyState(VK_ESCAPE) & 0x8001))
	{
		scene_ConvertTo(EXIT);
		return;
	}
}

void scene_GameAllClear()
{
	//���� - ȭ����� ������Ʈ
	buffer_UpdateScene(staticScene[GAME_OVER].memory);

	//�Է�
	///����Ű : ���� �����
	if ((GetAsyncKeyState(VK_RETURN) & 0x8001))
	{
		scene_ConvertTo(TITLE);
		return;
	}
	///ESCŰ : ���� ����
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