/* 
 * File:   main.cpp
 * Author: fancel
 *
 * Created on 28 July 2011, 23:50
 */

#include <iostream>
#include <fstream>

#include "FeedManager.hpp"
#include "Feed.hpp"
#include "XMLParser.hpp"

void testNetwork() {
	FeedManager manager;

	std::string input = "http://www.rockpapershotgun.com/feed/";
	
	Feed test(manager, input);

	test.fetchArticle();
}

void getFileFromFile(std::string& in, const std::string& from) {
	std::ifstream file(from);

	if (file.good()) {
		file.seekg(0, std::ios::end);
		std::size_t size = static_cast<std::size_t>(file.tellg());
		if (size) {
			file.seekg(0, std::ios::beg);
			std::vector< char > buffer(size);
			file.read(buffer.data(), size);
			if (file.gcount()) {
				in.assign(buffer.begin(), buffer.end());
			} else {
				std::cout << "read fail" << std::endl;
			}
		} else {
			std::cout << "file empty" << std::endl;
		}
	} else {
		std::cout << "loading " << from << " fail" << std::endl;
	}
}

void testParser() {
	std::string text;
	XMLParser::Balise balise;

	getFileFromFile(text, "rssTest.txt");
	if (text.size()) {
		XMLParser parser(text);
		if (parser.consumeHeader()) {
			XMLParser::ArticleList list;
			if (parser.getArticle(list)) {
				for (unsigned int i = 0; i < list.size(); i++) {
					std::cout << list[i]->title << std::endl;
					std::cout << list[i]->body << std::endl << std::endl;
				}
			}
			else {
				std::cout << "getArticle fail" << std::endl;
			}
		} else {
			std::cout << "error at " << parser.getIndex() << std::endl;
			std::cout << "letter " << parser.getChar()  << " " << static_cast<int>(parser.getChar()) << std::endl;
		}
	} else {
		std::cout << "text empty" << std::endl;
	}
}

void testAgregator() {
	FeedManager man;

	man.addFeed("http://www.rockpapershotgun.com/feed/");
	man.addFeed("http://www.pcinpact.com/include/news.xml");

	const FeedManager::ArticleList& list = man.getList();

	FeedManager::ArticleList::const_iterator it = list.begin();
	FeedManager::ArticleList::const_iterator ite = list.end();

	while (it != ite) {
		std::cout << it->get()->title << std::endl;
		std::cout << it->get()->pubDate << std::endl;
		//std::cout << it->get()->body << std::endl;
		it++;
	}
}

int main(void) {
	testAgregator();
	std::cin.get();
	return 0;
}

