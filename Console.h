#pragma once

#ifndef __CONSOLE_H__
#define __CONSOLE_H__

//-------------------------------------------------------------
// 콘솔 제어를 위한 준비 작업.
//
//-------------------------------------------------------------
void cs_Initial(void);

//-------------------------------------------------------------
// 콘솔 화면의 커서를 X, Y 좌표로 이동시킨다.
//
//-------------------------------------------------------------
void cs_MoveCursor(int iPosX, int iPosY);

//-------------------------------------------------------------
// 콘솔 화면을 초기화 한다.
//
//-------------------------------------------------------------
void cs_ClearScreen(void);

//-------------------------------------------------------------
// 콘솔에서 키보드 입력을 받는다.
// 게임의 조작키인 방향키(←↑→↓)와 Space바 입력만 처리한다.
//
//-------------------------------------------------------------
SHORT cs_GetKeyInput(void);

#endif