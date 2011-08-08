
#include <boost\bind.hpp>

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

bool XMLParser::spaceOrEqualSign() {
	return consume(' ') || consume('<') || consume('>');
}

bool XMLParser::parseBalise(Balise& in) {
	if (consume('<') && read_until_func(in.name, boost::bind(&XMLParser::spaceOrEqualSign, this))) {
		parseArg(in.arg);
	}
}

bool XMLParser::parseArg(ArgMap& arg) {
	consume_blanks();
	std::string name;
	std::string value;
	while (read_until(
}

bool XMLParser::parseBaliseSimple(std::string& in, const std::string& name) {
	return consume('<') && consume(name) && consume_until('>') && read_until(in, "</") && consume(name) && consume('>');
}