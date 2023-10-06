/*
	노트 생성과 싱크 맞추기 남음
*/

#include "main.h"

/* 음악 재생에 필요함 */
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

/* 입력 키 */
#define KEY_D 0x44 // D
#define KEY_F 0x46 // F
#define KEY_J 0x4A // J
#define KEY_K 0x4B // K

/* 동작 순서 */
enum Sequence {
	Main,
	Select,
	Playing
}; 
enum Sequence sequence = Main;

/* 색상 */
typedef enum _ColorKinds {
	black,
	blue,
	green,
	skyBlue,
	red,
	pink,
	orange,
	white,
	gray,
	lightBlue,
	brightgreen,
	sky,
	brightRed,
	brightPink,
	brightYellow,
	brightWhite
}ColorKinds;
ColorKinds colorkinds;

int main(void)
{
	Init();
	while (true) {
		PrintMainDisplay();
		PrintSelectMusic();
		PrintInGameDisplay();
		KeyInput();
	}
	return;
}

void Init()
{
	/* 커서 유무 설정 */
	CursorView(0);
	/* CMD 창 색 설정 */
	system("COLOR 0F");
	/* CMD 창 크기 조절 */
	system("mode con: cols=150 lines=50");
	/* CMD 창 제목 수정 */
	system("title EZ2MAX");
}

void PrintMainDisplay()
{
	if (sequence == Main)
	{
		/* 첫 화면 출력 */
		gotoxy(30, 10); printf(":\'########::::\'########:::::\'#######:::::\'##::::\'##:::::::\'###:::::::\'##::::\'##:");
		gotoxy(30, 11); printf(": ##.....:::::..... ##:::::\'##.... ##:::: ###::\'###::::::\'## ##::::::. ##::\'##::");
		gotoxy(30, 12); printf(": ##:::::::::::::: ##::::::..::::: ##:::: ####\'####:::::\'##:. ##::::::. ##\'##:::");
		gotoxy(30, 13); printf(": ######::::::::: ##::::::::\'#######::::: ## ### ##::::\'##:::. ##::::::. ###::::");
		gotoxy(30, 14); printf(": ##...::::::::: ##::::::::\'##::::::::::: ##. #: ##:::: #########:::::: ## ##:::");
		gotoxy(30, 15); printf(": ##::::::::::: ##::::::::: ##::::::::::: ##:.:: ##:::: ##.... ##::::: ##:. ##::");
		gotoxy(30, 16); printf(": ########:::: ########:::: #########:::: ##:::: ##:::: ##:::: ##:::: ##:::. ##:");
		gotoxy(30, 17); printf(":........:::::........:::::.........:::::..:::::..:::::..:::::..:::::..:::::..::");
		gotoxy(55, 30); printf("Press Enter Key To Start!!!");

		/* 엔터 입력 확인 */
		while (true)
		{
			if (keystate(VK_RETURN)) // Enter가 입력되면
			{
				cls;				 // 화면 지움
				delay(100);
				sequence = Select;
				break;
			}
		}
	}
	return;
}

