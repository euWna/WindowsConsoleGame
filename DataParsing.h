#pragma once
#ifndef __DATA_PARSING_H__
#define __DATA_PARSING_H__

size_t getFileSize(FILE* fp);

void parseData_Player(void);
void parseData_Enemy(void);
void parseData_Scenes(void);
void parseData_Scene(const char* fileName, char memory[][dfSCREEN_WIDTH]);

#endif 
