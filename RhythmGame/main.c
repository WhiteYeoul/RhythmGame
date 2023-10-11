#include "main.h"

/* �Է� Ű */
#define KEY_D 0x44 // D
#define KEY_F 0x46 // F
#define KEY_J 0x4A // J
#define KEY_K 0x4B // K

#define SCR_HEIGHT 50

/* Ű �Է� ���� */
int KeyAct[4] = { 0, };
int KeyState[4] = { 0, };

/* ���� */
unsigned int Score = 0;

/* ���� ���� */
enum Sequence {
	End,
	Main,
	Select,
	Playing,
	Result
};
enum Sequence sequence = Main;

/* �뷡 */
char list[3][25] = { "Odysseus.txt", "JUSTITIA.txt", "IronCloud.txt" };
int longth[3] = { 12000, 8300, 12000 };
int delay[3] = { 14, 14, 14 };

/* ���� ���۸� */
char front_buffer[SCR_HEIGHT][4] = { 0, };
char back_buffer[SCR_HEIGHT][4] = { 0, };

void Init()
{
	/* Ŀ�� ���� ���� */
	CursorView(FALSE);
	/* CMD â �� ���� */
	system("COLOR 0F");
	/* CMD â ���� ���� */
	system("title EZ2MAX");
	/* CMD â ũ�� ����*/
	system("mode con: cols=150 lines=50");
}

int ExitGame()
{
	if (sequence == End) {
		MakeBox(50, 16, 92, 27);
		gotoxy(61, 20);
		printf("������ �����ðڽ��ϱ�?");
		gotoxy(62, 23);
		printf("Yes(Enter)  No(Esc)");

		while (TRUE) {
			if (keystate(VK_ESCAPE))
			{
				cls;
				delay(100);
				sequence = Main;
				break;
			}
			else if (keystate(VK_RETURN))
			{
				return 1;
			}
		}
	}
	return 0;
}

void PrintMainDisplay()
{
	if (sequence == Main) {
		/* ù ȭ�� ��� */
		gotoxy(35, 10); printf(":\'########::::\'########:::::\'#######:::::\'##::::\'##:::::::\'###:::::::\'##::::\'##:");
		gotoxy(35, 11); printf(": ##.....:::::..... ##:::::\'##.... ##:::: ###::\'###::::::\'## ##::::::. ##::\'##::");
		gotoxy(35, 12); printf(": ##:::::::::::::: ##::::::..::::: ##:::: ####\'####:::::\'##:. ##::::::. ##\'##:::");
		gotoxy(35, 13); printf(": ######::::::::: ##::::::::\'#######::::: ## ### ##::::\'##:::. ##::::::. ###::::");
		gotoxy(35, 14); printf(": ##...::::::::: ##::::::::\'##::::::::::: ##. #: ##:::: #########:::::: ## ##:::");
		gotoxy(35, 15); printf(": ##::::::::::: ##::::::::: ##::::::::::: ##:.:: ##:::: ##.... ##::::: ##:. ##::");
		gotoxy(35, 16); printf(": ########:::: ########:::: #########:::: ##:::: ##:::: ##:::: ##:::: ##:::. ##:");
		gotoxy(35, 17); printf(":........:::::........:::::.........:::::..:::::..:::::..:::::..:::::..:::::..::");
		gotoxy(61, 30); printf("Press Enter Key To Start!!!");

		/* Ű �Է� Ȯ�� */
		while (TRUE) {
			if (keystate(VK_RETURN)) // Enter�� �ԷµǸ�
			{
				cls;				 // ȭ�� ����
				delay(100);
				sequence = Select;   // ���� ����
				break;
			}
			else if (keystate(VK_ESCAPE))
			{
				cls;
				delay(100);
				sequence = End;
				break;
			}
		}
	}
}

