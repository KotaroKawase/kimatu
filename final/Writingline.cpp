#include "stdafx.h"
#include <curses.h>
#include "Myfinal.h"

//c–_‚Ì•`‰æ
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
//‰¡–_‚Ì•`‰æ
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