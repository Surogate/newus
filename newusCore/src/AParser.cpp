

#include <iostream>
#include <sstream>

#include "AParser.hpp"

AParser::AParser(const std::string& buffer) : _index(0), _size(buffer.size()), _buffer(buffer)
{}

AParser::~AParser()
{}

AParser::AParser(const AParser& orig) : _index(orig._index), _size(orig._size), _buffer(orig._buffer)
{}

AParser& AParser::operator=(const AParser&) {
	return *this;
}

bool AParser::consume_str(const std::string& str) {
	if (peek(str)) {
		_index += str.size();
		return true;
	}
	return false;
}

bool AParser::consume(const boost::function< bool() >& func) {
	unsigned int tmp = _index;
	if (!func()) {
		_index = tmp;
		return false;
	}
	return true;
}


bool AParser::consume_blanks() {
	if (consume_blanks_simple()) {
		while (consume_blanks_simple());
		return true;
	}
	return false;
}

bool AParser::consume_until(char c) {
	unsigned int i = 0;
	while (peek(c) && consume(getChar()))
		i++;

	return i > 0;
}

bool AParser::consume_until_str(const std::string& delim) {
	unsigned int i = 0;
	
	while (!peek(delim) && consume(getChar()))
		i++;
	
	return i > 0;
}

bool AParser::consume_until(const boost::function< bool() >& delim) {
	unsigned int i = 0;
	
	while (!consume(delim) && consume(getChar()))
		i++;

	return i > 0;
}

bool AParser::read_some(std::string& in, unsigned int size) {
	if (_index + size < _buffer.size()) {
		unsigned int i = 0;
		while (i < size) {
			in.push_back(getChar());
			_index++;
			i++;
		}
		return true;
	}
	return false;
}

bool AParser::read_until(std::string& in, char delim) {
	unsigned int i = 0;

	while (!eof() && !peek(delim)) {
		in.push_back(getChar());
		i++;
		_index++;
	}
	if (i > 0)
		return true;
	return false;
}

bool AParser::read_until(std::string& in, const std::string& delim) {
	unsigned int i = 0;

	while (!eof() && !peek(delim)) {
		in.push_back(getChar());
		i++;
		_index++;
	}
	if (i > 0)
		return true;
	return false;
}

bool AParser::read_until_func(std::string& in, const boost::function< bool() >& delim) {
	unsigned int i = 0;
	
	while (!eof() && !delim()) {
		in.push_back(getChar());
		i++;
		_index++;
	}
	if (i > 0)
		return true;
	return false;
}

bool AParser::read_quoted_text(std::string& in) {
	return consume('"') && read_until(in, '"') && consume('"');
}

void AParser::displayText() const {
	if (!eof()) {
		std::cout << &_buffer[_index] << std::endl;
	} else {
		std::cout << "EOF" << std::endl;
	}
}

unsigned int AParser::findIntLength() const {
	unsigned int tmp = _index;
	unsigned int result = 0;

	while (_buffer[tmp] == '-' || _buffer[tmp] == '+') {
		tmp++;
	}

	while (_buffer[tmp] >= '0' && _buffer[tmp] <= '9') {
		result++;
		tmp++;
	}
	return result;
}

unsigned int AParser::findFloatLenght() const {
	unsigned int tmp = _index;
	unsigned int result = 0;

	while (_buffer[tmp] == '-' || _buffer[tmp] == '+') {
		tmp++;
	}

	while ((_buffer[tmp] >= '0' && _buffer[tmp] <= '9') || _buffer[tmp] == '.') {
		result++;
		tmp++;
	}
	return result;
}

bool AParser::readInt(int& in) {
	return readIntNumber(in);
}

bool AParser::readChar(char& in) {
	return readIntNumber(in);
}

bool AParser::readInt(unsigned int& in) {
	return readIntNumber(in);
}

bool AParser::readChar(unsigned char& in) {
	return readIntNumber(in);
}

bool AParser::readShort(short& in) {
	return readIntNumber(in);
}

bool AParser::readShort(unsigned short& in) {
	return readIntNumber(in);
}

bool AParser::readFloat(float& in) {
	return readFloatNumber(in);
}

bool AParser::readDouble(double& in) {
	return readFloatNumber(in);
}

void AParser::debug_dumpPoint(unsigned int size) const {
	std::cout << "## " << _index << std::endl;
	std::cout << _buffer.substr(_index, size);
}