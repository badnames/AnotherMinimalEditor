#include "window.hpp"
#include <curses.h>

int main() {
	
	Window window([](Window* window, char input) {
				if (input == 'q') {
					window->quit();
				}
			});
			

	mvaddstr(10, 10, "Hello World!");
	refresh();
	
	window.eventLoop();
	
	return 0;
}
