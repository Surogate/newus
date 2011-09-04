
#include <fstream>

#include <boost/thread.hpp>
#include <boost/make_shared.hpp>

#include "FeedManager.hpp"
#include "RequestForge.hpp"

FeedManager::FeedManager() : _io_service(), _feed(), _guid(), _list() {
	loadGuid();
	loadFeed();
}

FeedManager::~FeedManager() {
	saveGuid();
	saveFeed();
}

void FeedManager::loadFeed() {
	std::ifstream file("FeedSave.txt");

	if (file.good()) {
		std::string buffer;
		do {
			std::getline(file, buffer);
			if (buffer.size()) {
				addFeed(buffer);
			}
		} while (buffer.size());
	}
}

void FeedManager::saveFeed() const {
	std::ofstream file("FeedSave.txt", std::ios::trunc);

	if (file.good()) {
		FeedMap::const_iterator it = _feed.begin();
		FeedMap::const_iterator ite = _feed.end();

		while (it != ite) {
			file << it->first << '\n';
			++it;
		}
	}
}

void FeedManager::loadGuid() {
	std::ifstream file("GuidSave.txt");

	if (file.good()) {
		std::string buffer;
		do {
			std::getline(file, buffer);
			if (buffer.size()) {
				_guid.insert(buffer);
			}
		} while (buffer.size());
	}
}

void FeedManager::saveGuid() const {
	std::ofstream file("GuidSave.txt", std::ios::trunc);

	if (file.good()) {
		GuidUsed::const_iterator it = _guid.begin();
		GuidUsed::const_iterator ite = _guid.end();

		while (it != ite) {
			file << *it << '\n';
			++it;
		}
	}
}

FeedManager::Io_service& FeedManager::getIo_service() {
	return _io_service;
}

const FeedManager::Io_service& FeedManager::getIo_service() const {
	return _io_service;
}

void FeedManager::addFeed(const std::string& host) {
	if (!_feed.count(host)) {
		_feed[host] = Feed::FeedPtr(new Feed(*this, host));
	}
}

void FeedManager::deleteFeed(const std::string& host) {
	_feed.erase(host);
}

void FeedManager::addGuid(const std::string& guid) {	
	_guid.insert(guid);
}

void FeedManager::fetchArticle() {
	FeedMap::const_iterator it = _feed.begin();
	FeedMap::const_iterator ite = _feed.end();

	boost::thread_group threads;
	while (it != ite) {
		threads.create_thread(boost::bind(&Feed::fetchArticle, it->second));
		++it;
	}
	threads.join_all();

	it = _feed.begin();
	while (it != ite) {
		insertFeed(*it->second);
		++it;
	}
}

const FeedManager::ArticleList& FeedManager::getList() const {
	return _list;
}

void FeedManager::insertFeed(Feed& feed) {
	const Feed::ArticleList& list = feed.getArticleList();
	Feed::ArticleList::const_iterator it = list.begin();
	Feed::ArticleList::const_iterator ite = list.end();

	while (it != ite) {
		orderInsertList(*it);
		++it;	
	}
}

void FeedManager::orderInsertList(Article::ArticlePtr ptr) {
	if (_guid.count(ptr->guid) == 0) {
		if (!_list.size()) {
			_list.push_back(ptr);
			return;
		}
	
		ArticleList::iterator it = _list.begin();
		ArticleList::iterator ite = _list.end();

		while (it != ite && (*it)->pubDate > ptr->pubDate) {
			++it;
		}

		if (it != ite) {
			_list.insert(it, ptr);
		} else {
			_list.push_back(ptr);
		}
	}
}