void PrintSelectMusic()
{
	if (sequence == Select) {
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
		MakeBox(85, 10, 132, 30);
		MakeBox(10, 33, 69, 37);
		gotoxy(13, 35); printf("����Ű - ��  ��  |  �ڷΰ��� - Esc  |  �뷡���� - Enter");

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
			else if (keystate(VK_ESCAPE))
			{
				Menu = -1;
				break;
			}
			/* ���õ� �޴� - �Ķ���, �� �� �޴� - ��� */
			switch (Menu) {
			case 0:
				SetColor(FOREGROUND_BLUE);
				gotoxy(90, 15); printf("�� Odysseus");
				SetColor(FOREGROUND_WHITE);
				gotoxy(90, 20); printf("�� JUSTITIA");
				gotoxy(90, 25); printf("�� IronCloud");
				break;
			case 1:
				gotoxy(90, 15); printf("�� Odysseus");
				SetColor(FOREGROUND_BLUE);
				gotoxy(90, 20); printf("�� JUSTITIA");
				SetColor(FOREGROUND_WHITE);
				gotoxy(90, 25); printf("�� IronCloud");
				break;
			case 2:
				gotoxy(90, 15); printf("�� Odysseus");
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
		if (Menu == -1)
		{
			cls;
			delay(100);
			sequence = Main;
		}
		else if (Menu == 0)
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
}

void PrintInGameDisplay()
{
	if (sequence == Playing)
	{
		/* ��Ʈ ���� */
		MakeBox(2, 1, 52, 48);
		/* ������ */
		gotoxy(3, 40);
		printf("��������������������������������������������������������������������������������������������������");
		gotoxy(3, 41);
		printf("��������������������������������������������������������������������������������������������������");
		/* ���� ���� */
		MakeBox(60, 22, 90, 28);
		MakeBox(60, 31, 90, 37);
		MakeBox(60, 40, 140, 48);
		MakeBox(100, 31, 130, 37);


		/* ����Ű */
		gotoxy(65, 34);
		printf("����Ű - D, F, J, K");

		/* ���� */
		gotoxy(105, 34);
		printf("���� : ");
	}
}

void PlayMusic(int num)
{
	int i = 0, miss = 0, LongCombo = 0, Combo = 0;
	int j, k;
	int early[4] = { 0, };

	/* ���κ� ��Ʈ ����*/
	char* line1Ptr = malloc(sizeof(char) * 10000);
	char* line2Ptr = malloc(sizeof(char) * 10000);
	char* line3Ptr = malloc(sizeof(char) * 10000);
	char* line4Ptr = malloc(sizeof(char) * 10000);

	DWORD real_delay;
	clock_t start, end;
	FILE* fp = fopen(list[num], "r"); // �б���
	if (!fp)
	{
		MakeBox(45, 20, 100, 26);
		gotoxy(50, 22);
		printf("��Ʈ������ �� �� �����ϴ�.");
		gotoxy(50, 24);
		printf("3�� �Ŀ� ����ȭ������ ���ư��ϴ�.");
		delay(1000);
		gotoxy(50, 24);
		printf("2�� �Ŀ� ����ȭ������ ���ư��ϴ�.");
		delay(1000);
		gotoxy(50, 24);
		printf("1�� �Ŀ� ����ȭ������ ���ư��ϴ�.");
		delay(1000);
		cls;
		sequence = Select;
		return;
	}
	/* ��Ʈ ���� �о���� */
	fgets(line1Ptr, 10000, fp);
	fgets(line2Ptr, 10000, fp);
	fgets(line3Ptr, 10000, fp);
	fgets(line4Ptr, 10000, fp);

	/* ���� Ű �Է� ������ */
	_beginthreadex(NULL, 0, (_beginthreadex_proc_type)PressD, NULL, 0, NULL);
	_beginthreadex(NULL, 0, (_beginthreadex_proc_type)PressF, NULL, 0, NULL);
	_beginthreadex(NULL, 0, (_beginthreadex_proc_type)PressJ, NULL, 0, NULL);
	_beginthreadex(NULL, 0, (_beginthreadex_proc_type)PressK, NULL, 0, NULL);

	/* �� ���� */
	PrintInGameDisplay();

	/* �뷡 ��� */
	if (num == 0)
	{
		PlaySound(TEXT("Odysseus.wav"), 0, SND_FILENAME | SND_ASYNC);
		system("title EZ2MAX - Odysseus");
		gotoxy(65, 44); printf("�� Now Playing - Odysseus");
	}
	else if (num == 1)
	{
		PlaySound(TEXT("JUSTITIA.wav"), 0, SND_FILENAME | SND_ASYNC);
		system("title EZ2MAX - JUSTITIA");
		gotoxy(65, 44); printf("�� Now Playing - JUSTITIA");
	}
	else
	{
		PlaySound(TEXT("IronCloud.wav"), 0, SND_FILENAME | SND_ASYNC);
		system("title EZ2MAX - IronCloud");
		gotoxy(65, 44); printf("�� Now Playing - IronCloud");
	}
	start = clock();
	while (TRUE)
	{
		/* ��Ʈ �׸��� */
		for (j = i; j >= 0; j--)
		{
			if (j > 40) j = 40;
			if (line1Ptr[i - j] == '1')
				back_buffer[j][0] = '1';
			if (line2Ptr[i - j] == '1')
				back_buffer[j][1] = '1';
			if (line3Ptr[i - j] == '1')
				back_buffer[j][2] = '1';
			if (line4Ptr[i - j] == '1')
				back_buffer[j][3] = '1';
		}
		/* �̸� ���� ��Ʈ ���� */
		for (j = 0; j < 4; j++) {
			if (early[j] == 1)
			{
				back_buffer[40][j] = '\0';
				front_buffer[40][j] = '\0';
				early[j] = 0;
			}
		}
		/* ������ */
		Render();

		SetColor(NULL);
		SetColor(FOREGROUND_WHITE);
		for (k = 0; k < 4; k++)
		{
			if (front_buffer[39][k] == '1') miss++; /* miss ó�� */	
			if (KeyAct[k] == 1)
			{
				if (KeyState[k] == 1)
				{
					if (front_buffer[38][k] == '\0' && front_buffer[39][k] == '\0') KeyState[k] = '\0';
					/* �ճ�Ʈ Early ���� */
					else if (front_buffer[37][k] == '1' && front_buffer[38][k] == '1')
					{
						LongCombo++;
						if (LongCombo % 50) Combo++;
						miss = 0;
						early[k] = 1;
						Score += (Combo / 30 * 50);
						gotoxy(112, 34);
						printf("GOOD");
					}
					/* �ճ�Ʈ COOL ���� */
					else if (front_buffer[38][k] == '1' && front_buffer[39][k] == '1')
					{
						LongCombo++;
						if (LongCombo % 50) Combo++;
						miss = 0;
						Score += (Combo / 30 * 100);
						gotoxy(112, 34);
						printf("COOL");
					}
					/* �ܳ�Ʈ Early ���� */
					else if (front_buffer[38][k] == '1' && front_buffer[39][k] == '\0')
					{
						Combo++;
						miss = 0;
						Score += 50;
						KeyState[k] = '\0';
						early[k] = 1;
						gotoxy(112, 34);
						printf("GOOD");
					}
					/* �ܳ�Ʈ COOL ���� */
					else if (front_buffer[39][k] == '1')
					{
						Combo++;
						miss = 0;
						Score += 100;
						KeyState[k] = '\0';
						gotoxy(112, 34);
						printf("COOL");
					}
				}
				KeyAct[k] = '\0';
				LongCombo = 0;
			}
		}
		/* MISS�߸� COMBO �ʱ�ȭ */
		if (miss > 0) Combo = 0;

		gotoxy(65, 25);
		printf("MISS : %d     ", miss);
		gotoxy(94, 45);
		printf("COMBO : %d    ", Combo);
		gotoxy(94, 43);
		printf("SCORE : %d    ", Score);
		gotoxy(115, 43);
		printf("Time : %d", i);
		i++;
		if (i > longth[num]) break;
		if (keystate(VK_ESCAPE)) break;
		/* ������ Ȯ�� */
		end = clock();
		real_delay = delay[num] - (end - start);
		gotoxy(115, 45);
		printf("Delay : %d  |  %d  ", real_delay, delay[num]);
		Sleep(real_delay);
		start = clock();
	}
	/* ���� */
	free(line1Ptr);
	free(line2Ptr);
	free(line3Ptr);
	free(line4Ptr);
	PlaySound(NULL, 0, 0);
	system("title EZ2MAX");
	cls;
	delay(100);
	sequence = Result;
}

/* Ű���� - D */
void PressD()
{
	while (TRUE)
	{
		if (keystate(KEY_D))
		{
			/* ������ �� ���� ��Ÿ���� */
			back_buffer[42][0] = '1';
			back_buffer[43][0] = '1';
			back_buffer[44][0] = '1';
			back_buffer[45][0] = '1';
			back_buffer[46][0] = '1';
			back_buffer[47][0] = '1';
			KeyAct[0] = TRUE;
		}
		else
		{
			KeyAct[0] = '\0';
			KeyState[0] = TRUE;
		}
		delay(1);
	}
}

/* Ű���� - F */
void PressF()
{
	while (TRUE) {
		if (keystate(KEY_F))
		{
			back_buffer[42][1] = '1';
			back_buffer[43][1] = '1';
			back_buffer[44][1] = '1';
			back_buffer[45][1] = '1';
			back_buffer[46][1] = '1';
			back_buffer[47][1] = '1';
			KeyAct[1] = TRUE;
		}
		else
		{
			KeyAct[1] = '\0';
			KeyState[1] = TRUE;
		}
		delay(1);
	}
}

/* Ű���� - J */
void PressJ()
{
	while (TRUE) {
		if (keystate(KEY_J))
		{
			back_buffer[42][2] = '1';
			back_buffer[43][2] = '1';
			back_buffer[44][2] = '1';
			back_buffer[45][2] = '1';
			back_buffer[46][2] = '1';
			back_buffer[47][2] = '1';
			KeyAct[2] = TRUE;
		}
		else
		{
			KeyAct[2] = '\0';
			KeyState[2] = TRUE;
		}
		delay(1);
	}
}

/* Ű���� - K */
void PressK()
{
	while (TRUE) {
		if (keystate(KEY_K))
		{
			back_buffer[42][3] = '1';
			back_buffer[43][3] = '1';
			back_buffer[44][3] = '1';
			back_buffer[45][3] = '1';
			back_buffer[46][3] = '1';
			back_buffer[47][3] = '1';
			KeyAct[3] = TRUE;
		}
		else
		{
			KeyAct[3] = '\0';
			KeyState[3] = TRUE;
		}
		delay(1);
	}
}

void Render()
{
	/* �� ���ۿ� �ۼ� */
	int x, y;
	for (y = 2; y < SCR_HEIGHT; y++)
	{
		for (x = 0; x < 4; x++)
		{
			if (back_buffer[y][x] != front_buffer[y][x])
			{
				if (y == 40) continue;
				gotoxy(x * 12 + 5, y);
				if (back_buffer[y][x] == '\0')
				{
					SetColor(NULL);
					printf("          ");
				}
				else
				{
					if (x == 0) SetColor(BACKGROUND_WHITE);
					else if (x == 1) SetColor(BACKGROUND_GREEN);
					else if (x == 2) SetColor(BACKGROUND_GREEN);
					else if (x == 3) SetColor(BACKGROUND_WHITE);
					printf("          ");
				}
			}
		}
	}

	/* ����ۿ� �ۼ��� ������ ����Ʈ���ۿ� ���� */
	for (y = 2; y < SCR_HEIGHT; y++)
	{
		for (x = 0; x < 4; x++)
		{
			front_buffer[y][x] = back_buffer[y][x];
			back_buffer[y][x] = '\0';
		}
	}
}

void ResultScreen()
{
	if (sequence == Result)
	{
		MakeBox(50, 16, 92, 26);

		gotoxy(65, 21);
		printf("Score : %d", Score);

		while (TRUE) {
			if (keystate(VK_ESCAPE))
			{
				cls;
				delay(100);
				Score = 0;
				sequence = Select;
				break;
			}
		}
	}
}

int main(void)
{
	/* ���۾� */
	Init();

	while (TRUE)
	{
		/* ù ȭ�� */
		PrintMainDisplay();

		/* �뷡 ���� */
		PrintSelectMusic();

		/* ���� �÷��� */
		PrintInGameDisplay();

		/* ��� ��� */
		ResultScreen();

		/* ���� ���� */
		if (ExitGame()) break;
	}

	return 0;
}