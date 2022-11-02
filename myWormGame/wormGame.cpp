#include "wormGame.h"

NODE head = { 0 };
NODE tail = { 0 };
COORD curPos = { 0 };
int curDir = 0;
int lastMoveDir = 0;
int gameMap[SIZE_GAMEMAP_X][SIZE_GAMEMAP_Y] = { 0 };
COORD itemPos;
BOOL isGetItem = FALSE;
float Speed = DEFAULTSPEED;
int Score = 0;

void CursorView(BOOL flag)
{
	CONSOLE_CURSOR_INFO info = { 0 };
	info.bVisible = flag;
	info.dwSize = 1;//커서의 굵기
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

void EraseArea(COORD pos)
{
	GotoxyDraw(pos.X, pos.Y, "  ");
}

void KeyboardControl(void)
{
	int nKey = 0;
	if (_kbhit())
	{
		nKey = _getch();
		if (nKey == KEY_DIRECTION)
		{
			nKey = _getch();
			switch (nKey)
			{
			case KEY_LEFT:
			{
				if (lastMoveDir != DIR_RIGHT)
				{
					curDir = DIR_LEFT;				
				}
			}
			break;
			case KEY_RIGHT:
			{
				if (lastMoveDir != DIR_LEFT)
				{
					curDir = DIR_RIGHT;
				}
			}
			break;
			case KEY_UP:
			{
				if (lastMoveDir != DIR_DOWN)
				{
					curDir = DIR_UP;
				}
			}
			break;
			case KEY_DOWN:
			{
				if (lastMoveDir != DIR_UP)
				{
					curDir = DIR_DOWN;
				}
			}
			break;
			}
		}
		else if (nKey == KEY_p || nKey == KEY_P)
		{
			Pause();
		}
	}
}

void InitHeadTail(void)
{
	head.after = &tail;
	head.before = NULL;
	tail.before = &head;
	tail.after = NULL;
}
void InsertFromHead(COORD pos)
{
	NODE* newNode = (NODE*)malloc(sizeof(NODE));
	newNode->pos = pos;
	newNode->before = &head;
	newNode->after = head.after;
	head.after->before = newNode;
	head.after = newNode;
}
COORD DeleteFromTail(void)
{
	COORD outputData = tail.before->pos;
	NODE* deleteNode = tail.before;
	deleteNode->before->after = &tail;
	tail.before = deleteNode->before;
	free(deleteNode);
	return outputData;
}
void DeleteAllNode(void)
{
	NODE* findNode = head.after;
	NODE* deleteNode = NULL;

	while (findNode != &tail)
	{
		deleteNode = findNode;
		findNode = findNode->after;
		free(deleteNode);
	}
}

void SetTextColor(int bgColor, int textColor)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, (bgColor << 4) + textColor);
}

