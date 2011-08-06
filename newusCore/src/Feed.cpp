
#include <iostream>

#include "Feed.hpp"
#include "FeedManager.hpp"

Feed::Feed(FeedManager& fm, const std::string& addr) : _forge(fm), _host(), _path() {
	parseAddr(addr);
	_forge.ConnectTo(_host);
}

Feed::~Feed()
{}

void Feed::parseAddr(const std::string& addr) {
	unsigned int index = 0;
	while (addr[index] != 'w') index++;
	unsigned int start = index;
	while (addr[index] != '/') index++;
	unsigned int end = index;
	unsigned int pathEndIndex = addr.size() - 1;
	while (addr[pathEndIndex] != '/') pathEndIndex--;

	_host = addr.substr(start, end - start);
	_path = addr.substr(end, pathEndIndex - end + 1);
}

void Feed::GetArticle() {
	if (_forge.GetRequest(_host, _path))
		std::cout << "request ok" << std::endl;
	else {
		std::cout << "request fail" << std::endl;
		std::cout << _forge.getError() << std::endl;
	}

}