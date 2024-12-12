#include <stdio.h>
#include <windows.h>

#include "ScreenSetting.h"
#include "MovePattern.h"
#include "Enemy.h"
#include "Player.h"
#include "Scene.h"
#include "GameStage.h"
#include "DataParsing.h"

extern char ScreenBuffer[dfSCREEN_HEIGHT][dfSCREEN_WIDTH];
//extern StageMgr stageMgr;

//파일 경로 및 파일명
const char* DATA_PATH = "Data/";
const char* DATA_MGR_FILE_NAME__SCENE = "SceneMgr.txt";
const char* DATA_MGR_FILE_NAME__PLAYER = "PlayerMgr.txt";
const char* DATA_MGR_FILE_NAME__ENEMY = "EnemyMgr.txt";
const char* DATA_MGR_FILE_NAME__STAGE = "StageMgr.txt";
char DATA_FILE_PATHS__STAGE[MAX_STAGE + 1][MAX_FILE_LEN];


//파싱 함수
void parseData_Player(void);
void parseData_EnemyMgr(void);
void parseData_EnemyType(int typeNum, const char* filePath);
void parseData_MovePatternType(int typeNum, const char* filePath);
void parseData_SceneMgr(void);
void parseData_Scene(const char* filePath, char memory[][dfSCREEN_WIDTH]);
void parseData_StageMgr(void);
void parseData_Stage(const char* filePath);

//파싱 보조함수 (파일 스트림)
char* file_WriteDataOnBuffer(const char* fileName);
size_t file_GetSize(FILE* fp);


void parseData_Player(void)
{
	//파싱할 데이터
	char* sprite = &playerSetting._sprite;
	char* shotSprite = &playerSetting._shotSprite;
	int* maxLife = &playerSetting._maxLife;

	//데이터 불러오기
	char* buffer = file_WriteDataOnBuffer(DATA_MGR_FILE_NAME__PLAYER);

	//파싱
	char* bufferPtr = buffer;

	///1. Player Sprite (char)
	*sprite = *bufferPtr;

	while (*bufferPtr != '\n') bufferPtr++;
	bufferPtr++;

	///2. Player Shot Sprite (char)
	*shotSprite = *bufferPtr;
	bufferPtr++;

	while (*bufferPtr != '\n') bufferPtr++;
	bufferPtr++;

	///3. Player Max Life (int)
	char* endOfInt = bufferPtr;
	while (*endOfInt != '\n') endOfInt++;
	*endOfInt = '\0';
	*maxLife = atoi(bufferPtr);

	//fclose(fp);
	free(buffer);
}

