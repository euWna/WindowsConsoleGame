#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <Windows.h>

#include "Console.h"
#include "Buffer.h"
#include "Player.h"
#include "Enemy.h"
#include "Scene.h"
#include "ScreenSetting.h"

const char* FILE_SCENE = "SceneInfo.txt";
const char* FILE_STAGE = "StageInfo.txt";
const char* FILE_PLAYER = "PlayereInfo.txt";
const char* FILE_ENEMY = "EnemyInfo.txt";
const char* FILE_ENEMYSHOT = "EnemyShotInfo.txt";

SCENE_NUM currentScene;
int currentStage;
//--------------------------------------------------------------------
// 화면 깜빡임을 없애기 위한 화면 버퍼.
// 게임이 진행되는 상황을 매번 화면을 지우고 비행기 찍고, 지우고 찍고,
// 하게 되면 화면이 깜빡깜빡 거리게 된다.
//
// 그러므로 화면과 똑같은 크기의 메모리를 할당한 다음에 화면에 바로 찍지않고
// 메모리(버퍼)상에 그림을 그리고 메모리의 화면을 그대로 화면에 찍어준다.
//
// 이렇게 해서 화면을 매번 지우고, 그리고, 지우고, 그리고 하지 않고
// 메모리(버퍼)상의 그림을 화면에 그리는 작업만 하게 되어 깜박임이 없어진다.
//
// 버퍼의 각 줄 마지막엔 NULL 을 넣어 문자열로서 처리하며, 
// 한줄한줄을 printf 로 찍어나갈 것이다.
//
// for ( N = 0 ~ height )
// {
// 	  cs_MoveCursor(0, N);
//    printf(szScreenBuffer[N]);
// }
//
// 줄바꿈에 printf("\n") 을 쓰지 않고 커서좌표를 이동하는 이유는
// 화면을 꽉 차게 출력하고 줄바꿈을 하면 2칸이 내려가거나 화면이 밀릴 수 있으므로
// 매 줄 출력마다 좌표를 강제로 이동하여 확실하게 출력한다.
//--------------------------------------------------------------------
char ScreenBuffer[dfSCREEN_HEIGHT][dfSCREEN_WIDTH];

Player player;
PlayerShot pShot[dfSCREEN_WIDTH];
Enemy enemy[dfSCREEN_HEIGHT * dfSCREEN_WIDTH];
EnemyShot eShot[dfSCREEN_HEIGHT * dfSCREEN_WIDTH];

void LoadGameData(void);
void RenderScreen(void);


#pragma comment (lib, "winmm") //timeGetTime() 라이브러리
int main(void)
{
	//게임 초기화
	timeBeginPeriod(1);
	LoadGameData();
	currentScene = TITLE; //초기화면 타이틀로 세팅
	cs_Initial();
	
	//프레임 로직
	while (true)
	{
		//buffer_Clear();
		//cs_ClearScreen();
		
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
			Sleep(1000);
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

		//Render
		RenderScreen();
	}

	return 0;
}

void LoadGameData(void)
{
	FILE* fp = nullptr;
	//플레이어 데이터 로드
	//fclose(fp);

	//씬 데이터 로드
	fopen_s(&fp, FILE_SCENE, "r");
	if (fp == nullptr) return;

	for (int iCnt = 0; iCnt < NUM_OF_SCENE; iCnt++)
	{
		char sceneIdx; 	//SCENE_NUM 참조
		char fileName[MAX_NAME_LEN];
		fread(&sceneIdx, 1, 1, fp);
		fgetc(fp);
		fgets(fileName, MAX_NAME_LEN, fp);
		fileName[strlen(fileName)-1] = '\0'; //개행문자 제거
		scene_LoadSceneData(fileName, Scene[sceneIdx-'0'].memory);
	}
	fclose(fp);
	


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

//--------------------------------------------------------------------
// GetAsyncKeyState(int iKey)  #include <Windows.h>
//
// 윈도우 API 로 키보드가 눌렸는지를 확인한다.
// 인자로 키보드 버튼에 대한 디파인 값을 넣으면 해당 키가 눌렸는지 (눌렸던적이 있는지) 를 확인 해준다.
// 모든 키에대한 확인이 가능하고, 논블럭 체크가 되므로 게임에서도 쓰기 좋다.
//
// Virtual-Key Codes
//
// VK_SPACE / VK_ESCAPE / VK_LEFT / VK_UP / 키보드 문자는 대문자 아스키 코드와 같음.
// winuser.h 파일에 위와 같이 디파인 되어 있다.
//
//
// GetAsyncKeyState(VK_LEFT) 호출시 결과값은
//
// 0x0001  > *이전 체크 이후 눌린적이 있음
// 0x8000  > 지금 눌려있음
// 0x8001  > *이전 체크 이후 눌린적도 있고 지금도 눌려 있음
//
// * 이전 체크라는건 이전에 GetAsyncKeyState 를 호출한 때를 말 한다.
// 
// 10프레임 짜리 게임이라면 1초에 10회의 키 체크를 하게 되므로 체크 간격은 20ms 가 된다.
// 빠른 커맨드 입력이 필요한 게임에서는 20ms 이내에 여러개의 키입력이 있다면 체크하지 못하는 키 입력이 발생 할 수 있다.
// 그래서 0x0001 비트에 대한 처리도 필요하다.
//