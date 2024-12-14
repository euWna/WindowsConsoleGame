#include <stdio.h>
#include <windows.h>

#include "Buffer.h"

StaticScene staticScene[NUM_OF_STATIC_SCENES] 
= { {TITLE}, {LOADING}, {STAGE_CLEAR} ,{GAME_OVER}, {GAME_ALLCLEAR} };


extern SceneType currentScene;
extern int currentStage;
void scene_ConvertTo(SceneType scene)
{
	currentScene = scene;
}

void scene_Title()
{
	//·ÎÁ÷ - È­¸é¹öÆÛ ¾÷µ¥ÀÌÆ®
	buffer_UpdateScene(staticScene[TITLE].memory);
		
	//ÀÔ·Â - ¿£ÅÍÅ° ´©¸£¸é °ÔÀÓ ½ÃÀÛ
	if ((GetAsyncKeyState(VK_RETURN) & 0x8001))
	{
		scene_ConvertTo(LOADING);
		currentStage = 1;
		return;
	}
}

extern void InitGame();
extern void game_InitStage();
//½ºÅ×ÀÌÁö ·Îµù ÇÔ¼ö 
void scene_Loading()
{
	buffer_UpdateScene(staticScene[LOADING].memory);

	//°ÔÀÓ ½ÃÀÛ½Ã ÃÊ±âÈ­
	if (currentStage == 0)
	{
		InitGame();
	}

	//½ºÅ×ÀÌÁö ½ÃÀÛ½Ã ÃÊ±âÈ­
	else
	{
		game_InitStage();
	}

	return;
}

void scene_StageClear()
{
	//·ÎÁ÷ - È­¸é¹öÆÛ ¾÷µ¥ÀÌÆ®
	buffer_UpdateScene(staticScene[STAGE_CLEAR].memory);

	//ÀÔ·Â - ¿£ÅÍÅ° : ´ÙÀ½ ½ºÅ×ÀÌÁö / °ÔÀÓ Á¾·á
	if ((GetAsyncKeyState(VK_RETURN) & 0x8001))
	{
		currentStage++;
		scene_ConvertTo(LOADING);
		return;
	}
}

void scene_GameOver()
{
	//·ÎÁ÷ - È­¸é¹öÆÛ ¾÷µ¥ÀÌÆ®
	buffer_UpdateScene(staticScene[GAME_OVER].memory);
	
	//ÀÔ·Â - ¿£ÅÍÅ° : °ÔÀÓ Àç½ÃÀÛ
	if ((GetAsyncKeyState(VK_RETURN) & 0x8001))
	{
		scene_ConvertTo(TITLE);
		return;
	}
	else if ((GetAsyncKeyState(VK_ESCAPE) & 0x8001))
	{
		scene_ConvertTo(EXIT);
		return;
	}
}

void scene_GameAllClear()
{
	//ë¡œì§ - í™”ë©´ë²„í¼ ì—…ë°ì´íŠ¸
	buffer_UpdateScene(staticScene[GAME_OVER].memory);

	//ì…ë ¥
	///ì—”í„°í‚¤ : ê²Œì„ ì¬ì‹œì‘
	if ((GetAsyncKeyState(VK_RETURN) & 0x8001))
	{
		scene_ConvertTo(TITLE);
		return;
	}
	///ESCí‚¤ : ê²Œì„ ì¢…ë£Œ
	else if ((GetAsyncKeyState(VK_ESCAPE) & 0x8001))
	{
		scene_ConvertTo(EXIT);
		return;
	}
}


extern int processFrame();
void scene_PlayGame()
{
	static int frameResult = PLAY; //processFrame();

	switch (frameResult)
	{
	case PLAY:
		frameResult = processFrame();
		return;
	case GAME_OVER:
		frameResult = PLAY;
		scene_ConvertTo(GAME_OVER);
		//Sleep(2000);
		return;
	case STAGE_CLEAR:
		frameResult = PLAY;
		scene_ConvertTo(STAGE_CLEAR);
		return;
	default:
		return;
	}
}