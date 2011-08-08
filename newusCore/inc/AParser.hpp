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
    AParser(std::string& buffer);
    AParser(const AParser& orig);
    ~AParser();

	inline char& getChar() {
		return _buffer[_index];
	}

	inline const char& getChar() const {
		return _buffer[_index];
	}

    inline bool consume(char c) {
        if (!eof() && c == getChar()) {
            _index++;
            return true;
        }
        return false;
    }

    inline bool eof() const {
        return _index >= _buffer.size();
    }

    inline bool read_char(char& c) {
        if (!eof()) {
            c = getChar();
            _index++;
            return true;
        }
        return false;
    }

	bool consume(const std::string& str);

	bool consume(const boost::function< bool() >& func); 

	bool consume_blanks();

	bool consume_until(char c);

	bool consume_until(const std::string& delim);

	bool consume_until(const boost::function< bool() >& delim);

    bool read_some(std::string& in, unsigned int size);

    bool read_until(std::string& in, char delim);

    bool read_until(std::string& in, const std::string& delim);

	bool read_until_func(std::string& in, const boost::function< bool() >& delim);

protected:
    unsigned int _index;
    std::string& _buffer;

private:
	AParser& operator=(const AParser& orig);
};

#endif	/* APARSER_HPP */

