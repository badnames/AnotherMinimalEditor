#ifndef _WINDOW_HPP_
#define _WINDOW_HPP_

#include <functional>

#include <curses.h>

/* Manages the input and output on the console using ncurses.
 * */
class Window {
private:
	WINDOW *m_window;
	bool m_running;
	
	//callbacks
	std::function<void(char)> m_onCharPressed; 
public:
	Window(std::function<void(char)> onCharPressed);
	~Window();

	void eventLoop();
	
	WindowDimensions getDimensions();
};

struct WindowDimensions {
	const unsigned int width;
	const unsigned int height;
};

#endif
