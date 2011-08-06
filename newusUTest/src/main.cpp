/* 
 * File:   main.cpp
 * Author: fancel
 *
 * Created on 28 July 2011, 23:50
 */

#include <iostream>

#include "FeedManager.hpp"
#include "Feed.hpp"

int main(void) {
    FeedManager manager;

	std::string input = "http://www.rockpapershotgun.com/feed/";
	
	Feed test(manager, input);

	test.GetArticle();

	std::cin.get();
    return 0;
}

