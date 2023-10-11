#include "main.h"

/* 색상 설정 */
void SetColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

/* 좌표 설정 */
void gotoxy(int x, int y)
{
	COORD Cur = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

/* 커서 유무 */
void CursorView(bool show)
{
	CONSOLE_CURSOR_INFO CurInfo = { 20, show };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
}

/* 박스 만들기 */
void MakeBox(int x, int y, int x2, int y2)
{
	/* 모서리 채우기*/
	gotoxy(x, y);
	printf("┌");
	gotoxy(x2, y);
	printf("┐");
	gotoxy(x, y2);
	printf("└");
	gotoxy(x2, y2);
	printf("┘");
	/* 가로 채우기 */
	for (int i = x + 1; i < x2; i++)
	{
		gotoxy(i, y);
		printf("─");
		gotoxy(i, y2);
		printf("─");
	}
	/* 세로 채우기 */
	for (int i = y + 1; i < y2; i++)
	{
		gotoxy(x, i);
		printf("│");
		gotoxy(x2, i);
		printf("│");
	}
}