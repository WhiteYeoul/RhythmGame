#include "main.h"

/* ���� ���� */
void SetColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

/* ��ǥ ���� */
void gotoxy(int x, int y)
{
	COORD Cur = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

/* Ŀ�� ���� */
void CursorView(bool show)
{
	CONSOLE_CURSOR_INFO CurInfo = { 20, show };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
}