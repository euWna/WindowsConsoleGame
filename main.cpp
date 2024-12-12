#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <windows.h>

//화면 출력
#include "ScreenSetting.h"
#include "Console.h"
#include "Buffer.h"
char ScreenBuffer[dfSCREEN_HEIGHT][dfSCREEN_WIDTH];
void RenderScreen(void);

//게임 데이터
#include "GameStage.h"
#include "MovePattern.h"
#include "DataParsing.h"
void InitGame(void);

//씬 제어
#include "Scene.h"
SceneType currentScene;
int currentStage;

//프레임 제어 (50fps)
const DWORD FRAME_TIME = 20;
DWORD t_Standard;
int t_gap;
//void CheckFPS(void);

//게임 오브젝트
#include "Player.h"
#include "Enemy.h"


#pragma comment (lib, "winmm") //timeGetTime() 라이브러리
int main(void)
{
	timeBeginPeriod(1);
	DWORD t_ProgramStart = timeGetTime();
	InitGame();
	cs_Initial();

	while (true)
	{
		//buffer_Clear();
		//cs_ClearScreen();
		
		//로직부
		DWORD t_LogicStart = timeGetTime();
		switch (currentScene)
		{
		///Game Play
		case PLAY:
			scene_PlayGame();
			break;

		///Static Scenes
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

enum GameSetting
{
	Init,
	Data_SceneMgr,
	Data_StageMgr,
	Data_Player,
	Data_EnemyMgr,
	Finish
};

void InitGame()
{
	static int nowSetting = Init;

	switch (nowSetting)
	{
	case Init:
		currentScene = LOADING;
		break;

	//SceneMgr 데이터 파싱 -> Scene별 데이터 저장
	case Data_SceneMgr: 
		parseData_SceneMgr();
		break;

	//StageMgr 데이터 파싱 -> Stage별 파일경로 저장
	case Data_StageMgr:
		parseData_StageMgr();
		break;

	//Player 데이터 파싱 및 저장
	case Data_Player:
		parseData_Player();
		break;

	//EnemyMgr 데이터 파싱 -> Enemy type별 데이터 및 저장
	case Data_EnemyMgr:
		parseData_EnemyMgr();
		break;

	case Finish:
		currentScene = TITLE;
		break;

	default:
		return;
	}

	nowSetting++;
}

void RenderScreen(void)
{
	int iBufCnt;

	for (iBufCnt = 0; iBufCnt < dfSCREEN_HEIGHT; iBufCnt++)
	{
		cs_MoveCursor(0, iBufCnt);
		printf(ScreenBuffer[iBufCnt]);
	}
}


////프레임 제어 예시
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
