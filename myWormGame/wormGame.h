#pragma once
#include<windows.h>
#ifndef __STDIO_H__
#define __STDIO_H__
	#include<stdio.h>
#endif
#ifndef __STDLIB_H__
#define __STDLIB_H__
	#include<stdlib.h>
#endif
#ifndef __CONIO_H__
#define __CONIO_H__
	#include<conio.h>
#endif
#ifndef __TIME_H__
#define __TIME_H__
	#include<time.h>
#endif

#define KEY_ESC 27
#define KEY_SPACE 32
#define KEY_DIRECTION 224
#define KEY_LEFT 75  
#define KEY_RIGHT 77 
#define KEY_UP 72  
#define KEY_DOWN 80 

#define KEY_p 'p'
#define KEY_P 'P'

#define DIR_LEFT 1
#define DIR_RIGHT 2
#define DIR_UP 3
#define DIR_DOWN 4

#define BODYLEN 5
#define DEFAULTPOS_X 9
#define DEFAULTPOS_Y 9

#define DATA_EMPTY 0
//#define DATA_HEAD 1
#define DATA_BODY 2
#define DATA_ITEM 3

#define OFFSET_TITLE_X 5
#define OFFSET_TITLE_Y 4
#define OFFSET_GAME_X 5
#define OFFSET_GAME_Y 5

#define SIZE_GAMEMAP_X 20 
#define SIZE_GAMEMAP_Y 20

#define UI_POS_END_X 5
#define UI_POS_END_Y 5
#define UI_SIZE_END_X 30
#define UI_SIZE_END_Y 15

#define UI_POS_GAME_X 27
#define UI_POS_GAME_Y 6
#define UI_POS_PAUSE_X 5
#define UI_POS_PAUSE_Y 0

#define DRAW_EMPTY "  "
#define DRAW_WORM_HEAD "¡Ý"
#define DRAW_WORM_BODY "¢Á"
#define DRAW_UI_END_FRAME "¢Ë"
#define DRAW_GAME_WALL "¢Ì"
#define DRAW_ITEM "¡Ú"
#define DRAW_UI_FRAME "¢Ã"
#define DRAW_PAUSE_FRAME "¡Ø"

#define EXIT_BG_COLOR COLOR_BLACK
#define EXIT_COLOR COLOR_GRAY
#define HEAD_COLOR COLOR_YELLOW
#define BODY_COLOR COLOR_GREEN
#define WALL_COLOR COLOR_RED
#define GAME_BG_COLOR COLOR_BLACK
#define ITEM_COLOR COLOR_SKYBLUE
#define UI_GAME_BG_COLOR COLOR_BLACK
#define UI_GAME_COLOR COLOR_YELLOW 
#define UI_GAME_UI_FRAME_COLOR COLOR_GRAY
#define UI_PAUSE_COLOR COLOR_SKYBLUE

#define FRAME_UNIT 10
#define DEFAULTSPEED 100
#define SPEEDUNITP 3
#define SCOREUNIT 10

enum
{
	COLOR_BLACK = 0,
	COLOR_WHITE = 15,
	COLOR_BLUE = 9,
	COLOR_SKYBLUE = 11,
	COLOR_RED = 12,
	COLOR_DARK_RED = 4,
	COLOR_ORANGE = 6,
	COLOR_YELLOW = 14,
	COLOR_PURLPE = 13,
	COLOR_GREEN = 10,
	COLOR_GRAY = 7,
	COLOR_DARK_GRAY = 8
};

typedef struct _NODE
{
	COORD pos;
	_NODE* before;
	_NODE* after;
}NODE;

void EraseArea(COORD pos);
void KeyboardControl(void);

void InitHeadTail(void);
void InsertFromHead(COORD pos);
COORD DeleteFromTail(void);
void DeleteAllNode(void);

void SetTextColor(int bgColor, int textColor);
void GotoxyDraw(int x, int y, const char* str);
void Gotoxy(int x, int y);
void SetNoCursor(void);
void Title(void);
void Game(void);
void Exit(void);
void Init(void);
void ResetGameMapData(void);
void DrawWall(void);
void MoveWorm(void);
BOOL IsGameOver();
void CreateItem(void);
void DrawUIFrame(void);
void UpdateUI(void);
void ShowGameOver(void);
void Pause(void);