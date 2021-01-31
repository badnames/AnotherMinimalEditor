#include <curses.h>

int main() {
	initscr();
	cbreak();
	noecho();
	clear();
	refresh();

	bool running = true;
	while (running) {
		char input = getch();
		if (input == 'q') {
			running = false;
		}
	}

	endwin();

	return 0;
}
