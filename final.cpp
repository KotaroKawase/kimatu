#include "stdafx.h"
#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <time.h>
#include <random>



#define BUFFSIZE 1024
#define CHARBUFF 124

void iniLine();
void Writingline1(int a, int b);
void Writingline2(int a, int b);
void Title();
void disOver();
void disClear();
int sx1;
int sy1;
int sx2;
int sy2;
int ax, bx,cx,dx,ex;
int ay, by,cy,dy,ey;
int t = 0;
int cnt = 0;
int  x, y, w, h;
void getGurrentDirectory(char* currentDirectory) {
	GetCurrentDirectory(CHARBUFF, currentDirectory);
}

int main()
{
	int a;
	char keyValue[CHARBUFF];
	char currentDirectory[CHARBUFF];
	getGurrentDirectory(currentDirectory);

	char section[CHARBUFF];
	sprintf_s(section, "section1");
	char keyWord[CHARBUFF];
	sprintf_s(keyWord, "BestTime");
	char settingFile[CHARBUFF];
	sprintf_s(settingFile, "%s\\BestClearTime.ini", currentDirectory);

	const char* str;
	const char* etr1;
	const char* etr2;
	const char* etr3;
	const char* etr4;
	const char* etr5;
	str = "@";
	etr1 = "#";
	etr2 = "#";
	etr3 = "#";
	etr4 = "#";
	etr5 = "#";
	int  key;
	int check = 0;
	int cleartime;
	initscr();
	noecho();
	cbreak();
	keypad(stdscr, TRUE);

	getmaxyx(stdscr, h, w);
	y = h / 2;
	x = w / 2;

	start_color();
	init_pair(1, COLOR_YELLOW, COLOR_BLACK);	// 色1 は黒地に黄文字
	init_pair(2, COLOR_MAGENTA, COLOR_BLUE);	// 色2 は青地にマゼンタ文字
	init_pair(3, COLOR_BLACK, COLOR_WHITE);		// 色3 は白地に黒文字
	init_pair(4, COLOR_RED, COLOR_BLACK);		// 色3 は黒地に赤文字
	init_pair(5, COLOR_CYAN, COLOR_BLACK);		// 色3 は黒地にシアン文字
	init_pair(6, COLOR_WHITE, COLOR_BLACK);		// 色3 は黒地にシアン文字

	bkgd(COLOR_PAIR(1));

	time_t t1, t2;	//タイマー機能
	while (1) {
	TITLE:
		Title();
		GetPrivateProfileString(section, keyWord, "none", keyValue, CHARBUFF, settingFile);
		a = atoi(keyValue);
		mvprintw(28, 40, "BestTime = %d", a);
		while (1) {
			key = getch();
			if (key == 's') {
				clear();

				goto START;
			}
		}
	START:
		time(&t1);		//スタート時刻を記憶
		iniLine();
		while (1) {
			t++;
			timeout(0);
			key = getch();

			t2 = 0;
			if (t % 100000 == 0) {
				sx1 = w + 1;
				sy1 = rand() % (h - 10);
				Writingline1(sx1, sy1);
			}
			if (t % 100000 == 10000) {
				sx2 = rand() % (w - 15);
				sy2 = -1;
				Writingline2(sx2, sy2);
			}
			if (t % 100000 == 0) {
				ax = -1;
				ay = rand() % w;
				etr1 = "#";			
				mvaddstr(ax, ay, etr1);
			}
			if (t % 100000 == 20000) {
				bx = -1;
				by = rand() % w;
				etr2 = "#";				
				mvaddstr(bx, by, etr2);
			}
			if (t % 50000 == 0) {
				cx = -1;
				cy = rand() % w;
				etr3 = "#";				
				mvaddstr(cx, cy, etr3);
			}
			if (t % 50000 == 2000) {
				dx = -1;
				dy = rand() % w;
				etr4 = "#";
				mvaddstr(dx, dy, etr4);
			}
			if (t % 200000 == 5000) {
				ex = -1;
				ey = rand() % w;
				etr5 = "#";
				mvaddstr(ex, ey, etr5);
			}

			switch (key) {
			case KEY_UP:	if (y > 0) { y--; erase(); }
							break;		
			case KEY_DOWN:	if (y < h - 1) { y++; erase(); }
							break;
			case KEY_LEFT:	if (x > 0) { x--;  erase(); }
							break;
			case KEY_RIGHT:	if (x < w - 1) {
				x++;
				erase();
			}
							break;
			case 'a':		//[A]ボタンを押す取リトライ
				check = 0;
				str = "@";
				bkgd(COLOR_PAIR(1));
				y = h / 2;
				x = w / 2;
				time(&t2);
				t1 = t2;
				iniLine();
				erase();
				break;
			}
			if (t % 700 == 0) {
				erase();
				sx1--;

			}
			if (t % 3000 == 0 && t > 10000) {
				erase();
				sy2++;
			}
			if (t % 5000 == 0) {
				erase();
				ax++;
			}
			if (t % 5000 == 0) {
				erase();
				bx++;
			}
			if (t % 3000 == 0) {
				erase();
				cx++;
			}
			if (t % 3000 == 0) {
				erase();
				dx++;
			}
			if (t % 4000 == 0) {
				erase();
				ex++;
			}
			attrset(COLOR_PAIR(1));
			mvaddstr(y, x, str);
			mvprintw(1, 1, "count = %d", cnt);
			refresh();
			
			Writingline1(sx1, sy1);
			Writingline2(sx2, sy2);
			mvaddstr(ax, ay, etr1);
			mvaddstr(bx, by, etr2);
			attrset(COLOR_PAIR(4));
			mvaddstr(cx, cy, etr3);
			attrset(COLOR_PAIR(4));
			mvaddstr(dx, dy, etr4);
			attrset(COLOR_PAIR(5));
			mvaddstr(ex, ey, etr5);
			if ((x == sx1 && (y <= sy1 || y > sy1 + 10)) || ((x <= sx2 || x > sx2 + 15) && y == sy2)) {
				check = 1;

			}
			if ((x == ay && y == ax) && ((etr1 == "#"))) {
				cnt++;
				etr1 = " ";
			}
			else if ((x == by && y == bx) && (etr2 == "#")) {
				cnt++;
				etr2 = " ";
			}
			else if ((x == cy && y == cx) && (etr3 == "#")) {
				cnt--;
				etr3 = " ";
			}
			else if ((x == dy && y == dx) && (etr4 == "#")) {
				cnt--;
				etr4 = " ";
			}
			else if ((x == ey && y == ex) && (etr5 == "#")) {
				cnt+=2;
				etr5 = " ";
			}

			if (cnt >= 5) {
				check = 2;
			}
			if (check == 1) {
				erase();
				time(&t2);
				goto OVER;
			}
			else if (check == 2) {
				erase();
				time(&t2);
				goto CLEAR;
			}
		}
	CLEAR:
		while (1) {
			str = " ";
			attrset(COLOR_PAIR(2));
			disClear();
			//ベストタイムだった場合にiniに書き込む
			cleartime = (int)t2 - (int)t1;
			char clear_data[CHARBUFF];
			sprintf_s(clear_data, "%d", cleartime);
			GetPrivateProfileString(section, keyWord, "none", keyValue, CHARBUFF, settingFile);
			a = atoi(keyValue);
			if (cleartime < a || a == NULL) {
				WritePrivateProfileString(section, keyWord, clear_data, settingFile);
			}

			mvprintw(25, 36, "time = %d", (t2 - t1));
			mvaddstr(28, 36, "RETRY -> Press [A] Button");
			check = 0;
			key = getch();
			if (key == 'a') {
				attrset(COLOR_PAIR(1));
				str = "@";
				cnt = 0;
				goto TITLE;
			}
		}
	OVER:
		while (1) {
			str = " ";
			attrset(COLOR_PAIR(3));
			disOver();
			mvprintw(23, 36, "time = %d", (t2 - t1));
			mvprintw(25, 36, "Count = %d", cnt);
			mvaddstr(28, 36, "RETRY -> Press [A] Button");
			check = 0;
			key = getch();
			if (key == 'a') {
				attrset(COLOR_PAIR(1));
				str = "@";
				cnt = 0;
				goto TITLE;
			}
		}

	}
	endwin();
	return (0);
}

