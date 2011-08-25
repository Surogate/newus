/* 
 * File:   Feed.hpp
 * Author: fancel
 *
 * Created on 29 July 2011, 00:26
 */

#ifndef FEED_HPP
#define	FEED_HPP

class FeedManager;

#include <deque>

#include <boost/smart_ptr.hpp>

#include "Article.hpp"
#include "RequestForge.hpp"
#include "XMLParser.hpp"

class Feed {
public:
	typedef XMLParser::ArticleList ArticleList;
	Feed(FeedManager& fm, const std::string& addr);
	~Feed();

	void fetchArticle();
	const ArticleList& getArticleList() const;

private:
	void parseAddr(const std::string& addr);

	RequestForge _forge;
	ArticleList _articleList;

	std::string _host;
	std::string _path;
};

#endif	/* FEED_HPP */
