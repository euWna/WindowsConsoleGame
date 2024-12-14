#include <stdio.h>
#include <windows.h>

#include "Buffer.h"
#include "Scene.h"
#include "GameStage.h"

#include "Player.h"
#include "MovePattern.h"
#include "Enemy.h"

#define MAX_FILE_LEN 105 //100 + Ȯ���� 4 (".txt") + �ι��� 1

//���� ��� �� ���ϸ�
const char* DATA_PATH = "Data/";
const char* DATA_MGR_FILE_NAME__SCENE = "SceneMgr.txt";
const char* DATA_MGR_FILE_NAME__PLAYER = "PlayerMgr.txt";
const char* DATA_MGR_FILE_NAME__ENEMY = "EnemyMgr.txt";
const char* DATA_MGR_FILE_NAME__STAGE = "StageMgr.txt";

//stage�� ���� ��� ���� �迭
char DATA_FILE_PATHS__STAGE[MAX_STAGE + 1][MAX_FILE_LEN]; 

//������ �Ľ� �Լ�
void parseMgrData_StaticScene(void);
void parseMgrData_Stage(void);
void parseMgrData_Player(void);
void parseMgrData_Enemy(void);

void parseData_StaticScene(int sceneNum, const char* filePath);
void parseData_Stage(int stageNum);
void parseData_EnemyType(int typeNum, const char* filePath);
void parseData_MovePatternType(int typeNum, const char* filePath);


//�ڷ����� �Ľ� �Լ�
char parseChar(char** buffer);
int parseInt(char** buffer);
void parseString(char** buffer, char* dst);

//���� ��Ʈ�� �Լ�
char* file_WriteDataOnBuffer(const char* fileName);
size_t file_GetSize(FILE* fp);


void parseMgrData_StaticScene(void)
{
	//�Ľ��� ������
	///1. scene ���� ���� ���
	char fileDir[MAX_FILE_LEN];
	///2. ���� scene ���� ����
	///2-1. scene ��ȣ
	int sceneNum;
	///2-1. scene ���ϸ�
	char fileName[MAX_FILE_LEN];

	//������ �ҷ�����
	char* buffer = (char*)file_WriteDataOnBuffer(DATA_MGR_FILE_NAME__SCENE);

	//�Ľ�
	char* bufferPtr = buffer;

	///1. scene ���� ���� ���
	parseString(&bufferPtr, fileDir);

	///2. ���� scene ���� ���� 
	for (int iCnt = 0; iCnt < NUM_OF_STATIC_SCENES; iCnt++)
	{
		///2-1. scene ��ȣ
		sceneNum = parseInt(&bufferPtr);

		///2-1. scene ��ȣ
		parseString(&bufferPtr, fileName);

		///���� scene ���� �Ľ�
		char sceneFilePath[MAX_FILE_LEN * 2];
		strcpy_s(sceneFilePath, fileDir);
		strcat_s(sceneFilePath, fileName);
		parseData_StaticScene(sceneNum, sceneFilePath);
	}

	free(buffer);
}


void parseMgrData_Stage(void)
{
	//�Ľ��� ������
	///1. stage ���� ���� ���
	char fileDir[MAX_FILE_LEN];
	///2. stage ����
	int numOfStages;
	///3. ���� stage ���� ����
	///3-1. stage ��ȣ
	int stageNum;
	///3-2. stage ���ϸ�
	char fileName[MAX_FILE_LEN];

	//������ �ҷ�����
	char* buffer = (char*)file_WriteDataOnBuffer(DATA_MGR_FILE_NAME__STAGE);

	//�Ľ�
	char* bufferPtr = buffer;

	///1. File Directory
	parseString(&bufferPtr, fileDir);

	///2. Number of Stages
	numOfStages = parseInt(&bufferPtr);

	///3. ���� stage ���� ����
	for (int iCnt = 0; iCnt < numOfStages; iCnt++)
	{
		///3-1. stage ��ȣ
		stageNum = parseInt(&bufferPtr);

		///3-2. stage ���ϸ�
		parseString(&bufferPtr, fileName);

		/// ����stage ���ϰ�� �迭�� ����		
		char stageFilePath[MAX_FILE_LEN * 2];
		strcpy_s(stageFilePath, fileDir);
		strcat_s(stageFilePath, fileName);
		strcpy_s(DATA_FILE_PATHS__STAGE[stageNum], stageFilePath);
	}

	free(buffer);
}

