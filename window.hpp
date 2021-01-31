#ifndef _WINDOW_HPP_
#define _WINDOW_HPP_

#include <functional>

#include <curses.h>

struct WindowDimensions {
	const unsigned int width;
	const unsigned int height;
};

/* Manages the input and output on the console using ncurses.
 * */
class Window {
private:
	WINDOW *m_window;
	bool m_running;
	
	//callbacks
	std::function<void(Window*, char)> m_onCharPressed; 
public:
	Window(std::function<void(Window*, char)> onCharPressed);
	~Window();

	void eventLoop();
	void quit();

	WindowDimensions getDimensions();
};


#endif
