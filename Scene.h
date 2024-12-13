#pragma once

#ifndef __SCENE_H__
#define __SCENE_H__

#define NUM_OF_STATIC_SCENES 5

enum SceneType
{
	//Static Sceness
	TITLE = 0,
	LOADING = 1,
	STAGE_CLEAR = 2,
	GAME_OVER = 3,
	GAME_ALLCLEAR = 4,

	//Dynamic Scene
	PLAY,

	//Exit
	EXIT
};

struct StaticScene
{
	SceneType type;
	char memory[dfSCREEN_HEIGHT][dfSCREEN_WIDTH] = { 0 };
};

extern StaticScene staticScene[NUM_OF_STATIC_SCENES];
void scene_ConvertTo(SceneType scene);
void scene_Title();
void scene_Loading();
void scene_StageClear();
void scene_GameOver();
void scene_GameAllClear();
void scene_PlayGame();

#endif