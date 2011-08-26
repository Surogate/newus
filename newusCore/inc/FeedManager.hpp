/* 
 * File:   FeedManager.hpp
 * Author: fancel
 *
 * Created on 29 July 2011, 00:35
 */

#ifndef FEEDMANAGER_HPP
#define	FEEDMANAGER_HPP

#include <map>
#include <string>
#include <set>

#include <boost/asio.hpp>
#include <boost/smart_ptr.hpp>

#include "Feed.hpp"

class FeedManager {
public:
	typedef boost::asio::io_service Io_service;
	typedef std::map< std::string /* host */, Feed::FeedPtr /* feed */ > FeedMap;
	typedef std::set< std::string /* guid */ > GuidUsed;
	typedef std::list< Article::ArticlePtr > ArticleList;

	FeedManager();
	~FeedManager();

	Io_service& getIo_service();
	const Io_service& getIo_service() const;

	void addFeed(const std::string& host);
	void deleteFeed(const std::string& host);
	const FeedMap& getFeed() const;
	void addGuid(const std::string& guid);
	const ArticleList& getList(); 

private:
	void loadGuid();
	void saveGuid() const;

	void insertFeed(Feed& feed);
	void orderInsertList(Article::ArticlePtr ptr);

	Io_service _io_service;
	FeedMap _feed;
	GuidUsed _guid;
	ArticleList _list;
};

#endif	/* FEEDMANAGER_HPP */

