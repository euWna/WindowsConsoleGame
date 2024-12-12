#pragma once
#ifndef __DATA_PARSING_H__
#define __DATA_PARSING_H__

#define MAX_FILE_LEN 105 //100 + 확장자 4 (".txt") + 널문자 1

void parseData_SceneMgr(void);
void parseData_Player(void);
void parseData_EnemyMgr(void);
void parseData_StageMgr(void);

#endif 
