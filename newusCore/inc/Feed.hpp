/* 
 * File:   Feed.hpp
 * Author: fancel
 *
 * Created on 29 July 2011, 00:26
 */

#ifndef FEED_HPP
#define	FEED_HPP

class FeedManager;

#include "RequestForge.hpp"

class Feed {
public:
	Feed(FeedManager& fm, const std::string& addr);
	~Feed();

private:
	void parseAddr(const std::string& addr);

	RequestForge _forge;
	std::string _host;
	std::string _path;
};

#endif	/* FEED_HPP */

