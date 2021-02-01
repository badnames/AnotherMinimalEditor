#include "window.hpp"

#include <functional>
#include <string>
#include <tuple>

#include <curses.h>

Window::Window(std::function<void(Window*, char)> onCharPressed,
	       std::function<void(Window*)> onUpdate) {
	m_window = initscr();
	cbreak();
	noecho();
	clear();
	refresh();
	
	m_running = true;
	m_onCharPressed = onCharPressed;
	m_onUpdate = onUpdate;
}

Window::~Window() {
	endwin();
}

void Window::eventLoop() {
	m_onUpdate(this);

	while (m_running) {
		auto input = getch();
		
		if(input != KEY_RESIZE) {
			m_onCharPressed(this, input);
		}
		
		clear();
		m_onUpdate(this);
		refresh();
	}
}

void Window::quit() {
	m_running = false;
}

void Window::writeTextAtCursor(std::string& text) {
	waddstr(m_window, text.c_str());
}

void Window::setCursor(int x, int y) {
	wmove(m_window, y, x);	
}

std::tuple<int, int> Window::getDimensions() {
	int x, y;
	
	getmaxyx(m_window, y, x);
	return {x, y};
}

std::tuple<int, int> Window::getCursorPosition() {
	int x, y;
	
	getyx(m_window, y, x);
	return {x, y};
}
