#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <windows.h>

//화면 출력
#include "Console.h"
#include "Buffer.h"
char ScreenBuffer[dfSCREEN_HEIGHT + 1][dfSCREEN_WIDTH];
void RenderScreen(void);

//게임 데이터
#include "MovePattern.h"
#include "DataParsing.h"
enum GameSetting;
void LoadGameData(void);

//게임 로직
#include "GameStage.h"

//씬 제어
#include "Scene.h"
SceneType currentScene;
int currentStage;

//프레임 제어 (10fps)
const DWORD FRAME_TIME = 100;
DWORD t_Elapsed;
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
	cs_Initial();
	LoadGameData();

	while (true)
	{
		buffer_Clear();
		
		//로직 (씬 제어)
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

		case GAME_OVER:
			scene_GameOver();
			break;
		
		case STAGE_CLEAR:
			scene_StageClear();
			break;
		
		case GAME_ALLCLEAR:
			scene_GameAllClear();
			break;
		
		case EXIT:
			timeEndPeriod(1);
			return 0;

		default:
			timeEndPeriod(1);
			return 0;
		}

		//프레임 제어
		///실제 경과 시간 업데이트
		t_Elapsed = timeGetTime() - t_ProgramStart;
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
	Finish,
};

void LoadGameData(void)
{
	static int nowSetting = Init;

	switch (nowSetting)
	{
	case Init:
		scene_ConvertTo(LOADING);
		break;

	//SceneMgr 데이터 파싱 -> Scene별 데이터 저장
	case Data_SceneMgr: 
		parseMgrData_StaticScene();
		break;

	//StageMgr 데이터 파싱 -> Stage별 파일경로 저장
	case Data_StageMgr:
		parseMgrData_Stage();
		break;

	//Player 데이터 파싱 및 저장
	case Data_Player:
		parseMgrData_Player();
		break;

	//EnemyMgr 데이터 파싱 -> Enemy type별 데이터 및 저장
	case Data_EnemyMgr:
		parseMgrData_Enemy();
		break;

	case Finish:
		scene_ConvertTo(TITLE);
		break;

	//Game Restart시  
	default:
		currentStage = 0;
		nowSetting = Finish;
		return;
	}

	nowSetting++;
}

const char* ScreenBorderLine = "================================================================================";
void RenderScreen(void)
{
	int iBufCnt;

	for (iBufCnt = 0; iBufCnt < dfSCREEN_HEIGHT; iBufCnt++)
	{
		cs_MoveCursor(0, iBufCnt);
		printf(ScreenBuffer[iBufCnt]);
	}
	cs_MoveCursor(0, iBufCnt);
	printf(ScreenBorderLine);
}