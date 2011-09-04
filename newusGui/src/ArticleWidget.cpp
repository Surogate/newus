
#include "ArticleWidget.hpp"

ArticleWidget::ArticleWidget(QWidget* parent) 
	: QWidget(parent), _layout(), _title(), _authors(), _body() {
	setup_ui();
}

ArticleWidget::ArticleWidget(const Article& article) 
	: QWidget(), _layout()
	, _title(QString::fromStdString(article.title))
	, _authors(QString::fromStdString(article.author))
	, _body(QString::fromStdString(article.body)) 
{
	setup_ui();
}

ArticleWidget::ArticleWidget(const ArticleWidget& orig) {
	this->operator=(orig);
}

ArticleWidget& ArticleWidget::operator=(const ArticleWidget& orig) {
	if (this != &orig) {
		_title.setText(orig._title.text());
		_authors.setText(orig._authors.text());
		_body.setPlainText(orig._body.toPlainText());
		setup_ui();
	}
	return *this;
}

ArticleWidget::~ArticleWidget() 
{}

void ArticleWidget::setup_ui() {
	_body.setReadOnly(true);

	_layout.addWidget(&_title);
	_layout.addWidget(&_authors);
	_layout.addWidget(&_body);

	setLayout(&_layout);
}