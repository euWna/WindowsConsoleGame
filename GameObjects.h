#pragma once
#ifndef __GAME_OBJECTS_H__
#define __GAME_OBJECTS_H__

extern PlayerSettingMemory playerSetting;

extern Player player;
extern PlayerShot pShot[dfSCREEN_WIDTH];
extern Enemy enemy[dfSCREEN_HEIGHT * dfSCREEN_WIDTH];
extern EnemyShot eShot[dfSCREEN_HEIGHT * dfSCREEN_WIDTH];

#endif