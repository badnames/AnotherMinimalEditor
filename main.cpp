#include <curses.h>

int main() {
	initscr();
	cbreak();
	noecho();
	clear();
	refresh();
	
	mvaddstr(10, 10, "Hello World!");
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
