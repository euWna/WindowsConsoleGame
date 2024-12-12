#include "MovePattern.h"

const MoveSign MoveSign_Table[8] =
{
	{ '¡ç',  {-1, 0} },
	{ '¡è',	{ 0,-1} },
	{ '¡æ',	{ 1, 0} },
	{ '¡é',	{ 0, 1} },
	{ '¢Ø',	{-1,-1} },
	{ '¢Ö',	{ 1,-1} },
	{ '¢Ù',	{ 1, 1} },
	{ '¢×',	{-1, 1} },
};

MovePattern MovePattern_Table[MAX_ENEMY_MOVEPATTERN_TYPE + 1];
