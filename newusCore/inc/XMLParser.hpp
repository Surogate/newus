/* 
 * File:   XMLParser.hpp
 * Author: fancel
 *
 * Created on 29 July 2011, 00:17
 */

#ifndef XMLPARSER_HPP
#define	XMLPARSER_HPP

#include <string>
#include <map>
#include <deque>

#include "AParser.hpp"

class XMLParser : AParser {
public:
	typedef std::map< std::string /* arg name */, std::string /* arg value */ > ArgMap;
	struct Balise {
		std::string name;
		ArgMap arg;
		std::string body;
		//std::deque< Balise > child;
	};

    XMLParser(std::string& stream);
    ~XMLParser();
    XMLParser(const XMLParser& orig);

    bool parseRss();
	bool spaceOrEqualSign();
	bool parseBalise(Balise& in);
	bool parseArg(ArgMap& arg);
	bool parseBaliseSimple(std::string& in, const std::string& name);
	bool parseBaliseClose(const std::string& name);
};

#endif	/* XMLPARSER_HPP */

