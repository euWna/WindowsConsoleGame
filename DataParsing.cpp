#include <stdio.h>
#include <windows.h>

#include "Player.h"
#include "Enemy.h"
#include "Scene.h"
#include "ScreenSetting.h"
#include "GameObjects.h"
#include "DataFiles.h"


size_t getFileSize(FILE* fp)
{
	size_t file_size;

	fseek(fp, 0, SEEK_END);
	file_size = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	return file_size;
}


void parseData_Player(void)
{
	//데이터 불러오기
	FILE* fp = nullptr;
	fopen_s(&fp, FILE_PLAYER, "r");
	if (fp == nullptr)
	{
		printf("Player Data does not exist.\n");
		return;
	}

	size_t fileSize = getFileSize(fp);
	char* buffer = (char*)malloc(fileSize + 1);

	fread(buffer, fileSize, 1, fp);

	//파싱
	char* bufferPtr = buffer;
	///1. Player Sprite (char)
	playerSetting.SPRITE = *(bufferPtr++);

	while (*bufferPtr != '\n') bufferPtr++;

	///2. Player Shot Sprite (char)
	playerSetting.SHOT_SPRITE = *(bufferPtr++);

	while (*bufferPtr != '\n') bufferPtr++;

	///3. Player Max Life (int)
	char* endOfInt = bufferPtr;
	while (*endOfInt != '\n') endOfInt++;
	*endOfInt = '\0';
	playerSetting.MAX_LIFE = atoi(bufferPtr);

	fclose(fp);

}

void parseData_Enemy(void)
{

}

void parseData_Scene(const char* fileName, char memory[][dfSCREEN_WIDTH])
{
	FILE* fp = nullptr;
	fopen_s(&fp, fileName, "r");
	if (fp == nullptr)
	{
		printf("%s Scene Data does not exist.\n", fileName);
		return;
	}

	fread(memory, SCREEN_SIZE, 1, fp);
	for (int iBufCnt = 0; iBufCnt < dfSCREEN_HEIGHT; iBufCnt++)
	{
		memory[iBufCnt][dfSCREEN_WIDTH - 1] = '\0';
	}

	fclose(fp);
}

void parseData_Scenes(void)
{
	FILE* fp = nullptr;
	fopen_s(&fp, FILE_SCENE, "r");
	if (fp == nullptr)
	{
		printf("Scene List Data does not exist.\n");
		return;
	}

	for (int iCnt = 0; iCnt < NUM_OF_SCENE; iCnt++)
	{
		char buffer_SceneNum[6]; 	//SCENE_NUM 참조
		char buffer_FileName[MAX_NAME_LEN];

		//파싱
		///1. Scene Num
		fread(&buffer_SceneNum, 5, 1, fp);
		buffer_SceneNum[5] = '\0';
		int iSceneNum = atoi(buffer_SceneNum);

		////공백 제거
		fgetc(fp);

		///2. Scene Name
		fgets(buffer_FileName, MAX_NAME_LEN, fp);

		////개행문자 제거
		int len = strlen(buffer_FileName) - 1;
		if (buffer_FileName[len] == '\n')
			buffer_FileName[len] = '\0';

		//개별 Scene 파싱
		char DirFileName[MAX_NAME_LEN * 2];
		strcpy_s(DirFileName, FILE_DIRECTORY);
		strcat_s(DirFileName, buffer_FileName);

		parseData_Scene(DirFileName, Scene[atoi(buffer_SceneNum)].memory);
	}
	fclose(fp);
}
