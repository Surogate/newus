
#include <iostream>

#include "Feed.hpp"
#include "FeedManager.hpp"

Feed::Feed(FeedManager& fm, const std::string& addr) : _forge(fm), _host(), _path() {
	parseAddr(addr);
	std::cout << "host " << _host << std::endl;
	std::cout << "path " << _path << std::endl;
}

void Feed::parseAddr(const std::string& addr) {
	unsigned int index = 0;
	while (addr[index] != 'w') index++;
	unsigned int start = index;
	while (addr[index] != '/') index++;
	unsigned int end = index;
	unsigned int pathEndIndex = addr.size() - 1;
	while (addr[pathEndIndex] != '/') pathEndIndex--;

        if (start + (end - start) < addr.size() && end + (pathEndIndex - end) < addr.size()) {
            std::cout << "parse ok" << std::endl;
        }
	_host = addr.substr(start, end - start);
	_path = addr.substr(end, pathEndIndex - end);
}