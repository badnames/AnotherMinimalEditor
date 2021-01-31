#include <curses.h>

int main() {
	
	Window window([](char input) {if (input == 'q')

	mvaddstr(10, 10, "Hello World!");
	refresh();

	

	return 0;
}
