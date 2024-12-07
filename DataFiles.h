#pragma once
#ifndef __DATA_DIRECTORY_H__
#define __DATA_DIRECTORY_H__

#define MAX_FILE_LEN 105 //100 + 확장자 4 (".txt") + 널문자 1

extern const char* DATA_FILE_PATH;

extern const char* DATA_FILE_NAME__SCENE;
extern const char* DATA_FILE_NAME__STAGE;
extern const char* DATA_FILE_NAME__PLAYER;
extern const char* DATA_FILE_NAME__ENEMY;
extern const char* DATA_FILE_NAME__ENEMYSHOT;

#endif