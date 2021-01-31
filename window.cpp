#include "window.hpp"

#include <functional>

#include <curses.h>

Window::Window(std::function<void(Window*, char)> onCharPressed) {
	m_window = initscr();
	cbreak();
	noecho();
	clear();
	refresh();
	
	m_running = true;
	m_onCharPressed = onCharPressed;
}

Window::~Window() {
	endwin();
}

void Window::eventLoop() {
	while (m_running) {
		char input = getch();
		m_onCharPressed(this, input);	
	}
}

void Window::quit() {
	m_running = false;
}

WindowDimensions getDimensions() {
	//TODO get window size
	return WindowDimensions{0, 0};
}
