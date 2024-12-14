#include <stdio.h>
#include <windows.h>

#include "Buffer.h"
#include "Scene.h"
#include "GameStage.h"

#include "Player.h"
#include "MovePattern.h"
#include "Enemy.h"

#define MAX_FILE_LEN 105 //100 + 확장자 4 (".txt") + 널문자 1

//파일 경로 및 파일명
const char* DATA_PATH = "Data/";
const char* DATA_MGR_FILE_NAME__SCENE = "SceneMgr.txt";
const char* DATA_MGR_FILE_NAME__PLAYER = "PlayerMgr.txt";
const char* DATA_MGR_FILE_NAME__ENEMY = "EnemyMgr.txt";
const char* DATA_MGR_FILE_NAME__STAGE = "StageMgr.txt";

//stage별 파일 경로 저장 배열
char DATA_FILE_PATHS__STAGE[MAX_STAGE + 1][MAX_FILE_LEN]; 

//데이터 파싱 함수
void parseMgrData_StaticScene(void);
void parseMgrData_Stage(void);
void parseMgrData_Player(void);
void parseMgrData_Enemy(void);

void parseData_StaticScene(int sceneNum, const char* filePath);
void parseData_Stage(int stageNum);
void parseData_EnemyType(int typeNum, const char* filePath);
void parseData_MovePatternType(int typeNum, const char* filePath);


//자료형별 파싱 함수
char parseChar(char** buffer);
int parseInt(char** buffer);
void parseString(char** buffer, char* dst);

//파일 스트림 함수
char* file_WriteDataOnBuffer(const char* fileName);
size_t file_GetSize(FILE* fp);


void parseMgrData_StaticScene(void)
{
	//파싱할 데이터
	///1. scene 파일 폴더 경로
	char fileDir[MAX_FILE_LEN];
	///2. 개별 scene 파일 정보
	///2-1. scene 번호
	int sceneNum;
	///2-1. scene 파일명
	char fileName[MAX_FILE_LEN];

	//데이터 불러오기
	char* buffer = (char*)file_WriteDataOnBuffer(DATA_MGR_FILE_NAME__SCENE);

	//파싱
	char* bufferPtr = buffer;

	///1. scene 파일 폴더 경로
	parseString(&bufferPtr, fileDir);

	///2. 개별 scene 파일 정보 
	for (int iCnt = 0; iCnt < NUM_OF_STATIC_SCENES; iCnt++)
	{
		///2-1. scene 번호
		sceneNum = parseInt(&bufferPtr);

		///2-1. scene 번호
		parseString(&bufferPtr, fileName);

		///개별 scene 파일 파싱
		char sceneFilePath[MAX_FILE_LEN * 2];
		strcpy_s(sceneFilePath, fileDir);
		strcat_s(sceneFilePath, fileName);
		parseData_StaticScene(sceneNum, sceneFilePath);
	}

	free(buffer);
}


void parseMgrData_Stage(void)
{
	//파싱할 데이터
	///1. stage 파일 폴더 경로
	char fileDir[MAX_FILE_LEN];
	///2. stage 개수
	int numOfStages;
	///3. 개별 stage 파일 정보
	///3-1. stage 번호
	int stageNum;
	///3-2. stage 파일명
	char fileName[MAX_FILE_LEN];

	//데이터 불러오기
	char* buffer = (char*)file_WriteDataOnBuffer(DATA_MGR_FILE_NAME__STAGE);

	//파싱
	char* bufferPtr = buffer;

	///1. File Directory
	parseString(&bufferPtr, fileDir);

	///2. Number of Stages
	numOfStages = parseInt(&bufferPtr);

	///3. 개별 stage 파일 정보
	for (int iCnt = 0; iCnt < numOfStages; iCnt++)
	{
		///3-1. stage 번호
		stageNum = parseInt(&bufferPtr);

		///3-2. stage 파일명
		parseString(&bufferPtr, fileName);

		/// 개별stage 파일경로 배열에 저장		
		char stageFilePath[MAX_FILE_LEN * 2];
		strcpy_s(stageFilePath, fileDir);
		strcat_s(stageFilePath, fileName);
		strcpy_s(DATA_FILE_PATHS__STAGE[stageNum], stageFilePath);
	}

	free(buffer);
}

