#pragma once

#ifndef __SCENE_H__
#define __SCENE_H__

typedef int SCENE;

enum SCENE_NUM
{
	PLAY = 0,
	LOADING = 1,
	TITLE = 2,
	RES_FAIL = 3,
	RES_CLEAR = 4,
	EXIT = 5
};

void scene_Game();
void scene_Loading(const char* StageFileName);
void scene_Title();
void scene_ResClear();
void scene_ResFail();

#endif