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

#include "Article.hpp"
#include "RequestForge.hpp"

class Feed {
public:
    Feed(FeedManager& fm, const std::string& addr);
    ~Feed();

    void GetArticle();

private:
    void parseAddr(const std::string& addr);

    RequestForge _forge;
    std::deque< Article > _ArticleList;
    std::string _host;
    std::string _path;
};

#endif	/* FEED_HPP */
