
#ifndef ARTICLE_H
#define ARTICLE_H

#include <string>
#include <vector>

struct Article {
	std::string uid;
	std::string title;
	std::string link;
	std::string body;
	std::vector< std::string > category;
};

#endif /* ARCTICLE_H */

