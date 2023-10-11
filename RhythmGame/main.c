#include "main.h"

/* 입력 키 */
#define KEY_D 0x44 // D
#define KEY_F 0x46 // F
#define KEY_J 0x4A // J
#define KEY_K 0x4B // K

#define SCR_HEIGHT 50

/* 키 입력 상태 */
int KeyAct[4] = { 0, };
int KeyState[4] = { 0, };

/* 점수 */
unsigned int Score = 0;

/* 동작 순서 */
enum Sequence {
	End,
	Main,
	Select,
	Playing,
	Result
};
enum Sequence sequence = Main;

/* 노래 */
char list[3][25] = { "Odysseus.txt", "JUSTITIA.txt", "IronCloud.txt" };
int longth[3] = { 12000, 8300, 12000 };
int delay[3] = { 14, 14, 14 };

/* 더블 버퍼링 */
char front_buffer[SCR_HEIGHT][4] = { 0, };
char back_buffer[SCR_HEIGHT][4] = { 0, };

void Init()
{
	/* 커서 유무 설정 */
	CursorView(FALSE);
	/* CMD 창 색 설정 */
	system("COLOR 0F");
	/* CMD 창 제목 수정 */
	system("title EZ2MAX");
	/* CMD 창 크기 설정*/
	system("mode con: cols=150 lines=50");
}

