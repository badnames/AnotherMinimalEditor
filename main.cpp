#include "window.hpp"
#include "textbuffer.hpp"
#include <tuple>
#include <curses.h>
#include <memory>

int main() {
	std::shared_ptr<TextBuffer> textbuffer(new TextBuffer("Hello World!"));

	Window window([](Window* window, char input) {
				if (input == 'q') {
					window->quit();
				}
			},
		      [textbuffer](Window* window) {
		      		int x, y;
				std::tie(x, y) = window->getDimensions();
				
				window->setCursor(x / 2, y / 2);
				window->writeTextAtCursor(textbuffer->getText());
			});
			

	window.eventLoop();
	
	return 0;
}