void parseData_EnemyMgr(void)
{
	//파싱할 데이터
	char* shotSprite = &(enemySetting._shotSprite);

	int eNumOfTypes;
	char fileDir_Types[MAX_FILE_LEN];
	int eTypeNum;
	char fileName_Types[MAX_FILE_LEN];

	int eNumOfMovePatterns;
	char fileDir_MovePatterns[MAX_FILE_LEN];
	int eMovePatternTypeNum;
	char fileName_MovePatterns[MAX_FILE_LEN];

	//데이터 불러오기
	char* buffer = (char*)file_WriteDataOnBuffer(DATA_MGR_FILE_NAME__ENEMY);

	//파싱
	char* bufferPtr1 = buffer;
	char* bufferPtr2 = buffer;

	///1. Enemy Shot Sprite
	*shotSprite = *bufferPtr2;
	
	bufferPtr1 = ++bufferPtr2;

	///2. Number of Enemy Types
	while (*bufferPtr2 != '\n') bufferPtr2++;
	*bufferPtr2 = '\0';
	eNumOfTypes = atoi(bufferPtr1);

	bufferPtr1 = ++bufferPtr2;

	///3. Enemy Types - File Directory
	while (*bufferPtr2 != '\n') bufferPtr2++;
	*bufferPtr2 = '\0';
	strcpy_s(fileDir_Types, bufferPtr1);

	bufferPtr1 = ++bufferPtr2;

	for (int y = 0; y < eNumOfTypes; y++)
	{
		///4. Enemy Type - Number
		while (*bufferPtr2 != '\n') bufferPtr2++;
		*bufferPtr2 = '\0';
		eTypeNum = atoi(bufferPtr1);

		bufferPtr1 = ++bufferPtr2;

		///5. Enemy Type - File Name
		while (*bufferPtr2 != '\n') bufferPtr2++;
		*bufferPtr2 = '\0';
		strcpy_s(fileName_Types, bufferPtr1);

		bufferPtr1 = ++bufferPtr2;

		///개별 Enemy Type 파싱
		char filePath_Type[MAX_FILE_LEN * 2];
		strcpy_s(filePath_Type, fileDir_Types);
		strcat_s(filePath_Type, fileName_Types);

		parseData_EnemyType(eTypeNum, filePath_Type);
	}

	///6. Number of Enemy Move Patterns
	while (*bufferPtr2 != '\n') bufferPtr2++;
	*bufferPtr2 = '\0';
	eNumOfMovePatterns = atoi(bufferPtr1);

	bufferPtr1 = ++bufferPtr2;

	///7. Enemy Move Patterns - File Directory
	while (*bufferPtr2 != '\n') bufferPtr2++;
	*bufferPtr2 = '\0';
	strcpy_s(fileDir_MovePatterns, bufferPtr1);

	bufferPtr1 = ++bufferPtr2;

	for (int y = 0; y < eNumOfTypes; y++)
	{
		///8. Enemy Move Pattern - Number
		while (*bufferPtr2 != '\n') bufferPtr2++;
		*bufferPtr2 = '\0';
		eMovePatternTypeNum = atoi(bufferPtr1);

		bufferPtr1 = ++bufferPtr2;

		///9. Enemy Move Pattern - File Name
		while (*bufferPtr2 != '\n') bufferPtr2++;
		*bufferPtr2 = '\0';
		strcpy_s(fileName_MovePatterns, bufferPtr1);

		bufferPtr1 = ++bufferPtr2;

		///개별 Enemy Move Pattern 파싱
		char filePath_MovePattern[MAX_FILE_LEN * 2];
		strcpy_s(filePath_MovePattern, fileDir_MovePatterns);
		strcat_s(filePath_MovePattern, fileName_MovePatterns);

		parseData_MovePatternType(eMovePatternTypeNum, filePath_MovePattern);
	}

	free(buffer);
}

void parseData_EnemyType(int typeNum, const char* filePath)
{
	//파싱할 데이터
	int* maxLife = &(EnemyType_Table[typeNum]._maxLife);
	int* coolTime = &(EnemyType_Table[typeNum]._shotCoolTime);
	int* movePatternTypeNum = &(EnemyType_Table[typeNum]._movePatternTypeNum);

	//데이터 불러오기
	char* buffer = file_WriteDataOnBuffer(filePath);

	//파싱
	char* bufferPtr1 = buffer;
	char* bufferPtr2 = buffer;
	
	///1. Enemy Max life
	while (*bufferPtr2 != '\n') bufferPtr2++;
	*bufferPtr2 = '\0';
	*maxLife = atoi(bufferPtr1);

	bufferPtr1 = ++bufferPtr2;

	///2. Enemy Shot Cool Time
	while (*bufferPtr2 != '\n') bufferPtr2++;
	*bufferPtr2 = '\0';
	*coolTime = atoi(bufferPtr1);

	bufferPtr1 = ++bufferPtr2;

	///3. Move Pattern Number
	while (*bufferPtr2 != '\n') bufferPtr2++;
	*bufferPtr2 = '\0';
	*movePatternTypeNum = atoi(bufferPtr1);

	free(buffer);
}