void parseMgrData_Player(void)
{
	//�Ľ��� ������
	///1. Player Sprite 
	char* sprite = &playerSetting._sprite;
	///2. Player Shot Sprite 
	char* shotSprite = &playerSetting._shotSprite;
	///3. Player Max Life
	int* maxLife = &playerSetting._maxLife;

	//������ �ҷ�����
	char* buffer = file_WriteDataOnBuffer(DATA_MGR_FILE_NAME__PLAYER);

	//�Ľ�
	char* bufferPtr = buffer;
	*sprite = parseChar(&bufferPtr);
	*shotSprite = parseChar(&bufferPtr);
	*maxLife = parseInt(&bufferPtr);

	//fclose(fp);
	free(buffer);
}

void parseMgrData_Enemy(void)
{
	//�Ľ��� ������
	///1. Enemy Shot Sprite
	char* shotSprite = &(enemySetting._shotSprite);
	///2. Enemy Type ����
	int eNumOfTypes;
	///3. Enemy Type ���� ���
	char fileDir_Types[MAX_FILE_LEN];
	///4. ���� Enemy Type ���� ����
	///4-1. Enemy Type ��ȣ
	int eTypeNum;
	///4-2. Enemy Type N�� ���ϸ�
	char fileName_Types[MAX_FILE_LEN];
	///5. Move pattern ����
	int eNumOfMovePatterns;
	///6. Move pattern ���� ���
	char fileDir_MovePatterns[MAX_FILE_LEN];
	///7. ���� Move pattern ���� ����
	///7-1. Move pattern ��ȣ
	int eMovePatternTypeNum;
	///7-2. Move pattern ���ϸ�
	char fileName_MovePatterns[MAX_FILE_LEN];

	//������ �ҷ�����
	char* buffer = (char*)file_WriteDataOnBuffer(DATA_MGR_FILE_NAME__ENEMY);

	//�Ľ�
	char* bufferPtr = buffer;

	///1. Enemy Shot Sprite
	*shotSprite = parseChar(&bufferPtr);
	///2. Enemy Type ����
	eNumOfTypes = parseInt(&bufferPtr);
	///3. Enemy Type ���� ���
	parseString(&bufferPtr, fileDir_Types);

	///4. ���� Enemy Type ���� ����
	for (int iCnt = 0; iCnt < eNumOfTypes; iCnt++)
	{
		///4-1. Enemy Type ��ȣ
		eTypeNum = parseInt(&bufferPtr);
		///4-2. Enemy Type N�� ���ϸ�
		parseString(&bufferPtr, fileName_Types);

		/// ���� Enemy Type ���� �Ľ�
		char filePath_Type[MAX_FILE_LEN * 2];
		strcpy_s(filePath_Type, fileDir_Types);
		strcat_s(filePath_Type, fileName_Types);
		parseData_EnemyType(eTypeNum, filePath_Type);
	}

	///5. Move pattern ����
	eNumOfMovePatterns = parseInt(&bufferPtr);
	///6. Move pattern ���� ���
	parseString(&bufferPtr, fileDir_MovePatterns);

	///7. ���� Enemy Move Pattern ����
	for (int iCnt = 0; iCnt < eNumOfTypes; iCnt++)
	{
		///7-1. Move pattern ��ȣ
		eMovePatternTypeNum = parseInt(&bufferPtr);
		///7-2. Move pattern ���ϸ�
		parseString(&bufferPtr, fileName_MovePatterns);
		
		///���� Enemy Move Pattern �Ľ�
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
	//�Ľ��� ������
	///scene ��ũ�� ������
	char(*sceneMemory)[dfSCREEN_WIDTH] = staticScene[sceneNum].memory;

	//�Ľ��� ������ �ҷ�����
	char* buffer = file_WriteDataOnBuffer(filePath);

	//�Ľ�
	char* bufferPtr1 = buffer;
	char* bufferPtr2 = buffer;

	///�� �� ���� ������ ����Ʈ �ι��ڷ� ��ȯ
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
	//�Ľ��� ������
	///1. ���� Enemy �� ����
	int* numOfEnemies = &(stageMgr._enemyTotal);
	///2. stage ��ũ�� ������
	char(*stageData)[dfSCREEN_WIDTH] = stageMgr._stageData;

	//������ �ҷ�����
	const char* filePath = DATA_FILE_PATHS__STAGE[stageNum];
	char* buffer = file_WriteDataOnBuffer(filePath);


	//�Ľ�
	char* bufferPtr = buffer;

	///1. ���� Enemy �� ����
	*numOfEnemies = parseInt(&bufferPtr);

	///2. stage ��ũ�� ������
	char* bufferPtr1 = bufferPtr;
	char* bufferPtr2 = bufferPtr;

	///�� �� ���� ������ ����Ʈ �ι��ڷ� ��ȯ
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
	//�Ľ��� ������
	///1. Enemy Max life
	int* maxLife = &(EnemyType_Table[typeNum]._maxLife);
	///2. Enemy Shot ��Ÿ��
	int* coolTime = &(EnemyType_Table[typeNum]._shotCoolTime);
	///3. Move Pattern ��ȣ
	int* movePatternTypeNum = &(EnemyType_Table[typeNum]._movePatternTypeNum);

	//������ �ҷ�����
	char* buffer = file_WriteDataOnBuffer(filePath);

	//�Ľ�
	char* bufferPtr = buffer;

	*maxLife = parseInt(&bufferPtr);
	*coolTime = parseInt(&bufferPtr);
	*movePatternTypeNum = parseInt(&bufferPtr);

	free(buffer);
}

void parseData_MovePatternType(int typeNum, const char* filePath)
{
	//�Ľ��� ������
	///move pattern ���ڿ�
	char movePattern[MAX_ENEMY_MOVEPATTERN_LEN];
	
	//������ ��ȯ
	///1. move pattern�� ���̴� ȭ��ǥ ��ȣ�� 3byte ¥���̹Ƿ� 3byte�� �Ľ�
	///2. �� ȭ��ǥ ��ȣ�� �̵� offset���� ��ȯ
	///3. Move pattern ���̺� ����
	///4. pattern ���� ����
	int* length = &(MovePattern_Table[typeNum]._length);


	//������ �ҷ�����
	char* buffer = file_WriteDataOnBuffer(filePath);

	//�Ľ�
	char* bufferPtr = buffer;
	
	///move pattern ���ڿ�
	parseString(&bufferPtr, movePattern);

	///������ ��ȯ
	char* patternPtr = movePattern;
	int signNum = 0;
	int signIdx = 0;
	int offsetIdx;

	while (*patternPtr != '\0')
	{
		//1. 3byte�� �Ľ�
		signNum = 0;
		signNum |= 0xff << 24;
		signNum |= (unsigned char)(*patternPtr++) << 16;
		signNum |= (unsigned char)(*patternPtr++) << 8;
		signNum |= (unsigned char)(*patternPtr++);

		///2. �� ȭ��ǥ ��ȣ�� �̵� offset���� ��ȯ
		switch (signNum)
		{
		case 0xffe28690: //��
			offsetIdx = 0;
			break;
		case 0xffe28691: //��
			offsetIdx = 1;
			break;
		case 0xffe28692: //��
			offsetIdx = 2;
			break;
		case 0xffe28693: //��
			offsetIdx = 3;
			break;
		case 0xffe28696: //��
			offsetIdx = 4;
			break;
		case 0xffe28697: //��
			offsetIdx = 5;
			break;
		case 0xffe28698: //��
			offsetIdx = 6;
			break;
		case 0xffe28699: //��
			offsetIdx = 7;
			break;
		default:
			return;
		}

		///3. Move pattern ���̺� ����
		MovePattern_Table[typeNum]._pattern[signIdx] = MoveSign_ConversionTable[offsetIdx]._offset;
		signIdx++;
	}

	///4. pattern ���� ����
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