//縦棒の描画
void Writingline1(int a, int b) {
	int i, h, w;
	getmaxyx(stdscr, h, w);
	for (i = 0; i < h; i++) {
		if ((a < 10 && i != 1) || a >= 10) {
			mvaddstr(i, a, "*");
			if (i == b) {
				i = i + 10;
			}
		}
	}
}
//横棒の描画
void Writingline2(int a, int b) {
	int i, h, w;
	getmaxyx(stdscr, h, w);
	for (i = 0; i < w; i++) {
		if ((i < 10 && b != 1) || i >= 10) {
			mvaddstr(b, i, "*");
			if (i == a) {
				i = i + 15;
			}
		}

	}
}




// タイトルを表示
void Title()
{
	clear();
	bkgd(COLOR_PAIR(1));
	mvprintw(LINES / 2 - 4, (COLS - 70) / 2, " GGGG    AAA   M     M  EEEEE        SSSS   TTTTTTT   AAA   RRRR    TTTTTTT    ");
	mvprintw(LINES / 2 - 3, (COLS - 70) / 2, "G    G  A   A  MM   MM  E           S    S     T     A   A  R   R      T");
	mvprintw(LINES / 2 - 2, (COLS - 70) / 2, "G       A   A  M M M M  E           S          T     A   A  R    R     T");
	mvprintw(LINES / 2 - 1, (COLS - 70) / 2, "G       AAAAA  M  M  M  EEEEE       S          T     AAAAA  RRRRR      T");
	mvprintw(LINES / 2, (COLS - 70) / 2, "G       A   A  M     M  E            SSSSS     T     A   A  R  R       T");
	mvprintw(LINES / 2 + 1, (COLS - 70) / 2, "G   GGG A   A  M     M  E                 S    T     A   A  R   R      T");
	mvprintw(LINES / 2 + 2, (COLS - 70) / 2, "G    G  A   A  M     M  E           S     S    T     A   A  R    R     T");
	mvprintw(LINES / 2 + 3, (COLS - 70) / 2, " GGGG   A   A  M     M  EEEEE       SSSSSS     T     A   A  R     R    T");
	
	attrset(COLOR_PAIR(6));
	mvaddstr(2, 4, "***RULE****");
	for (int i = 3; i<= 9; i++) {
		mvaddstr(i, 4, "*");
	}
	for (int i = 4; i <= 14; i++) {
		mvaddstr(9, i, "*");
	}
	for (int i = 3; i <= 9; i++) {
		mvaddstr(i, 14, "*");
	}
	attrset(COLOR_PAIR(1));
	mvaddstr(4, 6, "# -> +1");
	attrset(COLOR_PAIR(5));
	mvaddstr(6, 6, "# -> +2");
	attrset(COLOR_PAIR(4));
	mvaddstr(8, 6, "# -> -1");
	attrset(COLOR_PAIR(1));
	mvaddstr(25, 40, "START -> Press [S] Button");
	
}
void disOver() {
	clear();
	bkgd(COLOR_PAIR(3));
	mvprintw(LINES / 2 - 4, (COLS - 70) / 2, " GGGG    AAA   M     M  EEEEE        OOOO   V     V  EEEEE  RRRR       ");
	mvprintw(LINES / 2 - 3, (COLS - 70) / 2, "G    G  A   A  MM   MM  E           O    O  V     V  E      R   R      ");
	mvprintw(LINES / 2 - 2, (COLS - 70) / 2, "G       A   A  M M M M  E           O    O  V     V  E      R    R     ");
	mvprintw(LINES / 2 - 1, (COLS - 70) / 2, "G       AAAAA  M  M  M  EEEEE       O    O  V     V  EEEEE  RRRRR      ");
	mvprintw(LINES / 2, (COLS - 70) / 2, "G       A   A  M     M  E           O    O  V     V  E      R  R       ");
	mvprintw(LINES / 2 + 1, (COLS - 70) / 2, "G   GGG A   A  M     M  E           O    O   V   V   E      R   R      ");
	mvprintw(LINES / 2 + 2, (COLS - 70) / 2, "G    G  A   A  M     M  E           O    O    V V    E      R    R     ");
	mvprintw(LINES / 2 + 3, (COLS - 70) / 2, " GGGG   A   A  M     M  EEEEE        OOOO      V     EEEEE  R     R    ");
}
void disClear() {
	clear();
	bkgd(COLOR_PAIR(2));
	mvprintw(LINES / 2 - 4, (COLS - 70) / 2, " GGGG    AAA   M     M  EEEEE        cccc   L         EEEEE    AAA    RRRR     ");
	mvprintw(LINES / 2 - 3, (COLS - 70) / 2, "G    G  A   A  MM   MM  E           c       L         E       A   A   R   R    ");
	mvprintw(LINES / 2 - 2, (COLS - 70) / 2, "G       A   A  M M M M  E           c       L         E       A   A   R    R   ");
	mvprintw(LINES / 2 - 1, (COLS - 70) / 2, "G       AAAAA  M  M  M  EEEEE       c       L         EEEEE   AAAAA   RRRRR    ");
	mvprintw(LINES / 2, (COLS - 70) / 2, "G       A   A  M     M  E           c       L         E       A   A   R   R    ");
	mvprintw(LINES / 2 + 1, (COLS - 70) / 2, "G   GGG A   A  M     M  E           c       L         E       A   A   R    R   ");
	mvprintw(LINES / 2 + 2, (COLS - 70) / 2, "G    G  A   A  M     M  E           c       L         E       A   A   R     R  ");
	mvprintw(LINES / 2 + 3, (COLS - 70) / 2, " GGGG   A   A  M     M  EEEEE        cccc   LLLLLLL   EEEEE   A   A   R      R ");
}
void iniLine() {
	t = 0;
	sx1 = 130;
	sy2 = -1;
	y = h / 2;
	x = w / 2;
	ax = -1; bx = -1; cx = -1; dx = -1; ex = -1;

}