void parseData_MovePatternType(int typeNum, const char* filePath)
{
	//파싱할 데이터
	int* _length = &(MovePattern_Table[typeNum]._length);
	char movePattern[MAX_ENEMY_MOVEPATTERN_LEN];

	//데이터 불러오기
	char* buffer = file_WriteDataOnBuffer(filePath);

	//파싱
	char* bufferPtr1 = buffer;
	char* bufferPtr2 = buffer;

	while (*bufferPtr2 != '\n') bufferPtr2++;
	*bufferPtr2 = '\0';
	strcpy_s(movePattern, bufferPtr1);

	///1. Move Pattern Length
	*_length = strlen(movePattern);

	///2. Move Pattern String -> convert each char into MoveOffset
	char* patternPtr = movePattern;
	int currentLen = 0;
	int signIdx;

	while (*patternPtr != '\0');
	{
		switch (*patternPtr)
		{
		case '↓':
			signIdx = 0;
			break;
		case '→':
			signIdx = 1;
			break;
		case '↑':
			signIdx = 2;
			break;
		case '←':
			signIdx = 3;
			break;
		case '↗':
			signIdx = 4;
			break;
		case '↙':
			signIdx = 5;
			break;
		case '↖':
			signIdx = 6;
			break;
		case '↘':
			signIdx = 7;
			break;
		default:
			return;
		}
		MovePattern_Table[typeNum]._pattern[currentLen] = MoveSign_Table[signIdx]._offset;

		patternPtr++;
		currentLen++;
	}

	free(buffer);
}

void parseData_SceneMgr(void)
{
	//파싱할 데이터
	char fileDir[MAX_FILE_LEN];
	int sceneNum;
	char fileName[MAX_FILE_LEN];

	//데이터 불러오기
	char* buffer = (char*)file_WriteDataOnBuffer(DATA_MGR_FILE_NAME__SCENE);

	//파싱
	char* bufferPtr1 = buffer;
	char* bufferPtr2 = buffer;

	///1. File Directory
	while (*bufferPtr2 != '\n') bufferPtr2++;
	*bufferPtr2 = '\0';
	strcpy_s(fileDir, bufferPtr1);

	bufferPtr1 = ++bufferPtr2;

	for (int iCnt = 0; iCnt < NUM_OF_SCENE; iCnt++)
	{
		///2. Scene Num
		while (*bufferPtr2 != ' ') bufferPtr2++;
		*bufferPtr2 = '\0';
		sceneNum = atoi(bufferPtr1);

		bufferPtr1 = ++bufferPtr2;

		///3. Scene File Name
		while (*bufferPtr2 != '\n') bufferPtr2++;
		*bufferPtr2 = '\0';
		strcpy_s(fileName, bufferPtr1);

		bufferPtr1 = ++bufferPtr2;

		///개별 Scene 파싱
		char sceneFilePath[MAX_FILE_LEN * 2];
		strcpy_s(sceneFilePath, fileDir);
		strcat_s(sceneFilePath, fileName);

		parseData_Scene(sceneFilePath, Scene[sceneNum].memory);
	}

	free(buffer);
}

void parseData_Scene(const char* filePath, char memory[][dfSCREEN_WIDTH])
{
	//파싱할 데이터 불러오기
	char* buffer = file_WriteDataOnBuffer(filePath);
	
	//파싱
	char* bufferPtr1 = buffer;
	char* bufferPtr2 = buffer;

	///씬 각 행의 마지막 바이트 널문자로 변환
	for (int iBufCnt = 0; iBufCnt < dfSCREEN_HEIGHT; iBufCnt++)
	{
		while (*bufferPtr2 != '\n') bufferPtr2++;
		*bufferPtr2 = '\0';
		strcpy_s(memory[iBufCnt],bufferPtr1);
		bufferPtr1 = ++bufferPtr2;
	}

	free(buffer);
}

