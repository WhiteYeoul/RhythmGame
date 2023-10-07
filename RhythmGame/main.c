/*
	1. ��Ʈ����
	2. ��ũ����
	3. �ڷΰ���
	4. �������
	5. �ɼ�
	6. ��Ʈ�� Ű���� �Է� Ȯ�� �� �޺�
*/

#include "main.h"

/* �Է� Ű */
#define KEY_D 0x44 // D
#define KEY_F 0x46 // F
#define KEY_J 0x4A // J
#define KEY_K 0x4B // K

struct KeyLine {
	int Line1;
	int Line2;
	int Line3;
	int Line4;
};
struct KeyLine keyLine;

/* ���� ���� */
enum Sequence {
	Main,
	Select,
	Playing,
	Result
}; 
enum Sequence sequence = Main;

enum Music {
	Xeon,
	JUSTITIA,
	IronCloud
};
enum Music music;

int KeyAct[4] = { 0, };
int Map[1000][4] = { 0, };
int MapPlaying = FALSE;

HANDLE InputHandle;
HANDLE MapHandle;

void Init()
{
	/* Ŀ�� ���� ���� */
	CursorView(0);
	/* CMD â �� ���� */
	system("COLOR 0F");
	/* CMD â ũ�� ���� */
	system("mode con: cols=150 lines=50");
	/* CMD â ���� ���� */
	system("title EZ2MAX");
}

void PrintMainDisplay()
{
	if (sequence == Main)
	{
		/* ù ȭ�� ��� */
		gotoxy(30, 10); printf(":\'########::::\'########:::::\'#######:::::\'##::::\'##:::::::\'###:::::::\'##::::\'##:");
		gotoxy(30, 11); printf(": ##.....:::::..... ##:::::\'##.... ##:::: ###::\'###::::::\'## ##::::::. ##::\'##::");
		gotoxy(30, 12); printf(": ##:::::::::::::: ##::::::..::::: ##:::: ####\'####:::::\'##:. ##::::::. ##\'##:::");
		gotoxy(30, 13); printf(": ######::::::::: ##::::::::\'#######::::: ## ### ##::::\'##:::. ##::::::. ###::::");
		gotoxy(30, 14); printf(": ##...::::::::: ##::::::::\'##::::::::::: ##. #: ##:::: #########:::::: ## ##:::");
		gotoxy(30, 15); printf(": ##::::::::::: ##::::::::: ##::::::::::: ##:.:: ##:::: ##.... ##::::: ##:. ##::");
		gotoxy(30, 16); printf(": ########:::: ########:::: #########:::: ##:::: ##:::: ##:::: ##:::: ##:::. ##:");
		gotoxy(30, 17); printf(":........:::::........:::::.........:::::..:::::..:::::..:::::..:::::..:::::..::");
		gotoxy(55, 30); printf("Press Enter Key To Start!!!");

		/* ���� �Է� Ȯ�� */
		while (TRUE)
		{
			if (keystate(VK_RETURN)) // Enter�� �ԷµǸ�
			{
				cls;				 // ȭ�� ����
				delay(100);
				sequence = Select;   // ���� ����
				break;
			}
		}
	}
}

