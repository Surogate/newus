/* 
 * File:   XMLParser.hpp
 * Author: fancel
 *
 * Created on 29 July 2011, 00:17
 */

#ifndef XMLPARSER_HPP
#define	XMLPARSER_HPP

#include "AParser.hpp"

class XMLParser : AParser {
public:
    XMLParser(std::istream& stream);
    ~XMLParser();
    XMLParser(const XMLParser& orig);

    bool parseRss();
};

#endif	/* XMLPARSER_HPP */

