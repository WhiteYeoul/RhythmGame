#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <time.h>
#include <conio.h>
#include <stdio.h>
#include <stdbool.h>
#include <Windows.h>
#include <process.h>
/* 음악 재생에 필요함 */
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

#define delay(n) Sleep(n)
#define cls system("cls")
#define pause system("pause")
/* 키 입력 */
#define keystate(k) GetAsyncKeyState(k) & 0x8000
/* 글자색(흰색) */
#define FOREGROUND_WHITE 0X0001 | 0X0004 | 0X0002
/* 배경색(흰색) */
#define BACKGROUND_WHITE 0X0010 | 0X0020 | 0X0040

/* 사용하기 편한 설정 */
void SetColor(int color);
void gotoxy(int x, int y);
void CursorView(bool show);

/* 초기 설정 */
void Init();
void MakeBox(int x, int y, int x2, int y2);

/* 종료 여부 */
int ExitGame();

/* 화면 출력 */
void PrintMainDisplay();
void PrintSelectMusic();

/* 인게임 */
void PrintInGameDisplay();
void PlayMusic(int num);

/* 키 확인 */
void PressD();
void PressF();
void PressJ();
void PressK();

/* 더블 버퍼링 */
void Render();

/* 결과 출력 */
void ResultScreen();