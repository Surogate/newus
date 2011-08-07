/* 
 * File:   AParser.hpp
 * Author: fancel
 *
 * Created on 29 July 2011, 00:01
 */

#ifndef APARSER_HPP
#define	APARSER_HPP

#include <istream>

class AParser {
public:
    AParser(std::string& buffer);
    AParser(const AParser& orig);
    ~AParser();

    inline bool consume(char c) {
        if (!eof() && c == _buffer[_index]) {
            _index++;
            return true;
        }
        return false;
    }

    inline bool consume(const std::string& str) {
        unsigned int tmp = _index;
        unsigned int i = 0;
        while (!eof() && i < str.size() && str[i] == _buffer[_index]) {
            ++i;
            ++_index;
        }
        if (i < str.size()) {
            _index = tmp;
            return false;
        }
        return true;
    }

    inline bool eof() const {
        return _index >= _buffer.size();
    }

    inline bool read_char(char& c) {
        if (!eof()) {
            c = _buffer[_index];
            _index++;
            return true;
        }
        return false;
    }

    inline bool read_some(std::string& in, unsigned int size) {
        if (_index + size < _buffer.size()) {
            unsigned int i = 0;
            while (i < size) {
                in.push_back(_buffer[_index]);
                _index++;
                i++;
            }
            return true;
        }
        return false;
    }

    inline bool read_until(std::string& in, char c) {
        unsigned int i = 0;

        while (!eof() && consume(c)) {
            in.push_back(_buffer[_index]);
            i++;
            _index++;
        }
       if (i > 0)
           return true;
        return false;
    }

    inline bool read_until(std::string& in, const std::string& str) {
        unsigned int i = 0;

        while (!eof() && consume(str)) {
            in.push_back(_buffer[_index]);
            i++;
            _index++;
        }
        if (i > 0)
            return true;
        return false;
    }

private:
    AParser & operator=(const AParser&);

    unsigned int _index;
    std::string& _buffer;
};

#endif	/* APARSER_HPP */

