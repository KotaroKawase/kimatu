#include "stdafx.h"
#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <time.h>
#include "Myfinal.h"


int t = 0;
int cnt = 0;
int  x, y, w, h;

point A, B, C, D, E;
jama L1,L2;
void getGurrentDirectory(char* currentDirectory) {
	GetCurrentDirectory(CHARBUFF, currentDirectory);
}

int main()
{
	int a;     //iniファイルの中身を書き込む変数
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
	etr1 = "#";	//+1点
	etr2 = "#";	//+1点
	etr3 = "#";	//-1点
	etr4 = "#";	//-1点
	etr5 = "#";	//+2点

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
	init_pair(4, COLOR_RED, COLOR_BLACK);		// 色4 は黒地に赤文字
	init_pair(5, COLOR_CYAN, COLOR_BLACK);		// 色5 は黒地にシアン文字
	init_pair(6, COLOR_WHITE, COLOR_BLACK);		// 色6 は黒地に白文字

	bkgd(COLOR_PAIR(1));

	time_t t1, t2;	//タイマー機能
	while (1) {
	TITLE:
		Title();
		GetPrivateProfileString(section, keyWord, "none", keyValue, CHARBUFF, settingFile);
		a = atoi(keyValue);
		if (a != NULL) {
			mvprintw(28, 40, "BestTime => %d [秒]", a);
		}
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
			t++;	//whileが回るごとにt++
			timeout(0);
			key = getch();

			t2 = 0;

////////////#を自動で生成(tの値によって生成速度を制御)////////////////
			if (t % 100000 == 0) {
				L1.x = w + 1;
				L1.y = rand() % (h - 10);
				Writingline1(L1.x, L1.y);
			}
			if (t % 100000 == 10000) {
				L2.x = rand() % (w - 15);
				L2.y = -1;
				Writingline2(L2.x, L2.y);
			}
			if (t % 100000 == 0) {
				A.x = -1;
				A.y = rand() % w;
				etr1 = "#";			
				mvaddstr(A.x, A.y, etr1);
			}
			if (t % 100000 == 20000) {
				B.x = -1;
				B.y = rand() % w;
				etr2 = "#";				
				mvaddstr(B.x, B.y, etr2);
			}
			if (t % 50000 == 0) {
				C.x = -1;
				C.y = rand() % w;
				etr3 = "#";				
				mvaddstr(C.x, C.y, etr3);
			}
			if (t % 50000 == 2000) {
				D.x = -1;
				D.y = rand() % w;
				etr4 = "#";
				mvaddstr(D.x, D.y, etr4);
			}
			if (t % 200000 == 5000) {
				E.x = -1;
				E.y = rand() % w;
				etr5 = "#";
			mvaddstr(E.x, E.y, etr5);
			}
/////////////////ここまで//////////////////

/////////////プレイヤーのキー操作///////////
			switch (key) {
			case KEY_UP:	
				if (y > 0) { 
					y--; 
					erase(); 
				}
				break;		
			case KEY_DOWN:
				if (y < h - 1) {
					y++; 
					erase(); 
				}
				break;
			case KEY_LEFT:	
				if (x > 0) { 
					x--;  
					erase(); 
				}
				break;
			case KEY_RIGHT:	
				if (x < w - 1) {
					x++;	
					erase(); 
				}
				break;

			}

///////////ここまで/////////////////



//////////ラインの自動移動///////////
			if (t % 700 == 0) {
				erase();
				L1.x--;

			}
			if (t % 3000 == 0 && t > 10000) {
				erase();
				L2.y++;
			}
/////////ここまで///////////



/////////#の自動移動//////////
			if (t % 5000 == 0) {
				erase();
				A.x++;
			}
			if (t % 5000 == 0) {
				erase();
				B.x++;
			}
			if (t % 3000 == 0) {
				erase();
				C.x++;
			}
			if (t % 3000 == 0) {
				erase();
				D.x++;
			}
			if (t % 4000 == 0) {
				erase();
				E.x++;
			}
//////////////ここまで/////////////


			attrset(COLOR_PAIR(1));
			mvaddstr(y, x, str);
			mvprintw(1, 1, "count = %d", cnt);
			refresh();


/////////移動後の位置でラインと#を描画/////////			
			Writingline1(L1.x, L1.y);
			Writingline2(L2.x, L2.y);
			mvaddstr(A.x, A.y, etr1);
			mvaddstr(B.x, B.y, etr2);
			attrset(COLOR_PAIR(4));
			mvaddstr(C.x, C.y, etr3);
			attrset(COLOR_PAIR(4));
			mvaddstr(D.x, D.y, etr4);
			attrset(COLOR_PAIR(5));
			mvaddstr(E.x, E.y, etr5);
//////////////ここまで///////////////


///////////ラインとの当たり判定//////////////
			if ((x == L1.x && (y <= L1.y || y > L1.y + 10)) || ((x <= L2.x || x > L2.x + 15) && y == L2.y)) {
				check = 1;
			}
///////////ここまで////////////


////////#との当たり判定, 当たるとcnt++,cnt--,cnt+=2 /////////////////
			if ((x == A.y && y == A.x) && ((etr1 == "#"))) {
				cnt++;
				etr1 = " ";
			}
			else if ((x == B.y && y == B.x) && (etr2 == "#")) {
				cnt++;
				etr2 = " ";
			}
			else if ((x == C.y && y == C.x) && (etr3 == "#")) {
				cnt--;
				etr3 = " ";
			}
			else if ((x == D.y && y == D.x) && (etr4 == "#")) {
				cnt--;
				etr4 = " ";
			}
			else if ((x == E.y && y == E.x) && (etr5 == "#")) {
				cnt+=2;
				etr5 = " ";
			}
///////////ここまで/////////////


//////////クリア条件//////////
			if (cnt >= 5) {
				check = 2;
			}
////////////ここまで////////


////////////GAMEOVERかGAMECLEARへの遷移////////////
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

			mvprintw(25, 36, "time = %d [秒]", (t2 - t1));
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
			mvprintw(23, 36, "time = %d [秒]" , (t2 - t1));
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
////////////////ここまで///////////////////////
	endwin();
	return (0);
}

//設定をすべて初期値に戻す
void iniLine() {
	t = 0;
	L1.x = 130;
	L2.y = -1;
	y = h / 2;
	x = w / 2;
	A.y = -1; 
	B.y = -1; 
	C.y = -1; 
	D.y = -1; 
	E.y = -1;

}