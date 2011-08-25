
#include <boost/bind.hpp>
#include <boost/date_time.hpp>

#include "XMLParser.hpp"
#include "DateParser.hpp"

XMLParser::XMLParser(const std::string& stream) : AParser(stream)
{}

XMLParser::~XMLParser()
{}

XMLParser::XMLParser(const XMLParser& orig) : AParser(orig)
{}

bool XMLParser::getArticle(std::deque< Article >& list) {
	bool result = false;
	while (!eof()) {
		Article art;
		if (parserItem(art))
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

bool XMLParser::parserItem(Article& in) {
	consume_blanks();
	if (consumeName("item")) {
		Balise title;
		Balise description;
		Balise link;
		Balise guid;
		Balise author;
		Balise pubDate;
		std::deque< Balise > cat;

		while (parseBalise(title, "title")
			|| parseBalise(description, "description")
			|| parseBalise(link, "link")
			|| parseBalise(guid, "guid")
			|| parseBalise(author, "author")
			|| parseBalise(pubDate, "pubDate")
			|| parseCategory(cat));

		if (consumeEndName("item")) {
			in.title = title.body;
			in.link = link.body;
			in.body = description.body;
			in.guid = guid.body;
			in.author = author.body;
			
			DateParser parse(pubDate.body);

			bool result = parse(in.pubDate);
			
			if (result)
				std::cout << in.pubDate << std::endl;

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


