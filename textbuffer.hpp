#ifndef TEXTBUFFER_H
#define TEXTBUFFER_H

#include <string>
#include <vector>

struct PieceTableEntry {
	bool isInEditBuffer;
	long unsigned int start;
	long unsigned int end;
};

/* Implements a piece table for fast text editing.
 * */
class TextBuffer {
private:
	// piece table data
	std::string m_originalText;
	std::string m_editText;
	std::vector<PieceTableEntry> m_pieceTable;
	
	//cache data
	long unsigned int m_lines = 0;
	bool m_linesValid = false;

	std::string m_combinedText = "";
	bool m_combinedTextValid = false;

	long unsigned int m_length = 0;
	bool m_lengthValid = false;

	long unsigned int countLinesInString(std::string& str);
public:
	TextBuffer(std::string originalText);
	~TextBuffer();

	std::string& getText();

	long unsigned int getLength();
	long unsigned int getLines();

	void addText(std::string text, long unsigned int offset);
	void removeText(long unsigned int start, long unsigned int end);

	void removeCharAt(long unsigned int location);

	// Throws invalid_argument exception if cursor position
	// is out of bounds m_lengthValid;.
	long unsigned int cursorPositionToStringOffset(unsigned int x, unsigned int y);
};

#endif
