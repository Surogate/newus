
#include "XMLParser.hpp"

XMLParser::XMLParser(std::string& stream) : AParser(stream)
{}

XMLParser::~XMLParser()
{}

XMLParser::XMLParser(const XMLParser& orig) : AParser(orig)
{}

bool XMLParser::parseRss() {
    return true;
}