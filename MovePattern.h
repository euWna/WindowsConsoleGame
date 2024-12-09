#pragma once
#ifndef __MOVE_PATTERN_H__
#define __MOVE_PATTERN_H__

#define MAX_ENEMY_MOVEPATTERN_TYPE 3
#define MAX_ENEMY_MOVEPATTERN_LEN 20

struct MoveOffset
{
	int _x;
	int _y;
};

struct MoveSign
{
	int _char;
	MoveOffset _offset;
};

struct MovePatternType
{
	int _patternLen;
	MoveOffset _pattern[MAX_ENEMY_MOVEPATTERN_LEN];
};

extern const MoveSign MoveSign_Table[8];
extern MovePatternType MovePatternType_Table[MAX_ENEMY_MOVEPATTERN_TYPE + 1];


#endif