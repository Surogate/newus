
#include "XMLParser.hpp"

XMLParser::XMLParser(std::istream& stream) : AParser(stream)
{}

XMLParser::~XMLParser()
{}

XMLParser::XMLParser(const XMLParser& orig) : AParser(orig)
{}

bool XMLParser::parseRss() {
    return true;
}