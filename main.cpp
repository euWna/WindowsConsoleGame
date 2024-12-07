#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <windows.h>

#include "Console.h"
#include "Buffer.h"
#include "Player.h"
#include "Enemy.h"
#include "Scene.h"
#include "ScreenSetting.h"

//게임 데이터
const char* FILE_DIRECTORY = "Data/";
const char* FILE_SCENE = "Data/SceneInfo.txt";
const char* FILE_STAGE = "Data/StageInfo.txt";
const char* FILE_PLAYER = "Data/PlayereInfo.txt";
const char* FILE_ENEMY = "Data/EnemyInfo.txt";
const char* FILE_ENEMYSHOT = "Data/EnemyShotInfo.txt";
void LoadGameData(void);

//씬 제어
SCENE_NUM currentScene;
int currentStage;

//화면 출력
char ScreenBuffer[dfSCREEN_HEIGHT][dfSCREEN_WIDTH];
void RenderScreen(void);

//프레임 제어 (50fps)
static const DWORD FRAME_TIME = 20;
static DWORD t_Standard;
static int t_gap;
//void CheckFPS(void);

//게임 오브젝트
Player player;
PlayerShot pShot[dfSCREEN_WIDTH];
Enemy enemy[dfSCREEN_HEIGHT * dfSCREEN_WIDTH];
EnemyShot eShot[dfSCREEN_HEIGHT * dfSCREEN_WIDTH];


#pragma comment (lib, "winmm") //timeGetTime() 라이브러리
int main(void)
{
	DWORD t_ProgramStart = timeGetTime();
	int i = 0;
	//게임 초기화
	timeBeginPeriod(1);
	LoadGameData();
	currentScene = TITLE; //초기화면 타이틀로 세팅
	cs_Initial();

	while (true)
	{
		//buffer_Clear();
		//cs_ClearScreen();
		
		//로직부
		DWORD t_LogicStart = timeGetTime();
		switch (currentScene)
		{
		//Game Play
		case PLAY:
			scene_Game();
			break;

		//Static Scenes
		case TITLE:
			scene_Title();
			break;

		case LOADING:
			scene_Loading();
			//스테이지 로딩 함수
			//Sleep(1000);
			break;

		case RES_FAIL:
			scene_ResFail();
			break;
		
		case RES_CLEAR:
			scene_ResClear();
			break;
		
		/*
		case EXIT:
			Sleep(1500);
			timeEndPeriod(1);
			return 0;
		*/

		default:
			return 0;
		}

		//프레임 제어
		///실제 경과 시간 업데이트
		DWORD t_Elapsed = timeGetTime() - t_ProgramStart;
		///프레임 기준 시간 업데이트
		t_Standard += FRAME_TIME;
		///경과 시간 & 기준 시간 차이 계산
		t_gap += (t_Elapsed - t_Standard);

		if (t_gap < 0)
		{
			//프레임 전환 대기
			Sleep(abs(t_gap));
		}
		else if (t_gap >= FRAME_TIME)
		{
			//프레임 스킵
			t_gap -= FRAME_TIME;
			continue;
		}

		//렌더부
		RenderScreen();
		//CheckFPS();
	}
}


//static int iFPSCnt = 0;
//
//void CheckFPS()
//{
//	static DWORD Tick = timeGetTime();
//
//	iFPSCnt++;
//	if (timeGetTime() - Tick >= 1000)
//	{
//		//printf("FPS %d \n", iFPSCnt);
//		iFPSCnt = 0;
//		//Tick = timeGetTime();
//		Tick += 1000;
//	}
//}

void RenderScreen(void)
{
	int iBufCnt;

	for (iBufCnt = 0; iBufCnt < dfSCREEN_HEIGHT; iBufCnt++)
	{
		cs_MoveCursor(0, iBufCnt);
		printf(ScreenBuffer[iBufCnt]);
	}
}

void LoadData_Player(void)
{
	FILE* fp = nullptr;
	fopen_s(&fp, FILE_SCENE, "r");
	if (fp == nullptr)
	{
		printf("Player Data does not exist.\n");
		return;
	}


}


void LoadData_Scene(void)
{
	FILE* fp = nullptr;
	fopen_s(&fp, FILE_SCENE, "r");
	if (fp == nullptr)
	{
		printf("Scene Data does not exist.\n");
		return;
	}

	for (int iCnt = 0; iCnt < NUM_OF_SCENE; iCnt++)
	{
		char sceneNum[6]; 	//SCENE_NUM 참조
		char fileName[MAX_NAME_LEN];

		//Scene Num
		fread(&sceneNum, 5, 1, fp);
		sceneNum[5] = '\0';
		int iSceneNum = atoi(sceneNum);

		//공백 제거
		fgetc(fp);

		//Scene Name
		fgets(fileName, MAX_NAME_LEN, fp);
		//개행문자 제거
		int len = strlen(fileName) - 1;
		if (fileName[len] == '\n')
			fileName[len] = '\0';

		char DirFileName[MAX_NAME_LEN * 2];
		strcpy_s(DirFileName, FILE_DIRECTORY);
		strcat_s(DirFileName, fileName);

		scene_LoadSceneData(DirFileName, Scene[atoi(sceneNum)].memory);
	}
	fclose(fp);
}


void LoadGameData(void)
{
	//플레이어 데이터 로드
	LoadData_Player();
	//씬 데이터 로드
	LoadData_Scene();

}


////프레임 제어 예시 함수
//int main()
//{
//	timeBeginPeriod(1);
//	DWORD OldTick = timeGetTime();
//
//	while (true)
//	{
//		//키
//		Sleep(2);
//
//		//로직
//		Sleep(4);
//
//		//대기
//		int t = timeGetTime() - OldTick;
//		int sleeptick = 20 - t;
//		if (sleeptick > 0)
//		{
//			Sleep(sleeptick);
//		}
//		//OldTick = timeGetTime();
//		OldTick += 20;
//
//		//렌더
//		Sleep(6);
//		CheckFPS();
//	}
//
//	timeEndPeriod(1);
//}