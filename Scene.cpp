#include <stdio.h>
#include <windows.h>

#include "ScreenSetting.h"
#include "Scene.h"
#include "Buffer.h"

extern SCENE_NUM currentScene;

SCENE Scene[4] = { {TITLE}, {LOADING}, {RES_FAIL}, {RES_CLEAR} };

void scene_Title()
{
	//���� - ȭ����� ������Ʈ
	buffer_UpdateScene(Scene[TITLE].memory);
		
	//�Է� - ����Ű ������ ���� ����
	if ((GetAsyncKeyState(VK_RETURN) & 0x8001))
	{
		currentScene = LOADING;
		return;
	}
}


//�������� �ε� �Լ� 
void scene_Loading()
{
	//���� - ȭ����� ������Ʈ
	buffer_UpdateScene(Scene[LOADING].memory);
	
	//�������� ������ �ҷ�����

	return;
}

void scene_ResFail()
{
	//���� - ȭ����� ������Ʈ
	buffer_UpdateScene(Scene[RES_FAIL].memory);
	
	//�Է� - ����Ű : ���� �����
	if ((GetAsyncKeyState(VK_RETURN) & 0x8001))
	{
		currentScene = TITLE;
		return;
	}
}

void scene_ResClear()
{
	//���� - ȭ����� ������Ʈ
	buffer_UpdateScene(Scene[RES_CLEAR].memory);

	//�Է� - �����̽��� : ���� ��������
	if ((GetAsyncKeyState(VK_SPACE) & 0x8001))
	{
		//currentScene =
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
		Sleep(2000);
		return;
	case RES_CLEAR:
		currentScene = RES_CLEAR;
		return;
	default:
		return;
	}
}