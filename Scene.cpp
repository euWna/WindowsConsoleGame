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
	//�Է�
	int inputKey = cs_GetKeyInput();

	//����	
	switch (inputKey)
	{
	///����Ű �Է� -> ���� ����
	case VK_RETURN:
		currentStage = 1;
		scene_SwitchTo(LOADING);
		break;

	///ESC �Է� -> ���� ����
	case VK_ESCAPE:
		scene_SwitchTo(EXIT);
		break;

	default:
		break;
	}

	//��� -> Title ȭ�� ������Ʈ
	buffer_UpdateScene(staticScene[TITLE].memory);
}



//�������� �ε� �Լ� 
extern void LoadGameData(void);
extern void stage_InitStage(void);
void scene_Loading()
{
	//�Է� x

	//����
	//���� ���۽� �ʱ�ȭ
	if (currentStage == 0)
	{
		LoadGameData();
	}

	//�������� ���۽� �ʱ�ȭ
	else
	{
		stage_InitStage();
	}
	 
	//��� -> Loading ȭ�� ������Ʈ
	buffer_UpdateScene(staticScene[LOADING].memory);

	return;
}

void scene_StageClear()
{
	//�Է�
	int inputKey = cs_GetKeyInput();

	//����	
	switch (inputKey)
	{
	///����Ű �Է� -> ���� ��������
	case VK_RETURN:
		currentStage++;
		scene_SwitchTo(LOADING);
		break;

	///ESC �Է� -> ���� ����
	case VK_ESCAPE:
		scene_SwitchTo(EXIT);
		break;

	default:
		break;
	}

	//��� -> Stage Clear ȭ�� ������Ʈ
	buffer_UpdateScene(staticScene[STAGE_CLEAR].memory);
}

void scene_GameOver()
{
	//�Է�
	int inputKey = cs_GetKeyInput();

	//����	
	switch (inputKey)
	{
	///����Ű �Է� -> ���� �����
	case VK_RETURN:
		currentStage = 0;
		scene_SwitchTo(TITLE);
		break;

	///ESC �Է� -> ���� ����
	case VK_ESCAPE:
		scene_SwitchTo(EXIT);
		break;

	default:
		break;
	}

	//��� -> Game Over ȭ�� ������Ʈ
	buffer_UpdateScene(staticScene[GAME_OVER].memory);
}

void scene_GameAllClear()
{
	//�Է�
	int inputKey = cs_GetKeyInput();

	//����	
	switch (inputKey)
	{
	///����Ű �Է� -> ���� �����
	case VK_RETURN:
		currentStage = 0;
		scene_SwitchTo(TITLE);
		return;

	///ESC �Է� -> ���� ����
	case VK_ESCAPE:
		scene_SwitchTo(EXIT);
		break;

	default:
		break;
	}

	//��� -> Game AllClear ȭ�� ������Ʈ
	buffer_UpdateScene(staticScene[GAME_ALLCLEAR].memory);
}

extern SceneType processFrame(SHORT inputKey);
void scene_PlayGame()
{
	//�Է�
	SHORT inputKey = cs_GetKeyInput();

	//����
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