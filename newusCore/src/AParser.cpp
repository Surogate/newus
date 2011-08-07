
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



