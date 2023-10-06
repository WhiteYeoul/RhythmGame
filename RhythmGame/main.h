#pragma once

#include <stdio.h>
#include <Windows.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>

#define cls system("cls")
#define pause system("pause")
#define keystate(k) GetAsyncKeyState(k)
#define delay(n) Sleep(n)

void gotoxy(int x, int y);
void CursorView(bool show);

void Init();
void PrintMainDisplay();
void PrintSelectMusic();
void PrintInGameDisplay();
void PlayMusic(int a);

void KeyInput();

void CreateNote(int b);
void PrintNote();
