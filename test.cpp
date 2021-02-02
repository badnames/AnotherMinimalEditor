#include <iostream>
#include <cassert>
#include <string>

#include "textbuffer.hpp"

void testTextBufferConstructor() {
	std::cout << "Testing textbuffer construcor...";	
	
	TextBuffer textbuffer("Hello World!");

	std::string test1("Hello World!");
	assert(test1.compare(textbuffer.getText()) == 0);
	
	std::cout << "DONE" << std::endl;
}

void testTextBufferAddText() {
	std::cout << "Testing textbuffer.addText()...";
	
	TextBuffer textbuffer("Hello World!");
	textbuffer.addText("you beautiful ", 6);

	std::string test1("Hello you beautiful World!");
	assert(test1.compare(textbuffer.getText()) == 0);
	
	textbuffer.addText("very ", 10);
	
	std::string test2("Hello you very beautiful World!");
	assert(test2.compare(textbuffer.getText()) == 0);

	std::cout << "DONE" << std::endl;
}

int main() {
	testTextBufferConstructor();
	testTextBufferAddText();
}
