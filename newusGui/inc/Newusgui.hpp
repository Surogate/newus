
#ifndef NEWUSGUI_HPP
#define NEWUSGUI_HPP

#include <QtGui/QMainWindow>
#include <QString>
#include <QVBoxLayout>
#include <QList>

#include "FeedManager.hpp"
#include "Article.hpp"

#include "ArticleWidget.hpp"
#include "ListViewer.hpp"

class NewusGui : public QWidget
{
	Q_OBJECT

	typedef FeedManager::ArticleList ArticleList;

public:
	NewusGui(QWidget* parent = 0);
	~NewusGui();

public slots:
	void addFeed(const QString& value);
	void deleteFeed(const QString& value);
	void displayFeedlist();
	void fetchingNews();

signals:
	void newsFetchted();

private:
	FeedManager _feedMan;
	QList<ArticleWidget> _list;
	ListViewer _newsView;
	QVBoxLayout _layout;

	void addArticle(const Article& value);
	void setup_ui();
	void setup_connection();
	void debug_testInsert();
};

#endif // NEWUSGUI_HPP