void PrintSelectMusic()
{
	if (sequence == Select)
	{
		/* 노래 선택 화면 출력 */
		gotoxy(10, 10); printf(":'######::'########:'##:::::::'########::'######::'########:");
		gotoxy(10, 11); printf("'##... ##: ##.....:: ##::::::: ##.....::'##... ##:... ##..::");
		gotoxy(10, 12); printf(" ##:::..:: ##::::::: ##::::::: ##::::::: ##:::..::::: ##::::");
		gotoxy(10, 13); printf(". ######:: ######::: ##::::::: ######::: ##:::::::::: ##::::");
		gotoxy(10, 14); printf(":..... ##: ##...:::: ##::::::: ##...:::: ##:::::::::: ##::::");
		gotoxy(10, 15); printf("'##::: ##: ##::::::: ##::::::: ##::::::: ##::: ##:::: ##::::");
		gotoxy(10, 16); printf(". ######:: ########: ########: ########:. ######::::: ##::::");
		gotoxy(10, 17); printf(":......:::........::........::........:::......::::::..:::::");
		gotoxy(15, 22); printf("'##::::'##:'##::::'##::'######::'####::'######::");
		gotoxy(15, 23); printf(" ###::'###: ##:::: ##:'##... ##:. ##::'##... ##:");
		gotoxy(15, 24); printf(" ####'####: ##:::: ##: ##:::..::: ##:: ##:::..::");
		gotoxy(15, 25); printf(" ## ### ##: ##:::: ##:. ######::: ##:: ##:::::::");
		gotoxy(15, 26); printf(" ##. #: ##: ##:::: ##::..... ##:: ##:: ##:::::::");
		gotoxy(15, 27); printf(" ##:.:: ##: ##:::: ##:'##::: ##:: ##:: ##::: ##:");
		gotoxy(15, 28); printf(" ##:::: ##:. #######::. ######::'####:. ######::");
		gotoxy(15, 29); printf("..:::::..:::.......::::......:::....:::......:::");
		gotoxy(85, 10); printf("┌───────────────────────────────────────────────┐");
		for (int i = 11; i < 30; i++) { gotoxy(85, i); printf("│                                               │"); }
		gotoxy(85, 30); printf("└───────────────────────────────────────────────┘");

		int Menu = 0;
		/* 노래 선택 확인 */
		while (true)
		{
			if (keystate(VK_UP)) // 위 방향키
			{
				if (Menu == 0) Menu = 2;
				else Menu -= 1;
			}
			else if (keystate(VK_DOWN)) // 아래 방향키
			{
				if (Menu == 2) Menu = 0;
				else Menu += 1;
			}
			else if (keystate(VK_RETURN)) // 엔터키
			{
				break;
			}
			/* 선택된 메뉴 - 파란색, 그 외 메뉴 - 흰색 */
			switch (Menu) {
			case 0:
				SetColor(black, blue);
				gotoxy(90, 15); printf("♪ Xeon");
				SetColor(black,white);
				gotoxy(90, 20); printf("♪ JUSTITIA");
				gotoxy(90, 25); printf("♪ IronCloud");
				break;
			case 1:
				gotoxy(90, 15); printf("♪ Xeon");
				SetColor(black, blue);
				gotoxy(90, 20); printf("♪ JUSTITIA");
				SetColor(black, white);
				gotoxy(90, 25); printf("♪ IronCloud");
				break;
			case 2:
				gotoxy(90, 15); printf("♪ Xeon");
				gotoxy(90, 20); printf("♪ JUSTITIA");
				SetColor(black, blue);
				gotoxy(90, 25); printf("♪ IronCloud");
				SetColor(black, white);
				break;
			default:
				break;
			}
			delay(100);
		}
		/* 화면 초기화 */
		cls;

		/* 선택한 노래 실행 */
		if (Menu == 0)
		{
			sequence = Playing;
			PlayMusic(Menu);
		}

		else if (Menu == 1)
		{
			sequence = Playing;
			PlayMusic(Menu);
		}

		else if (Menu == 2)
		{
			sequence = Playing;
			PlayMusic(Menu);
		}
	}
	return;
}

void PrintInGameDisplay()
{
	if (sequence == Playing)
	{
		/* 노트 구간 */
		gotoxy(3, 1); printf("┌───────────────────────────────────────────────────┐");
		gotoxy(3, 48); printf("└───────────────────────────────────────────────────┘");
		gotoxy(4, 41); printf("───────────────────────────────────────────────────");

		for (int i = 2; i < 48; i++)
		{
			gotoxy(3, i);
			printf("│");
		}
		for (int i = 2; i < 48; i++)
		{
			gotoxy(55, i);
			printf("│");
		}

		/* 정보 구간 */
		gotoxy(60, 42); printf("┌────────────────────────────────────────────────────────────────────────────────────┐");
		gotoxy(60, 48); printf("└────────────────────────────────────────────────────────────────────────────────────┘");


		for (int i = 43; i < 48; i++)
		{
			gotoxy(60, i);
			printf("│");
		}
		for (int i = 43; i < 48; i++)
		{
			gotoxy(145, i);
			printf("│");
		}
	}
}

void PlayMusic(int a)
{
	if (sequence == Playing)
	{
		if (a == 0)
		{
			PlaySound(TEXT("XeoN.wav"), 0, SND_FILENAME | SND_ASYNC);
			gotoxy(70, 45); printf("♪ Now Playing - XeoN");
			CreateNote(a); // 구현해야 될 곳

		}

		else if (a == 1)
		{
			PlaySound(TEXT("JUSTITIA.wav"), 0, SND_FILENAME | SND_ASYNC);
			gotoxy(70, 45); printf("♪ Now Playing - JUSTITIA");
			CreateNote(a);
		}

		else if (a == 2)
		{
			PlaySound(TEXT("IronCloud.wav"), 0, SND_FILENAME | SND_ASYNC);
			gotoxy(70, 45); printf("♪ Now Playing - IronCloud");
			CreateNote(a);
		}
	}
}

void KeyInput()
{
	if (sequence == Playing) 
	{
		/* 키보드 - D */
		if (keystate(KEY_D))
		{
			gotoxy(10, 44);
			printf("■"); // 키가 눌리면 그려줌
		}
		else
		{
			gotoxy(10, 44);
			printf("  "); // 키가 떨어지면 지워줌
		}
		/* 키보드 - F */
		if (keystate(KEY_F))
		{
			gotoxy(22, 44);
			printf("■");
		}
		else
		{
			gotoxy(22, 44);
			printf("  ");
		}
		/* 키보드 - J */
		if (keystate(KEY_J))
		{
			gotoxy(35, 44);
			printf("■");
		}
		else
		{
			gotoxy(35, 44);
			printf("  ");
		}
		/* 키보드 - K */
		if (keystate(KEY_K))
		{
			gotoxy(47, 44);
			printf("■");
		}
		else
		{
			gotoxy(47, 44);
			printf("  ");
		}
	}
}


