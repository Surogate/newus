
#include "AParser.hpp"

AParser::AParser(std::string& buffer) : _index(0), _buffer(buffer)
{}

AParser::~AParser()
{}

AParser::AParser(const AParser& orig) : _index(orig._index), _buffer(orig._buffer)
{}

AParser& AParser::operator=(const AParser&) {
	return *this;
}

bool AParser::consume(const std::string& str) {
	unsigned int tmp = _index;
	unsigned int i = 0;
	while (!eof() && i < str.size() && str[i] == getChar()) {
		++i;
		++_index;
	}
	if (i < str.size()) {
		_index = tmp;
		return false;
	}
	return true;
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
	if (consume('\r') || consume('\n') || consume('\t') || consume(' ')) {
		while (consume('\r') || consume('\n') || consume('\t') || consume(' '));
		return true;
	}
	return false;
}

bool AParser::consume_until(char c) {
	unsigned int i = 0;
	while (getChar() != c && consume(getChar()))
		i++;

	return i > 0;
}

bool AParser::consume_until(const std::string& delim) {
	unsigned int i = 0;
	
	while (!consume(delim) && consume(getChar()))
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

	while (!eof() && !consume(delim)) {
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

	while (!eof() && !consume(delim)) {
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
	
	while (!eof() && !consume(delim)) {
		in.push_back(getChar());
		i++;
		_index++;
	}
	if (i > 0)
		return true;
	return false;
}


