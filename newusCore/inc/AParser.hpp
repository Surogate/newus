/* 
 * File:   AParser.hpp
 * Author: fancel
 *
 * Created on 29 July 2011, 00:01
 */

#ifndef APARSER_HPP
#define	APARSER_HPP

#include <string>

#include <boost/function.hpp>

class AParser {
public:
	AParser(const std::string& buffer);
	AParser(const AParser& orig);
	~AParser();

	inline unsigned int size() const {
		return _size;
	}

	inline unsigned int size_left() const {
		return _size - _index;
	}

	inline unsigned int getIndex() const {
		return _index;
	}

	inline const std::string& getBuffer() const {
		return _buffer;
	}

	inline const char& getChar() const {
		return _buffer[_index];
	}

	inline const char& getChar(unsigned int index) const {
		return _buffer[index];
	}

	inline bool consume(char c) {
		if (peek(c)) {
			_index++;
			return true;
		}
		return false;
	}

	inline bool consume_size(unsigned int size) {
		if (!eof(_index + size)) {
			_index += size;
			return true;
		}
		return false;
	}

	inline bool eof() const {
		return _index >= _size;
	}

	inline bool eof(unsigned int index) const {
		return index >= _size;
	}

	inline bool read_char(char& c) {
		if (!eof()) {
			c = getChar();
			_index++;
			return true;
		}
		return false;
	}

	inline bool peek(char c) const {
		return (!eof() && getChar() == c);
	}

	inline bool peek(const std::string& str) const {
		unsigned int i = _index;
		unsigned int o = 0;
		while (!eof(i) && o < str.size() && str[o] == getChar(i))
		{
			++o;
			++i;
		}
		return o >= str.size();
	}

	bool consume_str(const std::string& str);

	bool consume(const boost::function< bool() >& func); 

	bool AParser::consume_blanks_simple() {
		return consume('\r') 
			|| consume('\n') 
			|| consume('\t') 
			|| consume(' ') 
			|| consume('\r')
			|| consume('\a')
			|| consume('\f');
	}

	bool consume_blanks();

	bool consume_until(char c);

	bool consume_until_str(const std::string& delim);

	bool consume_until(const boost::function< bool() >& delim);

	bool read_some(std::string& in, unsigned int size);

	bool read_until(std::string& in, char delim);

	bool read_until(std::string& in, const std::string& delim);

	bool read_until_func(std::string& in, const boost::function< bool() >& delim);

	bool read_quoted_text(std::string& in);

	void displayText() const;

	bool readInt(int& in);
	
	bool readInt(unsigned int& in);

	bool readChar(char& in);

	bool readChar(unsigned char& in);

	bool readShort(short& in);

	bool readShort(unsigned short& in);

	bool readFloat(float& in);

	bool readDouble(double& in);

protected:
	unsigned int _index;
	unsigned int _size;
	const std::string& _buffer;

	void debug_dumpPoint(unsigned int size) const;

private:
	AParser& operator=(const AParser& orig);

	template <typename T>
	inline bool readIntNumber(T& in) {
		unsigned int size = findIntLength();

		if (size) {
			int sign = 1;
			std::string buf;
			buf.reserve(size);
			std::stringstream stream(buf);

			while (_buffer[_index] == '-' || _buffer[_index] == '+') {
				if (_buffer[_index] == '-')
					sign *= -1;
				_index++;
			}

			while (_buffer[_index] >= '0' && _buffer[_index] <= '9') {
				stream << _buffer[_index];
				_index++;
			}
			stream >> in;
			in *= sign;
			return true;
		}
		return false;
	}

	template <typename T>
	inline bool readFloatNumber(T& in) {
		unsigned int size = findFloatLenght();

		if (size) {
			int sign = 1;
			std::string buf;
			buf.reserve(size);
			std::stringstream stream(buf);

			while (_buffer[_index] == '-' || _buffer[_index] == '+') {
				if (_buffer[_index] == '-')
					sign *= -1;
				_index++;
			}

			while ((_buffer[_index] >= '0' && _buffer[_index] <= '9') || _buffer[_index] == '.') {
				stream << _buffer[_index];
				_index++;
			}
			stream >> in;
			in *= sign;
			return true;
		}
		return false;
	}

	unsigned int findIntLength() const;
	unsigned int findFloatLenght() const;
};

#endif	/* APARSER_HPP */