void parseMgrData_Player(void)
{
	//파싱할 데이터
	///1. Player Sprite 
	char* sprite = &playerSetting._sprite;
	///2. Player Shot Sprite 
	char* shotSprite = &playerSetting._shotSprite;
	///3. Player Max Life
	int* maxLife = &playerSetting._maxLife;

	//데이터 불러오기
	char* buffer = file_WriteDataOnBuffer(DATA_MGR_FILE_NAME__PLAYER);

	//파싱
	char* bufferPtr = buffer;
	*sprite = parseChar(&bufferPtr);
	*shotSprite = parseChar(&bufferPtr);
	*maxLife = parseInt(&bufferPtr);

	//fclose(fp);
	free(buffer);
}

void parseMgrData_Enemy(void)
{
	//파싱할 데이터
	///1. Enemy Shot Sprite
	char* shotSprite = &(enemySetting._shotSprite);
	///2. Enemy Type 개수
	int eNumOfTypes;
	///3. Enemy Type 폴더 경로
	char fileDir_Types[MAX_FILE_LEN];
	///4. 개별 Enemy Type 파일 정보
	///4-1. Enemy Type 번호
	int eTypeNum;
	///4-2. Enemy Type N의 파일명
	char fileName_Types[MAX_FILE_LEN];
	///5. Move pattern 개수
	int eNumOfMovePatterns;
	///6. Move pattern 폴더 경로
	char fileDir_MovePatterns[MAX_FILE_LEN];
	///7. 개별 Move pattern 파일 정보
	///7-1. Move pattern 번호
	int eMovePatternTypeNum;
	///7-2. Move pattern 파일명
	char fileName_MovePatterns[MAX_FILE_LEN];

	//데이터 불러오기
	char* buffer = (char*)file_WriteDataOnBuffer(DATA_MGR_FILE_NAME__ENEMY);

	//파싱
	char* bufferPtr = buffer;

	///1. Enemy Shot Sprite
	*shotSprite = parseChar(&bufferPtr);
	///2. Enemy Type 개수
	eNumOfTypes = parseInt(&bufferPtr);
	///3. Enemy Type 폴더 경로
	parseString(&bufferPtr, fileDir_Types);

	///4. 개별 Enemy Type 파일 정보
	for (int iCnt = 0; iCnt < eNumOfTypes; iCnt++)
	{
		///4-1. Enemy Type 번호
		eTypeNum = parseInt(&bufferPtr);
		///4-2. Enemy Type N의 파일명
		parseString(&bufferPtr, fileName_Types);

		/// 개별 Enemy Type 파일 파싱
		char filePath_Type[MAX_FILE_LEN * 2];
		strcpy_s(filePath_Type, fileDir_Types);
		strcat_s(filePath_Type, fileName_Types);
		parseData_EnemyType(eTypeNum, filePath_Type);
	}

	///5. Move pattern 개수
	eNumOfMovePatterns = parseInt(&bufferPtr);
	///6. Move pattern 폴더 경로
	parseString(&bufferPtr, fileDir_MovePatterns);

	///7. 개별 Enemy Move Pattern 정보
	for (int iCnt = 0; iCnt < eNumOfTypes; iCnt++)
	{
		///7-1. Move pattern 번호
		eMovePatternTypeNum = parseInt(&bufferPtr);
		///7-2. Move pattern 파일명
		parseString(&bufferPtr, fileName_MovePatterns);
		
		///개별 Enemy Move Pattern 파싱
		char filePath_MovePattern[MAX_FILE_LEN * 2];
		strcpy_s(filePath_MovePattern, fileDir_MovePatterns);
		strcat_s(filePath_MovePattern, fileName_MovePatterns);
		parseData_MovePatternType(eMovePatternTypeNum, filePath_MovePattern);
	}

	free(buffer);
}

