
#include "AParser.hpp"


AParser::AParser(std::istream& stream) : _stream(stream), _index(0)
{}

AParser::~AParser()
{}

AParser::AParser(const AParser& orig) : _stream(orig._stream), _index(0)
{}

AParser& AParser::operator=(const AParser& orig) {
	return *this;
}



