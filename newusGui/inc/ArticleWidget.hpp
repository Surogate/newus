
#ifndef ARTICLEWIDGET_HPP
#define ARTICLEWIDGET_HPP

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QTextEdit>
#include <QListWidgetItem>

#include "Article.hpp"

class ArticleWidget : public QWidget {
	Q_OBJECT

public:
	ArticleWidget(QWidget* parent = 0);
	ArticleWidget(const Article& article);
	ArticleWidget(const ArticleWidget& orig);
	ArticleWidget& operator=(const ArticleWidget& orig);
	~ArticleWidget();

private:
	QVBoxLayout _layout;
	QLabel _title;
	QLabel _authors;
	QTextEdit _body;

	void setup_ui();
};

#endif