/////////////////////////////////////////////////////////////////

void parseData_StaticScene(int sceneNum, const char* filePath)
{
	//파싱할 데이터
	///scene 스크린 데이터
	char(*sceneMemory)[dfSCREEN_WIDTH] = staticScene[sceneNum].memory;

	//파싱할 데이터 불러오기
	char* buffer = file_WriteDataOnBuffer(filePath);

	//파싱
	char* bufferPtr1 = buffer;
	char* bufferPtr2 = buffer;

	///씬 각 행의 마지막 바이트 널문자로 변환
	for (int iBufCnt = 0; iBufCnt < dfSCREEN_HEIGHT; iBufCnt++)
	{
		while (*bufferPtr2 != '\r' && *bufferPtr2 != '\0') bufferPtr2++;
		*bufferPtr2++ = '\0';
		if (*bufferPtr2 == '\n') *bufferPtr2++ = '\0';

		strcpy_s(sceneMemory[iBufCnt], bufferPtr1);

		bufferPtr1 = ++bufferPtr2;
	}

	free(buffer);
}

void parseData_Stage(int stageNum)
{
	//파싱할 데이터
	///1. 등장 Enemy 총 개수
	int* numOfEnemies = &(stageMgr._enemyTotal);
	///2. stage 스크린 데이터
	char(*stageData)[dfSCREEN_WIDTH] = stageMgr._stageData;

	//데이터 불러오기
	const char* filePath = DATA_FILE_PATHS__STAGE[stageNum];
	char* buffer = file_WriteDataOnBuffer(filePath);


	//파싱
	char* bufferPtr = buffer;

	///1. 등장 Enemy 총 개수
	*numOfEnemies = parseInt(&bufferPtr);

	///2. stage 스크린 데이터
	char* bufferPtr1 = bufferPtr;
	char* bufferPtr2 = bufferPtr;

	///씬 각 행의 마지막 바이트 널문자로 변환
	for (int iBufCnt = 0; iBufCnt < dfSCREEN_HEIGHT; iBufCnt++)
	{
		while (*bufferPtr2 != '\r' && *bufferPtr2 != '\0') bufferPtr2++;
		*bufferPtr2++ = '\0';
		if (*bufferPtr2 == '\n') *bufferPtr2++ = '\0';

		strcpy_s(stageData[iBufCnt], bufferPtr1);

		bufferPtr1 = ++bufferPtr2;
	}

	free(buffer);
}


void parseData_EnemyType(int typeNum, const char* filePath)
{
	//파싱할 데이터
	///1. Enemy Max life
	int* maxLife = &(EnemyType_Table[typeNum]._maxLife);
	///2. Enemy Shot 쿨타임
	int* coolTime = &(EnemyType_Table[typeNum]._shotCoolTime);
	///3. Move Pattern 번호
	int* movePatternTypeNum = &(EnemyType_Table[typeNum]._movePatternTypeNum);

	//데이터 불러오기
	char* buffer = file_WriteDataOnBuffer(filePath);

	//파싱
	char* bufferPtr = buffer;

	*maxLife = parseInt(&bufferPtr);
	*coolTime = parseInt(&bufferPtr);
	*movePatternTypeNum = parseInt(&bufferPtr);

	free(buffer);
}

