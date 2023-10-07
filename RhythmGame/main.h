#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <time.h>
#include <math.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <Windows.h>
#include <process.h>
/* 음악 재생에 필요함 */
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

#define delay(n) Sleep(n)
#define cls system("cls")
#define pause system("pause")
#define keystate(k) GetAsyncKeyState(k) & 0x0001
/* 글자색(흰색) */
#define FOREGROUND_WHITE 0X0001 | 0X0004 | 0X0002
/* 배경색(흰색 */
#define BACKGROUND_WHITE 0X0010 | 0X0020 | 0X0040

void SetColor(int color);
void gotoxy(int x, int y);
void CursorView(bool show);

void Init();
void PrintMainDisplay();
void PrintSelectMusic();
void PrintInGameDisplay();
void PlayMusic();

/* 키보드 입력 */
void KeyInput();

/* 노트 불러오기 */
void LoadMap();
/* 노트 출력 */
void PrintMap();

/* 결과 */
void ResultScreen();