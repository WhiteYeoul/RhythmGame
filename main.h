#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <time.h>
#include <conio.h>
#include <stdio.h>
#include <stdbool.h>
#include <Windows.h>
#include <process.h>
/* ���� ����� �ʿ��� */
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

#define delay(n) Sleep(n)
#define cls system("cls")
#define pause system("pause")
/* Ű �Է� */
#define keystate(k) GetAsyncKeyState(k) & 0x8000
/* ���ڻ�(���) */
#define FOREGROUND_WHITE 0X0001 | 0X0004 | 0X0002
/* ����(���) */
#define BACKGROUND_WHITE 0X0010 | 0X0020 | 0X0040

/* ����ϱ� ���� ���� */
void SetColor(int color);
void gotoxy(int x, int y);
void CursorView(bool show);

/* �ʱ� ���� */
void Init();
void MakeBox(int x, int y, int x2, int y2);

/* ���� ���� */
int ExitGame();

/* ȭ�� ��� */
void PrintMainDisplay();
void PrintSelectMusic();

/* �ΰ��� */
void PrintInGameDisplay();
void PlayMusic(int num);

/* Ű Ȯ�� */
void PressD();
void PressF();
void PressJ();
void PressK();

/* ���� ���۸� */
void Render();

/* ��� ��� */
void ResultScreen();