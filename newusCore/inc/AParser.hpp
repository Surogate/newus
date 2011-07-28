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
    AParser(std::istream& stream);
    AParser(const AParser& orig);
    ~AParser();

private:
    std::istream& _stream;
};

#endif	/* APARSER_HPP */

