#include "window.hpp"
#include "textbuffer.hpp"
#include <tuple>
#include <curses.h>
#include <memory>
#include <string>

int main() {
	std::shared_ptr<TextBuffer> textbuffer(new TextBuffer(""));

	Window window([textbuffer](Window* window, char input) {
				//esc key
				if (input == 27) {
					window->quit();
				}

				textbuffer->addText(std::string(1, input), textbuffer->getLength());
			},
		      [textbuffer](Window* window) {
		      		int x, y;
				std::tie(x, y) = window->getDimensions();
				
				window->setCursor(0, 0);
				window->writeTextAtCursor(textbuffer->getText());
			});
			

	window.eventLoop();
	
	return 0;
}
