
#include "newusgui.hpp"

newusGui::newusGui(QWidget* parent)
	: QWidget(parent), _feedMan(), _list(), _newsView(), _layout()
{
	setup_connection();
	setup_ui();

	debug_testInsert();
}

newusGui::~newusGui()
{

}

void newusGui::addFeed(const QString& value) {
	_feedMan.addFeed(value.toStdString());
}

void newusGui::deleteFeed(const QString& value) {
	_feedMan.deleteFeed(value.toStdString());
}

void newusGui::fetchingNews() {
	_feedMan.fetchArticle();

	const ArticleList& list = _feedMan.getList();

	ArticleList::const_iterator it = list.begin();
	ArticleList::const_iterator ite = list.end();

	while (it != ite) {
		addArticle(*(it->get()));
		++it;
	}
	emit newsFetchted();
}

void newusGui::displayFeedlist() {
	_newsView(_list);	
}

void newusGui::addArticle(const Article& value) {
	_list.append(ArticleWidget(value));
}

void newusGui::setup_ui() {
	_layout.addWidget(&_newsView);

	setLayout(&_layout);
}

void newusGui::setup_connection() {
	QObject::connect(this, SIGNAL(newsFetchted()), this, SLOT(displayFeedlist())); 
}

void newusGui::debug_testInsert() {
	addFeed("http://www.rockpapershotgun.com/feed/");
	addFeed("http://www.pcinpact.com/include/news.xml");
	fetchingNews();
}
