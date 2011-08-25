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
#include "Article.hpp"

class XMLParser : public AParser {
public:
	typedef std::map< std::string /* arg name */, std::string /* arg value */ > ArgMap;
	struct Balise {
		std::string name;
		ArgMap arg;
		std::string body;
	};

	XMLParser(const std::string& stream);
	~XMLParser();
	XMLParser(const XMLParser& orig);

	bool getArticle(std::deque< Article >& list);
	bool spaceOrEqualSign() const;
	bool endArg();

	bool consumeHeader();

	bool parserItem(Article& in);

	bool consumeEndName(const std::string& name);
	bool consumeName(const std::string& name);

	bool parseCategory(std::deque<Balise>& cat);

	bool parseBalise(Balise& in);
	bool parseBalise(Balise& in, const std::string& name);
	bool parseArg(ArgMap& arg);
	bool parseBaliseSimple(std::string& in, const std::string& name);
	bool parseBaliseClose(const std::string& name);
};

#endif	/* XMLPARSER_HPP */

