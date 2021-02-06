#include "window.hpp"
#include "textbuffer.hpp"
#include <tuple>
#include <curses.h>
#include <memory>
#include <string>

int main() {
	std::shared_ptr<TextBuffer> textbuffer(new TextBuffer(""));

	Window window([textbuffer](Window* window, int input) {
				//esc key
				switch (input) {
					//case
					case 27:
						window->quit();
						break;
					
					//backspace
					case KEY_BACKSPACE:
						textbuffer->removeText(textbuffer->getLength() - 1L, textbuffer->getLength());
					break;

					default:
						textbuffer->addText(std::string(1, input), textbuffer->getLength());
						break;
				}

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