void GotoxyDraw(int x, int y, const char* str)
{
	COORD pos = { (SHORT)(x * 2), (SHORT)y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	printf("%s", str);
}
void Gotoxy(int x, int y)
{
	COORD pos = { (SHORT)(x * 2), (SHORT)y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void SetNoCursor(void)
{
	CONSOLE_CURSOR_INFO CurInfo = { 0 };
	CurInfo.dwSize = 1;
	CurInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
}

void Title(void)
{
	SetTextColor(COLOR_BLACK, COLOR_BLACK);
	system("cls");
	int nCnt = 0;
	SetTextColor(COLOR_BLACK, COLOR_WHITE);
	GotoxyDraw(OFFSET_TITLE_X, OFFSET_TITLE_Y + 0, "■■■■■■■■■■■■■■■■");
	GotoxyDraw(OFFSET_TITLE_X, OFFSET_TITLE_Y + 1, "■                            ■");
	GotoxyDraw(OFFSET_TITLE_X, OFFSET_TITLE_Y + 2, "■                            ■");
	GotoxyDraw(OFFSET_TITLE_X, OFFSET_TITLE_Y + 3, "■                            ■");
	GotoxyDraw(OFFSET_TITLE_X, OFFSET_TITLE_Y + 4, "■■■■■■■■■■■■■■■■");
	Sleep(50);
	SetTextColor(COLOR_BLACK, COLOR_GREEN);
	GotoxyDraw(OFFSET_TITLE_X + 4, OFFSET_TITLE_Y + 2, "W");
	Sleep(50);								  
	GotoxyDraw(OFFSET_TITLE_X + 4, OFFSET_TITLE_Y + 2, "W O");
	Sleep(50);								  
	GotoxyDraw(OFFSET_TITLE_X + 4, OFFSET_TITLE_Y + 2, "W O R");
	Sleep(50);								  
	GotoxyDraw(OFFSET_TITLE_X + 4, OFFSET_TITLE_Y + 2, "W O R M");
	Sleep(50);								  
	GotoxyDraw(OFFSET_TITLE_X + 4, OFFSET_TITLE_Y + 2, "W O R M  G");
	Sleep(50);								  
	GotoxyDraw(OFFSET_TITLE_X + 4, OFFSET_TITLE_Y + 2, "W O R M  G A");
	Sleep(50);								  
	GotoxyDraw(OFFSET_TITLE_X + 4, OFFSET_TITLE_Y + 2, "W O R M  G A M");
	Sleep(50);								  
	GotoxyDraw(OFFSET_TITLE_X + 4, OFFSET_TITLE_Y + 2, "W O R M  G A M E");
	SetTextColor(COLOR_BLACK, COLOR_YELLOW);
	GotoxyDraw(OFFSET_TITLE_X, OFFSET_TITLE_Y + 9, "           △ ");
	GotoxyDraw(OFFSET_TITLE_X, OFFSET_TITLE_Y + 10, "         ◁  ▷ : 방향전환");
	GotoxyDraw(OFFSET_TITLE_X, OFFSET_TITLE_Y + 11, "           ▽");
	GotoxyDraw(OFFSET_TITLE_X, OFFSET_TITLE_Y + 12, "              P : Pause");
	GotoxyDraw(OFFSET_TITLE_X - 3, OFFSET_TITLE_Y + 13, "  (메인 화면에서) ESC : Exit");


	GotoxyDraw(OFFSET_TITLE_X, OFFSET_TITLE_Y + 7, "★ Please Enter Any Key to Start ★");
	while (TRUE)
	{
		if (_kbhit())
		{
			if (_getch() == KEY_ESC)
			{
				Exit();
			}
			break;
		}
		if ((nCnt % 25) == 0)
		{
			GotoxyDraw(OFFSET_TITLE_X, OFFSET_TITLE_Y + 7, "                                                                 ");
		}
		if (nCnt % 50 == 0)
		{
			GotoxyDraw(OFFSET_TITLE_X, OFFSET_TITLE_Y + 7, "★ Please Enter Any Key to Start ★");
			nCnt = 0;
		}

		Sleep(10); // 00.1초 딜레이  
		nCnt++;
	}

	while (_kbhit())
	{
		_getch();//버퍼에 기록된 키값을 버림 
	}
}
void Game(void)
{
	system("cls");
	InitHeadTail();
	ResetGameMapData();
	DrawWall();

	curPos.X = DEFAULTPOS_X;
	curPos.Y = DEFAULTPOS_Y;
	curDir = DIR_RIGHT;
	Speed = DEFAULTSPEED;
	Score = 0;
	DrawUIFrame();
	UpdateUI();
	COORD arrPos[BODYLEN] = { 0 };
	for (int i = BODYLEN - 1; i >= 0; i--)
	{
		arrPos[i].X = curPos.X - i;
		arrPos[i].Y = curPos.Y;
		InsertFromHead(arrPos[i]);
		if (i == 0)
		{
			SetTextColor(GAME_BG_COLOR, HEAD_COLOR);
			GotoxyDraw(OFFSET_GAME_X + arrPos[i].X + 1,  OFFSET_GAME_Y + arrPos[i].Y + 1, DRAW_WORM_HEAD);
		}
		else
		{
			gameMap[arrPos[i].X][arrPos[i].Y] = DATA_BODY;
			SetTextColor(GAME_BG_COLOR, BODY_COLOR);
			GotoxyDraw(OFFSET_GAME_X + arrPos[i].X + 1, OFFSET_GAME_Y + arrPos[i].Y + 1, DRAW_WORM_BODY);
		}
	}
	CreateItem();

	int MoveT = 0;

	while (TRUE)
	{
		KeyboardControl();
		if ((float)MoveT >= Speed)
		{
			MoveWorm();
			if (IsGameOver())
			{
				//게임오버			
				DeleteAllNode();
				ShowGameOver();
				break;
			}
			if ((curPos.X == itemPos.X &&
				curPos.Y == itemPos.Y))
			{
				//아이템 획득
				Score += SCOREUNIT;
				Speed -= (Speed * ((float)SPEEDUNITP / 100.0f));
				UpdateUI();
				CreateItem();
				isGetItem = TRUE;
			}

			MoveT = 0;
		}

		MoveT += FRAME_UNIT;
		Sleep(FRAME_UNIT);
	}
}
void Exit(void)
{
	system("cls");
	SetTextColor(EXIT_BG_COLOR, EXIT_COLOR);

	for (int i = UI_POS_END_X; i < UI_POS_END_X + UI_SIZE_END_X; i++)
	{
		for (int j = UI_POS_END_Y; j < UI_POS_END_Y + UI_SIZE_END_Y; j++)
		{
			if ((i == UI_POS_END_X) || (i == UI_POS_END_X + UI_SIZE_END_X - 1) ||
				(j == UI_POS_END_Y) || (j == UI_POS_END_Y + UI_SIZE_END_Y - 1))
			{
				GotoxyDraw(i, j, DRAW_UI_END_FRAME);
			}
			else
			{
				GotoxyDraw(i, j, DRAW_EMPTY);
			}
		}
	}
	GotoxyDraw(UI_POS_END_X + 8, UI_POS_END_Y + 7, "게임 프로그램을 종료합니다.");
	Gotoxy(0, UI_POS_END_Y + UI_SIZE_END_Y + 1);
	exit(0);
}

void Init(void)
{
	srand((unsigned int)time(NULL));
	SetNoCursor();
}

void ResetGameMapData(void)
{
	for (int i = 0; i < SIZE_GAMEMAP_X; i++)
	{
		for (int j = 0; j < SIZE_GAMEMAP_Y; j++)
		{
			gameMap[i][j] = DATA_EMPTY;
		}
	}
}

void DrawWall(void)
{
	SetTextColor(GAME_BG_COLOR, WALL_COLOR);
	for (int i = OFFSET_GAME_X; i < (OFFSET_GAME_X + SIZE_GAMEMAP_X + 1); i++)
	{
		GotoxyDraw(i, OFFSET_GAME_Y, DRAW_GAME_WALL);
		GotoxyDraw(i, OFFSET_GAME_Y + SIZE_GAMEMAP_Y + 1, DRAW_GAME_WALL);
	}
	for (int i = OFFSET_GAME_Y; i < (OFFSET_GAME_Y + SIZE_GAMEMAP_Y + 2); i++)
	{
		GotoxyDraw(OFFSET_GAME_X, i, DRAW_GAME_WALL);
		GotoxyDraw(OFFSET_GAME_X + SIZE_GAMEMAP_X + 1, i, DRAW_GAME_WALL);
	}
}

void MoveWorm(void)
{
	SetTextColor(GAME_BG_COLOR, BODY_COLOR);
	GotoxyDraw(OFFSET_GAME_X + curPos.X + 1, OFFSET_GAME_Y + curPos.Y + 1, DRAW_WORM_BODY);
	gameMap[curPos.X][curPos.Y] = DATA_BODY;

	switch (curDir)
	{
	case DIR_LEFT:
	{
		curPos.X--;
		lastMoveDir = DIR_LEFT;
	}
	break;
	case DIR_RIGHT:
	{
		curPos.X++;
		lastMoveDir = DIR_RIGHT;
	}
	break;
	case DIR_UP:
	{
		curPos.Y--;
		lastMoveDir = DIR_UP;
	}
	break;
	case DIR_DOWN:
	{
		curPos.Y++;
		lastMoveDir = DIR_DOWN;
	}
	break;
	}

	InsertFromHead(curPos);
	SetTextColor(GAME_BG_COLOR, HEAD_COLOR);
	GotoxyDraw(OFFSET_GAME_X + curPos.X + 1, OFFSET_GAME_Y + curPos.Y + 1, DRAW_WORM_HEAD);

	if (!isGetItem)
	{
		COORD tailPos = DeleteFromTail();
		GotoxyDraw(OFFSET_GAME_X + tailPos.X + 1, OFFSET_GAME_Y + tailPos.Y + 1, DRAW_EMPTY);
		gameMap[tailPos.X][tailPos.Y] = DATA_EMPTY;
	}
	else
	{
		isGetItem = FALSE;
	}
}

BOOL IsGameOver()
{
	if (curPos.X >= SIZE_GAMEMAP_X ||
		curPos.X < 0 ||
		curPos.Y >= SIZE_GAMEMAP_Y ||
		curPos.Y < 0 ||
		gameMap[curPos.X][curPos.Y] == DATA_BODY)
	{
		return TRUE;
	}
	return FALSE;
}

void CreateItem(void)
{
	COORD randPos = { 0 };
	do
	{
		randPos.X = rand() % SIZE_GAMEMAP_X;
		randPos.Y = rand() % SIZE_GAMEMAP_Y;
	} while 
		((gameMap[randPos.X][randPos.Y] == DATA_BODY) ||
		(curPos.X == randPos.X && curPos.Y == randPos.Y));

	gameMap[randPos.X][randPos.Y] = DATA_ITEM;
	SetTextColor(GAME_BG_COLOR, ITEM_COLOR);
	GotoxyDraw(OFFSET_GAME_X + randPos.X + 1, OFFSET_GAME_Y + randPos.Y + 1, DRAW_ITEM);
	itemPos = randPos;
}

void DrawUIFrame(void)
{
	SetTextColor(UI_GAME_BG_COLOR, UI_GAME_UI_FRAME_COLOR);
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (i == 0 || i == 11 || j == 0 || j == 3)
			{
				GotoxyDraw(UI_POS_GAME_X + i + 1, UI_POS_GAME_Y + j - 1, DRAW_UI_FRAME);
			}
		}
	}
}

void UpdateUI(void)
{
	SetTextColor(UI_GAME_BG_COLOR, UI_GAME_COLOR);
	GotoxyDraw(UI_POS_GAME_X + 2, UI_POS_GAME_Y, "현재 점수 : ");
	printf("%d", Score);
	GotoxyDraw(UI_POS_GAME_X + 2, UI_POS_GAME_Y + 1, "현재 속도 : ");
	printf("%.1f", Speed);
}

void ShowGameOver(void)
{
	SetTextColor(GAME_BG_COLOR, UI_GAME_UI_FRAME_COLOR);

	for (int i = UI_POS_END_X; i < UI_POS_END_X + UI_SIZE_END_X; i++)
	{
		for (int j = UI_POS_END_Y; j < UI_POS_END_Y + UI_SIZE_END_Y; j++)
		{
			if ((i == UI_POS_END_X) || (i == UI_POS_END_X + UI_SIZE_END_X - 1) ||
				(j == UI_POS_END_Y) || (j == UI_POS_END_Y + UI_SIZE_END_Y - 1))
			{
				GotoxyDraw(i, j, DRAW_UI_END_FRAME);
			}
			else
			{
				GotoxyDraw(i, j, DRAW_EMPTY);
			}
		}
	}

	SetTextColor(EXIT_BG_COLOR, UI_GAME_COLOR);
	GotoxyDraw(UI_POS_END_X + 13, UI_POS_END_Y + 3, "게임 오버...");
	GotoxyDraw(UI_POS_END_X + 8, UI_POS_END_Y + 9, "최종 점수 : ");
	printf("%d", Score);
	GotoxyDraw(UI_POS_END_X + 5, UI_POS_END_Y + 12, "아무 키나 누르시면 시작화면으로 돌아갑니다");
	_getch();
}

void Pause(void)
{
	SetTextColor(GAME_BG_COLOR, UI_PAUSE_COLOR);

	for (int i = 0; i < SIZE_GAMEMAP_X; i++)
	{
		for (int j = 0; j < OFFSET_GAME_Y; j++)
		{
			if (i == 0 || j == 0 || i == SIZE_GAMEMAP_X - 1 || j == OFFSET_GAME_Y - 1)
			{
				GotoxyDraw(OFFSET_GAME_X + i + 1, j, DRAW_PAUSE_FRAME);
			}
		}
	}
	GotoxyDraw(OFFSET_GAME_X + 7, 2, "일시 정지 중...");
	GotoxyDraw(OFFSET_GAME_X + 3, 3, "(해제하려면 아무 키나 누르세요)");

	if (_getch() == KEY_DIRECTION)
	{
		_getch();
	}

	for (int i = 0; i < SIZE_GAMEMAP_X; i++)
	{
		for (int j = 0; j < OFFSET_GAME_Y; j++)
		{
			GotoxyDraw(OFFSET_GAME_X + i + 1, j, DRAW_EMPTY);		
		}
	}
}
