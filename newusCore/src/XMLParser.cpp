
#include <boost/bind.hpp>
#include <boost/date_time.hpp>

#include <string>

#include "XMLParser.hpp"
#include "DateParser.hpp"
#include "Singleton.hpp"
#include "Pool.hpp"

XMLParser::XMLParser(const std::string& stream) : AParser(stream)
{}

XMLParser::~XMLParser()
{}

XMLParser::XMLParser(const XMLParser& orig) : AParser(orig)
{}

bool XMLParser::getArticle(ArticleList& list) {
	bool result = false;
	while (!eof()) {
		boost::shared_ptr< Article > art = Singleton< Pool< Article > >::getInstance().getObj();
		if (parserItem(*art))
			list.push_back(art);
		else
			_index++;
		result = true;
	}
	return result;
}

bool XMLParser::consumeHeader() {
	consume_blanks();
	return consume_str("<?") && consume_until_str("?>") && consume_str("?>");
}

bool XMLParser::spaceOrEqualSign() const {
	return peek(' ') || peek('<') || peek('>') || peek("/>");
}

bool XMLParser::consumeEndName(const std::string& name) {
	return consume_str("</") && consume_str(name) && consume('>');
}

bool XMLParser::consumeName(const std::string& name) {
	return consume('<') && consume_str(name) && consume('>');
}

bool XMLParser::parseBaliseNotIn(
        BaliseMap& map,
        const std::string& noti) {
	Balise tmp;
	if (parseBaliseNot(tmp, noti)) {
		map[tmp.name] = tmp;
		return true;
	}
	return false;
}

bool XMLParser::parserItem(Article& in) {
	consume_blanks();
	if (consumeName("item")) {
		std::map<std::string, Balise> map; 
		std::deque< Balise > cat;

		while (parseCategory(cat) || parseBaliseNotIn(map, "/item"));

		if (consumeEndName("item")) {
			in.title = map["title"].body;
			in.link = map["link"].body;
			in.body = map["description"].body;
			in.guid = map["guid"].body;
			in.author = map["author"].body;
			in.comments = map["comments"].body;

			DateParser parse(map["pubDate"].body);

			bool result = parse(in.pubDate);

			for (unsigned int i = 0; i < cat.size(); ++i) {
				in.category.push_back(cat[i].body);
			}

			return result;
		}
	}
	return false;
}

bool XMLParser::parseCategory(std::deque<Balise>& cat) {
	Balise tmp;
	if (parseBalise(tmp, "category")) {
		cat.push_back(tmp);
		while (parseBalise(tmp, "category"))
			cat.push_back(tmp);
		return true;
	}
	return false;
}

bool XMLParser::parseBalise(Balise& in, const std::string& name) {
	consume_blanks();
	unsigned int tmp = _index;
	if (consume('<') && consume_str(name)) {
		in.name = name;
		parseArg(in.arg);
		if (consume_blanks() || consume('>')) {
			boost::function< bool() > delim = boost::bind(&XMLParser::consumeEndName, this, in.name);
			read_until(in.body, '<');
			while (!consume(delim)) {
				read_some(in.body, 1);
				read_until(in.body, '<');
			}
			return true;
		}
	}
	_index = tmp;
	return false;
}

bool XMLParser::parseBaliseNot(Balise& in, const std::string& nameToNot) {
	consume_blanks();
	unsigned int tmp = _index;
	if (consume('<') && read_until_func(in.name, boost::bind(&XMLParser::spaceOrEqualSign, this)) && in.name != nameToNot) {
		parseArg(in.arg);
		if (consume_blanks() || consume('>')) {
			boost::function< bool() > delim = boost::bind(&XMLParser::consumeEndName, this, in.name);
			read_until(in.body, '<');
			while (!consume(delim)) {
				read_some(in.body, 1);
				read_until(in.body, '<');
			}
			return true;
		}
	}
	_index = tmp;
	return false;
}

bool XMLParser::parseBalise(Balise& in) {
	consume_blanks();
	if (consume('<') && read_until_func(in.name, boost::bind(&XMLParser::spaceOrEqualSign, this))) {
		parseArg(in.arg);
		if (consume_blanks() || consume('>')) {
			boost::function< bool() > delim = boost::bind(&XMLParser::consumeEndName, this, in.name);
			read_until(in.body, '<');
			while (!consume(delim)) {
				read_some(in.body, 1);
				read_until(in.body, '<');
			}
			return true;
		}
	}
	return false;
}

bool XMLParser::parseArg(ArgMap& arg) {
	std::string name;
	std::string value;

	if (consume_blanks() && getChar() != '>' && read_until(name, '=') && consume('=') && read_quoted_text(value)) {
		arg[name] = value;
		name.clear();
		value.clear();

		while (consume_blanks() && read_until(name, '=') && consume('=') && read_quoted_text(value)) {
			arg[name] = value;
			name.clear();
			value.clear();
		}

		return true;
	}
	return false;
}

bool XMLParser::parseBaliseSimple(std::string& in, const std::string& name) {
	return consume('<') && consume_str(name) && consume_until('>') && read_until(in, "</") && consume_str(name) && consume('>');
}


