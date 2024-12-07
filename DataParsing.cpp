#include <stdio.h>
#include <windows.h>

#include "Player.h"
#include "Enemy.h"
#include "ScreenSetting.h"
#include "Scene.h"
#include "GameObjects.h"
#include "DataFiles.h"

//�Ľ� �Լ�
void parseData_Player(void);
void parseData_Enemy(void);
void parseData_Scenes(void);
void parseData_Scene(const char* fileName, char memory[][dfSCREEN_WIDTH]);

//�Ľ� �����Լ�
char* getFileDataToBuffer(const char* fileName);
size_t getFileSize(FILE* fp);


void parseData_Player(void)
{
	//�Ľ��� ������
	char* pSprite = &playerSetting.SPRITE;
	char* pShotSprite = &playerSetting.SHOT_SPRITE;
	int* pMaxLife = &playerSetting.MAX_LIFE;

	//������ �ҷ�����
	char* buffer = getFileDataToBuffer(DATA_FILE_NAME__PLAYER);

	//�Ľ�
	char* bufferPtr = buffer;

	///1. Player Sprite (char)
	*pSprite = *bufferPtr;

	while (*bufferPtr != '\n') bufferPtr++;
	bufferPtr++;

	///2. Player Shot Sprite (char)
	*pShotSprite = *bufferPtr++;

	while (*bufferPtr != '\n') bufferPtr++;
	bufferPtr++;

	///3. Player Max Life (int)
	char* endOfInt = bufferPtr;
	while (*endOfInt != '\n') endOfInt++;
	*endOfInt = '\0';
	*pMaxLife = atoi(bufferPtr);

	//fclose(fp);
	free(buffer);
}

void parseData_Enemy(void)
{

}

void parseData_Scenes(void)
{
	//�Ľ��� ������
	char scFileDir[MAX_FILE_LEN];
	int scNum;
	char scFileName[MAX_FILE_LEN];

	//������ �ҷ�����
	char* buffer = (char*)getFileDataToBuffer(DATA_FILE_NAME__SCENE);

	//�Ľ�
	char* bufferPtr1 = buffer;
	char* bufferPtr2 = buffer;

	//1. File Directory
	while (*bufferPtr2 != '\n') bufferPtr2++;
	*(bufferPtr2++) = '\0';
	strcpy_s(scFileDir, bufferPtr1);

	bufferPtr1 = bufferPtr2;

	for (int iCnt = 0; iCnt < NUM_OF_SCENE; iCnt++)
	{
		///2. Scene Num
		while (*bufferPtr2 != ' ') bufferPtr2++;
		*(bufferPtr2++) = '\0';
		scNum = atoi(bufferPtr1);

		bufferPtr1 = bufferPtr2;

		///3. Scene Name
		while (*bufferPtr2 != '\n') bufferPtr2++;
		*(bufferPtr2++) = '\0';
		strcpy_s(scFileName, bufferPtr1);

		bufferPtr1 = bufferPtr2;

		////���� Scene �Ľ�
		char scFilePath[MAX_FILE_LEN * 2];
		strcpy_s(scFilePath, scFileDir);
		strcat_s(scFilePath, scFileName);

		parseData_Scene(scFilePath, Scene[scNum].memory);
	}

	free(buffer);
}

void parseData_Scene(const char* fileName, char memory[][dfSCREEN_WIDTH])
{
	//�Ľ��� ������ �ҷ�����
	char* buffer = getFileDataToBuffer(fileName);
	
	//�Ľ�
	char* bufferPtr1 = buffer;
	char* bufferPtr2 = buffer;

	///�� �� ���� ������ ����Ʈ �ι��ڷ� ��ȯ
	for (int iBufCnt = 0; iBufCnt < dfSCREEN_HEIGHT; iBufCnt++)
	{
		while (*bufferPtr2 != '\n') bufferPtr2++;
		*(bufferPtr2++) = '\0';
		strcpy_s(memory[iBufCnt],bufferPtr1);
		bufferPtr1 = bufferPtr2;
	}
	free(buffer);
}

//////////////////////////////////////////////////

char* getFileDataToBuffer(const char* fileName)
{
	FILE* fp = nullptr;
	char filePath[MAX_FILE_LEN];
	strcpy_s(filePath, DATA_FILE_PATH);
	strcat_s(filePath, fileName);

	fopen_s(&fp, filePath, "r");
	if (fp == nullptr)
	{
		printf("%s File does not exist.\n", fileName);
		return nullptr;
	}

	size_t fileSize = getFileSize(fp);
	char* buffer = (char*)malloc(fileSize + 1);
	fread(buffer, fileSize, 1, fp);

	fclose(fp);
	return buffer;
}


size_t getFileSize(FILE* fp)
{
	size_t file_size;

	fseek(fp, 0, SEEK_END);
	file_size = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	return file_size;
}





