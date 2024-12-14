#pragma once
#ifndef __MOVE_PATTERN_H__
#define __MOVE_PATTERN_H__

#define MAX_ENEMY_MOVEPATTERN_TYPE 3
#define MAX_ENEMY_MOVEPATTERN_LEN 61 //( 3 (화살표 문자 byte 크기) * 20 (문자 수) ) + 1(널문자)


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

struct MovePattern
{
	int _length;
	MoveOffset _pattern[MAX_ENEMY_MOVEPATTERN_LEN];
};

extern const MoveSign MoveSign_ConversionTable[8];
extern MovePattern MovePattern_Table[MAX_ENEMY_MOVEPATTERN_TYPE + 1];


#endif