int ExitGame()
{
	if (sequence == End) {
		MakeBox(50, 16, 92, 27);
		gotoxy(61, 20);
		printf("정말로 나가시겠습니까?");
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
		/* 첫 화면 출력 */
		gotoxy(35, 10); printf(":\'########::::\'########:::::\'#######:::::\'##::::\'##:::::::\'###:::::::\'##::::\'##:");
		gotoxy(35, 11); printf(": ##.....:::::..... ##:::::\'##.... ##:::: ###::\'###::::::\'## ##::::::. ##::\'##::");
		gotoxy(35, 12); printf(": ##:::::::::::::: ##::::::..::::: ##:::: ####\'####:::::\'##:. ##::::::. ##\'##:::");
		gotoxy(35, 13); printf(": ######::::::::: ##::::::::\'#######::::: ## ### ##::::\'##:::. ##::::::. ###::::");
		gotoxy(35, 14); printf(": ##...::::::::: ##::::::::\'##::::::::::: ##. #: ##:::: #########:::::: ## ##:::");
		gotoxy(35, 15); printf(": ##::::::::::: ##::::::::: ##::::::::::: ##:.:: ##:::: ##.... ##::::: ##:. ##::");
		gotoxy(35, 16); printf(": ########:::: ########:::: #########:::: ##:::: ##:::: ##:::: ##:::: ##:::. ##:");
		gotoxy(35, 17); printf(":........:::::........:::::.........:::::..:::::..:::::..:::::..:::::..:::::..::");
		gotoxy(61, 30); printf("Press Enter Key To Start!!!");

		/* 키 입력 확인 */
		while (TRUE) {
			if (keystate(VK_RETURN)) // Enter가 입력되면
			{
				cls;				 // 화면 지움
				delay(100);
				sequence = Select;   // 순서 설정
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
		MakeBox(85, 10, 132, 30);
		MakeBox(10, 33, 69, 37);
		gotoxy(13, 35); printf("조작키 - ↑  ↓  |  뒤로가기 - Esc  |  노래선택 - Enter");

		int Menu = 0;
		/* 노래 선택 확인 */
		while (TRUE)
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
			else if (keystate(VK_ESCAPE))
			{
				Menu = -1;
				break;
			}
			/* 선택된 메뉴 - 파란색, 그 외 메뉴 - 흰색 */
			switch (Menu) {
			case 0:
				SetColor(FOREGROUND_BLUE);
				gotoxy(90, 15); printf("♪ Odysseus");
				SetColor(FOREGROUND_WHITE);
				gotoxy(90, 20); printf("♪ JUSTITIA");
				gotoxy(90, 25); printf("♪ IronCloud");
				break;
			case 1:
				gotoxy(90, 15); printf("♪ Odysseus");
				SetColor(FOREGROUND_BLUE);
				gotoxy(90, 20); printf("♪ JUSTITIA");
				SetColor(FOREGROUND_WHITE);
				gotoxy(90, 25); printf("♪ IronCloud");
				break;
			case 2:
				gotoxy(90, 15); printf("♪ Odysseus");
				gotoxy(90, 20); printf("♪ JUSTITIA");
				SetColor(FOREGROUND_BLUE);
				gotoxy(90, 25); printf("♪ IronCloud");
				SetColor(FOREGROUND_WHITE);
				break;
			default:
				break;
			}
			delay(100);
		}
		/* 화면 초기화 */
		cls;

		/* 선택한 노래 실행 */
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
		/* 노트 구간 */
		MakeBox(2, 1, 52, 48);
		/* 판정선 */
		gotoxy(3, 40);
		printf("─────────────────────────────────────────────────");
		gotoxy(3, 41);
		printf("─────────────────────────────────────────────────");
		/* 정보 구간 */
		MakeBox(60, 22, 90, 28);
		MakeBox(60, 31, 90, 37);
		MakeBox(60, 40, 140, 48);
		MakeBox(100, 31, 130, 37);


		/* 조작키 */
		gotoxy(65, 34);
		printf("조작키 - D, F, J, K");

		/* 판정 */
		gotoxy(105, 34);
		printf("판정 : ");
	}
}

void PlayMusic(int num)
{
	int i = 0, miss = 0, LongCombo = 0, Combo = 0;
	int j, k;
	int early[4] = { 0, };

	/* 라인별 노트 저장*/
	char* line1Ptr = malloc(sizeof(char) * 10000);
	char* line2Ptr = malloc(sizeof(char) * 10000);
	char* line3Ptr = malloc(sizeof(char) * 10000);
	char* line4Ptr = malloc(sizeof(char) * 10000);

	DWORD real_delay;
	clock_t start, end;
	FILE* fp = fopen(list[num], "r"); // 읽기모드
	if (!fp)
	{
		MakeBox(45, 20, 100, 26);
		gotoxy(50, 22);
		printf("노트파일을 열 수 없습니다.");
		gotoxy(50, 24);
		printf("3초 후에 선택화면으로 돌아갑니다.");
		delay(1000);
		gotoxy(50, 24);
		printf("2초 후에 선택화면으로 돌아갑니다.");
		delay(1000);
		gotoxy(50, 24);
		printf("1초 후에 선택화면으로 돌아갑니다.");
		delay(1000);
		cls;
		sequence = Select;
		return;
	}
	/* 노트 파일 읽어오기 */
	fgets(line1Ptr, 10000, fp);
	fgets(line2Ptr, 10000, fp);
	fgets(line3Ptr, 10000, fp);
	fgets(line4Ptr, 10000, fp);

	/* 다중 키 입력 스레드 */
	_beginthreadex(NULL, 0, (_beginthreadex_proc_type)PressD, NULL, 0, NULL);
	_beginthreadex(NULL, 0, (_beginthreadex_proc_type)PressF, NULL, 0, NULL);
	_beginthreadex(NULL, 0, (_beginthreadex_proc_type)PressJ, NULL, 0, NULL);
	_beginthreadex(NULL, 0, (_beginthreadex_proc_type)PressK, NULL, 0, NULL);

	/* 맵 생성 */
	PrintInGameDisplay();

	/* 노래 재생 */
	if (num == 0)
	{
		PlaySound(TEXT("Odysseus.wav"), 0, SND_FILENAME | SND_ASYNC);
		system("title EZ2MAX - Odysseus");
		gotoxy(65, 44); printf("♪ Now Playing - Odysseus");
	}
	else if (num == 1)
	{
		PlaySound(TEXT("JUSTITIA.wav"), 0, SND_FILENAME | SND_ASYNC);
		system("title EZ2MAX - JUSTITIA");
		gotoxy(65, 44); printf("♪ Now Playing - JUSTITIA");
	}
	else
	{
		PlaySound(TEXT("IronCloud.wav"), 0, SND_FILENAME | SND_ASYNC);
		system("title EZ2MAX - IronCloud");
		gotoxy(65, 44); printf("♪ Now Playing - IronCloud");
	}
	start = clock();
	while (TRUE)
	{
		/* 노트 그리기 */
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
		/* 미리 눌린 노트 삭제 */
		for (j = 0; j < 4; j++) {
			if (early[j] == 1)
			{
				back_buffer[40][j] = '\0';
				front_buffer[40][j] = '\0';
				early[j] = 0;
			}
		}
		/* 렌더링 */
		Render();

		SetColor(NULL);
		SetColor(FOREGROUND_WHITE);
		for (k = 0; k < 4; k++)
		{
			if (front_buffer[39][k] == '1') miss++; /* miss 처리 */	
			if (KeyAct[k] == 1)
			{
				if (KeyState[k] == 1)
				{
					if (front_buffer[38][k] == '\0' && front_buffer[39][k] == '\0') KeyState[k] = '\0';
					/* 롱노트 Early 판정 */
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
					/* 롱노트 COOL 판정 */
					else if (front_buffer[38][k] == '1' && front_buffer[39][k] == '1')
					{
						LongCombo++;
						if (LongCombo % 50) Combo++;
						miss = 0;
						Score += (Combo / 30 * 100);
						gotoxy(112, 34);
						printf("COOL");
					}
					/* 단노트 Early 판정 */
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
					/* 단노트 COOL 판정 */
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
		/* MISS뜨면 COMBO 초기화 */
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
		/* 딜레이 확인 */
		end = clock();
		real_delay = delay[num] - (end - start);
		gotoxy(115, 45);
		printf("Delay : %d  |  %d  ", real_delay, delay[num]);
		Sleep(real_delay);
		start = clock();
	}
	/* 종료 */
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

/* 키보드 - D */
void PressD()
{
	while (TRUE)
	{
		if (keystate(KEY_D))
		{
			/* 눌렀을 때 색깔 나타내기 */
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

/* 키보드 - F */
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

/* 키보드 - J */
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

/* 키보드 - K */
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
	/* 백 버퍼에 작성 */
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

	/* 백버퍼에 작성한 내용을 프론트버퍼에 저장 */
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
	/* 선작업 */
	Init();

	while (TRUE)
	{
		/* 첫 화면 */
		PrintMainDisplay();

		/* 노래 선택 */
		PrintSelectMusic();

		/* 게임 플레이 */
		PrintInGameDisplay();

		/* 결과 출력 */
		ResultScreen();

		/* 게임 끄기 */
		if (ExitGame()) break;
	}

	return 0;
}