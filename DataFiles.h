#pragma once
#ifndef __DATA_DIRECTORY_H__
#define __DATA_DIRECTORY_H__

#define MAX_FILE_LEN 105 //100 + 확장자 4 (".txt") + 널문자 1

extern const char* DATA_FILE_PATH = "Data/";

extern const char* DATA_FILE_NAME__SCENE = "SceneData.txt";
extern const char* DATA_FILE_NAME__STAGE = "StageData.txt";
extern const char* DATA_FILE_NAME__PLAYER = "PlayerData.txt";
extern const char* DATA_FILE_NAME__ENEMY = "EnemyData.txt";
extern const char* DATA_FILE_NAME__ENEMYSHOT = "EnemyShotData.txt";

#endif