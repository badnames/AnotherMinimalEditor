#include "window.hpp"
#include <tuple>
#include <curses.h>

int main() {
	
	Window window([](Window* window, char input) {
				if (input == 'q') {
					window->quit();
				}
			},
		      [](Window* window) {
		      		int x, y;
				std::tie(x, y) = window->getDimensions();
				
				window->setCursor(x / 2, y / 2);
				window->writeTextAtCursor("Hallo Welt!");
			});
			

	window.eventLoop();
	
	return 0;
}
