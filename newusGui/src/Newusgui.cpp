
#include "Newusgui.hpp"

NewusGui::NewusGui(QWidget* parent)
	: QWidget(parent), _feedMan(), _list(), _newsView(), _layout()
{
	setup_connection();
	setup_ui();

	debug_testInsert();
}

NewusGui::~NewusGui()
{

}

void NewusGui::addFeed(const QString& value) {
	_feedMan.addFeed(value.toStdString());
}

void NewusGui::deleteFeed(const QString& value) {
	_feedMan.deleteFeed(value.toStdString());
}

void NewusGui::fetchingNews() {
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

void NewusGui::displayFeedlist() {
	_newsView(_list);	
}

void NewusGui::addArticle(const Article& value) {
	_list.append(ArticleWidget(value));
}

void NewusGui::setup_ui() {
	_layout.addWidget(&_newsView);

	setLayout(&_layout);
}

void NewusGui::setup_connection() {
	QObject::connect(this, SIGNAL(newsFetchted()), this, SLOT(displayFeedlist())); 
}

void NewusGui::debug_testInsert() {
	addFeed("http://www.rockpapershotgun.com/feed/");
	addFeed("http://www.pcinpact.com/include/news.xml");
	fetchingNews();
}
