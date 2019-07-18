#include "stdafx.h"
#include <curses.h>
#include "Myfinal.h"

// タイトルを表示
void Title()
{
	clear();
	bkgd(COLOR_PAIR(1));
	mvprintw(LINES / 2 - 4, (COLS - 70) / 2, " GGGG    AAA   M     M  EEEEE        SSSS   TTTTTTT   AAA   RRRR    TTTTTTT    ");
	mvprintw(LINES / 2 - 3, (COLS - 70) / 2, "G    G  A   A  MM   MM  E           S    S     T     A   A  R   R      T");
	mvprintw(LINES / 2 - 2, (COLS - 70) / 2, "G       A   A  M M M M  E           S          T     A   A  R    R     T");
	mvprintw(LINES / 2 - 1, (COLS - 70) / 2, "G       AAAAA  M  M  M  EEEEE       S          T     AAAAA  RRRRR      T");
	mvprintw(LINES / 2, (COLS - 70) / 2,     "G       A   A  M     M  E            SSSSS     T     A   A  R  R       T");
	mvprintw(LINES / 2 + 1, (COLS - 70) / 2, "G   GGG A   A  M     M  E                 S    T     A   A  R   R      T");
	mvprintw(LINES / 2 + 2, (COLS - 70) / 2, "G    G  A   A  M     M  E           S     S    T     A   A  R    R     T");
	mvprintw(LINES / 2 + 3, (COLS - 70) / 2, " GGGG   A   A  M     M  EEEEE       SSSSSS     T     A   A  R     R    T");

	attrset(COLOR_PAIR(6));
	mvaddstr(2, 4, "***RULE****");
	for (int i = 3; i <= 9; i++) {
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
	mvprintw(LINES / 2, (COLS - 70) / 2,     "G       A   A  M     M  E           O    O  V     V  E      R  R       ");
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