#ifndef TEXTBUFFER_H
#define TEXTBUFFER_H

#include <string>
#include <vector>
#include <stack>

struct PieceTableEntry {
	bool isInEditBuffer;
	unsigned int start;
	unsigned int end;
};

// Implements a piece table data structure
class TextBuffer {
private:
	std::string m_originalText;
	std::string m_editText;
	std::vector<PieceTableEntry> m_pieceTable;
	
	unsigned int m_lines;
public:
	TextBuffer();
	~TextBuffer();

	std::string getText(int start, int end);
	unsigned int getLength();	
	unsigned int getLines();
	
	void addText(std::string text, unsigned int position);
	void removeText(unsigned int start, unsigned int end);	
};

#endif
