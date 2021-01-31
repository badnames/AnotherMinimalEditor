#include "window.hpp"

#include <functional>

#include <curses.h>

Window::Window(std::function<void(char)> onCharPressed) {
	m_window = initscr();
	cbreak();
	noecho();
	clear();
	refresh();
	
	m_runnning = true;
}

Window::~Window() {
	endwin();
}

void Window::eventLoop() {
	while (m_running) {
		char input = getch();
		m_onCharPressed(input);	
	}
}

void Window::quit() {
	m_running = false;
}