void parseData_StageMgr(void)
{
	//파싱할 데이터
	char fileDir[MAX_FILE_LEN];
	int numOfStages;
	int stageNum;
	char fileName[MAX_FILE_LEN];

	//데이터 불러오기
	char* buffer = (char*)file_WriteDataOnBuffer(DATA_MGR_FILE_NAME__SCENE);

	//파싱
	char* bufferPtr1 = buffer;
	char* bufferPtr2 = buffer;

	///1. File Directory
	while (*bufferPtr2 != '\n') bufferPtr2++;
	*bufferPtr2 = '\0';
	strcpy_s(fileDir, bufferPtr1);

	bufferPtr1 = ++bufferPtr2;

	///2. Number of Stages
	while (*bufferPtr2 != '\n') bufferPtr2++;
	*bufferPtr2 = '\0';
	numOfStages = atoi(bufferPtr1);

	bufferPtr1 = ++bufferPtr2;

	for (int iCnt = 0; iCnt < NUM_OF_SCENE; iCnt++)
	{
		///3. Stage Number
		while (*bufferPtr2 != ' ') bufferPtr2++;
		*bufferPtr2 = '\0';
		stageNum = atoi(bufferPtr1);

		bufferPtr1 = ++bufferPtr2;

		///4. Stage File Name
		while (*bufferPtr2 != '\n') bufferPtr2++;
		*bufferPtr2 = '\0';
		strcpy_s(fileName, bufferPtr1);

		bufferPtr1 = ++bufferPtr2;

		///Stage 파일경로 배열에 저장
		char stageFilePath[MAX_FILE_LEN * 2];
		strcpy_s(stageFilePath, fileDir);
		strcat_s(stageFilePath, fileName);

		strcpy_s(DATA_FILE_PATHS__STAGE[stageNum], stageFilePath);
		//parseData_Stage(stageFilePath);
	}

	free(buffer);
}

void parseData_Stage(int stageNum)
{
	const char* filePath = DATA_FILE_PATHS__STAGE[stageNum];

	//파싱할 데이터
	int* numOfEnemies = &(stageMgr._iEnemyAlive);
	char (*stageData)[dfSCREEN_WIDTH] = stageMgr._stageData;

	char* buffer = file_WriteDataOnBuffer(filePath);

	//파싱
	char* bufferPtr1 = buffer;
	char* bufferPtr2 = buffer;

	///1. Number of Enemies
	while (*bufferPtr2 != '\n') bufferPtr2++;
	*bufferPtr2 = '\0';
	*numOfEnemies = atoi(bufferPtr1);

	bufferPtr1 = ++bufferPtr2;

	///2. Stage Screen Data
	char* screenDataPtr = bufferPtr1;
	int eCnt = 0;
	////2-1. 씬 각 행의 마지막 바이트 널문자로 변환
	for (int iBufCnt = 0; iBufCnt < dfSCREEN_HEIGHT; iBufCnt++)
	{
		while (*bufferPtr2 != '\n') bufferPtr2++;
		*bufferPtr2 = '\0';
		strcpy_s(ScreenBuffer[iBufCnt], bufferPtr1);
		bufferPtr1 = ++bufferPtr2;
	}

	////2-2.
	//if (*screenDataPtr == '1')
	//{
	//	gameMgr._e[eCnt] = 
	//}

	free(buffer);
}



//////////////////////////////////////////////////

char* file_WriteDataOnBuffer(const char* fileName)
{
	FILE* fp = nullptr;
	char filePath[MAX_FILE_LEN];
	strcpy_s(filePath, DATA_PATH);
	strcat_s(filePath, fileName);

	fopen_s(&fp, filePath, "r");
	if (fp == nullptr)
	{
		printf("%s File does not exist.\n", fileName);
		return nullptr;
	}

	size_t fileSize = file_GetSize(fp);
	char* buffer = (char*)malloc(fileSize + 1);
	fread(buffer, fileSize, 1, fp);

	fclose(fp);
	return buffer;
}


size_t file_GetSize(FILE* fp)
{
	size_t file_size;

	fseek(fp, 0, SEEK_END);
	file_size = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	return file_size;
}





