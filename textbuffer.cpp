#include "textbuffer.hpp"

#include <stdexcept>

TextBuffer::TextBuffer(std::string originalText) {
	m_originalText = originalText;
	m_pieceTable.push_back({false, 0, originalText.length()});
}

TextBuffer::~TextBuffer() {}

void TextBuffer::addText(std::string text, long unsigned int offset) {
	PieceTableEntry newEntry = {true, m_editText.length(), m_editText.length() + text.length()}; 
	
	m_editText = m_editText + text;

	// Find out which entry needs to be modified.
	long unsigned int textLength = 0;
	PieceTableEntry currEntry;
	
	// The iterator is needed to remove the old entry later.
	std::vector<PieceTableEntry>::iterator it = m_pieceTable.begin();
	while (it != m_pieceTable.end()) {
		currEntry = *it;
		textLength += currEntry.end - currEntry.start;
		
		if (textLength >= offset) {
			break;
		}

		it++;
	}
	
	// Split the old entry if required
	if (textLength > offset) {
		PieceTableEntry newEntryLeft = currEntry;
		PieceTableEntry newEntryRight = currEntry;
		
		auto splitPosition = offset - (textLength - (currEntry.end - currEntry.start));
		newEntryLeft.end = splitPosition;
		newEntryRight.start = splitPosition;

		m_pieceTable.erase(it);
		if (it == m_pieceTable.end()) {
			m_pieceTable.push_back(newEntryLeft);
			m_pieceTable.push_back(newEntry);
			m_pieceTable.push_back(newEntryRight);
		} else {
			m_pieceTable.insert(it, newEntryLeft);
			m_pieceTable.insert(++it, newEntry);
			m_pieceTable.insert(++it, newEntryRight);
		}
	} else if (textLength == offset) {
		m_pieceTable.insert(++it, newEntry);
	}
	
	// update caches
	if (m_linesValid) {
		m_lines += TextBuffer::countLinesInString(text);
	}

	if (m_lengthValid) {
		m_length += text.length();
	}

	m_combinedTextValid = false;
}

std::string& TextBuffer::getText() {
	if (m_combinedTextValid) {
		return m_combinedText;
	}

	std::string combinedText;

	for (auto entry : m_pieceTable) {
		std::string subString;

		if (entry.isInEditBuffer) {
			subString = m_editText.substr(entry.start, entry.end - entry.start);
		} else {
			subString = m_originalText.substr(entry.start, entry.end - entry.start);
		}

		combinedText = combinedText + subString;
	}

	m_combinedText = combinedText;
	m_combinedTextValid = true;

	return m_combinedText;
}

void TextBuffer::removeText(long unsigned int start, long unsigned int end) {
	
	//find the first entry that contains text that should be removed
	auto it = m_pieceTable.begin();
	long unsigned int charCount = 0;

	while (it != m_pieceTable.end()) {
		auto relativeStart = start - charCount;
		auto relativeEnd = end - charCount;
		
		// skip all entries before until the first one that needs to be changed
		if (charCount < start)
			continue;
		
		
		if (it->start < relativeStart && it->end <= relativeEnd) {
			it->end = relativeStart;
		} else if (it->start >= relativeStart && it->end <= relativeEnd) {
			m_pieceTable.erase(it);	
		} else if (it->start >= relativeStart && it->end > relativeEnd) {
			it->start = relativeEnd;
			break;
		}
		
		charCount += it->end - it->start;
		it++;
	}

	// invalidate chaches
	m_linesValid = false;
	m_combinedTextValid = false;
	m_lengthValid = false;
	
}

long unsigned int TextBuffer::getLength() {
	if (m_lengthValid) {
		return m_length;
	}

	m_length = 0;

	for (auto entry : m_pieceTable) {
		m_length += entry.end - entry.start;
	}

	m_lengthValid = true;
	return m_length;
}

long unsigned int TextBuffer::getLines() {
	if (!m_linesValid) {
		if (!m_combinedTextValid) getText();
		m_lines = TextBuffer::countLinesInString(m_combinedText);
		m_linesValid = true;
	}
	
	return m_lines;
}

long unsigned int TextBuffer::cursorPositionToStringOffset(unsigned int x, unsigned int y) {
	if (y > getLines()) {
		throw std::invalid_argument("cursor y position is out of bounds");
	}

	std::string& text = getText();
	long unsigned int length = 0;	

	for (long unsigned int i = 0; i < text.length(); i++) {
		length++;

		if (y > 0 && text[i] == '\n') {
			y--;
			continue;
		}
		
		if (i == text.length() - 1) {
			throw new std::invalid_argument("cursor x position out of bounds");
		}

		if (x > 0) {
			break;
		}
	}

	return length;
}

long unsigned int TextBuffer::countLinesInString(std::string& str) {
	long unsigned int newLines = 0;	

	for (long unsigned int i = 0; i < str.size(); i++) {
		if (str[i] == '\n') {
			newLines++;
		}
	}

	return newLines;
}