void PrintSelectMusic()
{
	if (sequence == Select)
	{
		/* �뷡 ���� ȭ�� ��� */
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
		gotoxy(85, 10); printf("��������������������������������������������������������������������������������������������������");
		for (int i = 11; i < 30; i++) { gotoxy(85, i); printf("��                                               ��"); }
		gotoxy(85, 30); printf("��������������������������������������������������������������������������������������������������");

		int Menu = 0;
		/* �뷡 ���� Ȯ�� */
		while (TRUE)
		{
			if (keystate(VK_UP)) // �� ����Ű
			{
				if (Menu == 0) Menu = 2;
				else Menu -= 1;
			}
			else if (keystate(VK_DOWN)) // �Ʒ� ����Ű
			{
				if (Menu == 2) Menu = 0;
				else Menu += 1;
			}
			else if (keystate(VK_RETURN)) // ����Ű
			{
				break;
			}
			/* ���õ� �޴� - �Ķ���, �� �� �޴� - ��� */
			switch (Menu) {
			case 0:
				SetColor(FOREGROUND_BLUE);
				gotoxy(90, 15); printf("�� Xeon");
				SetColor(FOREGROUND_WHITE);
				gotoxy(90, 20); printf("�� JUSTITIA");
				gotoxy(90, 25); printf("�� IronCloud");
				break;
			case 1:
				gotoxy(90, 15); printf("�� Xeon");
				SetColor(FOREGROUND_BLUE);
				gotoxy(90, 20); printf("�� JUSTITIA");
				SetColor(FOREGROUND_WHITE);
				gotoxy(90, 25); printf("�� IronCloud");
				break;
			case 2:
				gotoxy(90, 15); printf("�� Xeon");
				gotoxy(90, 20); printf("�� JUSTITIA");
				SetColor(FOREGROUND_BLUE);
				gotoxy(90, 25); printf("�� IronCloud");
				SetColor(FOREGROUND_WHITE);
				break;
			default:
				break;
			}
			delay(100);
		}
		/* ȭ�� �ʱ�ȭ */
		cls;

		/* ������ �뷡 ���� */
		if (Menu == 0)
		{
			delay(1);
			sequence = Playing;
			music = Xeon;
		}

		else if (Menu == 1)
		{
			delay(1);
			sequence = Playing;
			music = JUSTITIA;
		}

		else if (Menu == 2)
		{
			delay(1);
			sequence = Playing;
			music = IronCloud;
		}
	}
}

void PrintInGameDisplay()
{
	if (sequence == Playing)
	{
		/* ��Ʈ ���� */
		gotoxy(3, 1); printf("������������������������������������������������������������������������������������������������������");
		gotoxy(3, 48); printf("������������������������������������������������������������������������������������������������������");
		gotoxy(4, 41); printf("��������������������������������������������������������������������������������������������������");

		for (int i = 2; i < 48; i++)
		{
			gotoxy(3, i);
			printf("��");
		}
		for (int i = 2; i < 48; i++)
		{
			gotoxy(53, i);
			printf("��");
		}

		/* ���� ���� */
		gotoxy(60, 42); printf("����������������������������������������������������������������������������������������������������������������������������������������������������������������������������");
		gotoxy(60, 48); printf("����������������������������������������������������������������������������������������������������������������������������������������������������������������������������");


		for (int i = 43; i < 48; i++)
		{
			gotoxy(60, i);
			printf("��");
		}
		for (int i = 43; i < 48; i++)
		{
			gotoxy(145, i);
			printf("��");
		}
	}
}

void PlayMusic()
{
	if (sequence == Playing)
	{
		if (music == Xeon)
		{
			PlaySound(TEXT("XeoN.wav"), 0, SND_FILENAME | SND_ASYNC);
			gotoxy(70, 45); printf("�� Now Playing - XeoN");
		}

		else if (music == JUSTITIA)
		{
			PlaySound(TEXT("JUSTITIA.wav"), 0, SND_FILENAME | SND_ASYNC);
			gotoxy(70, 45); printf("�� Now Playing - JUSTITIA");
		}

		else if (music == IronCloud)
		{
			PlaySound(TEXT("IronCloud.wav"), 0, SND_FILENAME | SND_ASYNC);
			gotoxy(70, 45); printf("�� Now Playing - IronCloud");
		}
	}
}

void KeyInput()
{
	if (sequence == Playing)
	{
		while (TRUE) {
			/* Ű���� - D */
			if (keystate(KEY_D))
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_WHITE);
				KeyAct[0] = TRUE;
				for (int i = 42; i < 48; i++)
				{
					gotoxy(7, i);
					printf("       ");
				}
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), NULL);
				KeyAct[0] = FALSE;
				for (int i = 42; i < 48; i++)
				{
					gotoxy(7, i);
					printf("       ");
				}
			}
			/* Ű���� - F */
			if (keystate(KEY_F))
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_WHITE);
				KeyAct[1] = TRUE;
				for (int i = 42; i < 48; i++)
				{
					gotoxy(19, i);
					printf("       ");
				}
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), NULL);
				KeyAct[1] = FALSE;
				for (int i = 42; i < 48; i++)
				{
					gotoxy(19, i);
					printf("       ");
				}
			}
			/* Ű���� - J */
			if (keystate(KEY_J))
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_WHITE);
				KeyAct[2] = TRUE;
				for (int i = 42; i < 48; i++)
				{
					gotoxy(32, i);
					printf("       ");
				}
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), NULL);
				KeyAct[2] = FALSE;
				for (int i = 42; i < 48; i++)
				{
					gotoxy(32, i);
					printf("       ");
				}
			}
			/* Ű���� - K */
			if (keystate(KEY_K))
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_WHITE);
				KeyAct[3] = TRUE;
				for (int i = 42; i < 48; i++)
				{
					gotoxy(44, i);
					printf("       ");
				}
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), NULL);
				KeyAct[3] = FALSE;
				for (int i = 42; i < 48; i++)
				{
					gotoxy(44, i);
					printf("       ");
				}
			}
		}
	}
}

