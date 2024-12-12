#include "MovePattern.h"

const MoveSign MoveSign_Table[8] =
{
	{ '��',  {-1, 0} },
	{ '��',	{ 0,-1} },
	{ '��',	{ 1, 0} },
	{ '��',	{ 0, 1} },
	{ '��',	{-1,-1} },
	{ '��',	{ 1,-1} },
	{ '��',	{ 1, 1} },
	{ '��',	{-1, 1} },
};

MovePattern MovePattern_Table[MAX_ENEMY_MOVEPATTERN_TYPE + 1];
