
#include "AParser.hpp"


AParser::AParser(std::istream& stream) : _stream(stream)
{}

AParser::~AParser()
{}

AParser::AParser(const AParser& orig) : _stream(orig._stream)
{}