void parseData_MovePatternType(int typeNum, const char* filePath)
{
	//파싱할 데이터
	///move pattern 문자열
	char movePattern[MAX_ENEMY_MOVEPATTERN_LEN];
	
	//데이터 변환
	///1. move pattern에 쓰이는 화살표 기호가 3byte 짜리이므로 3byte씩 파싱
	///2. 각 화살표 기호를 이동 offset으로 변환
	///3. Move pattern 테이블에 저장
	///4. pattern 길이 저장
	int* length = &(MovePattern_Table[typeNum]._length);


	//데이터 불러오기
	char* buffer = file_WriteDataOnBuffer(filePath);

	//파싱
	char* bufferPtr = buffer;
	
	///move pattern 문자열
	parseString(&bufferPtr, movePattern);

	///데이터 변환
	char* patternPtr = movePattern;
	int signNum = 0;
	int signIdx = 0;
	int offsetIdx;

	while (*patternPtr != '\0')
	{
		//1. 3byte씩 파싱
		signNum = 0;
		signNum |= 0xff << 24;
		signNum |= (unsigned char)(*patternPtr++) << 16;
		signNum |= (unsigned char)(*patternPtr++) << 8;
		signNum |= (unsigned char)(*patternPtr++);

		///2. 각 화살표 기호를 이동 offset으로 변환
		switch (signNum)
		{
		case 0xffe28690: //←
			offsetIdx = 0;
			break;
		case 0xffe28691: //↑
			offsetIdx = 1;
			break;
		case 0xffe28692: //→
			offsetIdx = 2;
			break;
		case 0xffe28693: //↓
			offsetIdx = 3;
			break;
		case 0xffe28696: //↖
			offsetIdx = 4;
			break;
		case 0xffe28697: //↗
			offsetIdx = 5;
			break;
		case 0xffe28698: //↘
			offsetIdx = 6;
			break;
		case 0xffe28699: //↙
			offsetIdx = 7;
			break;
		default:
			return;
		}

		///3. Move pattern 테이블에 저장
		MovePattern_Table[typeNum]._pattern[signIdx] = MoveSign_ConversionTable[offsetIdx]._offset;
		signIdx++;
	}

	///4. pattern 길이 저장
	*length = signIdx;

	free(buffer);
}


//////////////////////////////////////////////////

char parseChar(char** buffer)
{
	if (*buffer == nullptr) return -1;
	
	char res;
	char* ptr = *buffer;

	res = *ptr++;
	while (*ptr == '\r' || *ptr == '\n' || *ptr == ' ')
	{
		*ptr = '\0';
		ptr++;
	}
	*buffer = ptr;

	return res;
}

int parseInt(char** buffer)
{
	if (*buffer == nullptr) return -1;

	int res;
	char* startPtr = *buffer;
	char* endPtr = *buffer;

	while (*endPtr != '\r' && *endPtr != ' ' && *endPtr != '\0') endPtr++;
	*endPtr++ = '\0';
	res = atoi(startPtr);

	if (*endPtr == '\n') *endPtr++ = '\0';
	*buffer = endPtr;

	return res;
}

void parseString(char** buffer, char* dst)
{
	if (*buffer == nullptr) return;

	char* ptr = *buffer;
	
	while (*ptr != '\r' && *ptr != '\n' && *ptr != ' ' && *ptr != '\0')
	{
		*dst++ = *ptr++;
	}
	*dst = '\0';

	while (*ptr == '\r' || *ptr == '\n' || *ptr == ' ')
	{
		*ptr++ = '\0';
	}
	*buffer = ptr;
}

/////////////////////////////////////////////////////////////////

char* file_WriteDataOnBuffer(const char* fileName)
{
	FILE* fp = nullptr;
	char filePath[MAX_FILE_LEN];
	strcpy_s(filePath, DATA_PATH);
	strcat_s(filePath, fileName);

	fopen_s(&fp, filePath, "rb");
	if (fp == nullptr)
	{
		printf("%s File does not exist.\n", fileName);
		return nullptr;
	}

	size_t fileSize = file_GetSize(fp);
	char* buffer = (char*)malloc(fileSize + 1);
	if (buffer == nullptr)
	{
		printf("Memory allocation failed.\n");
		return nullptr;
	}

	fread(buffer, fileSize, 1, fp);
	buffer[fileSize] = '\0';

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