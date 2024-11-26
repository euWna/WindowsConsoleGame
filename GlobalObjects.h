#pragma once
#ifndef __GLOBAL_OBJECTS_H__
#define __GLOBAL_OBJECTS_H__

#include "Player.h"
#include "Enemy.h"
#include "ScreenSetting.h"

extern Player player;
extern PlayerShot pShot[dfSCREEN_WIDTH];
extern Enemy enemy[dfSCREEN_HEIGHT * dfSCREEN_WIDTH];
extern EnemyShot eShot[dfSCREEN_HEIGHT * dfSCREEN_WIDTH];

#endif