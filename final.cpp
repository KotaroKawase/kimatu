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
int sx1;
int sy1;
int sx2;
int sy2;
int t = 0;

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

	int  x, y, w, h;
	const char* str;
	str = "@";
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
	bkgd(COLOR_PAIR(1));

	time_t t1, t2, t3;	//タイマー機能
	while (1) {
		Title();
		mvaddstr(25, 40, "START -> Press [S] Button");
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
				sx1 = 130;
				sy1 = rand() % (h - 10);
				Writingline1(sx1, sy1);
			}
			if (t % 100000 == 10000) {
				sx2 = rand() % (w - 15);
				sy2 = -1;
				Writingline2(sx2, sy2);
			}

			switch (key) {
			case KEY_UP:	if (y > 0) {
				y--;
				erase();
			}
							break;		//キー操作のたびにt2を更新
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
			mvaddstr(y, x, str);
			refresh();
			Writingline1(sx1, sy1);
			Writingline2(sx2, sy2);
			if ((x == sx1 && (y <= sy1 || y > sy1 + 10)) || ((x <= sx2 || x > sx2 + 15) && y == sy2)) {
				check = 1;
				t3 = t2;
			}

			if (check == 1) {
				erase();
				time(&t2);
				break;
			}
		}
		while (1) {
			str = " ";
			bkgd(COLOR_PAIR(3));
			disOver();
			mvprintw(25, 36, "time = %d", (t2 - t1));
			mvaddstr(28, 36, "RETRY -> Press [A] Button");
			check = 0;
			key = getch();
			if (key == 'a') {
				bkgd(COLOR_PAIR(1));
				str = "@";
				goto START;
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
		mvaddstr(i, a, "|");
		if (i == b) {
			i = i + 10;
		}
	}
}
//横棒の描画
void Writingline2(int a, int b) {
	int i, h, w;
	getmaxyx(stdscr, h, w);
	for (i = 0; i < w; i++) {
		mvaddstr(b, i, "_");
		if (i == a) {
			i = i + 15;
		}
	}
}



// タイトルを表示
// タイトルを表示
void Title()
{
	clear();
	mvprintw(LINES / 2 - 4, (COLS - 70) / 2, " GGGG    AAA   M     M  EEEEE        SSSS   TTTTTTT   AAA   RRRR    TTTTTTT    ");
	mvprintw(LINES / 2 - 3, (COLS - 70) / 2, "G    G  A   A  MM   MM  E           S    O     T     A   A  R   R      T");
	mvprintw(LINES / 2 - 2, (COLS - 70) / 2, "G       A   A  M M M M  E           S          T     A   A  R    R     T");
	mvprintw(LINES / 2 - 1, (COLS - 70) / 2, "G       AAAAA  M  M  M  EEEEE       S          T     AAAAA  RRRRR      T");
	mvprintw(LINES / 2, (COLS - 70) / 2, "G       A   A  M     M  E            SSSSS     T     A   A  R  R       T");
	mvprintw(LINES / 2 + 1, (COLS - 70) / 2, "G   GGG A   A  M     M  E                 S    T     A   A  R   R      T");
	mvprintw(LINES / 2 + 2, (COLS - 70) / 2, "G    G  A   A  M     M  E           S     S    T     A   A  R    R     T");
	mvprintw(LINES / 2 + 3, (COLS - 70) / 2, " GGGG   A   A  M     M  EEEEE       SSSSSS     T     A   A  R     R    T");
}
void disOver() {
	clear();
	mvprintw(LINES / 2 - 4, (COLS - 70) / 2, " GGGG    AAA   M     M  EEEEE        OOOO   V     V  EEEEE  RRRR       ");
	mvprintw(LINES / 2 - 3, (COLS - 70) / 2, "G    G  A   A  MM   MM  E           O    O  V     V  E      R   R      ");
	mvprintw(LINES / 2 - 2, (COLS - 70) / 2, "G       A   A  M M M M  E           O    O  V     V  E      R    R     ");
	mvprintw(LINES / 2 - 1, (COLS - 70) / 2, "G       AAAAA  M  M  M  EEEEE       O    O  V     V  EEEEE  RRRRR      ");
	mvprintw(LINES / 2, (COLS - 70) / 2, "G       A   A  M     M  E           O    O  V     V  E      R  R       ");
	mvprintw(LINES / 2 + 1, (COLS - 70) / 2, "G   GGG A   A  M     M  E           O    O   V   V   E      R   R      ");
	mvprintw(LINES / 2 + 2, (COLS - 70) / 2, "G    G  A   A  M     M  E           O    O    V V    E      R    R     ");
	mvprintw(LINES / 2 + 3, (COLS - 70) / 2, " GGGG   A   A  M     M  EEEEE        OOOO      V     EEEEE  R     R    ");
}

void iniLine() {
	t = 0;
	sx1 = 130;
	sy2 = -1;

}