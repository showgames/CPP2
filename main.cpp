#include <ncurses.h>
#include "Stage.hpp"

int
inputKey()
{
	int key;
	int dir;
	while(1) {
		key = getch();
		switch(key) {
			case KEY_UP: dir = 0; break;
			case KEY_DOWN: dir = 1; break;
			case KEY_LEFT: dir = 2; break;
			case KEY_RIGHT: dir = 3; break;
		}
		if (dir >= 0 && dir <= 3) break;
	}
	return dir;
}

int
main(int argc, char* argv[]) {
	char stageData[] = "#########..p   ##oo    ##      #########";
	int sizeX = 8;
	int sizeY = 5;
	int dir;
	Stage stage;
	stage.m_init(stageData, sizeX, sizeY);

	initscr(); //端末制御開始
	noecho();
	cbreak();
	keypad(stdscr, TRUE);

	while(1) {
		erase();
		refresh();
		stage.m_draw();
		if(stage.m_checkFinish()) break;
		dir = inputKey();
		stage.m_update(dir);
	}
	printw("Congratulations! You win.");
	getch();
	endwin();  //端末制御終了
	return 0;
}