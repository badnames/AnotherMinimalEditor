#ifndef _WINDOW_HPP_
#define _WINDOW_HPP_

#include <tuple>
#include <functional>
#include <string>

#include <curses.h>


/* Manages the input and output on the console using ncurses.
 * */
class Window {
private:
	WINDOW *m_window;
	bool m_running;
	
	// callbacks
	// executed when getch() returns a key
	std::function<void(Window*, char)> m_onCharPressed;
	//executed every time the window should be redrawn
	std::function<void(Window*)> m_onUpdate;
public:
	Window(std::function<void(Window*, char)> onCharPressed,
	       std::function<void(Window*)> onUpdate);
	~Window();

	void eventLoop();
	void quit();

	void setCursor(int x, int y);
	void writeTextAtCursor(std::string& text);
	
	//coordinate format is x,y instead of curses' y,x
	std::tuple<int, int> getDimensions();
	std::tuple<int, int> getCursorPosition();
};


#endif
