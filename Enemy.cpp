#include "Enemy.h"
#include "Player.h"
#include "ScreenSetting.h"

extern Player player;
extern Enemy enemy[dfSCREEN_HEIGHT * dfSCREEN_WIDTH];

void enemy_Shoot(int enemyIdx)
{
	Enemy target = enemy[enemyIdx];
	
}

void enemy_GetShot(int enemyIdx)
{

}

enum ENEMY_SHOT_TYPE
{
};

enum ENEMY_MOVE_PATTERN_TYPE
{
};