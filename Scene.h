#pragma once

#ifndef __SCENE_H__
#define __SCENE_H__

#include "ScreenSetting.h"

#define NUM_OF_SCENE 4
#define MAX_NAME_LEN 55 //50 + 확장자 4 (".txt") + 널문자 1

enum SCENE_NUM
{
	TITLE = 0,
	LOADING = 1,
	RES_FAIL = 2,
	RES_CLEAR = 3,
	PLAY = 4,
	//EXIT = 5
};

struct SCENE
{
	SCENE_NUM num;
	char memory[dfSCREEN_HEIGHT][dfSCREEN_WIDTH] = { 0 };
};

extern SCENE Scene[4];

void scene_LoadSceneData(const char* fileName, char memory[][dfSCREEN_WIDTH]);
void scene_Game();
void scene_Loading();
void scene_Title();
void scene_ResClear();
void scene_ResFail();

#endif