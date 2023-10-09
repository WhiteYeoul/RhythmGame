#include "main.h"

/* 입력 키 */
#define KEY_D 0x44 // D
#define KEY_F 0x46 // F
#define KEY_J 0x4A // J
#define KEY_K 0x4B // K

#define SCR_WIDTH 150
#define SCR_HEIGHT 50

/* 키 입력 상태 */
int KeyAct[4] = { 0, };
int KeyState[4] = { 0, };

/* 점수 */
int Combo = 0;

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
int longth[3] = { 12000, 12000, 12000 };
int delay[3] = { 14, 14, 14 };

/* 라인별 노트 저장*/
char buf[10000];
char buf2[10000];
char buf3[10000];
char buf4[10000];

/* 더블 버퍼링 */
char front_buffer[SCR_HEIGHT][4] = { 0, };
char back_buffer[SCR_HEIGHT][4] = { 0, };

void Init()
{
	/* 커서 유무 설정 */
	CursorView(0);
	/* CMD 창 색 설정 */
	system("COLOR 0F");
	/* CMD 창 제목 수정 */
	system("title EZ2MAX");
	/* CMD 창 크기 설정*/
	system("mode con: cols=150 lines=50");
}

void MakeBox(int x, int y, int x2, int y2)
{
	/* 모서리 채우기*/
	gotoxy(x, y);
	printf("┌");
	gotoxy(x2, y);
	printf("┐");
	gotoxy(x, y2);
	printf("└");
	gotoxy(x2, y2);
	printf("┘");
	/* 가로 채우기 */
	for (int i = x + 1; i < x2; i++)
	{
		gotoxy(i, y);
		printf("─");
		gotoxy(i, y2);
		printf("─");
	}
	/* 세로 채우기 */
	for (int i = y + 1; i < y2; i++)
	{
		gotoxy(x, i);
		printf("│");
		gotoxy(x2, i);
		printf("│");
	}
}

int ExitGame()
{
	if (sequence == End) {
		MakeBox(50, 16, 92, 26);
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
		MakeBox(85,10,132,30);

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
				cls;
				delay(100);
				sequence = Main;
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
}

void PrintInGameDisplay()
{
	if (sequence == Playing)
	{
		/* 노트 구간 */
		MakeBox(3, 1, 51, 48);
		
		/* 정보 구간 */
		MakeBox(60, 31, 90, 37);
		MakeBox(60, 40, 140, 48);
		MakeBox(100, 31, 130, 37);

		/* 판정선 */
		gotoxy(4, 40); 
		printf("───────────────────────────────────────────────");
		gotoxy(4, 41);
		printf("───────────────────────────────────────────────");

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
	int i = 0, j, k, m = 0, miss = 0;
	int temp[4] = { 0, };
	unsigned score = 0; // 점수는 음수x
	DWORD real_delay;
	clock_t start, end;
	FILE* fp = fopen(list[num], "r"); // 읽기모드
	if (!fp)
	{
		gotoxy(50, 20);
		printf(" 노트파일을 열 수 없습니다.\n");
		return;
	}
	/* 노트 파일 읽어오기 */
	fgets(buf, sizeof(buf), fp);
	fgets(buf2, sizeof(buf2), fp);
	fgets(buf3, sizeof(buf3), fp);
	fgets(buf4, sizeof(buf3), fp);
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
		gotoxy(65, 44); printf("♪ Now Playing - Odysseus");
	}
	else if (num == 1)
	{
		PlaySound(TEXT("JUSTITIA.wav"), 0, SND_FILENAME | SND_ASYNC);
		gotoxy(65, 44); printf("♪ Now Playing - JUSTITIA");
	}
	else
	{
		PlaySound(TEXT("IronCloud.wav"), 0, SND_FILENAME | SND_ASYNC);
		gotoxy(65, 44); printf("♪ Now Playing - IronCloud");
	}
	start = clock();
	while (TRUE)
	{
		/* 노트 그리기 */
		for (j = i; j >= 0; j--)
		{
			if (j >= 40) j = 40;
			if (buf[i - j] == '1')
				back_buffer[j][0] = '1';
			if (buf2[i - j] == '1')
				back_buffer[j][1] = '1';
			if (buf3[i - j] == '1')
				back_buffer[j][2] = '1';
			if (buf4[i - j] == '1')
				back_buffer[j][3] = '1';
		}
		/* 미리 눌린 노트 삭제 */
		for (j = 0; j < 4; j++) {
			if (temp[j] == 1)
			{
				back_buffer[40][j] = '\0';
				front_buffer[40][j] = '\0';
				temp[j] = 0;
			}
		}
		Render();
		SetColor(NULL);
		SetColor(FOREGROUND_WHITE);
		for (k = 0; k < 4; k++)
		{
			if (front_buffer[40][k] == '1') miss++;
			if (KeyAct[k] == 1)
			{
				if (KeyState[k] == 1)
				{
					if (front_buffer[38][k] == '\0' && front_buffer[39][k] == '\0') KeyState[k] = '\0';
					/* 이른 누름 */
					else if (front_buffer[37][k] == '1' && front_buffer[38][k] == '1')
					{
						Combo++;
						miss--;
						temp[k] = 1;
						score += (Combo / 10) * 50;
						gotoxy(112, 34);
						printf("GOOD");
					}
					/* 정확히 누름 */
					else if (front_buffer[38][k] == '1' && front_buffer[39][k] == '1')
					{
						Combo++;
						miss--;
						score += (Combo / 10) * 100;
						gotoxy(112, 34);
						printf("COOL");
					}
					/* 이른 누름 */
					else if (front_buffer[38][k] == '1' && front_buffer[39][k] == '\0')
					{
						Combo++;
						score += 50;
						KeyState[k] = '\0';
						temp[k] = 1;
						gotoxy(112, 34);
						printf("GOOD");
					}
					/* 정확히 누름 */
					else if (front_buffer[39][k] == '1')
					{
						Combo++;
						miss--;
						score += 100;
						KeyState[k] = '\0';
						gotoxy(112, 34);
						printf("COOL");
					}
				}
				KeyAct[k] = '\0';
			}
		}
		/* MISS뜨면 COMBO 초기화 */
		if (miss > 0) Combo = 0;

		gotoxy(94, 45);
		printf("COMBO x %d    ", Combo);
		gotoxy(94, 43);
		printf("SCORE : %d    ", score);
		gotoxy(115, 43);
		printf("Time : %d", i);
		i++;
		if (i > longth[num]) break;
		/* 딜레이 확인 */
		end = clock();
		real_delay = delay[num] - (end - start);
		gotoxy(115, 45);
		printf("Delay : %d  |  %d  ", real_delay, delay[num]);
		Sleep(real_delay);
		start = clock();
	}
	/* 종료 */
	PlaySound(NULL, 0, 0);
	system("cls");
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
					else if (x == 1) SetColor(BACKGROUND_BLUE);
					else if (x == 2) SetColor(BACKGROUND_BLUE);
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

		gotoxy(67, 21); 
		printf("Combo : %d", Combo);

		while (TRUE) {
			if (keystate(VK_ESCAPE))
			{
				cls;	
				delay(100);
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