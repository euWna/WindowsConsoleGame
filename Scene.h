#pragma once

#ifndef __SCENE_H__
#define __SCENE_H__

#define NUM_OF_SCENE 4

enum SceneType
{
	TITLE,
	LOADING,
	RES_FAIL,
	RES_CLEAR,
	PLAY,
	//EXIT
};

struct SCENE
{
	SceneType type;
	char memory[dfSCREEN_HEIGHT][dfSCREEN_WIDTH] = { 0 };
};

extern SCENE Scene[4];
void scene_PlayGame();
void scene_Loading();
void scene_Title();
void scene_ResClear();
void scene_ResFail();

#endif