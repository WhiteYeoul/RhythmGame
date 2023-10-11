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

/* �ڽ� ����� */
void MakeBox(int x, int y, int x2, int y2)
{
	/* �𼭸� ä���*/
	gotoxy(x, y);
	printf("��");
	gotoxy(x2, y);
	printf("��");
	gotoxy(x, y2);
	printf("��");
	gotoxy(x2, y2);
	printf("��");
	/* ���� ä��� */
	for (int i = x + 1; i < x2; i++)
	{
		gotoxy(i, y);
		printf("��");
		gotoxy(i, y2);
		printf("��");
	}
	/* ���� ä��� */
	for (int i = y + 1; i < y2; i++)
	{
		gotoxy(x, i);
		printf("��");
		gotoxy(x2, i);
		printf("��");
	}
}