void LoadMap()
{
	if (sequence == Playing) 
	{
		if (music == Xeon) 
		{
			int count = 0;
			char line[256];
			FILE* file = fopen("XeoN.txt", "r");
			while (!feof(file))
			{
				fgets(line, sizeof(line), file);
				for (int i = 0; i < 4; i++)
				{
					Map[count][i] = line[i];
				}
				count++;
			}
			count = 0;
			fclose(file);
		}
		else if (music == JUSTITIA) 
		{
			int count = 0;
			char line[256];
			FILE* file = fopen("JUSTITIA.txt", "r");
			while (!feof(file))
			{
				fgets(line, sizeof(line), file);
				for (int i = 0; i < 4; i++)
				{
					Map[count][i] = line[i];
				}
				count++;
			}
			count = 0;
			fclose(file);
		}
		else if (music == IronCloud) 
		{
			int count = 0;
			char line[256];
			FILE* file = fopen("IronCloud.txt", "r");
			while (!feof(file))
			{
				fgets(line, sizeof(line), file);
				for (int i = 0; i < 4; i++)
				{
					Map[count][i] = line[i];
				}
				count++;
			}
			count = 0;
			fclose(file);
		}
	}
}

void PrintMap()
{
	if (sequence == Playing)
	{
		for (int i = 0; i < 1000; i++)
		{
			if ((Map[i][0] | Map[i][1] | Map[i][2] | Map[i][3]) == 0) break;

			for (int j = 3; j < 40; j++)
			{
				if (Map[i][0] == '1')
				{
					keyLine.Line1 = 7;
					gotoxy(keyLine.Line1, j - 1);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), NULL);
					printf("       ");
					gotoxy(keyLine.Line1, j);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_BLUE);
					printf("       ");
					if (j > 38)
					{
						gotoxy(keyLine.Line1, 39);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), NULL);
						printf("       ");
					}
				}
				if (Map[i][1] == '1')
				{
					keyLine.Line2 = 19;
					gotoxy(keyLine.Line2, j - 1);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), NULL);
					printf("       ");
					gotoxy(keyLine.Line2, j);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED);
					printf("       ");
					if (j > 38)
					{
						gotoxy(keyLine.Line2, 39);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), NULL);
						printf("       ");
					}
				}
				if (Map[i][2] == '1')
				{
					keyLine.Line3 = 32;
					gotoxy(keyLine.Line3, j - 1);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), NULL);
					printf("       ");
					gotoxy(keyLine.Line3, j);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN);
					printf("       ");
					if (j > 38)
					{
						gotoxy(keyLine.Line3, 39);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), NULL);
						printf("       ");
					}
				}
				if (Map[i][3] == '1')
				{
					keyLine.Line4 = 44;
					gotoxy(keyLine.Line4, j - 1);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), NULL);
					printf("       ");
					gotoxy(keyLine.Line4, j);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN | BACKGROUND_RED);
					printf("       ");
					if (j > 38)
					{
						gotoxy(keyLine.Line4, 39);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), NULL);
						printf("       ");
					}
				}
				delay(10);
			}
		}
	}
}

void ResultScreen()
{
	if (sequence == Result)
	{
		/* ���� ���� */
	}
}

int main(void)
{
	/* ���۾� */
	Init();

	/* ù ȭ�� */
	PrintMainDisplay();

	/* �뷡 ���� */
	PrintSelectMusic();

	/* ���� �÷��� */
	PrintInGameDisplay();
	PlayMusic();
	LoadMap();
	PrintMap();
	KeyInput();

	/* ��� ��� */
	ResultScreen();

	return 0;
}